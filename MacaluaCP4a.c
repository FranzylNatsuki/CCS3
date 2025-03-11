// Franzyl Bjorn L. Macalua
/* Problem is to use 2d arrays to record the test scores of 10 students.
Storing them in one array and then calculating their statistics and showing
the 2d arrays in a table */
// Date Created: 3/10/2025
// Date Finished: 3/11/2025

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ROW 10
#define COLUMN 9

void dataInput(int record[][COLUMN]);
// inputs the data in each cell
void output(int record[][COLUMN]);
// contains all print statements
void lowScore(int record[][COLUMN]);
// scans through the array for the lowest value
void highScore(int record[][COLUMN]);
//scans through the array for the highest value
void averageScore(int record[][COLUMN]);
// calculates the sum of the arrays divided by amount of items

int main() {
    char choice;
    do {
        int record[ROW][COLUMN] = {0};
		// initializing all cells to zero, to be able to input a new of scores
        dataInput(record);
        lowScore(record);
        highScore(record);
        averageScore(record);
        system("cls");
        output(record);

        printf("Would you like to record another set? Y/n:");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            system("cls");
        }
    } while (choice == 'Y' || choice == 'y');

    return 0;
}

void dataInput(int record[][COLUMN]) {
    for (int i = 0; i < ROW; i++) {
        int studentID;
        int duplicateCheck;
        do {
        	duplicateCheck = 0;
        	
            printf("%d Student ID: ", i + 1);
            scanf("%d", &studentID);
			// this loop looks through all entries in record[][0] which contains all student IDs, in existing Rows
            for (int search = 0; search < i; search++) {
				if (studentID == record[search][0]) {
					duplicateCheck = 1;
					break;
				}
			}
			// trappings
            if (studentID < 1000 || studentID > 9999) {
                printf("Out of range! (Please select ID between 1000-9999)\n");
                getch();
                system("cls");
            }

            if (duplicateCheck == 1) {
				printf("Already an existing student code!");
				getch();
				system("cls");
            }
        } while (studentID < 1000 || studentID > 9999 || duplicateCheck == 1);

        record[i][0] = studentID;
		// write to array
        for (int j = 1; j < (COLUMN - 3); j++) {
        	// input data for column 1-5
            int quizScore;
            do {
                printf("Quiz %d:", j);
                scanf("%d", &quizScore);
                if (quizScore < 0 || quizScore > 100) {
                    printf("Out of range! (Please select ID between 1000-9999)\n");
                    getch();
                    system("cls");
                }
            } while (quizScore < 0 || quizScore > 100);
            record[i][j] = quizScore;
            //write all the scores
        }
        system("cls");
    }
}

void output(int record[][COLUMN]) {
    printf("%-13s%-13s%-13s%-13s%-13s%-13s%-13s%-13s%-13s\n", "Student ID", "Quiz 1", "Quiz 2", "Quiz 3", "Quiz 4", "Quiz 5", "Highest", "Lowest", "Average");

    for (int i = 0; i < ROW; i++) {
        printf("%-13d", record[i][0]);
        for (int j = 1; j < COLUMN; j++) {
            printf("%-13d", record[i][j]);
        }
        printf("\n");
    }
}

void lowScore(int record[][COLUMN]) {
    for (int i = 0; i < ROW; i++) {
        int smallest = record[i][1];
		// set the first quiz element as the lowest number
        for (int j = 1; j <= 5; j++) {
            if (record[i][j] < smallest) {
                smallest = record[i][j];
                // set the new lower number as current lowest
            }
        }
        record[i][7] = smallest;
        // write to 2nd column for calculated data
    }
}

void highScore(int record[][COLUMN]) {
    for (int i = 0; i < ROW; i++) {
    	// set the first quiz element as the biggest number
        int largest = record[i][1];

        for (int j = 1; j <= 5; j++) {
            if (record[i][j] > largest) {
                largest = record[i][j];
                // set the new large number as biggest
            }
        }
        record[i][6] = largest;
        // write to 1st column for calculated data
    }
}

void averageScore(int record[][COLUMN]) {
    for (int i = 0; i < ROW; i++){
        int sum = 0;
        for (int j = 1; j <= (COLUMN - 4); j++) {
            sum += record[i][j];
        }
        record[i][8] = sum / (COLUMN - 4);
        // the math for column 3
    }
}