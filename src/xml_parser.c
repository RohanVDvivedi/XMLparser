#include<xml_parser.h>

#include<xml_lexer.h>

#include<stdio.h>

xml_node* parse_xml(const dstring* xml_string)
{
	xml_lexer xml_lxr;
	init_xml_lexer(&xml_lxr, xml_string);


	return NULL;
}