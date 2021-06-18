#ifndef XML_NODE_H
#define XML_NODE_H

#include<dstring.h>
#include<hashmap.h>
#include<linkedlist.h>

typedef struct xml_node xml_node;
struct xml_node
{
	dstring tag_name;		// i.e. <tag_name> ... </tag_name> OR <tag_name/>

	hashmap attributes;		// hashmap of struct attribute i.e. dstring vs dstring
							// i.e. <tag_name attribute_key="attribute_value">

	int is_empty : 1;		// an XML tag is empty if
							// <tag_name></tag_name> OR <tag_name/>

	int has_content : 1;	// or has child_nodes

	// an XML tag contains children_nodes or content
	union
	{
		struct
		{
			unsigned int children_count;
			array child_nodes;	// a dynamic array of xml_node*
		};

		dstring content;		// string content
	};
};

typedef struct attribute attribute;
struct attribute
{
	dstring key;
	dstring value;
};

#endif