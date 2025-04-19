#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_NAME 50

// Simple student record
typedef struct {
    char name[MAX_NAME];
    int roll_no;
    float marks;
} Student;

// All functions we will use
void add_student(Student students[], int *total_students);
void show_all_students(Student students[], int total_students);
void sort_students_by_marks(Student students[], int total_students);
void find_student(Student students[], int total_students);
float get_class_average(Student students[], int total_students);
void find_highest_lowest_marks(Student students[], int total_students);

int main() {
    Student students[MAX_STUDENTS];
    int total_students = 0;
    int choice;
    
    printf("Welcome to Student Record System\n");
    
    do {
        // Show menu
        printf("\nWhat would you like to do?\n");
        printf("1. Add new student\n");
        printf("2. Show all students\n");
        printf("3. Sort students by marks\n");
        printf("4. Find a student\n");
        printf("5. Show class average\n");
        printf("6. Show highest and lowest marks\n");
        printf("7. Exit program\n");
        printf("\nType a number (1-7): ");
        scanf("%d", &choice);
        getchar(); // Clear the enter key from input
        
        switch(choice) {
            case 1:
                if (total_students < MAX_STUDENTS) {
                    add_student(students, &total_students);
                } else {
                    printf("\nSorry, class is full! Maximum %d students allowed.\n", MAX_STUDENTS);
                }
                break;
                
            case 2:
                show_all_students(students, total_students);
                break;
                
            case 3:
                sort_students_by_marks(students, total_students);
                printf("\nStudents sorted by marks (highest to lowest).\n");
                show_all_students(students, total_students);
                break;
                
            case 4:
                find_student(students, total_students);
                break;
                
            case 5: {
                float average = get_class_average(students, total_students);
                printf("\nClas s average marks: %.2f\n", average);
                break;
            }
                
            case 6:
                find_highest_lowest_marks(students, total_students);
                break;
                
            case 7:
                printf("\nThank you for using Student Record System. Goodbye!\n");
                break;
                
            default:
                printf("\nPlease type a number between 1 and 7.\n");
        }
    } while (choice != 7);
    
    return 0;
}

void add_student(Student students[], int *total_students) {
    printf("\n--- Add New Student ---\n");
    
    printf("Enter student name: ");
    fgets(students[*total_students].name, MAX_NAME, stdin);
    students[*total_students].name[strcspn(students[*total_students].name, "\n")] = 0;
    
    printf("Enter roll number: ");
    scanf("%d", &students[*total_students].roll_no);
    
    printf("Enter marks (0-100): ");
    scanf("%f", &students[*total_students].marks);
    
    if (students[*total_students].marks >= 0 && students[*total_students].marks <= 100) {
        (*total_students)++;
        printf("\nStudent added successfully!\n");
    } else {
        printf("\nError: Marks should be between 0 and 100.\n");
    }
    getchar();
}

void show_all_students(Student students[], int total_students) {
    if (total_students == 0) {
        printf("\nNo students in the system yet.\n");
        return;
    }
    
    printf("\n--- All Students ---\n");
    printf("Name                  Roll No    Marks\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < total_students; i++) {
        printf("%-20s %-10d %.2f\n", 
               students[i].name, 
               students[i].roll_no, 
               students[i].marks);
    }
}

void sort_students_by_marks(Student students[], int total_students) {
    if (total_students <= 1) return;
    
    // Simple bubble sort
    for (int i = 0; i < total_students - 1; i++) {
        for (int j = 0; j < total_students - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                // Swap students
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void find_student(Student students[], int total_students) {
    if (total_students == 0) {
        printf("\nNo students in the system yet.\n");
        return;
    }
    
    int roll_no;
    printf("\nEnter roll number to find student: ");
    scanf("%d", &roll_no);
    
    for (int i = 0; i < total_students; i++) {
        if (students[i].roll_no == roll_no) {
            printf("\nStudent found!\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll number: %d\n", students[i].roll_no);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }
    
    printf("\nNo student found with roll number %d.\n", roll_no);
}

float get_class_average(Student students[], int total_students) {
    if (total_students == 0) {
        printf("\nNo students in the system yet.\n");
        return 0;
    }
    
    float total = 0;
    for (int i = 0; i < total_students; i++) {
        total += students[i].marks;
    }
    
    return total / total_students;
}

void find_highest_lowest_marks(Student students[], int total_students) {
    if (total_students == 0) {
        printf("\nNo students in the system yet.\n");
        return;
    }
    
    float highest = students[0].marks;
    float lowest = students[0].marks;
    int highest_index = 0;
    int lowest_index = 0;
    
    for (int i = 1; i < total_students; i++) {
        if (students[i].marks > highest) {
            highest = students[i].marks;
            highest_index = i;
        }
        if (students[i].marks < lowest) {
            lowest = students[i].marks;
            lowest_index = i;
        }
    }
    
    printf("\n--- Highest and Lowest Marks ---\n");
    printf("Highest marks: %.2f (Student: %s)\n", highest, students[highest_index].name);
    printf("Lowest marks: %.2f (Student: %s)\n", lowest, students[lowest_index].name);
} 