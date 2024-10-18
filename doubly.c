#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CarNode
{
    char model[100];
    char manufacturer[100];
    float price;
    struct CarNode *next;
    struct CarNode *prev;
};

struct CarNode *createCarNode(char *model, char *manufacturer, float price)
{
    struct CarNode *newNode = (struct CarNode *)malloc(sizeof(struct CarNode));
    strcpy(newNode->model, model);
    strcpy(newNode->manufacturer, manufacturer);
    newNode->price = price;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addCar(struct CarNode **head, char *model, char *manufacturer, float price)
{
    struct CarNode *newNode = createCarNode(model, manufacturer, price);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct CarNode *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteCar(struct CarNode **head, char *model)
{
    if (*head == NULL)
        return;
    struct CarNode *temp = *head;

    while (temp != NULL && strcmp(temp->model, model) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Car model '%s' not found.\n", model);
        return;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {

        *head = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Car model '%s' deleted successfully.\n", model);
}

// Function to update car model data
void updateCar(struct CarNode *head, char *model, char *newManufacturer, float newPrice)
{
    struct CarNode *temp = head;

    while (temp != NULL && strcmp(temp->model, model) != 0)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Car model '%s' not found.\n", model);
        return;
    }

    strcpy(temp->manufacturer, newManufacturer);
    temp->price = newPrice;
    printf("Car model '%s' updated successfully.\n", model);
}

void displayCars(struct CarNode *head)
{
    struct CarNode *temp = head;
    if (temp == NULL)
    {
        printf("No cars available.\n");
        return;
    }
    printf("Car Models:\n");
    while (temp != NULL)
    {
        printf("Model: %s, Manufacturer: %s, Price: $%.2f\n", temp->model, temp->manufacturer, temp->price);
        temp = temp->next;
    }
}

int main()
{
    struct CarNode *head = NULL;
    int choice;
    char model[100], manufacturer[100];
    float price;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Add New Car Model\n");
        printf("2. Delete Car Model\n");
        printf("3. Update Car Model\n");
        printf("4. Display Car Models\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Enter car model: ");
            fgets(model, sizeof(model), stdin);
            model[strcspn(model, "\n")] = 0;
            printf("Enter manufacturer name: ");
            fgets(manufacturer, sizeof(manufacturer), stdin);
            manufacturer[strcspn(manufacturer, "\n")] = 0;
            printf("Enter price: ");
            scanf("%f", &price);
            addCar(&head, model, manufacturer, price);
            break;
        case 2:
            printf("Enter car model to delete: ");
            fgets(model, sizeof(model), stdin);
            model[strcspn(model, "\n")] = 0; // Remove newline character
            deleteCar(&head, model);
            break;
        case 3:
            printf("Enter car model to update: ");
            fgets(model, sizeof(model), stdin);
            model[strcspn(model, "\n")] = 0; // Remove newline character
            printf("Enter new manufacturer name: ");
            fgets(manufacturer, sizeof(manufacturer), stdin);
            manufacturer[strcspn(manufacturer, "\n")] = 0; // Remove newline character
            printf("Enter new price: ");
            scanf("%f", &price);
            updateCar(head, model, manufacturer, price);
            break;
        case 4:
            displayCars(head);
            break;
        case 5:

            while (head != NULL)
            {
                struct CarNode *temp = head;
                head = head->next;
                free(temp);
            }
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
