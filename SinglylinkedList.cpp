#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int bookid;
    char bookname[100];
    char author[100];
    int price;
    struct node *next;
};

struct node *head = NULL;

void begininsert();
void lastinsert();
void randominsert();
void begin_delete();
void last_delete();
void random_delete();
void display();
void search();

int main() {
    int choice = 0;
    while (choice != 9) {
        printf("\n\n *********************** Main Menu ***********************\n");
        printf("Choose one option from the following list...\n");
        printf("\n1. Insert Book at Beginning\n");
        printf("2. Insert Book at Last\n");
        printf("3. Insert Book at Random Location\n");
        printf("4. Delete Book from Beginning\n");
        printf("5. Delete Book from Last\n");
        printf("6. Delete Book after Specified Location\n");
        printf("7. Search for a Book\n");
        printf("8. Display Books\n");
        printf("9. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: begininsert(); break;
            case 2: lastinsert(); break;
            case 3: randominsert(); break;
            case 4: begin_delete(); break;
            case 5: last_delete(); break;
            case 6: random_delete(); break;
            case 7: search(); break;
            case 8: display(); break;
            case 9: exit(0); break;
            default: printf("Please enter a valid choice...\n");
        }
    }
    return 0;
}

void begininsert() {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("\nOverflow\n");
        return;
    }
    
    printf("\nEnter Book ID: ");
    scanf("%d", &ptr->bookid);
    printf("Enter Book Name: ");
    scanf(" %[^\n]s", ptr->bookname);
    printf("Enter Book Author: ");
    scanf(" %[^\n]s", ptr->author);
    printf("Enter Book Price: ");
    scanf("%d", &ptr->price);

    ptr->next = head;
    head = ptr;
    printf("\nBook Is Inserted Successfully...\n");
}

void lastinsert() {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("\nOverflow\n");
        return;
    }
    
    printf("\nEnter Book ID: ");
    scanf("%d", &ptr->bookid);
    printf("Enter Book Name: ");
    scanf(" %[^\n]s", ptr->bookname);
    printf("Enter Book Author: ");
    scanf(" %[^\n]s", ptr->author);
    printf("Enter Book Price: ");
    scanf("%d", &ptr->price);
    
    ptr->next = NULL;

    if (head == NULL) {
        head = ptr;
    } else {
        struct node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = ptr;
    }
    printf("Book Is Inserted Successfully at Last...\n");
}

void randominsert() {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("\nOverflow\n");
        return;
    }
    
    printf("\nEnter Book ID: ");
    scanf("%d", &ptr->bookid);
    printf("Enter Book Name: ");
    scanf(" %[^\n]s", ptr->bookname);
    printf("Enter Book Author: ");
    scanf(" %[^\n]s", ptr->author);
    printf("Enter Book Price: ");
    scanf("%d", &ptr->price);
    
    int loc;
    printf("\nEnter the location after which you want to insert: ");
    scanf("%d", &loc);

    struct node *temp = head;
    for (int i = 0; i < loc; i++) {
        if (temp == NULL) {
            printf("\nCan't Insert at this location\n");
            free(ptr);
            return;
        }
        temp = temp->next;
    }
    
    ptr->next = temp->next;
    if (temp != NULL) {
        temp->next = ptr;
    }
    printf("Book Inserted at Random Position Successfully...\n");
}

void begin_delete() {
    if (head == NULL) {
        printf("\nList is empty..\n");
    } else {
        struct node *ptr = head;
        head = head->next;
        free(ptr);
        printf("Book deleted from beginning!\n");
    }
}

void last_delete() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    struct node *ptr = head;
    struct node *ptr1 = NULL;

    if (ptr->next == NULL) {
        free(head);
        head = NULL;
        printf("\nLast Book Is Deleted Successfully!\n");
    } else {
        while (ptr->next != NULL) {
            ptr1 = ptr;
            ptr = ptr->next;
        }
        ptr1->next = NULL;
        free(ptr);
        printf("\nLast Book Is Deleted Successfully!\n");
    }
}

void random_delete() {
    int loc;
    printf("\nEnter the location of the book after which you want to perform the deletion: ");
    scanf("%d", &loc);

    struct node *ptr = head;
    struct node *ptr1 = NULL;

    for (int i = 0; i <= loc; i++) {
        if (ptr == NULL) {
            printf("\nCan't Delete\n");
            return;
        }
        ptr1 = ptr;
        ptr = ptr->next;
    }

    if (ptr1 != NULL) {
        ptr1->next = ptr->next;
        free(ptr);
        printf("\nDeleted book at position %d\n", loc + 1);
    }
}

void search() {
    if (head == NULL) {
        printf("\nEmpty List!\n");
        return;
    }

    char name[100];
    printf("\nEnter Book Name Which You Want To Search: ");
    scanf(" %[^\n]s", name);

    struct node *ptr = head;
    int found = 0;
    int i = 0;
    
    while (ptr != NULL) {
        if (strcmp(ptr->bookname, name) == 0) {
            printf("Book found at location %d\n", i + 1);                   
            found = 1;
            break;
        }
        ptr = ptr->next;
        i++;
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

void display() {
    struct node *ptr = head;
    if (ptr == NULL) {
        printf("Nothing to print.\n");
    } else {
        printf("\nPrinting values...\n");
        while (ptr != NULL) {
            printf("Book ID: %d, Name: %s, Author: %s, Price: %d\n", ptr->bookid, ptr->bookname, ptr->author, ptr->price);
            ptr = ptr->next;
        }
    }
}

