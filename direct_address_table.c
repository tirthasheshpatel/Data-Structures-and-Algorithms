#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000


typedef size_t size_type;
typedef struct Table* iterator;
typedef const struct Table* const_iterator;

struct Table
{
	int key;
	char element[100];
};

int insert_in_dat(iterator t, int key, char element[])
{
	if(key < 0 || key >= MAX) return 1;
	else if(t[key].key != -1) return 2;
	struct Table temp = {key, element};
	t[key] = temp;
	return 0;
}

int del_from_dat(iterator t, int key)
{
	if(key < 0 || key >= MAX) return 1;
	t[key].key = -1;
	strcpy(t[key].element, "");
	return 0;
}

int search_in_dat(iterator t, int key)
{
	if(key < 0 || key >= MAX) return 0;
	else if(t[key].key == -1) return 0;
	return 1;
}

int main()
{
	iterator slots = (iterator)malloc(MAX*sizeof(struct Table));
	for(int i=0;i<MAX;i++){
		slots[i].key = -1;
		strcpy(slots[i].element,"");
	}
	int error_code = 0;
	char command;
	while(!error_code)
	{
		printf("Enter command: ");
		fflush(stdout);
		scanf("%c", &command);
		fflush(stdin);
		if(command == 'i'){
			printf("Enter the key and correseponding string you want to store in the table: ");
			int key;
			char element[100];
			scanf("%d%s", &key, element);
			fflush(stdin);
			error_code = insert(slots, key, element);
		}
		else if(command == 'd'){
			printf("Enter the key you want to delete: ");
			int key;
			scanf("%d", &key);
			error_code = del(slots, key);
		}
		else if(command == 's'){
			printf("Enter the key you want to search: ");
			int key;
			scanf("%d", &key);
			int success = search(slots, key);
			if(success) printf("The element present at %d is %s\n", key, slots[key]);
			else printf("Key not found!\n");
		}
		else if(command == 'q') break;
	}
	if(error_code == 1) printf("ERROR 1: Out of index access not allowed!\nTerminating Program...\n");
	else if(error_code == 2) printf("ERROR 2: Entered key doesn't exist in the table!\nTerminating Program...\n");
}