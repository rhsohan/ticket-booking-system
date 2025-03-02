#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
    int id;
    char name[50];
    int seat;
    struct Ticket *next;
};

struct Ticket *bookTicket(struct Ticket *head, int id, char name[], int seat);
struct Ticket *cancelTicket(struct Ticket *head, int id);
void displayTickets(struct Ticket *head);
int searchTicket(struct Ticket *head, int id);
int countTickets(struct Ticket *head);

int main() {
    printf("Program started!\n");
    struct Ticket *head = NULL;
    int choice, id, seat;
    char name[50];

    while (1) {
        printf("\n1. Book Ticket\n2. Cancel Ticket\n3. Display Tickets\n4. Search Ticket\n5. Count Tickets\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Ticket ID: ");
            scanf("%d", &id);
            printf("Enter Name: ");
            scanf(" %[^\n]s", name);
            printf("Enter Seat Number: ");
            scanf("%d", &seat);
            head = bookTicket(head, id, name, seat);
        }
        else if (choice == 2) {
            printf("Enter Ticket ID to cancel: ");
            scanf("%d", &id);
            head = cancelTicket(head, id);
        }
        else if (choice == 3) {
            displayTickets(head);
        }
        else if (choice == 4) {
            printf("Enter Ticket ID to search: ");
            scanf("%d", &id);
            int pos = searchTicket(head, id);
            if (pos != -1) {
                printf("Ticket found at position %d\n", pos);
            }
            else {
                printf("Ticket not found\n");
            }
        }
        else if (choice == 5) {
            printf("Total tickets: %d\n", countTickets(head));
        }
        else if (choice == 6) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

struct Ticket *bookTicket(struct Ticket *head, int id, char name[], int seat) {
    struct Ticket *newTicket = (struct Ticket *)malloc(sizeof(struct Ticket));
    newTicket->id = id;
    strcpy(newTicket->name, name);
    newTicket->seat = seat;
    newTicket->next = NULL;

    if (head == NULL) {
        printf("Ticket booked: ID=%d, Name=%s, Seat=%d\n", id, name, seat);
        return newTicket;
    }

    struct Ticket *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newTicket;


    printf("Ticket booked: ID=%d, Name=%s, Seat=%d\n", id, name, seat);
    return head;
}

struct Ticket *cancelTicket(struct Ticket *head, int id) {
    if (head == NULL) {
        printf("No tickets booked.\n");
        return NULL;
    }

    struct Ticket *temp = head, *prev = NULL;
    if (head->id == id) {
        head = head->next;
        free(temp);
        printf("Ticket ID %d canceled\n", id);
        return head;
    }

     while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Ticket ID %d not found.\n", id);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    printf("Ticket ID %d canceled\n", id);
    return head;
}

void displayTickets(struct Ticket *head) {
    if (head == NULL) {
        printf("No tickets booked.\n");
        return;
    }

    printf("\nBooked Tickets:\n");
    struct Ticket *temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Seat: %d\n", temp->id, temp->name, temp->seat);
        temp = temp->next;
    }
}

int searchTicket(struct Ticket *head, int id) {
    struct Ticket *temp = head;
    int position = 1;

    while (temp != NULL) {
        if (temp->id == id) {
            return position;
        }
        temp = temp->next;
        position++;
    }

    return -1;
}

int countTickets(struct Ticket *head) {
    int count = 0;
    struct Ticket *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}
