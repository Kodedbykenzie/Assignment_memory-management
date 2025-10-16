#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STUDENTS 10
#define RETAINED_STUDENTS 6
#define EMAIL_LENGTH 50 // 49 characters + 1 for '\0'

// Function prototypes
char **allocate_memory(int size);
void read_emails(char **emails, int size);
void display_emails(char **emails, int size);
char **shrink_memory(char **emails, int new_size);
void free_memory(char **emails, int size);

int main() {
    char **student_emails = NULL;

    // Step 1: Allocate memory for 10 students
    student_emails = allocate_memory(INITIAL_STUDENTS);
    if (student_emails == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    printf("=== Enter email addresses of %d students ===\n", INITIAL_STUDENTS);
    read_emails(student_emails, INITIAL_STUDENTS);

    printf("\n=== List of all %d students ===\n", INITIAL_STUDENTS);
    display_emails(student_emails, INITIAL_STUDENTS);

    // Step 2: Shrink to 6 students using realloc
    printf("\nSchool retained only %d students. Shrinking memory...\n", RETAINED_STUDENTS);
    student_emails = shrink_memory(student_emails, RETAINED_STUDENTS);
    if (student_emails == NULL) {
        fprintf(stderr, "Memory reallocation failed!\n");
        return 1;
    }

    printf("\n=== Updated list of %d students ===\n", RETAINED_STUDENTS);
    display_emails(student_emails, RETAINED_STUDENTS);

    // Step 3: Free memory
    free_memory(student_emails, RETAINED_STUDENTS);

    printf("\nMemory successfully freed. Program completed.\n");
    return 0;
}

char **allocate_memory(int size) {
    char **emails = (char **)malloc(size * sizeof(char *));
    if (emails == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        emails[i] = (char *)malloc(EMAIL_LENGTH * sizeof(char));
        if (emails[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(emails[j]);
            }
            free(emails);
            return NULL;
        }
    }

    return emails;
}

void read_emails(char **emails, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter email for student %d: ", i + 1);
        fgets(emails[i], EMAIL_LENGTH, stdin);
        emails[i][strcspn(emails[i], "\n")] = '\0'; // remove newline
    }
}

void display_emails(char **emails, int size) {
    for (int i = 0; i < size; i++) {
        printf("Student %d: %s\n", i + 1, emails[i]);
    }
}

char **shrink_memory(char **emails, int new_size) {
    // Free memory of removed students BEFORE shrinking
    for (int i = new_size; i < INITIAL_STUDENTS; i++) {
        free(emails[i]);
    }

    // Now shrink the main array of pointers
    char **temp = (char **)realloc(emails, new_size * sizeof(char *));
    if (temp == NULL) {
        return NULL;
    }

    return temp;
}

void free_memory(char **emails, int size) {
    for (int i = 0; i < size; i++) {
        free(emails[i]);
    }
    free(emails);
}