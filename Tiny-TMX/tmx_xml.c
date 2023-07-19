#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tmxml.h"

#include "tmx.h"
#include "tmx_utils.h"

static void error_handler(const char* msg) {
	tmx_err(E_XDATA, "tmxml parser: error: %s", msg);
}

static int check_reader(tmxml_node_t* tree) {
	if (tree == NULL) {
		tmx_err(E_XDATA, "tmxml parser: error parsing XML");
		return 0;
	}
	return 1;
}

static int parse_property(tmxml_node_t* node, tmx_property* prop) {
	const char* value;

	if ((value = tmxmlElementGetAttr(node, "name"))) { /* name */
		prop->name = strdup(value);
	}
	else {
		tmx_err(E_MISSEL, "tmxml parser: missing 'name' attribute in the 'property' element");
		return 0;
	}

	if ((value = tmxmlElementGetAttr(node, "type"))) { /* type */
		prop->type = parse_property_type(value);
	}
	else {
		prop->type = PT_STRING;
	}

	if ((value = tmxmlElementGetAttr(node, "value"))) { /* source */
		switch (prop->type) {
		case PT_INT:
			prop->value.integer = atoi(value);
			break;
		case PT_FLOAT:
			prop->value.decimal = (float)atof(value);
			break;
		case PT_BOOL:
			prop->value.integer = parse_boolean(value);
			break;
		case PT_COLOR:
			prop->value.integer = get_color_rgb(value);
			break;
		case PT_NONE:
		case PT_STRING:
		case PT_FILE:
		default:
			prop->value.string = strdup(value);
			break;
		}
	}
	else if (prop->type == PT_NONE || prop->type == PT_STRING) {
		if (!(value = tmxmlGetOpaque(node))) {
			tmx_err(E_MISSEL, "tmxml parser: missing 'value' attribute or inner XML for the 'property' element");
		}
		prop->value.string = strdup(value);
	}
	else {
		tmx_err(E_MISSEL, "tmxml parser: missing 'value' attribute in the 'property' element");
		return 0;
	}
	return 1;
}

static int parse_properties(tmxml_node_t* node, tmx_properties** prop_hashptr) {
	tmx_property* res;
	tmxml_node_t* property_node;
	const char* name;

	/* Create hashtable */
	if (*prop_hashptr == NULL)
	{
		if (!(*prop_hashptr = (tmx_properties*)mk_hashtable(5))) return 0;
	}

	/* Parse each child */
	for (property_node = tmxmlFindElement(node, node, "property", NULL, NULL, TMXML_DESCEND);
		property_node != NULL;
		property_node = tmxmlFindElement(property_node, node, "property", NULL, NULL, TMXML_NO_DESCEND)) {
		if (!(res = alloc_prop())) return 0;
		if (!parse_property(property_node, res)) return 0;
		hashtable_set((void*)*prop_hashptr, res->name, (void*)res, NULL);
	}
	return 1;
}

static int parse_points(tmxml_node_t* node, tmx_shape* shape) {
	char* value, * v;
	int i;

	if (!(value = (char*)tmxmlElementGetAttr(node, "points"))) { /* points */
		tmx_err(E_MISSEL, "tmxml parser: missing 'points' attribute in the 'object' element");
		return 0;
	}

	shape->points_len = 1 + count_char_occurences(value, ' ');

	shape->points = (double**)tmx_alloc_func(NULL, shape->points_len * sizeof(double*)); /* points[i][x,y] */
	if (!(shape->points)) {
		tmx_errno = E_ALLOC;
		return 0;
	}

	shape->points[0] = (double*)tmx_alloc_func(NULL, shape->points_len * 2 * sizeof(double));
	if (!(shape->points[0])) {
		tmx_free_func(shape->points);
		tmx_errno = E_ALLOC;
		return 0;
	}

	for (i = 1; i < shape->points_len; i++) {
		shape->points[i] = shape->points[0] + (i * 2);
	}

	v = value;
	for (i = 0; i < shape->points_len; i++) {
		if (sscanf(v, "%lf,%lf", shape->points[i], shape->points[i] + 1) != 2) {
			tmx_err(E_XDATA, "tmxml parser: corrupted point list");
			return 0;
		}
		v = 1 + strchr(v, ' ');
	}

	tmx_free_func(value);
	return 1;
}

static int parse_text(tmxml_node_t* node, tmx_text* text) {
	char* value;

	if ((value = (char*)tmxmlElementGetAttr(node, "fontfamily"))) { /* fontfamily */
		text->fontfamily = value;
	}
	else {
		text->fontfamily = tmx_strdup("sans-serif");
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "pixelsize"))) { /* pixelsize */
		text->pixelsize = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "color"))) { /* color */
		text->color = get_color_rgb(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "wrap"))) { /* wrap */
		text->wrap = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "bold"))) { /* bold */
		text->bold = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "italic"))) { /* italic */
		text->italic = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "underline"))) { /* underline */
		text->underline = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "strikeout"))) { /* strikeout */
		text->strikeout = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "kerning"))) { /* kerning */
		text->kerning = (int)atoi(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "halign"))) { /* halign */
		text->halign = parse_horizontal_align(value);
	}

	if ((value = (char*)tmxmlElementGetAttr(node, "valign"))) { /* valign */
		text->valign = parse_vertical_align(value);
	}

	if ((value = (char*)tmxmlGetOpaque(node))) {
		text->text = value;
	}

	return 1;
}

static tmx_template* parse_template_document(tmxml_node_t* node, tmx_resource_manager* rc_mgr, const char* filename);

static int parse_object(tmxml_node_t* reader, tmx_object *obj, int is_on_map, tmx_resource_manager *rc_mgr, const char *filename) {
	int curr_depth;
	const char *name;
	char *value, *ab_path;
	resource_holder *tmpl;
	tmxml_node_t* sub_reader;

	/* parses each attribute */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"id"))) { /* id */
		obj->id = atoi(value);
		tmx_free_func(value);
	} else if (is_on_map) {
		tmx_err(E_MISSEL, "xml parser: missing 'id' attribute in the 'object' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"x"))) { /* x */
		obj->x = atof(value);
		tmx_free_func(value);
	} else if (is_on_map) {
		tmx_err(E_MISSEL, "xml parser: missing 'x' attribute in the 'object' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"y"))) { /* y */
		obj->y = atof(value);
		tmx_free_func(value);
	} else if (is_on_map) {
		tmx_err(E_MISSEL, "xml parser: missing 'y' attribute in the 'object' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"template"))) { /* template */
		if (rc_mgr) {
			tmpl = (resource_holder*) hashtable_get((void*)rc_mgr, value);
			if (tmpl && tmpl->type == RC_TX) {
				obj->template_ref = tmpl->resource.template;
			}
		}
		if (!(obj->template_ref)) {
			if (!(ab_path = mk_absolute_path(filename, value))) return 0;
			if (!(sub_reader = xmlReaderForFile(ab_path, NULL, 0))) { /* opens */
				tmx_err(E_XDATA, "xml parser: cannot open object template file '%s'", ab_path);
				tmx_free_func(ab_path);
				tmx_free_func(value);
				return 0;
			}
			obj->template_ref = parse_template_document(sub_reader, rc_mgr, ab_path); /* and parses the template file */
			tmx_free_func(ab_path);
			if (!(obj->template_ref))
			{
				tmx_free_func(value);
				return 0;
			}
			if (rc_mgr) {
				add_template(rc_mgr, value, obj->template_ref);
			} else {
				obj->template_ref->is_embedded = 1;
			}
		}
		obj->obj_type = obj->template_ref->object->obj_type;
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"name"))) { /* name */
		obj->name = value;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"type"))) { /* type */
		obj->type = value;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"visible"))) { /* visible */
		obj->visible = (char)atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"height"))) { /* height */
		obj->obj_type = OT_SQUARE;
		obj->height = atof(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"width"))) { /* width */
		obj->width = atof(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"gid"))) { /* gid */
		obj->obj_type = OT_TILE;
		obj->content.gid = atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"rotation"))) { /* rotation */
		obj->rotation = atof(value);
		tmx_free_func(value);
	}

	/* If it has a child, then it's a polygon or a polyline or an ellipse */
	tmxml_node_t* child;
	for (child = tmxmlGetFirstChild(reader); child; child = tmxmlGetNextSibling(child)) {
		if (tmxmlGetType(child) == TMXML_ELEMENT) {
			const char* name = tmxmlGetElement(child);
			if (!strcmp(name, "properties")) {
				if (!parse_properties(child, &(obj->properties))) return 0;
			}
			else if (!strcmp(name, "ellipse")) {
				obj->obj_type = OT_ELLIPSE;
			}
			else {
				if (!strcmp(name, "polygon")) {
					obj->obj_type = OT_POLYGON;
				}
				else if (!strcmp(name, "polyline")) {
					obj->obj_type = OT_POLYLINE;
				}
				else if (!strcmp(name, "text")) {
					obj->obj_type = OT_TEXT;
				}
				if (obj->obj_type == OT_POLYGON || obj->obj_type == OT_POLYLINE) {
					if (obj->content.shape = alloc_shape(), !(obj->content.shape)) return 0;
					if (!parse_points(child, obj->content.shape)) return 0;
				}
				else if (obj->obj_type == OT_TEXT) {
					if (obj->content.text = alloc_text(), !(obj->content.text)) return 0;
					if (!parse_text(child, obj->content.text)) return 0;
				}
			}
		}
	}
	if (obj->obj_type == OT_NONE)
	{
		obj->obj_type = OT_POINT;
	}
	return 1;
}

static int parse_data(tmxml_node_t* reader, uint32_t **gidsadr, size_t gidscount) {
	char *value, *inner_xml;
	enum enccmp_t data_type;

	if (!(value = (char*)xmlTextReaderGetAttribute(reader, (char*)"encoding"))) { /* encoding */
		tmx_err(E_MISSEL, "xml parser: missing 'encoding' attribute in the 'data' element");
		return 0;
	}

	if (!(inner_xml = (char*)xmlTextReaderReadInnerXml(reader))) {
		tmx_err(E_XDATA, "xml parser: missing content in the 'data' element");
		tmx_free_func(value);
		return 0;
	}

	if (!strcmp(value, "base64")) {
		tmx_free_func(value);
		value = (char*)xmlTextReaderGetAttribute(reader, (char*)"compression"); /* compression */

		data_type = B64;
		if (value && !strcmp(value, "zstd")) {
			data_type = B64ZSTD;
		} else if (value && !(strcmp(value, "zlib") && strcmp(value, "gzip"))) {
			data_type = B64Z;
		} else {
			tmx_err(E_ENCCMP, "xml parser: unsupported data compression: '%s'", value); /* unsupported compression */
			goto cleanup;
		}
		if (!data_decode(str_trim(inner_xml), data_type, gidscount, gidsadr)) goto cleanup;

	} else if (!strcmp(value, "xml")) {
		tmx_err(E_ENCCMP, "xml parser: unimplemented data encoding: XML");
		goto cleanup;
	} else if (!strcmp(value, "csv")) {
		if (!data_decode(str_trim(inner_xml), CSV, gidscount, gidsadr)) goto cleanup;
	} else {
		tmx_err(E_ENCCMP, "xml parser: unknown data encoding: %s", value);
		goto cleanup;
	}
	tmx_free_func(value);
	tmx_free_func(inner_xml);
	return 1;

cleanup:
	tmx_free_func(value);
	tmx_free_func(inner_xml);
	return 0;
}

static int parse_image(tmxml_node_t* reader, tmx_image **img_adr, short strict, const char *filename) {
	tmx_image *res;
	char *value;

	if (!(res = alloc_image())) return 0;
	*img_adr = res;

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"source"))) { /* source */
		res->source = value;
		if (!(load_image(&(res->resource_image), filename, value))) {
			tmx_err(E_UNKN, "xml parser: an error occured in the delegated image loading function");
			return 0;
		}
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'source' attribute in the 'image' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"height"))) { /* height */
		res->height = atoi(value);
		tmx_free_func(value);
	} else if (strict) {
		tmx_err(E_MISSEL, "xml parser: missing 'height' attribute in the 'image' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"width"))) { /* width */
		res->width = atoi(value);
		tmx_free_func(value);
	} else if (strict) {
		tmx_err(E_MISSEL, "xml parser: missing 'width' attribute in the 'image' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"trans"))) { /* trans */
		res->trans = get_color_rgb(value);
		res->uses_trans = 1;
		tmx_free_func(value);
	}

	return 1;
}

static int parse_layer(tmxml_node_t* reader, tmx_layer **layer_headadr, int map_h, int map_w, enum tmx_layer_type type, tmx_resource_manager *rc_mgr, const char *filename) {
	tmx_layer *res;
	tmx_object *obj;
	int curr_depth;
	const char *name;
	char *value;
	enum tmx_layer_type child_type;

	curr_depth = xmlTextReaderDepth(reader);

	if (!(res = alloc_layer())) return 0;
	res->type = type;
	while(*layer_headadr) {
		layer_headadr = &((*layer_headadr)->next);
	}
	*layer_headadr = res;

	/* parses each attribute */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"id"))) { /* id */
		res->id = atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"name"))) { /* name */
		res->name = value;
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'name' attribute in the 'layer' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"visible"))) { /* visible */
		res->visible = (char)atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"opacity"))) { /* opacity */
		res->opacity = atof(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"offsetx"))) { /* offsetx */
		res->offsetx = (int)atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"offsety"))) { /* offsety */
		res->offsety = (int)atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"parallaxx"))) { /* parallaxx */
		res->parallaxx = atof(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"parallaxy"))) { /* parallaxy */
		res->parallaxy = atof(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tintcolor"))) { /* tintcolor */
		res->tintcolor = get_color_rgb(value);
		tmx_free_func(value);
	}

	/* objectgroups have more properties */
	if (type == L_OBJGR) {
		tmx_object_group *objgr = alloc_objgr();
		res->content.objgr = objgr;

		if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"color"))) { /* color */
			objgr->color = get_color_rgb(value);
			tmx_free_func(value);
		}

		value = (char*)xmlTextReaderGetAttribute(reader, (char*)"draworder"); /* draworder */
		objgr->draworder = parse_objgr_draworder(value);
		tmx_free_func(value);
	}

	if (type == L_OBJGR && xmlTextReaderIsEmptyElement(reader)) {
		return 1;
	}

	tmxml_node_t* child;
	for (child = tmxmlGetFirstChild(reader); child; child = tmxmlGetNextSibling(child)) {
		name = tmxmlGetElement(child);
		if (!strcmp(name, "properties")) {
			if (!parse_properties(child, &(res->properties))) return 0;
		}
		else if (!strcmp(name, "data")) {
			if (!parse_data(child, &(res->content.gids), map_h * map_w)) return 0;
		}
		else if (!strcmp(name, "image")) {
			if (!parse_image(child, &(res->content.image), 0, filename)) return 0;
		}
		else if (!strcmp(name, "object")) {
			if (!(obj = alloc_object())) return 0;

			obj->next = res->content.objgr->head;
			res->content.objgr->head = obj;

			if (!parse_object(child, obj, 1, rc_mgr, filename)) return 0;
		}
		else if (type == L_GROUP && (child_type = parse_layer_type(name)) != L_NONE) {
			if (!parse_layer(child, &(res->content.group_head), map_h, map_w, child_type, rc_mgr, filename)) return 0;
		}
	}
	return 1;
}

static int parse_tileoffset(tmxml_node_t* reader, int *x, int *y) {
	char *value;
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"x"))) { /* x offset */
		*x = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'x' attribute in the 'tileoffset' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"y"))) { /* y offset */
		*y = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'y' attribute in the 'tileoffset' element");
		return 0;
	}

	return 1;
}

static tmx_anim_frame* parse_animation(tmxml_node_t* node, int frame_count, unsigned int* length) {
	char* value;
	tmx_anim_frame frame;
	tmx_anim_frame* res;
	tmxml_node_t* child;

	value = (char*)tmxmlElementGetAttr(node, "tileid");
	if (value) { /* tileid */
		frame.tile_id = atoi(value);
	}
	else {
		tmx_err(E_MISSEL, "xml parser: missing 'tileid' attribute in the 'frame' element");
		return 0;
	}

	value = (char*)tmxmlElementGetAttr(node, "duration"); /* duration */
	if (value) {
		frame.duration = atoi(value);
	}
	else {
		tmx_err(E_MISSEL, "xml parser: missing 'duration' attribute in the 'frame' element");
		return 0;
	}

	/* Iterate over child nodes */
	for (child = tmxmlFindElement(node, node, "frame", NULL, NULL, TMXML_DESCEND);
		child != NULL;
		child = tmxmlFindElement(child, node, "frame", NULL, NULL, TMXML_NO_DESCEND)) {
		/* recurse */
		res = parse_animation(child, frame_count + 1, length);
		if (res != NULL) {
			res[frame_count] = frame;
		}
		return res;
	}

	/* no more frames, alloc on the heap and returns */
	res = (tmx_anim_frame*)tmx_alloc_func(NULL, (frame_count + 1) * sizeof(tmx_anim_frame));
	if (res == NULL) {
		tmx_err(E_ALLOC, "xml parser: failed to alloc %d animation frames", frame_count + 1);
		return NULL;
	}
	res[frame_count] = frame;
	*length = frame_count + 1;
	return res;
}

static int parse_tile(tmxml_node_t* reader, tmx_tileset *tileset, tmx_resource_manager *rc_mgr, const char *filename) {
	tmx_tile *res = NULL;
	tmx_object *obj;
	unsigned int id;
	int curr_depth;
	int len, to_move;
	const char *name;
	char *value;

	curr_depth = xmlTextReaderDepth(reader);

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"id"))) { /* id */
		id = atoi(value);
		/* Insertion sort */
		len = tileset->user_data.integer;
		for (to_move=0; (len-1)-to_move >= 0; to_move++) {
			if (tileset->tiles[(len-1)-to_move].id < id) {
				break;
			}
		}
		if (to_move > 0) {
			memmove((tileset->tiles)+(len-to_move+1), (tileset->tiles)+(len-to_move), to_move * sizeof(tmx_tile));
		}
		res = &(tileset->tiles[len-to_move]);

		if ((unsigned int)(tileset->user_data.integer) == tileset->tilecount) {
			tileset->user_data.integer = 0;
		}
		else {
			tileset->user_data.integer += 1;
		}
		/* --- */
		res->id = id;
		res->tileset = tileset;
		tmx_free_func(value);
	}
	else {
		tmx_err(E_MISSEL, "xml parser: missing 'id' attribute in the 'tile' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"type"))) { /* type */
		res->type = value;
	}

	for (value = tmxmlGetFirstChild(reader); value; value = tmxmlGetNextSibling(value)) {
		name = tmxmlGetElement(value);
		if (!strcmp(name, "properties")) {
			if (!parse_properties(value, &(res->properties))) return 0;
		}
		else if (!strcmp(name, "image")) {
			if (!parse_image(value, &(res->image), 0, filename)) return 0;
		}
		else if (!strcmp(name, "objectgroup")) { /* tile collision */
			tmxml_node_t* innerChild;
			for (innerChild = tmxmlGetFirstChild(value); innerChild; innerChild = tmxmlGetNextSibling(innerChild)) {
				name = tmxmlGetElement(innerChild);
				if (!strcmp(name, "object")) {
					if (!(obj = alloc_object())) return 0;

					obj->next = res->collision;
					res->collision = obj;

					if (!parse_object(innerChild, obj, 0, rc_mgr, filename)) return 0;
				}
				/* else: ignore */
			}
		}
		else if (!strcmp(name, "animation")) {
			tmxml_node_t* innerChild;
			for (innerChild = tmxmlGetFirstChild(value); innerChild; innerChild = tmxmlGetNextSibling(innerChild)) {
				name = tmxmlGetElement(innerChild);
				if (!strcmp(name, "frame")) {
					res->animation = parse_animation(innerChild, 0, &(res->animation_len));
					if (!(res->animation)) return 0;
				}
				/* else: ignore */
			}
		}
		/* else: ignore */
	}

	return 1;
}

static int parse_tileset(tmxml_node_t* reader, tmx_tileset *ts_addr, tmx_resource_manager *rc_mgr, const char *filename) {
	int curr_depth;
	const char *name;
	char *value;

	curr_depth = xmlTextReaderDepth(reader);

	/* parses each attribute */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"name"))) { /* name */
		ts_addr->name = value;
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'name' attribute in the 'tileset' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tilecount"))) { /* tilecount */
		ts_addr->tilecount = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'tilecount' attribute in the 'tileset' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tilewidth"))) { /* tile_width */
		ts_addr->tile_width = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'tilewidth' attribute in the 'tileset' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tileheight"))) { /* tile_height */
		ts_addr->tile_height = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'tileheight' attribute in the 'tileset' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"spacing"))) { /* spacing */
		ts_addr->spacing = atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"margin"))) { /* margin */
		ts_addr->margin = atoi(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"objectalignment"))) { /* objectalignment */
		ts_addr->objectalignment = parse_obj_alignment(value);
		tmx_free_func(value);
	}

	if (!(ts_addr->tiles = alloc_tiles(ts_addr->tilecount))) return 0;

	for (value = tmxmlGetFirstChild(reader); value; value = tmxmlGetNextSibling(value)) {
		name = tmxmlGetElement(value);
		if (!strcmp(name, "image")) {
			if (!parse_image(value, &(ts_addr->image), 1, filename)) return 0;
		}
		else if (!strcmp(name, "tileoffset")) {
			if (!parse_tileoffset(value, &(ts_addr->x_offset), &(ts_addr->y_offset))) return 0;
		}
		else if (!strcmp(name, "properties")) {
			if (!parse_properties(value, &(ts_addr->properties))) return 0;
		}
		else if (!strcmp(name, "tile")) {
			if (!parse_tile(value, ts_addr, rc_mgr, filename)) return 0;
		}
		/* else: ignore */
	}

	if (ts_addr->image && !set_tiles_runtime_props(ts_addr)) return 0;

	return 1;
}

static int parse_tileset_list(tmxml_node_t* reader, tmx_tileset_list **ts_headadr, tmx_resource_manager *rc_mgr, const char *filename) {
	tmx_tileset_list *res_list = NULL;
	tmx_tileset *res = NULL;
	resource_holder *rc_holder;
	int ret;
	char *value, *ab_path;
	tmxml_node_t* sub_reader;

	if (!(res_list = alloc_tileset_list())) return 0;
	res_list->next = *ts_headadr;
	*ts_headadr = res_list;

	/* parses each attribute */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"firstgid"))) { /* fisrtgid */
		res_list->firstgid = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'firstgid' attribute in the 'tileset' element");
		return 0;
	}

	/* External Tileset */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"source"))) { /* source */
		res_list->source = value;
		if (rc_mgr) {
			rc_holder = (resource_holder*) hashtable_get((void*)rc_mgr, value);
			if (rc_holder && rc_holder->type == RC_TSX) {
				res = rc_holder->resource.tileset;
				if (res) {
					res_list->tileset = res;
					return 1;
				}
			}
		}
		if (!(res = alloc_tileset())) {
			return 0;
		}
		res_list->tileset = res;
		if (rc_mgr) {
			add_tileset(rc_mgr, value, res);
		}
		else {
			res_list->is_embedded = 1;
		}
		if (!(ab_path = mk_absolute_path(filename, value))) return 0;
		if (!(sub_reader = xmlReaderForFile(ab_path, NULL, 0)) || !check_reader(sub_reader)) { /* opens */
			tmx_err(E_XDATA, "xml parser: cannot open extern tileset '%s'", ab_path);
			tmx_free_func(ab_path);
			return 0;
		}
		ret = parse_tileset(sub_reader, res, rc_mgr, ab_path); /* and parses the tsx file */
		xmlFreeTextReader(sub_reader);
		tmx_free_func(ab_path);
		return ret;
	}

	/* Embedded tileset */
	if (!(res = alloc_tileset())) return 0;
	res_list->is_embedded = 1;
	res_list->tileset = res;

	return parse_tileset(reader, res, rc_mgr, filename);
}

static int parse_template(tmxml_node_t* node, tmx_template* template, tmx_resource_manager* rc_mgr, const char* filename) {
	tmxml_node_t* child;
	const char* name;

	for (child = tmxmlGetFirstChild(node); child; child = tmxmlGetNextSibling(child)) {
		name = tmxmlGetElement(child);
		if (!strcmp(name, "tileset")) {
			parse_tileset_list(child, &(template->tileset_ref), rc_mgr, filename);
		}
		else if (!strcmp(name, "object")) {
			if (!parse_object(child, template->object, 0, rc_mgr, filename)) return 0;
		}
		/* else: ignore */
	}
	return 1;
}

static int parse_map(tmxml_node_t* reader, tmx_map *map, tmx_resource_manager *rc_mgr, const char *filename) {
	int curr_depth, flag;
	const char *name;
	char *value;
	enum tmx_layer_type type;

	curr_depth = xmlTextReaderDepth(reader);

	/* infinite maps not supported */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"infinite"))) {
		flag = atoi(value);
		tmx_free_func(value);
		if (flag == 1) {
			tmx_err(E_XDATA, "xml parser: chunked layer data is not supported, edit this map to remove the infinite flag");
			return 0;
		}
	}

	/* parses each attribute */
	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"orientation"))) { /* orientation */
		if (map->orient = parse_orient(value), map->orient == O_NONE) {
			tmx_err(E_XDATA, "xml parser: unsupported 'orientation' '%s'", value);
			return 0;
		}
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'orientation' attribute in the 'map' element");
		return 0;
	}

	value = (char*)xmlTextReaderGetAttribute(reader, (char*)"staggerindex"); /* staggerindex */
	if (value != NULL && (map->stagger_index = parse_stagger_index(value), map->stagger_index == SI_NONE)) {
		tmx_err(E_XDATA, "xml parser: unsupported 'staggerindex' '%s'", value);
		return 0;
	}
	tmx_free_func(value);

	value = (char*)xmlTextReaderGetAttribute(reader, (char*)"staggeraxis"); /* staggeraxis */
	if (map->stagger_axis = parse_stagger_axis(value), map->stagger_axis == SA_NONE) {
		tmx_err(E_XDATA, "xml parser: unsupported 'staggeraxis' '%s'", value);
		return 0;
	}
	tmx_free_func(value);

	value = (char*)xmlTextReaderGetAttribute(reader, (char*)"renderorder"); /* renderorder */
	if (map->renderorder = parse_renderorder(value), map->renderorder == R_NONE) {
		tmx_err(E_XDATA, "xml parser: unsupported 'renderorder' '%s'", value);
		return 0;
	}
	tmx_free_func(value);

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"height"))) { /* height */
		map->height = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'height' attribute in the 'map' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"width"))) { /* width */
		map->width = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'width' attribute in the 'map' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tileheight"))) { /* tileheight */
		map->tile_height = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'tileheight' attribute in the 'map' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"tilewidth"))) { /* tilewidth */
		map->tile_width = atoi(value);
		tmx_free_func(value);
	} else {
		tmx_err(E_MISSEL, "xml parser: missing 'tilewidth' attribute in the 'map' element");
		return 0;
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"backgroundcolor"))) { /* backgroundcolor */
		map->backgroundcolor = get_color_rgb(value);
		tmx_free_func(value);
	}

	if ((value = (char*)xmlTextReaderGetAttribute(reader, (char*)"hexsidelength"))) { /* hexsidelength */
		map->hexsidelength = atoi(value);
		tmx_free_func(value);
	}

	for (value = tmxmlGetFirstChild(reader); value; value = tmxmlGetNextSibling(value)) {
		name = tmxmlGetElement(value);
		if (!strcmp(name, "tileset")) {
			if (!parse_tileset_list(value, &(map->ts_head), rc_mgr, filename)) return 0;
		}
		else if (!strcmp(name, "properties")) {
			if (!parse_properties(value, &(map->properties))) return 0;
		}
		else if ((type = parse_layer_type(name)) != L_NONE) {
			if (!parse_layer(value, &(map->ly_head), map->height, map->width, type, rc_mgr, filename)) return 0;
		}
		/* else: ignore */
	}
	return 1;
}

static tmx_map* parse_map_document(tmxml_node_t* node, tmx_resource_manager* rc_mgr, const char* filename) {
	tmx_map* res = NULL;
	const char* name;

	if (node) {
		name = tmxmlGetElement(node);
		if (strcmp(name, "map")) {
			tmx_err(E_XDATA, "xml parser: root of map document is not a 'map' element");
		}
		else if ((res = alloc_map())) {
			if (!parse_map(node, res, rc_mgr, filename)) {
				tmx_map_free(res);
				res = NULL;
			}
		}
	}
	return res;
}

static tmx_tileset* parse_tileset_document(tmxml_node_t* reader, const char *filename) {
	tmx_tileset *res = NULL;
	char *name;

	if (check_reader(reader)) {
		name = (char*) xmlTextReaderConstName(reader);
		if (strcmp(name, "tileset")) {
			tmx_err(E_XDATA, "xml parser: root of tileset document is not a 'tileset' element");
			return NULL;
		}
		else if ((res = alloc_tileset())) {
			if (!parse_tileset(reader, res, NULL, filename)) {
				free_ts(res);
				res = NULL;
			}
		}
	}
	xmlFreeTextReader(reader);
	return res;
}

static tmx_template* parse_template_document(tmxml_node_t* reader, tmx_resource_manager *rc_mgr, const char *filename) {
	tmx_template *res = NULL;
	char *name;

	if (check_reader(reader)) {
		name = (char*) xmlTextReaderConstName(reader);
		if (strcmp(name, "template")) {
			tmx_err(E_XDATA, "xml parser: root of template document is not a 'template' element");
			return NULL;
		}
		else if ((res = alloc_template())) {
			if (!parse_template(reader, res, rc_mgr, filename)) {
				free_template(res);
				res = NULL;
			}
		}
	}
	xmlFreeTextReader(reader);
	return res;
}

tmx_map *parse_xml(tmx_resource_manager *rc_mgr, const char *filename) {
	tmxml_node_t* reader;
	tmx_map *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFile(filename, NULL, 0))) {
		res = parse_map_document(reader, rc_mgr, filename);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to open %s", filename);
	}

	return res;
}

tmx_map* parse_xml_buffer(tmx_resource_manager *rc_mgr, const char *buffer, int len) {
	tmxml_node_t* reader;
	tmx_map *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForMemory(buffer, len, NULL, NULL, 0))) {
		res = parse_map_document(reader, rc_mgr, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for buffer");
	}

	return res;
}

tmx_map* parse_xml_fd(tmx_resource_manager *rc_mgr, int fd) {
	tmxml_node_t* reader;
	tmx_map *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFd(fd, NULL, NULL, 0))) {
		res = parse_map_document(reader, rc_mgr, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable create parser for file descriptor");
	}

	return res;
}

tmx_map* parse_xml_callback(tmx_resource_manager* rc_mgr, tmx_read_functor callback, void* userdata) {
	tmxml_node_t* tree;
	tmx_map* res = NULL;

	tree = tmxmlLoadFile(NULL, callback, TMXML_OPAQUE_CALLBACK);
	if (tree) {
		res = parse_map_document(tree, rc_mgr, NULL);
		tmxmlDelete(tree);
	}
	else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for input callback");
	}

	return res;
}

tmx_tileset* parse_tsx_xml(const char *filename) {
	tmxml_node_t* reader;
	tmx_tileset *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFile(filename, NULL, 0))) {
		res = parse_tileset_document(reader, filename);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to open %s", filename);
	}

	return res;
}

tmx_tileset* parse_tsx_xml_buffer(const char *buffer, int len) {
	tmxml_node_t* reader;
	tmx_tileset *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForMemory(buffer, len, NULL, NULL, 0))) {
		res = parse_tileset_document(reader, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for buffer");
	}

	return res;
}

tmx_tileset* parse_tsx_xml_fd(int fd) {
	tmxml_node_t* reader;
	tmx_tileset *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFd(fd, NULL, NULL, 0))) {
		res = parse_tileset_document(reader, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable create parser for file descriptor");
	}

	return res;
}

tmx_tileset* parse_tsx_xml_callback(tmx_read_functor callback, void* userdata) {
	tmxml_node_t* tree;
	tmx_tileset* res = NULL;

	tree = tmxmlLoadFile(NULL, callback, TMXML_OPAQUE_CALLBACK);
	if (tree) {
		res = parse_tileset_document(tree, NULL);
		tmxmlDelete(tree);
	}
	else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for input callback");
	}

	return res;
}

tmx_template* parse_tx_xml(tmx_resource_manager *rc_mgr, const char *filename) {
	tmxml_node_t* reader;
	tmx_template *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFile(filename, NULL, 0))) {
		res = parse_template_document(reader, rc_mgr, filename);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to open %s", filename);
	}

	return res;
}

tmx_template* parse_tx_xml_buffer(tmx_resource_manager *rc_mgr, const char *buffer, int len) {
	tmxml_node_t* reader;
	tmx_template *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForMemory(buffer, len, NULL, NULL, 0))) {
		res = parse_template_document(reader, rc_mgr, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for buffer");
	}

	return res;
}

tmx_template* parse_tx_xml_fd(tmx_resource_manager *rc_mgr, int fd) {
	tmxml_node_t* reader;
	tmx_template *res = NULL;

	setup_libxml_mem();

	if ((reader = xmlReaderForFd(fd, NULL, NULL, 0))) {
		res = parse_template_document(reader, rc_mgr, NULL);
	} else {
		tmx_err(E_UNKN, "xml parser: unable create parser for file descriptor");
	}

	return res;
}

tmx_template* parse_tx_xml_callback(tmx_resource_manager* rc_mgr, tmx_read_functor callback, void* userdata) {
	tmxml_node_t* tree;
	tmx_template* res = NULL;

	tree = tmxmlLoadFile(NULL, callback, TMXML_OPAQUE_CALLBACK);
	if (tree) {
		res = parse_template_document(tree, rc_mgr, NULL);
		tmxmlDelete(tree);
	}
	else {
		tmx_err(E_UNKN, "xml parser: unable to create parser for input callback");
	}

	return res;
}
