
// Github URl: https://github.com/saraho-mar/Car-Showroom


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure for customising the car features
typedef struct {
    bool hasCustomWheels; //if the car has custom wheels
    bool hasLeatherSeats; //if the car has leather seats 
    bool hasSoundSystemUpgrade; //in the car has a sound upgarde system
} CustomizationOptions;

// Definition of the main Car structure
typedef struct 
{
    char registration[10]; // This puts it in the format of yyDxnnnn
    char makeAndModel[50]; //car make and model
    char colour[20]; // colour of car
    int previousOwners; // number of previous owners
    bool isReserved; // indicates if the car is reserved 
    CustomizationOptions customization; //options for customisation for the car 
    float reserveAmount; // the reservation amount 
} Car;

// This is the Node for the linked list of cars
typedef struct Node 
{
    Car car; //car object
    struct Node* next;  //pointer to the next node n the list 
} Node;

// function to validate car registration format
bool isValidRegistration(const char* reg) 
{
    // Validation that ensures the date is in the correct format 
    return strlen(reg) == 8 && reg[2] == 'D' && (reg[3] == '1' || reg[3] == '2');
}

// Function to add a new car to the showroom
void addCar(Node** head)
 {
    Node* newNode = (Node*)malloc(sizeof(Node)); //this allocates memory for a new node
    if (newNode == NULL) 
    {
        printf("Memory allocation failed."); // memory allocation error
        return;
    }

    // Initialize the new node to null
    newNode->next = NULL;

    printf("Enter car registration (yyDxnnnn): "); //input car registration 
    scanf("%9s", newNode->car.registration);

    if (!isValidRegistration(newNode->car.registration))  //this is validation for the registration format
    {
        printf("Invalid registration format.");
        free(newNode); //this frees the allocated node if it is invalid 
        return;
    }

    printf("Enter car make and model: "); //input car make and model
    scanf(" %[^\n]", newNode->car.makeAndModel); // Read it until the newline is encountered

    printf("Enter car colour: "); // input colour
    scanf(" %[^\n]", newNode->car.colour);

    printf("Enter number of previous owners (0-3): "); //input previous owners
    scanf("%d", &newNode->car.previousOwners);
    //this checks for the valid number of previous owners 
    if (newNode->car.previousOwners < 0 || newNode->car.previousOwners > 3) 
    {
        printf("Invalid number of previous owners.");
        free(newNode);
        return;
    }

// input reservation status
    printf("Is the car reserved? (0 for no, 1 for yes): ");
    int isReserved;
    scanf("%d", &isReserved);
    newNode->car.isReserved = isReserved ? true : false;

// if it is reserved input the reserve amount 
    if (newNode->car.isReserved) 
    {
        printf("Enter reserve amount (500-1500): ");
        scanf("%f", &newNode->car.reserveAmount);
        // validates the reserve amount 
        if (newNode->car.reserveAmount < 500.0 || newNode->car.reserveAmount > 1500.0) 
        {
            printf("Invalid reserve amount.");
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

    printf("Car added successfully.");
}

// Function to sell a car from the showroom
void sellCar(Node** head) 
{
    //if no cars are present this informs them that the showrom is empty 
    if (head == NULL || *head == NULL) 
    {
        printf("There are no cars in the showroom.");
        return;
    }

    char registration[10]; // stores cars registration number for selling
    printf("Enter the registration of the car to sell: ");
    scanf("%9s", registration); // read reg input

    Node *current = *head, *prev = NULL; //initiliase pointers for current node and previous node
    while (current != NULL) { // loop through the linkedlist to find the car
      //if the car is found break 
        if (strcmp(current->car.registration, registration) == 0) {
            break; // exits loop
        }
        prev = current; // move to the current node 
        current = current->next; // move to the next node 
    }

    // Car not found
    if (current == NULL) {
        printf("Car with registration %s not found in the showroom.", registration);
        return;
    }

    // Check if the car is reserved
    if (!current->car.isReserved) {
        printf("Car with registration %s has not been reserved and cannot be sold.", registration);
        return;
    }

    // Car is found and reserved; proceed to sell (delete it from the list)
    if (prev == NULL) {
        // The car that will be sold is the first car in the list
        *head = current->next;
    } else {
        // The car that will be sold is not the first car
        prev->next = current->next;
    }

    printf("Car with registration %s has been sold.", registration);
    free(current); 
}



 // Function to reserve or unreserve a car
void reserveUnreserveCar(Node** head) {
    if (head == NULL || *head == NULL) {
        printf("There are no cars in the showroom./n"); //list is empty
        return;
    }

    char registration[10]; // To store the car's registration number for reservation changes
    printf("Enter the registration of the car to reserve/unreserve: ");
    scanf("%9s", registration); // Read the registration input

    Node *current = *head; // Initialize pointer for the current node
    while (current != NULL) { // Loop through the linked list to find the car
        if (strcmp(current->car.registration, registration) == 0) {
            // Found the car
            if (current->car.isReserved) {
                printf("Car is currently reserved. Unreserving it now.");
                current->car.isReserved = false; // Change status to unreserved
                current->car.reserveAmount = 0.0; // Reset the reserve amount
            } else {
                printf("Car is currently not reserved. Reserving it now.");
                current->car.isReserved = true;
                printf("Enter reserve amount (500-1500): "); // ask for reserve amount
                scanf("%f", &current->car.reserveAmount);
                if (current->car.reserveAmount < 500.0 || current->car.reserveAmount > 1500.0) {
                    printf("Invalid reserve amount. Cancelling the reservation.");
                    current->car.isReserved = false; // revert reservation status 
                    current->car.reserveAmount = 0.0; // reset reservation amount
                }
            }
            return;
        }
        current = current->next; // move to the next node
    }

    printf("Car with registration %s not found in the showroom.", registration); // car is not found 
}

// Function to view all cars in the showroom
void viewCars(Node* head) {
    if (head == NULL) 
    {
        printf("The showroom is currently empty.");
        return;
    }

    printf("List of all cars in the showroom:\n");
    while (head != NULL) {
        printf("Registration: %s\n", head->car.registration); // car registration 
        printf("Make and Model: %s\n", head->car.makeAndModel); // car make and model 
        printf("Colour: %s\n", head->car.colour); // car colour 
        printf("Previous Owners: %d\n", head->car.previousOwners); // preious owners
        printf("Reserved: %s\n", head->car.isReserved ? "Yes" : "No"); // reserved or not 
        // if the car is reserved 
        if (head->car.isReserved) {
            printf("Reserve Amount: %.2f\n", head->car.reserveAmount);
        }
        printf("\n"); //This adds an extra line between the cars displayed which makes it mor readable/aesthetic 

        head = head->next; // Move to the next car in the list
    }
}


 // Function to view a specific car in the showroom
void viewSpecificCar(Node* head) {
    if (head == NULL) {
        printf("There are no cars in the showroom.\n"); // tell user showrrom is empty 
        return;
    }

    char registration[10]; // Variable for car registration
    printf("Enter the registration of the car you want to view: ");
    scanf("%9s", registration); // Read input

    Node* current = head; // Start at the beginning of the list
    while (current != NULL) { // Loop through the list
        if (strcmp(current->car.registration, registration) == 0) { // If the car is found
            // display details
            printf("\nCar Details:\n");
            printf("Registration: %s\n", current->car.registration);
            printf("Make and Model: %s\n", current->car.makeAndModel);
            printf("Colour: %s\n", current->car.colour);
            printf("Previous Owners: %d\n", current->car.previousOwners);
            printf("Reserved: %s\n", current->car.isReserved ? "Yes" : "No");
            if (current->car.isReserved) {
                printf("Reserve Amount: %.2f\n", current->car.reserveAmount); // Show reserve amount if reserved
            }
            return; // End function after displaying details
        }
        current = current->next; // Move to next node
    }

    printf("Car with registration %s not found in the showroom.\n", registration); // Inform if car not found
}

// New function to customize a car
void customizeCar(Node* head) {
    if (head == NULL) {
        printf("There are no cars in the showroom.\n");
        return;
    }

    char registration[10]; // Variable for car registration
    printf("Enter the registration of the car to customize: ");
    scanf("%9s", registration); // Read input

    Node *current = head; // Start at the beginning of the list
    while (current != NULL) { // Loop through the list
        if (strcmp(current->car.registration, registration) == 0) { // If the car is found
           // ask user what customisations they would like 
            printf("Customizing car: %s\n", registration);
            printf("Custom Wheels (0 for No, 1 for Yes): ");
            scanf("%d", &current->car.customization.hasCustomWheels);
            printf("Leather Seats (0 for No, 1 for Yes): ");
            scanf("%d", &current->car.customization.hasLeatherSeats);
            printf("Sound System Upgrade (0 for No, 1 for Yes): ");
            scanf("%d", &current->car.customization.hasSoundSystemUpgrade);

            printf("Car customization updated successfully.\n"); // message confirming custmisation 
            return;
        }
        current = current->next;
    }

    printf("Car with registration %s not found in the showroom.\n", registration);
}


 

// Main function
int main() {
    Node* head = NULL; // This is the head of the linked list initialised as NULL
    int choice; // Variable for user menu choice

    do {
        // Display menu options
        printf("\nCar Showroom System Menu:\n");
        printf("1. Add a new car\n");
        printf("2. Sell a car\n");
        printf("3. Reserve/Unreserve a car\n");
        printf("4. View all cars\n");
        printf("5. View a specific car\n");
         printf("6. Customize a car\n"); 
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // read the users choice 
        getchar(); // Newline character 

// Process user choice
        switch (choice) {
            case 1:
                addCar(&head);
                break;
             case 2:
                sellCar(&head); 
                break;
           case 3:
                reserveUnreserveCar(&head);
                break;
             case 4:
                viewCars(head);
                break;
            case 5:
                viewSpecificCar(head);
                break; 
            case 6:
                customizeCar(head); 
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 7);
    
    
    return 0;
}
