#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "secret_defs.h"

typedef struct Node {
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

// Initialize a new empty list
DoublyLinkedList* createList() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Add element to the end of the list. The application must allocate the node.
void addElement(DoublyLinkedList* list, Node* newNode) {
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
}

// Insert element before a specific element. Both nodes are allocated by the application.
void insertBefore(DoublyLinkedList* list, Node* nextNode, Node* newNode) {
    if (list->head == NULL || nextNode == NULL) return;

    newNode->next = nextNode;
    newNode->prev = nextNode->prev;

    if (nextNode->prev != NULL) {
        nextNode->prev->next = newNode;
    } else {
        list->head = newNode;
    }
    nextNode->prev = newNode;
}

// Remove element from the list and return the removed node instead of freeing it.
Node* removeElement(DoublyLinkedList* list, Node* nodeToRemove) {
    if (nodeToRemove == NULL) return NULL;

    if (nodeToRemove->prev != NULL) {
        nodeToRemove->prev->next = nodeToRemove->next;
    } else {
        list->head = nodeToRemove->next;
    }

    if (nodeToRemove->next != NULL) {
        nodeToRemove->next->prev = nodeToRemove->prev;
    } else {
        list->tail = nodeToRemove->prev;
    }

    nodeToRemove->next = nodeToRemove->prev = NULL;
    return nodeToRemove;
}

// Replace a node with another in the list. Both nodes are allocated by the application.
void replaceElement(DoublyLinkedList* list, Node* oldNode, Node* newNode) {
    newNode->prev = oldNode->prev;
    newNode->next = oldNode->next;

    if (oldNode->prev != NULL) {
        oldNode->prev->next = newNode;
    } else {
        list->head = newNode;
    }

    if (oldNode->next != NULL) {
        oldNode->next->prev = newNode;
    } else {
        list->tail = newNode;
    }

    oldNode->next = oldNode->prev = NULL; // Detach the old node from the list
}

typedef struct AnimalStruct {
    Node node; // This allows Animal to be part of a doubly linked list
    char* name;
    const char* species;
    int age;
} Animal;

// Function to create a new Animal
Animal* createAnimal(const char* name, const char* species, int age) {
    Animal* newAnimal = (Animal*)malloc(sizeof(Animal));
    if (newAnimal == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newAnimal->name = strdup(name); 
    newAnimal->species = species;
    newAnimal->age = age;
    return newAnimal;
}

// Function to free an Animal
void freeAnimal(Animal* animal) {
    if (animal != NULL) {
        free(animal);
    }
}

// Function to print an Animal's details
void printAnimal(Animal* animal) {
    if (animal != NULL) {
        printf("Name: %s, Species: %s, Age: %d\n", animal->name, animal->species, animal->age);
    }
}

// Utility function to print the list of Animals
void printAnimals(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Animal* animal = (Animal*)temp; // Cast Node back to Animal
        printAnimal(animal);
        temp = temp->next;
    }
}

// Find an animal by its name
Animal* findAnimalByName(DoublyLinkedList* list, const char* name) {
    Node* current = list->head;
    while (current != NULL) {
        Animal* animal = (Animal*)current;
        if (strcmp(animal->name, name) == 0) {
            return animal;
        }
        current = current->next;
    }
    return NULL; // Not found
}

// Rename an existing animal
void renameAnimal(Animal* animal, const char* newName) {
    if (animal != NULL) {
        animal->name = strdup(newName); // Assign the new name
    }
}


// Add more animals to the zoo
void populateZoo(DoublyLinkedList* list) {
    const char* species[] = {"Lion", "Tiger", "Bear", "Giraffe", "Elephant"};
    const char* names[] = {"Leo", "Tigger", "Baloo", "Gerry", "Ellie",
                           "Simba", "Rajah", "Yogi", "Melman", "Dumbo",
                           "Nala", "Shere Khan", "Boo Boo", "Geoffrey", "Babar",
                           "Mufasa", "Kaa", "Paddington", "Twiga", "Horton",
                           "Scar", "Bagheera", "Winnie", "Gemma", "Stampy"};
    int ages[] = {5, 3, 7, 4, 10, 2, 6, 8, 1, 9, 4, 5, 6, 3, 7, 8, 9, 2, 10, 1, 3, 4, 5, 6, 7};

    for (int i = 0; i < 25; ++i) {
        Animal* animal = createAnimal(names[i], species[i % 5], ages[i]);
        addElement(list, (Node*)animal);
    }
}

// Simulate births in the zoo
void simulateBirths(DoublyLinkedList* list) {
    Animal* babyLion = createAnimal("Kiara", "Lion", 0);
    Animal* babyElephant = createAnimal("Kopa", "Elephant", 0);
    addElement(list, (Node*)babyLion);
    addElement(list, (Node*)babyElephant);
}

// Simulate deaths in the zoo
void simulateDeaths(DoublyLinkedList* list) {
    // For simplicity, remove the first and last animals
    Animal* firstAnimal = (Animal*)removeElement(list, list->head);
    Animal* lastAnimal = (Animal*)list->tail; // Remember the last animal before iteration
    Node* current = list->head;
    while (current != NULL && current->next != (Node*)lastAnimal) {
        current = current->next;
    }
    Animal* secondLastAnimal = (Animal*)removeElement(list, current);

    freeAnimal(firstAnimal);
    freeAnimal(secondLastAnimal);
}

int main() {
    DoublyLinkedList* list = createList();
    
    printf("Using %ld bytes before populating zoo\n",mallinfo2().uordblks);
    populateZoo(list);
    
    printf("Initial Zoo:\n");
    printAnimals(list);

    simulateBirths(list);
    printf("\nAfter Births:\n");
    printAnimals(list);

    Animal* foundAnimal = findAnimalByName(list, "Leo");
    if (foundAnimal != NULL) {
        renameAnimal(foundAnimal, "Leonardo");
        printf("\nAfter renaming Leo:\n");
        printAnimals(list);
    } else {
        printf("\nAnimal 'Leo' not found.\n");
    }    

    simulateDeaths(list);
    printf("\nAfter Deaths:\n");
    printAnimals(list);
    printf("Using %ld bytes before cleaning up.\n",mallinfo2().uordblks);

    while (list->head != NULL) {
        removeElement(list, list->head);
    }
    free(list);
    printf("Using %ld bytes after cleaning up\n",mallinfo2().uordblks);
    return 0;
}

