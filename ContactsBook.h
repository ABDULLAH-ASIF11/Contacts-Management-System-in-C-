#pragma once
#ifndef CONTACTSBOOK_H
#define CONTACTSBOOK_H
#include <iostream>
#include <fstream>
#include<string>

using namespace std;


// Base class for common attributes
class Base
{
protected:
    string firstName;
    string lastName;
    string phone;
    string email;

public:
    Base() {}
    Base(const string& firstName, const string& lastName, const string& phone, const string& email)
        : firstName(firstName), lastName(lastName), phone(phone), email(email) {}

    // All are Getters

    string getFirstName() const
    {
        return firstName;
    }

    string getLastName() const
    {
        return lastName;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return email;
    }
};


class Address : public Base
{
private:
    string street;
    string country;
    string house;
    string city;

public:
    Address() {}
    Address(const string& street, const string& country, const string& house, const string& city)
        : street(street), country(country), house(house), city(city) {}


    // All are Getters

    string getStreet() const
    {
        return street;
    }

    string getCountry() const
    {
        return country;
    }

    string getCity() const
    {
        return city;
    }

    string getHouse() const
    {
        return house;
    }
};

class Contact : public Base
{
private:
    string firstName;
    string lastName;
    string phone;
    string email;
    int index; 
    Address address;
    int viewCount; 


public:
    Contact() {}
    Contact(const string& firstName, const string& lastName, const string& phone, const string& email, const Address& address, int index)
        : firstName(firstName), lastName(lastName), phone(phone), email(email), address(address), index(index) {}


    // All are Getters

    string getFirstName() const
    {
        return firstName;
    }

    string getLastName() const
    {
        return lastName;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return email;
    }

    Address getAddress() const
    {
        return address;
    }

    int getIndex() const
    {
        return index;
    }

    void updateContact(const string& firstName, const string& lastName, const string& phone, const string& email, const Address& address)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->phone = phone;
        this->email = email;
        this->address = address;
    }

    
    int getViewCount() const
    {
        return viewCount;
    }

  
    void incrementViewCount()
    {
        viewCount++;
    }
};



class Group : public Base
{
private:
    string name;
    int contactIDs[100]; 
    int numContacts;
    mutable int viewCount; 

public:
    Group() : numContacts(0), viewCount(0) {} 

    // Constructor with name
    Group(const string& name) : name(name), numContacts(0), viewCount(0) {}

    // All are Getters
    const string& getName() const
    {
        return name;
    }

    void addContact(int contactID);

    
    const int* getContactIDs() const
    {
        return contactIDs;
    }

    
    int getNumContacts() const
    {
        return numContacts;
    }

    void decrementNumContacts()
    {
        if (numContacts > 0)
        {
            numContacts--;
        }
    }

    
    int getViewCount() const
    {
        return viewCount;
    }

  
    void incrementViewCount() const
    {
        viewCount++;
    }
};




class SearchHistory : public Base
{
private:
    static const int MAX_ENTRIES = 5; 

    string queries[MAX_ENTRIES];
    int numEntries;

public:
    SearchHistory() : numEntries(0) {}


    void addSearchQuery(const string& query);

    void displayHistory() const;
};


class ContactsBook
{
private:
    static const int MAX_CONTACTS = 100;
    static const int MAX_GROUPS = 10; 
    Contact contacts[MAX_CONTACTS];
    int numContacts;
    Group groups[MAX_GROUPS]; 
    int numGroups; 
    mutable SearchHistory searchHistory;

public:
    ContactsBook() : numContacts(0), numGroups(0) {}

    int generateIndex();
    bool addContact(const Contact& contact);
    void mergeDuplicates();
    void storeToFile(const string& fileName) const;
    void loadFromFile(const string& fileName);
    void printContactsSorted(const std::string& sortBy) const;
    friend void manualSort(Contact* contacts, int numContacts, const std::string& sortBy);
    Contact* searchContacts(const string& searchTerm, int& numMatches) const;
    int getCountOfContacts() const;
    Contact* getContactByIndex(int index);
    void updateContactDetails(int index, const string& firstName, const string& lastName, const string& phone, const string& email, const Address& address);
    void deleteContact(int index);
    bool createGroup(const string& groupName);
    bool addContactToGroup(int contactIndex, int groupIndex);
    void storeGroupsToFile(const string& fileName) const;
    bool removeContactFromGroup(int contactIndex, int groupIndex);
    void viewContactGroups(int contactIndex) const;
    void deleteGroup(int groupIndex);
    void displaySearchHistory() const; 



    // All are Getters

    int getNumGroups() const
    {
        return numGroups;
    }
    static int indexCounter;

    
    SearchHistory& getSearchHistory()
    {
        return searchHistory;
    }
};


#endif