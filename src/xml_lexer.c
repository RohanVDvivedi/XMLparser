#include<xml_lexer.h>

#include<stdio.h>
#include<ctype.h>

void init_xml_lexer(xml_lexer* xml_lexer_p, dstring* xml_string)
{
	xml_lexer_p->next_token_start = xml_string->cstring;
	xml_lexer_p->xml_string = xml_string;
}

int get_next_xml_lexeme(xml_lexer* xml_lexer_p, xml_lexeme* xml_lexeme_p)
{
	char* end_char_at = xml_lexer_p->xml_string->cstring + xml_lexer_p->xml_string->bytes_occupied;

	if(xml_lexer_p->next_token_start == NULL || xml_lexer_p->next_token_start == end_char_at)
	{
		xml_lexeme_p->type = END_OF_XML_STRING;
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
		case '<' :	// case for < OR </
		{
			xml_lexeme_p->type = OPEN_ANGULAR_BRACKET;
			xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
			if((xml_lexer_p->next_token_start != end_char_at) && (*(xml_lexer_p->next_token_start)) == '/')
			{
				xml_lexeme_p->type = OPEN_ANGULAR_BRACKET_FORWARD_SLASH;
				xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
			}
			xml_lexeme_p->value.bytes_occupied = xml_lexer_p->next_token_start - xml_lexeme_p->value.cstring;
			return 1;
		}
		case '/' :	// case for />
		{
			return 1;
		}
		case '>' :	// case for >
		{
			xml_lexeme_p->type = CLOSE_ANGULAR_BRACKET;
			xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
			xml_lexeme_p->value.bytes_occupied = 1;
			return 1;
		}
		case '=' :	// case for =
		{
			xml_lexeme_p->type = EQUALS;
			xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
			xml_lexeme_p->value.bytes_occupied = 1;
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
				xml_lexeme_p->type = UNQUOTED_STRING;
				xml_lexeme_p->value.cstring = xml_lexer_p->next_token_start++;
				xml_lexeme_p->value.bytes_occupied = 1;
				while((xml_lexer_p->next_token_start != end_char_at) && !isspace(*(xml_lexer_p->next_token_start))
					&& (*(xml_lexer_p->next_token_start)) != '<' && (*(xml_lexer_p->next_token_start)) != '>')
					xml_lexer_p->next_token_start++;
				xml_lexeme_p->value.bytes_occupied = xml_lexer_p->next_token_start - xml_lexeme_p->value.cstring;
				return 1;
			}
		}
	}
}