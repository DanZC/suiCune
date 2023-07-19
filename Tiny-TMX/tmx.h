#ifndef TMX_H
#define TMX_H

#include <stddef.h>
#include <stdint.h>

#ifndef TMXEXPORT
#define TMXEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define TMX_FLIPPED_HORIZONTALLY 0x80000000
#define TMX_FLIPPED_VERTICALLY   0x40000000
#define TMX_FLIPPED_DIAGONALLY   0x20000000
#define TMX_FLIP_BITS_REMOVAL    0x1FFFFFFF

	/* Custom realloc and free function, for memalloc debugging purposes
	   Please modify these values once before you use tmx_load */
	TMXEXPORT extern void* (*tmx_alloc_func) (void* address, size_t len); /* realloc */
	TMXEXPORT extern void  (*tmx_free_func) (void* address);             /* free */

	/* load/free tmx_image->resource_image, you should set this if you want
	   the library to load/free images */
	TMXEXPORT extern void* (*tmx_img_load_func) (const char* path);
	TMXEXPORT extern void  (*tmx_img_free_func) (void* address);

	enum tmx_map_orient { O_NONE, O_ORT, O_ISO, O_STA, O_HEX };
	enum tmx_map_renderorder { R_NONE, R_RIGHTDOWN, R_RIGHTUP, R_LEFTDOWN, R_LEFTUP };
	enum tmx_stagger_index { SI_NONE, SI_EVEN, SI_ODD };
	enum tmx_stagger_axis { SA_NONE, SA_X, SA_Y };
	enum tmx_obj_alignment { OA_NONE, OA_TOP, OA_LEFT, OA_BOTTOM, OA_RIGHT, OA_CENTER, OA_TOPLEFT, OA_TOPRIGHT, OA_BOTTOMLEFT, OA_BOTTOMRIGHT };
	enum tmx_layer_type { L_NONE, L_LAYER, L_OBJGR, L_IMAGE, L_GROUP };
	enum tmx_objgr_draworder { G_NONE, G_INDEX, G_TOPDOWN };
	enum tmx_obj_type { OT_NONE, OT_SQUARE, OT_POLYGON, OT_POLYLINE, OT_ELLIPSE, OT_TILE, OT_TEXT, OT_POINT };
	enum tmx_property_type { PT_NONE, PT_INT, PT_FLOAT, PT_BOOL, PT_STRING, PT_COLOR, PT_FILE };
	enum tmx_horizontal_align { HA_NONE, HA_LEFT, HA_CENTER, HA_RIGHT };
	enum tmx_vertical_align { VA_NONE, VA_TOP, VA_CENTER, VA_BOTTOM };

	typedef struct _tmx_prop tmx_property;
	typedef struct _tmx_img tmx_image;
	typedef struct _tmx_frame tmx_anim_frame;
	typedef struct _tmx_tile tmx_tile;
	typedef struct _tmx_ts tmx_tileset;
	typedef struct _tmx_ts_list tmx_tileset_list;
	typedef struct _tmx_shape tmx_shape;
	typedef struct _tmx_text tmx_text;
	typedef struct _tmx_obj tmx_object;
	typedef struct _tmx_objgr tmx_object_group;
	typedef struct _tmx_templ tmx_template;
	typedef struct _tmx_layer tmx_layer;
	typedef struct _tmx_map tmx_map;
	typedef void tmx_properties; /* hashtable, use function tmx_get_property(...) */

	typedef union {
		int integer;
		float decimal;
		void* pointer;
	} tmx_user_data;

	typedef union {
		int integer, boolean; /* type = int or bool */
		float decimal; /* type = float */
		char* string, * file; /* default and type = string or file */
		uint32_t color; /* type = color, bytes : ARGB */
	} tmx_property_value;

	struct _tmx_prop { /* <properties> and <property> */
		char* name;
		enum tmx_property_type type;
		tmx_property_value value;
	};

	struct _tmx_img { /* <image> */
		char* source;
		unsigned int trans; /* bytes : RGB */
		int uses_trans;
		unsigned long width, height;
		void* resource_image;
	};

	struct _tmx_frame { /* <frame> */
		unsigned int tile_id;
		unsigned int duration;
	};

	struct _tmx_tile { /* <tile> */
		unsigned int id;
		tmx_tileset* tileset;
		unsigned int ul_x, ul_y; /* upper-left coordinate of this tile */

		tmx_image* image;
		tmx_object* collision;

		unsigned int animation_len;
		tmx_anim_frame* animation;

		char* type;
		tmx_properties* properties;

		tmx_user_data user_data;
	};

	struct _tmx_ts { /* <tileset> and <tileoffset> */
		char* name;

		unsigned int tile_width, tile_height;
		unsigned int spacing, margin;
		int x_offset, y_offset; /* tileoffset */
		enum tmx_obj_alignment objectalignment;

		unsigned int tilecount;
		tmx_image* image;

		tmx_user_data user_data;
		tmx_properties* properties;
		tmx_tile* tiles;
	};

	struct _tmx_ts_list { /* Linked list */
		int is_embedded; /* used internally to free this node */
		unsigned int firstgid;
		char* source;
		tmx_tileset* tileset;
		tmx_tileset_list* next;
	};

	struct _tmx_shape { /* <polygon> and <polyline> */
		double** points; /* point[i][x,y]; x=0 y=1 */
		int points_len;
	};

	struct _tmx_text { /* <text> */
		char* fontfamily;
		int pixelsize;
		uint32_t color; /* bytes : ARGB */

		int wrap; /* 0 == false */
		int bold;
		int italic;
		int underline;
		int strikeout;
		int kerning;

		enum tmx_horizontal_align halign;
		enum tmx_vertical_align valign;

		char* text;
	};

	struct _tmx_obj { /* <object> */
		unsigned int id;
		enum tmx_obj_type obj_type;

		double x, y;
		double width, height;

		union {
			int gid;
			tmx_shape* shape;
			tmx_text* text;
		} content;

		int visible; /* 0 == false */
		double rotation;

		char* name, * type;
		tmx_template* template_ref;
		tmx_properties* properties;
		tmx_object* next;
	};

	struct _tmx_objgr { /* <objectgroup> */
		uint32_t color; /* bytes : ARGB */
		enum tmx_objgr_draworder draworder;
		tmx_object* head;
	};

	struct _tmx_templ { /* <template> */
		int is_embedded; /* used internally to free this node */
		tmx_tileset_list* tileset_ref; /* not null if object is a tile, is a singleton list */
		tmx_object* object; /* never null */
	};

	struct _tmx_layer { /* <layer> or <imagelayer> or <objectgroup> */
		int id;
		char* name;
		double opacity;
		int visible; /* 0 == false */
		int offsetx, offsety;
		double parallaxx, parallaxy;
		uint32_t tintcolor; /* bytes : ARGB */

		enum tmx_layer_type type;
		union layer_content {
			uint32_t* gids;
			tmx_object_group* objgr;
			tmx_image* image;
			tmx_layer* group_head;
		} content;

		tmx_user_data user_data;
		tmx_properties* properties;
		tmx_layer* next;
	};

	struct _tmx_map { /* <map> (Head of the data structure) */
		enum tmx_map_orient orient;

		unsigned int width, height;
		unsigned int tile_width, tile_height;

		enum tmx_stagger_index stagger_index;
		enum tmx_stagger_axis stagger_axis;
		int hexsidelength;

		uint32_t backgroundcolor; /* bytes : ARGB */
		enum tmx_map_renderorder renderorder;

		tmx_properties* properties;
		tmx_tileset_list* ts_head;
		tmx_layer* ly_head;

		unsigned int tilecount; /* length of map->tiles */
		tmx_tile** tiles; /* GID indexed tile array (array of pointers to tmx_tile) */

		tmx_user_data user_data;
	};

		typedef struct _tmx_prop tmx_property;
		typedef struct _tmx_map tmx_map;
		typedef struct _tmx_layer tmx_layer;
		typedef struct _tmx_tile tmx_tile;
		typedef void tmx_properties; /* hashtable, use function tmx_get_property(...) */
		typedef void tmx_resource_manager;

		typedef int (*tmx_read_functor)(void* userdata, char* buffer, int len);
		typedef void (*tmx_property_functor)(tmx_property* property, void* userdata);

		typedef enum _tmx_error_codes {
			E_NONE = 0,
			E_UNKN = 1,
			E_INVAL = 2,
			E_ALLOC = 8,
			E_ACCESS = 10,
			E_NOENT = 11,
			E_FORMAT = 12,
			E_ENCCMP = 13,
			E_FONCT = 16,
			E_BDATA = 20,
			E_ZDATA = 21,
			E_XDATA = 22,
			E_ZSDATA = 23,
			E_CDATA = 24,
			E_MISSEL = 30
		} tmx_error_codes;

		extern tmx_error_codes tmx_errno;

		TMXEXPORT tmx_map* tmx_load(const char* path);
		TMXEXPORT tmx_map* tmx_load_buffer(const char* buffer, int len);
		TMXEXPORT tmx_map* tmx_load_fd(int fd);
		TMXEXPORT tmx_map* tmx_load_callback(tmx_read_functor callback, void* userdata);
		TMXEXPORT void tmx_map_free(tmx_map* map);
		TMXEXPORT tmx_tile* tmx_get_tile(tmx_map* map, unsigned int gid);
		TMXEXPORT tmx_layer* tmx_find_layer_by_id(const tmx_map* map, int id);
		TMXEXPORT tmx_layer* tmx_find_layer_by_name(const tmx_map* map, const char* name);
		TMXEXPORT tmx_property* tmx_get_property(tmx_properties* hash, const char* key);
		TMXEXPORT void tmx_property_foreach(tmx_properties* hash, tmx_property_functor callback, void* userdata);
		TMXEXPORT tmx_resource_manager* tmx_make_resource_manager();
		TMXEXPORT void tmx_free_resource_manager(tmx_resource_manager* rc_mgr);
		TMXEXPORT int tmx_load_tileset(tmx_resource_manager* rc_mgr, const char* path);
		TMXEXPORT int tmx_load_tileset_buffer(tmx_resource_manager* rc_mgr, const char* buffer, int len, const char* key);
		TMXEXPORT int tmx_load_tileset_fd(tmx_resource_manager* rc_mgr, int fd, const char* key);
		TMXEXPORT int tmx_load_tileset_callback(tmx_resource_manager* rc_mgr, tmx_read_functor callback, void* userdata, const char* key);
		TMXEXPORT int tmx_load_template(tmx_resource_manager* rc_mgr, const char* path);
		TMXEXPORT int tmx_load_template_buffer(tmx_resource_manager* rc_mgr, const char* buffer, int len, const char* key);
		TMXEXPORT int tmx_load_template_fd(tmx_resource_manager* rc_mgr, int fd, const char* key);
		TMXEXPORT int tmx_load_template_callback(tmx_resource_manager* rc_mgr, tmx_read_functor callback, void* userdata, const char* key);
		TMXEXPORT tmx_map* tmx_rcmgr_load(tmx_resource_manager* rc_mgr, const char* path);
		TMXEXPORT tmx_map* tmx_rcmgr_load_buffer(tmx_resource_manager* rc_mgr, const char* buffer, int len);
		TMXEXPORT tmx_map* tmx_rcmgr_load_fd(tmx_resource_manager* rc_mgr, int fd);
		TMXEXPORT tmx_map* tmx_rcmgr_load_callback(tmx_resource_manager* rc_mgr, tmx_read_functor callback, void* userdata);
		TMXEXPORT void tmx_perror(const char*);
		TMXEXPORT const char* tmx_strerr(void);

		typedef struct { uint8_t r, g, b, a; } tmx_col_bytes;
		typedef struct { float r, g, b, a; } tmx_col_floats;

#ifdef __cplusplus
	}
#endif

#endif /* TMX_H */

