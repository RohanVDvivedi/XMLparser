#ifndef XML_SERIALIZER_H
#define XML_SERIALIZER_H

#include<dstring.h>
#include<xml_node.h>

void serialize_xml(dstring* result, const xml_node* node_p);

#endif