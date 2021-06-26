#include<stdio.h>
#include<stdlib.h>

#include<xml_lexer.h>

char* xml_lexemes_string[] = {
	"[whitespaces]",
	"[<]",
	"[>]",
	"[</]",
	"[/>]",
	"[=]",
	"[\"string\"]",
	"[string]",
	"EOF"
};

int main()
{
	printf("xml string building start\n\n");

	dstring const * const xml_str = dstring_DUMMY_CSTRING(" \
		<root>\
			<name give=\"firstname,lastname\" preserve_order=\"true\">\
				<firstname> Rohan </firstname>\
				<lastname> Dvivedi </lastname>\
			</name>\
			<age input=\"integer\">\
				25\
			</age>\
			<score mandatory=\"no\" can_be_empty=\"yup\" />\
			<endtag/>\
		</root>\
	");

	printf("String built : ");
	printf_dstring(xml_str);
	printf("\n\n");

	xml_lexer jslx;
	init_xml_lexer(&jslx, (dstring*)xml_str);

	xml_lexeme jslxm;
	int success = 1;
	do
	{
		success = get_next_xml_lexeme(&jslx, &jslxm);
		printf("<");
		if(jslxm.type != END_OF_XML_STRING)
			printf_dstring(&(jslxm.value));
		printf("> \n \t\t\t\t %s\n", xml_lexemes_string[jslxm.type]);
	}
	while(success && jslxm.type != END_OF_XML_STRING);
	return 0;
}