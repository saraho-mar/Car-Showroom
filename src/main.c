#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definition of the Car structure
typedef struct 
{
    char registration[10]; // This puts it in the format of yyDxnnnn
    char makeAndModel[50];
    char colour[20];
    int previousOwners;
    bool isReserved;
    float reserveAmount;
} Car;

// This is the Node for the linked list
typedef struct Node 
{
    Car car;
    struct Node* next;
} Node;

// Helper function to validate car registration format
bool isValidRegistration(const char* reg) 
{
    // Validation that ensures the date is in the correct format 
    return strlen(reg) == 8 && reg[2] == 'D' && (reg[3] == '1' || reg[3] == '2');
}

// Function to add a new car to the showroom
void addCar(Node** head)
 {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }

    // Initialize the new node
    newNode->next = NULL;

    printf("Enter car registration (yyDxnnnn): ");
    scanf("%9s", newNode->car.registration);

    if (!isValidRegistration(newNode->car.registration)) 
    {
        printf("Invalid registration format.\n");
        free(newNode);
        return;
    }

    printf("Enter car make and model: ");
    scanf(" %[^\n]", newNode->car.makeAndModel); // Read it until the newline is encountered

    printf("Enter car colour: ");
    scanf(" %[^\n]", newNode->car.colour);

    printf("Enter number of previous owners (0-3): ");
    scanf("%d", &newNode->car.previousOwners);
    if (newNode->car.previousOwners < 0 || newNode->car.previousOwners > 3) 
    {
        printf("Invalid number of previous owners.\n");
        free(newNode);
        return;
    }

    printf("Is the car reserved? (0 for no, 1 for yes): ");
    int isReserved;
    scanf("%d", &isReserved);
    newNode->car.isReserved = isReserved ? true : false;

    if (newNode->car.isReserved) 
    {
        printf("Enter reserve amount (500-1500): ");
        scanf("%f", &newNode->car.reserveAmount);
        if (newNode->car.reserveAmount < 500.0 || newNode->car.reserveAmount > 1500.0) 
        {
            printf("Invalid reserve amount.\n");
            free(newNode);
            return;
        }
    } else 
    {
        newNode->car.reserveAmount = 0.0; // Make sure reserve amount is set to 0 for unreserved cars
    }

    // Insert the new node at the end of the list
    if (*head == NULL) 
    {
        // List is empty
        *head = newNode;
    } else 
    {
        // Finds the last node
        Node* current = *head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode; // this appends the new node 
    }

    printf("Car added successfully.\n");
}

// Function to sell a car from the showroom
void sellCar(Node** head) 
{
    if (head == NULL || *head == NULL) 
    {
        printf("There are no cars in the showroom.\n");
        return;
    }

    char registration[10];
    printf("Enter the registration of the car to sell: ");
    scanf("%9s", registration);

    Node *temp = *head, *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->car.registration, registration) == 0) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // Car not found
    if (temp == NULL) {
        printf("Car with registration %s not found in the showroom.\n", registration);
        return;
    }

    // Check if the car is reserved
    if (!temp->car.isReserved) {
        printf("Car with registration %s has not been reserved and cannot be sold.\n", registration);
        return;
    }

    // Car is found and reserved; proceed to sell (delete it from the list)
    if (prev == NULL) {
        // The car tat will be sold is the first car in the list
        *head = temp->next;
    } else {
        // The car that will be sold is not the first car
        prev->next = temp->next;
    }

    printf("Car with registration %s has been sold.\n", registration);
    free(temp); 
}



/* // Function to reserve or unreserve a car
void reserveUnreserveCar(Node** head) {
    
}

// Function to view all cars in the showroom
void viewCars(Node* head) {
    
}

// Function to view a specific car in the showroom
void viewSpecificCar(Node* head) {
   
}  */

// Main function
int main() {
    Node* head = NULL; // This is the head of the linked list
    int choice;

    do {
        printf("\nCar Showroom System Menu:\n");
        printf("1. Add a new car\n");
        printf("2. Sell a car\n");
        printf("3. Reserve/Unreserve a car\n");
        printf("4. View all cars\n");
        printf("5. View a specific car\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Newline character 

        switch (choice) {
            case 1:
                addCar(&head);
                break;
             case 2:
                sellCar(&head);
                break;
          /*  case 3:
                reserveUnreserveCar(&head);
                break;
            case 4:
                viewCars(head);
                break;
            case 5:
                viewSpecificCar(head);
                break; */ 
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 6);

    
    
    return 0;
}
