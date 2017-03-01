#include "error.h"

// Imprime los errores de léxico
void lexical_error(int in_char){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (ALLOCATION);
	fgets (line, ALLOCATION, source);

	printf("Lexical Error: %c is not defined at line %d:\n" , in_char, line_info.number);
	printf( "%s\n", line);
	
	close_files();

	exit(1);
}

// Imprime los errores de sintaxis
void syntax_error(){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (ALLOCATION);
	fgets (line, ALLOCATION, source);

	printf( "Syntax Error: ");
	printf("at line %d: \n %s\n" , line_info.number, line);
	
	close_files();

	exit(1);
}

// Imprime los errores de semática
void semantic_error(){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (ALLOCATION);
	fgets (line, ALLOCATION, source);

	printf( "Semantic Error: " );
	printf( "%s is not defined at line %d: \n %s\n" , token_buffer.token, line_info.number, line);
	
	close_files();

	exit(1);
}

// Cierra los archivos
void close_files(){
	fclose(source);

	if(output){
		fclose(output);
		remove(output_name);
	}
}