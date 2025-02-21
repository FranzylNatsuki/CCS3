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

void nameSearch(GROCERY ItemRecords[SIZE], int count) {
	char search[15];
	int i, searchcheck, searchIndex;
	
	printf("Item Name:");
	getchar();
	gets(search);
	
	int found = 0;
	
	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].itemName, search);
		
		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found = 1;
		}
		
		searchIndex = i;
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
		        break;	
	      	case 4:
		        break;			
	      	case 5:
		        break;					    
	      	case 6:
		        DisplayAllRecords(ItemRecords, recordCount);
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
		printf("RECORDS FULL!");
		return;
	}
	
	int itemCode;
	char itemName[20];
	char manufacturer[20]; 
	char type[20];
	float price; 
	int stock;
	
	do {
		printf("Item Code (10000 - 99999):");
		scanf("%d", &itemCode);
		getchar();
		ItemRecords[*count].itemCode = itemCode;
		if (itemCode < 10000 || itemCode > 99999) {
			printf("Item Code not in range, press enter to retry");
			getch();
			system("cls");
		}
		system("cls");
	} while (itemCode < 10000 || itemCode > 99999);
	
	do {
	printf("Item Name:");
	gets(itemName);
	strcpy(ItemRecords[*count].itemName, itemName);
		if (strlen(itemName) == 0) {
			printf("Item Name should not be blank");
			getch();
			system("cls");
		}
	system("cls");
	} while (strlen(itemName) == 0);

	do {
	printf("Manufacturer:");
	gets(manufacturer);
	strcpy(ItemRecords[*count].manufacturer, manufacturer);
		if (strlen(itemName) == 0) {
			printf("Manufacturer should not be blank");
			getch();
			system("cls");
		}
	system("cls");
	} while (strlen(itemName) == 0);
	
	
	do {
	printf("Type:");
	gets(type);
	strcpy(ItemRecords[*count].productType, type);
		if (strlen(itemName) == 0) {
			printf("Item Type should not be blank");
			getch();
			system("cls");
		}
	system("cls");
	} while (strlen(itemName) == 0);

	do {	
	printf("Price:");
	scanf("%f", &price);
	getchar();
	ItemRecords[*count].price = price;
		if (price <= 0) {
			printf("Price should not be zero");
			getch();
			system("cls");
		}
	system("cls");
	} while (price <= 0);

	printf("Stock:");
	scanf("%d", &stock);
	getchar();
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
		printf("1. Item type:\n");
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
	gets(search);
	
	int found = 0;
	
	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	for (i = 0; i < count; i++) {
		searchcheck = strcmpi(ItemRecords[i].productType, search);
		
		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", ItemRecords[i].itemCode, ItemRecords[i].itemName, ItemRecords[i].manufacturer, ItemRecords[i].productType, ItemRecords[i].price, ItemRecords[i].currentStock);
			found += 1;
		}
		
		searchIndex = i;
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
		} while (choice < 1 || choice >2);
		
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
		
		else if (choice == 2) {
			int stock;
			printf("Stock:");
			scanf("%d", &stock);
			getchar();
			ItemRecords[searchIndex].currentStock = stock;
			system("cls");
		}
	}
	
	if (found > 1) {
		nameSearch(ItemRecords, count);
	}
	
	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}
