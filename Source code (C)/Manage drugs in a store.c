#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRUGS 100
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    int quantity;
    float price;
} Drug;

Drug drugs[MAX_DRUGS];
int drug_count = 0;

void display_drugs() {
    printf("List of Drugs:\n");
     printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Price");
    printf("---------------------------------------------------\n");
   for (int i = 0; i < drug_count; i++) {
        printf("%-20s %-10d $%-9.2f\n", drugs[i].name, drugs[i].quantity, drugs[i].price);
    }
}



void sort_drugs() {
    int option;
    printf("Sort by: 1. Name, 2. Quantity, 3. Price\n");
    scanf("%d", &option);

    for (int i = 0; i < drug_count - 1; i++) {
        for (int j = i + 1; j < drug_count; j++) {
            if ((option == 1 && strcmp(drugs[i].name, drugs[j].name) > 0) ||
                (option == 2 && drugs[i].quantity > drugs[j].quantity) ||
                (option == 3 && drugs[i].price > drugs[j].price)) {
                Drug temp = drugs[i];
                drugs[i] = drugs[j];
                drugs[j] = temp;
            }
        }
    }
    printf("Drugs sorted successfully.\n");
}

void search_drug() {
    char name[NAME_LENGTH];
    printf("Enter drug name to search: ");
    scanf("%s", name);

    for (int i = 0; i < drug_count; i++) {
        if (strcmp(drugs[i].name, name) == 0) {
            printf("Drug found: Name: %s, Quantity: %d, Price: %.2f\n", drugs[i].name, drugs[i].quantity, drugs[i].price);
            return;
        }
    }
    printf("Drug not found.\n");
}

void save_to_file() {
    FILE *file = fopen("drugs.txt", "w");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }
    for (int i = 0; i < drug_count; i++) {
        fprintf(file, "Name: %s, Quantity: %d, Price: %.2f\n", drugs[i].name, drugs[i].quantity, drugs[i].price);
    }
    fclose(file);
    printf("Data saved to file successfully.\n");
}

void delete_drug() {
    char name[NAME_LENGTH];
    printf("Enter drug name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < drug_count; i++) {
        if (strcmp(drugs[i].name, name) == 0) {
            for (int j = i; j < drug_count - 1; j++) {
                drugs[j] = drugs[j + 1];
            }
            drug_count--;
            printf("Drug deleted successfully.\n");
            return;
        }
    }
    printf("Drug not found.\n");
}

void delete_all_drugs() {
    drug_count = 0;
    printf("All drugs deleted successfully.\n");
}

void menu() {
    printf("\nDrug Store Management System\n");
    printf("1. Display all drugs\n");
    printf("2. Add a new drug\n");
    printf("3. Sort drugs\n");
    printf("4. Search for a drug\n");
    printf("5. Save to file\n");
    printf("6. Delete a drug\n");
    printf("7. Delete all drugs\n");
    printf("8. Exit\n");
}

int main() {
    int choice;
    strcpy(drugs[0].name, "Paracetamol");
    drugs[0].quantity = 50;
    drugs[0].price = 0.50;

    strcpy(drugs[1].name, "Aspirin");
    drugs[1].quantity = 30;
    drugs[1].price = 0.30;

    strcpy(drugs[2].name, "Amoxicillin");
    drugs[2].quantity = 20;
    drugs[2].price = 1.00;

    strcpy(drugs[3].name, "Ibuprofen");
    drugs[3].quantity = 40;
    drugs[3].price = 0.60;

    strcpy(drugs[4].name, "Cetirizine");
    drugs[4].quantity = 25;
    drugs[4].price = 0.45;

    drug_count = 5;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                display_drugs();
                break;
            case 2:
                add_drug();
                break;
            case 3:
                sort_drugs();
                break;
            case 4:
                search_drug();
                break;
            case 5:
                save_to_file();
                break;
            case 6:
                delete_drug();
                break;
            case 7:
                delete_all_drugs();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
