#ifndef TMXML_H
#define TMXML_H

typedef enum tmxml_type_e		/**** The XML node type. ****/
{
	TMXML_IGNORE = -1,			/* Ignore/throw away node @since Mini-XML 2.3@ */
	TMXML_ELEMENT,				/* XML element with attributes */
	TMXML_INTEGER,				/* Integer value */
	TMXML_OPAQUE,				/* Opaque string */
	TMXML_REAL,				/* Real value */
	TMXML_TEXT,				/* Text fragment */
	TMXML_CUSTOM				/* Custom data @since Mini-XML 2.1@ */
} tmxml_type_t;

typedef struct tmxml_attr_s		/**** An XML element attribute value. ****/
{
	char* name;		/* Attribute name */
	char* value;		/* Attribute value */
} tmxml_attr_t;

typedef struct tmxml_element_s		/**** An XML element value. ****/
{
	char* name;		/* Name of element */
	int num_attrs;	/* Number of attributes */
	tmxml_attr_t* attrs;		/* Attributes */
} tmxml_element_t;

typedef struct tmxml_text_s		/**** An XML text value. ****/
{
	int	whitespace;	/* Leading whitespace? */
	char* string;	/* Fragment string */
} tmxml_text_t;

typedef struct tmxml_custom_s		/**** An XML custom value. ****/
{
	void* data;		/* Pointer to (allocated) custom data */
	void (*destroy)(void*);	/* Pointer to destructor function */
} tmxml_custom_t;

typedef union tmxml_value_u		/**** An XML node value. ****/
{
	tmxml_element_t	element;	/* Element */
	int	integer;	/* Integer number */
	char* opaque;	/* Opaque string */
	double	real;		/* Real number */
	tmxml_text_t	text;		/* Text fragment */
	tmxml_custom_t	custom;	/* Custom data @since Mini-XML 2.1@ */
} tmxml_value_t;

typedef struct tmxml_node_s			/**** An XML node. ****/
{
	tmxml_type_t		type;		/* Node type */
	struct tmxml_node_s* next;		/* Next node under same parent */
	struct tmxml_node_s* prev;		/* Previous node under same parent */
	struct tmxml_node_s* parent;	/* Parent node */
	struct tmxml_node_s* child;		/* First child node */
	struct tmxml_node_s* last_child;	/* Last child node */
	tmxml_value_t		value;		/* Node value */
	int			ref_count;	/* Use count */
	void* user_data;	/* User data */
} tmxml_node_t;

#  define TMXML_DESCEND		1	/* Descend when finding/walking */
#  define TMXML_NO_DESCEND	0	/* Don't descend when finding/walking */

#  define TMXML_OPAQUE_CALLBACK	tmxml_opaque_cb
/* Treat all data as opaque */

extern tmxml_type_t	tmxml_opaque_cb(tmxml_node_t* node);

#endif /* !TMXML_H */
