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


int addToStart(struct Node* header, int num, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToStart (NULL pokazivac)!\n");
        return 1;
    }
    node->element = num;
    node->next = header->next;
    header->next = node;
    return 0;
}

int addToEnd(struct Node* header, int num, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToEnd (NULL pokazivac)!\n");
        return 1;
    }
    node->element = num;
    node->next = NULL;

    struct Node* current = header;
    while (current->next != NULL)
        current = current->next;

    current->next = node;
    return 0;
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

int deleteNode(struct Node* header, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u deleteNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* currentNode = header;
    while (currentNode->next != NULL) {
        if (currentNode->next == node) {
            currentNode->next = node->next;
            free(node);
            printf("Element uspjesno izbrisan iz liste!\n");
            return 0;
        }
        currentNode = currentNode->next;
    }
    printf("Element nije pronaden!");
    return 1;
}

int addAfterNode(struct Node* header, int targetIndex, int num, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addAfterNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header->next;
    int i = 0;
    while (pointer != NULL) {
        if (i == targetIndex) {
            newNode->element = num;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Clan uspjesno dodan nakon elementa s indeksom %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}

int addBeforeNode(struct Node* header, int targetIndex, int num, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addBeforeNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header;
    int i = 0;
    while (pointer->next != NULL) {
        if (i == targetIndex) {
            newNode->element = num;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Clan uspjesno dodan prije elementa s indeksom %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}


int addSortedNode(struct Node* header, int num, struct Node* newNode) {
    if (header == NULL || newNode == NULL)
    {
        printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
        return 1;
    }

    struct Node* current = header;
    while (current->next != NULL) {
        if (num >= current->next->element)
            break;
        current = current->next;
    }

    newNode->element = num;
    newNode->next = current->next;
    current->next = newNode;

    return 0;
}

int sortPolynomial(struct Node** header) {
    if (header == NULL || *header == NULL)
    {
        printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
        return 1;
    }
    if ((*header)->next == NULL) {
        printf("Lista je prazna!");
        return 0;
    }

    struct Node* newHeader = createNode();
    if (newHeader == NULL)
        return 2;

    struct Node* current = (*header)->next;
    struct Node* newNode = NULL;
    while (current != NULL)
    {
        newNode = createNode();
        if (newNode == NULL)
            return 2;
        if (addSortedNode(newHeader, current->element, newNode) != 0) {
            printf("Greska prilikom dodavanja elemenata u novu listu!");
            return 3;
        }
        current = current->next;
    }
    deleteList(*header);
    *header = newHeader;
    return 0;
}

int existsInList(struct Node* header, int number) {
    if (header == NULL)
    {
        printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
        return -1;
    }

    struct Node* current = header->next;

    while (current != NULL)
    {
        if (current->element == number) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

struct Node* joinListsWithoutDuplicates(struct Node** headers, unsigned short arr_length) {
    if (headers == NULL)
    {
        printf("Greska prilikom ucitavanja niza! (Pokazivac NULL)");
        return NULL;
    }
    struct Node* newHeader = createNode();
    if (newHeader == NULL) {
        printf("Greska prilikom alokacije cvora! (joinLists)");
        return NULL;
    }
    struct Node* newNode;
    struct Node* current = NULL;
    for (int i = 0; i < arr_length; i++)
    {
        if (headers[i] == NULL) {
            printf("Greska prilikom ucitavanja jedne liste u nizu! (Pokazivac NULL)");
            free(newHeader);
            return NULL;
        }
        current = headers[i]->next;
        while (current != NULL)
        {
            newNode = createNode();
            if (newNode == NULL) {
                printf("Greska prilikom alokacije cvora! (joinLists)");
                free(newHeader);
                return NULL;
            }
            if (existsInList(newHeader, current->element) == 0)
                addSortedNode(newHeader, current->element, newNode);
            current = current->next;
        }
    }
    return newHeader;
}

struct Node* intersectionList (struct Node** headers, unsigned short arr_length) {
    //Radi samo za 2 liste kao sto je zadano u zadatku
    if (headers == NULL)
    {
        printf("Greska prilikom ucitavanja niza! (Pokazivac NULL)");
        return NULL;
    }
    struct Node* newHeader = createNode();
    if (newHeader == NULL) {
        printf("Greska prilikom alokacije cvora! (joinLists)");
        return NULL;
    }
    struct Node* newNode;
    struct Node* current = NULL;
    for (int i = 1; i < arr_length; i++)
    {
        if (headers[i] == NULL) {
            printf("Greska prilikom ucitavanja jedne liste u nizu! (Pokazivac NULL)");
            free(newHeader);
            return NULL;
        }
        current = headers[i]->next;
        while (current != NULL)
        {
            newNode = createNode();
            if (newNode == NULL) {
                printf("Greska prilikom alokacije cvora! (joinLists)");
                free(newHeader);
                return NULL;
            }
            if (existsInList(headers[0], current->element) == 1 && existsInList(newHeader, current->element) == 0)
                addSortedNode(newHeader, current->element, newNode);
            current = current->next;
        }
    }
    return newHeader;
}

struct Node* readSortedListFromFile(FILE* file) {
    if (file == NULL) {
        printf("Greska: datoteka nije otvorena!\n");
        return NULL;
    }

    struct Node* header = createNode();
    if (header == NULL)
        return NULL;

    int num;
    struct Node* node = NULL;
    while (fscanf_s(file, "%d", &num) == 1)
    {
        node = createNode();
        if (node == NULL) {
            deleteList(header);
            free(header);
            return NULL;
        }
        addSortedNode(header, num, node);
    }

    return header;
}

FILE* fileInput() {
    FILE* file = NULL;
    printf("Unesi ime datoteke: ");
    char fileName[40] = "";
    scanf_s(" %s", fileName, 40);

    fopen_s(&file, fileName, "r");

    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke!\n");
    }
    return file;
}

int main() {
    FILE* files[2] = { NULL };
    struct Node* headers[2];

    for (int i = 0; i < 2; i++)
    {
        printf("%d ", i + 1);
        files[i] = fileInput();
        if (files[i] == NULL)
            i--;
    }

    for (int i = 0; i < 2; i++)
    {
        headers[i] = readSortedListFromFile(files[i]);
        if (headers[i] == NULL) {
            printf("Pogreska prilikom citanja liste iz datoteke!");
            return 1;
        }
    }
    char input = '0';
    do
    {
        printf("\nUnesi znak za trazenu radnju:\n1) Unija brojeva 2) Presjek brojeva x) Prekid programa\n");
        scanf_s(" %c", &input, 1);


        struct Node* newHeader = NULL;

        switch (input)
        {
        case '1': {
            newHeader = joinListsWithoutDuplicates(&headers, 2);
            if (newHeader == NULL)
                input = 'x';
            printf("Nova lista: ");
            printLinkedList(newHeader);
            deleteList(newHeader);
            free(newHeader);
            break;
        }
        case '2': {
            newHeader = intersectionList(&headers, 2);
            if (newHeader == NULL)
                input = 'x';
            printf("Nova lista: ");
            printLinkedList(newHeader);
            deleteList(newHeader);
            free(newHeader);
            break;
        }
        default:
            break;
        }

    } while (input != 'x');

    for (int i = 0; i < 2; i++)
    {
        if (files[i] != NULL)
            fclose(files[i]);
        if (headers[i] != NULL) {
            deleteList(headers[i]);
            free(headers[i]);
        }
    }
    return 0;

}
