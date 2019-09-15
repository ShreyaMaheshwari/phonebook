#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char all_num[100][20];
char all_name[100][20];
int k = 1;

typedef struct tNode {
    struct tNode *children[26];
    int endofword[10];
    int index;
}node;

typedef struct tNode1 {
    struct tNode1 *children[10];
    int endofnum[10];
    int index;
}node1;

node* getNewNode() {
    node *newNode = (node*) malloc(sizeof(node));
    newNode -> index = 0;
    int i = 0;
    for(i = 0; i < 10; i++) {
        newNode -> endofword[i] = 0;
    }
    for(i = 0; i < 26; i++) {
        newNode -> children[i] = NULL;
    }
    return newNode;
}

node1* getNewNode1() {
    node1 *newNode = (node1*) malloc(sizeof(node1));
    newNode -> index = 0;
    int i = 0;
    for(i = 0; i < 10; i++) {
        newNode -> endofnum[i] = 0;
    }
    for(i = 0; i < 10; i++) {
        newNode -> children[i] = NULL;
    }
    return newNode;
}

void insert(node* root, char *key, int xx) {
    int len = strlen(key);
    node *x = root;
    int index;
    for(int i = 0; i < len; i++) {
            index = ((int)key[i] - (int)'a');
            if(x -> children[index] == NULL) {
                x -> children[index] = getNewNode();
        }
        x = x -> children[index];
    }
    x -> endofword[x -> index] = xx;
    x -> index += 1;
}

void insert1(node1* root, char *key, int xx) {
    int len = strlen(key);
    node1 *x = root;
    int index;
    for(int i = 0; i < len; i++) {
        index = ((int)key[i] - (int)'0');
        if(x -> children[index] == NULL) {
            x -> children[index] = getNewNode1();
        }
        x = x -> children[index];
    }
    x -> endofnum[x -> index] = xx;
    x -> index += 1;
}

void displaycontacts(node *root ,char* query) {
    node *prevNode = root;
    char prefix[100];
    int l = 1;
    memset(prefix, '\0', sizeof(prefix));
    int len = strlen(query);
    int i = 0;
    for(i = 0; i < len; i++) {
        prefix[l-1] = query[i];
        l = l + 1;
        printf("Suggestions for %s:\n", prefix);
        char lastchar = query[i];
        node *curr = prevNode -> children[(int)lastchar - 'a'];
        if(curr == NULL)
            break;
        displaycontactsuntil(curr, prefix);
        prevNode = curr;
    }
    while(i < len) {
        printf("No results found\n");
        if(i == (len - 1)) break;
        i = i + 1;
        prefix[l-1] = query[i];
        l = l + 1;
        printf("Suggestions for %s:\n", prefix);
    }
}

void displayall(node *root, char* query) {
        node *prevNode = root;
        char prefix[2];
        int l = 1;
        memset(prefix, '\0', sizeof(prefix));
        int len = strlen(query);
        int i = 0;
        for(i = 0; i < len; i++) {
            prefix[0] = *query;
        char lastchar = *query;
        node *curr = prevNode -> children[(int)lastchar - 'a'];
        if(curr == NULL)
            break;
        displaycontactsuntil(curr, prefix);
        prevNode = curr;
    }
}

void displaycontactsuntil(node *curr, char *prefix) {
    if(curr -> index != 0) {
        for(int i = 0; i < curr -> index; i++) {
            printf("%s %s\n", all_name[curr -> endofword[i]], all_num[curr -> endofword[i]]);
        }
    }
    for(int i = 0; i < 26; i++) {
        node *next = curr -> children[i];
        if(next != NULL) {
            char *n[100];
            memset(n, '\0', strlen(n));
            strncpy(n, prefix, strlen(prefix));
            n[strlen(prefix)] = 'a';
            displaycontactsuntil(next, n);
        }
    }
    return;
}

void displaycontacts1(node1 *root ,char* query) {
    node1 *prevNode = root;
    char prefix[100];
    int l = 1;
    memset(prefix, '\0', sizeof(prefix));
    int len = strlen(query);
    int i = 0;
    for(i = 0; i < len; i++) {
        prefix[l-1] = query[i];
        l = l + 1;
        printf("Suggestions for %s:\n", prefix);
        char lastchar = query[i];
        node1 *curr = prevNode -> children[(int)lastchar - '0'];
        if(curr == NULL)
            break;
        displaycontactsuntil1(curr, prefix);
        prevNode = curr;
    }
    while(i < len) {
        printf("No results found\n");
        if(i == (len - 1)) break;
        i = i + 1;
        prefix[l-1] = query[i];
        l = l + 1;
        printf("Suggestions for %s:\n", prefix);
    }
}

void displaycontactsuntil1(node1 *curr, char *prefix) {
    if(curr -> index != 0) {
        for(int i = 0; i < curr -> index; i++) {
            printf("%s %s\n", all_name[curr -> endofnum[i]], all_num[curr -> endofnum[i]]);
        }
    }
    for(int i = 0; i < 10; i++) {
        node1 *next = curr -> children[i];
        if(next != NULL) {
            char *n[100];
            memset(n, '\0', strlen(n));
            strncpy(n, prefix, strlen(prefix));
            n[strlen(prefix)] = '0';
            displaycontactsuntil1(next, n);
        }
    }
    return;
}

int main() {
    node *root = getNewNode();
    node1 *root1 = getNewNode1();
    int choice;
while(1) {
        printf("Enter your choice:\n");
        printf("1. Enter new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for existing contact according to name\n");
        printf("4. Search for existing contact according to number\n");
        printf("5. Exit\n");
        scanf("%d", &choice);
        switch(choice) {
        case 1:
                    printf("Enter name: ");
                    char name[100];
                    scanf("%s", name);
                    printf("Enter number: ");
                    char num[100];
                    scanf("%s", num);
                    if(strlen(num) != 10) {
                        printf("Invalid number\nInsertion unsuccessful\n");
                    }
                    else {
                    insert(root, name, k);
                    insert1(root1, num, k);

                    strcpy(all_num[k], num);
                    strcpy(all_name[k],name);

                    k = k + 1;
                    }
                    break;

        case 2:
                    ;
                    char x;
                    for(int i = 0; i < 26; i++) {
                            x = (char)'a' + i;
                            displayall(root, &x);
                    }
                    break;
        case 3:
                    printf("Enter search query: ");
                    char s[100];
                    scanf("%s", s);
                    displaycontacts(root, s);
                    break;

        case 4:
                    printf("Enter search query: ");
                    char t[100];
                    scanf("%s", t);
                    displaycontacts1(root1, t);
                    break;
        case 5:
                    exit(0);
                    break;
        default:
                    printf("Invalid choice\n");
        }
    }
}

