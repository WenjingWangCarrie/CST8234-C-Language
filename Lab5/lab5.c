#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

int Length(struct node* head);
void PrintList(struct node* head);
void Add(struct node** headRef, int new);
int Delete(struct node** headRef);
void ZeroList(struct node** headRef);

int main() {
	struct node* head = NULL;
	int num, f;
	char c;
	char select = 'n';

	while (select !='e' || select !='E' || f !=EOF) {
	    printf("a: add a new node with value x to the list, at the front of the list\n");
		printf("d: delete the fist node of list\n");
		printf("l: print the number of nodes in the list\n");
		printf("p: print the complete list\n");
		printf("z: delete the entire list\n");
		printf("e: quit the program\n");

		f = (fscanf(stdin, "%c", &select));

		if (f == EOF) {
			break;
		}

		if (select =='a' || select == 'A') {
			f = (fscanf(stdin, "%d%c", &num, &c));
			if (c == '\n') {
				Add(&head, num);
			}
		} else {
			fscanf(stdin, "%c", &c);
			if ((select == 'd' && c == '\n') || (select == 'D' && c == '\n')) {
				Delete(&head);
			} else if ((select == 'l' && c == '\n') || (select == 'L' && c == '\n')) {
				printf("There are %d nodes.\n", Length(head));
			} else if((select == 'p' && c == '\n') || (select == 'P' && c == '\n')) {
				PrintList(head);
			} else if ((select == 'z' && c == '\n') || (select == 'Z' && c == '\n')) {
				ZeroList(&head);
			} else if ((select == 'e' && c == '\n') || (select == 'E' && c == '\n')) {
				break;
			} else {
				printf("Invalid option, please try again.\n");
			}
		}

	}

	return EXIT_SUCCESS;
}

/* return number of nodes in the list. */
int Length (struct node* head) {
	int count = 0;
	struct node* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

/* Prints all the nodes on a list */
void PrintList(struct node* head) {
	struct node* current = head;

	if (current == NULL) {
		printf("Linked list is empty!\n");
		return;
	} 

    printf("The list is: ");
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	
    printf("\n");
    return;

}

/*Given an int and a reference to the head pointer, add a new node at the head of the list. */
void Add(struct node** headRef, int new) {
	struct node* head;

	head = (struct node*) malloc(sizeof(struct node));
	head->data = new;
	head->next = *headRef;	
	*headRef = head;

	printf("New node added to the list.\n");
	return;
}

/*Takes a non-empty list, deletes the head node, and returns the head node's data. */
int Delete(struct node** headRef) {
	struct node* current;
	int val = 0;

	if (*headRef == NULL) {
		printf("List is empty. Nothing to delete.\n");
		return val;
	}

	current = *headRef;
	val = current->data;
	*headRef = current->next;
	free(current);

	printf("The head is deleted.\n");
	return val;
}

/* Deallocates all of its memory and sets its head pointer to NULL*/
void ZeroList(struct node** headRef) {
	struct node* p;

	if (*headRef == NULL) {
		printf("List is empty, nothing to free\n");
		return;
	}

	while (*headRef != NULL) {
		p = *headRef;
		*headRef = p->next;
		free(p);
	}

	printf("All nodes have been deleted.\n");
	return;

}
