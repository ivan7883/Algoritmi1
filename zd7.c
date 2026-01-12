#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned int maxElements = 0;
static unsigned int currentElements = 0;

struct Node {
	int element;
	short priority;
	struct Node* next;
};

struct Node* createNode() {
	struct Node* node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("Pogreska: nije moguce alocirati memoriju za cvor!\n");
		return NULL;
	}
	srand((unsigned)time(NULL));
	node->priority = rand() % (5 - 1 + 1) + 1;
	node->next = NULL;
	return node;
}

int push(struct Node* header, int num) {
	if(maxElements > 0 && currentElements >= maxElements) {
		printf("Stog je pun! Maksimalan broj elemenata je %u\n", maxElements);
		return 3;
	}
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
	currentElements++;
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
		currentElements--;
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

int enqueue(struct Node* header, int num) {
	if (header == NULL) {
		printf("Pogreska u enqueue (NULL pokazivac)!\n");
		return -1;
	}

	struct Node* node = createNode();
	if (node == NULL) {
		printf("Pogreska prilikom alokacije memorije! (enqueue)\n");
		return -2;
	}

	struct Node* current = header;
	while (current->next != NULL) {
		if (node->priority > current->next->priority)
			break;
		current = current->next;
	}

	node->element = num;
	node->next = current->next;
	current->next = node;
	return node->priority;
}

int dequeue(struct Node* header) {
	if (header == NULL) {
		printf("Pogreska u dequeue (NULL pokazivac)!\n");
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
		printf("Odaberite strukturu za pohranu podataka:\na) Cirkularni stog (Stack)\nb) Red s prioritetom (Queue)\nx) Izlaz\n");
		scanf_s(" %c", &input, 1);
		switch (input) {
		case 'a': {
			printf("Unesite maksimalan broj elemenata stoga (0 za neograniceno): ");
			scanf_s(" %u", &maxElements);
			do {
				printf("Odaberite radnju: a) Push b) Pop c) Push random (10-100) d) Ispis stoga x) Izlaz\n");
				scanf_s(" %c", &action, 1);
				switch (action) {
				case 'a': {
					printf("Unesi broj: ");
					scanf_s(" %d", &num);
					int output = push(header, num);
					if (output != 0 && output != 3)
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
					int output = push(header, num);
					if (output != 0 && output != 3)
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
					int output = enqueue(header, num);
					if (output < 0)
						action = 'x';
					else
						printf("Uspjesno je dodan element s prioritetom %d\n", output);
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
					int output = enqueue(header, num);
					if (output < 0)
						action = 'x';
					else
						printf("Uspjesno je dodan element vrijednosti: %d s prioritetom %d\n", num, output);
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
