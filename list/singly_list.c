#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
struct data {
	int age;
	int value;
};
struct list {
	struct data *data;
	struct list *next;
};

struct list *head;
struct list *tail;
int initlist()
{
	assert((head = (struct list *)malloc(sizeof(struct list))) != NULL);
	head->data = NULL;
	head->next = NULL;
	tail = head;
	return 0;
}
int insert_no(struct data *data, int no)
{
	assert(data);	
	int cnt = 0;
	struct list *p = head;
	while(cnt < no) {
		p = p->next;
		assert(p != NULL);
		cnt++;
	}
	struct list *new_code = (struct list *)malloc(sizeof(struct list));
	assert(new_code);

	struct data *data_buf = (struct data *)malloc(sizeof(struct data));
	assert(data_buf);
	data_buf->age = data->age;
	data_buf->value = data->value;
	new_code->data = data_buf;
	new_code->next = p->next ? p->next : NULL;
	p->next = new_code;
	if (new_code->next == NULL)
		tail = new_code;
	return 0;
}
int insert_head(struct data *data)
{
	assert(head);

	struct list *new_code = (struct list *)malloc(sizeof (struct list));
	assert(new_code);

	struct data *data_buf = (struct data *)malloc(sizeof(struct data));
	assert(data_buf);
	data_buf->age = data->age;
	data_buf->value = data->value;

	new_code->next = NULL;
	new_code->data = data_buf;
	new_code->next = head->next;
	head->next = new_code;
	if(new_code->next == NULL)
		tail = new_code;
	return 0;	
}
int insert_tail(struct data *data)
{
	struct list *new_code = (struct list *)malloc(sizeof(struct list));	
	assert(new_code);

	struct data *data_buf = (struct data *)malloc(sizeof(struct data));
	assert(data_buf);
	data_buf->age = data->age;
	data_buf->value = data->value;

	new_code->next = NULL;
	new_code->data = data_buf;

	tail->next = new_code;
	tail = new_code;
	return 0;
}

int search_node(struct data *data)
{
	struct list *p = head->next;
	int no = 0;
	while(p) {
		if (p->data->age == data->age && p->data->value == data->value) return no;
		p = p->next;
		no++;
	}
	printf("cannot find the data\n");
	return -1;
}
int del_node_pos(int no)
{
	int cnt = 0;
	struct list *p = head;
	while (cnt < no && p != NULL) {
		p = p->next;
		cnt++;
	}

	if (p == NULL || p->next == NULL) {
		printf("The linked list currently does not have so many nodes!\n");
		return -1;
	}
	struct list *tmp = p->next;
	p->next = p->next->next;
	assert(tmp->data);
	free(tmp->data);
	free(tmp);

	return 0;
}

int del_node_data(struct data *data)
{
	assert(data);
	struct list *p = head->next;
	struct list *pp = head;
	while(p) {
		if (p->data->age == data->age && p->data->value == data->value) {
			struct list *tmp = p;
			pp->next = p->next;	
			assert(tmp->data);
			free(tmp->data);
			free(tmp);
			return 0;
		}
		pp = p;
		p = p->next;
	}
	printf("The node you are searching for does not exist in the current linked list\n");
	return -1;
}
void print_list()
{
	struct list *p = head->next;
	while(p) {
		if (p != head) {
			printf("data: %d %d ",p->data->age, p->data->value);
		}
		p = p->next;
	}
	assert(tail);
	printf("tail: %d %d", tail->data->age, tail->data->value);
	printf("\n");
}
int main() {
	initlist();	
	struct data data = {1, 2};
	struct data data1 = {2, 3};
	struct data data2 = {4, 5};
	struct data data4 = {6, 7};
	struct data data5 = {999, 7};
	insert_no(&data, 0);
	print_list();
	insert_no(&data, 1);
	print_list();
	insert_head(&data1);
	print_list();
	insert_head(&data2);
	print_list();
	insert_head(&data4);
	print_list();
	insert_no(&data5, 4);
	print_list();
	insert_tail(&data5);
	print_list();
	insert_tail(&data5);
	print_list();
	printf("%d %d <- %d\n", data.age, data.value, search_node(&data));
	printf("%d %d <- %d\n", data1.age, data1.value, search_node(&data1));
	printf("%d %d <- %d\n", data2.age, data2.value, search_node(&data2));
	printf("%d %d <- %d\n", data4.age, data4.value, search_node(&data4));
	printf("%d %d <- %d\n", data5.age, data5.value, search_node(&data5));
	del_node_pos(0);
	print_list();
	del_node_pos(0);
	print_list();
	del_node_pos(2);
	print_list();
	del_node_data(&data5);
	print_list();
	return 0;
}
