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

    return 0;
}
float *smooth(int avr_n, float *pt_array){
	float *pt_rs;
	*(pt_rs) = 0.0;
	for (int i=0;i<10-avr_n+1;i++){
		for (int j=i;j<i+avr_n;j++){
			*(pt_rs+i) += *(pt_array+j)/avr_n;
		}
	}
	return pt_rs;
}
//main
int main(){
	int numcs;
	float array[10] = {1.2, 7.2, 9.0, 2.1, 4.2, 6.0, 23.1, 5.1, 2.4, 10.2};
	float *ptr_array = array;
	float *ptr_result;
	printf("Input smooth number: "); scanf("%d", &numcs);
	ptr_result = smooth(numcs,ptr_array);
	for (int i=0;i<10-numcs+1;i++){
		printf("%f   ", *(ptr_result+i));
	}
	return 0;
}
