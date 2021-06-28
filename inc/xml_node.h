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

xml_node* get_new_empty_xml_node();

int append_content_xml_node(xml_node* xml_node_p, const dstring* content_to_append);
int clear_content_xml_node(xml_node* xml_node_p);

int append_child_xml_node(xml_node* xml_node_p, xml_node* child_xml_p);
xml_node* get_child_xml_node(xml_node* xml_node_p, unsigned int index);
int delete_child_xml_node(xml_node* xml_node_p, unsigned int index);

void delete_xml_node_tree(xml_node* xml_node_p);

#endif