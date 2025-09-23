// CH.SC.U4CSE24130
// Capstone Project: Fitness Tracker using Linked List

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char date[20];
    int steps;
    int calories;
    float distance;
    int active_minutes;
    struct Node *next;
} Node;

// Defining Head, Tail Pointers
typedef struct{
    Node *head;
    Node *tail;
} FitnessList;

// Function to create a new node
Node *createNode(char date[], int steps, int calories, float distance, int active_minutes){
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->date, date);
    newNode->steps = steps;
    newNode->calories = calories;
    newNode->distance = distance;
    newNode->active_minutes = active_minutes;
    newNode->next = NULL;
    return newNode;
}

// Insert node in sorted order by date
void sortedInsert(FitnessList *list, char date[], int steps, int calories, float distance, int active_minutes){
    Node *newNode = createNode(date, steps, calories, distance, active_minutes);
    // Case 1: Empty list OR insert before head
    if (list->head == NULL || strcmp(newNode->date, list->head->date) < 0){
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL){
            list->tail = newNode;
        }
        return;
    }
    Node *temp = list->head;
    // Traverse until we find the correct position
    while (temp->next != NULL && strcmp(temp->next->date, newNode->date) < 0){
        temp = temp->next;
    }
    // Insert node after 'temp'
    newNode->next = temp->next;
    temp->next = newNode;
    // Update tail if newNode is last
    if (newNode->next == NULL){
        list->tail = newNode;
    }
}

// Delete record by date
void deleteByDate(FitnessList *list, char date[]){
    Node *temp = list->head;
    Node *prev = NULL;
    while (temp != NULL && strcmp(temp->date, date) != 0){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Record with date %s not found.\n", date);
        return;
    }
    if (prev == NULL){
        // deleting head
        list->head = temp->next;
        if (temp == list->tail){
            list->tail = NULL; // list became empty
        }
    }
    else{
        prev->next = temp->next;
        if (temp == list->tail){
            list->tail = prev; // update tail if last node deleted
        }
    }
    free(temp);
    printf("Record with date %s deleted successfully.\n", date);
}

// Update record by date
void updateRecord(FitnessList *list, char date[]){
    Node *temp = list->head;
    while (temp != NULL && strcmp(temp->date, date) != 0){
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Record with date %s not found.\n", date);
        return;
    }
    printf("Updating record for %s\n", date);
    printf("Enter new Steps: ");
    scanf("%d", &temp->steps);
    printf("Enter new Calories: ");
    scanf("%d", &temp->calories);
    printf("Enter new Distance (km): ");
    scanf("%f", &temp->distance);
    printf("Enter new Active Minutes: ");
    scanf("%d", &temp->active_minutes);
    printf("Record for %s updated successfully.\n", date);
}

// Search record by date
void searchByDate(FitnessList list, char date[]){
    Node *temp = list.head;
    while (temp != NULL && strcmp(temp->date, date) != 0){
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Record with date %s not found.\n", date);
    }
    else{
        printf("Record found:\n");
        printf("Date: %s | Steps: %d | Calories: %d | Distance: %.2f km | Active Minutes: %d\n",
               temp->date, temp->steps, temp->calories, temp->distance, temp->active_minutes);
    }
}

// Display all records
void display(FitnessList list){
    if (list.head == NULL){
        printf("No records found.\n");
        return;
    }
    Node *temp = list.head;
    while (temp != NULL){
        printf("Date: %s | Steps: %d | Calories: %d | Distance: %.2f km | Active Minutes: %d\n",
               temp->date, temp->steps, temp->calories, temp->distance, temp->active_minutes);
        temp = temp->next;
    }
}

// Main function
int main(){
    printf("CH.SC.U4CSE24130\n");
    FitnessList fitnessList;
    fitnessList.head = NULL;
    fitnessList.tail = NULL;
    int choice;
    char date[20];
    int steps, calories, active_minutes;
    float distance;
    do{
        printf("\n===== Fitness Tracker Menu =====\n");
        printf("1. Add Fitness Record (Sorted by Date)\n");
        printf("2. Display All Records\n");
        printf("3. Delete Record by Date\n");
        printf("4. Update Record by Date\n");
        printf("5. Search Record by Date\n");
        printf("6. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            printf("Enter Date (YYYY-MM-DD): ");
            scanf("%s", date);
            printf("Enter Steps: ");
            scanf("%d", &steps);
            printf("Enter Calories: ");
            scanf("%d", &calories);
            printf("Enter Distance (km): ");
            scanf("%f", &distance);
            printf("Enter Active Minutes: ");
            scanf("%d", &active_minutes);
            sortedInsert(&fitnessList, date, steps, calories, distance, active_minutes);
            printf("Record added successfully (in sorted order).\n");
            break;

        case 2:
            printf("\n--- Fitness Records ---\n");
            display(fitnessList);
            break;

        case 3:
            printf("Enter Date to Delete (YYYY-MM-DD): ");
            scanf("%s", date);
            deleteByDate(&fitnessList, date);
            break;

        case 4:
            printf("Enter Date to Update (YYYY-MM-DD): ");
            scanf("%s", date);
            updateRecord(&fitnessList, date);
            break;

        case 5:
            printf("Enter Date to Search (YYYY-MM-DD): ");
            scanf("%s", date);
            searchByDate(fitnessList, date);
            break;
            
        case 6:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice...\n");
        }
    } while (choice != 6);
    return 0;
}



