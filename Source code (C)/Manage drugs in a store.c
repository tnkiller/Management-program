#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDRUGS 100
#define NAME_LENGTH 50
#define DATE_LENGTH 11

typedef struct{
    char name[NAME_LENGTH];
    int quantity;
    float price;
    char expiryDate[DATE_LENGTH];
} Drug;

Drug drugs[MAXDRUGS];
int drugCount=0;

void displayDrugs(){
    printf("List of Drugs:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Name", "Quantity", "Price", "Expiry Date");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < drugCount; i++) {
        printf("%-20s %-10d %-10.2f %-15s\n", drugs[i].name, drugs[i].quantity, drugs[i].price, drugs[i].expiryDate);
    }
}

void addDrug(){
    if (drugCount>=MAXDRUGS){
        printf("Drug list is full!\n");
        return;
    }
    printf("Input drug name: ");
    scanf("%s", drugs[drugCount].name);
    printf("Quantity: ");
    scanf("%d", &drugs[drugCount].quantity);
    printf("Price: ");
    scanf("%f", &drugs[drugCount].price);
    printf("Expiry Date (DD-MM-): ");
    scanf("%s", drugs[drugCount].expiryDate);
    drugCount++;
}

void sortDrugs() {
    int options;
    printf("Sort by: 1. Name, 2. Quantity, 3. Price, 4. Expiry Date\n");
    scanf("%d", &options);

    for (int i=0;i<drugCount-1;i++){
        for (int j=i+1;j<drugCount;j++) {
            if ((options==1&&strcmp(drugs[i].name, drugs[j].name)>0)||
                (options==2&&drugs[i].quantity>drugs[j].quantity)||
                (options==3&&drugs[i].price>drugs[j].price)||
                (options==4&&strcmp(drugs[i].expiryDate, drugs[j].expiryDate)>0)){
                Drug temp=drugs[i];
                drugs[i]=drugs[j];
                drugs[j]=temp;
            }
        }
    }
    printf("Drugs sorted.\n");
}

void search_drug() {
    char name[NAME_LENGTH];
    printf("Enter drug name to search: ");
    scanf("%s", name);

    for (int i = 0; i < drugCount; i++) {
        if (strcmp(drugs[i].name, name) == 0) {
            printf("Drug found: Name: %s, Quantity: %d, Price: %.2f, Expiry Date: %s\n", drugs[i].name, drugs[i].quantity, drugs[i].price, drugs[i].expiryDate);
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
    for (int i = 0; i < drugCount; i++) {
        fprintf(file, "Name: %s, Quantity: %d, Price: %.2f, Expiry Date: %s\n", drugs[i].name, drugs[i].quantity, drugs[i].price, drugs[i].expiryDate);
    }
    fclose(file);
    printf("Data saved to file successfully.\n");
}

void delete_drug() {
    char name[NAME_LENGTH];
    printf("Enter drug name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < drugCount; i++) {
        if (strcmp(drugs[i].name, name) == 0) {
            for (int j = i; j < drugCount - 1; j++) {
                drugs[j] = drugs[j + 1];
            }
            drugCount--;
            printf("Drug deleted successfully.\n");
            return;
        }
    }
    printf("Drug not found.\n");
}

void delete_all_drugs() {
    drugCount = 0;
    printf("All drugs deleted successfully.\n");
}

void menu() {
    printf("\n---------------------------------------\n");
    printf("|          Drug Store Management      |\n");
    printf("---------------------------------------\n");
    printf("| 1 | Display all drugs               |\n");	
    printf("| 2 | Add new drug                    |\n");
    printf("| 3 | Sort drugs                      |\n");
    printf("| 4 | Search for a drug               |\n");
    printf("| 5 | Save to file                    |\n");
    printf("| 6 | Delete a drug                   |\n");
    printf("| 7 | Delete all drugs                |\n");
    printf("| 8 | Exit                            |\n");
    printf("---------------------------------------\n");
}

int main() {
    int choice;
    strcpy(drugs[0].name, "Paracetamol");
    drugs[0].quantity = 50;
    drugs[0].price = 10000.0;
    strcpy(drugs[0].expiryDate, "31-12-2024");

    strcpy(drugs[1].name, "Berberin");
    drugs[1].quantity = 30;
    drugs[1].price = 8000.0;
    strcpy(drugs[1].expiryDate, "15-10-2024");

    strcpy(drugs[2].name, "Aspirin");
    drugs[2].quantity = 20;
    drugs[2].price = 15000.0;
    strcpy(drugs[2].expiryDate, "01-05-2024");

    strcpy(drugs[3].name, "Benadryl");
    drugs[3].quantity = 40;
    drugs[3].price = 10000.0;
    strcpy(drugs[3].expiryDate, "20-01-2025");

    strcpy(drugs[4].name, "Cetirizine");
    drugs[4].quantity = 25;
    drugs[4].price = 13000.0;
    strcpy(drugs[4].expiryDate, "15-11-2024");

    drugCount = 5;

    while (1) {
        menu();
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayDrugs();
                break;
            case 2:
                addDrug();
                break;
            case 3:
                sortDrugs();
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
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
