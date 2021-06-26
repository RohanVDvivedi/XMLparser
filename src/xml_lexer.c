#include<xml_lexer.h>

void init_xml_lexer(xml_lexer* xml_lexer_p, dstring* xml_string)
{
	xml_lexer_p->next_token_start = xml_string->cstring;
	xml_lexer_p->xml_string = xml_string;
}

int get_next_xml_lexeme(xml_lexer* xml_lexer_p, xml_lexeme* lexeme_p)
{
	char* end_char_at = xml_lexer_p->xml_string->cstring + xml_lexer_p->xml_string->bytes_occupied;

	if(xml_lexer_p->next_token_start == NULL || xml_lexer_p->next_token_start == end_char_at)
	{
		xml_lexeme_p->type = END_OF_xml_STRING;
		xml_lexeme_p->value = ((dstring){});
		return 1;
	}

	switch(*(xml_lexer_p->next_token_start))
	{
		case '\"':
		{
			xml_lexeme_p->type = QUOTED_STRING;
			xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
			while((xml_lexer_p->next_token_start != end_char_at) && (*(xml_lexer_p->next_token_start++)) != '\"');
			if(xml_lexer_p->next_token_start == end_char_at)
				return 0; //error
			xml_lexeme_p->value.bytes_occupied = xml_lexer_p->next_token_start - xml_lexeme_p->value.cstring;
			return 1;
		}
		case '<' :
		{
			return 1;
		}
		case '/' :
		{
			return 1;
		}
		case '>' :
		{
			return 1;
		}
		default :
		{
			if(isspace(*(xml_lexer_p->next_token_start)))
			{
				xml_lexeme_p->type = WHITESPACES_STRING;
				xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
				xml_lexeme_p->value.bytes_occupied = 1;
				while((xml_lexer_p->next_token_start != end_char_at) && isspace(*(xml_lexer_p->next_token_start)))
					xml_lexer_p->next_token_start++;
				xml_lexeme_p->value.bytes_occupied = xml_lexer_p->next_token_start - xml_lexeme_p->value.cstring;
				return 1;
			}
			else	// case of unquoted string
			{
				return 1;
			}
		}
	}
}