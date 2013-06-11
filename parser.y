/* ===== Definition Section ===== */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
int linenumber = 1;
AST_NODE *prog;
int STRUCT_DEC = 0;

static inline void  makesibling(AST_NODE *a,AST_NODE *b){ a->sibling=b; b->parent=a->parent;}
static inline void  makechild(AST_NODE *a,AST_NODE *b){ a->child=b; b->parent=a;}
static inline void  makefirstborn(AST_NODE *a,AST_NODE *b){ a->firstborn=b->firstborn;}
%}



%union{
	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;
};

%token <lexeme>ID
%token <const1>CONST
%token VOID    
%token INT     
%token FLOAT   
%token IF      
%token ELSE    
%token WHILE   
%token FOR 
%token TYPEDEF 
%token OP_ASSIGN  
%token OP_OR   
%token OP_AND  
%token OP_NOT  
%token OP_EQ   
%token OP_NE   
%token OP_GT   
%token OP_LT   
%token OP_GE   
%token OP_LE   
%token OP_PLUS 
%token OP_MINUS        
%token OP_TIMES        
%token OP_DIVIDE       
%token MK_LB 
%token MK_RB 
%token MK_LPAREN       
%token MK_RPAREN       
%token MK_LBRACE       
%token MK_RBRACE       
%token MK_COMMA        
%token MK_SEMICOLON    
%token MK_DOT  
%token ERROR
%token RETURN

%type <node> program global_decl_list global_decl function_decl block stmt_list decl_list decl var_decl type init_id_list init_id  stmt relop_expr relop_term relop_factor expr term factor var_ref
%type <node> param_list param dim_fn dimfn1 expr_null id_list dim_decl cexpr mcexpr cfactor assign_expr_list test assign_expr rel_op relop_expr_list nonempty_relop_expr_list
%type <node> add_op mul_op dim type_decl nonempty_assign_expr_list


%start program

%%

/* ==== Grammar Section ==== */

/* Productions */               /* Semantic actions */
program		: global_decl_list { $$=Allocate(PROGRAM);  makechild($$,$1); prog=$$;}
		| { $$=Allocate(PROGRAM); prog=$$;}
		;

global_decl_list: global_decl_list global_decl {$$=Allocate(GLOBAL_DECL_LIST); makechild($$,$2);makesibling($1, $$);makefirstborn($$,$1);}	
		| global_decl {$$=Allocate(GLOBAL_DECL_LIST);  makechild($$,$1); $$->firstborn=$$;}
		; 

global_decl	: decl_list function_decl {$$=Allocate(GLOBAL_DECL); makechild($$,$1); makesibling($$->child,$2);}
		| function_decl {$$=Allocate(GLOBAL_DECL); makechild($$,$1);}
		;

function_decl	: type ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE {$$=Allocate(FUNCTION_DECL);  makechild($$,$1); makesibling($1,Allocate(ID_value)); $1->sibling->semantic_value.lexeme=$2; makesibling($1->sibling,$4); makesibling($4,$7); $$->semantic_value.func_decl=FD_TYPE_PARAM;}
		| VOID ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE {$$=Allocate(FUNCTION_DECL);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$2; makesibling($$->child,$4);  makesibling($4,$7); $$->semantic_value.func_decl=FD_VOID_PARAM;}
		| type ID MK_LPAREN  MK_RPAREN MK_LBRACE block MK_RBRACE {$$=Allocate(FUNCTION_DECL);  makechild($$,$1); makesibling($$->child,Allocate(ID_value)); $$->child->sibling->semantic_value.lexeme=$2; makesibling($$->child->sibling,$6); $$->semantic_value.func_decl=FD_TYPE_NONE;}
		| VOID ID MK_LPAREN  MK_RPAREN MK_LBRACE block MK_RBRACE {$$=Allocate(FUNCTION_DECL);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$2; makesibling($$->child,$6); $$->semantic_value.func_decl=FD_VOID_NONE;} 
		;

param_list	: param_list MK_COMMA  param {$$=Allocate(PARAM_LIST);  makesibling($1,$$); makefirstborn($$,$1); makechild($$,$3);}
		| param	{$$=Allocate(PARAM_LIST);  makechild($$,$1); $$->firstborn=$$;}
		;

param		: type ID {$$=Allocate(PARAM);  makechild($$,$1); makesibling($1,Allocate(ID_value)); $1->sibling->semantic_value.lexeme=$2; $$->semantic_value.param=P_TYPE_NONE;}
		| type ID dim_fn {$$=Allocate(PARAM);  makechild($$,$1); makesibling($1,Allocate(ID_value)); $1->sibling->semantic_value.lexeme=$2; makesibling($1->sibling,$3); $$->semantic_value.param=P_TYPE_ARR;}
		;
dim_fn		:MK_LB expr_null MK_RB dimfn1 {$$=Allocate(DIM_FN);  makechild($$,$2); makesibling($2,$4);}
		;

dimfn1		:MK_LB expr MK_RB dimfn1 {$$=Allocate(DIMFN1);  makechild($$,$2); makesibling($2,$4);}
		|{ $$=Allocate(DIMFN1);}
		;
expr_null	:expr {$$=Allocate(EXPR_NULL);  makechild($$,$1);}
		|{ $$=Allocate(EXPR_NULL); }
		;

block           : decl_list stmt_list {$$=Allocate(BLOCK);  makechild($$,$1); makesibling($$->child,$2); $$->semantic_value.block=B_DECL_STMT;}
                | stmt_list  {$$=Allocate(BLOCK);  makechild($$,$1); $$->semantic_value.block=B_STMT;}
                | decl_list {$$=Allocate(BLOCK);   makechild($$,$1); $$->semantic_value.block=B_DECL;}
		| {$$=Allocate(BLOCK); $$->semantic_value.block=B_NULL;}
                ;
 
decl_list	: decl_list decl { $$=Allocate(DECL_LIST);  makesibling($1,$$); makefirstborn($$,$1); makechild($$,$2);}
		| decl {$$=Allocate(DECL_LIST);  makechild($$,$1); $$->firstborn=$$;}
		;

decl		: type_decl { $$=Allocate(DECL);  makechild($$,$1);}
		| var_decl {$$=Allocate(DECL);   makechild($$,$1);}
		;

type_decl 	: TYPEDEF type id_list MK_SEMICOLON  {$$=Allocate(TYPE_DECL);  makechild($$,$2);  makesibling($2,$3); $$->semantic_value.type_decl=TD_TYPE_ID;}
		| TYPEDEF VOID id_list MK_SEMICOLON {$$=Allocate(TYPE_DECL);  makechild($$,$3); $$->semantic_value.type_decl=TD_VOID_ID;}
		;

var_decl	: type init_id_list MK_SEMICOLON {$$=Allocate(VAR_DECL);  makechild($$,$1); makesibling($1,$2); $$->semantic_value.var_decl=VD_TYPE;}
		| ID id_list MK_SEMICOLON {$$=Allocate(VAR_DECL);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; makesibling($$->child,$2); $$->semantic_value.var_decl=VD_ID;}
		;

type		: INT {$$=Allocate(TYPE);  $$->semantic_value.type=INT_;}
		| FLOAT {$$=Allocate(TYPE);  $$->semantic_value.type=FLOAT_;}
		;

id_list		: ID {$$=Allocate(ID_LIST);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; $$->semantic_value.type=STR_VAR_; $$->firstborn=$$;}
		| id_list MK_COMMA ID {$$=Allocate(ID_LIST);  makesibling($1,$$); makefirstborn($$,$1); $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$3; $$->semantic_value.type=STR_VAR_;}
		| id_list MK_COMMA ID dim_decl {$$=Allocate(ID_LIST);  makesibling($1,$$); makefirstborn($$,$1); $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$3; makesibling($$->child,$4); $$->semantic_value.type=ARR_;}
		| ID dim_decl {$$=Allocate(ID_LIST);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; makesibling($$->child,$2); $$->semantic_value.type=ARR_; $$->firstborn=$$;}
		;
dim_decl	: MK_LB cexpr MK_RB {$$=Allocate(DIM_DECL);  makechild($$,$2); $$->firstborn=$$;} 
		| dim_decl MK_LB cexpr MK_RB {$$=Allocate(DIM_DECL);  makesibling($1,$$); makefirstborn($$,$1); makechild($$,$3);}
		;
cexpr		: cexpr OP_PLUS mcexpr {$$=Allocate(CEXPR);  makechild($$,$1); makesibling($1,$3); $$->semantic_value.op_type=OPT_ADD; } 
		| cexpr OP_MINUS mcexpr {$$=Allocate(CEXPR); makechild($$,$1); makesibling($1,$3); $$->semantic_value.op_type=OPT_SUB;}
		| mcexpr {$$=Allocate(CEXPR);   makechild($$,$1); $$->semantic_value.op_type=OPT_NONE;}
		;  
mcexpr		: mcexpr OP_TIMES cfactor {$$=Allocate(MCEXPR);   makechild($$,$1); makesibling($1,$3); $$->semantic_value.op_type=OPT_MUL;}
		| mcexpr OP_DIVIDE cfactor  {$$=Allocate(MCEXPR);   makechild($$,$1); makesibling($1,$3); $$->semantic_value.op_type=OPT_DIV;}
		| cfactor {$$=Allocate(MCEXPR);   makechild($$,$1); $$->semantic_value.op_type=OPT_NONE; }
		;
cfactor         : CONST {$$=Allocate(CFACTOR);  $$->child=Allocate(CONST_value); $$->child->semantic_value.const1=$1;}
		|MK_LPAREN cexpr MK_RPAREN {$$=Allocate(CFACTOR);   makechild($$,$2);}
		;

init_id_list	: init_id {$$=Allocate(INIT_ID_LIST);    makechild($$,$1); $$->firstborn=$$; }
		| init_id_list MK_COMMA init_id {$$=Allocate(INIT_ID_LIST);  makesibling($1,$$); makefirstborn($$,$1);  makechild($$,$3);}
		;

init_id		: ID {$$=Allocate(INIT_ID);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; $$->semantic_value.type=STR_VAR_;}
		| ID dim_decl {$$=Allocate(INIT_ID);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; makesibling($$->child,$2); $$->semantic_value.type=ARR_; }
		| ID OP_ASSIGN relop_expr {$$=Allocate(INIT_ID);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; makesibling($$->child,$3); $$->semantic_value.type=ASSIGN_;}
		;

stmt_list	: stmt_list stmt {$$=Allocate(STMT_LIST);  makesibling($1,$$); makefirstborn($$,$1); makechild($$,$2);}
		| stmt {$$=Allocate(STMT_LIST);  makechild($$,$1); $$->firstborn=$$; }
		;



stmt		: MK_LBRACE block MK_RBRACE {$$=Allocate(STMT);  makechild($$, $2); $$->semantic_value.stmt=STMT_BLOCK;}
		| WHILE MK_LPAREN test MK_RPAREN stmt {$$=Allocate(STMT); makechild($$, $3); makesibling($3, $5); $$->semantic_value.stmt=STMT_WHILE;}
	    	| FOR MK_LPAREN assign_expr_list MK_SEMICOLON relop_expr_list MK_SEMICOLON assign_expr_list MK_RPAREN stmt {$$=Allocate(STMT); makechild($$, $3); makesibling($3, $5); makesibling($5, $7); makesibling($7, $9); $$->semantic_value.stmt=STMT_FOR;}
		| var_ref OP_ASSIGN relop_expr MK_SEMICOLON {$$=Allocate(STMT);  makechild($$, $1); makesibling($1, $3); $$->semantic_value.stmt=STMT_ASSIGN;}
		| IF MK_LPAREN test MK_RPAREN stmt { $$=Allocate(STMT);  makechild($$, $3); makesibling($3, $5); $$->semantic_value.stmt=STMT_IF;}
		| IF MK_LPAREN test MK_RPAREN stmt ELSE stmt { $$=Allocate(STMT);  makechild($$, $3); makesibling($3, $5); makesibling($5, $7); $$->semantic_value.stmt=STMT_IF_ELSE;}
		| ID MK_LPAREN relop_expr_list MK_RPAREN MK_SEMICOLON {$$=Allocate(STMT);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme=$1; makesibling($$->child, $3);   $$->semantic_value.stmt=STMT_FUNC_CALL;}
		| MK_SEMICOLON {$$=Allocate(STMT);  $$->semantic_value.stmt=STMT_NONE;}
		| RETURN MK_SEMICOLON  {$$=Allocate(STMT);  $$->semantic_value.stmt=STMT_RETURN_VOID;}
		| RETURN relop_expr MK_SEMICOLON {$$=Allocate(STMT);  makechild($$, $2); $$->semantic_value.stmt=STMT_RETURN;}
		;

assign_expr_list : nonempty_assign_expr_list {$$=Allocate(ASSIGN_EXPR_LIST);  makechild($$, $1);}
                |  {$$=Allocate(ASSIGN_EXPR_LIST); }
                ;

nonempty_assign_expr_list        : nonempty_assign_expr_list MK_COMMA assign_expr {$$=Allocate(NONEMPTY_ASSIGN_EXPR_LIST);  makesibling($1, $$); makefirstborn($$, $1); makechild($$, $3);}
                | assign_expr {$$=Allocate(NONEMPTY_ASSIGN_EXPR_LIST);  $$->child=$1; $$->firstborn=$$;}
		;

test		: assign_expr {$$=Allocate(TEST);  makechild($$, $1);}
		;

assign_expr     : ID OP_ASSIGN relop_expr {$$=Allocate(ASSIGN_EXPR);  $$->child=Allocate(ID_value); $$->child->semantic_value.lexeme= $1; makesibling($$->child,  $3); $$->semantic_value.type=ASSIGN_;}
                | relop_expr {$$=Allocate(ASSIGN_EXPR);  makechild($$, $1); $$->semantic_value.type=VOID_;}
		;

relop_expr	: relop_term {$$=Allocate(RELOP_EXPR);  makechild($$, $1); $$->semantic_value.op_type=OPT_NONE;}
		| relop_expr OP_OR relop_term {$$=Allocate(RELOP_EXPR);  makechild($$, $1); makesibling($1, $3); $$->semantic_value.op_type=OPT_OR;}
		;

relop_term	: relop_factor {$$=Allocate(RELOP_TERM);  makechild($$, $1); $$->semantic_value.op_type=OPT_NONE;}
		| relop_term OP_AND relop_factor {$$=Allocate(RELOP_TERM);  makesibling($$, $1); makechild($$, $3); $$->semantic_value.op_type=OPT_AND;}
		;

relop_factor	: expr {$$=Allocate(RELOP_FACTOR);  makechild($$, $1); $$->semantic_value.op_type=OPT_NONE;}
		| expr rel_op expr {$$=Allocate(RELOP_FACTOR); makechild($$, $1); makesibling($1, $2); makesibling($2, $3); $$->semantic_value.op_type=OPT_REL;}
		;

rel_op		: OP_EQ {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_EQ;}
		| OP_GE {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_GE;}
		| OP_LE {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_LE;}
		| OP_NE {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_NE;}
		| OP_GT {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_GT;}
		| OP_LT {$$=Allocate(REL_OP);  $$->semantic_value.op_type=OPT_LT;};









relop_expr_list	: nonempty_relop_expr_list {$$=Allocate(RELOP_EXPR_LIST);  makechild($$,$1);}
		| {$$=Allocate(RELOP_EXPR_LIST); }
		;

nonempty_relop_expr_list	: nonempty_relop_expr_list MK_COMMA relop_expr {$$=Allocate(NONEMPTY_RELOP_EXPR_LIST);  makesibling($1,$$); makefirstborn($$,$1); makechild($$,$3);}
		| relop_expr {$$=Allocate(NONEMPTY_RELOP_EXPR_LIST);  makechild($$,$1); $$->firstborn=$$;}
		;

expr		: expr add_op term {$$=Allocate(EXPR);  makechild($$,$1); makesibling($1,$2); makesibling($2,$3); $$->semantic_value.op_type=OPT_REL;}
		| term {$$=Allocate(EXPR);  makechild($$,$1); $$->semantic_value.op_type=OPT_NONE;}
		;

add_op		: OP_PLUS {$$=Allocate(ADD_OP);  $$->semantic_value.op_type=OPT_ADD;}
		| OP_MINUS {$$=Allocate(ADD_OP);  $$->semantic_value.op_type=OPT_SUB;}
		;

term		: term mul_op factor {$$=Allocate(TERM);  makechild($$,$1); makesibling($1,$2); makesibling($2,$3); $$->semantic_value.op_type=OPT_REL;}
		| factor {$$=Allocate(TERM);  makechild($$,$1); $$->semantic_value.op_type=OPT_NONE;}
		;

mul_op		: OP_TIMES {$$=Allocate(MUL_OP);  $$->semantic_value.op_type=OPT_MUL;}
		| OP_DIVIDE {$$=Allocate(MUL_OP);  $$->semantic_value.op_type=OPT_DIV;}
		;

factor		: MK_LPAREN relop_expr MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,$2); $$->semantic_value.factor=F_REL;}
		| OP_MINUS MK_LPAREN relop_expr MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,$3); $$->semantic_value.factor=F_REL_MINUS;}
		| OP_NOT MK_LPAREN relop_expr MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,$3); $$->semantic_value.factor=F_REL_NOT;}
		| CONST {$$=Allocate(FACTOR); makechild($$,Allocate(CONST_value)); $$->child->semantic_value.const1=$1; $$->semantic_value.factor=F_CONST;}
		| OP_MINUS CONST {$$=Allocate(FACTOR);  makechild($$,Allocate(CONST_value)); $$->child->semantic_value.const1=$2; $$->semantic_value.factor=F_CONST_MINUS;}
		| OP_NOT CONST {$$=Allocate(FACTOR);  makechild($$,Allocate(CONST_value)); $$->child->semantic_value.const1=$2; $$->semantic_value.factor=F_CONST_NOT;}
		| ID MK_LPAREN relop_expr_list MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$1; makesibling($$->child,$3); $$->semantic_value.factor=F_ID;}
		| OP_MINUS ID MK_LPAREN relop_expr_list MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$2; makesibling($$->child,$4); $$->semantic_value.factor=F_ID_MINUS;}
		| OP_NOT ID MK_LPAREN relop_expr_list MK_RPAREN {$$=Allocate(FACTOR);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$2; makesibling($$->child,$4); $$->semantic_value.factor=F_ID_NOT;}
		| var_ref {$$=Allocate(FACTOR);  makechild($$,$1); $$->semantic_value.factor=F_VAR;}
		| OP_MINUS var_ref {$$=Allocate(FACTOR);  makechild($$,$2); $$->semantic_value.factor=F_VAR_MINUS;}
		| OP_NOT var_ref {$$=Allocate(FACTOR);  makechild($$,$2); $$->semantic_value.factor=F_VAR_NOT;}
		;

var_ref		: ID {$$=Allocate(VAR_REF);  makechild($$,Allocate(ID_value)); $$->child->semantic_value.lexeme=$1; $$->semantic_value.type=STR_;}
		|var_ref dim {$$=Allocate(VAR_REF);  makechild($$,$1); makesibling($1,$2); $$->semantic_value.type=ARR_;}
		;


dim		: MK_LB expr MK_RB {$$=Allocate(DIM);  makechild($$,$2);}
		;



%%

#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
	 printf("%s\n", "Parsing completed. No errors found.");
//	 printGV(prog);
	 insert_buildin_functions();
	 build_symtable_check(prog);
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }



