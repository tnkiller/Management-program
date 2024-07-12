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
char drugName[MAX_PRODUCTS][MAX_PRODUCT_NAME_LENGTH];
int drugQuantity[MAX_PRODUCTS];
float drugPrice[MAX_PRODUCTS];
char drugUnit[MAX_PRODUCTS][MAX_UNIT_LENGTH];
char drugDate[MAX_PRODUCTS][MAX_DATE_LENGTH];
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
		fprintf(p_file, "%s-%d-%.2f-%s-%s\n", drugName[i], drugQuantity[i], drugPrice[i], drugUnit[i], drugDate[i]);
	}
	fclose(p_file);
}
//load
void loadProducts() {
	FILE *p_file = fopen("drug data.txt", "r");
	if (p_file == NULL) {
		printf("Error opening drugs file\n");
		return;
	}
	numProducts = 0;
	while (fscanf(p_file, "%[^-]-%d-%f-%[^-]-%[^\n]", drugName[numProducts], &drugQuantity[numProducts], &drugPrice[numProducts], drugUnit[numProducts], drugDate[numProducts]) == 5) {
		numProducts++;
	}
	fclose(p_file);
}


/*Store menu*/
void display();
void addProduct();
void deleteProduct();
void findProduct();
void editProduct();
void StoreMenu() {
	int choice;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|                -STORE MENU-                |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Display 			 					\n");
		printf("| 2 | Add new  			     				\n");
		printf("| 3 | Delete 			    				\n");
		printf("| 4 | Search 			     				\n");
		printf("| 5 | Edit 		     	 					\n");
		printf("| 6 | Back 		     			 			\n");
		printf("----------------------------------------------\n");
		printf("You choose: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				display();
				break;
			}
			case 2: {
				addProduct();
				break;
			}
			case 3: {
				deleteProduct();
				break;
			}
			case 4: {
				findProduct();
				break;
			}
			case 5: {
				editProduct();
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
//display
void display() {
	printf("\n--------------------------------- Drug List ----------------------------------\n");
	printf("%-25s | %-10s | %-5s | %-5s | %-20s\n","Name", "Quantity", "Price", "Unit", "Expire date");

	for (int i = 0; i < numProducts; i++) {
		printf("%-25s   %-10d   %-5.2f   %-5s  %-20s\n", drugName[i], drugQuantity[i], drugPrice[i], drugUnit[i],drugDate[i]);
	}
	printf("------------------------------------------------------------------------------\n");
}
//Add new
void addProduct() {
	printf("Enter drug name: ");
	getchar();
	fgets(drugName[numProducts], MAX_PRODUCT_NAME_LENGTH, stdin);
	drugName[numProducts][strlen(drugName[numProducts]) - 1] = '\0';

	printf("Enter drug quantity: ");
	scanf("%d", &drugQuantity[numProducts]);

	printf("Enter product price: ");
	scanf("%f", &drugPrice[numProducts]);

	printf("Enter drug unit: ");
	getchar();
	fgets(drugUnit[numProducts], MAX_UNIT_LENGTH, stdin);
	drugUnit[numProducts][strlen(drugUnit[numProducts]) - 1] = '\0';

	printf("Enter drug expired date: ");
	getchar();
	fgets(drugDate[numProducts], MAX_DATE_LENGTH, stdin);
	drugDate[numProducts][strlen(drugDate[numProducts]) - 1] = '\0';

	numProducts++;
	saveProducts();
	printf("\nAdded!\n");
}
//Delete
void deleteProduct() {
	display();
	if (numProducts != 0) {
		char name[1000];
		printf("Enter drug name to delete: ");
		getchar();
		gets(name);

		for (int i = 0; i < numProducts; i++) {
			if (strcmpi(name, drugName[i]) == 0) {
				for (int j = i; j < numProducts - 1; j++) {
					strcpy(drugName[j], drugName[j + 1]);
					drugQuantity[j] = drugQuantity[j + 1];
					drugPrice[j] = drugPrice[j + 1];
					strcpy(drugUnit[j], drugUnit[j + 1]);
					strcpy(drugDate[j], drugDate[j + 1]);
				}
				numProducts--;
				saveProducts();
				printf("Deleted !\n");
				return;
			}
		}
		printf("\nInvalid name!\n");
	} else printf("No products!!");
	saveProducts();
}
//Search
void findProduct() {
	char name[1000];
	printf("Enter drug name to find: ");
	getchar();
	gets(name);

	for (int i = 0; i < numProducts; i++) {
		if (strcmpi(drugName[i],name) == 0) {
			printf("\nNAME: %s\n", drugName[i]);
			printf("QUANTITY: %d\n", drugQuantity[i]);
			printf("PRICE: %.2f\n", drugPrice[i]);
			printf("UNIT: %s\n", drugUnit[i]);
			printf("EXPIRE DATE: %s\n",drugDate[i]);
			printf("\n");
			return;
		}
	}
	printf("Not found\n");
}
//Edit
void editProduct() {
	char name[1000];
	printf("Enter drug name to edit: ");
	getchar();
	gets(name);

	for (int i = 0; i < numProducts; i++) {
		if (strcmpi(drugName[i],name) == 0) {

			printf("Enter new drug name: ");
			fgets(drugName[i], MAX_PRODUCT_NAME_LENGTH, stdin);
			drugName[i][strlen(drugName[i]) - 1] = '\0'; // remove newline character

			printf("Enter new drug quantity: ");
			scanf("%d", &drugQuantity[i]);

			printf("Enter new drug price: ");
			scanf("%f", &drugPrice[i]);

			printf("Enter new drug unit: ");
			getchar();
			fgets(drugUnit[i], MAX_UNIT_LENGTH, stdin);
			drugUnit[i][strlen(drugUnit[i]) - 1] = '\0'; // remove newline character
			
			printf("Enter new drug date: ");
			getchar();
			fgets(drugUnit[i], MAX_DATE_LENGTH, stdin);
			drugUnit[i][strlen(drugUnit[i]) - 1] = '\0'; // remove newline character

			saveProducts();
			printf("\nUpdated !\n");
			return;
		}
	}
	printf("\nNot found\n");
}




/*--------------------------------------------------------------------------------------------------------------------*/
///*FILE*/
////customer
////save
//void saveCustomers() {
//	FILE *p_file = fopen("customer data.txt", "a");
//	if (p_file == NULL) {
//		printf("Not working\n");
//		return;
//	}
//	for (int i = 0; i < numCustomers; i++) {
//		fprintf(p_file, "%s-%s-%d-%s-%s\n", customerName[i],customerGender[i], customerAge[i], customerPhoneNum[i],customerNote[i]);
//	}
//	fclose(p_file);
//}
////load
//void loadCustomers() {
//	FILE *p_file = fopen("customer data.txt", "r");
//	if (p_file == NULL) {
//		printf("Not working\n");
//		return;
//	}
//	numCustomers = 0;
//	while (fscanf(p_file, "%[^-]-%[^-]-%d-%[^-]-%[^\n]", customerName[numCustomers],customerGender[numCustomers], &customerAge[numCustomers], customerPhoneNum[numCustomers],customerNote[numCustomers]) == 5) {
//		numCustomers++;
//	}
//	fclose(p_file);
//}
//
///*Customer menu*/
//void CustomerMenu() {
//	int choice;
//	do {
//		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//		printf("|               -CUSTOMER MENU-              |\n");
//		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//		printf("| 1 | Add		 							\n");
//		printf("| 2 | Information		 					\n");
//		printf("| 3 | History		 						\n");
//		printf("| 4 | Back		 							\n");
//		printf("----------------------------------------------\n");
//		printf("You choose: ");
//		scanf("%d", &choice);
//
//		switch (choice) {
//			case 1: {
//				printf("\n");
//				addCustomer();
//				break;
//			}
//			case 2: {
//				printf("\n");
//				printCustomerList();
//				break;
//			}
//			case 3: {
//
//				break;
//			}
//			default: {
//				printf("Invalid. Try again!");
//				break;
//			}
//		}
//	} while(choice != 4);
//}
////Add new customer
//void addCustomer() {
//	printf("Enter customer name: ");
//	getchar(); // consume newline left by previous input
//	fgets(customerName[numCustomers], MAX_CUSTOMER_NAME_LENGTH, stdin);
//	customerName[numCustomers][strlen(customerName[numCustomers]) - 1] = '\0'; // remove newline character
//
//	printf("Enter gender: ");
//	getchar();
//	fgets(customerGender[numCustomers], MAX_GENDER_LENGTH, stdin);
//	customerGender[numCustomers][strlen(customerGender[numCustomers]) - 1] = '\0';
//
//	printf("Enter age: ");
//	scanf("%d", &customerAge[numCustomers]);
//	getchar();
//
//	printf("Enter customer phonenumber: ");
//	fgets(customerPhoneNum[numCustomers], MAX_PHONENUMBER_LENGTH, stdin);
//	customerPhoneNum[numCustomers][strlen(customerPhoneNum[numCustomers]) - 1] = '\0';
//
//	printf("Enter note of customer: ");
//	fgets(customerNote[numCustomers], MAX_NOTE_LENGTH, stdin);
//	customerNote[numCustomers][strlen(customerNote[numCustomers]) - 1] = '\0';
//	numCustomers++;
//	saveCustomers();
//	printf("\nCustomer added successfully!\n");
//}
//
////Information
//void printCustomerList() {
//	printf("\n------------------------------------- Customer List ---------------------------------\n");
//	printf("%-20s | %-15s | %-10s | %-20s | %-30s\n", "Name","Gender", "Age", "Phone Number", "Note");
//	printf("----------------------------------------------------------------------------------------\n");
//	for (int i = 0; i < numCustomers; i++) {
//		printf("%-20s   %-15s   %-10d   %-20s   %-30s\n", customerName[i],customerGender[i], customerAge[i],customerPhoneNum[i],customerNote[i]);
//	}
//	printf("---------------------------------------------------------------------------------------\n");
//}
//
//
//
//
//
//
//
///*PAYMENT*/
////load
//void loadPayment() {
//    FILE *p_file = fopen("payment data.txt", "r");
//    if (p_file == NULL) return;
//    numPayment = 0;
//    while (fscanf(p_file, "%[^-]-%[^-]-%[^-]-%d-%f\n", paymentCustomerNames[numPayment], paymentCustomerAdd[numPayment], paymentProductNames[numPayment], &paymentQuantities[numPayment], &paymentTotals[numPayment]) == 5) {
//        numPayment++;
//    }
//    fclose(p_file);
//}
//
////Save
//void savePayment() {
//    FILE *p_file = fopen("payment data.txt", "a");
//    if (p_file == NULL) return;
//    for (int i = 0; i < numPayment; i++) {
//        fprintf(p_file, "%s-%s-%s-%d-%.2f\n", paymentCustomerNames[i], paymentCustomerAdd[i], paymentProductNames[i], &paymentQuantities[i], &paymentTotals[i]);
//    }
//    fclose(p_file);
//}
///*Payment menu*/
//void PaymentMenu() {
//	int choice;
//	do {
//		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//		printf("|               -PAYMENT MENU-              |\n");
//		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//		printf("| 1 | Pay		 							\n");
//		printf("| 2 | Print invoice		 					\n");
//		printf("| 3 | Delete		 						\n");
//		printf("| 4 | Back		 							\n");
//		printf("----------------------------------------------\n");
//		printf("You choose: ");
//		scanf("%d", &choice);
//
//		switch (choice) {
//			case 1: {
//				printf("\n");
//				addCustomer();
//				break;
//			}
//			case 2: {
//				printf("\n");
//				printCustomerList();
//				break;
//			}
//			case 3: {
//
//				break;
//			}
//			default: {
//				printf("Invalid. Try again!");
//				break;
//			}
//		}
//	} while(choice != 4);
//}
/*--------------------------------------------------------------------------------------------------------------------*/
//main
int main() {
//	loadCustomers();
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
//				CustomerMenu();
				break;
			}
			case 3: {
				printf("\n");
//				Payment();
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