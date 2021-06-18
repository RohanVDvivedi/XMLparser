#ifndef XML_PARSER_H
#define XML_PARSER_H

#include<dstring.h>
#include<xml_node.h>

xml_node* parse_xml(const dstring* xml_string);

#endif