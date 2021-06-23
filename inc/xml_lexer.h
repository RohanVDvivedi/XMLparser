#ifndef XML_LEXER_H
#define XML_LEXER_H

typedef enum xml_lexeme_type xml_lexeme_type;
enum xml_lexeme_type
{
	OPEN_ANGULAR_BRACKET,				// <
	CLOSE_ANGULAR_BRACKET,				// >
	OPEN_ANGULAR_BRACKET_FORWARD_SLASH,	// </
	FORWARD_SLASH_CLOSE_SQUARE_BRACKET,	// />
	EQUALS,								// =
	QUOTED_STRING,						// "string"
	UNQUOTED_STRING,					// string
	END_OF_XML_STRING
};

typedef struct xml_lexeme xml_lexeme;
struct xml_lexeme
{
	xml_lexeme_type type;	// type of lexeme

	// the value points to the position of the lexeme in the xml_string
	dstring value;
};

typedef struct xml_lexer xml_lexer;
struct xml_lexer
{
	char* next_token_start;

	dstring* xml_string;
};

void init_xml_lexer(xml_lexer* xml_lexer_p, dstring* xml_string);

// after this function call the lex points to the next lexeme after its previous value
// returns 1 for success, a return value of 0 represents lexical error
int get_next_xml_lexeme(xml_lexer* xml_lexer_p, xml_lexeme* lexeme_p);

#endif