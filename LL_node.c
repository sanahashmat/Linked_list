//add node in front, end & between, search node & delete from between

#include <stdio.h>
#include <stdlib.h>

// Self-referential structure
struct NODE {
    int data;
    struct NODE *next;  
};

// Function to create a new node
struct NODE* createNode(int value) {
    struct NODE *newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at front
struct NODE* insertFront(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    newNode->next = head;
    return newNode;
}

// Insert at end
struct NODE* insertEnd(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    if (head == NULL) {
        return newNode;
    }
    struct NODE *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Insert in between at specific position
struct NODE* insertAtPosition(struct NODE *head, int value, int pos) {
    if (pos == 1) {
        return insertFront(head, value);
    }

    struct NODE *newNode = createNode(value);
    struct NODE *temp = head;
    int i;

    for (i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

// Search a specific node
void searchNode(struct NODE *head, int key) {
    struct NODE *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            printf("Node %d found at position %d\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Node %d not found!\n", key);
}

// Delete node from between
struct NODE* deleteAtPosition(struct NODE *head, int pos) {
    if (head == NULL) {
        printf("List is empty!\n");
        return head;
    }

    if (pos == 1) {
        struct NODE *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct NODE *temp = head;
    int i;

    for (i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position!\n");
        return head;
    }

    struct NODE *del = temp->next;
    temp->next = del->next;
    free(del);

    return head;
}

// Display the list
void display(struct NODE *head) {
    struct NODE *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    struct NODE *head = NULL;
    int n, value, pos, key;

    printf("How many nodes? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        head = insertEnd(head, value);
    }

    printf("\nInitial Linked List:\n");
    display(head);

    // Insert at front
    printf("\nEnter value to insert at front: ");
    scanf("%d", &value);
    head = insertFront(head, value);
    display(head);

    // Insert at end
    printf("\nEnter value to insert at end: ");
    scanf("%d", &value);
    head = insertEnd(head, value);
    display(head);

    // Insert at position
    printf("\nEnter value and position to insert: ");
    scanf("%d %d", &value, &pos);
    head = insertAtPosition(head, value, pos);
    display(head);

    // Search for a node
    printf("\nEnter value to search: ");
    scanf("%d", &key);
    searchNode(head, key);

    // Delete from position
    printf("\nEnter position to delete node: ");
    scanf("%d", &pos);
    head = deleteAtPosition(head, pos);
    display(head);

    return 0;
}