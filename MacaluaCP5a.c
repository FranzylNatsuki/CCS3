/* 
Name: Franzyl Bjorn L. Macalua
Problem is to rebuild CP3 into the same body of work but using singly-linked lists as the
back bone of the program 
Date Created: April 1, 2025
Data Finished: April 9, 2025
*/

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
// a seperate Data Entry function to make the code more readable
void editRecord(nd *head);
void typeSearch(nd *head);
void nameSearch(nd *head);
void deleteRecord(nd *head);
void typeDelete(nd *head);
void nameDelete(nd *head);
void displayType(nd *head);
void displayManufacturer(nd *head);
// same function uses as CP3

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
    // declarations for my external pointers.

    if (*head == NULL) {
        *head = malloc(sizeof(GROCERY));
        (*head)->next = NULL;
        dataEntry(head, &CODE, NAME, MANU, TYPE, &PRICE, &STOCK);
        // data assignments
        (*head)->itemCode = CODE;
        strcpy((*head)->itemName, NAME);
        strcpy((*head)->manufacturer, MANU);
        strcpy((*head)->productType, TYPE);
        (*head)->price = PRICE;
        (*head)->currentStock = STOCK;
        return;
    }
    // creates a new node with data when the list is empty
	// block below deals with a pre-existing node/s
    else {
        temp = malloc(sizeof(GROCERY));
        dataEntry(head, &CODE, NAME, MANU, TYPE, &PRICE, &STOCK);
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
        // if the Code inputed is smaller than the head's code than it should go before

        else {
            p = *head;
            // this while loop basically moves if the temp code is bigger
            while (p->next != NULL && p->next->itemCode < CODE) {
                p = p->next;
            }
			// the temporary will go to where the next cell is and the cell before will link up to temp
            temp->next = p->next;
            p->next = temp;
        }
    }
}

void DisplayAllRecords(nd *head) {
    nd h = *head, p;
    p = h;
    int found = 0;
    // if there is no record at all
    if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}
    
	printf("Displaying all records:\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	while (p != NULL) {
		printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
        found++;
		p = p->next;
	}
	// a bunch of error messages
	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
		return;
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
	// same trappings as the previous work
	do {
        duplicateCheck = 0;
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
	} while (ITEMCODE < 10000 || ITEMCODE > 99999 || duplicateCheck == 1);

	*itemCode = ITEMCODE;
	system("cls");

	do {
        duplicateCheck = 0;
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

        else if (duplicateCheck == 1) {
			printf("Already an existing item name, press enter to retry");
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

	    if (strlen(MANUFACTURER) == 0) {
	        printf("Manufacturer should not be blank");
	        getch();
	        system("cls");
	    }
	} while (strlen(MANUFACTURER) == 0);

	strcpy(manufacturer, MANUFACTURER);
	system("cls");
	fflush(stdin);

	do {
		printf("Type:");
	    gets(TYPE);

	    if (strlen(TYPE) == 0) {
	        printf("Item Type should not be blank");
	        getch();
	        system("cls");
	    }
	} while (strlen(TYPE) == 0);

	strcpy(productType, TYPE);
	system("cls");
	fflush(stdin);

    do {
		printf("Price:");
		scanf("%f", &PRICE);
		if (PRICE <= 0) {
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
	
	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}	
	
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
	nd q = NULL, p = *head;
	char search[15];
	char confirmation;
	int i, searchcheck, found = 0;;

	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}

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
			found += 1;
			q = p;
			// use this in the case that there is really only 1 result, this makes p be able to check for multiple results
		}
		p = p->next;
		// traverse
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
				if (price <= 0) {
					printf("Price should not be zero");
					getch();
					system("cls");
				}
			} while (price <= 0);
			
			puts("The new data will be saved. Do you want to continue (Y/N)?");
			scanf(" %c", &confirmation);
			
			if (confirmation == 'Y' || confirmation == 'y') {
				q->price = price;
				system("cls");
			}
			else {
				system("cls");
				return;
			}
		}
		else if (choice == 2) {
			int stock;
			printf("Stock:");
			scanf("%d", &stock);
			getchar();
			
			puts("The new data will be saved. Do you want to continue (Y/N)?");
			scanf(" %c", &confirmation);
			
			if (confirmation == 'Y' || confirmation == 'y') {
				q->currentStock = stock;
				system("cls");
			}
			else {
				system("cls");
				return;
			}
		}
	}

	else if (found > 1) {
		fflush(stdin);
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
	char confirmation;
    int i, searchcheck, found = 0;
    nd p = *head;

	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}

    printf("Item Name: ");
    fflush(stdin);
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	// use just one pointer because I know there will be no duplicates as its trapped already
	while (p != NULL) {
		searchcheck = strcmpi(p->itemName, search);
		if (searchcheck == 0) {
			printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
			found = 1;
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
				if (price <= 0) {
					printf("Price should not be zero");
					getch();
					system("cls");
				}
				system("cls");
			} while (price <= 0);
			
			puts("The new data will be saved. Do you want to continue (Y/N)?");
			scanf(" %c", &confirmation);
			
			if (confirmation == 'Y' || confirmation == 'y') {
				p->price = price;
				system("cls");
			}
			else {
				system("cls");
				return;
			}
		}

		if (choice == 2) {
			int stock;
			printf("Stock:");
			scanf("%d", &stock);
			getchar();
			
			puts("The new data will be saved. Do you want to continue (Y/N)?");
			scanf(" %c", &confirmation);
			
			if (confirmation == 'Y' || confirmation == 'y') {
				p->currentStock = stock;
				system("cls");
			}
			else {
				system("cls");
				return;
			}
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
	
	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}
	
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
	nd p = *head;
	nd prev = NULL;
	nd Delete = NULL;
	nd prevDelete = NULL;
	int searchcheck, found = 0;
	// setting up a main pointer as well as a previous, Delete, and previous Delete	
	
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
	        found++;
	        Delete = p;
	        // for every iteration that it goes through the current node will be the one to be deleted
	        prevDelete = prev;
	        // prevDelete basically acts as a delayed pointer, refering to the cell before the to be deleted node
	    }
	    prev = p; // previous is a node behind p
	    p = p->next; // traverse
	}

	if (found == 1 && Delete != NULL) {
	    char choice;
	    printf("Confirm Delete? Y/n: ");
	    scanf(" %c", &choice);
	
	    if (choice == 'Y' || choice == 'y') {
	        if (prevDelete == NULL) {
	            // if the head is to be deleted (previous is NULL, delete is first element)
	            *head = Delete->next;
	            // make the next node the head
	        } else {
	            prevDelete->next = Delete->next;
	            // make the previous cell skip the deleted node, and go to the next
	        }
	        free(Delete);
	        // free the memory
	        printf("Deleted!\n");
	        getch();
			system("cls");
	    }
	    
	    else {
			system("cls");
			return;
		}
	}

	else if (found > 1 && Delete != NULL) {
		fflush(stdin);
		nameDelete(head);
	}

	else if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
	}
}

void nameDelete(nd *head) {
    char search[15];
    nd p = *head;
	nd prev = NULL;
	nd Delete = NULL;
	nd prevDelete = NULL;
	int searchcheck, found = 0;

    printf("Item Name: ");
    fflush(stdin);
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

	printf("Item Name: %s\n", search);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Item Code", "Item Name", "Manufacturer", "Product Type", "Price", "Stock");
	
	// similar logic to Type Delete
    while (p != NULL) {
    	searchcheck = strcmpi(p->itemName, search);
	    if (searchcheck == 0) {
	    	printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", p->itemCode, p->itemName, p->manufacturer, p->productType, p->price, p->currentStock);
	        found++;
	        Delete = p;
	        prevDelete = prev;
	    }
	    prev = p;
	    p = p->next;
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
            if (prevDelete == NULL) {
                *head = Delete->next; // Deleting head
            } else {
                prevDelete->next = Delete->next;
            }
	        free(Delete);
	        printf("Deleted!\n");
	        getch();
			system("cls");
		}

		else {
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

void displayType(nd *head) {
	nd p = *head;
	char search[15];
	int i, searchcheck, found = 0;

	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}

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
			found++;
		}
		p = p->next;
	}
	p = *head;
	
	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
		return;
	}

	getch();
	system("cls");
}

void displayManufacturer(nd *head) {
	char search[15];
	int i, searchcheck, found = 0;
	nd p = *head;

	if (*head == NULL) {
		puts("Sorry, there are no records in the list. Press any key to continue");
		getch();
		system("cls");
		return;
	}

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
			found++;
		}
		p = p->next;
	}
	p = *head;
	
	if (found == 0) {
		printf("No Result Found. Press [Enter] to proceed");
		getch();
		system("cls");
		return;
	}

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
	      		deleteRecord(&head);
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
