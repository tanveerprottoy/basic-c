#include "student.h"
#include <stdio.h>

struct Student {
    char name[50];
    int roll;
    float marks;
};

// pass by value
void display(struct Student s) {
    printf("\nDisplaying information\n");
    printf("Name: %s", s.name);
    printf("\Roll: %d", s.roll);
    printf("\Marks: %f", s.marks);
}

// pass by reference
void detail(struct Student* s) {
    printf("\nDisplaying information\n");
    printf("Name: %s", s->name);
    printf("\Roll: %d", s->roll);
    printf("\Marks: %f", s->marks);
}

struct Student create_student() {
    struct Student s;

    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    return s;
}

void struct_example_simple() {
    struct Student s;

    printf("Enter information:\n");
    printf("Enter name: ");
    scanf("%s", &s.name);
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    printf("Displaying Information:\n");
    printf("Name: %s\n", s.name);
    printf("Roll: %d\n", s.roll);
    printf("Marks: %.2f\n", s.marks);

    // pointer to struct studentPtr
    struct Student *studentPtr, student;
    studentPtr = &student;

    printf("Enter information:\n");
    printf("Enter name: ");
    scanf("%s", &studentPtr->name);
    printf("Enter roll number: ");
    scanf("%d", &studentPtr->roll);
    printf("Enter marks: ");
    scanf("%f", &studentPtr->marks);

    printf("Displaying Information:\n");
    printf("Name: %s\n", studentPtr->name);
    printf("Roll: %d\n", studentPtr->roll);
    printf("Marks: %.2f\n", studentPtr->marks);
}

void struct_example_dynamic_allocation() {
    struct Student* ptr;
    int i, n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    // allocating memory for n numbers of struct person
    ptr = (struct Student*)malloc(sizeof(struct Student) * n);

    for (i = 0; i < n; ++i) {
        printf("Enter name, roll and marks respectively: ");

        scanf("%s %d %d", (ptr + i)->name, &(ptr + i)->roll, &(ptr + i)->marks);
    }

    printf("Displaying Information:\n");
    for (i = 0; i < n; ++i) {
        printf("Name: %s\tRoll: %d\nMarks: %d\n", (ptr + i)->name, &(ptr + i)->roll, &(ptr + i)->marks);
    }

    // deallocating the memory
    free(ptr);

    // set the pointer to NULL
    ptr = NULL;
}