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

printf("Nguyen an cut");
    return 0;
}
