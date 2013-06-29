#include "header.h"
#include "parser.tab.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define TABLE_SIZE  1024
#define OUTPUT "output.s"
#define GLOBAL 0

#define BASE_FRAME_SIZE 92
void init();

typedef struct List {
    char * data;
    int index;
    struct List * cons;
} List;

int tempInt;
float tempFloat;


FILE * fp;

int localVariableOrder;
int globalVariableInitialized;
int parameterNumber = 4;
int argumentIndex = 1;
ST_TYPE LHTYPE;

// .data
List * literalStringList;

// register
int iRegisterIndex = 8;
int fpRegisterIndex = 4;
int literalStringIndex = 0;

int labelIndex = 0;

// currentFunction
char * currentFunction;

// parameter list
Parameter * parameters;

// control statement labels
int whileIndex = 0;
int ifIndex = 0;
int ifElseIndex = 0;





extern symtab * hash_table[TABLE_SIZE];
extern int linenumber;
int scope=0;
ST_TYPE func_return;
int IS_RETURN=0;
int global_error=0;

char *AST_TYPE_string[]={"PROGRAM", "GLOBAL_DECL_LIST", "GLOBAL_DECL", "DECL_LIST", "FUNCTION_DECL", "PARAM_LIST", "PARAM", "DIM_FN", "DIMFN1", "EXPR_NULL", "BLOCK", "DECL", "TYPE_DECL", "VAR_DECL",
    "TYPE", "STRUCT_TYPE", "DEF_LIST", "DEF", "OPT_TAG", "TAG", "ID_LIST", "DIM_DECL", "CEXPR", "MCEXPR", "CFACTOR", "INIT_ID_LIST", "INIT_ID", "STMT_LIST", "STMT", "ASSIGN_EXPR_LIST", 
    "NONEMPTY_ASSIGN_EXPR_LIST", "TEST", "ASSIGN_EXPR", "RELOP_EXPR", "RELOP_TERM", "RELOP_FACTOR", "REL_OP", "RELOP_EXPR_LIST", "NONEMPTY_RELOP_EXPR_LIST", "EXPR", "ADD_OP", "TERM",
    "MUL_OP", "FACTOR", "VAR_REF", "DIM", "STRUCT_TAIL", "NUL","ID_value", "CONST_value"};

char*  printtype(ST_TYPE TYPE){
    char *ST_TYPE_string[]={"ZERO_", "INT_", "FLOAT_", "ARR_", "STR_","VOID_","ERROR_","CONST_","FUNC_","POINTER_","STR_VAR_","STRING_","TYPEDEF_", "ASSIGN_"}; 
    return ST_TYPE_string[TYPE];
}

void printAST(AST_NODE *ptr){
    if (ptr->type!=NUL){
        printf("-%s-",AST_TYPE_string[ptr->type]);
        printAST(ptr->sibling);
        printAST(ptr->child);
        printAST(ptr->sibling);
    }
    else{
        printf("\n");
    }
}


void VerifyMainCall(){
   struct symtab * temp;
   temp = lookup("main"); 
   if (temp != NULL) {
      if ( (temp->scope ==0) && (temp->type == FUNC_) 
         && (temp->symtab_u.st_func->params == 0) )
               return;
         }
   printf("Warning: no valid Main function \n");
}

Reference
getStrLit () {
    Reference r;
    r.index = literalStringIndex++;
    r.type = StrLit;
    return r;
}

Reference 
getIReg () {
    Reference r;
    r.type = IReg;
    r.index = iRegisterIndex;
    iRegisterIndex++;
    if (iRegisterIndex == 20)
        iRegisterIndex = 8;
    return r;
}

// f4 ~ f14
Reference 
getFPReg () {
    Reference r;
    r.type = FPReg;
    r.index = fpRegisterIndex;
    fpRegisterIndex += 2;
    if (fpRegisterIndex == 20)
        fpRegisterIndex = 4;
    return r;
}

char *
toReg (Reference r) {
    char * str = malloc(sizeof(char) * 20);
    switch (r.type) {
        case IReg:
            sprintf(str, "$%d", r.index);
            return str;
        case FPReg:
            sprintf(str, "$f%d", r.index);
            return str;
        case StrLit:
            sprintf(str, "m%d", r.index);
            return str;
    }
}

void
insertLiteralString (char * string, int index) {

    List * l = malloc(sizeof(List));
    l -> data = string;
    l -> cons = literalStringList;
    l -> index = index;
    literalStringList = l;
}

void
genLiteralString () {
    List * l = literalStringList;
    while (l) {
        // printf("%d %p %p\n", l -> index, l -> data, l -> cons);
        if (l -> data) {
            fprintf(fp, "    m%d: .asciiz %s\n", l -> index, l -> data);
        }
        l = l -> cons;
    } 
}


void build_symtable_check(AST_NODE *ast){
    init();

    AST_NODE *temp;
    ST_TYPE result=ZERO_;
    ST_TYPE generate;
    if (ast->type!=PROGRAM){
        printf("ERROR AST type: should be PROGRAM",ast->type);
        exit(0);
    }
    else if (ast->child->type==GLOBAL_DECL_LIST){
        temp=ast->child->firstborn;
        do{
            generate=deal_global_decl(temp->child);
            result=(result==ERROR_)?ERROR_:generate;
            temp=temp->sibling;
        }while(temp->type==GLOBAL_DECL_LIST);
    }


    fprintf(fp, ".data\n");
    genLiteralString();
    
    VerifyMainCall();
    
    if ((result==ERROR_)||(global_error)){
        printf("error:  Semantic Analysis failed due to errors\n");
    }
}

//
//
//
void
printTab (symtab * tab) {
    printf("------------------\n");
    printf("    name: %s\n", tab -> lexeme);
    if (tab -> type == FUNC_)
        printf("    return type: %d\n", tab -> symtab_u.st_func -> ret_type);
    printf("    scope: %d\n", tab -> scope);
    printf("    offset: %d\n", tab -> offset);
    printf("    register: %d\n", tab -> reference.index);
    printf("------------------\n");
}
void
printReference (Reference reference) {
    printf("------------------\n");
    switch (reference.type) {
        case IReg:
            printf("    type: Int\n");
            printf("    register: $%d\n", reference.index);
            break;
        case FPReg:
            printf("    type: Float\n");
            printf("    register: $f%d\n", reference.index);
            break;
        case StrLit:
            printf("    type: String Literal\n");
            printf("    label: #%d\n", reference.index);
            break;
        default:
            printf("    ??: %d\n", reference.type);
    }
    printf("------------------\n");
}

void init () {
    fp = fopen(OUTPUT, "w");
}



void
functionStart () {
    fprintf(fp, ".data\n");
    localVariableOrder = 0;
    globalVariableInitialized = 0;

}

void
functionFinish () {
}

void
genGlobalVariableDeclaration (char * name, ST_TYPE type) {
    switch (type) {
        case INT_:
            if (tempInt == 0 && tempFloat != 0) {
                tempInt = tempFloat;
                tempFloat = 0;                
            }
            fprintf(fp, "    var_%s:\t\t.word %d\n", name, tempInt);
            tempInt = 0;
            break;
        case FLOAT_:
            if (tempInt != 0 && tempFloat == 0) {
                tempFloat = tempInt;
                tempInt = 0;                
            }
            fprintf(fp, "    var_%s:\t\t.float %f\n", name, tempFloat);
            tempFloat = 0.0;
            break;
        default:
            printf("??? %s\n", name);
    }
}

Reference
genFloattoInt (Reference i) {
    Reference tempIntReg = getIReg();   
    fprintf(fp, "    # Float -> Int conversion \n");         
    fprintf(fp, "    cvt.w.s $f%d, $f%d\n", i.index, i.index);
    fprintf(fp, "    mfc1 $%d, $f%d\n", tempIntReg.index, i.index);
    return tempIntReg;
}

Reference
genInttoFloat (Reference f) {
    Reference tempFloatReg = getFPReg();    
    fprintf(fp, "    # Int -> Float conversion \n");         
    fprintf(fp, "    mtc1 $%d, $f%d\n", f.index, tempFloatReg.index);
    fprintf(fp, "    cvt.s.w $f%d, $f%d\n", tempFloatReg.index, tempFloatReg.index);
    return tempFloatReg;
}

void
genLocalVariableInitialization (char * name, ST_TYPE type, var_ref * expression) {
    int frameOffset = lookup(name) -> offset;
    int registerOffset = expression -> reference.index;

    switch (type) {
        case INT_:
            fprintf(fp, "    # Int const initialization\n");
            if (expression -> type == INT_) {
                fprintf(fp, "    sw $%d, %d($fp)\n", registerOffset, frameOffset);
            } else {
                Reference tempIntReg = genFloattoInt(expression -> reference);
                fprintf(fp, "    sw $%d, %d($fp)\n", tempIntReg.index, frameOffset);
            }
            break;
        case FLOAT_:
            fprintf(fp, "    # Float const initialization\n");
            if (expression -> type == FLOAT_) {
                fprintf(fp, "    s.s $f%d, %d($fp)\n", registerOffset, frameOffset);
                
            } else {
                Reference tempFloatReg = genInttoFloat(expression -> reference);
                fprintf(fp, "    s.s $f%d, %d($fp)\n", tempFloatReg.index, frameOffset);
            }

            break;
        default:
            printf("??? %s\n", name);
    }
}

void
genLocalVariableDeclaration (char * name, ST_TYPE type) {
    symtab * tab;
    tab = lookup(name);
    tab -> offset = -4 + -4 * localVariableOrder;
    tab -> number = localVariableOrder;
    localVariableOrder++;
}

void
genReturn (Reference ref) {
    fprintf(fp, "    # return\n");        
    if (ref.type == IReg)
        fprintf(fp, "    move $v0, $%d\n", ref.index);
    else if (ref.type == FPReg)
        fprintf(fp, "    mov.s $f0, $f%d\n", ref.index);
    fprintf(fp, "    j %s_end\n", currentFunction);
};

void
genWrite (var_ref * ref) {
    fprintf(fp, "    # write\n");        
    switch (ref -> type) {
        case INT_:
            fprintf(fp, "    li $v0, 1\n");
            fprintf(fp, "    move $a0, $%d\n", ref -> reference.index);
            break;
        case FLOAT_:
            fprintf(fp, "    li $v0, 2\n");
            fprintf(fp, "    mov.s $f12, $f%d\n", ref -> reference.index);
            break;
        case STRING_:
            fprintf(fp, "    li $v0, 4\n");
            fprintf(fp, "    la $a0, m%d\n", ref -> reference.index);
            break;
    }
    fprintf(fp, "    syscall\n");
}

void
genSaveParameter () {
    // parameters
    fprintf(fp, "    # save parameters\n");
    int i;
    for (i = 0; i < 8; i++) {
        fprintf(fp, "    sw $%d, %d($sp)\n", 23 - i, 32 - i * 4 + 4);

    }
}

void
genRestoreParameter () {
    // parameters
    int i;
    for (i = 0; i < 8; i++) {
        fprintf(fp, "    lw $%d, %d($sp)\n", 23 - i, 32 - i * 4 + 4);
    }
}

void
genParameter (AST_NODE * id, var_ref * ref) {
    genSaveParameter();

    Reference temp;
    ST_func * funcStruct = id -> symptr -> symtab_u.st_func; 
    param_list * PL = funcStruct -> PL;
    Parameter * parameter = ref -> parameter;
    int i = 0;

    int parameterNumber = funcStruct -> params;

    fprintf(fp, "    # moving parameters\n");
    while (PL) {
        ST_TYPE parameterType = PL -> PPAR -> type;
        if (parameterType == INT_ && parameter -> reference.type == IReg) {
            fprintf(fp, "    move $%d, $%d \n", -i + 15 + parameterNumber, parameter -> reference.index);
        } else if (parameterType == FLOAT_ && parameter -> reference.type == IReg) {
            temp = genInttoFloat(parameter -> reference);
            fprintf(fp, "    mov.s $f%d, $f%d \n", -i + 15 + parameterNumber, temp.index);
        } else if (parameterType == FLOAT_ && parameter -> reference.type == FPReg) {
            fprintf(fp, "    s.s $f%d, 4($sp) \n", parameter -> reference.index);
            fprintf(fp, "    lw $%d, 4($sp) \n", -i + 15 + parameterNumber);
            // fprintf(fp, "    move $%d, $f%d \n", -i + 15 + parameterNumber, parameter -> reference.index);
        } else if (parameterType == INT_ && parameter -> reference.type == FPReg) {
            temp = genFloattoInt(parameter -> reference);
            fprintf(fp, "    move $%d, $%d \n", -i + 15 + parameterNumber, temp.index);
        }
        parameter = (void *)parameter -> cons;
        PL = PL -> next;
        i++;
    }
    // printTab(id -> symptr);
    // Parameter * parameter = parameters;
    // int i = 0;
    // while (parameter) {

    //     printReference(parameter -> reference);
    //     // if (parameter -> reference.type == IReg) {
    //     //     fprintf(fp, "    move $a%d, $%d, \n", i, parameter -> reference.index);
    //     // } else {
    //     //     fprintf(fp, "    mov.s $a%d, $f%d, \n", i, parameter -> reference.index);
    //     // }
    //     parameter = parameter -> cons;
    //     i++;
    // }


    // free parameter list
    // Parameter * dummy;
    // while (parameters) {
    //     dummy = parameters;
    //     parameters = (void *)parameters -> cons;
    //     free(dummy);
    // }
}

Reference
genInvocation (char * name) {
    Reference reference;
    if ((strcmp(name, "fread") == 0)|| 
        (strcmp(name, "read") == 0) ||
        (strcmp(name, "READ") == 0) ||
        (strcmp(name, "FREAD") == 0)) {
        fprintf(fp, "    # read\n");
        switch (LHTYPE) {
            case INT_:
                reference = getIReg();
                fprintf(fp, "    li $v0, 5\n");
                fprintf(fp, "    syscall\n");
                fprintf(fp, "    move $%d, $v0\n", reference.index);
                break;
            case FLOAT_:
                reference = getFPReg();
                fprintf(fp, "    li $v0, 6\n");
                fprintf(fp, "    syscall\n");
                fprintf(fp, "    mov.s $f%d, $f0\n", reference.index);
                break;
            default:
                fprintf(fp, "    # A_A %d\n", LHTYPE);
                break;
        }
        // printf("read type: %d\n", reference.type);
        return reference;
    } else {

        symtab * tab = lookup(name);

        fprintf(fp, "    # function call\n");
        fprintf(fp, "    jal %s_entry\n", name);
        genRestoreParameter();
        if (tab -> symtab_u.st_func -> ret_type == INT_) {
            reference = getIReg();
            fprintf(fp, "    move $%d, $v0\n", reference.index);
        } else {
            reference = getFPReg();
            fprintf(fp, "    mov.s $f%d, $f0\n", reference.index);
        }
        return reference;
    }
}

void
genPrologue (char * name) {

    currentFunction = name;

    fprintf(fp, ".text\n");
    if (strcmp(name, "main") == 0)
        fprintf(fp, "%s:\n", name);
    else
        fprintf(fp, "%s_entry:\n", name);

    // prologue
    fprintf(fp, "    # prologue\n");        
    fprintf(fp, "    sw $ra, 0($sp)\n");
    fprintf(fp, "    sw $fp, -4($sp)\n");
    fprintf(fp, "    add $fp, $sp, -4\n");
    fprintf(fp, "    add $sp, $sp, -8\n");
    fprintf(fp, "    lw $2, %s_framesize\n", name);
    fprintf(fp, "    sub $sp, $sp, $2\n");

    int i = BASE_FRAME_SIZE;
    int f;

    // floating point
    fprintf(fp, "    # save floating point\n");
    for (f = 4; f < 20; f += 2 , i -= 4) {
        fprintf(fp, "    s.s $f%d, %d($sp)\n", f, i);   
    }

    // integer
    fprintf(fp, "    # save integers\n");
    for (f = 8; f < 16; f += 1 , i -= 4) {
        fprintf(fp, "    sw $%d, %d($sp)\n", f, i);
    }


}

void
genEpilogue (char * name) {
    // eiplogue
    fprintf(fp, "%s_end:\n", name);
    fprintf(fp, "    # eiplogue\n");        
    fprintf(fp, "%s_epilogue:\n", name);

    int i = BASE_FRAME_SIZE;
    int f;

    // floating point
    fprintf(fp, "    # save floating point\n");
    for (f = 4; f < 20; f += 2 , i -= 4) {
        fprintf(fp, "    l.s $f%d, %d($sp)\n", f, i);   
    }

    // integer
    fprintf(fp, "    # load integers\n");
    for (f = 8; f < 16; f += 1 , i -= 4) {
        fprintf(fp, "    lw $%d, %d($sp)\n", f, i);
    }

    fprintf(fp, "    lw $ra, 4($fp)\n");
    fprintf(fp, "    add $sp, $fp, 4\n");
    fprintf(fp, "    lw $fp, 0($fp)\n");

    if (!strcmp(name, "main")) {
        fprintf(fp, "    li $v0, 10\n");
        fprintf(fp, "    syscall\n");
    } else {
        fprintf(fp, "    jr $ra\n");
    }

    // misc data
    fprintf(fp, ".data\n");
    fprintf(fp, "    %s_framesize: .word %d\n", name, BASE_FRAME_SIZE + localVariableOrder * 4);


    // parameterNumber = 0;
    currentFunction = NULL;
}


Reference
genIntConst (int value) {
    Reference r = getIReg();
    fprintf(fp, "    # Int const\n");        
    fprintf(fp, "    li $%d, %d\n", r.index, value);
    return r;
}

Reference
genFloatConst (float value) {
    Reference r = getFPReg();
    fprintf(fp, "    # Float const\n");        
    fprintf(fp, "    li.s $f%d, %f\n", r.index, value);
    return r;
}

Reference
genStringConst (char * value) {
    Reference r = getStrLit();
    fprintf(fp, "    # string literal\n");        
    insertLiteralString(value, r.index);
    return r;
}

Reference
genIDConst (var_ref * ref) {
    Reference reference;
    fprintf(fp, "    # variable reference\n");        
    int offset = lookup(ref -> name) -> offset;
    int global = offset == 0;
    int argument = offset > 0;
    if (ref -> type == INT_) {
        reference = getIReg();
        if (global)
            fprintf(fp, "    lw $%d, var_%s\n", reference.index, ref -> name);
        else if (argument)
            fprintf(fp, "    move $%d, $%d\n", reference.index, lookup(ref -> name) -> offset + 15);
        else
            fprintf(fp, "    lw $%d, %d($fp)\n", reference.index, lookup(ref -> name) -> offset);

    } else if (ref -> type == FLOAT_) {
        reference = getFPReg();
        if (global)
            fprintf(fp, "    l.s $f%d, var_%s\n", reference.index, ref -> name);
        else if (argument) {
            printf("%d\n", offset);
            fprintf(fp, "    lw $%d, 4($sp)\n", lookup(ref -> name) -> offset + 15);
            fprintf(fp, "    s.s $f%d, 4($sp)\n", reference.index); //, -(lookup(ref -> name) -> offset) + 15);
            // fprintf(fp, "    mov.s $f%d, $%d\n", reference.index, -(lookup(ref -> name) -> offset) + 15);
        } else    
            fprintf(fp, "    l.s $f%d, %d($fp)\n", reference.index, lookup(ref -> name) -> offset);

    }
    return reference;
}

void 
genConvert (var_ref * a, var_ref * b) {
    fprintf(fp, "    # type coersion Int => Float\n");        
    Reference new;
    if (a -> type == FLOAT_ && b -> type == INT_) {
        b -> type = FLOAT_;
        new = genInttoFloat(b -> reference);
        b -> reference = new;
    } else if (a -> type == INT_ && b -> type == FLOAT_) {
        a -> type = FLOAT_;
        new = genInttoFloat(a -> reference);
        a -> reference = new;
    }
}

Reference
genRel (var_ref * a, var_ref * b, OP_TYPE_PROP type) {
    Reference r = getIReg();
    fprintf(fp, "    # relational operator\n");        

    if (a -> type == INT_) {
        switch (type) {
            case OPT_EQ:
                fprintf(fp, "    seq $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
            case OPT_NE:
                fprintf(fp, "    sne $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
            case OPT_GE:
                fprintf(fp, "    sge $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
            case OPT_LE:
                fprintf(fp, "    sle $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
            case OPT_GT:
                fprintf(fp, "    sgt $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
            case OPT_LT:
                fprintf(fp, "    slt $%d, $%d, $%d\n", r.index, a -> reference.index, b -> reference.index);
                break;
        }
    } else {
        int reverse = 0;
        switch (type) {
            case OPT_NE:
                reverse = 1;
            case OPT_EQ:
                fprintf(fp, "    c.eq.s $f%d, $f%d\n", a -> reference.index, b -> reference.index);
                break;
            case OPT_GT:
                reverse = 1;
            case OPT_LE:
                fprintf(fp, "    c.le.s $f%d, $f%d\n", a -> reference.index, b -> reference.index);
                break;
            case OPT_GE:
                reverse = 1;
            case OPT_LT:
                fprintf(fp, "    c.lt.s $f%d, $f%d\n", a -> reference.index, b -> reference.index);
                break;
        }
        if (reverse)
            fprintf(fp, "    bc1f label_%d\n", labelIndex);
        else
            fprintf(fp, "    bc1t label_%d\n", labelIndex);

        fprintf(fp, "    li $%d, 0\n", r.index);
        fprintf(fp, "    j label_exit_%d\n", labelIndex);
        fprintf(fp, "label_%d:\n", labelIndex);
        fprintf(fp, "    li $%d, 1\n", r.index);
        fprintf(fp, "label_exit_%d:\n", labelIndex);
        labelIndex++;
    }
    return r;
}


Reference
genOr (var_ref * a, var_ref * b) {
    Reference reference = getIReg();
    fprintf(fp, "    # logical OR\n");        
    fprintf(fp, "    or $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
    return reference;
}
Reference
genAnd (var_ref * a, var_ref * b) {
    Reference reference = getIReg();
    fprintf(fp, "    # logical AND\n");        
    fprintf(fp, "    and $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
    return reference;
}

Reference
genNeg (var_ref * a) {
    Reference reference;
    switch (a -> type) {
        case INT_:
            reference = getIReg();
            fprintf(fp, "    # Int negation\n");        
            fprintf(fp, "    neg $%d, $%d\n", reference.index, a -> reference.index);
            break;
        case FLOAT_:
            reference = getFPReg();
            fprintf(fp, "    # Float negation\n");        
            fprintf(fp, "    neg.s $f%d, $f%d\n", reference.index, a -> reference.index);
            break;
    }
    return reference;
}

Reference
genNot (var_ref * a) {
    Reference reference = getIReg();
    fprintf(fp, "    # logical NOT\n");        
    fprintf(fp, "    not $%d, $%d\n", reference.index, a -> reference.index);
    return reference;
}

Reference
genMul (var_ref * a, var_ref * b) {
    fprintf(fp, "    # multiplication\n");        
    Reference reference;
    if (a -> type == INT_) {
        reference = getIReg();
        fprintf(fp, "    mul $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
        
    } else if (a -> type == FLOAT_) {
        reference = getFPReg();
        fprintf(fp, "    mul.s $f%d, $f%d, $f%d\n", reference.index, a -> reference.index, b -> reference.index);
    }
    return reference;
}

Reference
genDiv (var_ref * a, var_ref * b) {
    fprintf(fp, "    # division\n");        
    Reference reference;
    if (a -> type == INT_) {
        reference = getIReg();
        fprintf(fp, "    div $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
        
    } else if (a -> type == FLOAT_) {
        reference = getFPReg();
        fprintf(fp, "    div.s $f%d, $f%d, $f%d\n", reference.index, a -> reference.index, b -> reference.index);
    }
    return reference;
}
Reference
genAdd (var_ref * a, var_ref * b) {
    fprintf(fp, "    # addition\n");        
    Reference reference;
    if (a -> type == INT_) {
        reference = getIReg();
        fprintf(fp, "    add $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
        
    } else if (a -> type == FLOAT_) {
        reference = getFPReg();
        fprintf(fp, "    add.s $f%d, $f%d, $f%d\n", reference.index, a -> reference.index, b -> reference.index);
    }
    return reference;
}

Reference
genSub (var_ref * a, var_ref * b) {
    fprintf(fp, "    # subtraction\n");        
    Reference reference;
    if (a -> type == INT_) {
        reference = getIReg();
        fprintf(fp, "    sub $%d, $%d, $%d\n", reference.index, a -> reference.index, b -> reference.index);
        
    } else if (a -> type == FLOAT_) {
        reference = getFPReg();
        fprintf(fp, "    sub.s $f%d, $f%d, $f%d\n", reference.index, a -> reference.index, b -> reference.index);
    }
    return reference;
}


void
genAssignment (char * leftName, Reference rightReference) {
    fprintf(fp, "    # assignment\n");        
    symtab * tab = lookup(leftName);
    int offset = tab -> offset;
    int global = offset == 0;

    Reference new;
    if (tab -> type == INT_ && rightReference.type == IReg) {
        if (global)
            fprintf(fp, "    sw $%d, var_%s\n", rightReference.index, leftName);
        else
            fprintf(fp, "    sw $%d, %d($fp)\n", rightReference.index, offset);
        tab -> reference = rightReference;
    } else if (tab -> type == INT_ && rightReference.type == FPReg) {
        new = getIReg();
        fprintf(fp, "    cvt.w.s $f%d, $f%d\n", rightReference.index, rightReference.index);
        fprintf(fp, "    mfc1 $%d, $f%d\n", new.index, rightReference.index);
        if (global)
            fprintf(fp, "    sw $%d, var_%s\n", new.index, leftName);
        else
            fprintf(fp, "    sw $%d, %d($fp)\n", new.index, offset);
        tab -> reference = new;
    } else if (tab -> type == FLOAT_ && rightReference.type == FPReg) {
        if (global)
            fprintf(fp, "    s.s $f%d, var_%s\n", rightReference.index, leftName);
        else
            fprintf(fp, "    s.s $f%d, %d($fp)\n", rightReference.index, offset);
        tab -> reference = rightReference;
    } else if (tab -> type == FLOAT_ && rightReference.type == IReg) {
        new = getFPReg();
        fprintf(fp, "    mtc1 $%d, $f%d\n", rightReference.index, new.index);
        fprintf(fp, "    cvt.s.w $f%d, $f%d\n", new.index, new.index);
        if (global)
            fprintf(fp, "    s.s $f%d, var_%s\n", new.index, leftName);
        else
            fprintf(fp, "    s.s $f%d, %d($fp)\n", new.index, offset);
        tab -> reference = new;       
        
    }
}


void
genWhileHead () {
    fprintf(fp, "    # while\n");        
    fprintf(fp, "while_%d:\n", whileIndex);
    
}

void
genWhileOpen (var_ref * test) {
    Reference reference = test -> reference;
    fprintf(fp, "    move $t0, $%d\n", reference.index);
    fprintf(fp, "    beqz $t0, while_%d_exit\n", whileIndex);
}

void 
genWhileClose () {
    fprintf(fp, "    j while_%d\n", whileIndex);
    fprintf(fp, "while_%d_exit:\n", whileIndex);
    whileIndex++;

}

void
genIfOpen (var_ref * test) {
    fprintf(fp, "    # if\n");        
    Reference reference = test -> reference;
    fprintf(fp, "    move $t0, $%d\n", reference.index);
    fprintf(fp, "    beqz $t0, if_%d_exit\n", ifIndex);
    fprintf(fp, "    # then\n");        
}

void 
genIfClose () {
    fprintf(fp, "if_%d_exit:\n", ifIndex);
    ifIndex++;

}




void
genIfElseOpen (var_ref * test) {
    fprintf(fp, "    # if else\n");        
    Reference reference = test -> reference;
    fprintf(fp, "    move $t0, $%d\n", reference.index);
    fprintf(fp, "    beqz $t0, if_else_%d_else\n", ifElseIndex);
    fprintf(fp, "    # then\n");        
}

void
genIfElseBody () {
    fprintf(fp, "    j if_else_%d_exit\n", ifElseIndex);
    fprintf(fp, "    # else\n");        
    fprintf(fp, "if_else_%d_else:\n", ifElseIndex);
}

void 
genIfElseClose () {
    fprintf(fp, "if_else_%d_exit:\n", ifElseIndex);
    ifElseIndex++;

}





void
genBlock (char * name) {
    // block
    fprintf(fp, "%s_begin:\n", name);
}

//
//
//


ST_TYPE deal_global_decl(AST_NODE *ptr){

    ST_TYPE result=ZERO_;
    if (ptr->child->sibling->type==NUL){
        functionStart();
        
        result=deal_func_decl(ptr->child);

    }
    else if (ptr->child->sibling->type==FUNCTION_DECL){
        functionStart();

        deal_decl_list(ptr->child);
        result=deal_func_decl(ptr->child->sibling);
    }
    else
        result=ERROR_;



    return result;
}

ST_TYPE deal_func_decl(AST_NODE *ptr){
    ST_TYPE result;
    ST_func *PSF;
    symtab *PST;
    param_list *PL;
    param_list *temp;
    int i=0;


    // int toGenGlobalFuncitonDeclratation = 0;

    IS_RETURN=0;
    scope++;
    
    if(ptr->type!=FUNCTION_DECL){
        printf("ERROR AST type: %d\n",ptr->type);
        exit(0);
    }
    else{
        PSF=(ST_func*)malloc(sizeof(ST_func));
        switch(ptr->semantic_value.func_decl){
            case FD_TYPE_PARAM:
            //type ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE

                func_return=ptr->child->semantic_value.type;
                if((PST=lookup(ptr->child->sibling->semantic_value.lexeme))==NULL){
                    PSF->ret_type=ptr->child->semantic_value.type;
                    PL=deal_param_list(ptr->child->sibling->sibling);
                    PSF->PL=PL;
                    while(PL!=NULL){
                        i++;
                        PL=PL->next;
                    }
                    PSF->params=i;
                    ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, FUNC_, PSF, 0, ptr->linenumber);
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }
                genPrologue(ptr -> child -> sibling -> semantic_value.lexeme);
                genBlock(ptr -> child -> sibling -> semantic_value.lexeme);
                result = deal_block(ptr -> child -> sibling -> sibling -> sibling);
                genEpilogue(ptr -> child -> sibling -> semantic_value.lexeme);
                break;
            case FD_TYPEDEF_PARAM:
            //struct_type ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE
                //TO-DO
                if ((PST=lookup(ptr->child->sibling->semantic_value.lexeme))==NULL){
                    PSF->ret_type=TYPEDEF_;
                    PL=deal_param_list(ptr->child->sibling->sibling);
                    while(PL!=NULL){
                        i++;
                        PL=PL->next;
                    }
                    PSF->PL=PL;
                    PSF->params=i;
                    ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, FUNC_, PSF, 0, ptr->linenumber);
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }
                result=deal_block(ptr->child->sibling->sibling->sibling);
                
                break;
            case FD_VOID_PARAM:
            //VOID ID MK_LPAREN param_list MK_RPAREN MK_LBRACE block MK_RBRACE
            
                IS_RETURN = 1;
                                func_return=VOID_;
                if((PST=lookup(ptr->child->semantic_value.lexeme))==NULL){
                    PSF->ret_type=VOID_;
                    PL=deal_param_list(ptr->child->sibling);
                    PSF->PL=PL;
                    while(PL!=NULL){
                        i++;
                        PL=PL->next;
                    }
                    PSF->params=i;
                    ptr->child->symptr=insert(ptr->child->semantic_value.lexeme, FUNC_, PSF, 0, ptr->linenumber);
                    
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }
                genPrologue(ptr -> child -> semantic_value.lexeme);
                genBlock(ptr -> child -> semantic_value.lexeme);
                result = deal_block(ptr -> child -> sibling -> sibling);
                genEpilogue(ptr -> child -> semantic_value.lexeme);
                break;
            case FD_TYPE_NONE:;
                int gen = 0;
            //type ID MK_LPAREN  MK_RPAREN MK_LBRACE block MK_RBRACE
                func_return=ptr->child->semantic_value.type;
                if((PST=lookup(ptr->child->sibling->semantic_value.lexeme))==NULL){
                    PSF->ret_type=ptr->child->semantic_value.type;
                    PSF->PL=NULL;
                    PSF->params=0;
                    ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, FUNC_, PSF, 0, ptr->linenumber);
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }
                genPrologue(ptr -> child -> sibling -> semantic_value.lexeme);
                genBlock(ptr -> child -> sibling -> semantic_value.lexeme);
                result=deal_block(ptr->child->sibling->sibling);
                genEpilogue(ptr -> child -> sibling -> semantic_value.lexeme);
                break;
            case FD_TYPEDEF_NONE:
            //struct_type ID MK_LPAREN  MK_RPAREN MK_LBRACE block MK_RBRACE
                //TODO
                if((PST=lookup(ptr->child->sibling->semantic_value.lexeme))==NULL){
                    PSF->ret_type=TYPEDEF_;
                    PSF->PL=NULL;
                    PSF->params=0;
                    ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, FUNC_,PSF, 0, ptr->linenumber);
                    
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s sibling on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }
                result=deal_block(ptr->child->sibling->sibling);
                break;
            case FD_VOID_NONE:;

            //VOID ID MK_LPAREN  MK_RPAREN MK_LBRACE block MK_RBRACE
                IS_RETURN = 1;
                func_return=VOID_;
                if((PST=lookup(ptr->child->semantic_value.lexeme))==NULL){
                    PSF->ret_type=VOID_;
                    PSF->PL=NULL;
                    PSF->params=0;
                    ptr->child->symptr=insert(ptr->child->semantic_value.lexeme, FUNC_, PSF, 0, ptr->linenumber);
                }
                else{
                    printf("error %d: redeclaration of symbol as function, declared previously as %s on line %d\n",ptr->linenumber,printtype(PST->type),PST->line);
                    result=ERROR_;
                }

                genPrologue(ptr -> child -> semantic_value.lexeme);
                genBlock(ptr -> child -> semantic_value.lexeme);
                result=deal_block(ptr->child->sibling);
                genEpilogue(ptr -> child -> semantic_value.lexeme);
                break;
        }
    }
    
    if (IS_RETURN==0){
        printf("error %d: missing return statement\n",ptr->linenumber);
        result=ERROR_;
    }
    delete_scope(scope);
    scope--;

    functionFinish();
    return result;
}

ST_TYPE deal_block(AST_NODE* ptr){
    AST_NODE *temp;
    ST_TYPE result=ZERO_;
    ST_TYPE generate;
    if (ptr->type==BLOCK){
        if (ptr->semantic_value.block==B_DECL_STMT){
        //decl_list stmt_list
            result=deal_decl_list(ptr->child);
            //deal_stmt_list
                temp=ptr->child->sibling->firstborn;
                while ((temp->type==STMT_LIST)){
                    generate=deal_stmt(temp->child);
                    result=(result==ERROR_)?ERROR_:generate;
                    temp=temp->sibling;
                }
        }
        else if (ptr->semantic_value.block==B_STMT){
        //stmt_list
            //deal_stmt_list
            temp=ptr->child->firstborn;
            while ((temp->type==STMT_LIST)){
                generate=deal_stmt(temp->child);
                result=(result==ERROR_)?ERROR_:generate;
                temp=temp->sibling;
            }
        }
        else if (ptr->semantic_value.block==B_DECL){
        //decl_list 
            result=deal_decl_list(ptr->child);
        }
        //null block
    }
    else{
        printf("AST type ERROR: %d\n",ptr->type);
        result=ERROR_;
    }
    return result;
    
}

ST_TYPE deal_stmt(AST_NODE * ptr){
    var_ref* temp;
    AST_NODE* p;
    ST_TYPE result=ZERO_;
    ST_TYPE generate;
    switch(ptr->semantic_value.stmt){
        case STMT_BLOCK:
        //MK_LBRACE block MK_RBRACE
            scope++;
            result=deal_block(ptr->child);
            delete_scope(scope);
            scope--;
            break;
        case STMT_WHILE:
        //WHILE MK_LPAREN test MK_RPAREN stmt
            genWhileHead();
            temp=deal_test(ptr->child);
            if ((temp->type!=INT_)&&(temp->type!=FLOAT_)){
                printf("error %d: condition not a basic type in while statement\n",ptr->linenumber);
                result=ERROR_;
            }
            genWhileOpen(temp);
            generate=deal_stmt(ptr->child->sibling);
            result=(result==ERROR_)?ERROR_:generate;
            genWhileClose();
            break;
        case STMT_FOR:
        //FOR MK_LPAREN assign_expr_list MK_SEMICOLON relop_expr_list MK_SEMICOLON assign_expr_list MK_RPAREN stmt
            if (ptr->child->child->type==NONEMPTY_ASSIGN_EXPR_LIST){
                p=ptr->child->child->firstborn;    //To nonempty_assign_expr_list
                while((p->type==NONEMPTY_ASSIGN_EXPR_LIST)){
                    temp=deal_assign_expr(p->child);
                    p=p->sibling;
                    generate=(temp->type==ERROR_)?ERROR_:ZERO_;
                    result=(result==ERROR_)?ERROR_:generate;
                    }
            }
            if (ptr->child->sibling->child->type==NONEMPTY_RELOP_EXPR_LIST){
                p=ptr->child->sibling->child->firstborn;     //To nonempty_relop_expr_list
                while(p->type==NONEMPTY_RELOP_EXPR_LIST){
                    temp=deal_relop_expr(p->child);
                    p=p->sibling;
                    generate=(temp->type==ERROR_)?ERROR_:ZERO_;
                    result=(result==ERROR_)?ERROR_:generate;
                }
            }
            if (ptr->child->sibling->sibling->child->type==NONEMPTY_ASSIGN_EXPR_LIST){
                p=ptr->child->sibling->sibling->child->firstborn;    //To nonempty_assign_expr_list
                while((p->type==NONEMPTY_ASSIGN_EXPR_LIST)){
                    temp=deal_assign_expr(p->child);
                    p=p->sibling;
                    generate=(temp->type==ERROR_)?ERROR_:ZERO_;
                    result=(result==ERROR_)?ERROR_:generate;
                }
            }
            if (ptr->child->sibling->sibling->sibling->type==STMT){
                generate=deal_stmt(ptr->child->sibling->sibling->sibling);
                result=(result==ERROR_)?ERROR_:generate;
            }
            break;
        case STMT_ASSIGN:;
        //var_ref OP_ASSIGN relop_expr MK_SEMICOLON
            var_ref * left = deal_var_ref(ptr -> child);
            LHTYPE = left -> type;
            var_ref * right = deal_relop_expr(ptr -> child -> sibling);

            
            genAssignment(left -> name, right -> reference);

            result= stmt_assign_ex(left, right, ptr->linenumber);
            break;
        case STMT_IF:
        //IF MK_LPAREN test MK_RPAREN stmt
            temp=deal_test(ptr->child);
            genIfOpen(temp);
            if ((temp->type!=INT_)&&(temp->type!=FLOAT_)){
                printf("error %d: condition not a basic type in if statement\n",ptr->linenumber);
                result=ERROR_;
            }
            generate=deal_stmt(ptr->child->sibling);
            genIfClose();
            result=(result==ERROR_)?ERROR_:generate;
            break;
        case STMT_IF_ELSE:
        //IF MK_LPAREN test MK_RPAREN stmt ELSE stmt
            temp=deal_test(ptr->child);
            genIfElseOpen(temp);
            if ((temp->type!=INT_)&&(temp->type!=FLOAT_)){
                printf("error %d: condition not a basic type in if statement\n",ptr->linenumber);
                result=ERROR_;
            }
            generate=deal_stmt(ptr->child->sibling);
            result=(result==ERROR_)?ERROR_:generate;
            genIfElseBody();
            generate=deal_stmt(ptr->child->sibling->sibling);
            genIfElseClose();
            result=(result==ERROR_)?ERROR_:generate;
            break;
        case STMT_FUNC_CALL:
        //ID MK_LPAREN relop_expr_list MK_RPAREN MK_SEMICOLON
            if ((strcmp(ptr->child->semantic_value.lexeme, "write")== 0)||      //<----maybe reduce
                (strcmp(ptr->child->semantic_value.lexeme, "WRITE")== 0)){
                    if (ptr->child->sibling->child->type==NUL){     //relop_expr_list is empty
                        printf("error %d: too few arguments to function write\n",ptr->linenumber);
                        result=ERROR_;
                    }
                    else if (ptr->child->sibling->child->firstborn!=ptr->child->sibling->child){ 
                        printf("error %d: too many arguments to function write\n",ptr->linenumber); 
                        result=ERROR_;
                    }
                    else {
                        temp=deal_relop_expr(ptr->child->sibling->child->child);
                        genWrite(temp);
                        if ((temp->type!=INT_) &&
                            (temp->type!=FLOAT_) &&
                            (temp->type!=STRING_)){
                                printf("error %d: wrong type of argument %s to write\n",ptr->linenumber,printtype(temp->type));
                                result=ERROR_;
                        }
                        else {
                            result=ZERO_;
                        }
                    }
            }
            else {
                temp=check_function(ptr->child, ptr->child->sibling);
                genParameter(ptr->child, temp);
                genInvocation(ptr -> child -> semantic_value.lexeme);

                result=(temp->type==ERROR_)?ERROR_:ZERO_;
            }
            break;
        case STMT_NONE:
        //MK_SEMICOLON
                result=ZERO_;
            break;
        case STMT_RETURN_VOID:
        //RETURN MK_SEMICOLON
        
            if ((func_return!=ERROR_)&&(func_return!=VOID_)){
                printf("error %d: returning nothing from function expecting to return %s\n",ptr->linenumber,printtype(func_return));
                result=ERROR_;
            }
            else{
                result=ZERO_;
            }
            IS_RETURN=1;
            break;
        case STMT_RETURN:
        //RETURN relop_expr MK_SEMICOLON
            LHTYPE = func_return;
            temp=deal_relop_expr(ptr->child);
            // printf("fuck %p\n", temp -> reference);
            // printReference(temp -> reference);
            if ((func_return==ERROR_)||(temp->type==ERROR_)){
                result=ERROR_;
            } else if (func_return!= temp->type){
                switch (func_return){
                    case INT_:
                    case FLOAT_:
                        if (func_return == INT_ && temp -> type == FLOAT_) {
                            genReturn(genFloattoInt(temp -> reference));
                        } else if (func_return == FLOAT_ && temp -> type == INT_) {
                            genReturn(genInttoFloat(temp -> reference));
                        }
                        if ((temp->type!=INT_)&&(temp->type!=FLOAT_)){
                            printf("error %d: incompatible return type, expects to return %s, returning %s\n",ptr->linenumber,printtype(func_return),printtype(temp->type));
                            result=ERROR_;
                        }
                        break;
                    case VOID_:
                        printf("error %d: cannot return value from a void function\n",ptr->linenumber);
                        result=ERROR_;
                        break;
                }
            }
            else{
                genReturn(temp -> reference);
                result=ZERO_;
            }
            IS_RETURN=1;
            break;
    }
    return result;
}

ST_TYPE stmt_assign_ex(var_ref *a,var_ref *b, int line){
    if((a->type==ERROR_)||(b->type==ERROR_))
        return ERROR_;
    if(a->type!=b->type){
        if((a->type==INT_||a->type==FLOAT_)&&(b->type==INT_||b->type==FLOAT_)){
            free(a);
            free(b);
            return ZERO_;
        }
        else{
            printf("error %d: incompatible assignment, %s %s to %s %s\n",line,printtype(b->type),(b->name)?(b->name):"",printtype(a->type),(a->name)?a->name:"");   
            free(a);
            free(b);
            return ERROR_;
        }
    }
    else
        switch(a->type){
            case STR_VAR_:
                if(a->var_ref_u.type_name!=b->var_ref_u.type_name){
                    printf("error %d: incomaptible assignment, struct %s to struct %s of different types\n",line,(b->name)?(b->name):"",a->name);
                    free(a);
                    free(b);
                    return ERROR_;
                }
                break;
            case ARR_:
                printf("error %d: incompatible assignment array %s to array %s\n",line,(b->name)?(b->name):"",a->name);
                free(a);
                free(b);
                return ERROR_;
                break;
            case INT_:
            case FLOAT_:
                free(a);
                free(b);
                return ZERO_;
                break;
                
            default:
                printf("CHECKER ERROR: unknown types, line %d\n",line);
                free(a);
                free(b);
                return ERROR_;
                break;
        }
}

var_ref* deal_assign_expr(AST_NODE *ptr){
        var_ref* temp;
        if (ptr->semantic_value.type==ASSIGN_){
        //ID OP_ASSIGN relop_expr
            symtab *PST;
            temp=deal_relop_expr(ptr->child->sibling);
            if ((PST=lookup(ptr->child->semantic_value.lexeme))==NULL){
                printf("error %d: undeclared variable %s\n",ptr->linenumber,ptr->child->semantic_value.lexeme);
                temp->type=ERROR_;
            }
            else if ((PST->type==ERROR_)||(temp->type==ERROR_)){
                temp->type=ERROR_;
            }
            else if (PST->type!=temp->type){
                if ((PST->type==INT_||PST->type==FLOAT_)&&(temp->type==INT_||temp->type==FLOAT_))
                    temp->type=((PST->type==FLOAT_)||(temp->type==FLOAT_))?FLOAT_:INT_;
                else{
                    printf("error %d: incompatible assignment, %s to %s %s\n",ptr->linenumber,printtype(temp->type),printtype(PST->type),PST->lexeme);
                    temp->type=ERROR_;
                }
            }
            else{
                switch (PST->type){
                    case STR_VAR_:
                        if(PST->symtab_u.type_name!=temp->var_ref_u.type_name){
                            printf("error %d: incompatible assignment, struct %s to struct %s of different types\n",ptr->linenumber,(temp->name)?(temp->name):"",ptr->child->semantic_value.lexeme);
                            temp->type=ERROR_;
                        }
                        break;
                    case ARR_:
                        printf("error %d: incompatible assignment array %s to array %s\n",ptr->linenumber,(temp->name)?(temp->name):"",ptr->child->semantic_value.lexeme);
                        temp->type=ERROR_;
                        break;
                    case INT_:
                    case FLOAT_:
                        break;
                }
            }
            if(temp->type!=ERROR_)ptr->child->symptr=PST;
            return temp;
        }
        else{
        //relop_expr
            return deal_relop_expr(ptr->child);
        }
}

var_ref* deal_test(AST_NODE * ptr){
        ptr=ptr->child;   //To assign_expr
        return deal_assign_expr(ptr);
}



param_list* deal_param_list(AST_NODE *ptr){
    param_list *PL;
    param_list *temp;
    ptr=ptr->firstborn;
    PL=build_param(ptr->child);
    // parameterNumber = 1;
    temp=PL;
    ptr=ptr->sibling;
    while(ptr->type==PARAM_LIST){
        argumentIndex++;
        temp->next=build_param(ptr->child);
        ptr=ptr->sibling;
        temp=temp->next;

        // parameterNumber
        // parameterNumber++;

    }
    temp->next=NULL;

    argumentIndex = 1;
    return PL;
}

param_list* build_param(AST_NODE *ptr){
    param* p;
    param_list *PL;
    var_ref* dim_expr;
    AST_NODE* temp;
    Type_arr * arr_info;
    int i=0;
    if(ptr->type!=PARAM){
        printf("ERROR\n");
        exit(1);
    }
    else{
        p = (param*) malloc (sizeof(param));
        PL = (param_list*)malloc (sizeof(param_list));
        switch(ptr->semantic_value.param){
            case P_TYPE_NONE:
            //type ID
                p->type=ptr->child->semantic_value.type;
                ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, p->type, NULL, 0, ptr->linenumber);
                ptr->child->sibling->symptr -> offset = argumentIndex;
                break;
            case P_TYPEDEF_NONE:
            //struct_type ID
                p->type=TYPEDEF_;
                //TO-DO
                break;
            case P_TYPE_ARR:
            //type ID dim_fn
                p->type=ARR_;
                p->arrtype=ptr->child->semantic_value.type;
                temp=ptr->child->sibling->sibling;
                if(temp->type==DIM_FN){
                    i++;
                    if (temp->child->child->type==EXPR){  //EXPR_NULL is expr
                        dim_expr=deal_expr(temp->child->child);
                        if (dim_expr->type!=INT_){
                            printf("error %d: size of array \' %s \' has non-integer type\n", ptr->linenumber, ptr->child->sibling->semantic_value.lexeme);
                            global_error=1;
                        }
                    }
                    temp=temp->child->sibling; //to dimfn1 
                    while(temp->child->type==EXPR){ //check dimfn1
                        i++;
                        dim_expr=deal_expr(temp->child);
                        if (dim_expr->type!=INT_){
                             printf("error %d: size of array \' %s \' has non-integer type\n", ptr->linenumber, ptr->child->sibling->semantic_value.lexeme);
                             global_error=1;
                        }
                        temp=temp->child->sibling;
                    }
                }
                p->dim=i;
                arr_info=(Type_arr*)malloc(sizeof(Type_arr));
                arr_info->dim=i;
                arr_info->arrtype=p->arrtype;
                ptr->child->sibling->symptr=insert(ptr->child->sibling->semantic_value.lexeme, ARR_, arr_info, 0, ptr->linenumber);
                break;
            case P_TYPEDEF_ARR:
            //struct_type ID dim_fn
                p->type=ARR_;
                p->arrtype=TYPEDEF_;
                temp=ptr->child->sibling->sibling;
                if(temp->type==DIM_FN){
                    i++;
                    temp=temp->child->sibling;
                    while(temp->child->type!=EXPR){ //check dimfn1
                        i++;
                        temp=temp->child->sibling;
                    }
                }
                p->dim=i;
                break;
            default:
                printf("ERROR\n");
                return 0;
        }
        PL->PPAR=p;
        return PL;
    }
}

ST_TYPE deal_decl_list(AST_NODE *ptr){

    ST_TYPE result=ZERO_;
    ST_TYPE generate;
    ptr=ptr->firstborn;
    if (ptr->type!=DECL_LIST){
        printf("ERROR AST type: %d, should be DECL_LIST\n",ptr->type);
        result=ERROR_;
        exit(0);
    }
    while ((ptr->type!=NUL)){
        if (ptr->child->child->type==TYPE_DECL){
            generate=deal_type_decl(ptr->child->child);
            result=(result==ERROR_)?ERROR_:generate;
        }
        else if (ptr->child->child->type==VAR_DECL){
            generate=deal_var_decl(ptr->child->child);
            result=(result==ERROR_)?ERROR_:generate;
        }
        ptr=ptr->sibling;
    }
    
    return result;
}


ST_TYPE deal_type_decl(AST_NODE *ptr){
    ST_TYPE result=ZERO_;
    symtab *PST;
    AST_NODE *id_list;
    Type_arr *arr_info;
    
    if(ptr->semantic_value.type_decl==TD_TYPE_ID){
    //TYPEDEF type id_list MK_SEMICOLON
        id_list=ptr->child->sibling->firstborn;
        do{
            if ((PST=lookup(id_list->child->semantic_value.lexeme))!=NULL){
                if (PST->scope>=scope){
                    printf("error %d: variable or type redeclared, %s, declared earlier at line %d\n",ptr->linenumber,id_list->child->semantic_value.lexeme,PST->line);
                    result=ERROR_;
                }
            }
            else{
                if (id_list->semantic_value.type==ARR_){
                    arr_info=deal_dim_decl(id_list->child->sibling);   //to dim_decl  :ID dim_decl
                    arr_info->arrtype=ptr->child->semantic_value.type;
                    id_list->child->symptr=insert(id_list->child->semantic_value.lexeme, TYPEDEF_, arr_info, TYPEDEF_ARR, ptr->linenumber);
                }
                else if (ptr->child->semantic_value.type==INT_)
                    id_list->child->symptr=insert(id_list->child->semantic_value.lexeme, TYPEDEF_, NULL, TYPEDEF_INT, ptr->linenumber);
                else
                    id_list->child->symptr=insert(id_list->child->semantic_value.lexeme, TYPEDEF_ ,NULL, TYPEDEF_FLT, ptr->linenumber);
            }   
            id_list=id_list->sibling;   
        }while(id_list->type!=NUL);
    }
    else if(ptr->semantic_value.type_decl==TD_VOID_ID){
    //TYPEDEF VOID id_list MK_SEMICOLON
        result=ZERO_;
    }
    else if (ptr->semantic_value.type_decl==TD_TYPEDEF_ID){
    //TYPEDEF struct_type id_list MK_SEMICOLON
        printf("NOT implement\n");
        result=ZERO_;
    }
    else{
    //struct_type MK_SEMICOLON
        printf("error %d: struct declaration with no variables\n",ptr->linenumber);
        result=ERROR_;
    }
    
    return result;
}

ST_TYPE deal_var_decl(AST_NODE *ptr){
    AST_NODE * temp;
    symtab * PST;
    Type_arr * arr_info;
    var_ref* vt;
    ST_TYPE result=ZERO_;
    ST_TYPE generate;

    if(ptr->type!=VAR_DECL){
        printf("AST type ERROR: not VAR_DECL\n");
        exit(1);
    }
    if(ptr->semantic_value.var_decl==VD_TYPE){
        // type init_id_list MK_SEMICOLON
        temp=ptr->child->sibling->firstborn;
        while (temp->type==INIT_ID_LIST){
            switch(temp->child->semantic_value.type){     //To init_id
                case STR_VAR_:
                //ID
                    PST=lookup(temp->child->child->semantic_value.lexeme);
                    if ((PST)&&(PST->scope>=scope)){
                        printf("error %d: redeclaration of variable %s declared previously at line %d\n",ptr->linenumber,temp->child->child->semantic_value.lexeme,PST->line);
                        result=ERROR_;
                    }
                    else {
                        temp->child->child->symptr=insert(temp->child->child->semantic_value.lexeme,ptr->child->semantic_value.type,NULL,0, ptr->linenumber);
                        if (scope == 0) { // global
                            genGlobalVariableDeclaration(temp -> child -> child -> semantic_value.lexeme, ptr->child->semantic_value.type); 
                        } else { // local
                            genLocalVariableDeclaration(temp -> child -> child -> semantic_value.lexeme, ptr->child->semantic_value.type); 
                        }
                    }
                    break;
                case ARR_:
                //ID dim_decl
                    PST=lookup(temp->child->child->semantic_value.lexeme);
                    if ((PST)&&(PST->scope>=scope)){
                        printf("error %d: redeclaration of variable %s declared previously at line %d\n",ptr->linenumber,temp->child->child->semantic_value.lexeme,PST->line);
                        result=ERROR_;
                    }
                    else{
                        arr_info=deal_dim_decl(temp->child->child->sibling);
                        arr_info->arrtype=ptr->child->semantic_value.type;
                        temp->child->child->symptr=insert(temp->child->child->semantic_value.lexeme, ARR_, arr_info, 0, ptr->linenumber);
                    }
                    break;
                case ASSIGN_:
                //ID OP_ASSIGN relop_expr
                    //TODO
                    PST=lookup(temp->child->child->semantic_value.lexeme);
                    if ((PST)&&(PST->scope>=scope)){
                        printf("error %d: redeclaration of variable %s declared previously at line %d\n",ptr->linenumber,temp->child->child->semantic_value.lexeme,PST->line);
                        result=ERROR_;
                    }
                    else{
                        vt=deal_relop_expr(temp->child->child->sibling);
                        if ((vt->type!=INT_)&&(vt->type!=FLOAT_)){
                            printf("error %d: initialization of variable %s with expression of type %s\n",ptr->linenumber,temp->child->child->semantic_value.lexeme,printtype(vt->type));
                            result=ERROR_;
                        }
                        else{
                            temp->child->child->symptr=insert(temp->child->child->semantic_value.lexeme,ptr->child->semantic_value.type,NULL,0, ptr->linenumber);
                            if (scope == 0) { // global
                                genGlobalVariableDeclaration(temp -> child -> child -> semantic_value.lexeme, ptr->child->semantic_value.type); 
                            } else {
                                genLocalVariableDeclaration(temp -> child -> child -> semantic_value.lexeme, ptr->child->semantic_value.type); 
                                genLocalVariableInitialization(temp -> child -> child -> semantic_value.lexeme, ptr->child->semantic_value.type, vt); 
                            }
                        }
                    }
                    break;
            }
            temp=temp->sibling;
        }
    }
    else if(ptr->semantic_value.var_decl==VD_TYPEDEF){
        // struct_type id_list MK_SEMICOLON
    }
    else if(ptr->semantic_value.var_decl==VD_ID){
    //ID id_list MK_SEMICOLON
        if((PST=lookup(ptr->child->semantic_value.lexeme))==NULL){
            printf("error %d: undeclared type %s\n",ptr->linenumber, ptr->child->semantic_value.lexeme);
            result=ERROR_;
        
        }
        else if(PST->type!=TYPEDEF_){
            printf("error %d: %s not a type\n",ptr->linenumber, ptr->child->semantic_value.lexeme);
            result=ERROR_;
        }
        else{
            switch(PST->type_when_def){
                case TYPEDEF_INT:
                        temp=ptr->child->sibling->firstborn;
                        while (temp->type==ID_LIST){
                            if (temp->semantic_value.type==STR_VAR_){       //ID, at id_list
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, INT_, NULL, 0, ptr->linenumber);
                            }
                            else{                                                               //ID dim_decl, at id_list
                                arr_info=deal_dim_decl(temp->child->sibling);   
                                arr_info->arrtype=INT_;
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, ARR_, arr_info, 0, ptr->linenumber);
                            }
                            temp=temp->sibling;
                        }
                    break;
                case TYPEDEF_FLT:
                        temp=ptr->child->sibling->firstborn;
                        while (temp->type==ID_LIST){
                            if (temp->semantic_value.type==STR_VAR_){       //ID, at id_list
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, FLOAT_, NULL, 0, ptr->linenumber);
                            }
                            else{                                                       //ID dim_decl, at id_list
                                arr_info=deal_dim_decl(temp->child->sibling);
                                arr_info->arrtype=FLOAT_;
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, ARR_, arr_info, 0 ,ptr->linenumber);
                            }
                            temp=temp->sibling;
                        }
                    break;
                case TYPEDEF_ARR:
                        temp=ptr->child->sibling->firstborn;
                        while (temp->type==ID_LIST){
                            if (temp->semantic_value.type==STR_VAR_){   //ID, at id_list
                                arr_info = (Type_arr*)malloc(sizeof(Type_arr));
                                arr_info->dim=PST->symtab_u.st_arr->dim;
                                arr_info->arrtype= PST->symtab_u.st_arr->arrtype;
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, ARR_, arr_info, 0 , ptr->linenumber);
                            }
                            else {                                                      //ID dim_decl, at id_list
                                arr_info=deal_dim_decl(ptr->child->sibling->child->sibling);
                                arr_info->dim+=PST->symtab_u.st_arr->dim;
                                arr_info->arrtype= PST->symtab_u.st_arr->arrtype;
                                temp->child->symptr=insert(temp->child->semantic_value.lexeme, ARR_, arr_info, 0 , ptr->linenumber);
                            }
                            temp=temp->sibling;
                        }
                    break;
                case TYPEDEF_STR:
                    //
                    break;
            }
        }
    }
    
    return result;
}


var_ref* deal_relop_expr(AST_NODE* ptr){
    var_ref* op1;
    var_ref* op2;
    if (ptr->semantic_value.op_type==OPT_NONE){
    //relop_term
        
        
        var_ref * t = deal_relop_term(ptr->child);
        // printf("%s form %p\n", currentFunction, t -> reference);
        // printReference(t -> reference);
        return t;
    }
    else {
    //relop_expr OP_OR relop_term
        op1=deal_relop_expr(ptr->sibling);
        op2=deal_relop_term(ptr->child);
        if(op1->type==ERROR_||op2->type==ERROR_)
            op1->type=ERROR_;
        else if (op1->type!=INT_||op2->type!=INT_){
            if ((op1->type==INT_||op1->type==FLOAT_)&&(op2->type==INT_||op2->type==FLOAT_)){
                printf("warning %d: operator || applied to non integer type\n",ptr->linenumber);
                op1->type=INT_;
            }
            else{
                printf("error %d: operator || applied to non basic type\n",ptr->linenumber);
                op1->type=ERROR_;
            }
        }
        else{
            op1->type= INT_;
        }
        op1 -> reference = genOr(op1, op2);
        return op1;
    }
}

var_ref* deal_relop_term(AST_NODE* ptr){
    var_ref* op1;
    var_ref* op2;
    if (ptr->semantic_value.op_type==OPT_NONE){
    //relop_factor
        return deal_relop_factor(ptr->child);
    }
    else {
    //relop_term OP_AND relop_factor
        op1=deal_relop_term(ptr->sibling);
        op2=deal_relop_factor(ptr->child);

        if (op1->type==ERROR_||op2->type==ERROR_)
            op1->type= ERROR_;
        else if (op1->type!=INT_||op2->type!=INT_){
            if ((op1->type==INT_||op2->type==FLOAT_)&&(op2->type==INT_||op2->type==FLOAT_)){
                printf("warning %d: operator && applied to non integer type\n",ptr->linenumber);
                op1->type= INT_;
            }
            else{
                printf("error %d: operator || applied to non basic type\n",ptr->linenumber);
                op1->type= ERROR_;
            }
        }
        else{
            op1->type= INT_;
        }
        op1 -> reference = genAnd(op1, op2);
        return op1;
    }

}
            
var_ref* deal_relop_factor(AST_NODE* ptr){
    var_ref* op1;
    var_ref* op2;
    if (ptr->semantic_value.op_type==OPT_NONE){
    //expr
        return deal_expr(ptr->child);
    }
    else {
    //expr rel_op expr
        op1=deal_expr(ptr->child);
        op2=deal_expr(ptr->child->sibling->sibling);

        if ((op1->type==ERROR_)||(op2->type==ERROR_))
            op1->type=ERROR_;
        else if((((op1->type!=INT_)&&op1->type!=FLOAT_))||((op2->type!=INT_)&&(op2->type!=FLOAT_))){
            printf("error %d: relational operators applied to expression of non basic type\n",ptr->linenumber);
            op1->type= ERROR_;
        }
        else{
            genConvert(op1, op2);
        }
        op1 -> reference = genRel(op1, op2, ptr -> child -> sibling -> semantic_value.op_type);
        return op1;
    }
}

var_ref* deal_expr(AST_NODE* ptr){
    var_ref* op1;
    var_ref* op2;
    if (ptr->semantic_value.op_type==OPT_NONE){
    //term
        return deal_term(ptr->child);
    }
    else {
    //expr add_op term
        op1=deal_expr(ptr->child);
        op2=deal_term(ptr->child->sibling->sibling);
        if ((op1->type==ERROR_)||(op2->type==ERROR_))
            op1->type= ERROR_;
        else if ((op1->type!=INT_)&&(op1->type!=FLOAT_)){
            printf("error %d: operator %s applied to non basic expr\n",ptr->linenumber,(ptr->child->sibling->semantic_value.op_type==OPT_ADD)?"+":"-");
            op1->type= ERROR_;
        }
        else if((op2->type!=INT_)&&(op2->type!=FLOAT_)){
            printf("error %d: operator %s applied to non basic expr\n",ptr->linenumber,(ptr->child->sibling->semantic_value.op_type==OPT_ADD)?"+":"-");
            op1->type= ERROR_;
        }
        else{
            genConvert(op1, op2);
        }
        if (ptr -> child -> sibling -> semantic_value.op_type == OPT_ADD)
            op1 -> reference = genAdd(op1, op2);
        else if (ptr -> child -> sibling -> semantic_value.op_type == OPT_SUB)
            op1 -> reference = genSub(op1, op2);
        return op1;
    }
}

var_ref* deal_term(AST_NODE* ptr){
    var_ref* op1;
    var_ref* op2;
    if (ptr->semantic_value.op_type==OPT_NONE){
    //factor
        return deal_factor(ptr->child);
    }
    else {
    //term mul_op factor
        op1=deal_term(ptr->child);
        op2=deal_factor(ptr->child->sibling->sibling);
        if (op1->type==ERROR_||op2->type==ERROR_)
            op1->type= ERROR_;
        else if((op1->type!=INT_)&&(op1->type!=FLOAT_)){
            printf("error %d: operator %s applied to non basic term (%s)\n",ptr->linenumber,(ptr->child->sibling->semantic_value.op_type==OPT_MUL)?"*":"/", op1->name);
            op1->type= ERROR_;
        }
        else if ((op2->type!=INT_)&&(op2->type!=FLOAT_)){
            printf("error %d: operator %s applied to non basic term (%s)\n",ptr->linenumber,(ptr->child->sibling->semantic_value.op_type==OPT_MUL)?"*":"/", op2->name);
            op1->type= ERROR_;
        }
        else{
            genConvert(op1, op2);
        }

        if (ptr -> child -> sibling -> semantic_value.op_type == OPT_MUL)
            op1 -> reference = genMul(op1, op2);
        if (ptr -> child -> sibling -> semantic_value.op_type == OPT_DIV)
            op1 -> reference = genDiv(op1, op2);
        return op1;
    }
}

var_ref* deal_factor(AST_NODE* ptr){
    var_ref* op;
    switch (ptr->semantic_value.factor){
        case F_REL:
        //MK_LPAREN relop_expr MK_RPAREN
            op=deal_relop_expr(ptr->child);
            break;
        case  F_REL_MINUS:
        //OP_MINUS MK_LPAREN relop_expr MK_RPAREN
            op=deal_relop_expr(ptr->child);
            if ((op->type!=INT_)&&(op->type!=FLOAT_)){
                printf("error %d: operator Unary Minus applied to expression of non basic type\n",ptr->linenumber);
                op->type=ERROR_;
            }
            op -> reference = genNeg(op);
            break;
        case F_REL_NOT:
        //OP_NOT MK_LPAREN relop_expr MK_RPAREN
            op=deal_relop_expr(ptr->child);
            if (op->type!=INT_){
                if (op->type!=FLOAT_){
                    printf("error %d: operator ! applied to non scalar expression\n",ptr->linenumber);
                    op->type= ERROR_;
                }
                else{
                    printf("warning %d: operator ! applied to a float expression\n",ptr->linenumber);
                    op->type= INT_;
                }
            }
            op -> reference = genNot(op);

            break;
        case F_CONST:
        //CONST
            op=(var_ref*)malloc(sizeof(var_ref));
            op->name=NULL;
            switch (ptr->child->semantic_value.const1->const_type){
                case INTEGERC:
                    // printf("INT %d\n", ptr -> child -> semantic_value.const1 -> const_u.intval);
                    op -> type = INT_;
                    if (scope == GLOBAL) {
                        tempInt = ptr -> child -> semantic_value.const1 -> const_u.intval;
                    } else {
                        op -> reference = genIntConst(ptr -> child -> semantic_value.const1 -> const_u.intval);
                    }
                    break;
                case FLOATC:
                    op -> type = FLOAT_;
                    // printf("FLOAT %f\n", ptr -> child -> semantic_value.const1 -> const_u.fval);

                    if (scope == GLOBAL) {
                        tempFloat = ptr -> child -> semantic_value.const1 -> const_u.fval;
                    } else {
                        op -> reference = genFloatConst(ptr -> child -> semantic_value.const1 -> const_u.fval);
                    }

                    break;
                case STRINGC:
                    op -> type= STRING_;
                    op -> reference = genStringConst(ptr -> child -> semantic_value.const1 -> const_u.sc);
                    break;
                default:
                    op->type= ERROR_;
            }
            break;
        case F_CONST_MINUS:
        //OP_MINUS CONST
            op=(var_ref*)malloc(sizeof(var_ref));
            op->name=NULL;
            if ((ptr->child->semantic_value.const1->const_type!=INTEGERC)&&(ptr->child->semantic_value.const1->const_type!=FLOATC)){
                printf("error %d: operator Unary Minus applied to non Basic constant\n",ptr->linenumber);
                op->type= ERROR_;
            }
            else {
                op -> type = (ptr->child->semantic_value.const1->const_type==INTEGERC)?INT_:FLOAT_; 
                // printf("- %f\n", tempFloat);
                switch (op -> type){
                    case INT_:
                        if (scope == GLOBAL) {
                            tempInt = -(ptr -> child -> semantic_value.const1 -> const_u.intval);
                        } else {
                            op -> reference = genIntConst(ptr -> child -> semantic_value.const1 -> const_u.intval);
                            op -> reference = genNeg(op);
                        }
                        break;
                    case FLOAT_:
                        if (scope == GLOBAL) {
                            tempFloat = -(ptr -> child -> semantic_value.const1 -> const_u.fval);
                        } else {
                            op -> reference = genFloatConst(ptr -> child -> semantic_value.const1 -> const_u.fval);
                            op -> reference = genNeg(op);
                        }

                        break;
                    default:
                        op->type= ERROR_;
                }
            }
            break;
        case F_CONST_NOT:
        //OP_NOT CONST
            op=(var_ref*)malloc(sizeof(var_ref));
            op->name=NULL;
            if (ptr->child->semantic_value.const1->const_type!=INTEGERC){
                if (ptr->child->semantic_value.const1->const_type!=FLOATC){
                    printf("error %d: operator ! applied to non scalar constant\n",ptr->linenumber);
                    op->type= ERROR_;
                }
                else{
                    printf("warning %d: operator ! applied to a float constant\n",ptr->linenumber);
                    op->type= INT_;

                    op -> reference = genFloatConst(ptr -> child -> semantic_value.const1 -> const_u.fval);
                    op -> reference = genNot(op);
                }
            }
            else{
                op->type= INT_;
                op -> reference = genIntConst(ptr -> child -> semantic_value.const1 -> const_u.intval);
                op -> reference = genNot(op);
            }
            break;
        case F_ID:
        //ID MK_LPAREN relop_expr_list MK_RPAREN
            op = check_function(ptr->child,ptr->child->sibling);
            genParameter(ptr->child, op);
            op -> reference = genInvocation(ptr -> child -> semantic_value.lexeme);
            op -> type = (op -> reference.type == IReg) ? INT_ : FLOAT_;
            break;
        case F_ID_MINUS:
        //OP_MINUS ID MK_LPAREN relop_expr_list MK_RPAREN
            op=check_function(ptr->child, ptr->child->sibling);
            if ((op->type!=ERROR_)&&((op->type!=INT_)||(op->type!=FLOAT_))){
                printf("error %d: unary minus applied to non scalar expression\n",ptr->linenumber);
                op->type=ERROR_;
            }
            genParameter(ptr->child, op);
            op -> reference = genInvocation(ptr -> child -> semantic_value.lexeme);
            op -> reference = genNeg(op);
            break;
        case F_ID_NOT:
        //OP_NOT ID MK_LPAREN relop_expr_list MK_RPAREN
            op=check_function(ptr->child, ptr->child->sibling);
            if((op->type!=ERROR_)&&((op->type!=INT_)||(op->type!=FLOAT_))){
                printf("error %d: operator ! applied to non integer expression\n",ptr->linenumber);
                op->type=ERROR_;
            }
            genParameter(ptr->child, op);
            op -> reference = genInvocation(ptr -> child -> semantic_value.lexeme);
            op -> reference = genNot(op);
            break;
        case F_VAR:
        //var_ref
            op=deal_var_ref(ptr->child);
            op -> reference = genIDConst(op);

            break;
        case F_VAR_MINUS:
        //OP_MINUS var_ref
            op=deal_var_ref(ptr->child);
            if ((op->type!=INT_)&&(op->type!=FLOAT_)){
                printf("error %d: operator Unary Minus applied to non Basic type %s\n",ptr->linenumber,op->name);
                op->type= ERROR_;
            }
            op -> reference = genIDConst(op);
            op -> reference = genNeg(op);
            break;
        case F_VAR_NOT:
        //OP_NOT var_ref
            op=deal_var_ref(ptr->child);
            if (op->type!=INT_){
                if (op->type!=FLOAT_){
                    printf("error %d: operator ! applied to non scalar type%s\n",ptr->linenumber,op->name);
                    op->type= ERROR_;
                }
                else{
                    printf("warning %d: operator ! applied to a float constant\n",ptr->linenumber);
                    op->type= INT_;
                }
            }
            op -> reference = genIDConst(op);
            op -> reference = genNot(op);
            break;
    }
    return op;
}

var_ref* deal_var_ref(AST_NODE * ptr){

    var_ref * temp;
    symtab *STP;
    var_ref * op;
    switch(ptr->semantic_value.type){
        case STR_:
        //ID
            temp=(var_ref*)malloc(sizeof(var_ref));
            if (((STP=lookup(ptr->child->semantic_value.lexeme))==NULL)||(STP->scope>scope)){
                printf("error %d: undeclared variable %s\n",ptr->linenumber,ptr->child->semantic_value.lexeme);
                temp->type= ERROR_;
            }
            else if (STP->type==FUNC_||STP->type==TYPEDEF_){
                printf("error %d: referenced symbol %s is not a variable \n",ptr->linenumber,ptr->child->semantic_value.lexeme);
                temp->type= ERROR_;
            }
            else if (STP->type==ERROR_){
                temp->type= ERROR_;
            }
            else {

                
                temp->type=STP->type;
                temp->name=ptr->child->semantic_value.lexeme;

                // symtab * tab = lookup(temp -> name);
                // printTab(tab);


                if (temp->type==STR_VAR_)
                    temp->var_ref_u.type_name=STP->symtab_u.type_name;
                    
                if (temp->type==ARR_){
                    Type_arr *PTA;
                    PTA=(Type_arr*)malloc(sizeof(Type_arr));
                    PTA->dim=STP->symtab_u.st_arr->dim;
                    PTA->arrtype=STP->symtab_u.st_arr->arrtype;
                    PTA->type_name=STP->symtab_u.st_arr->type_name;
                    temp->var_ref_u.arr_info=PTA;
                }
                ptr->child->symptr=STP;
            }
            break;
        case ARR_:
        //var_ref dim
            temp =deal_var_ref(ptr->child);
            if (temp->type==ERROR_)
                return temp;
            else{
                if (temp->type!=ARR_){
                    STP=lookup(temp->name);
                    
                    if ((STP)&&(STP->type==ARR_))
                        printf("error %d: array %s has only %d dimension(s)\n",ptr->linenumber,temp->name,STP->symtab_u.st_arr->dim);
                    else
                        printf("error %d: variable not an array %s\n", ptr->linenumber,temp->name);
                    temp->type=ERROR_;
                }
                else{
                    op=deal_expr(ptr->child->sibling->child);
                    if ((op->type!=ERROR_)&&(op->type!=INT_)){
                    printf("error %d: dimension is not an integer in array variable %s\n",ptr->linenumber,temp->name);
                    temp->type=ERROR_;
                    }
                    int i;
                    i=--temp->var_ref_u.arr_info->dim;
                    
                    /*we have reached the variable in the array*/
                    if(i==0){
                        temp->type=temp->var_ref_u.arr_info->arrtype;
                        if(temp->type==STR_){
                            temp->type=STR_VAR_;
                            temp->var_ref_u.type_name=temp->var_ref_u.arr_info->type_name;
                        }
                    }
                }
                return temp;
            }
            break;
        case TYPEDEF_:
        //var_ref struct_tail
            temp= deal_var_ref(ptr->child);
            break;
    }
    return temp;
}
    



var_ref* check_function(AST_NODE *id, AST_NODE* list){         //list is RELOP_EXPR_LIST
    symtab *PST;
    int i=0;
    var_ref* temp=ZERO_;
    AST_NODE *temp1;
    AST_NODE *temp2;
    temp = (var_ref*)malloc(sizeof(var_ref));
    if (list->child->type==NONEMPTY_RELOP_EXPR_LIST){   //param list not NULL
        temp1=list->child->firstborn;    //to NONEMPTY_RELOP_EXPR_LIST
        temp2=list->child->firstborn;    //to NONEMPTY_RELOP_EXPR_LIST
        while (temp1->type==NONEMPTY_RELOP_EXPR_LIST){
            i++;
            temp1=temp1->sibling;
        }
        if ((PST=lookup(id->semantic_value.lexeme))==NULL){
            printf("error %d: undefined function %s\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else if(PST->type!=FUNC_){
            printf("error %d: %s is not a function\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else if(i>PST->symtab_u.st_func->params){
            printf("error %d: too many arguments to function %s\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else if(i<PST->symtab_u.st_func->params){
            printf("error %d: too few arguments to function %s\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else{
            ST_func *x;
            param_list *y;
            x=PST->symtab_u.st_func;
            y=x->PL;
            i=0;
            var_ref* generate;
            temp->type=PST->symtab_u.st_func->ret_type;
            id->symptr = PST;
            
            while(y){
                generate=deal_relop_expr(temp2->child);
                if((y->PPAR==NULL)||(generate->type==ERROR_)){
                    y=y->next;
                    temp2=temp2->sibling;
                    i++;
                    temp->type= ERROR_;
                    continue;
                }

                Parameter * parameter = malloc(sizeof(Parameter));
                parameter -> reference = generate -> reference;
                parameter -> cons = (void *)temp -> parameter;
                temp -> parameter = parameter;
                // printf("added\n");
                
                switch(y->PPAR->type){
                    case INT_:
                    case FLOAT_:
                        if ((generate->type!=INT_)&&(generate->type!=FLOAT_)){
                            printf("error %d: function arg %d, expects scalar, passed type %s\n",list->linenumber,i,printtype(generate->type)); 
                            temp->type=ERROR_;
                        }
                        break;
                    case ARR_:
                        if ((generate->type==INT_)||(generate->type==FLOAT_)){
                            printf("error %d: function arg %d, scalar  passed, expects a %dD array\n",list->linenumber,i,PST->symtab_u.st_arr->dim);
                            temp->type=ERROR_;
                        }
                        else if(generate->type==ARR_){
                            ////
                            if ((y->PPAR->arrtype!=generate->var_ref_u.arr_info->arrtype)||(y->PPAR->dim!=generate->var_ref_u.arr_info->dim)){
                                printf("warning %d: passing arg %d of %s from incompatible pointer type\n",list->linenumber,i,id->semantic_value.lexeme);
                            }
                        }
                        else{
                            ////
                        }
                }
                i++;
                y=y->next;
                temp2=temp2->sibling;
            }
        }
    }
    else { //the input param is null 
        if ((PST=lookup(id->semantic_value.lexeme))==NULL){
            printf("error %d: undefined function %s\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else if(PST->type!=FUNC_){
            printf("error %d: %s is not a function\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else if(i<PST->symtab_u.st_func->params){
            printf("error %d: too few arguments to function %s\n",list->linenumber,id->semantic_value.lexeme);
            temp->type= ERROR_;
        }
        else{
            temp->type=PST->symtab_u.st_func->ret_type;
        }
        id->symptr = PST;
    }
    return temp;
}
            
        


Type_arr* deal_dim_decl(AST_NODE* ptr){
    Type_arr * arrinfo;
    AST_NODE *temp;
    int dim_number;
    ptr=ptr->firstborn;
    arrinfo=(Type_arr*)malloc(sizeof(Type_arr));
    arrinfo->dim=0;
    temp=ptr;
    while(temp->type==DIM_DECL){
        dim_number=deal_cexpr(temp->child);
        if (dim_number <= 0) {
            printf("error %d : Invalid dimension declaration %d \n",ptr->linenumber, dim_number); } 
        arrinfo->dim_limit[arrinfo->dim]=dim_number;
        arrinfo->dim=arrinfo->dim+1;
        temp=temp->sibling;
    }
    return arrinfo;
}

int deal_cexpr(AST_NODE* ptr){               //that's the special case doesn't need the firstborn
    if (ptr->semantic_value.op_type==OPT_ADD)
        return deal_cexpr(ptr->sibling)+deal_mcexpr(ptr->child);
    else if(ptr->semantic_value.op_type==OPT_SUB)
        return deal_cexpr(ptr->sibling)-deal_mcexpr(ptr->child);
    else
        return deal_mcexpr(ptr->child);
}

int deal_mcexpr(AST_NODE* ptr){             //that's the special case doesn't need the firstborn
    int oprand1,oprand2;
    if (ptr->semantic_value.op_type==OPT_MUL)
        return deal_mcexpr(ptr->sibling)*deal_cfactor(ptr->child);
    else if(ptr->semantic_value.op_type==OPT_DIV){
        oprand2=deal_cfactor(ptr->child);
        if (oprand2==0){
            printf("ERROR %d :divide by ZERO\n", ptr->linenumber);
            global_error=1;
            return 0;
        }
        oprand1=deal_mcexpr(ptr->sibling);
        if (oprand1 % oprand2 != 0){
            printf("ERROR %d: non integer expression in array dimension\n", ptr->linenumber);
            global_error=1;
        }
        return oprand1 / oprand2;
    }
    else
        return deal_cfactor(ptr->child);
}   

int deal_cfactor(AST_NODE*ptr){
    if (ptr->child->type==CONST_value){
        if(ptr->child->semantic_value.const1->const_type!=INTEGERC){
            printf("error %d: non integer expression in array dimension\n",ptr->linenumber);
            return 0; //DOTO
        }
        else
            return ptr->child->semantic_value.const1->const_u.intval;
    }
    else
        return deal_cexpr(ptr->child);
}

void insert_buildin_functions()
{
    ST_func *func_info;

    func_info = malloc(sizeof(ST_func));
    func_info->ret_type = INT_;
    func_info->params = 0;
    func_info->PL = NULL;
    insert(strdup("read"), FUNC_, func_info, 0, 0);

    func_info = malloc(sizeof(ST_func));
    func_info->ret_type = FLOAT_;
    func_info->params = 0;
    func_info->PL = NULL;
    insert(strdup("fread"), FUNC_, func_info, 0, 0);
    
    func_info = malloc(sizeof(ST_func));
    func_info->ret_type = VOID_;
    func_info->params = 1;
    func_info->PL = NULL; /* not good */
    insert(strdup("write"), FUNC_, func_info, 0, 0);
}
