#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//DRUG
#define MAX_PRODUCTS 100
#define MAX_DATE_LENGTH 20
#define MAX_PRODUCT_NAME_LENGTH 100
#define MAX_UNIT_LENGTH 20
//CUSTOMER
#define MAX_CUSTOMERS 100
#define MAX_CUSTOMER_NAME_LENGTH 100
#define MAX_GENDER_LENGTH 10
#define MAX_AGE_LENGTH 5
#define MAX_PHONENUMBER_LENGTH 10
#define MAX_NOTE_LENGTH 200
//Payment
#define MAX_PAYMENT 100

/*DATA*/
// Customer
char customerName[MAX_CUSTOMERS][MAX_CUSTOMER_NAME_LENGTH];
char customerGender[MAX_CUSTOMERS][MAX_GENDER_LENGTH];
int customerAge[MAX_AGE_LENGTH];
char customerPhoneNum[MAX_CUSTOMERS][MAX_PHONENUMBER_LENGTH];
char customerNote[MAX_CUSTOMERS][MAX_NOTE_LENGTH];
int numCustomers = 0;

// Product
char productName[MAX_PRODUCTS][MAX_PRODUCT_NAME_LENGTH];
int productQuantity[MAX_PRODUCTS];
float productPrice[MAX_PRODUCTS];
char productUnit[MAX_PRODUCTS][MAX_UNIT_LENGTH];
char productDate[MAX_PRODUCTS][MAX_DATE_LENGTH];
int numProducts = 0;

//payment
char paymentCustomerNames[MAX_PAYMENT][MAX_CUSTOMER_NAME_LENGTH];
char paymentCustomerAdd[MAX_PAYMENT][MAX_CUSTOMER_NAME_LENGTH];
char paymentProductNames[MAX_PAYMENT][MAX_PRODUCT_NAME_LENGTH];
int paymentQuantities[MAX_PAYMENT];
double paymentTotals[MAX_PAYMENT];
int numPayment = 0;
/*--------------------------------------------------------------------------------------------------------------------*/
/*FILE*/
//product
//save
void saveProducts() {
	FILE *p_file = fopen("drug data.txt", "a");
	if (p_file == NULL) {
		printf("Error opening products file\n");
		return;
	}
	for (int i = 0; i < numProducts; i++) {
		fprintf(p_file, "%s-%d-%.2f-%s-%s\n", productName[i], productQuantity[i], productPrice[i], productUnit[i], productDate[i]);
	}
	fclose(p_file);
}
//load
void loadProducts() {
	FILE *p_file = fopen("drug data.txt", "r");
	if (p_file == NULL) {
		printf("Error opening products file\n");
		return;
	}
	numProducts = 0;
	while (fscanf(p_file, "%[^-]-%d-%f-%[^-]-%[^\n]", productName[numProducts], &productQuantity[numProducts], &productPrice[numProducts], productUnit[numProducts], productDate[numProducts]) == 5) {
		numProducts++;
	}
	fclose(p_file);
}


/*Store menu*/
void StoreMenu() {
	int choice;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|                -STORE MENU-                |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Display 			 					\n");
		printf("| 2 | Add new  			     				\n");
		printf("| 3 | Sort 			    					\n");
		printf("| 4 | Search 			     				\n");
		printf("| 5 | Delete 		     	 				\n");
		printf("| 6 | Back 		     			 			\n");
		printf("----------------------------------------------\n");
		printf("You choose: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				break;
			}
			case 2: {
				break;
			}
			case 3: {
				break;
			}
			case 4: {
				break;
			}
			case 5: {
				break;
			}
			case 6: {
				return;
				break;
			}
			default: {
				printf("Invalid. Try again!");
				break;
			}
		}
	} while(choice != 6);

}








/*FILE*/
//customer
//save
void saveCustomers() {
	FILE *p_file = fopen("customer data.txt", "a");
	if (p_file == NULL) {
		printf("Not working\n");
		return;
	}
	for (int i = 0; i < numCustomers; i++) {
		fprintf(p_file, "%s-%s-%d-%s-%s\n", customerName[i],customerGender[i], customerAge[i], customerPhoneNum[i],customerNote[i]);
	}
	fclose(p_file);
}
//load
void loadCustomers() {
	FILE *p_file = fopen("customer data.txt", "r");
	if (p_file == NULL) {
		printf("Not working\n");
		return;
	}
	numCustomers = 0;
	while (fscanf(p_file, "%[^-]-%[^-]-%d-%[^-]-%[^\n]", customerName[numCustomers],customerGender[numCustomers], &customerAge[numCustomers], customerPhoneNum[numCustomers],customerNote[numCustomers]) == 5) {
		numCustomers++;
	}
	fclose(p_file);
}
//Add new customer
void addCustomer() {
	printf("Enter customer name: ");
	getchar(); // consume newline left by previous input
	fgets(customerName[numCustomers], MAX_CUSTOMER_NAME_LENGTH, stdin);
	customerName[numCustomers][strlen(customerName[numCustomers]) - 1] = '\0'; // remove newline character

	printf("Enter gender: ");
	getchar();
	fgets(customerGender[numCustomers], MAX_GENDER_LENGTH, stdin);
	customerGender[numCustomers][strlen(customerGender[numCustomers]) - 1] = '\0';

	printf("Enter age: ");
	scanf("%d", &customerAge[numCustomers]);
	getchar();

	printf("Enter customer phonenumber: ");
	fgets(customerPhoneNum[numCustomers], MAX_PHONENUMBER_LENGTH, stdin);
	customerPhoneNum[numCustomers][strlen(customerPhoneNum[numCustomers]) - 1] = '\0';

	printf("Enter note of customer: ");
	fgets(customerNote[numCustomers], MAX_NOTE_LENGTH, stdin);
	customerNote[numCustomers][strlen(customerNote[numCustomers]) - 1] = '\0';
	numCustomers++;
	saveCustomers();
	printf("\nCustomer added successfully!\n");
}

//Information
void printCustomerList() {
	printf("\n------------------------------------- Customer List ---------------------------------\n");
	printf("%-20s | %-15s | %-10s | %-20s | %-30s\n", "Name","Gender", "Age", "Phone Number", "Note");
	printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < numCustomers; i++) {
		printf("%-20s   %-15s   %-10d   %-20s   %-30s\n", customerName[i],customerGender[i], customerAge[i],customerPhoneNum[i],customerNote[i]);
	}
	printf("---------------------------------------------------------------------------------------\n");
}
/*Customer menu*/
void CustomerMenu() {
	int choice;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|               -CUSTOMER MENU-              |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Add		 							\n");
		printf("| 2 | Information		 					\n");
		printf("| 3 | History		 						\n");
		printf("| 4 | Back		 							\n");
		printf("----------------------------------------------\n");
		printf("You choose: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				printf("\n");
				addCustomer();
				break;
			}
			case 2: {
				printf("\n");
				printCustomerList();
				break;
			}
			case 3: {

				break;
			}
			default: {
				printf("Invalid. Try again!");
				break;
			}
		}
	} while(choice != 4);
}



/*PAYMENT*/
//load
void loadPayment() {
    FILE *p_file = fopen("payment data.txt", "r");
    if (p_file == NULL) return;
    numPayment = 0;
    while (fscanf(p_file, "%[^-]-%[^-]-%[^-]-%d-%f\n", paymentCustomerNames[numPayment], paymentCustomerAdd[numPayment], paymentProductNames[numPayment], &paymentQuantities[numPayment], &paymentTotals[numPayment]) == 5) {
        numPayment++;
    }
    fclose(p_file);
}
	
//Save 
void savePayment() {
    FILE *p_file = fopen("payment data.txt", "a");
    if (p_file == NULL) return;
    for (int i = 0; i < numPayment; i++) {
        fprintf(p_file, "%s-%s-%s-%d-%.2f\n", paymentCustomerNames[i], paymentCustomerAdd[i], paymentProductNames[i], &paymentQuantities[i], &paymentTotals[i]);
    }
    fclose(p_file);
}
/*Payment menu*/
void PaymentMenu() {
	int choice;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|               -PAYMENT MENU-              |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Pay		 							\n");
		printf("| 2 | Print invoice		 					\n");
		printf("| 3 | Delete		 						\n");
		printf("| 4 | Back		 							\n");
		printf("----------------------------------------------\n");
		printf("You choose: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				printf("\n");
				addCustomer();
				break;
			}
			case 2: {
				printf("\n");
				printCustomerList();
				break;
			}
			case 3: {

				break;
			}
			default: {
				printf("Invalid. Try again!");
				break;
			}
		}
	} while(choice != 4);
}
//main
int main() {
	loadCustomers();
	loadProducts();
	int option;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|           -DRUG MANAGEMENT TOOL-           |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Store management		 				\n");
		printf("| 2 | Customer management			     	\n");
		printf("| 3 | Payment			     				\n");
		printf("| 3 | Exit			     					\n");
		printf("----------------------------------------------\n");
		printf("You choose: ");
		scanf("%d",&option);
		switch (option) {
			case 1: {
				printf("\n");
				StoreMenu();
				break;
			}
			case 2: {
				printf("\n");
				CustomerMenu();
				break;
			}
			case 3: {
				printf("\n");
				Payment();
				break;
			}
			case 4: {
				printf("GOOD BYE!");
				break;
			}
			default: {
				printf("Invalid. Please choose again!!");
				break;
			}
		}
	} while (option != 3);
	return 0;
}