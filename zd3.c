#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Osoba {
    char ime[20], prezime[20];
    unsigned int godina_rod;
};

struct Node {
    struct Osoba element;
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

struct Osoba enterPersonData() {
    struct Osoba osoba;
    printf("Unesi ime osobe: ");
    scanf_s("%19s", osoba.ime, (unsigned)_countof(osoba.ime));

    printf("Unesi prezime osobe: ");
    scanf_s("%19s", osoba.prezime, (unsigned)_countof(osoba.prezime));

    printf("Unesi godinu rodenja: ");
    while (scanf_s("%u", &osoba.godina_rod) != 1) {
        printf("Neispravan unos! Pokusaj ponovo: ");
        while (getchar() != '\n');
    }
    return osoba;
}

char* stringInput(char* output) {
    printf("%s ", output);
    char* string = malloc(20 * sizeof(char));
    if (string == NULL) {
        printf("Pogreska: nije moguce alocirati memoriju za string!\n");
        return NULL;
    }
    scanf_s("%19s", string, 20);
    return string;
}

int addToStart(struct Node* header, struct Osoba osoba, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToStart (NULL pokazivac)!\n");
        return 1;
    }
    node->element = osoba;
    node->next = header->next;
    header->next = node;
    return 0;
}

int addToEnd(struct Node* header, struct Osoba osoba, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToEnd (NULL pokazivac)!\n");
        return 1;
    }
    node->element = osoba;
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
    int i = 1;
    if (current == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }

    while (current != NULL) {
        printf("Osoba %d: %s %s %u\n", i++, current->element.ime,
            current->element.prezime, current->element.godina_rod);
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


struct Node* findNode(struct Node* header, char* string) {
    if (header == NULL || string == NULL) {
        printf("Pogreska u findNode (NULL pokazivac)!\n");
        return NULL;
    }

    struct Node* currentNode = header->next;
    while (currentNode != NULL) {
        if (strcmp(currentNode->element.prezime, string) == 0)
            return currentNode;
        currentNode = currentNode->next;
    }
    return NULL;
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

    printf("Osoba nije pronadena!\n");
    return 1;
}

int addAfterNode(struct Node* header, int targetIndex, struct Osoba osoba, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addAfterNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header->next;
    int i = 0;
    while (pointer != NULL) {
        if (i == targetIndex) {
            newNode->element = osoba;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Osoba uspjesno dodana nakon elementa s indeksom %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}

int addBeforeNode(struct Node* header, int targetIndex, struct Osoba osoba, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addBeforeNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header;
    int i = 0;
    while (pointer->next != NULL) {
        if (i == targetIndex) {
            newNode->element = osoba;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Osoba uspjesno dodana prije elementa s indeksom %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}


int writeListToFile(struct Node* header, FILE* file) {
	FILE* file = NULL;
	fopen_s(&file, "list.txt", "w");
	if (file == NULL) {
        printf("Pogreska: datoteka nije otvorena!\n");
        return 1;
    }
    if (header == NULL) {
        printf("Pogreska: lista ne postoji!\n");
        fclose(file);
        return 1;
    }

    struct Node* current = header->next;
    if (current == NULL) {
        printf("Lista je prazna!\n");
        fclose(file);
        return 1;
    }

    int i = 1;
    while (current != NULL) {
        fprintf(file, "Osoba %d: %s %s %u\n", i++,
            current->element.ime,
            current->element.prezime,
            current->element.godina_rod);
        current = current->next;
    }
    fclose(file);
    printf("Uspjesno upisivanje u datoteku!\n");
    return 0;
}

struct Node* readListFromFile(FILE* file) {
	FILE* file = NULL;
	fopen_s(&file, "list.txt", "r");
	if (file == NULL) {
        printf("Greska: datoteka nije otvorena!\n");
        return NULL;
    }

    struct Node* header = createNode();
    if (header == NULL)
        return NULL;

    int id = 0;
    struct Osoba osoba = { "" };
    while (fscanf_s(file, "Osoba %d: %19s %19s %u\n",
        &id, osoba.ime, (unsigned)_countof(osoba.ime),
        osoba.prezime, (unsigned)_countof(osoba.prezime),
        &osoba.godina_rod) == 4) {
        addToEnd(header, osoba, createNode());
    }
    fclose(file);
    printf("Uspjesno ucitana lista iz datoteke!\n");
    return header;
}

int main() {
    struct Node* header = createNode();
    if (header == NULL)
        return 1;

    char input;
    do {
        printf("\nOdaberi radnju:\n");
        printf("a) Dodaj element na pocetak liste\n");
        printf("b) Ispisi listu\n");
        printf("c) Dodaj element na kraj liste\n");
        printf("d) Nadi element (po prezimenu)\n");
        printf("e) Izbrisi element iz liste\n");
        printf("f) Dodaj novi element iza nekog elementa\n");
        printf("g) Dodaj novi element prije nekog elementa\n");
        printf("h) Upisi listu u datoteku\n");
        printf("i) Procitaj listu iz datoteke\n");
        printf("x) Izlaz\n");
        printf("Odabir: ");
        scanf_s(" %c", &input, 1);

        switch (input) {
        case 'a': {
            struct Node* node = createNode();
            if (node != NULL)
                addToStart(header, enterPersonData(), node);
            else
                input = 'x';
            break;
        }
        case 'b':
            printLinkedList(header);
            break;
        case 'c': {
            struct Node* node = createNode();
            if (node != NULL)
                addToEnd(header, enterPersonData(), node);
            else
                input = 'x';
            break;
        }
        case 'd': {
            char* prezime = stringInput("Unesi prezime osobe:");
            if (prezime == NULL) {
                input = 'x';
                break;
            }
            struct Node* node = findNode(header, prezime);
            if (node == NULL)
                printf("Osoba nije pronadena!\n");
            else
                printf("Pronadena osoba: %s %s, %u\n",
                    node->element.ime,
                    node->element.prezime,
                    node->element.godina_rod);
            free(prezime);
            break;
        }
        case 'e': {
            char* prezime = stringInput("Unesi prezime osobe:");
           if (prezime == NULL) {
                input = 'x';
                break;
            }
            struct Node* node = findNode(header, prezime);
            if (node == NULL)
                printf("Osoba nije pronadena!\n");
            else
                deleteNode(header, node);
            free(prezime);
            break;
        }
        case 'f': {
            int index;
            printf("Unesi indeks: ");
            scanf_s("%d", &index);
            struct Node* node = createNode();
            if (node != NULL)
                addAfterNode(header, index, enterPersonData(), node);
            else
                input = 'x';
            break;
        }
        case 'g': {
            int index;
            printf("Unesi indeks: ");
            scanf_s("%d", &index);
            struct Node* node = createNode();
            if (node != NULL)
                addBeforeNode(header, index, enterPersonData(), node);
            else
                input = 'x';
            break;
        }
        case 'h': {
            
            writeListToFile(header, file);
            break;
        }
        case 'i': {
            
            struct Node* readNode = readListFromFile(file);
            if (readNode != NULL) {
                deleteList(header);
                free(header);
                header = readNode;
            }
            else
                input = 'x';
            break;
        }
        }
    } while (input != 'x');

    deleteList(header);
    free(header);
    return 0;
}
