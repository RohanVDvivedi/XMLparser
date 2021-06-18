#ifndef XML_NODE_H
#define XML_NODE_H

#include<dstring.h>
#include<hashmap.h>
#include<array.h>

typedef struct xml_node xml_node;
struct xml_node
{
	dstring tag_name;		// name of the tag i.e. <tag_name> </tag_name> OR <tag_name/>

	hashmap attributes;		// hashmap of dstring vs dstring
							// i.e. <tag_name attribute_key="attribute_value" >

	int is_empty : 1;

	int has_content : 1;

	// valid only if has_content == 0
	unsigned int children_count;

	// an XML tag contains children_nodes or content
	// if children_count > 0 then has_content must be 0

	union
	{
		array children_nodes;	// a dynamic array of xml_node*

		dstring content;		// string content
	}data;
};

#endif