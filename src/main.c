#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "error_codes.h"

#define MAX_STRING 128

// Structure to represent a contact
typedef struct {
    char name[MAX_STRING];
    char phoneNumber[MAX_STRING];
    char email[MAX_STRING];
    char group[MAX_STRING];
} Contact;

// Function to serialize a contact into a string
void serialize(const Contact *contact, char *output) {
    sprintf(output, "%s,%s,%s,%s", contact->name, contact->phoneNumber, contact->email, contact->group);
}

// Function to deserialize a contact from a string
Contact deserialize(const char *data) {
    Contact contact;
    char buffer[MAX_STRING];
    strcpy(buffer, data);
    char *token = strtok(buffer, ",");
    strcpy(contact.name, token);
    token = strtok(NULL, ",");
    strcpy(contact.phoneNumber, token);
    token = strtok(NULL, ",");
    strcpy(contact.email, token);
    token = strtok(NULL, ",");
    strcpy(contact.group, token);

    return contact;
}

void trimWhitespace(char *str) {
    // Trim leading spaces
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // If the string is empty after trimming, return
    if (*str == 0) {
        return;
    }

    // Trim trailing spaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Null-terminate the string after the last non-space character
    *(end + 1) = 0;
}

// Helper function for case-insensitive string comparison
int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2 && tolower((unsigned char)*s1) == tolower((unsigned char)*s2)) {
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

bool isValidEmail(const char *email) {
    if (email == NULL || strlen(email) < 3) {  // Minimum length: a@b
        return 0;
    }

    char *at = strchr(email, '@');  // Find '@' character
    if (!at || at == email || *(at + 1) == '\0') {  
        return 0;  // '@' must not be at the start or end
    }

    char *dot = strrchr(at, '.');  // Find last '.'
    if (!dot || dot <= at + 1 || *(dot + 1) == '\0') {  
        return 0;  // '.' must be after '@' and not at the end
    }

    return 1;  // Valid email format
}

// Function to perform binary search on the contacts array
int binarySearch(const Contact *contacts, int contactCount, const char *name) {
    int left = 0;
    int right = contactCount - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparison = strcasecmp_custom(contacts[mid].name, name);

        if (comparison == 0) {
            return mid; // Contact found at index mid
        } else if (comparison < 0) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Contact not found
}

// Function to search for a contact by name using binary search
void searchContact(const Contact *contacts, int contactCount, const char *name) {
    char trimmedName[MAX_STRING];
    strncpy(trimmedName, name, MAX_STRING - 1);
    trimmedName[MAX_STRING - 1] = '\0';
    trimWhitespace(trimmedName);

    int index = binarySearch(contacts, contactCount, trimmedName);
    if (index != -1) {
        printf("Contact found:\n");
        printf("Name: %s\n", contacts[index].name);
        printf("Phone Number: %s\n", contacts[index].phoneNumber);
        printf("Email: %s\n", contacts[index].email);
        printf("Group: %s\n", contacts[index].group);
    } else {
        printf("Contact not found.\n");
    }
}

// Function to check for duplicates
bool checkForDuplicates(const Contact *contacts, int contactCount, const Contact *newContact) {
    for (int i = 0; i < contactCount; ++i) {
        if (strcasecmp_custom(contacts[i].name, newContact->name) == 0 &&
            strcasecmp_custom(contacts[i].phoneNumber, newContact->phoneNumber) == 0 &&
            strcasecmp_custom(contacts[i].email, newContact->email) == 0) {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicates
}

// Function to trim leading and trailing spaces


void addContact(Contact **contacts, int *contactCount, int *capacity) {
    if (*contactCount >= *capacity) {
        *capacity *= 2;
        *contacts = realloc(*contacts, *capacity * sizeof(Contact));
  } 

  if (*contacts == NULL) {
    printf("Error: 0x%02X (Memory allocation failed)\n", ERROR_MEMORY_ALLOCATION);
    exit(ERROR_MEMORY_ALLOCATION);
}

    Contact newContact;

    printf("Enter name: ");
    fgets(newContact.name, MAX_STRING, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = 0;  // Remove trailing newline  
    trimWhitespace(newContact.name); // Remove remaining whitespaces

    printf("Enter phone number: ");
    fgets(newContact.phoneNumber, MAX_STRING, stdin);
    newContact.phoneNumber[strcspn(newContact.phoneNumber, "\n")] = 0;
    trimWhitespace(newContact.phoneNumber);

    printf("Enter email: ");
    fgets(newContact.email, MAX_STRING, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = 0;
    trimWhitespace(newContact.email);

    printf("Enter group: ");
    fgets(newContact.group, MAX_STRING, stdin);
    newContact.group[strcspn(newContact.group, "\n")] = 0;
    trimWhitespace(newContact.group);


  if (!isValidEmail(newContact.email)) {
    printf("Error: invalid email!\n");
    return;
  }
    if (checkForDuplicates(*contacts, *contactCount, &newContact)) {
        printf("The contact already exists!\n");
        return;
    }

    (*contacts)[*contactCount] = newContact;
    (*contactCount)++;
    printf("Contact added.\n");

}

// Comparison function for qsort
int compareContacts(const void *a, const void *b) {
    const Contact *contactA = (const Contact *)a;
    const Contact *contactB = (const Contact *)b;
    return strcasecmp_custom(contactA->name, contactB->name);
}

void sortContacts(Contact *contacts, int contactCount) {
    
  if (contacts == NULL) {
    printf("0x%02X\n", ERROR_NULL_POINTER);
    return;
  }

  if (contactCount < 0) {
    printf("0x%02X\n", ERROR_INVALID_COUNT);
    return;
  }


    qsort(contacts, contactCount, sizeof(Contact), compareContacts);
}

// Function to display all contacts
void displayContacts(const Contact *contacts, int contactCount) {
    if (contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("Contacts List:\n");
    for (int i = 0; i < contactCount; ++i) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone Number: %s\n", contacts[i].phoneNumber);
        printf("Email: %s\n", contacts[i].email);
        printf("Group: %s\n", contacts[i].group);
        printf("-------------------\n");
    }
}

// Function to find a contact by name using binary search and return its index
int findContactIndex(const Contact *contacts, int contactCount, const char *name) {
    int left = 0;
    int right = contactCount - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparison = strcasecmp_custom(contacts[mid].name, name);

        if (comparison == 0) {
            return mid; // Contact found at index mid
        } else if (comparison < 0) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Contact not found
}

// Function to edit a contact by name
void editContact(Contact *contacts, int contactCount) {
    char name[MAX_STRING];
    printf("Enter the name of the contact to edit: ");
    fgets(name, MAX_STRING, stdin);
    name[strcspn(name, "\n")] = 0;
    trimWhitespace(name);

    int index = findContactIndex(contacts, contactCount, name);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    Contact *contact = &contacts[index];
    printf("Editing contact: %s\n", contact->name);

    printf("Enter new phone number (leave blank to keep current): ");
    char newPhoneNumber[MAX_STRING];
    fgets(newPhoneNumber, MAX_STRING, stdin);
    newPhoneNumber[strcspn(newPhoneNumber, "\n")] = 0;
    trimWhitespace(newPhoneNumber);
    if (strlen(newPhoneNumber) > 0) {
        strcpy(contact->phoneNumber, newPhoneNumber);
    }

    printf("Enter new email (leave blank to keep current): ");
    char newEmail[MAX_STRING];
    fgets(newEmail, MAX_STRING, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;
    trimWhitespace(newEmail);
    
    if (strlen(newEmail) > 0) {  // Only validate if user enters a new email
    if (!isValidEmail(newEmail)) {
        printf("Error: Invalid email format!\n");
        return;
    }
    strcpy(contact->email, newEmail);
}

    printf("Enter new group (leave blank to keep current): ");
    char newGroup[MAX_STRING];
    fgets(newGroup, MAX_STRING, stdin);
    newGroup[strcspn(newGroup, "\n")] = 0;
    trimWhitespace(newGroup);
    if (strlen(newGroup) > 0) {
        strcpy(contact->group, newGroup);

    }
    printf("Contact updated.\n");
}

// Function to delete a contact by name
void deleteContact(Contact **contacts, int *contactCount, const char *name) {
    int index = findContactIndex(*contacts, *contactCount, name);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    for (int i = index; i < *contactCount - 1; ++i) {
        (*contacts)[i] = (*contacts)[i + 1];
    }
    char confirmation;
    printf("Are you sure you want to delete this contact?[Y/N]: ");
    scanf("%c", &confirmation);
    if (confirmation == 'N' || confirmation == 'n') {
    return;
   }
    if (confirmation == 'Y' || confirmation == 'y') {
    (*contactCount)--;
    printf("Contact deleted.\n");
}
}
// Function to load contacts from a file
void loadContacts(Contact **contacts, int *contactCount, int *capacity, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: 0x%02X (File not found)\n", ERROR_FILE_NOT_FOUND);
        return;
    }

    char line[MAX_STRING];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // Remove trailing newline
        if (*contactCount >= *capacity) {
            *capacity *= 2;
            *contacts = realloc(*contacts, *capacity * sizeof(Contact));

    if (*contacts == NULL) {
       printf("Error: 0x%02X (Memory allocation failed)\n", ERROR_MEMORY_ALLOCATION);
       exit(ERROR_MEMORY_ALLOCATION);
}

        }
        (*contacts)[*contactCount] = deserialize(line);
        (*contactCount)++;
    }
    fclose(file);

    // Sort contacts after loading
    sortContacts(*contacts, *contactCount);
}

// Function to save contacts to a file
void saveContacts(const Contact *contacts, int contactCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: 0x%02X (Error opening file for writing)\n", ERROR_OPENING_FILE);
        return;
    }

    char serializedContact[MAX_STRING];
    for (int i = 0; i < contactCount; ++i) {
        serialize(&contacts[i], serializedContact);
        fprintf(file, "%s\n", serializedContact);
    }
    fclose(file);
}

int main() {
    Contact *contacts = malloc(10 * sizeof(Contact));  // Initial capacity of 10
    int contactCount = 0;
    int capacity = 10;
    const char *filename = "contacts.csv";

    loadContacts(&contacts, &contactCount, &capacity, filename);

    int choice;
    do {
        printf("Contact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character after the number input

        switch (choice) {
            case 1:
                addContact(&contacts, &contactCount, &capacity);
                break;
            case 2:
                printf("---------\n");
                displayContacts(contacts, contactCount);
                break;
            case 3: {
                char name[MAX_STRING];
                printf("Enter the name to search: ");
                fgets(name, MAX_STRING, stdin);
                name[strcspn(name, "\n")] = 0;
                searchContact(contacts, contactCount, name);
                break;
            }
            case 4:
                editContact(contacts, contactCount);
                break;
            case 5: {
                char name[MAX_STRING];
                printf("Enter the name of the contact to delete: ");
                fgets(name, MAX_STRING, stdin);
                name[strcspn(name, "\n")] = 0;
                deleteContact(&contacts, &contactCount, name);
                break;
            }
            case 6:
                saveContacts(contacts, contactCount, filename);
                printf("Exiting and saving contacts...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 6);

    free(contacts);  // Free allocated memory before exiting
    return 0;
}
