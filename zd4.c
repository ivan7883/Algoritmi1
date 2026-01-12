#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Term {
    float coeff;
    float exp;
};

struct Node {
    struct Term element;
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


int addToStart(struct Node* header, struct Term term, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToStart (NULL pokazivac)!\n");
        return 1;
    }
    node->element = term;
    node->next = header->next;
    header->next = node;
    return 0;
}

int addToEnd(struct Node* header, struct Term term, struct Node* node) {
    if (header == NULL || node == NULL) {
        printf("Pogreska u addToEnd (NULL pokazivac)!\n");
        return 1;
    }
    node->element = term;
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
        return 2;
    }

    while (current != NULL) {
        if(current->element.exp == 0)
            printf("%.2f ", current->element.coeff);
        else
            printf("%.2fx^%.2f ", current->element.coeff, current->element.exp);
        if (current->next != NULL)
            printf("+ ");
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

    printf("term nije pronadena!\n");
    return 1;
}

int addAfterNode(struct Node* header, int targetIndex, struct Term term, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addAfterNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header->next;
    int i = 0;
    while (pointer != NULL) {
        if (i == targetIndex) {
            newNode->element = term;
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

int addBeforeNode(struct Node* header, int targetIndex, struct Term term, struct Node* newNode) {
    if (header == NULL || newNode == NULL) {
        printf("Pogreska u addBeforeNode (NULL pokazivac)!\n");
        return 1;
    }

    struct Node* pointer = header;
    int i = 0;
    while (pointer->next != NULL) {
        if (i == targetIndex) {
            newNode->element = term;
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

struct Node* readListFromFile(FILE* file) {
    if (file == NULL) {
        printf("Greska: datoteka nije otvorena!\n");
        return NULL;
    }

    struct Node* header = createNode();
    if (header == NULL)
        return NULL;

    int id = 0;
    struct Term term;
    while (fscanf_s(file, "%f %f", &term.coeff, &term.exp) == 2)
    {
        addToEnd(header, term, createNode());
    }

    return header;
}

int addSortedNode(struct Node* header, struct Term term, struct Node* newNode) {
    if (header == NULL || newNode == NULL)
    {
        printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
        return 1;
    }

    struct Node* current = header;
    while (current->next != NULL) {
        if (term.exp >= current->next->element.exp)
            break;
        current = current->next;
    }

    newNode->element = term;
    newNode->next = current->next;
    current->next = newNode;

    return 0;
}

FILE* fileInput() {
    FILE* file = NULL;
    printf("Unesi ime datoteke polinoma: ");
    char fileName[40] = "";
    scanf_s(" %s", fileName, 40);

    fopen_s(&file, fileName, "r+");

    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke!\n");
    }
    return file;
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

int tidyPolynomial(struct Node** header) {
    if (header == NULL || *header == NULL)
    {
        printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
        return 1;
    }
    if ((*header)->next == NULL) {
        printf("Lista je prazna!");
        return 0;
    }
    sortPolynomial(header);

    struct Node* newHeader = createNode();
    if (newHeader == NULL)
        return 2;

    struct Node* current = (*header)->next;

    struct Node* newNode = NULL;

    struct Term temp = { current->element.coeff, current->element.exp };

    while (current != NULL)
    {
        if (current->next != NULL && current->next->element.exp == current->element.exp)
            temp.coeff += current->next->element.coeff;
        else {
            newNode = createNode();
            if (newNode == NULL)
                return 2;
            temp.exp = current->element.exp;
            addSortedNode(newHeader, temp, newNode);
            if(current->next != NULL)
                temp.coeff = current->next->element.coeff;
        }
        current = current->next;
    }

    deleteList(*header);
    *header = newHeader;
    return 0;
}

struct Node* joinLists(struct Node** headers, unsigned short arr_length) {
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
            addToStart(newHeader, current->element, newNode);
            current = current->next;
        }
    }
    return newHeader;
}

struct Node* multiplyPolynomials(struct Node** headers, unsigned short arr_length) {
    if (headers == NULL)
    {
        printf("Greska prilikom ucitavanja niza! (Pokazivac NULL)");
        return NULL;
    }
    if (arr_length < 2) {
        printf("Nije moguce mnoziti bez min. 2 polinoma!");
        return NULL;
    }
    struct Node* newHeader = createNode();
    if (newHeader == NULL) {
        printf("Greska prilikom alokacije cvora! (multiplyPolynomials)");
        return NULL;
    }
    
    struct Node* newNode = NULL;
    struct Node* currI = NULL;
    struct Node* currJ = NULL;

    struct Term temp = { 0, 0 };

    for (int i = 1; i < arr_length; i++)
    {
        currI = headers[0]->next;
        while(currI != NULL) {
            currJ = headers[i]->next;
            while (currJ != NULL) {
                newNode = createNode();
                if (newNode == NULL) {
                    printf("Greska prilikom alokacije cvora! (multiplyPolynomials)");
                    deleteList(newHeader);
                    free(newHeader);
                    return NULL;
                }
                temp.coeff = currI->element.coeff * currJ->element.coeff;
                temp.exp = currI->element.exp + currJ->element.exp;
                addToStart(newHeader, temp, newNode);
                currJ = currJ->next;
            }
            currI = currI->next;
        }
    }

    if (tidyPolynomial(&newHeader) != 0)
        return NULL;
    return newHeader;
}

int main() {
    short n = 0;

    do
    {
        printf("Unesi broj polinoma nad kojim ce se vrsiti neka operacija: ");
        scanf_s(" %hd", &n);
    } while (n <= 0);

    FILE** files = malloc(sizeof(FILE*) * n);
    struct Node** headers = malloc(sizeof(struct Node*) * n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", i + 1);
        files[i] = fileInput();
        if (files[i] == NULL)
            i--;
    }

    char input = '0';
    do
    {
        for (int i = 0; i < n; i++)
        {
            headers[i] = readListFromFile(files[i]);
            if (headers[i] == NULL) {
                printf("Pogreska prilikom citanja liste iz datoteke!");
                return 1;
            }
        }

        printf("\nUnesi znak za trazenu radnju:\n+) Zbrajanje polinoma *) Mnozenje polinoma x) Prekid programa\n");
        scanf_s(" %c", &input, 1);



        switch (input)
        {
        case '+': {
            
            struct Node* joinedListHeader = joinLists(headers, n);
            if (joinedListHeader == NULL)
                break;
            if (tidyPolynomial(&joinedListHeader) == 0) {
                printf("Rezultat zbrajanja je: ");
                printLinkedList(joinedListHeader);
            }
            deleteList(joinedListHeader);
            free(joinedListHeader);
            printf("\n");
            break;
        }
        case '*': {
            struct Node* outputHeader = multiplyPolynomials(headers, n);
            if (outputHeader != NULL) {
                printLinkedList(outputHeader);
                deleteList(outputHeader);
                free(outputHeader);
            }
            break;
        }
        default:
            break;
        }

    } while (input != 'x');

    for (int i = 0; i < n; i++)
    {
        if (files[i] != NULL)
            fclose(files[i]);
        if (headers[i] != NULL) {
            deleteList(headers[i]);
            free(headers[i]);
        }
    }
    free(files);
    free(headers);
    return 0;

}
