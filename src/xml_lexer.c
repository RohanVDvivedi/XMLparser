#include<xml_lexer.h>

void init_xml_lexer(xml_lexer* xml_lexer_p, dstring* xml_string)
{
	xml_lexer_p->next_token_start = xml_string->cstring;
	xml_lexer_p->xml_string = xml_string;
}

int get_next_xml_lexeme(xml_lexer* xml_lexer_p, xml_lexeme* lexeme_p);