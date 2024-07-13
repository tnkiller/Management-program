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
char paymentCustomerPhoneNum[MAX_PAYMENT][MAX_CUSTOMER_NAME_LENGTH];
char paymentProductNames[MAX_PAYMENT][MAX_PRODUCT_NAME_LENGTH];
int paymentQuantities[MAX_PAYMENT];
double paymentTotals[MAX_PAYMENT];
int numPayment = 0;
/*--------------------------------------------------------------------------------------------------------------------*/
/*FILE*/
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
    printf("%-25s  %-10s | %-10s | %-10s |1 %-20s\n", "Name", "Quantity", "Price", "Unit", "Expire date");
	printf("\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%-25s   %-10d   %-10.2f   %-10s   %-20s\n", drugName[i], drugQuantity[i], drugPrice[i], drugUnit[i], drugDate[i]);
    }
    printf("------------------------------------------------------------------------------\n");
}

//Add new
// Add new product
void addProduct() {
    printf("Enter drug name: ");
    getchar(); // Consume newline character left by the previous input
    fgets(drugName[numProducts], MAX_PRODUCT_NAME_LENGTH, stdin);
    drugName[numProducts][strcspn(drugName[numProducts], "\n")] = '\0'; // Remove newline character

    printf("Enter drug quantity: ");
    scanf("%d", &drugQuantity[numProducts]);

    printf("Enter product price: ");
    scanf("%f", &drugPrice[numProducts]);

    printf("Enter drug unit: ");
    getchar(); // Consume newline character left by the previous input
    fgets(drugUnit[numProducts], MAX_UNIT_LENGTH, stdin);
    drugUnit[numProducts][strcspn(drugUnit[numProducts], "\n")] = '\0'; // Remove newline character

    printf("Enter drug expiry date: ");
    fgets(drugDate[numProducts], MAX_DATE_LENGTH, stdin);
    drugDate[numProducts][strcspn(drugDate[numProducts], "\n")] = '\0'; // Remove newline character

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

///*Customer menu*/
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
			case 2:{
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
			case 5:{
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




/*---------------------------------------------------------------------------------------------------------------------------*/
///*PAYMENT*/
// Add a new invoice
void addInvoice() {
	char customerId[100], productId[100];
	int quantity;

	printf("Enter new customer ID: ");
	getchar();
	gets(customerId);

	// Check if customer exists
	int customerIndex = -1;
	for (int i = 0; i < numCustomers; i++) {
		if (strcmpi(customerID[i],customerId) == 0) {
			customerIndex = i;
			break;
		}
	}

	if (customerIndex == -1) {
		printf("\nCustomer unavailable.\n");
		addCustomer();
	}

	printf("Enter product ID: ");
	getchar();
	gets(productId);

	// Check if product exists and has enough quantity
	int productIndex = -1;
	for (int i = 0; i < numProducts; i++) {
		if (strcmpi(productID[i],productId) == 0) {
			productIndex = i;
			break;
		}
	}

	if (productIndex == -1) {
		printf("\nProduct unavailable");
		addProduct();
	}

	printf("Enter quantity purchased: ");
	scanf("%d", &quantity);

	// Check if there is enough quantity
	if (productQuantity[productIndex] < quantity) {
		printf("\nNot enough!\n");
		return;
	}

	// Update product quantity
	productQuantity[productIndex] -= quantity;

	// Create invoice
	strcpy(invoiceCustomerIDs[numInvoices], customerID[customerIndex]);
	strcpy(invoiceCustomerNames[numInvoices], customerName[customerIndex]);
	strcpy(invoiceCustomerPhoneNum[numInvoices], customerPhoneNum[customerIndex]);
	strcpy(invoiceProductIDs[numInvoices],productId);
	strcpy(invoiceProductNames[numInvoices], productName[productIndex]);
	invoiceQuantities[numInvoices] = quantity;
	invoiceTotals[numInvoices] = quantity * productPrice[productIndex];
	numInvoices++;

	saveInvoicesToFile();
	saveProductsToFile();
	printf("\nInvoice added successfully.\n");
}

// Delete an invoice by ID
void deleteInvoice() {
	char customerId[100], productId[100];
	printf("Enter customer ID of the invoice to delete: ");
	getchar();
	gets(customerId);
	printf("Enter product ID of the invoice to delete: ");
	gets(productId);

	for (int i = 0; i < numInvoices; i++) {
		if (strcmpi(invoiceCustomerIDs[i],customerId) == 0 && strcmpi(invoiceProductIDs[i],productId) == 0) {
			// Restore product quantity
			for (int j = 0; j < numProducts; j++) {
				if (productID[j] == productId) {
					productQuantity[j] += invoiceQuantities[i];
					break;
				}
			}
			// Shift invoices
			for (int j = i; j < numInvoices - 1; j++) {
				strcpy(invoiceCustomerIDs[j], invoiceCustomerIDs[j + 1]);
				strcpy(invoiceCustomerNames[j], invoiceCustomerNames[j + 1]);
				strcpy(invoiceCustomerPhoneNum[j], invoiceCustomerPhoneNum[j + 1]);
				strcpy(invoiceProductIDs[j],invoiceProductIDs[j + 1]);
				strcpy(invoiceProductNames[j], invoiceProductNames[j + 1]);
				invoiceQuantities[j] = invoiceQuantities[j + 1];
				invoiceTotals[j] = invoiceTotals[j + 1];
			}
			numInvoices--;
			saveInvoicesToFile();
			saveProductsToFile();
			printf("\nInvoice deleted successfully\n");
			return;
		}
	}
	printf("\nInvoice not found\n");
}

double calculateTotalSum() {
	loadInvoicesFromFile();
	double totalSum = 0;
	for (int i = 0; i < numInvoices; i++) {
		totalSum += invoiceTotals[i];
	}
	return totalSum;
}

// Print invoice list
void printInvoices() {
	printf("\n------------------------------ Payment List ------------------------------\n");
	printf("%-10s | %-20s | %-20s | %-10s | %-20s | %-10s | %-10s\n", "Cust ID", "Cust Name", "Cust PhoneNum", "Prod ID", "Prod Name", "Quantity", "Total");
	printf("----------------------------------------------------------------------------\n");
	for (int i = 0; i < numInvoices; i++) {
		printf("%-10d | %-20s | %-20s | %-10d | %-20s | %-10d | %-10f\n", invoiceCustomerIDs[i], invoiceCustomerNames[i], invoiceCustomerPhoneNum[i], invoiceProductIDs[i], invoiceProductNames[i], invoiceQuantities[i], invoiceTotals[i]);
	}
	printf("----------------------------------------------------------------------------\n");
}


void invoiceMenu() {
	int choice;
	while (1) {
		printf("\n========================== Invoice Management ==========================\n");
		printf("1.Purchase\n");
		printf("2. Print payment\n");
		printf("3. Delete payment\n");
		printf("4. Total money of payment\n");
		printf("5. Back\n");
		printf("=========================================================================\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				addInvoice();
				break;
			case 2:
				printInvoices();
				break;
			case 3:
				deleteInvoice();
				break;
			case 4:
				printf("Total sum of all invoices: %.2f\n", calculateTotalSum());
				break;
			case 5:
				return;
			default:
				printf("\nInvalid choice. Please try again.\n");
		}
	}
}
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