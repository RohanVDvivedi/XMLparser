#ifndef XML_LEXER_H
#define XML_LEXER_H

typedef enum xml_lexeme_type xml_lexeme_type;
enum xml_lexeme_type
{
	START_OF_XML = 0,
	OPEN_ANGULAR_BRACKET,				// <
	CLOSE_ANGULAR_BRACKET,				// >
	OPEN_ANGULAR_BRACKET_FORWARD_SLASH,	// </
	FORWARD_SLASH_CLOSE_SQUARE_BRACKET,	// />
	EQUALS,								// =
	QUOTED_STRING,						// "string"
	UNQUOTED_STRING,					// string
	END_OF_XML
};

typedef struct xml_lexeme xml_lexeme;
struct xml_lexeme
{
	xml_lexeme_type type;	// type of lexeme

	// the value points to the position of the lexeme in the xml_string
	dstring value;
};

#define INIT_XML_LEXEME ((xml_lexeme){.type = START_OF_XML, .value = {}})

// after this function call the lex points to the next lexeme after its previous value
// returns 1 for success, a return value of 0 represents lexical error
int lexer_get_next_lexeme(xml_lexeme* lex, const dstring* xml_string);

#endif