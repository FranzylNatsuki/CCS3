#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define SIZE 10

typedef struct groceryItems *nd;
struct groceryItems {
	int itemCode;
	char itemName[15];
	char manufacturer[15];
	char productType[15];
	float price;
	int currentStock;
	nd next;
} 	GROCERY;

void menu(void);
int menuChoice(void);
void addRecord(nd *head);
void DisplayAllRecords(nd *head);
void dataEntry(nd *head, int *itemCode, char itemName[15], char manufacturer[15], char productType[15], float *price, int *currentStock);
void editRecord(nd *head);
void typeSearch(nd *head);
void nameSearch(nd *head);
void deleteRecord(nd *head);
void typeDelete(nd *head);
void nameDelete(nd *head);
void displayType(nd *head);
void displayManufacturer(nd *head);


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

void addRecord(nd *head) {
    int CODE;
	char NAME[15];
	char MANU[15];
	char TYPE[15];
	float PRICE;
	int STOCK;
    nd p, temp = NULL;

    if (*head == NULL) {
        *head = malloc(sizeof(GROCERY));
        (*head)->next = NULL;
        dataEntry(&head, &CODE, NAME, MANU, TYPE, &PRICE, &STOCK);
        // data assignments
        (*head)->itemCode = CODE;
        strcpy((*head)->itemName, NAME);
        strcpy((*head)->manufacturer, MANU);
        strcpy((*head)->productType, TYPE);
        (*head)->price = PRICE;
        (*head)->currentStock = STOCK;
        return;
    }

    else {
        temp = malloc(sizeof(GROCERY));
        dataEntry(&head, &CODE, NAME, MANU, TYPE, &PRICE, &STOCK);

        temp->itemCode = CODE;
        strcpy(temp->itemName, NAME);
        strcpy(temp->manufacturer, MANU);
        strcpy(temp->productType, TYPE);
        temp->price = PRICE;
        temp->currentStock = STOCK;
        temp->next = NULL;

        if (CODE < (*head)->itemCode) {
            temp->next = *head;
            *head = temp;
            return;
        }

        else {
            p = *head;
            // this while loop basically moves if the temp code is bigger
            while (p->next != NULL && p->next->itemCode < CODE) {
                p = p->next;
            }

            temp->next = p->next;
            p->next = temp;
        }
    }
}

void DisplayAllRecords(nd *head) {
    nd h = *head, p;
    p = h;
	printf("Displaying all records:\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	while (p != NULL) {
		printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
        p = p->next;
	}
	printf("Press [Enter] to proceed!");
  	getch();
  	system("cls");
}

void dataEntry(nd *head, int *itemCode, char itemName[15], char manufacturer[15], char productType[15], float *price, int *currentStock) {
	nd p = *head;
    int ITEMCODE;
	char ITEMNAME[15];
	char MANUFACTURER[15];
	char TYPE[15];
	float PRICE;
	int STOCK;
	int duplicateCheck = 0;
	
	do {
	    printf("Item Code (10000 - 99999):");
	    scanf("%d", &ITEMCODE);
	    getchar();
	
		while (p != NULL) {
			if (ITEMCODE == p->itemCode) {
				duplicateCheck = 1;
				break;
			}
			p = p->next;
		}
		p = *head;
	
	    if (ITEMCODE < 10000 || ITEMCODE > 99999) {
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
	
	*itemCode = ITEMCODE;
	system("cls");

	do {
	    printf("Item Name:");
	    gets(ITEMNAME);
	    
	    while (p != NULL) {
			if (strcmpi(ITEMNAME, p->itemName) == 0) {
				duplicateCheck = 1;
				break;
			}
			p = p->next;
		}
		p = *head;
	    
	    if (strlen(ITEMNAME) == 0) {
	        printf("Item Name should not be blank");
	        getch();
	        system("cls");
	    }
	} while (strlen(ITEMNAME) == 0 || duplicateCheck == 1);
	
	strcpy(itemName, ITEMNAME);
	system("cls");
	fflush(stdin);

	do {
		printf("Manufacturer:");
	    gets(MANUFACTURER);
	    
	    while (p != NULL) {
			if (strcmpi(MANUFACTURER, p->itemName) == 0) {
				duplicateCheck = 1;
				break;
			}
			p = p->next;
		}
		p = *head;
		
	    if (strlen(MANUFACTURER) == 0) {
	        printf("Manufacturer should not be blank");
	        getch();
	        system("cls");
	    }
	} while (strlen(MANUFACTURER) == 0 || duplicateCheck == 1);
	strcpy(manufacturer, MANUFACTURER);
	system("cls");
	fflush(stdin);
	
	do {
		printf("Type:");
	    gets(TYPE);
	    
	    while (p != NULL) {
			if (strcmpi(TYPE, p->productType) == 0) {
				duplicateCheck = 1;
				break;
			}
			p = p->next;
		}
		p = *head;
		
	    if (strlen(TYPE) == 0) {
	        printf("Item Type should not be blank");
	        getch();
	        system("cls");
	    }
	} while (strlen(TYPE) == 0 || duplicateCheck == 1);
	strcpy(productType, TYPE);
	system("cls");
	fflush(stdin);

    do {
		printf("Price:");
		scanf("%f", &PRICE);
		if (price <= 0) {
			printf("Price should not be zero");
			getch();
			system("cls");
		}
	} while (PRICE <= 0);

	*price = PRICE;
	system("cls");

    printf("Stock:");
	scanf("%d", &STOCK);
	*currentStock = STOCK;
	system("cls");

	printf("Added Record. Press [Enter] to proceed!");
	getch();
	system("cls");
}

void editRecord(nd *head) {
	int choice;
	do {
		printf("Search via Item Code or Item Name:\n");
		printf("1. Item Type:\n");
		printf("2. Item Name:\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				typeSearch(head);
				break;
			case 2:
				nameSearch(head);
				break;
			default:
				printf("Invalid Option, press [Enter] to retry");
				getch();
				system("cls");
		}
	} while (choice < 1 || choice > 2);
}

void typeSearch(nd *head){
	nd p = *head;
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	getchar();
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	
	int found = 0;

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	while (p != NULL) {
		searchcheck = strcmpi(p->productType, search);
		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
			found += 1;
			searchIndex = i;
			break;
		}
		p = p->next;
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
				p->price = price;
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
			p->currentStock = stock;
			system("cls");
		}
	}

	else if (found > 1) {
		fflush(stdin); 
		// to make sure no issues come up with the strings in the function below
		nameSearch(head);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameSearch(nd *head){
	char search[15];
    int i, searchcheck, searchIndex;
    nd p = *head;

    printf("Item Name: ");
    // using this to fix some missing characters
    fflush(stdin);
    // swapping gets() for fgets() due to buffer issues only on this part (after finding more than 1 of the same type)
    fgets(search, sizeof(search), stdin); 
    search[strcspn(search, "\n")] = '\0';

	int found = 0;

	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");

	while (p != NULL) {
		searchcheck = strcmpi(p->itemName, search);
		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
			found = 1;
			searchIndex = i;
		}
		p = p->next;
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
				p->price = price;
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
			p->currentStock = stock;
			system("cls");
		}
	}

	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void deleteRecord(nd *head) {
	int choice;
	do {
		printf("Search via Item Code or Item Name:\n");
		printf("1. Item Type:\n");
		printf("2. Item Name:\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				typeDelete(head);
				break;
			case 2:
				nameDelete(head);
				break;
			default:
				printf("Invalid Option, press [Enter] to retry");
				getch();
				system("cls");
		}
	} while (choice < 1 || choice > 2);	
}

void typeDelete(nd *head) {
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
            (*count)--;
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
		fflush(stdin);
		nameDelete(ItemRecords, count);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameDelete(nd *head) {
    char search[15];
    int i, searchcheck, searchIndex;

    printf("Item Name: ");
    fflush(stdin);
    // swapping gets() for fgets() due to buffer issues only on this part (after finding more than 1 of the same type)
    fgets(search, sizeof(search), stdin); 
    search[strcspn(search, "\n")] = '\0';

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

void displayType(nd *head) {
	nd p = *head;
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Item Type:");
	getchar();
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	while (p != NULL) {
		searchcheck = strcmpi(p->productType, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
		}
		p = p->next;
	}
	p = *head;
	
	getch();
	system("cls");
}

void displayManufacturer(nd *head) {
	char search[15];
	int i, searchcheck, searchIndex;

	printf("Manufacturer:");
	getchar();
	fflush(stdin);
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
	

	printf("Item Type: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	while (p != NULL) {
		searchcheck = strcmpi(p->manufacturer, search);

		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
		}
		p = p->next;
	}
	p = *head;
	
	getch();
	system("cls");
}

int main(void) {
	int choice;
	nd head = NULL;

	do {
	    menu();
	    choice = menuChoice();
	    switch (choice) {
	      	case 1:
		        addRecord(&head);
		        break;
	      	case 2:
	      		editRecord(&head);
		        break;
	      	case 3:
	      		// deleteRecord(&head);
		        break;
	      	case 4:
	      		displayType(&head);
		        break;
	      	case 5:
	      		displayManufacturer(&head);
		        break;
	      	case 6:
		        DisplayAllRecords(&head);
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