#include <stdio.h>
#include <stdlib.h>

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

int pop(struct Node* header, int *output) {
	if (header == NULL) {
		printf("Pogreska u pop (NULL pokazivac)!\n");
		return 1;
	}
	if (header->next != NULL) {
		struct Node* temp = 0;
		int output1 = header->next->element;
		temp = header->next->next;
		free(header->next);
		header->next = temp;
		*output = output1;
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

int calculatePostfixFromFile(char* filename, int *result) {
	FILE* file = NULL;
	fopen_s(&file, filename, "r");
	if (file == NULL) {
		printf("Pogreska: datoteka je NULL!\n");
		return 1;
	}

	if (fgetc(file) == EOF)
	{
		printf("Pogreska: datoteka je prazna!\n");
		fclose(file);
		return 6;
	}
	else
		rewind(file);

	struct Node* stackHeader = createNode();
	if (stackHeader == NULL) {
		printf("Pogreska prilikom alokacije memorije za stog!\n");
		fclose(file);
		return 2;
	}
	char ch = EOF;
	int num = 0;
	int previousWasDigit = 0;


	while ((ch = fgetc(file)) != EOF && ch != '\n')
	{
		if (ch >= '0' && ch <= '9') {
			num *= 10;
			num += ch - '0';
			previousWasDigit = 1;
		}
		else if (ch == ' ') {
			if (previousWasDigit == 1) {
				if (push(stackHeader, num) != 0) {
					deleteList(stackHeader);
					free(stackHeader);
					fclose(file);
					return 7;
				}
				num = 0;
				previousWasDigit = 0;
			}
			continue;
		}
		else {
			if (previousWasDigit == 1) {
				if (push(stackHeader, num) != 0) {
					deleteList(stackHeader);
					free(stackHeader);
					fclose(file);
					return 7;
				}
				num = 0;
			}
			previousWasDigit = 0;
			int operand2 = 0;
			int operand1 = 0;
			if (pop(stackHeader, &operand2) == 2 || pop(stackHeader, &operand1) == 2)
			{
				printf("Pogreska: izraz nije ispravan, nedostaje operand.\n");
				deleteList(stackHeader);
				free(stackHeader);
				fclose(file);
				return 3;
			}
			int result = 0;
			switch (ch) {
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0) {
					printf("Pogreska: dijeljenje s nulom!\n");
					fclose(file);
					deleteList(stackHeader);
					free(stackHeader);
					return 3;
				}
				result = operand1 / operand2;
				break;
			default:
				printf("Pogreska: nepoznat operator %c\n", ch);
				deleteList(stackHeader);
				free(stackHeader);
				fclose(file);
				return 4;
			}
			if (push(stackHeader, result) != 0) {
				deleteList(stackHeader);
				free(stackHeader);
				fclose(file);
				return 7;
			}
		}
	}
	if (previousWasDigit == 1) {
		if (push(stackHeader, num) != 0) {
			deleteList(stackHeader);
			free(stackHeader);
			fclose(file);
			return 7;
		}
		num = 0;
	}
	if (stackHeader->next->next != NULL)
	{
		printf("Pogreska: izraz nije ispravan, postoji visak operatora.\n");
		deleteList(stackHeader);
		free(stackHeader);
		fclose(file);
		return 5;
	}
	pop(stackHeader, result);
	deleteList(stackHeader);
	free(stackHeader);
	fclose(file);
	return 0;
}

int main() {
	printf("Unesi ime datoteke: ");
	char filename[100] = "";
	scanf_s("%s", filename, 100);

	int result = 0;
	if (calculatePostfixFromFile(filename, &result) == 0)
	{
		printf("Uspjesno izracunat postfix izraz iz datoteke.\nRezultat operacija: %d", result);
	}
}
