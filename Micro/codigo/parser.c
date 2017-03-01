#include "parser.h"

/* FUncion que se llama desde el main*/
void system_goal(){
	program();
	match(SCANEOF);
}

void program(){
	start();
	match(BEGIN);
	statement_list();
	match(END);
	
	finish();
}

void statement_list(){
	statement();
	while(true){
		switch(next_token()){
			case ID:
			case READ:
			case WRITE:
				statement();
				break;
			default:
				return;
		}
	}
}

// Verifica las instrucciones
void statement(){
	token tok = next_token();

	switch(tok) {
		case ID:
			match(ID); 
			expr_rec id = process_id(token_buffer.token);
			match(ASSIGNOP);
			expression(&id, 0); 
			match(SEMICOLON);
			break;

		case READ:
			match(READ); match(LPAREN);
			id_list(); match(RPAREN); 
			match(SEMICOLON);
			break;

		case WRITE:
			match(WRITE); match(LPAREN);
			expr_list(); match(RPAREN);
			match(SEMICOLON);
			break;

		default:
			syntax_error();
			break;
	}
}

// Verifica la lista de ids para el read
void id_list(){
	match(ID);
	
	if(!lookup(token_buffer.token)){
		semantic_error();
	
	}

	expr_rec id = process_id(token_buffer.token);
	read_id(id);
	
	while(next_token() == COMMA){
		match(COMMA);
		match(ID);
		
		if(!lookup(token_buffer.token)){
			semantic_error();
		}
		
		id = process_id(token_buffer.token);
		read_id(id);
	}
}

void condicional(expr_rec *target, token t){
	if(t == PIPEOP){
	 	char * label1 = malloc(ALLOCATION);
		char * label2 = malloc(ALLOCATION);

		/* Costruye las etiquetas de salto*/
		strcpy(label1, get_label());
		strcpy(label2, get_label());

		match(PIPEOP);

		write_jump(label1, *target);
		expression(target, CONDITIONAL_ON);

		match(PIPEOP);

		/* Imprime en el archivo las etiquetas y saltos */
		extrict_jump(label2);
		write_label(label1);

		expression(target, CONDITIONAL_OFF);

		write_label(label2);
		free(label1);
		free(label2);
	}
}

void expression(expr_rec *target, int cond_flag){
	token t;
	int print_flag = 0;
	int print_flag_write = 0; 

	if(target == NULL){
		char* tmp = get_temp();
		expr_rec tmp_expr = process_temp(tmp);

		target = &tmp_expr;

		print_flag = 1;
	}

	expr_rec op1 = primary(*target);

	for(t = next_token(); t == PLUSOP || t == MINUSOP; t = next_token()){
		op_rec op = add_op();
		expr_rec op2 = primary(*target);
		op1 = gen_infix(op1,op,op2);
	}

	
	/* SI es un identificador se hace la asignacion respectiva*/
	if(op1.kind ==  IDEXPR){
		char* tmp = get_temp();
		expr_rec tmp_expr = process_temp(tmp);
		assign(tmp_expr,op1);
		*target = tmp_expr;
	}
	else{
		if(print_flag){
			write_expr(op1);
			print_flag_write = 1;
		}else{
			assign(*target, op1);
		}
		
	}
	if(!cond_flag){
		condicional(target, t);
	}

	// Imprime la expresión
	if(print_flag){
		if(!print_flag_write){
			write_expr(*target);
		}
	}

}

//  Verifica una lista de expresiones
void expr_list(){ 
	expression(NULL, CONDITIONAL_OFF);

	while(next_token() == COMMA){
		match(COMMA);
		expression(NULL, CONDITIONAL_OFF);
	}
}

// Obtiene la operación de la expresión
op_rec add_op(){
	token tok = next_token();
	op_rec op;
	if(tok == PLUSOP || tok == MINUSOP){
		match(tok);
		op = process_op(token_buffer.token);
		return op;
	}
	else{
		syntax_error();
	}
	return op;
}

// Procesa las expresiones
expr_rec primary(expr_rec target){
	token tok = next_token();
	expr_rec source; 
	switch(tok){
		case LPAREN:
	 		/* <primary> ::= ( <expression> ) */
	 		match(LPAREN); 
	 		expression(&target, CONDITIONAL_OFF);
	 		source = target;
	 		match(RPAREN);
	 		break;
	 	case ID:
	 		/* <primary> ::= ID */
	 		if(!lookup(token_buffer.token)){
				semantic_error();
			}
	 		match(ID);
	 		source = process_id(token_buffer.token);
	 		break;
	 	case INTLITERAL:
	 		/* <primary> ::= INTLITERAL */
	 		match(INTLITERAL);
	 		source = process_literal(token_buffer.token);
	 		break;
	 	default:
	 		syntax_error();
	 		break;
	 }

	 return source;
}

// Verifica si el token de la gramática es el mismo que en el programa
void match(token t){
	if (tmp_token == NULL){
		if (scanner() == t){
			current_token = t;
		}
		else{
			syntax_error();
		}
	}
	else{
		if(*tmp_token == t){
			current_token = *tmp_token;
			tmp_token = NULL;
		}
		else{
			syntax_error();
		}
	}
}
token next_token(){
	token tok;
	if (tmp_token == NULL){
		tok = scanner();
		tmp_token = malloc(sizeof(tok));
		*tmp_token = tok;
	}
	else
		tok = *tmp_token;
	return tok;
}