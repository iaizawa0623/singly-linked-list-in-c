//	singly-linked_list.h
#include <stdlib.h>

///	リストの型
typedef struct list list_t;

///	新しいリストを作る
list_t *new_list(size_t);

///	要素を追加
void add_list(list_t *begin, void *data);

///	すべての要素を解放
void clear_list(list_t *begin);

///	comparisonを満たす(0以外を返す)ノードを抽出し
///	新しいリストを作り返す
list_t *select_list(list_t *begin, int (*comparison)(void *));

///	すべての要素に関数を適用
void foreach_list(list_t *, void (*f)(void *));

///	すべての要素(構造体)の特定メンバに関数を適用
void foreach_list_in_part(list_t *begin, void (*f)(void *), size_t member_offset);

