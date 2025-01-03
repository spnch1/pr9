#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/include/io.h"
#include "./src/include/color.h"

#define MAX_RECORDS 100

// Function prototypes
void createFile(const char *filename);
void readFile(const char *filename);
void deleteFile(const char *filename);
void addRecord(const char *filename);
void editRecord(const char *filename);
void deleteRecord(const char *filename);
void sortRecords(const char *filename, int ascending);
void insertSortedRecord(const char *filename);

// Utility functions
void displayMenu();
int loadRecords(const char *filename, Record records[], int *count);
void saveRecords(const char *filename, Record records[], int count);
int compareRecords(const void *a, const void *b, int ascending);

int main() {
    char filename[256];
    int choice;

    printf("Enter the filename to use: ");
    scanf("%s", filename);

    do {
        displayMenu();
        choice = getChoice("Enter your choice: ", 1, 9);

        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                readFile(filename);
                break;
            case 3:
                deleteFile(filename);
                break;
            case 4:
                addRecord(filename);
                break;
            case 5:
                editRecord(filename);
                break;
            case 6:
                deleteRecord(filename);
                break;
            case 7: {
                int ascending;
                printf("Sort ascending (1) or descending (0): ");
                scanf("%d", &ascending);
                sortRecords(filename, ascending);
                break;
            }
            case 8:
                insertSortedRecord(filename);
                break;
            case 9:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

void displayMenu() {
    printf( BLK WHTB "                   MAIN MENU                   \n" CRESET);
    printf("1. Create File          4. Add Record\n");
    printf("2. Read File            5. Read Record\n");
    printf("3. Delete File          6. Edit Record\n");
    printf("                        7. Delete Record\n");
    printf("                        8. Sort Records\n");
    printf("                        9. Insert Sorted Record\n");
    printf("                   0. Exit\n");
}

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    printf("File '%s' created successfully.\n", filename);
    fclose(file);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nRecords in '%s':\n", filename);
    Record record;
    while (fscanf(file, "%[^,],%f,%d\n", record.region_name, &record.area, &record.population) == 3) {
        printf("Region: %s, Area: %.2f, Population: %d\n", record.region_name, record.area, record.population);
    }

    fclose(file);
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

void addRecord(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Record record;
    printf("Enter region name: ");
    scanf("%s", record.region_name);
    printf("Enter area: ");
    scanf("%f", &record.area);
    printf("Enter population: ");
    scanf("%d", &record.population);

    fprintf(file, "%s,%.2f,%d\n", record.region_name, record.area, record.population);
    printf("Record added successfully.\n");

    fclose(file);
}

void editRecord(const char *filename) {
    Record records[MAX_RECORDS];
    int count;
    if (!loadRecords(filename, records, &count)) return;

    int recordIndex;
    printf("Enter record number to edit (1-%d): ", count);
    scanf("%d", &recordIndex);

    if (recordIndex < 1 || recordIndex > count) {
        printf("Invalid record number.\n");
        return;
    }

    Record *record = &records[recordIndex - 1];
    printf("Editing record: %s, %.2f, %d\n", record->region_name, record->area, record->population);
    printf("Enter new region name: ");
    scanf("%s", record->region_name);
    printf("Enter new area: ");
    scanf("%f", &record->area);
    printf("Enter new population: ");
    scanf("%d", &record->population);

    saveRecords(filename, records, count);
    printf("Record updated successfully.\n");
}

void deleteRecord(const char *filename) {
    Record records[MAX_RECORDS];
    int count;
    if (!loadRecords(filename, records, &count)) return;

    int recordIndex;
    printf("Enter record number to delete (1-%d): ", count);
    scanf("%d", &recordIndex);

    if (recordIndex < 1 || recordIndex > count) {
        printf("Invalid record number.\n");
        return;
    }

    for (int i = recordIndex - 1; i < count - 1; i++) {
        records[i] = records[i + 1];
    }
    count--;

    saveRecords(filename, records, count);
    printf("Record deleted successfully.\n");
}

void sortRecords(const char *filename, int ascending) {
    Record records[MAX_RECORDS];
    int count;
    if (!loadRecords(filename, records, &count)) return;

    qsort(records, count, sizeof(Record), ascending ? (int (*)(const void *, const void *))strcmp : (int (*)(const void *, const void *))strcmp);

    saveRecords(filename, records, count);
    printf("Records sorted successfully.\n");
}

void insertSortedRecord(const char *filename) {
    Record records[MAX_RECORDS];
    int count;
    if (!loadRecords(filename, records, &count)) return;

    Record newRecord;
    printf("Enter region name: ");
    scanf("%s", newRecord.region_name);
    printf("Enter area: ");
    scanf("%f", &newRecord.area);
    printf("Enter population: ");
    scanf("%d", &newRecord.population);

    records[count++] = newRecord;
    sortRecords(filename, 1);
    printf("Record inserted and sorted successfully.\n");
}

int loadRecords(const char *filename, Record records[], int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%f,%d\n", records[*count].region_name, &records[*count].area, &records[*count].population) == 3) {
        (*count)++;
    }

    fclose(file);
    return 1;
}

void saveRecords(const char *filename, Record records[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < count
; i++) {
              fprintf(file, "%s,%.2f,%d\n", records[i].region_name, records[i].area, records[i].population);
          }

    fclose(file);
}

int compareRecords(const void *a, const void *b, int ascending) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;

    int result = strcmp(recordA->region_name, recordB->region_name);

    if (ascending) {
        return result;
    } else {
        return -result;
    }
}
