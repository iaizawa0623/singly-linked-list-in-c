//	singly-linked_list.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

///	ノード
typedef struct node_t {
	void *data; //	扱うデータのポインタ
	struct node_t *next; //	次のnode
} node_t;

///	リストの先頭と扱うデータの大きさも持つ
typedef struct list_t {
	node_t *start; //	リストの先頭
	size_t length; //	データの大きさ
} list_t;

///	新しいリストを作る
///	その際リストにするデータの大きさを教えてもらう
list_t *new_list(size_t length) {
	list_t *p = malloc(sizeof(list_t*));
	p->start = NULL;
	p->length = length;
	return p;
}

///	最後にnodeを追加
void add_list(list_t *begin, void *data) {
	node_t *p = begin->start;

	if (p == NULL) { //	最初の1個目
		p = begin->start = malloc(sizeof(node_t*));
	} else { //	2個目以降
		while (p->next != NULL) {
			p = p->next;
		}
		p = p->next = malloc(sizeof(node_t*));
	}
	p->next = NULL;
	p->data = malloc(begin->length);
	memcpy(p->data, data, begin->length);
}

///	全てのnodeを解放
void clear_list(list_t *begin) {
	node_t* p = begin->start;
	begin->start = NULL;

	while (p != NULL) {
		free(p->data);
		p = p->next;
	}
}

///	comparisonを満たす(0以外を返す)ノードを抽出し
///	新しいリストを作り返す
list_t *select_list(list_t *begin, int (*comparison)(void *)) {
	node_t *p = begin->start;
	list_t *retval = new_list(begin->length);
	
	while (p != NULL) {
		if (comparison(p->data)) {
			add_list(retval, p->data);
		}
		p = p->next;
	}
	return retval;
}

///	全てのnodeに関数を適用
void foreach_list(list_t *begin, void (*f)(void *)) {
	node_t *p = begin->start;
	
	while (p != NULL) {
		f(p->data);
		p = p->next;
	}
}

///	全てのnode(構造体)の特定メンバに関数を適用
void foreach_list_in_part(list_t *begin, void (*f)(void *), size_t member_offset) {
	node_t *p = begin->start;
	
	while (p != NULL) {
		f((void *)*(long *)(member_offset + (char *)p->data));
		p = p->next;
	}
}



