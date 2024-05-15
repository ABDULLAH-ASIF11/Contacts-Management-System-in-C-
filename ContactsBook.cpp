#include "ContactsBook.h"



//static member
const int SearchHistory::MAX_ENTRIES;


int ContactsBook::indexCounter = 0;

//Index for Contacts
int ContactsBook::generateIndex()
{
    return ++indexCounter;
}


//Adding Contact
bool ContactsBook::addContact(const Contact& contact)
{
    if (numContacts < MAX_CONTACTS)
    {
        contacts[numContacts++] = contact;
        return true;
    }
    else
    {
        cerr << "Error: Contacts list full.\n";
        return false;
    }
}

// display menu and get user choice
int displayMenuAndGetChoice()
{
    int choice;
    cout << "\n\nMenu:\n"
        << "--------------------------------|\n"
        "1.  Add New Contact             |\n"
        "2.  Merge Duplicates            |\n"
        "3.  Store To File               |\n"
        "4.  Load From File              |\n"
        "5.  Print Contacts Sorted       |\n"
        "6.  Search Contacts             |\n"
        "7.  Display Count of Contacts   |\n"
        "8.  View Details of a Contact   |\n"
        "9.  Update Details of a Contact |\n"
        "10. Delete a Contact            |\n"
        "11. Create a Group              |\n"
        "12. Add Contact to Group        |\n"
        "13. Store Group info To File    |\n"
        "14. Remove contact from a Group |\n"
        "15. Contact to view its groups  |\n"
        "16. Delete a Group              |\n"
        "17. View Search History         |\n"
        "0. Exit                         |\n"
        << "--------------------------------|\n\n"
        "Enter your choice: ";
    cin >> choice;
    cout << endl << endl;
    return choice;
}




// get contact details from user input
Contact getContactDetailsFromInput(ContactsBook& contactsBook)
{
    string firstName, lastName, phone, email, street, country, house, city;
    cout << "------------------------\n";
    cout << "|Enter Contact Details:| \n";
    cout << "-----------------------|\n";
    cout << "Enter first name:      |\n";
    cin >> firstName;
    cout << "Enter last name:       |\n";
    cin >> lastName;
    cout << "Enter phone number:    |\n";
    cin >> phone;
    cout << "Enter email:           |\n";
    cin >> email;
    cout << "Enter country:         |\n";
    cin >> country;
    cout << "Enter city:            |\n";
    cin >> city;
    cout << "Enter street:          |\n";
    cin >> street;
    cout << "Enter house:           |\n";
    cin >> house;
    cout << "-----------------------|\n";
    Address address(street, country, house, city);
    int index = contactsBook.generateIndex(); //index for new contact
    return Contact(firstName, lastName, phone, email, address, index);
}


//Merge Duplicate Contacts
void ContactsBook::mergeDuplicates()
{
    for (int i = 0; i < numContacts; ++i)
    {
        for (int j = i + 1; j < numContacts;)
        {
            if (contacts[i].getPhone() == contacts[j].getPhone())
            {
                // Shift elements to left to remove duplicate
                for (int k = j; k < numContacts - 1; ++k)
                {
                    contacts[k] = contacts[k + 1];
                }
                --numContacts; // Reduce count of contacts
            }
            else
            {
                ++j;
            }
        }
    }
}



//Store contacts to a File.
void ContactsBook::storeToFile(const string& fileName) const
{
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (int i = 0; i < numContacts; ++i)
        {
            outFile << "First name: " << contacts[i].getFirstName() << "\n"
                << "Last name: " << contacts[i].getLastName() << "\n"
                << "Phone no: " << contacts[i].getPhone() << "\n"
                << "Email: " << contacts[i].getEmail() << "\n"
                << "Complete Adress is: \n"
                << "House no " << contacts[i].getAddress().getHouse()
                << ", street no " << contacts[i].getAddress().getStreet()
                << ", city " << contacts[i].getAddress().getCity()
                << ", country " << contacts[i].getAddress().getCountry() << endl;
        }
        outFile.close();
    }
    else
    {
        cerr << "Error: Unable to open file for writing.\n";
    }
}



//Load contact from a file
void ContactsBook::ContactsBook::loadFromFile(const string& fileName)
{ 

    ifstream inFile(fileName); 
    if (inFile.is_open())
    {
        numContacts = 0; 

        string line;
        while (getline(inFile, line)) // Read each line from the file
        {
            string token;
            string firstName, lastName, phone, email, country, city, street, house;

            // Extract each token separated by comma
            getline(inFile, firstName, ',');
            getline(inFile, lastName, ',');
            getline(inFile, phone, ',');
            getline(inFile, email, ',');
            getline(inFile, country, ',');
            getline(inFile, city, ',');
            getline(inFile, street, ',');
            getline(inFile, house, ',');

            Address address(street, country, house, city);
            int index = generateIndex(); // Generate index for the loaded contact
            contacts[numContacts++] = Contact(firstName, lastName, phone, email, address, index);
        }
        inFile.close(); 
    }
    else
    {
        cerr << "Error: Unable to open file for reading.\n"; // Error message if file cannot be opened
    }
}




// Manual sorting function definition
void manualSort(Contact* contacts, int numContacts, const string& sortBy) 
{
    for (int i = 0; i < numContacts - 1; ++i) 
    {
        for (int j = 0; j < numContacts - i - 1; ++j) 
        {
            if ((sortBy == "first_name" && contacts[j].getFirstName() > contacts[j + 1].getFirstName()) ||
                (sortBy == "last_name" && contacts[j].getLastName() > contacts[j + 1].getLastName())) 
            {
                // Swap contacts[j] and contacts[j+1]
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}


// Function to print sorted contacts
void ContactsBook::printContactsSorted(const string& sortBy) const
{
    // Copy contacts to a temp array
    Contact sortedContacts[MAX_CONTACTS];
    for (int i = 0; i < numContacts; ++i) 
    {
        sortedContacts[i] = contacts[i];
    }

    
    manualSort(sortedContacts, numContacts, sortBy);

    // Print sorted contacts
    for (int i = 0; i < numContacts; ++i) 
    {
        cout << "First Name: " << sortedContacts[i].getFirstName() << "\n"
            << "Last Name: " << sortedContacts[i].getLastName() << "\n"
            << "Phone: " << sortedContacts[i].getPhone() << "\n"
            << "Email: " << sortedContacts[i].getEmail() << "\n"
            << "Address: " << sortedContacts[i].getAddress().getStreet() << ", "
            << sortedContacts[i].getAddress().getCountry() << ", "
            << sortedContacts[i].getAddress().getCity() << ", "
            << sortedContacts[i].getAddress().getHouse() << "\n\n";
    }
}



//Search a contact
Contact* ContactsBook::searchContacts(const string& searchTerm, int& numMatches) const 
{
    Contact* matches = new Contact[numContacts];
    numMatches = 0;

    for (int i = 0; i < numContacts; ++i)
    {
        const Contact& c = contacts[i];
        if (c.getFirstName() == searchTerm || c.getLastName() == searchTerm ||
            c.getPhone() == searchTerm || c.getEmail() == searchTerm ||
            c.getAddress().getStreet() == searchTerm || c.getAddress().getCity() == searchTerm ||
            c.getAddress().getCountry() == searchTerm || c.getAddress().getHouse() == searchTerm)
        {
            matches[numMatches++] = c;
            
            cout << "Index: " << i + 1 << " ";
            searchHistory.addSearchQuery(searchTerm); // Update search history here
        }
    }

    return matches;
}


//Count number of contacts
int ContactsBook::getCountOfContacts() const
{
    return numContacts;
}


//Get index for contact
Contact* ContactsBook::getContactByIndex(int index)
{
    if (index >= 0 && index < numContacts)
    {
        // Increment the view count when the contact's details are viewed
        contacts[index].incrementViewCount();
        searchHistory.addSearchQuery("View Contact Details"); // Update search history
        return &contacts[index];
    }
    return nullptr;
}


//Update contact detail
void ContactsBook::updateContactDetails(int index, const string& firstName, const string& lastName, const string& phone, const string& email, const Address& address)
{
    if (index >= 0 && index < numContacts)
    {
        contacts[index].updateContact(firstName, lastName, phone, email, address);
    }
}


// Function to update details of a contact
void updateContact(ContactsBook& contactsBook)
{
    int index;
    cout << "Enter the index of the contact you want to update (starting from 1): ";
    cin >> index;
    // Adjust index to zero-based
    index -= 1;
    Contact* contact = contactsBook.getContactByIndex(index);
    if (contact)
    {
        // Get updated contact details
        string firstName, lastName, phone, email, street, country, house, city;
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Enter phone number: ";
        cin >> phone;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter country: ";
        cin >> country;
        cout << "Enter city: ";
        cin >> city;
        cout << "Enter street: ";
        cin >> street;
        cout << "Enter house: ";
        cin >> house;
        Address address(street, country, house, city);
        // Update contact details
        contactsBook.updateContactDetails(index, firstName, lastName, phone, email, address);
        cout << "Contact details updated successfully.\n";
    }
    else
    {
        cout << "Invalid index.\n";
    }
}




//Delete a contact
void ContactsBook::deleteContact(int index)
{
    if (index >= 0 && index < numContacts)
    {
        for (int i = index; i < numContacts - 1; ++i)
        {
            contacts[i] = contacts[i + 1];
        }
        numContacts--;
    }
}


//Creating a Group
bool ContactsBook::createGroup(const string& groupName)
{
    if (numGroups < 10)
    {
        groups[numGroups++] = Group(groupName);
        cout << "Group '" << groupName << "' created successfully with index: " << numGroups << " |" << endl;
        cout << "-----------------------------------------------|\n";
        return true;
    }
    else
    {
        cerr << "Error: Maximum number of groups reached.\n";
        return false;
    }
}


//Contact add in Group menu
void addContactToGroupMenu(ContactsBook& contactsBook)
{
    int contactIndex, groupIndex;
    cout << "Enter the index of the contact you want to add to a group: ";
    cin >> contactIndex;
    cout << "Enter the index of the group to which you want to add the contact: ";
    cin >> groupIndex;

    // Adjust index to zero-based
    contactIndex -= 1;
    groupIndex -= 1;

    // Check if indices are within bounds
    if (contactIndex >= 0 && contactIndex < contactsBook.getCountOfContacts() &&
        groupIndex >= 0 && groupIndex < contactsBook.getNumGroups())
    {
        bool success = contactsBook.addContactToGroup(contactIndex, groupIndex);
        if (success)
        {
            cout << "Contact added to the group successfully.\n";
            cout << "---------------------------------------------------------------------|\n";
        }
        else
        {
            cerr << "Failed to add contact to the group.\n";
            cerr << "---------------------------------------------------------------------|\n";
        }
    }
    else

    {
        cerr << "Invalid indices. Please ensure the indices are within bounds and start from 1.\n";
    }
}


//Add contacts to group
bool ContactsBook::addContactToGroup(int contactIndex, int groupIndex)
{

    if (contactIndex >= 0 && contactIndex < numContacts && groupIndex >= 0 && groupIndex < numGroups)
    {
        groups[groupIndex].addContact(contactIndex);
        return true;
    }
    return false;
}


//Store Groups to a File.
void ContactsBook::storeGroupsToFile(const string& fileName) const
{
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (int i = 0; i < numGroups; ++i)
        {
            outFile << "Group Name: " << groups[i].getName() << endl;
            outFile << "         |Group Members|         \n";
            const int* contactIDs = groups[i].getContactIDs();
            int numContactsInGroup = groups[i].getNumContacts();
            for (int j = 0; j < numContactsInGroup; ++j) {
                int contactIndex = contactIDs[j];
                const Contact& contact = contacts[contactIndex];
                outFile << "Index: " << contactIndex + 1 << ", " << "First Name: " << contact.getFirstName() << ", Last Name: " << contact.getLastName() << endl;
                outFile << "Phone: " << contact.getPhone() << endl; // Add phone number
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Groups stored to file successfully.\n";
        cout << "--------------------------------------------|\n";
    }
    else
    {
        cerr << "Error: Unable to open file for writing.\n";
        cout << "--------------------------------------------|\n";
    }
}


//Remove contact from a Group
bool ContactsBook::removeContactFromGroup(int contactIndex, int groupIndex)
{
    if (contactIndex >= 0 && contactIndex < numContacts && groupIndex >= 0 && groupIndex < numGroups) {
        Group& group = groups[groupIndex];
        const int* contactIDs = group.getContactIDs(); // Use const int* instead
        int numContactsInGroup = group.getNumContacts();

        // Find and remove the contact index from the group
        for (int i = 0; i < numContactsInGroup; ++i) 
        {
            if (contactIDs[i] == contactIndex) 
            {
                // Modify the group's contact IDs array
                int* mutableContactIDs = const_cast<int*>(contactIDs); 
                
                // Shift elements to fill the gap
                for (int j = i; j < numContactsInGroup - 1; ++j) 
                {
                    mutableContactIDs[j] = mutableContactIDs[j + 1];
                }
                mutableContactIDs[numContactsInGroup - 1] = -1; 
                group.decrementNumContacts(); // Decrement numContacts
                return true;
            }
        }
    }
    return false;
}


//View Contact Group
void ContactsBook::viewContactGroups(int contactIndex) const
{
    if (contactIndex >= 0 && contactIndex < numContacts)
    {
        searchHistory.addSearchQuery("View Contact Groups"); // Update search history
        cout << "Groups for contact at index " << contactIndex + 1 << "                              |\n";
        for (int i = 0; i < numGroups; ++i)
        {
            const int* contactIDs = groups[i].getContactIDs();
            int numContactsInGroup = groups[i].getNumContacts();
            for (int j = 0; j < numContactsInGroup; ++j)
            {
                if (contactIDs[j] == contactIndex)
                {
                    cout << "Index: " << contactIndex + 1
                        << "                                                   |\n";  // Display the index
                    cout << "- " << groups[i].getName() << endl;
                    cout << "-----------------------------------------------------------|\n";
                    // Increment the view count for the group
                    groups[i].incrementViewCount();
                    return; // Exit loop as we found the contact in one group
                }
            }
        }
    }
    else
    {
        cout << "Invalid contact index.\n";
        cout << "-----------------------------------------------------------|\n";
    }
}



//Delete a Group
void ContactsBook::deleteGroup(int groupIndex)
{
    if (groupIndex >= 0 && groupIndex < numGroups)
    {
        // Remove the group from the array
        for (int i = groupIndex; i < numGroups - 1; ++i)
        {
            groups[i] = groups[i + 1];
        }
        numGroups--;
        cout << "Group deleted Successfully.\n";
        cout << "-----------------------------------------------|\n";
    }
    else
    {
        cerr << "Invalid group index.\n";
        cout << "-----------------------------------------------|\n";
    }
}

//Contacts limiter in Group
void Group::addContact(int contactID)
{
    if (numContacts < 100)
    {
        contactIDs[numContacts++] = contactID;
    }

    else
    {
        cerr << "Error: Maximum number of contacts reached in group '" << name << "'.\n";
    }
}







void SearchHistory::displayHistory() const
{
    cout << "-----------------------------------------------|\n";
    cout << "Search History:\n";
    for (int i = 0; i < numEntries; ++i)
    {
        cout << queries[i] << endl;
    }

    cout << "-----------------------------------------------|\n";
}


void SearchHistory::addSearchQuery(const string& query)
{
    // Shift previous queries to make space for the new one
    int i = min(numEntries, MAX_ENTRIES - 1);
    while (i > 0)
    {
        queries[i] = queries[i - 1];
        --i;
    }

    queries[0] = query;
    numEntries = min(numEntries + 1, MAX_ENTRIES);
}


//Display Search History
void ContactsBook::displaySearchHistory() const
{
    bool contactOrGroupViewed = false; 

    cout << "-----------------------------------------------|\n";
    cout << "Search History:\n";

    // Iterate over each contact
    for (int i = 0; i < numContacts; ++i)
    {
        const Contact& contact = contacts[i];
        
        if (contact.getViewCount() > 0)
        {
            cout << "Index " << i + 1 << ": View Contact Details " << contact.getViewCount() << " times" << endl;
            contactOrGroupViewed = true;
        }
    }

    // Iterate over each group
    for (int i = 0; i < numGroups; ++i)
    {
        const Group& group = groups[i];
        // Check if the group was viewed
        if (group.getViewCount() > 0)
        {
            cout << "Group '" << group.getName() << "': Viewed " << group.getViewCount() << " times" << endl;
            contactOrGroupViewed = true;
        }
    }

    // If no contact or group was viewed, display a message
    if (!contactOrGroupViewed)
    {
        cout << "No contact or group viewed.\n";
    }

    cout << "-----------------------------------------------|\n";
}






void addingContactcases(ContactsBook& contactsBook) 
{
    int choice;

    system("Color 04");
    cout << "                ~~~~~~~~{Contact Management System}~~~~~~~~";
    do
    {
        choice = displayMenuAndGetChoice();
        system("Color e9");
        switch (choice)
        {
        case 1:
        {
            // Add new contact
            Contact contact = getContactDetailsFromInput(contactsBook); // Pass the contactsBook object as an argument
            bool success = contactsBook.addContact(contact);
            if (success)
            {
                cout << "Contact added successfully with index: " << contactsBook.getCountOfContacts() << endl;
            }
            break;
        }


        case 2:
        {
            system("Color e9");
            contactsBook.mergeDuplicates();
            cout << "-------------------\n";
            cout << "|Merging Contacts:|\n";
            cout << "-------------------------------------|\n";
            cout << "Done! Duplicates merged successfully.|\n";
            cout << "-------------------------------------|\n";
            break;
        }

        case 3:
        {
            system("Color e9");
            string fileName;
            cout << "---------------------------\n";
            cout << "|Contacts Storing to File:|\n";
            cout << "-------------------------------------------|\n";
            cout << "Enter file name to store contacts:         |\n";
            cin >> fileName;
            contactsBook.storeToFile(fileName);
            cout << "Done! Contacts stored to file successfully.|\n";
            cout << "-------------------------------------------|\n";
            break;
        }


        case 4:
        {
            system("Color e9");
            string fileName;
            cout << "-----------------------------\n";
            cout << "|Contacts Loading From File:|\n";
            cout << "---------------------------------------|\n";
            cout << "Enter file name to load contacts from: |\n";
            cin >> fileName;
            contactsBook.loadFromFile(fileName);
            cout << "Contacts loaded from file successfully.|\n";
            cout << "---------------------------------------|\n";
            break;
        }


        case 5:
        {
            system("Color e9");
            string sortBy;
            cout << "------------------\n";
            cout << "|Sorting Contats:|\n";
            cout << "-------------------------------------------------|\n";
            cout << "Enter sorting criteria (first_name or last_name):|\n";
            cin >> sortBy;
            cout << "-------------------------------------------------|\n";
            contactsBook.printContactsSorted(sortBy);
            break;
        }


        case 6:
        {
            system("Color e9");
            string searchTerm;
            cout << "------------\n";
            cout << "|Searching:|\n";
            cout << "------------------------|\n";
            cout << "Enter search term:      |\n";
            cin >> searchTerm;
            int numMatches = 0;
            Contact* matchedContacts = contactsBook.searchContacts(searchTerm, numMatches);
            cout << "Matched Contacts for    |\n" << searchTerm << "'\n";
            for (int i = 0; i < numMatches; ++i)
            {
                cout << "First Name:             |\n" << matchedContacts[i].getFirstName() << "\n"
                    << "Last Name:              |\n" << matchedContacts[i].getLastName() << "\n"
                    << "Phone:                  |\n" << matchedContacts[i].getPhone() << "\n"
                    << "Email:                  |\n" << matchedContacts[i].getEmail() << "\n"
                    << "Address:                |\n" << matchedContacts[i].getAddress().getStreet() << ", "
                    << matchedContacts[i].getAddress().getCountry() << ", "
                    << matchedContacts[i].getAddress().getCity() << ", "
                    << matchedContacts[i].getAddress().getHouse() << "\n";

            }
            cout << "------------------------|\n";
            delete[] matchedContacts; // Don't forget to free memory
            break;
        }


        case 7:
        {
            system("Color e9");
            cout << "----------------\n";
            cout << "|Total Contacts:|\n";
            cout << "-------------------------|\n";
            cout << "Total number of contacts:|\n" << contactsBook.getCountOfContacts() << "\n";
            cout << "-------------------------|\n";
            break;
        }


        case 8:
        {
            system("Color e9");
            int index;
            cout << "------------------\n";
            cout << "|Viewing Contact:|\n";
            cout << "-----------------------------------------------|\n";
            cout << "Enter the index of the contact you want to view|\n";
            cin >> index;

            Contact* contact = contactsBook.getContactByIndex(index - 1); // Adjust to zero-based index
            if (contact)
            {
                cout << "\nDetails of Contact at index " << index << "                  |\n";
                cout << "First Name: " << contact->getFirstName() << "                                  |\n"
                    << "Last Name: " << contact->getLastName() << "                                   |\n"
                    << "Phone: " << contact->getPhone() << "                                       |\n"
                    << "Email: " << contact->getEmail() << "                                       |\n"
                    << "Complete Address: \n"
                    << "House no. " << contact->getAddress().getHouse()
                    << ", Street no. " << contact->getAddress().getStreet()
                    << ", City " << contact->getAddress().getCity()
                    << ", Country " << contact->getAddress().getCountry() << "   |\n\n";
                cout << "-----------------------------------------------|\n";
            }
            else
            {
                cout << "Invalid index.\n";
                cout << "-----------------------------------------------|\n";
            }
            break;
        }


        case 9:
        {
            system("Color e9");
            int index;
            cout << "-----------------\n";
            cout << "|Update Contact:|\n";
            cout << "-------------------------------------------------------------------|\n";
            cout << "Enter the index of the contact you want to update (starting from 1)|\n";
            cin >> index;
            // Adjust index to zero-based
            index -= 1;
            Contact* contact = contactsBook.getContactByIndex(index);
            if (contact)
            {
                Contact updatedContact = getContactDetailsFromInput(contactsBook); // Pass contactsBook object
                contactsBook.updateContactDetails(index, updatedContact.getFirstName(), updatedContact.getLastName(), updatedContact.getPhone(), updatedContact.getEmail(), updatedContact.getAddress());
                cout << "Contact details updated successfully.\n";
                cout << "-------------------------------------------------------------------|\n";
            }
            else
            {
                cout << "Invalid index.\n";
                cout << "-------------------------------------------------------------------|\n";
            }
            break;
        }


        case 10:
        {
            system("Color e9");
            int index;
            cout << "-------------------\n";
            cout << "|Delete a Contact:|\n";
            cout << "---------------------------------------------------|\n";
            cout << "Enter the index of the contact you want to delete  |\n";
            cin >> index;
            contactsBook.deleteContact(index);
            cout << "Contact deleted successfully.\n";
            cout << "---------------------------------------------------|\n";
            break;
        }


        case 11:
        {
            system("Color e9");
            if (contactsBook.getNumGroups() >= 10)
            {
                cout << "Maximum number of groups reached. Cannot create more groups.\n";
            }
            else
            {
                string groupName;
                cout << "-----------------\n";
                cout << "|Creating Group:|\n";
                cout << "-----------------------------------------------|\n";
                cout << "Enter the name of the group                    |\n";
                cin >> groupName;

                contactsBook.createGroup(groupName);
            }
            break;
        }


        case 12:
        {
            system("Color e9");
            cout << "-----------------------\n";
            cout << "|Add Contact in Group:|\n";
            cout << "---------------------------------------------------------------------|\n";
            addContactToGroupMenu(contactsBook);
            break;
        }


        case 13:
        {
            system("Color e9");
            char choice;
            cout << "----------------------\n";
            cout << "|Store group in File:|\n";
            cout << "--------------------------------------------|\n";
            cout << "Do you want to store groups to a file? (y/n)|\n";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                string fileName;
                cout << "Enter file name to store groups             |\n";
                cin >> fileName;
                contactsBook.storeGroupsToFile(fileName);
            }
            break;
        }


        case 14:
        {
            system("Color e9");
            int contactIndex, groupIndex;

            cout << "----------------------------\n";
            cout << "|Remove Contact from Group:|\n";
            cout << "-------------------------------------------------------------------------|\n";
            cout << "Enter the index of the contact you want to remove from a group:          |\n";
            cin >> contactIndex;
            cout << "Enter the index of the group from which you want to remove the contact:  |\n";
            cin >> groupIndex;

            // Adjust index to zero-based
            contactIndex -= 1;
            groupIndex -= 1;

            if (contactsBook.removeContactFromGroup(contactIndex, groupIndex))
            {
                cout << "Contact removed from the group successfully.\n";
                cout << "-------------------------------------------------------------------------|\n";
            }
            else
            {
                cout << "Failed to remove contact from the group. Please check the indices.\n";
                cout << "-------------------------------------------------------------------------|\n";
            }
            break;
        }


        case 15:
        {
            system("Color e9");
            int contactIndex;

            cout << "------------------------\n";
            cout << "|View Contact in Group:|\n";
            cout << "-----------------------------------------------------------|\n";
            cout << "Enter the index of the contact you want to view its groups |\n ";
            cin >> contactIndex;
            contactsBook.viewContactGroups(contactIndex - 1); // Adjust to zero-based index
            break;
        }


        case 16:
        {

            system("Color e9");

            int groupIndex;

            cout << "-----------------\n";
            cout << "|Delete a Group:|\n";
            cout << "-----------------------------------------------|\n";
            cout << "Enter the index of the group you want to delete|\n";
            cin >> groupIndex;
            contactsBook.deleteGroup(groupIndex - 1); // Adjust to zero-based index
            break;
        }


        case 17:
        {
            system("Color e9");
            cout << "-----------------\n";
            cout << "|Display History:|\n";
            cout << "-----------------------------------------------|\n";
            contactsBook.displaySearchHistory();
            break;
        }

        case 0:
            system("Color 80");
            cout << "Exiting program...\n";
            break;
        default:
            system("Color 80");
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}