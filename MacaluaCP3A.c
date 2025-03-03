/*
Summary: Make a grocery store management system that allows you to add records, search and edit their price and stock,
search and delete entries based on type/name and then display all, by type, or by manufacturer
*/
//  Made by: Franzyl Bjorn L. Macalua
// Created on: February 20, 2025
// Finished on: March 2, 2025

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 10
#define STRING_LIMIT 20

typedef struct groceryItems {
	int itemCode;
	char itemName[STRING_LIMIT];
	char manufacturer[STRING_LIMIT];
	char productType[STRING_LIMIT];
	float price;
	int currentStock;
} 	GROCERY;

void menu(void);
// reusable menu functions
int menuChoice(void);
// recieve choice for menu
void addRecord(GROCERY ItemRecords[SIZE], int *count);
// adds an entry to the record
void editRecord(GROCERY ItemRecords[SIZE], int *count);
// contains the search system, and calls on the editing functions
void DisplayAllRecords(GROCERY ItemRecords[SIZE], int count);
// prints all records
void structureSort(GROCERY ItemRecords[SIZE], int count);
// recreated a simple bubble sort
void typeSearch(GROCERY ItemRecords[SIZE], int count);
// does string compare by type to find any results
void nameSearch(GROCERY ItemRecords[SIZE], int count);
// does string compare by name to find any results
void deleteRecord(GROCERY ItemRecords[SIZE], int *count);
// contains the delete functions
void typeDelete(GROCERY ItemRecords[SIZE], int *count);
// deletes by type
void nameDelete(GROCERY ItemRecords[SIZE], int *count);
// delete by name
void displayType(GROCERY ItemRecords[SIZE], int count);
// prints any element by type that is searched for
void displayManufacturer(GROCERY ItemRecords[SIZE], int count);
// prints any element by manufacturer that is searched for

int main(void) {
	int choice;
	int recordCount = 0;
	// keeps track of Actual array size
	GROCERY ItemRecords[SIZE];
    // declare the structure to be used

	do {
	    menu();
	    choice = menuChoice();
	    switch (choice) {
	      	case 1:
		        addRecord(ItemRecords, &recordCount);
		        break;
	      	case 2:
	      		editRecord(ItemRecords, &recordCount);
		        break;
	      	case 3:
	      		deleteRecord(ItemRecords, &recordCount);
		        break;
	      	case 4:
	      		displayType(ItemRecords, recordCount);
		        break;
	      	case 5:
	      		displayManufacturer(ItemRecords, recordCount);
		        break;
	      	case 6:
		        DisplayAllRecords(ItemRecords, recordCount);
		        break;
		    case 7:
		    	return 0;
		    	break;
	    }
		if (choice != 7 && (choice < 1 || choice > 7)) {
			printf("Invalid Input, Press [Enter] to Retry");
			getch();
			system("cls");
		}
	} while (choice != 7);

	return 0;
}

void menu(void) {
	printf("MAIN MENU\n");
	printf("1. Add a Record\n");
	printf("2. Edit a Record\n");
	printf("3. Delete a Record\n");
	printf("4. Display All Records of a particular type\n");
	printf("5. Display All Records from a particular company\n");
	printf("6. Display All Records\n");
	printf("7. Exit the program\n");
}

int menuChoice(void){
	int choice;
	scanf("%d", &choice);
	return choice;
}

void addRecord(GROCERY ItemRecords[SIZE], int *count) {
	system("cls");
	// Limiter to check if you are at max capacity
	if (*count >= SIZE) {
        system("cls");
		printf("Records Full!");
		getch();
        system("cls");
		return;
	}

	int itemCode;
	char itemName[STRING_LIMIT];
	char manufacturer[STRING_LIMIT];
	char type[STRING_LIMIT];
	float price;
	int stock;
	int duplicateCheck;

	do {
		duplicateCheck = 0;
		printf("Item Code (10000 - 99999):");
		scanf("%d", &itemCode);
        getchar();

		for (int i = 0; i < *count; i++) {
			if (itemCode == ItemRecords[i].itemCode) {
				duplicateCheck = 1;
				break;
			}
		}
		// go through all the entries to see if theres another item code existing already
		if (itemCode < 10000 || itemCode > 99999) {
			printf("Item Code not in range, press enter to retry");
			getch();
			system("cls");
		}
		else if (duplicateCheck == 1) {
			printf("Already an existing item code, press enter to retry");
			getch();
			system("cls");
		}
	} while (itemCode < 10000 || itemCode > 99999 || duplicateCheck == 1);

	ItemRecords[*count].itemCode = itemCode;
	system("cls");
    // assign the new code
	do {
		duplicateCheck = 0;
		printf("Item Name:");
		gets(itemName);
		for (int i = 0; i < *count; i++) {
			if (strcmpi(itemName, ItemRecords[i].itemName) == 0) {
				duplicateCheck = 1;
				break;
			}
		}
		// using strlen to check if the user inputted nothing
		if (strlen(itemName) == 0) {
			printf("Item Name should not be blank");
			getch();
			system("cls");
		}
		else if (duplicateCheck == 1) {
			printf("Already an existing item name, press enter to retry");
			getch();
			system("cls");
		}
	} while (strlen(itemName) == 0 || duplicateCheck == 1);
    // strcpy to assign the new string
	strcpy(ItemRecords[*count].itemName, itemName);
	system("cls");

	do {
		printf("Manufacturer:");
		gets(manufacturer);
		if (strlen(manufacturer) == 0) {
			printf("Manufacturer should not be blank");
			getch();
			system("cls");
		}
	} while (strlen(manufacturer) == 0);

	strcpy(ItemRecords[*count].manufacturer, manufacturer);
	system("cls");


	do {
		printf("Type:");
		gets(type);
		if (strlen(type) == 0) {
			printf("Item Type should not be blank");
			getch();
			system("cls");
		}
	} while (strlen(type) == 0);
	strcpy(ItemRecords[*count].productType, type);
	system("cls");

	do {
		printf("Price:");
		scanf("%f", &price);
		if (price <= 0) {
			printf("Price should not be zero");
			getch();
			system("cls");
		}
	} while (price <= 0);

	ItemRecords[*count].price = price;
	system("cls");

	printf("Stock:");
	scanf("%d", &stock);
	ItemRecords[*count].currentStock = stock;
	system("cls");

	printf("Added Record. Press [Enter] to proceed!");
	getch();
	system("cls");
	(*count)++;
    // add an element
	structureSort(ItemRecords, *count);

	return;
}

void editRecord(GROCERY ItemRecords[SIZE], int *count) {
	int choice;
	do {
		printf("Search via Item Code or Item Name:\n");
		printf("1. Item Type:\n");
		printf("2. Item Name:\n");
		scanf("%d", &choice);
        fflush(stdin);
        // using fflush to fix certain buffer issues in other parts
		switch (choice) {
			case 1:
				typeSearch(ItemRecords, *count);
				break;
			case 2:
				nameSearch(ItemRecords, *count);
				break;
			default:
				printf("Invalid Option, press [Enter] to retry");
				getch();
				system("cls");
		}
	} while (choice < 1 || choice > 2);
}

void DisplayAllRecords(GROCERY ItemRecords[SIZE], int count) {
	printf("Displaying all records:\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	for (int i = 0; i < count; i++) {
		printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
	}
	printf("Press [Enter] to proceed!");
  	getch();
  	system("cls");
}

void structureSort(GROCERY ItemRecords[SIZE], int count) {
    GROCERY temporary;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ItemRecords[j].itemCode > ItemRecords[j + 1].itemCode) {
                temporary = ItemRecords[j];
                ItemRecords[j] = ItemRecords[j + 1];
                ItemRecords[j + 1]= temporary;
            }
        }
    } // just a bubble sort
}

void typeSearch(GROCERY ItemRecords[SIZE], int count) {
	char search[STRING_LIMIT];
	int i, searchcheck, searchIndex;
    // search check acts as a boolean with strcmpi, searchIndex determines which element to edit
	printf("Item Type:");
    fflush(stdin);
    gets(search);

	int found = 0;

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");

	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].productType, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found += 1;
			searchIndex = i;
		}
	}

	if (found == 1) {
		int choice;
		do {
			printf("Edit Element:\n");
			printf("1 Price:\n");
			printf("2 Stock:\n");
			scanf("%d", &choice);
			getchar();
			if (choice < 1 || choice >2) {
				printf("Invalid Input, Press [Enter] to Retry");
				getch();
				system("cls");
			}
		} while (choice < 1 || choice >2);

		if (choice == 1) {
			float price;
			do {
				printf("Price:");
				scanf("%f", &price);
				getchar();
				ItemRecords[searchIndex].price = price;
					if (price <= 0) {
						printf("Price should not be zero");
						getch();
						system("cls");
					}
				system("cls");
			} while (price <= 0);
		}

		else if (choice == 2) {
			int stock;
			printf("Stock:");
			scanf("%d", &stock);
			getchar();
			ItemRecords[searchIndex].currentStock = stock;
			system("cls");
		}
	}

	else if (found > 1) {
		fflush(stdin);
		// to make sure no issues come up with the strings in the function below
		nameSearch(ItemRecords, count);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameSearch(GROCERY ItemRecords[SIZE], int count) {
    char search[STRING_LIMIT];
    int i, searchcheck, searchIndex;

    printf("Item Name: ");
    // using this to fix some missing characters
    fflush(stdin);
    gets(search);
	int found = 0;

	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");

	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].itemName, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found = 1;
			searchIndex = i;
		}
	}

	if (found == 1) {
		int choice;
		do {
			printf("Edit Element:\n");
			printf("1 Price:\n");
			printf("2 Stock:\n");
			scanf("%d", &choice);
			if (choice < 1 || choice >2) {
				printf("Invalid Input, Press [Enter] to Retry");
				getch();
				system("cls");
			}
		} while (choice < 1 || choice > 2);

		if (choice == 1) {
			float price;
			do {
				printf("Price:");
				scanf("%f", &price);
				ItemRecords[searchIndex].price = price;
					if (price <= 0) {
						printf("Price should not be zero");
						getch();
						system("cls");
					}
				system("cls");
			} while (price <= 0);
		}

		if (choice == 2) {
			int stock;
			printf("Stock:");
			scanf("%d", &stock);
			getchar();
			ItemRecords[searchIndex].currentStock = stock;
			system("cls");
		}
	}

	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void deleteRecord(GROCERY ItemRecords[SIZE], int *count) {
	int choice;
	do {
		printf("Search via Item Code or Item Name:\n");
		printf("1. Item Type:\n");
		printf("2. Item Name:\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				typeDelete(ItemRecords, count);
				break;
			case 2:
				nameDelete(ItemRecords, count);
				break;
			default:
				printf("Invalid Option, press [Enter] to retry");
				getch();
				system("cls");
		}
	} while (choice < 1 || choice > 2);
}

void typeDelete(GROCERY ItemRecords[SIZE], int *count) {
	char search[STRING_LIMIT];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
    fflush(stdin);
    gets(search);

	int found = 0;

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");

	for (i = 0; i < *count; i++) {
		searchcheck = strcmpi(ItemRecords[i].productType, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found += 1;
			searchIndex = i;
		}
	}

	if (found == 1) {
		char choice;
		do {
			printf("Confirm Delete (Data cannot be retrieved)? Y/n\n");
			scanf("%c", &choice);
			if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
				printf("Invalid Input, Press [Enter] to Retry");
				getch();
				system("cls");
			}
		} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

		if (choice == 'Y' || choice == 'y') {
			for (i = searchIndex; i < *count - 1; i++) {
                ItemRecords[i] = ItemRecords[i + 1];
            }
            // start from the selected element, then replace it with every element next to it
            (*count)--;
            // remove the slot in the count variable
			printf("Item successfully deleted!\n");
			getch();
			system("cls");
			return;
		}

		else if (choice == 'N' || choice == 'n') {
            system("cls");
			return;
		}
	}

	else if (found > 1) {
		fflush(stdin);
		nameDelete(ItemRecords, count);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameDelete(GROCERY ItemRecords[SIZE], int *count) {
    char search[STRING_LIMIT];
    int i, searchcheck, searchIndex;

    printf("Item Name: ");
    fflush(stdin);
    gets(search);

	int found = 0;

	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");

	for (i = 0; i < *count; i++) {
		searchcheck = strcmpi(ItemRecords[i].itemName, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found = 1;
			searchIndex = i;
		}
	}

	if (found == 1) {
		char choice;
		do {
			printf("Confirm Delete (Data cannot be retrieved)? Y/n\n");
			scanf("%c", &choice);
			if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
				printf("Invalid Input, Press [Enter] to Retry");
				getch();
				system("cls");
			}
		} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

		if (choice == 'Y' || choice == 'y') {
			for (i = searchIndex; i < *count - 1; i++) {
                ItemRecords[i] = ItemRecords[i + 1];
            }
            (*count)--;
			printf("Item successfully deleted!\n");
			getch();
			system("cls");
			return;
		}

		else if (choice == 'N' || choice == 'n') {
            system("cls");
			return;
		}
	}

	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void displayType(GROCERY ItemRecords[SIZE], int count) {
	char search[STRING_LIMIT];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	fflush(stdin);
    gets(search);

	int found = 0;

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].productType, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
		}
	}
	getch();
	system("cls");
}

void displayManufacturer(GROCERY ItemRecords[SIZE], int count) {
	char search[STRING_LIMIT];
	int i, searchcheck, searchIndex;

	printf("Manufacturer:");
	fflush(stdin);
    gets(search);

	int found = 0;

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].manufacturer, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
		}
	}
	getch();
	system("cls");
}
