#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define SIZE 10

typedef struct groceryItems {
	int itemCode;
	char itemName[15];
	char manufacturer[15];
	char productType[15];
	float price;
	int currentStock;
} 	GROCERY;

void menu(void);
int menuChoice(void);
void addRecord(GROCERY ItemRecords[SIZE], int *count);
void editRecord(GROCERY ItemRecords[SIZE], int *count);
void DisplayAllRecords(GROCERY ItemRecords[SIZE], int count);
void structureSort(GROCERY ItemRecords[SIZE], int count);
void typeSearch(GROCERY ItemRecords[SIZE], int count);
void nameSearch(GROCERY ItemRecords[SIZE], int count);
void deleteRecord(GROCERY ItemRecords[SIZE], int *count);
void typeDelete(GROCERY ItemRecords[SIZE], int count);
void nameDelete(GROCERY ItemRecords[SIZE], int count);
void displayType(GROCERY ItemRecords[SIZE], int count);
void displayManufacturer(GROCERY ItemRecords[SIZE], int count);

int main(void) {
	int choice;
	int recordCount = 0;
	GROCERY ItemRecords[SIZE];

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
	if (*count >= SIZE) {
		printf("Records Full!");
		return;
	}

	int itemCode;
	char itemName[20];
	char manufacturer[20];
	char type[20];
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
    }
}

void typeSearch(GROCERY ItemRecords[SIZE], int count) {
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	getchar();
    // Use fgets() instead of gets() due to some buffer overflow problems
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	
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
		nameSearch(ItemRecords, count);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameSearch(GROCERY ItemRecords[SIZE], int count) {
    char search[15];
    int i, searchcheck, searchIndex;

    printf("Item Name: ");
    getchar();
    // swapping gets() for fgets() due to buffer issues only on this part (after finding more than 1 of the same type)
    fgets(search, sizeof(search), stdin); 
    search[strcspn(search, "\n")] = '\0';

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
				typeDelete(ItemRecords, *count);
				break;
			case 2:
				nameDelete(ItemRecords, *count);
				break;
			default:
				printf("Invalid Option, press [Enter] to retry");
				getch();
				system("cls");
		}
	} while (choice < 1 || choice > 2);
}

void typeDelete(GROCERY ItemRecords[SIZE], int count) {
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	getchar();
    // Use fgets() instead of gets() due to some buffer overflow problems
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	
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
			for (i = searchIndex; i < count - 1; i++) {
                ItemRecords[i] = ItemRecords[i + 1];
            }
			(count)--;
			printf("Item successfully deleted!\n");
			getch();
			system("cls");
			return;
		}

		else if (choice == 'Y' || choice == 'y') {
			return;
		}
	}

	else if (found > 1) {
		nameDelete(ItemRecords, count);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameDelete(GROCERY ItemRecords[SIZE], int count) {
    char search[15];
    int i, searchcheck, searchIndex;

    printf("Item Name: ");
    getchar();
    // swapping gets() for fgets() due to buffer issues only on this part (after finding more than 1 of the same type)
    fgets(search, sizeof(search), stdin); 
    search[strcspn(search, "\n")] = '\0';

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
			for (i = searchIndex; i < count - 1; i++) {
                ItemRecords[i] = ItemRecords[i + 1];
            }
			(count)--;
			printf("Item successfully deleted!\n");
			getch();
			system("cls");
			return;
		}

		else if (choice == 'Y' || choice == 'y') {
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
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	getchar();
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	
	int found = 0;
	
	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].productType, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
		}
	}
}

void displayManufacturer(GROCERY ItemRecords[SIZE], int count) {
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Manufacturer:");
	getchar();
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	
	int found = 0;
	
	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].manufacturer, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
		}
	}	
}
