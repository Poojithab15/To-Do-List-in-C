#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 100
#define FILENAME "tasks.txt"

// Function prototypes
void addTask(char *task);
void displayTasks();
void deleteTask(int taskNumber);

int main() {
    char task[MAX_TASK_LENGTH];
    int choice, taskNumber;

    while(1) {
        printf("\n\nTo-Do List Application\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin); // Clear input buffer

        switch(choice) {
            case 1:
                printf("Enter task: ");
                scanf("%[^\n]", task);
                addTask(task);
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                printf("Enter task number to delete: ");
                scanf("%d", &taskNumber);
                deleteTask(taskNumber);
                break;
            case 4:
                printf("Exiting...");
                exit(0);
            default:
                printf("Invalid choice! Please try again.");
        }
    }

    return 0;
}

void addTask(char *task) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    fprintf(file, "%s\n", task);
    fclose(file);
    printf("Task added successfully.");
}

void displayTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks found!");
        return;
    }

    char task[MAX_TASK_LENGTH];
    int taskNumber = 1;
    printf("\nTasks:\n");
    while (fgets(task, sizeof(task), file) != NULL) {
        printf("%d. %s", taskNumber++, task);
    }
    fclose(file);
}

void deleteTask(int taskNumber) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks found!");
        return;
    }

    char task[MAX_TASK_LENGTH];
    FILE *tempFile = fopen("temp.txt", "w");
    int currentTask = 1;
    while (fgets(task, sizeof(task), file) != NULL) {
        if (currentTask != taskNumber) {
            fprintf(tempFile, "%s", task);
        }
        currentTask++;
    }
    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
    printf("Task deleted successfully.");
}
