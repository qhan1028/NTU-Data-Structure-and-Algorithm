#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "rb.h"
#include "bst.h"
#define MAX 130

void preorder_str_avl(const struct avl_node *node ){
	if(node == NULL)
		return;
	printf("%s ", ((char*)node->avl_data));
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL){
		putchar ('(');
		preorder_str_avl ( node->avl_link [0] );
		putchar (',');
		putchar (' ');
		preorder_str_avl ( node->avl_link [1] );
		putchar (')');
	}
}

void preorder_str_bst(const struct bst_node *node ){
	if(node == NULL)
		return;
	printf ("%s ", ((char*) node->bst_data ));
	if (node->bst_link[0] != NULL || node->bst_link[1] != NULL){
		putchar ('(');
		preorder_str_bst(node->bst_link[0]);
		putchar (',');
		putchar (' ');
		preorder_str_bst(node->bst_link[1]);
		putchar (')');
	}
}

void preorder_str_rb ( const struct rb_node *node ){
	if( node == NULL)
		return;
	printf ("%s ", ((char*) node->rb_data ));
	if ( node->rb_link[0] != NULL || node->rb_link[1] != NULL){
		putchar ('(');
		preorder_str_rb ( node->rb_link[0] );
		putchar (',');
		putchar (' ');
		preorder_str_rb ( node->rb_link[1] );
		putchar (')');
	}
}

int str_compare(const void *pa ,const void *pb ,void *param){
	const char *a = (const char *) pa ;
	const char *b = (const char *) pb ;
	return (strcmp(a, b) == 0)? 0 : (strcmp(a, b) > 0)? 1 : -1;
}

int main(){
	struct avl_table *tree_avl;
	struct bst_table *tree_bst;
	struct rb_table *tree_rb;
	tree_avl = avl_create(str_compare , NULL, NULL);
	tree_bst = bst_create(str_compare , NULL, NULL);
	tree_rb = rb_create(str_compare , NULL, NULL);
	char input[MAX];
	int i;
	for (i = 0; i < 32 ; i++){
		char *element_avl = (char*)malloc(sizeof(char) * MAX);
		char *element_bst = (char*)malloc(sizeof(char) * MAX);
		char *element_rb = (char*)malloc(sizeof(char) * MAX);
		scanf("%s", input);
		strcpy(element_avl, input);
		strcpy(element_bst, input);
		strcpy(element_rb, input);
		avl_probe(tree_avl ,element_avl);
		bst_probe(tree_bst ,element_bst);
		rb_probe(tree_rb ,element_rb);
	}
	preorder_str_avl(tree_avl->avl_root);puts("");
	preorder_str_bst(tree_bst->bst_root);puts("");
	preorder_str_rb(tree_rb->rb_root);puts("");
	return 0;
}