#include "scanner.h"
#include "parser.h"

char* create_newFile(const char *filename);

int main(int argc, char const *argv[])
{
	source = fopen (argv[1],"r");
	
	if (source != NULL)
	{
		output_name = create_newFile(argv[1]);
		sprintf(output_name, "%s.s", output_name);

		//Call to the compiler
		system_goal();
		
		fclose(source);
		fclose(output);

		return 0;
	}
	else{
		printf("Error abriendo el archivo '%s'\n", argv[1]);
		return 1;
	}
}

char* create_newFile(const char *filename) {
    char *result;
    char *lastdot;

    if (filename == NULL)
         return NULL;

    if ((result = malloc (strlen (filename) + 1)) == NULL)
        return NULL;

    strcpy (result, filename);
    lastdot = strrchr (result, '.');

    if (lastdot != NULL)
        *lastdot = '\0';

    return result;
}
