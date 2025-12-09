// func to create node,insert node in front,node bn 2 node,print node,search node,delete node

#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to search for a node with a given value
struct Node* searchNode(struct Node* head, int value) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current; // Node found
        }
        current = current->next;
    }
    return NULL; // Node not found
}

// Function to add a node in between two existing nodes
struct Node* addNodeInBetween(struct Node* head, int data, int prevValue) {
    struct Node* newNode = createNode(data);
    struct Node* current = head;

    while (current != NULL && current->data != prevValue) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Previous node with value %d not found. Cannot insert.\n", prevValue);
        free(newNode); // Free allocated memory if not inserted
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Function to delete a node with a given value
struct Node* deleteNode(struct Node* head, int value) {
    struct Node* current = head;
    struct Node* prev = NULL;

    // If head node itself holds the value to be deleted
    if (current != NULL && current->data == value) {
        head = current->next;
        free(current);
        return head;
    }

    // Search for the node to be deleted, keeping track of the previous node
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    // If value was not present in linked list
    if (current == NULL) {
        printf("Node with value %d not found. Cannot delete.\n", value);
        return head;
    }

    // Unlink the node from the linked list
    prev->next = current->next;
    free(current);
    return head;
}

// Function to delete a node from a specific position (0-indexed)
struct Node* deleteNodeFromPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }

    struct Node* temp = head;

    // If head needs to be removed
    if (position == 0) {
        head = temp->next;
        free(temp);
        return head;
    }

    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds. Cannot delete.\n");
        return head;
    }

    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    struct Node* nextNode = temp->next->next;
    free(temp->next); // Free memory
    temp->next = nextNode; // Unlink the deleted node

    return head;
}

int main() {
    struct Node* head = NULL;

    head = insertAtBeginning(head, 30);
    head = insertAtBeginning(head, 20);
    head = insertAtBeginning(head, 10);

    printf("Original Linked List: ");
    printList(head);

    // Search for a node
    int searchValue = 20;
    struct Node* foundNode = searchNode(head, searchValue);
    if (foundNode != NULL) {
        printf("Node with value %d found.\n", searchValue);
    } else {
        printf("Node with value %d not found.\n", searchValue);
    }

    // Add a node in between
    head = addNodeInBetween(head, 25, 20);
    printf("Linked List after adding 25 after 20: ");
    printList(head);

    // Delete a node
    head = deleteNode(head, 10);
    printf("Linked List after deleting 10: ");
    printList(head);

    // Delete a node from between (e.g., at position 1)
    head = deleteNodeFromPosition(head, 1);
    printf("Linked List after deleting node at position 1: ");
    printList(head);

    // Free remaining nodes
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;

    return 0;

}
