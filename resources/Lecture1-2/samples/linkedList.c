#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data; 
    struct Node *next;
}Node;

Node * createNode(int data){
    Node * node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void deleteNode(Node *node){
    free(node);
}




typedef struct LinkedList{
    Node * head;
}LinkedList;


// traveses and prints the elements in the linked list
void traverse(LinkedList *l){
    Node *current = l->head;

    printf("HEAD -> ");

    // loop until current becomes NULL, ie, end of the list
    while (current){
        printf("%d  -> ", current->data);

        // go to the next node
        current = current->next;
    }
    printf("NULL\n");

}



void insertAtBeginning(LinkedList *l, int value){
    Node * newNode = createNode(value);

    // new node should be before the initial head node
    newNode->next = l->head;

    // then set head pointer to new node
    l->head = newNode;
}


void insertAtEnd(LinkedList *l, int value){
    Node * newNode = createNode(value);

    // if list is empty, ie, head is null 
    if (!l->head){
        l->head = newNode;
        return;
    }

    Node *current = l->head;
    // travese till the end
    while (current->next){
        current = current->next;
    }

    // set newnode as next of final node in list
    current->next = newNode;
}

void insertAtIndex(LinkedList *l, int value, int index){
    Node * newNode = createNode(value);

    // if list is empty, ie, head is null 
    if (!l->head){
        l->head = newNode;
        return;
    }

    // basically insert at beginning
    if (index == 0){
        newNode->next = l->head;
        l->head = newNode;
        return;
    }


    Node *current = l->head;
    int i = 0;

    // travese until current is (index-1)th element
    while (current->next != NULL && i< index - 1){
        current = current->next;
        i++;
    }

    // set the node at index to be next node of new node
    newNode->next = current->next;

    // set newnode as next of current node
    current->next = newNode;
}

void deleteAtBeginning(LinkedList *l){
    // if list is empty, do nothing
    if (!l->head){
        return;
    }
    
    // the node to delete
    Node *nodeToRemove = l->head;

    // head should point to the second node now
    l->head = nodeToRemove->next;

    // delete node
    deleteNode(nodeToRemove);
}


void deleteAtEnd(LinkedList *l){
    // if list is empty, do nothing 
    if (!l->head){
        return;
    }

    // if there is only one node, set head to NULL
    if (!l->head->next){
        deleteNode(l->head);
        l->head = NULL;
    }

    Node *current = l->head;
    Node *previous = NULL;          // previous node to current node

    // travese till the end
    while (current->next != NULL){
        previous = current;
        current = current->next;
    }

    // set next of previous node as NULL as were deleting the last node
    previous->next = NULL;

    deleteNode(current);
}

void deleteAtIndex(LinkedList *l, int index){
    // if list is empty, do nothing 
    if (!l->head){
        return;
    }

    // basically delete at beginning
    if (index == 0){
        deleteAtBeginning(l);
        return;
    }

    Node *current = l->head;
    int i = 0;

    // travese until current is (index - 1)th element
    while (current->next != NULL && i< index - 1){
        current = current->next;
        i++;
    }

    // if there is a index-th element to delete
    if (current->next){
        Node *nodeToRemove = current->next;
        
        // set the node at index+1 to be next of index-1 node
        current->next = nodeToRemove->next;

        deleteNode(nodeToRemove);
    }
}



int linkedListTest(){
    // init linked list with head = NULL
    LinkedList l = {0};

    insertAtBeginning(&l, 1);
    traverse(&l);
    insertAtBeginning(&l, 2);
    traverse(&l);
    insertAtEnd(&l, 3);
    traverse(&l);
    insertAtIndex(&l, 4, 2);
    traverse(&l);

    deleteAtBeginning(&l);
    traverse(&l);
    deleteAtEnd(&l);
    traverse(&l);
    deleteAtIndex(&l, 2);
    traverse(&l);
    deleteAtIndex(&l, 1);
    traverse(&l);
    return 0;
}


int main(){
    linkedListTest();
    return 0;
}

