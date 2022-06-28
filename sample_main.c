#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "singly-linked_list.h"

//	適当な構造体
typedef struct person {
	char name[32];	//	名前
	int age;	//	年齢
	char *memo;	//	メモ。動的メモリ利用
} person_t;

//	構造体の中身を表示する
void show_person(void *data);
//	personの年齢が11で割り切れる時に1を返す
int divide_age_11(void *data);

int main()
{
	/// ---------- 文字列のリスト ----------
	list_t *str_list = new_list(sizeof(char[128]));
	add_list(str_list, "1.これは文字列のリスト\n");
	add_list(str_list, "2.こんにちは\n");
	add_list(str_list, "3.こんばんわ\n");
	foreach_list(str_list, (void(*)(void*))printf);
	clear_list(str_list);
	// 要素がクリアされたので何も表示されない
	foreach_list(str_list, (void(*)(void*))printf);

	/// -------- person_t構造体のリスト --------
	list_t *person_list = new_list(sizeof(person_t));
	person_t person_to_add = { "たろう ", 11, strdup("長男") };
	add_list(person_list, &person_to_add);
	//	追加することでリストが記憶域を確保しコピーとして管理するので
	//	あえてperson_to_addに上書きして追加
	strcpy(person_to_add.name, "じろう "); person_to_add.age = 20;
	//	この時リスト上のmemoはアドレスしか持っておらず
	//	freeするとたろうのmemoの内容が消えてしまう
	person_to_add.memo = strdup("次男");
	add_list(person_list, &person_to_add);
	strcpy(person_to_add.name, "さぶろう"); person_to_add.age = 33; person_to_add.memo = strdup("三男");
	add_list(person_list, &person_to_add);
	//	全員の構造体がリストには残っている
	foreach_list(person_list, show_person);
	//	年齢が11で割り切れる人のリストを作る
	printf("\" 年齢が11で割り切れる人↓\n");
	list_t *people_11 = select_list(person_list, divide_age_11);
	foreach_list(people_11, show_person);
	//	ノードのmemoをfree
	//	共有されているので別途people_11のmemoをfreeする必要なはい(できない)
	foreach_list_in_part(person_list, free, offsetof(person_t, memo));
	//	クリアー
	clear_list(person_list);
	clear_list(people_11);

    return EXIT_SUCCESS;
}

//	personのメンバを出力
void show_person(void *data){
	person_t *p = data;

	printf("名前:%s\t", p->name);
	printf("年齢:%d\t", p->age);
	printf("メモ:%s\n", p->memo);
}

//	personの年齢が11で割り切れる時に1を返す
int divide_age_11(void *data) {
	person_t *p = data;

	return !(p->age % 11);
}
