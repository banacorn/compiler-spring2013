typedef enum {PROGRAM, GLOBAL_DECL_LIST, GLOBAL_DECL, DECL_LIST, FUNCTION_DECL, PARAM_LIST, PARAM, DIM_FN, DIMFN1, EXPR_NULL, BLOCK, DECL, TYPE_DECL, VAR_DECL,
	TYPE, STRUCT_TYPE, DEF_LIST, DEF, OPT_TAG, TAG, ID_LIST, DIM_DECL, CEXPR, MCEXPR, CFACTOR, INIT_ID_LIST, INIT_ID, STMT_LIST, STMT, ASSIGN_EXPR_LIST, 
	NONEMPTY_ASSIGN_EXPR_LIST, TEST, ASSIGN_EXPR, RELOP_EXPR, RELOP_TERM, RELOP_FACTOR, REL_OP, RELOP_EXPR_LIST, NONEMPTY_RELOP_EXPR_LIST, EXPR, ADD_OP, TERM,
	MUL_OP, FACTOR, VAR_REF, DIM, STRUCT_TAIL, NUL,ID_value, CONST_value} AST_TYPE;

typedef enum {ZERO_,INT_,FLOAT_,ARR_,STR_,VOID_,ERROR_,CONST_,FUNC_,POINTER_,STR_VAR_,STRING_,TYPEDEF_, ASSIGN_} ST_TYPE;	

typedef enum {INTEGERC,FLOATC,STRINGC} C_type;

typedef enum {TYPEDEF_INT,TYPEDEF_FLT,TYPEDEF_ARR,TYPEDEF_STR} IS_TYPE_DEF;

typedef enum {FD_TYPEDEF_PARAM, FD_TYPEDEF_NONE, FD_TYPE_PARAM, FD_TYPE_NONE, FD_VOID_PARAM, FD_VOID_NONE} FUNC_DECL_PROP;

typedef enum {P_TYPEDEF_ARR, P_TYPEDEF_NONE, P_TYPE_ARR, P_TYPE_NONE} PARAM_PROP;

typedef enum {B_DECL_STMT, B_DECL, B_STMT, B_NULL} BLOCK_PROP;

typedef enum {TD_TYPEDEF_ID, TD_VOID_ID, TD_TYPE_ID, TD_TYPEDEF} TYPE_DECL_PROP;

typedef enum {VD_TYPE, VD_TYPEDEF, VD_ID} VAR_DECL_PROP;

typedef enum {STRUCT_T_DEF, STRUCT_T_NONE} STRUCT_TYPE_PROP;

typedef enum {OPT_ADD, OPT_SUB, OPT_MUL, OPT_DIV, OPT_EQ, OPT_GE, OPT_LE, OPT_NE, OPT_GT, OPT_LT, OPT_REL, OPT_AND, OPT_OR, OPT_NONE} OP_TYPE_PROP;  

typedef enum {STMT_BLOCK, STMT_WHILE, STMT_FOR, STMT_ASSIGN, STMT_IF_ELSE, STMT_IF, STMT_FUNC_CALL, STMT_NONE, STMT_RETURN_VOID, STMT_RETURN}STMT_PROP;

typedef enum {F_REL, F_REL_MINUS, F_REL_NOT, F_CONST, F_CONST_MINUS, F_CONST_NOT, F_ID, F_ID_MINUS, F_ID_NOT, F_VAR, F_VAR_MINUS, F_VAR_NOT} FACTOR_PROP;

typedef struct {
        C_type  const_type; 
	union { 
		int     intval; 
		double  fval; 
		char    *sc; } 
		const_u; 
} CON_Type;



struct AST_NODE{
	struct AST_NODE *parent;
	struct AST_NODE *child;
//	struct AST_NODE *partner;
	struct AST_NODE *sibling;
	struct AST_NODE *firstborn;
	AST_TYPE type;
	int linenumber;
	union{
		char *lexeme;
		CON_Type *const1;
		FUNC_DECL_PROP func_decl;
		PARAM_PROP param;
		BLOCK_PROP block;
		TYPE_DECL_PROP type_decl;
		VAR_DECL_PROP var_decl;
		ST_TYPE type;
		STRUCT_TYPE_PROP struct_type;
		OP_TYPE_PROP op_type;
		STMT_PROP stmt;
		FACTOR_PROP factor;
	} semantic_value;
 	struct symtab * symptr;
};
typedef struct AST_NODE AST_NODE;

typedef struct{
	int dim;
	int dim_limit[10];
	ST_TYPE arrtype;
	char * type_name;	/*in case of array of structs*/
						/*or in case of array of array through typedef*/
}Type_arr;

typedef struct{
	Type_arr * arr_info;
	char *name;	/*name of array in symbol table, filled in init_id or id_list*/
}array_semantic;

struct struct_semantic{
	ST_TYPE type;
	union{
		char * var_name;			/*name of the variable of type type. */ 
		array_semantic * arr_sem;	/*info if the element is an array*/
		struct{
			char *str_var_name;		/*name of variable in case of nested struct*/
			char * struct_type_name;/*if TYPE is STR_R, this is the name of 
									type of struct in symbol table
									this name is a temporary name since structs 
									do not have tags, but if they do have tags, 
									it is handled in the same way*/ 
		}str_info;
	}struct_semantic_u;
	struct struct_semantic *next;
};
typedef struct struct_semantic struct_semantic;


typedef struct{
	ST_TYPE type;		//type, could be basic type, array or error
	ST_TYPE arrtype;	//if type is ARR_, this the type of array
	int dim;		//if array number of dimensions
}param;

struct param_list{
	param* PPAR;
	struct param_list *next;
};
typedef struct param_list param_list;


typedef Type_arr ST_arr;

typedef struct{
	ST_TYPE ret_type;
	int params;
	param_list * PL;
}ST_func;

typedef struct_semantic ST_struct;


struct symtab{
	char *lexeme;
	ST_TYPE type;
	IS_TYPE_DEF type_when_def; 
	union{
		ST_arr *st_arr;		/*for arrays not nested inside a struct*/
		ST_func *st_func;	/*for function declaration*/
		ST_struct *st_struct;	/*for structure declaration*/
		char * type_name;	/*for structure variables*/
					/*also name of struct type in case of 
					typedef structs*/
	}symtab_u;
	struct symtab *front;
	struct symtab *back;
	int scope;
	int line;
	int offset;
	int number;
    int r;
};
typedef struct symtab symtab;

typedef struct{
	ST_TYPE type;
	char *name;
	union{
		char *type_name;
		Type_arr *arr_info;	
	}var_ref_u;
    int r;
}var_ref;	

/*
struct AST_program{
	struct AST_gdl *g_decl_l;
};

struct AST_gdl{
	struct AST_gdl *g_decl_l;
	struct AST_gd *g_decl;
};

struct AST_gd{
	struct AST_dl *dcl_l;
	struct AST_fd *func_d;
};

///TODO AST_pl
struct AST_fd{
	union func_type{
		AST_TYPE *type;
		char *ID;
	}func_type;
	char *ID;
	//struct AST_pl *param_l;
	struct AST_block *block;
};

struct AST_block{
	struct AST_dl *dcl_l;
	struct AST_sl *stmt_l;
};

struct AST_dl{
	struct AST_dl *dcl_l;
	struct AST_decl *decl;
};

////TODO AST_type_decl
struct AST_decl{
	struct AST_vd *var_decl;;
	//struct AST_type_decl;
};

///TODO AST_init_id_list
struct AST_vd{
	union var_type{
		AST_TYPE *type;
		char *ID;
	}var_type;
	union id_list{
		struct AST_init_id_list *iil;
		struct AST_id_list *il;
	}id_list;
};
//TODO AST_dim_decl
struct AST_id_list{
	struct AST_id_list *id_list;
	char *ID;
	//struct AST_dim_decl
};
//TODO AST_relop_expr
struct AST_init_id_list{
	char *ID;
	//struct AST_dim_decl
	//struct AST_relop_expr
};

struct AST_sl{
	struct AST_sl *stml_l;
	struct AST_stmt *stmt;
};
////TODO complete stmt
struct AST_stmt{
	struct AST_var_ref *var_ref;
	struct AST_relop_expr *relop_exprl;
};

struct AST_relop_expr{
	struct AST_relop_term *relop_term;
	struct AST_relop_expr *relop_expr;
};

struct AST_relop_term{
	struct AST_relop_factor *relop_factor;
	struct AST_relop_term *relop_term;
};

struct AST_relop_factor{
	struct expr *expr1;
	struct expr *expr2;
	AST_TYPE rel_op;
};

struct AST_expr{
	struct AST_term *term;
	struct AST_expr *expr;
	AST_TYPE add_op;
};

struct AST_term{
	struct AST_factor *factor;
	struct AST_term *term;
	AST_TYPE mul_op;
};
//TODO complete factor
struct AST_factor{
	CON_Type const1;
};

struct AST_var_ref{
	//struct AST_var_ref *var_ref;
	char *ID;
};
*/

AST_NODE *Allocate(AST_TYPE type);
char*  printtype(ST_TYPE TYPE);
void VerifyMainCall();

void build_symtable_check(AST_NODE *ast);
ST_TYPE deal_global_decl(AST_NODE *ptr);
ST_TYPE deal_func_decl(AST_NODE *ptr);
ST_TYPE deal_block(AST_NODE* ptr);
ST_TYPE deal_stmt(AST_NODE * ptr);
ST_TYPE stmt_assign_ex(var_ref *a,var_ref *b, int line);
var_ref* deal_assign_expr(AST_NODE *ptr);
var_ref* deal_test(AST_NODE * ptr);

param_list* deal_param_list(AST_NODE *ptr);
param_list* build_param(AST_NODE *ptr);

ST_TYPE deal_decl_list(AST_NODE *ptr);
ST_TYPE deal_var_decl(AST_NODE *ptr);
ST_TYPE deal_type_decl(AST_NODE *ptr);
var_ref* deal_relop_expr(AST_NODE* ptr);
var_ref* deal_relop_term(AST_NODE* ptr);
var_ref* deal_relop_factor(AST_NODE* ptr);
var_ref* deal_expr(AST_NODE* ptr);
var_ref* deal_term(AST_NODE* ptr);
var_ref* deal_factor(AST_NODE* ptr);
var_ref* deal_var_ref(AST_NODE * ptr);
var_ref* check_function(AST_NODE *id, AST_NODE* list);
Type_arr* deal_dim_decl(AST_NODE* ptr);
int deal_cexpr(AST_NODE* ptr);
int deal_mcexpr(AST_NODE* ptr);
int deal_cfactor(AST_NODE*ptr);

int HASH(char * str);
symtab * lookup(char *name);
symtab * insert(char *name,ST_TYPE type,void * P,IS_TYPE_DEF TypeDef, int line);
int delete_scope(int scp);
void insert_buildin_functions();
	
	
	
	
