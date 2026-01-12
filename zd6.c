#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
	int element;
	struct Node* next;
};

struct Node* createNode() {
	struct Node* node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("Pogreska: nije moguce alocirati memoriju za cvor!\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}

int push(struct Node* header, int num) {
	struct Node* node = createNode();
	if (node == NULL) {
		printf("Pogreska prilikom alokacije memorije! (push)\n");
		return 2;
	}
	if (header == NULL) {
		printf("Pogreska u push (NULL pokazivac)!\n");
		free(node);
		return 1;
	}
	node->element = num;
	node->next = header->next;
	header->next = node;
	return 0;
}

int pop(struct Node* header) {
	if (header == NULL) {
		printf("Pogreska u pop (NULL pokazivac)!\n");
		return 1;
	}
	if (header->next != NULL) {
		struct Node* temp = 0;
		temp = header->next->next;
		free(header->next);
		header->next = temp;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}

int printLinkedList(struct Node* header) {
	if (header == NULL) {
		printf("Pogreska u printLinkedList (NULL header)!\n");
		return 1;
	}

	struct Node* current = header->next;
	if (current == NULL) {
		printf("Lista je prazna.\n");
		return 2;
	}

	while (current != NULL) {
		printf("%d ", current->element);
		current = current->next;
	}
	printf("\n");
	return 0;
}

static int enqueue(struct Node* header, int num, short resetLastNode) {
	static struct Node* lastNode = NULL;
	if (resetLastNode > 0) {
		lastNode = NULL;
		return 3;
	}

	if (header == NULL) {
		printf("Pogreska u enqueue (NULL pokazivac)!\n");
		return 1;
	}
	if (lastNode == NULL)
		lastNode = header;

	struct Node* node = createNode();
	if (node == NULL) {
		printf("Pogreska prilikom alokacije memorije! (enqueue)\n");
		return 2;
	}
	node->element = num;
	node->next = NULL;
	lastNode->next = node;
	lastNode = node;
	return 0;
}

int dequeue(struct Node* header) {
	if (header == NULL) {
		printf("Pogreska u dequeue (NULL pokazivac)!\n");
		return 1;
	}
	if (header->next != NULL) {
		struct Node* temp = 0;
		temp = header->next->next;
		if (header->next->next == NULL)
			enqueue(NULL, 0, 1); // Prvi element je zadnji, počisti u enqueue lastNode
		free(header->next);
		header->next = temp;
		return 0;
	}
	else {
		printf("Red je prazan\n");
		return 2;
	}
}


int deleteList(struct Node* header) {
	if (header == NULL) {
		printf("Pogreska u deleteList (NULL header)!\n");
		return 1;
	}

	struct Node* current = header->next;
	while (current != NULL) {
		struct Node* next = current->next;
		free(current);
		current = next;
	}
	header->next = NULL;
	return 0;
}

int main() {
	char input = ' ';
	char action = ' ';
	int num = 0;
	struct Node* header = createNode();
	if (header == NULL)
		return 1;
	do
	{
		printf("Odaberite strukturu za pohranu podataka:\na) Stog (Stack)\nb) Red (Queue)\nx) Izlaz\n");
		scanf_s(" %c", &input, 1);
		switch (input) {
		case 'a': {
			do {
				printf("Odaberite radnju: a) Push b) Pop c) Push random (10-100) d) Ispis stoga x) Izlaz\n");
				scanf_s(" %c", &action, 1);
				switch (action) {
				case 'a': {
					printf("Unesi broj: ");
					scanf_s(" %d", &num);
					if (push(header, num) != 0)
						action = 'x';
					break;
				}
				case 'b': {
					int result = pop(header);
					switch (result) {
					case 0:
						printf("Uspjesno je izbrisan element iz reda!\n");
						break;
					case 2:
						break;
					default:
						action = 'x';
						break;
					}
					break;
				}
				case 'c': {
					srand((unsigned int)time(NULL));
					num = rand() % (100 - 10 + 1) + 10;
					if (push(header, num) != 0)
						action = 'x';
					else
						printf("Uspjesno je dodan element vrijednosti: %d\n", num);
					break;
				}
				case 'd': {
					printLinkedList(header);
					break;
				}
				default: {
					break;
				}
				}
			} while (action != 'x');
			break;
		}
		case 'b': {
			do {
				printf("Odaberite radnju: a) Enqueue b) Dequeue c) Enqueue random (10-100) d) Ispis reda x) Izlaz\n");
				scanf_s(" %c", &action, 1);
				switch (action) {
				case 'a': {
					printf("Unesi broj: ");
					scanf_s(" %d", &num);
					if (enqueue(header, num, 0) != 0)
						action = 'x';
					break;
				}
				case 'b': {
					int result = dequeue(header);
					switch (result) {
					case 0:
						printf("Uspjesno je izbrisan element iz reda!\n");
						break;
					case 2:
						break;
					default:
						action = 'x';
						break;
					}
					break;
				}
				case 'c': {
					srand((unsigned)time(NULL));
					num = rand() % (100 - 10 + 1) + 10;
					if (enqueue(header, num, 0) != 0)
						action = 'x';
					else
						printf("Uspjesno je dodan element vrijednosti: %d\n", num);
					break;
				}
				case 'd': {
					printLinkedList(header);
					break;
				}
				default: {
					break;
				}
				}
			} while (action != 'x');
			break;
		}
		default:
			break;
		}
	} while ((input != 'a' && input != 'b') && input != 'x');

	deleteList(header);
	free(header);
}
