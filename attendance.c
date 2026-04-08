#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int attendance; // 1 = Present, 0 = Absent
};

/* Function to check duplicate roll number */
int isRollExist(int roll) {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL)
        return 0;

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* Add Student */
void addStudent() {
    FILE *fp;
    struct Student s;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    if (isRollExist(s.roll)) {
        printf("Error: Roll Number Already Exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    s.attendance = 0;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("File open error!\n");
        return;
    }

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

/* View All Students */
void viewStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nRoll\tName\n");
    printf("------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\n", s.roll, s.name);
    }

    fclose(fp);
}

/* Mark Attendance */
void markAttendance() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Mark Attendance \n1 = Present: \n0 = Absent: ");
            scanf("%d", &s.attendance);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("Attendance Marked Successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

/* View Attendance */
void viewAttendance() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No attendance records found!\n");
        return;
    }

    printf("\nRoll\tName\tAttendance\n");
    printf("---------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%s\n", s.roll, s.name,
               s.attendance ? "Present" : "Absent");
    }

    fclose(fp);
}

/* Main Function */
int main() {
    int choice;

    do {
        printf("\n=== Student Attendance Management System ===\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Mark Attendance\n");
        printf("4. View Attendance\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: markAttendance(); break;
            case 4: viewAttendance(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    } while (1);

    return 0;
}
