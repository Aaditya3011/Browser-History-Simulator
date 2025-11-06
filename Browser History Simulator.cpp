#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 100

// Doubly linked list node structure
typedef struct Node {
    char url[MAX_URL];
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(newNode->url, url, MAX_URL - 1);
    newNode->url[MAX_URL - 1] = '\0';
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to visit a new page
Node* visit(Node* current, const char* url) {
    Node* newNode = createNode(url);
    // Delete forward history
    if (current) {
        Node* temp = current->next;
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        current->next = newNode;
        newNode->prev = current;
    }
    printf("\nVisited: %s\n", url);
    return newNode;
}

// Function to go back
Node* goBack(Node* current) {
    if (current && current->prev) {
        current = current->prev;
        printf("\nWent back to: %s\n", current->url);
    } else {
        printf("\nNo previous page.\n");
    }
    return current;
}

// Function to go forward
Node* goForward(Node* current) {
    if (current && current->next) {
        current = current->next;
        printf("\nWent forward to: %s\n", current->url);
    } else {
        printf("\nNo next page.\n");
    }
    return current;
}

// Function to show full browsing history
void showHistory(Node* head) {
    if (!head) {
        printf("\nHistory is empty.\n");
        return;
    }
    printf("\n=== Browser History ===\n");
    Node* temp = head;
    int count = 1;
    while (temp) {
        printf("%d. %s\n", count++, temp->url);
        temp = temp->next;
    }
}

// Function to free memory
void freeHistory(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    Node* current = NULL;
    int choice;
    char url[MAX_URL];

    printf("=== Browser History Simulator ===\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Visit new page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Show current page\n");
        printf("5. Show full history\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                fgets(url, MAX_URL, stdin);
                url[strcspn(url, "\n")] = 0; // remove newline
                current = visit(current, url);
                if (!head) head = current;
                break;
            case 2:
                current = goBack(current);
                break;
            case 3:
                current = goForward(current);
                break;
            case 4:
                if (current)
                    printf("\nCurrent page: %s\n", current->url);
                else
                    printf("\nNo page visited yet.\n");
                break;
            case 5:
                showHistory(head);
                break;
            case 6:
                freeHistory(head);
                printf("\nExiting... Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}
