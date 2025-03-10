#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ROW 5
#define COLUMN 6
#define STATCOLUMN 3

void output(int record[][COLUMN], int statistics[][STATCOLUMN]);
void lowScore(int record[][COLUMN], int statistics[][STATCOLUMN]);
void highScore(int record[][COLUMN], int statistics[][STATCOLUMN]);
void averageScore(int record[][COLUMN], int statistics[][STATCOLUMN]);

int main() {
    int record[ROW][COLUMN];
    int statistics[ROW][STATCOLUMN];

    for (int i = 0; i < ROW; i++) {
        int studentID;
        do {
            printf("Student ID: ");
            scanf("%d", &studentID);
            if (studentID < 1000 || studentID > 9999) {
                printf("Out of range! (Please select ID between 1000-9999)\n");
                getch();
                system("cls");
            }
        } while (studentID < 1000 || studentID > 9999);
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
    lowScore(record, statistics);
    highScore(record, statistics);
    averageScore(record, statistics);
    output(record, statistics);
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

        for (int j = 2; i < (COLUMN - 1); j++) {  // Start from the second element
            if (record[i][j] < smallest) {
                smallest = record[i][j];  // Update largest if a larger element is found
            }
        }
        statistics[i][1] = smallest;
    }
}

void highScore(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    for (int i = 0; i < ROW; i++) {
        int largest = record[i][1];

        for (int j = 2; i < (COLUMN - 1); j++) {  // Start from the second element
            if (record[i][j] > largest) {
                largest = record[i][j];  // Update largest if a larger element is found
            }
        }
        statistics[i][0] = largest;
    }
}

void averageScore(int record[][COLUMN], int statistics[][STATCOLUMN]) {
    for (int i = 0; i < ROW; i++){
        int sum = 0;
        for (int j = 1; j < COLUMN; j++) {
            sum = record[i][j];;
            sum += record[i][j + 1];
        }
        statistics[i][2] = sum / (COLUMN - 1);
    }
}
