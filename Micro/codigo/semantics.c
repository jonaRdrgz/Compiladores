#include "semantics.h"
#include "parser.h"
#include <string.h>
int lookup(char* s){
	char* symbol;
	for (int i = 0; i < TABLESIZE; i++)
	{
		symbol = symbol_table[i];
		if(symbol != NULL && strcmp(symbol,s) == 0){
			return 1;
		}
	}
	return 0;
}

void enter(char * s){
	static int index = 0;
	strcpy(symbol_table[index], s);
	index++;
}

char * get_temp(){
	static int max_temp = 0;
	static char tempname[MAXIDLEN];
	if(max_temp == 10) max_temp = 0;
	sprintf(tempname, "r%d", max_temp);
	max_temp++;
	return tempname;
}
char * get_label(){
	static int max_label = 0;
	static char label[MAXIDLEN];

	sprintf(label, "label%d", max_label);
	max_label++;

	return label;
}

void start() {
	/* Semantic initializations, none needed */
	output = fopen (output_name,"w");
	if (output!=NULL) {
		tmp_data_labels = tmpfile();
		fprintf(tmp_data_labels, "\naddress_of_return: .word return\n");
		tmp_data = tmpfile();
		fprintf(tmp_data, ".data\nreturn: .word 0\nformat: .asciz \"Se imprimio- %%d\\n\"\n");

		fprintf(output, ".text\n");
		fprintf(output, ".global main\n");
		fprintf(output, "main:\npush {r4,lr}\n");
	}
	else{
		printf("Error desconocido");
		exit(-1);
	}
}

void finish(){
	fprintf(output,"pop {r4,lr}\n");
	fprintf(output,"bx lr\n");
	fprintf(output,"\n");
	long lSize;
	char * buffer;

	size_t result;

	fseek (tmp_data_labels , 0 , SEEK_END);
	lSize = ftell (tmp_data_labels);
	rewind (tmp_data_labels);
	buffer = (char*) malloc (sizeof(char)*lSize);
 	// copy the file into the buffer:
	result = fread (buffer,1,lSize,tmp_data_labels);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

 	/* the whole file is now loaded in the memory buffer. */
	fprintf(output, "%s\n",buffer);

	fseek (tmp_data , 0 , SEEK_END);
	lSize = ftell (tmp_data);
	rewind (tmp_data);
	buffer = (char*) malloc (sizeof(char)*lSize);
 	// copy the file into the buffer:
	result = fread (buffer,1,lSize,tmp_data);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	fprintf(output, "%s\n",buffer);
}

// Asigna valores en el código ensamblador
void assign(expr_rec target, expr_rec source_expr){
	if(source_expr.kind == LITERALEXPR && target.kind == IDEXPR){
		if(!lookup(target.name)) {
			enter(target.name);
			fprintf(tmp_data_labels,"%s: .word %s\n", target.nameAux, target.name);
			fprintf(tmp_data,"%s: .word %s\n", target.name, extract(source_expr));
		}
		else{
			expr_rec e_rec;
			char* tmp = get_temp();
			e_rec.name = malloc(sizeof(tmp));
			strcpy(e_rec.name, tmp);
			char* tmp_reg1 = malloc(3);
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "mov %s, #%s\n", tmp_reg1, extract(source_expr));
			//fprintf(output, "sw %s, %s\n", tmp_reg, target.name);
			char* tmp_reg2 = malloc(3);
			strcpy(tmp_reg2, get_temp());
			printf("%s\n %s\n",tmp_reg1,tmp_reg2 );
			fprintf(output, "ldr  %s, %s\n", tmp_reg2, target.nameAux);
			fprintf(output, "str %s, [%s]\n", tmp_reg1, tmp_reg2);
		}
	}

	if(source_expr.kind == LITERALEXPR && target.kind == TEMPEXPR){
		fprintf(output, "mov  %s, #%s\n", target.name, extract(source_expr));
	}

	if(source_expr.kind == IDEXPR && target.kind == TEMPEXPR){
		fprintf(output, "ldr  %s, %s\n", target.name, extract(source_expr));
		fprintf(output, "ldr %s, [%s]\n", target.name,target.name);
	}

	if(source_expr.kind == IDEXPR && target.kind == IDEXPR){
		if(!lookup(target.name)) {
			enter(target.name);
			fprintf(tmp_data_labels,"%s: .word %s\n", target.nameAux, target.name);
			fprintf(tmp_data,"%s: .word %d\n", target.name, 0);
		}
	}

	if(source_expr.kind == TEMPEXPR && target.kind == IDEXPR){
		if(!lookup(target.name)) {
			enter(target.name);
			fprintf(tmp_data_labels,"%s: .word %s\n", target.nameAux, target.name);
			fprintf(tmp_data,"%s: .word %d\n", target.name, 0);
		}
		
		char* tmp_reg1 = malloc(3);
		strcpy(tmp_reg1, get_temp());
		fprintf(output, "ldr %s, %s\n",tmp_reg1, target.nameAux);
		fprintf(output, "str %s, [%s]\n",source_expr.name,tmp_reg1);
	}

	if(source_expr.kind == TEMPEXPR && target.kind == TEMPEXPR){
		fprintf(output, "mov %s, %s\n", target.name, source_expr.name);
	}

}

// Escribir saltos a etiquetas en ensamblador
void write_jump(char* label, expr_rec expr){
	char * zero_reg = malloc(3);
	strcpy(zero_reg, get_temp());

	fprintf(output, "mov %s, #%d\n", zero_reg, 0);

	if(expr.kind != TEMPEXPR){
		char * temp_reg = malloc(3);

		if(expr.kind == LITERALEXPR){
			strcpy(temp_reg, get_temp());
			fprintf(output, "mov %s, #%d\n", temp_reg, expr.val);
		}else{
			strcpy(temp_reg, get_temp());
			fprintf(output, "ldr %s, %s\n", temp_reg, expr.nameAux);
			fprintf(output, "ldr %s, [%s]\n",temp_reg,temp_reg);
		}
		fprintf(output, "cmp %s, %s\n", temp_reg, zero_reg);
		fprintf(output, "bne %s\n", label);
	}else{
		fprintf(output, "cmp %s, %s\n", expr.name, zero_reg);
		fprintf(output, "bne %s\n", label);
	}

}

void write_label(char* label){
	fprintf(output, "%s:\n", label);
}

// Escribe saltos explícitos a etiquetas
void extrict_jump(char* label){
	fprintf(output, "b %s\n", label);
}

op_rec process_op(){
	/* Produce operator descriptor */
	op_rec o;

	o.operator = (current_token == PLUSOP) ? PLUS : MINUS;

	return o;
}

// Escribe las operaciones a ensamblador
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
	expr_rec e_rec;

	// Constant Folding
	if(e1.kind == LITERALEXPR && e2.kind == LITERALEXPR){
		e_rec.kind = LITERALEXPR;
		e_rec.val = (op.operator == PLUS)? e1.val + e2.val : e1.val - e2.val;

	} else{
		e_rec.kind = TEMPEXPR;

		char* tmp = get_temp();
		e_rec.name = malloc(sizeof(tmp));

		strcpy(e_rec.name, tmp);
		char* tmp_reg1 = malloc(3);

		char* tmp_reg2 = malloc(3);

		if(e1.kind == LITERALEXPR){
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "mov %s, #%d\n", tmp_reg1, e1.val);
		}
		else if (e1.kind == IDEXPR){
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "ldr %s, %s\n", tmp_reg1, e1.nameAux);
			fprintf(output, "ldr %s, [%s]\n", tmp_reg1,tmp_reg1);
		}
		else{
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "mov %s, %s\n", tmp_reg1, e1.name);
		}

		if(e2.kind == LITERALEXPR){
			strcpy(tmp_reg2,get_temp());
			fprintf(output, "mov %s, #%d\n", tmp_reg2, e2.val);
		}
		else if (e2.kind == IDEXPR){
			strcpy(tmp_reg2, get_temp());
			fprintf(output, "ldr %s, %s\n", tmp_reg2, e2.nameAux);
			fprintf(output, "ldr %s, [%s]\n", tmp_reg2,tmp_reg2);
		}
		else{
			strcpy(tmp_reg2, get_temp());
			fprintf(output, "mov %s, %s\n", tmp_reg2, e2.name);
		}

		fprintf(output, "%s %s, %s, %s\n", extract_op(op), e_rec.name, tmp_reg1,tmp_reg2);
	}
	return e_rec;
}

// Lee información del usuario
void read_id(expr_rec in_var){
	/* Generate code for read. */
	fprintf(output, "ldr r0, addr_%s_scan\n", in_var.name);
	fprintf(output, "ldr r1, addr_%s_num\n", in_var.name );
	fprintf(output, "bl scanf\n");
	fprintf(output, "ldr r0, addr_%s_num\n", in_var.name );
	fprintf(output, "ldr r0,[r0]\n");
	fprintf(output, "ldr r1,%s\n",in_var.nameAux);
	fprintf(output, "str r0,[r1]\n");


	fprintf(tmp_data_labels,"addr_%s_scan: .word %s_scan\n",in_var.name ,in_var.name  );
	fprintf(tmp_data_labels,"addr_%s_num: .word %s_num\n",in_var.name , in_var.name );
	fprintf(tmp_data,"%s_scan: .asciz \"%%d\"\n", in_var.name);
	fprintf(tmp_data,"%s_num: .word 0\n", in_var.name);
	
}

// Procesa los identificadores
expr_rec process_id(char* token){
	expr_rec t;
	char * zero_reg = malloc(sizeof(token+3));
	sprintf(zero_reg, "addr_%s", token);
	t.kind = IDEXPR;
	t.name = malloc(sizeof(token));
	t.nameAux = malloc(sizeof(token+3));

	strcpy(t.nameAux,zero_reg);
	strcpy(t.name, token);
	return t;
}

// Procesa los registros temporales
expr_rec process_temp(char* token){
	expr_rec t;
	t.kind = TEMPEXPR;
	t.name = malloc(sizeof(token));
	strcpy(t.name, token);
	return t;
}

// Procesa los literales enteros
expr_rec process_literal(char* token){
	expr_rec t;
	 t.kind = LITERALEXPR;
	 sscanf(token, "%d", &t.val);
	 return t;
}

// Imprime las expresiones en la consola
void write_expr(expr_rec out_expr){
	if(out_expr.kind == LITERALEXPR) fprintf(output, "mov r1, #%s\n", extract(out_expr));
	else fprintf(output, "mov r1, %s\n", out_expr.name);
	
	fprintf(output, "ldr r0, =format\n");
	fprintf(output, "bl printf\n");
}

// Extrae información de una expresión
char* extract(expr_rec expr){
	char* data = NULL;
	 if (expr.kind == IDEXPR || expr.kind == TEMPEXPR){
	 	data = expr.nameAux;
	 }
	 else{
	 	data = malloc(sizeof(int));
	 	sprintf(data, "%d", expr.val);
	 }
	 return data;
}


// Extrae operaciones de la expresión
char* extract_op(op_rec op){
	char* operation = (op.operator == PLUS) ? "add" : "sub";
	return operation;
}
