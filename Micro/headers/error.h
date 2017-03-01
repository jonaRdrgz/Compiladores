#ifndef ERROR_H
#define ERROR_H

#include "constants.h"
#include "scanner.h"

/**
	Funciones que imprimen en consola un error específico 
*/

void lexical_error(int token);
void syntax_error(void);
void semantic_error(void);
void close_files(void);

#endif 