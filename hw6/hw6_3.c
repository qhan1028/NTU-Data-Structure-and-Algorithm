#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_ntudsa.h"
#define MAX 100000

struct avl_table *tree[MAX]; // game set
int boss[MAX], set_to_friend[MAX], tree_size[MAX]; 
long long int money, max_game;

typedef struct avl_node NODE;
typedef struct avl_table TABLE;
typedef long long int LLD;

void merge_tree(NODE *tree, TABLE *new_tree) 
{
	if (tree == NULL) return;
	if (tree->avl_link[0] != NULL || tree->avl_link[1] != NULL) {
		merge_tree(tree->avl_link[0], new_tree);
		merge_tree(tree->avl_link[1], new_tree);
	}
	int i;
	for (i = 0 ; i < tree->avl_cnt ; i++) avl_probe(new_tree, tree->avl_data);
	free(tree);
}

void merge_set(int set1 ,int set2, int stf) 
{
	if (tree_size[set1] > tree_size[set2]) {
		set_to_friend[set1] = stf;
		boss[set2] = set1;
		merge_tree(tree[set2]->avl_root, tree[set1]);
	} else if (tree_size[set2] > tree_size[set1]) {
		set_to_friend[set2] = stf;
		boss[set1] = set2;
		merge_tree(tree[set1]->avl_root, tree[set2]);
	} else {
		set_to_friend[set1] = stf;
		boss[set2] = set1;
		merge_tree(tree[set2]->avl_root, tree[set1]);
		tree_size[set1]++;
	}
}

void find_max_game(NODE * node) 
{
	if (node == NULL) return;
	if (node->avl_sum[0] <= money) {
		// left node
		max_game += (LLD)node->avl_cnode[0];
		money -= node->avl_sum[0];
		// current node
		LLD temp = money / (LLD)node->avl_data;
		int go_right_node = 0;
		if (temp >= (LLD)node->avl_cnt) {
			temp = (LLD)node->avl_cnt;
			go_right_node++;
		}
		max_game += temp;
		money -= (LLD)node->avl_data * temp;
		// right node
		if (go_right_node) {
			if (node->avl_sum[1] <= money) {
				max_game += (LLD)node->avl_cnode[1];
				return;
			} else find_max_game(node->avl_link[1]);
		}
	} else find_max_game(node->avl_link[0]);
}

int find_boss(int n)
{
	if (boss[n] != n) {
		find_boss(boss[n]);
	} 
	else return n;
}

int compare(const void *pa, const void *pb, void *param)
{
	int a = *(const int*)pa;
	int b = *(const int*)pb;
	if(a < b)	return -1;
	else if(a > b)	return +1;
	else return 0;
}

int main()
{
	int friend = 0, incident = 0, i;
	scanf("%d %d", &friend, &incident);
	for (i = 0 ; i < friend ; i++) {
		int price = 0;
		scanf("%d", &price);
		tree[i] = avl_create(compare, NULL, NULL);
		avl_probe(tree[i], price);
		boss[i] = i;
		set_to_friend[i] = i;
		tree_size[i] = 1;
	}
	for (i = 0 ; i < incident ; i++) {
		int command;
		scanf("%d", &command);
		if (command == 1) {
			int game1, game2;
			scanf("%d%d", &game1, &game2);
			int set1 = find_boss(game1-1), set2 = find_boss(game2-1);
			if (set1 != set2) merge_set(set1, set2, set_to_friend[set1]);
		} else {
			int game;
			max_game = 0;
			scanf("%d %lld", &game, &money);
			int set = find_boss(game-1);
			find_max_game(tree[set]->avl_root);
			printf("%d %lld\n", set_to_friend[set]+1, max_game);
		}
	}
}