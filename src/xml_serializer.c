#include<xml_serializer.h>

static void serialize_xml_attributes_wrapper(const attribute* attr, dstring* result)
{
	snprintf_dstring(result, " %.*s=\"%.*s\"", attr->key.bytes_occupied, attr->key.cstring, attr->value.bytes_occupied, attr->value.cstring);
}

static void serialize_xml_children_wrapper(const xml_node* node_p, unsigned int i, dstring* result)
{
	serialize_xml(result, node_p);
}

void serialize_xml(dstring* result, const xml_node* node_p)
{
	snprintf_dstring(result, "<%.*s", node_p->tag_name.bytes_occupied, node_p->tag_name.cstring);

	for_each_in_hashmap(&(node_p->attributes), (void (*)(const void*, const void*))serialize_xml_attributes_wrapper, result);
	
	if(node_p->is_empty)
	{
		snprintf_dstring(result, "/>");
		return;
	}
	snprintf_dstring(result, ">");

	if(node_p->has_content)
		snprintf_dstring(result, "%.*s", node_p->content.bytes_occupied, node_p->content.cstring);
	else
		for_each_in_array(&(node_p->child_nodes), (void (*)(void*, unsigned int, const void*))serialize_xml_children_wrapper, result);

	snprintf_dstring(result, "</%.*s>", node_p->tag_name.bytes_occupied, node_p->tag_name.cstring);
}