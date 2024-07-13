#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>

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
char paymentProductNames[MAX_PAYMENT][MAX_PRODUCT_NAME_LENGTH];
int paymentQuantities[MAX_PAYMENT];
double paymentTotals[MAX_PAYMENT];
int numPayment = 0;
/*--------------------------------------------------------------------------------------------------------------------*/
/*FILE*/
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
   
void saveCustomerData() {
	FILE *fp;
	fp = fopen("customer_data.txt", "w");
	if (fp == NULL) {
		printf("Error opening file.\n");
		return;
	}

	for (int i = 0; i < numCustomers; i++) {
		fprintf(fp, "%s|%s|%d|%s|%s\n", customerName[i], customerGender[i], customerAge[i], customerPhoneNum[i], customerNote[i]);
	}

	fclose(fp);
	printf("Customer data saved!\n");
}

void loadCustomerData() {
	FILE *fp;
	fp = fopen("customer_data.txt", "r");

	if (fp == NULL) {
		printf("Error opening file.\n");
		return;
	}
	numCustomers = 0;
	while (fscanf(fp, "%[^|]|%[^|]|%d|%[^|]|%[^\n]\n", customerName[numCustomers], customerGender[numCustomers], &customerAge[numCustomers], customerPhoneNum[numCustomers], customerNote[numCustomers]) == 5) {
		numCustomers++;
	}
	fclose(fp);
}

//product
void saveProducts() {
	FILE *p_file;
	p_file = fopen("drug_data.txt", "w");
	
	if (p_file == NULL) {
		printf("Error opening drugs data file\n");
		return;
	}
	for (int i = 0; i < numProducts; i++) {
		fprintf(p_file, "%s|%d|%.2f|%s|%s\n", drugName[i], drugQuantity[i], drugPrice[i], drugUnit[i], drugDate[i]);
	}
	fclose(p_file);
}

void loadProducts() {
	FILE *p_file;
	p_file = fopen("drug_data.txt", "r");
	if (p_file == NULL) {
		printf("Error opening drugs data file\n");
		return;
	}
	numProducts = 0;
	while (fscanf(p_file, "%[^|]|%d|%f|%[^|]|%[^\n]\n", drugName[numProducts], &drugQuantity[numProducts], &drugPrice[numProducts], drugUnit[numProducts], drugDate[numProducts]) == 5) {
		numProducts++;
		if (numProducts >= MAX_PRODUCTS) {
			break;
		}
	}
	fclose(p_file);
}

//save
void saveInvoicesToFile() {
    FILE *file; 
	file = fopen("payment_data.txt", "w");
    if (file == NULL) {
	printf("Error when opening!");
	return;
}
    for (int i = 0; i < numPayment; i++) {
        fprintf(file, "%s|%s|%d|%f\n", paymentCustomerNames[i], paymentProductNames[i], paymentQuantities[i], paymentTotals[i]);
    }
    fclose(file);
}

// Load invoice data from file
void loadInvoicesFromFile() {
    FILE *file;
	file = fopen("payment_data.txt", "r");
    if (file == NULL) return;
    numPayment = 0;
    while (fscanf(file, "%[^|]|%[^|]|%d|%lf\n", paymentCustomerNames[numPayment],paymentProductNames[numPayment], &paymentQuantities[numPayment], &paymentTotals[numPayment]) == 4) {
        numPayment++;
    }
    fclose(file);
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
	printf("\n|--------------------------------- Drug List -------------------------------------------|\n");
	printf("|%-25s  |%-10s | %-10s | %-10s|  %-20s|\n", "Name", "Quantity", "Price", "Unit","Expire date");
	printf("|---------------------------|-----------|------------|-----------|----------------------|\n");
	for (int i = 0; i < numProducts; i++) {
		printf("|%-25s  |%-10d | %-10.2f | %-10s|  %-20s|\n", drugName[i], drugQuantity[i], drugPrice[i], drugUnit[i], drugDate[i]);
	}
	printf("|---------------------------------------------------------------------------------------|");
}

// Add new product
void addProduct() {
	printf("Enter drug name: ");
	getchar();
	fgets(drugName[numProducts], MAX_PRODUCT_NAME_LENGTH, stdin);
	drugName[numProducts][strcspn(drugName[numProducts], "\n")] = '\0';
	printf("Enter drug quantity: ");
	scanf("%d", &drugQuantity[numProducts]);

	printf("Enter product price: ");
	scanf("%f", &drugPrice[numProducts]);

	printf("Enter drug unit: ");
	getchar();
	fgets(drugUnit[numProducts], MAX_UNIT_LENGTH, stdin);
	drugUnit[numProducts][strcspn(drugUnit[numProducts], "\n")] = '\0';

	printf("Enter drug expiry date: ");
	fgets(drugDate[numProducts], MAX_DATE_LENGTH, stdin);
	drugDate[numProducts][strcspn(drugDate[numProducts], "\n")] = '\0';

	numProducts++;
	saveProducts();
	printf("\nAdded!\n");
}

//Delete
void deleteProduct() {
	display();
	if (numProducts != 0) {
		char name[1000];
		printf("\nEnter drug name to delete: ");
		getchar();
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = 0;

		for (int i = 0; i < numProducts; i++) {
			if (strcasecmp(name, drugName[i]) == 0) {
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
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0;
	
	for (int i = 0; i < numProducts; i++) {
		if (strcasecmp(drugName[i],name) == 0) {
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
	display();
    char name[MAX_PRODUCT_NAME_LENGTH];
    printf("\nEnter drug name to edit: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character
    
    for (int i = 0; i < numProducts; i++) {
        if (strcasecmp(drugName[i], name) == 0) {
            
            printf("Enter new drug name: ");
            fgets(drugName[i], MAX_PRODUCT_NAME_LENGTH, stdin);
            drugName[i][strcspn(drugName[i], "\n")] = '\0'; // Remove newline character

            printf("Enter new drug quantity: ");
            scanf("%d", &drugQuantity[i]);
            clearInputBuffer();

            printf("Enter new drug price: ");
            scanf("%f", &drugPrice[i]);
            clearInputBuffer();

            printf("Enter new drug unit: ");
            fgets(drugUnit[i], MAX_UNIT_LENGTH, stdin);
            drugUnit[i][strcspn(drugUnit[i], "\n")] = '\0'; // Remove newline character

            printf("Enter new drug expiry date: ");
            fgets(drugDate[i], MAX_DATE_LENGTH, stdin);
            drugDate[i][strcspn(drugDate[i], "\n")] = '\0'; // Remove newline character

            saveProducts();
            printf("\nUpdated!\n");
            return;
        }
    }
    printf("\nDrug not found\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

///*Customer menu*/
char customerName[MAX_CUSTOMERS][MAX_CUSTOMER_NAME_LENGTH];
char customerGender[MAX_CUSTOMERS][MAX_GENDER_LENGTH];
int customerAge[MAX_AGE_LENGTH];
char customerPhoneNum[MAX_CUSTOMERS][MAX_PHONENUMBER_LENGTH];
char customerNote[MAX_CUSTOMERS][MAX_NOTE_LENGTH];
int numcustomers=0;

void addCustomer();
void deleteCustomer(int index);
void printCustomerList();
void viewHistory();
void saveCustomerData();
void loadCustomerData();

void addCustomer() {
	printf("Enter customer details:\n");

	printf("Name: ");
	scanf(" %[^\n]", customerName[numCustomers]);

	printf("Gender: ");
	scanf(" %[^\n]", customerGender[numCustomers]);

	printf("Age: ");
	scanf("%d", &customerAge[numCustomers]);

	printf("Phone Number: ");
	scanf(" %[^\n]", customerPhoneNum[numCustomers]);

	printf("Note: ");
	scanf(" %[^\n]", customerNote[numCustomers]);

	numCustomers++;
	saveCustomerData();
	printf("Updated!\n");
}

void deleteCustomer(int index) {

	if (index < 0 || index >= numCustomers) {
		printf("Invalid number. No customer deleted.\n");
		return;
	}
	for (int i = index; i < numCustomers; i++) {
		strcpy(customerName[i], customerName[i + 1]);
		strcpy(customerGender[i], customerGender[i + 1]);
		customerAge[i] = customerAge[i + 1];
		strcpy(customerPhoneNum[i], customerPhoneNum[i + 1]);
		strcpy(customerNote[i], customerNote[i + 1]);
	}
	numCustomers--;

	printf("Customer deleted successfully.\n");
	saveCustomerData();
}

void printCustomerList() {
	printf("Customer List:\n");

	printf("| %-4s | %-20s | %-10s | %-5s | %-15s | %-20s |\n", "No.", "Name", "Gender", "Age", "Phone Number", "Note");
	printf("|-------------------------------------------------------------------------------------------|\n");

	for (int i = 0; i < numCustomers; i++) {
		printf("| %-4d | %-20s | %-10s | %-5d | %-15s | %-20s |\n", i + 1, customerName[i], customerGender[i], customerAge[i], customerPhoneNum[i], customerNote[i]);
	}
}

void viewHistory() {
	printf("History:\n");

	if (numCustomers == 0) {
		printf("No customers added or deleted yet.\n");
		return;
	}

	for (int i = 0; i < numCustomers; i++) {
		printf("Customer %d: %s\n", i + 1, customerName[i]);
	}
}

void CustomerMenu() {
	int choice;
	loadCustomerData();
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|               -CUSTOMER MENU-              |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Add		 							\n");
		printf("| 2 | Delete	 							\n");
		printf("| 3 | Information		 					\n");
		printf("| 4 | History		 						\n");
		printf("| 5 | Back		 							\n");
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
				int index;
				printf("Enter customer number to delete: ");
				scanf("%d", &index);
				deleteCustomer(index - 1);
				break;
			}
			case 3: {
				printf("\n");
				printCustomerList();
				break;
			}
			case 4: {
				printf("\n");
				viewHistory();
				break;
			}
			case 5: {
				printf("Returning..\n");
				break;
			}
			default: {
				printf("Invalid. Try again!");
				break;
			}
		}
	} while(choice != 5);
}



/*--------------------------------------------------------------------------------------------------------------------------------*/
///*PAYMENT*/

//int numPayment = 0;

//Pay
void addInvoice() {
    char name_cus[50], name_pro[50]; 
    int quantity;

    getchar();
    printf("Enter customer name: ");
    scanf("%[^\n]", name_cus);

    // Check if customer exists
    int customerIndex = -1;
    for (int i = 0; i < numCustomers; i++) {
        if (strcmpi(customerName[i], name_cus) == 0) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        printf("\nCustomer not found.\n");
        return;
    }

    getchar();
    printf("Enter product name: ");
    scanf("%[^\n]", name_pro);

    // Check if product exists and has enough quantity
    int productIndex = -1;
    for (int i = 0; i < numProducts; i++) {
        if (strcmpi(drugName[i], name_pro) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("\nProduct not found.\n");
        return;
    }

    printf("Enter quantity purchased: ");
    scanf("%d", &quantity);

    // Check if there is enough quantity
    if (drugQuantity[productIndex] < quantity) {
        printf("\nInsufficient drug quantity.\n");
        return;
    }

    // Update drug quantity
    drugQuantity[productIndex] -= quantity;

    // Create invoice
    strcpy(paymentCustomerNames[numPayment], customerName[customerIndex]);
    strcpy(paymentProductNames[numPayment], drugName[productIndex]);
    paymentQuantities[numPayment] = quantity;
    paymentTotals[numPayment] = quantity * drugPrice[productIndex];
    numPayment++;

    saveInvoicesToFile();
    saveProducts();
    printf("\nInvoice added successfully.\n");
}

// Print invoices
void printInvoices() {
    printf("\n------------------------------ Invoice List ------------------------------\n");
    printf("%-20s | %-20s | %-10s | %-10s\n", "Cust Name", "Prod Name", "Quantity", "Total");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numPayment; i++) {
        printf("%-20s | %-20s | %-10d | %-10.2f\n", paymentCustomerNames[i], paymentProductNames[i], paymentQuantities[i], paymentTotals[i]);
    }
    printf("----------------------------------------------------------------------------\n");
}



// Delete an invoice by ID
void deleteInvoice() {
    char name_cus[MAX_CUSTOMER_NAME_LENGTH];
    char name_pro[MAX_PRODUCT_NAME_LENGTH];
    
    printf("Enter customer name of the invoice to delete: ");
    getchar(); // Consume newline character left in buffer
    fgets(name_cus, sizeof(name_cus), stdin);
    name_cus[strcspn(name_cus, "\n")] = 0; // Remove newline character if present
    
    printf("Enter product name of the invoice to delete: ");
    fgets(name_pro, sizeof(name_pro), stdin);
    name_pro[strcspn(name_pro, "\n")] = 0; // Remove newline character if present
    
    bool found = false;
    for (int i = 0; i < numPayment; i++) {
        if (strcasecmp(paymentCustomerNames[i], name_cus) == 0 && strcasecmp(paymentProductNames[i], name_pro) == 0) {
            // Restore product quantity (assuming drugQuantity and numProducts are defined elsewhere)
            // Code for restoring product quantity goes here
            
            // Shift invoices
            for (int j = i; j < numPayment - 1; j++) {
                strcpy(paymentCustomerNames[j], paymentCustomerNames[j + 1]);
                strcpy(paymentProductNames[j], paymentProductNames[j + 1]);
                paymentQuantities[j] = paymentQuantities[j + 1];
                paymentTotals[j] = paymentTotals[j + 1];
            }
            numPayment--;
            saveInvoicesToFile();
            saveProducts();
            printf("\nInvoice deleted successfully.\n");
            found = true;
            break;
        }
    }
    
    if (!found) {
        printf("\nInvoice not found.\n");
    }
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
				addInvoice();
				break;
			}
			case 2: {
				printf("\n");
				printInvoices();
				break;
			}
			case 3: {
				printf("\n");
				deleteInvoice();
				break;
			}
			case 4:{
				return;
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
	loadCustomerData();
	loadProducts();
	loadInvoicesFromFile();
	int option;
	do {
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("|           -DRUG MANAGEMENT TOOL-           |\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("| 1 | Store management		 				\n");
		printf("| 2 | Customer management			     	\n");
		printf("| 3 | Payment			     				\n");
		printf("| 4 | Exit			     					\n");
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
				PaymentMenu();
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
	} while (option != 4);
	return 0;
}