# Contact Management System

This is a simple contact management system written in C. It allows users to manage a list of contacts by adding, editing, searching, deleting, displaying, and saving contact details. The contacts are stored in a CSV file to ensure persistence between program executions.

## Features

- **Add Contact**: Add a new contact with a name, phone number, and email address.
- **Display Contacts**: View all stored contacts in a sorted list.
- **Search Contact**: Search for a contact by name using binary search.
- **Edit Contact**: Modify the phone number or email of an existing contact.
- **Delete Contact**: Remove a contact from the list by name.
- **Save and Load Contacts**: Save contacts to a CSV file and load them when the program starts.
- **Duplicate Detection**: Prevent duplicate contacts from being added.
- **Whitespace Trimming**: Automatically trim leading and trailing whitespace for inputs.
- **Input Validation**: Checks for valid emails.

## Features to be added
- [x] Input validation
- [x] Groups (Work, family, friends, etc)
- [x] Confirmation prompts for destructive actions
- [ ] Sorting by fields
- [ ] Filter by group
- [ ] Import/export files as other formats (JSON, vCard, etc)
- [ ] Undo/Redo
- [ ] Encryption
- [ ] GUI
- [ ] Audit log
- [ ] Multi-field search
- [ ] Unicode support

## File Structure

- **Source Code**: The main program is contained in a single C file.
- **Error Codes**: Uses an external `error_codes.h` file to handle error codes.
- **Data File**: Contacts are stored in a `contacts.csv` file in CSV format.

## Compilation and Execution

### Prerequisites
- GCC or any C compiler
- Git

### Clone, Compile, and execute the Program
```bash
git clone https://github.com/enabwds/contacts_c
cd contacts_c
gcc -o contact_manager main.c
./contact_manager
```

## Usage
1. Upon running the program, you will be presented with a menu:
```
Contact Management System
1. Add Contact
2. Display Contacts
3. Search Contact
4. Edit Contact
5. Delete Contact
6. Exit
```

2. Enter the corresponding number to perform an action:
- Add a contact by providing the name, phone number, and email.
- Display all contacts sorted by name.
- Search for a contact by name.
- Edit an existing contact by entering its name and updating details.
- Delete a contact by providing its name.
- Exit the program to save all changes to `contacts.csv`.

## Data Persistence
- The program will automatically load contacts from `contacts.csv` when started
- All changes are saved when exiting the program

## Error Handling
- Memory Allocation: Detects and handles memory allocation issues.
- File Operations: Handles errors when loading or saving files (e.g., file not found, write errors).
- Null Pointers: Handles potential null pointer dereferences.
- Duplicate Contacts: Prevents duplicate entries based on name, phone number, and email.

## Limitations
- The program assumes the `contacts.csv` file exists in the same directory. If the file is missing, it will create one upon saving.
- Case-insensitive comparison is used for names, but sorting and searching assume ASCII characters.

## Contributing
- Contributions, bug reports, and feature requests are welcome. Please submit them via the GitHub repository

## License
This project is licensed under the GNU General Public License v2.0 (GPL-2.0). See the [LICENSE](LICENSE) file for full details.

By contributing to this project, you agree that your contributions will be licensed under the GPL-2.0 as well.
