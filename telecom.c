#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "customers.dat"

struct Customer {
    char name[50];
    char phone[15];
    float usage;
    float bill;
};

struct Customer customers[MAX];
int customerCount = 0;

// ---------- FILE HANDLING ----------

void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "wb");
    fwrite(&customerCount, sizeof(int), 1, fp);
    fwrite(customers, sizeof(struct Customer), customerCount, fp);
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp != NULL) {
        fread(&customerCount, sizeof(int), 1, fp);
        fread(customers, sizeof(struct Customer), customerCount, fp);
        fclose(fp);
    }
}

// ---------- CORE FUNCTIONS ----------

int phoneExists(char phone[]) {
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

void addRecord() {
    if (customerCount >= MAX) {
        printf("Storage full!\n");
        return;
    }

    struct Customer c;
    printf("Enter name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone: ");
    scanf("%s", c.phone);

    if (phoneExists(c.phone)) {
        printf("Phone already exists!\n");
        return;
    }

    printf("Enter usage (minutes): ");
    scanf("%f", &c.usage);

    c.bill = c.usage * 0.1;
    customers[customerCount++] = c;
    saveToFile();

    printf("Record added successfully!\n");
}

void viewRecords() {
    printf("\nName\tPhone\tUsage\tBill\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < customerCount; i++) {
        printf("%s\t%s\t%.2f\t%.2f\n",
               customers[i].name,
               customers[i].phone,
               customers[i].usage,
               customers[i].bill);
    }
}

void modifyRecord() {
    char phone[15];
    printf("Enter phone to modify: ");
    scanf("%s", phone);

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            printf("Enter new usage: ");
            scanf("%f", &customers[i].usage);
            customers[i].bill = customers[i].usage * 0.1;
            saveToFile();
            printf("Record modified!\n");
            return;
        }
    }
    printf("Record not found!\n");
}

void deleteRecord() {
    char phone[15];
    printf("Enter phone to delete: ");
    scanf("%s", phone);

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            for (int j = i; j < customerCount - 1; j++) {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            saveToFile();
            printf("Record deleted!\n");
            return;
        }
    }
    printf("Record not found!\n");
}

void viewPayment() {
    char phone[15];
    printf("Enter phone to view payment: ");
    scanf("%s", phone);

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            printf("\nName: %s", customers[i].name);
            printf("\nPhone: %s", customers[i].phone);
            printf("\nUsage: %.2f", customers[i].usage);
            printf("\nBill: %.2f\n", customers[i].bill);
            return;
        }
    }
    printf("Record not found!\n");
}

// ---------- MENU ----------

void displayMenu() {
    printf("\n--- Telecom Billing System ---\n");
    printf("1. Add Record\n");
    printf("2. View Records\n");
    printf("3. Modify Record\n");
    printf("4. Delete Record\n");
    printf("5. View Payment\n");
    printf("6. Exit\n");
}

int main() {
    int choice;
    loadFromFile();

    while (1) {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            modifyRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            viewPayment();
            break;
        case 6:
            saveToFile();
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
