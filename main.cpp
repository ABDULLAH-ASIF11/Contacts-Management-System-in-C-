#include "ContactsBook.h"
#include<windows.h>

int main()
{
    int choice;
    ContactsBook contactsBook;
    void addContactToGroupMenu(ContactsBook & contactsBook);

    int displayMenuAndGetChoice();
    
    Contact getContactDetailsFromInput(ContactsBook & contactsBook);

    void addingContactcases(ContactsBook & contactsBook);

    addingContactcases(contactsBook);

    return 0;
    system("pause");
}