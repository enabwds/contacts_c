# contacts_c

A simple terminal-based contact management system written in C.

## Features

- Add new contacts with name, phone number, and email.
- Display all saved contacts in a formatted list.
- Search for a contact by name using a case-insensitive search.
- Edit existing contacts by updating their phone number or email.
- Delete contacts from the list.
- Save contacts to a file (`contacts.csv`) and load them at startup.

## Getting Started

1. Clone this repository:

   ```bash
   git clone https://github.com/enabwds/contacts_c.git
   cd contacts_c
   ```

2. Build the project:

    ```bash
    clang main.c
    ```

3. Run the executable
    ```bash
    ./a.out
    ```

## Code Structure

- **`Contact` Struct**: Represents a contact with the following fields:
  - `name`: The name of the contact (a `String`).
  - `phone_number`: The contact's phone number (a `String`).
  - `email`: The contact's email address (a `String`).

- **Functions**:
  - `add_contact`: Adds a new contact to the list and saves it to the file.
  - `display_contacts`: Prints all saved contacts in a formatted output.
  - `search_contact`: Searches for a contact by name using case-insensitive binary search.
  - `edit_contact`: Updates an existing contact's phone number or email.
  - `delete_contact`: Removes a contact from the list by name.
  - `load_contacts`: Loads contact data from `contacts.csv` at program start.
  - `save_contacts`: Saves all contacts to `contacts.csv` before exiting.
  - `check_for_duplicates`: Checks if a new contact already exists in the list.
  - `serialize`: Converts a `Contact` into a CSV-compatible string.
  - `deserialize`: Converts a CSV string into a `Contact`.

- **File Storage**:
  - Contacts are stored in a CSV file (`contacts.csv`) where each contact is a line in the format:  
    `name,phone_number,email`
  - The file is read when the application starts and written to whenever changes are made.

- **Main Menu**:
  The `main` function handles user interaction and allows the selection of options like adding, editing, or deleting contacts.

- **Error codes**:
  - 0x01: Null pointer error
  - 0x02: Invalid count
  - 0x03: File not found
  - 0x04: Memory allocation failure
  - 0x05: Unable to open file for reading/writing

## License

This project is licensed under the GPL-2.0 License. 

You are free to use, modify, and distribute this software, provided that the original copyright notice and permission notice are included in all copies or substantial portions of the software.

See the [LICENSE](LICENSE) file for full license details.


