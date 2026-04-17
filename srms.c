#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    char name[50];
    int roll;
    int subjectCount;
    char subjects[10][30];
    char grades[10][5];
};

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "a"); // create if not exists
    struct Student s;

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    printf("Enter Number of Subjects: ");
    scanf("%d", &s.subjectCount);

    for (int i = 0; i < s.subjectCount; i++) {
        printf("Enter Subject %d: ", i + 1);
        scanf(" %[^\n]", s.subjects[i]);

        printf("Enter Grade for %s: ", s.subjects[i]);
        scanf("%s", s.grades[i]);
    }

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}

void displayAll() {
    FILE *fp = fopen(FILE_NAME, "r");
    struct Student s;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nName: %s\nRoll No: %d\n", s.name, s.roll);
        printf("Subjects & Grades:\n");

        for (int i = 0; i < s.subjectCount; i++) {
            printf("%s - %s\n", s.subjects[i], s.grades[i]);
        }
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll No to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Name: %s\n", s.name);
            printf("Subjects & Grades:\n");

            for (int i = 0; i < s.subjectCount; i++) {
                printf("%s - %s\n", s.subjects[i], s.grades[i]);
            }
            found = 1;
            break;
        }
    }

    if (!found) printf("Record not found.\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "r+");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll No to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new Subject Count: ");
            scanf("%d", &s.subjectCount);

            for (int i = 0; i < s.subjectCount; i++) {
                printf("Enter Subject %d: ", i + 1);
                scanf(" %[^\n]", s.subjects[i]);

                printf("Enter Grade: ");
                scanf("%s", s.grades[i]);
            }

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Record not found.\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}