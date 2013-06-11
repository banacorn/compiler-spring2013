#include "header.h"
#include <stdlib.h>

extern int linenumber;

AST_NODE *Allocate(AST_TYPE type){
	AST_NODE *temp;
	temp=(AST_NODE*)malloc(sizeof(struct AST_NODE));
	temp->type=type;
	temp->child=(AST_NODE*)malloc(sizeof(struct AST_NODE));
	temp->child->type=NUL;
	temp->sibling=(AST_NODE*)malloc(sizeof(struct AST_NODE));
	temp->sibling->type=NUL;
	temp->parent=(AST_NODE*)malloc(sizeof(struct AST_NODE));
	temp->parent->type=NUL;
	temp->firstborn=(AST_NODE*)malloc(sizeof(struct AST_NODE));
	temp->firstborn->type=NUL;
	temp->linenumber=linenumber;
	return temp;
}
