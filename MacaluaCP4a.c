// Franzyl Bjorn L. Macalua
/* Problem is to use 2d arrays to record the test scores of 10 students.
Storing them in one array and then calculating their statistics and showing
the 2d arrays in a table */
// Date Created: 3/10/2025
// Date Finished: 3/11/2025

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ROW 2
#define COLUMN 6
#define STATCOLUMN 3

void dataInput(int record[][COLUMN]);
void output(int record[][COLUMN], int statistics[][STATCOLUMN]);
void lowScore(int record[][COLUMN], int statistics[][STATCOLUMN]);
void highScore(int record[][COLUMN], int statistics[][STATCOLUMN]);
void averageScore(int record[][COLUMN], int statistics[][STATCOLUMN]);

int main() {
    char choice;
    do {
        int record[ROW][COLUMN];
        int statistics[ROW][STATCOLUMN];

        dataInput(record);
        lowScore(record, statistics);
        highScore(record, statistics);
        averageScore(record, statistics);
        output(record, statistics);

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
        int duplicateCheck = 0;
        do {
            printf("%d Student ID: ", i + 1);
            scanf("%d", &studentID);

            for (int search = 0; search < ROW; search++) {
				if (studentID == record[search][0]) {
					duplicateCheck = 1;
					break;
				}
			}
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

        for (int j = 1; j < COLUMN; j++) {
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
        }
    }
}

void output(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "StudentID", "Quiz 1", "Quiz 2", "Quiz 3", "Quiz 4", "Quiz 5", "Highest", "Lowest", "Average");

    for (int i = 0; i < ROW; i++) {
        printf("%-10d", record[i][0]);
        for (int j = 1; j < COLUMN; j++) {
            printf("%-10d", record[i][j]);
        }
        for (int j = 0; j < STATCOLUMN; j++) {
            printf("%-10d", statistics[i][j]);
        }
        printf("\n");
    }
}

void lowScore(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    for (int i = 0; i < ROW; i++) {
        int smallest = record[i][1];

        for (int j = 2; j < (COLUMN - 1); j++) {
            if (record[i][j] < smallest) {
                smallest = record[i][j];
            }
        }
        statistics[i][1] = smallest;
    }
}

void highScore(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    for (int i = 0; i < ROW; i++) {
        int largest = record[i][1];

        for (int j = 2; j < (COLUMN - 1); j++) {
            if (record[i][j] > largest) {
                largest = record[i][j];
            }
        }
        statistics[i][0] = largest;
    }
}

void averageScore(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    for (int i = 0; i < ROW; i++){
        int sum = 0;
        for (int j = 1; j < COLUMN; j++) {
            sum += record[i][j];
        }
        statistics[i][2] = sum / (COLUMN - 1);
    }
}
