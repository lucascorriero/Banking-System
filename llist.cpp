/*****************************************************************
//  NAME:        Lucas Corriero
// 
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
// 
//  INSTRUCTOR:  Ravi Narayan
// 
//  DATE:        April 25, 2023
// 
//  FILE:        user_interface.cpp
//  
//  DESCRIPTION:
//     This file contains the functions that are called in 
//     user_interface.c. The functions in this file are 
//     addRecord, printAllRecords, findRecord, deleteRecord
//     writefile, readfile & cleanup
//  
// 
****************************************************************/

#include <cstring>
#include <iostream>
#include <fstream>
#include "llist.h"

/*****************************************************************
//  Function name: llist()
//
//  DESCRIPTION:   Calls readfile and sets the file name
//
//  Parameters:    N/A
//
//  Return values: N/A
****************************************************************/

llist::llist()
{
    int temp;
    strcpy(filename, "SecretBankRecords");
    start = NULL;
    temp = readfile();
    if (temp == -1)
    {
        std::cout << "Unable to open file to retrieve records";
    }
}

/*****************************************************************
//  Function name: llist()
//
//  DESCRIPTION:   Calls readfile and sets the file name
//
//  Parameters:    newfilename (char []) : The name of the file to
//                                         be created
//  Return values: N/A
****************************************************************/

llist::llist(char newfilename[])
{
    strcpy(filename, newfilename);
    int temp;
    start = NULL;
    temp = readfile();
    if (temp == -1)
    {
        std::cout <<"Unable to open file to retrieve records";
    }
}

/*****************************************************************
//  Function name: ~llist()
//
//  DESCRIPTION:   Calls writefile and cleanup functions before the 
//                 class closes
//
//  Parameters:    N/A
//
//  Return values:  N/A
****************************************************************/

llist::~llist()
{
    int temp = 0;
    temp = writefile();
        if (temp == -1)
        {
            std::cout <<"\nUnable to open File to save Records. RECORDS NOT SAVED\n";
        }
        if (temp == -2)
        {
            std::cout <<"\nNo records in memory. New records not saved\n";
        }
    cleanup();
}

/*****************************************************************
//  Function name: readfile
//
//  DESCRIPTION:   This function reads all the records in a .txt and
//                 writes them into memory.
//
//  Parameters:   N/A
//
//  Return values:  0 : success
//                 -1 : File could not be opened.
****************************************************************/

int llist::readfile()
{
    int uaccountno;
    char uname[30];
    char uaddress[50];
    struct record * temp;
    struct record * position;
    struct record * previous;
    char end;
    int zero = 0;
    int begining;
    int result;
    #ifdef DEBUG
    std::cout << "Variables used with Readfile start: ";
    std::cout << (void*)start;
    std::cout << "filename: ";
    std::cout << filename;
    std::cout << "\n";
    #endif
    begining = 0;
    position = (struct record *) (operator new(sizeof(struct record)));
    std::ifstream MyFile(filename);
    if (!MyFile.is_open()||MyFile.peek() == std::ifstream::traits_type::eof())
    {
        MyFile.close();
        result=-1;
    }
    else
    {
        while ( end != '#'&&end != EOF)
        {
            MyFile >> uaccountno;
            MyFile.get();
            MyFile.getline(uname, 30);
            zero = MyFile.get();
            MyFile.getline(uaddress, 50, '}');
            end = MyFile.get();
            if (begining == 0 && end != -1)
            {
                start = position;
                begining = 1;
            }
            if (zero == -1)
            {
                if (previous != NULL)
                {
                    previous->next = NULL;
                }
                end='#';
            }
            else
            {
                temp = (struct record *) (operator new(sizeof(struct record)));
                position->next = temp;
                strncpy(position->name, uname, 30);
                strncpy(position->address, uaddress, 50);
                position->accountno = uaccountno;
                previous = position;
                position = temp;
            }
        }
        #ifdef DEBUG
        std::cout << "Variables after running Readfile start: ";
        std::cout << (void*)start;
        std::cout << "filename: ";
        std::cout << filename;
        std::cout << "\n";
        #endif
        MyFile.close();
        result = 0;
    }
    return result;
}

/*****************************************************************
//  Function name: writefile
//
//  DESCRIPTION:   This function writes all the records in memory to 
//                 a .txt file.
//
//  Parameters:    N/A
//
//  Return values:  0 : success
//                 -1 : File could not be opened
//                 -2 : No records in memory to write to .txt file.
****************************************************************/

int llist::writefile()
{
    std::ofstream MyFile(filename);
    struct record * position;
    #ifdef DEBUG
    std::cout << "Variables used with writefile start: ";
    std::cout << (void*)start;
    std::cout << "filename: ";
    std::cout << filename;
    std::cout << "\n";
    #endif
    if ( !MyFile.is_open() )
    {
        MyFile.close();
        return -1;
    }
    position = start;
    if (start == NULL)
    {
        return -2;
    }
    else
    {
        while (position != NULL)
        {
            MyFile << position->accountno;
            MyFile << "\n";
            MyFile << position->name;
            MyFile << ".\n";
            MyFile << position->address;
            MyFile <<"}\n";
            position = position->next;
        }
    }
    MyFile.close();
    #ifdef DEBUG
    std::cout << "Variables after running writefile start: ";
    std::cout << (void*)start;
    std::cout << "filename: ";
    std::cout << filename;
    std::cout << "\n";
    #endif
    return 0;
}

/*****************************************************************
//  Function name: addRecord
//
//  DESCRIPTION:   This function allows for another record to be added
//                 according to it's account number
//
//  Parameters:    uaccountno (int): The account number of the
//                                   to-be added record.
//                 uname (char []): The name of the to-be added
//                                  record
//                 uaddress (char []): The address of the to-be
//                                     added record
//  Return values: N/A
****************************************************************/

void llist::addRecord(int uaccountno, char *uname, char *uaddress)
{
    struct record * temp;
    struct record * position;
    struct record * previous;
    int moved;
    #ifdef DEBUG
    std::cout << "Variables used with addRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "name: ";
    std::cout << uname;
    std::cout << "address: ";
    std::cout << uaddress;
    std::cout << "\n";
    #endif
    position = start;
    previous = NULL;
    moved = 0;
    temp = (struct record *) (operator new(sizeof(struct record)));
    temp->accountno = uaccountno;
    strcpy(temp->name, uname);
    strcpy(temp->address, uaddress);
    if (start == NULL)
    {
        start = temp;
        temp->next = NULL;
    }
    else
    {
        while ((uaccountno > (position->accountno)) && (position->next != NULL))
        {
            previous = position;
            position = (position->next);
            moved = 1;
        }
        if ((uaccountno > (position->accountno)))
        {
            (position->next) = temp;
            (temp->next) = NULL;
        }
        else
        {
            (temp->next) = position;
            if (previous != NULL)
            {
                (previous->next = temp);
            }
            if (moved == 0)
            {
                start = temp;
            }
        }
    }
    #ifdef DEBUG
    std::cout << "Variables after running addRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "name: ";
    std::cout << uname;
    std::cout << "address: ";
    std::cout << uaddress;
    std::cout << "\n";
    #endif
}

/*****************************************************************
//  Function name: findRecord
//
//  DESCRIPTION:   This function searchs for a certain record/records
//                 and then if it successfully finds that record.
//                 It prints the record.
//
//  Parameters:   uaccountno(int) : the account number of the record 
//  		                        the user wishes to find.
//
//  Return values:  0 : success
//                  -1: Record is not found
//
****************************************************************/

int llist::findRecord(int uaccountno)
{
    struct record * position;
    struct record * previous;
    int result;
    #ifdef DEBUG
    std::cout << "Variable used with findRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "\n";
    #endif
    position = start;
    previous = NULL;
    result = 0;
    if ( start == NULL)
    {
        result = -1;
        #ifdef DEBUG
        std::cout << "Variable after running findRecord accountno: ";
        std::cout << uaccountno;
        #endif
        return result;
    }
    while ( uaccountno > (position->accountno) && (position->next) != NULL )
    {
        previous = position;
        position = (position->next);
    }
    if ( uaccountno < (position->accountno) )
    {
        result = -1;
        #ifdef DEBUG
        std::cout << "Variable used with findRecord accountno: ";
        std::cout << uaccountno;
        std::cout << "\n";
        #endif
        return result;
    }
    if ( previous == NULL )
    {
        while ( (!(position == NULL)&& uaccountno == (position->accountno) ))
        {
            std::cout << "Account Number:";
            std::cout << position->accountno;
            std::cout << "\n";
            std::cout <<"Name: ";
            std::cout << position->name;
            std::cout << "\n";
            std::cout << "Address: ";
            std::cout << position->address;
            std::cout << "\n";
            std::cout << "\n";
            previous = position;
            position = (position->next);
        }
    }
    else
    {
        while ( (position) != NULL && uaccountno == (position->accountno) )
        {
            std::cout << "Account Number:";
            std::cout << position->accountno;
            std::cout << "\n";
            std::cout <<"Name: ";
            std::cout << position->name;
            std::cout << "\n";
            std::cout << "Address: ";
            std::cout << position->address;
            std::cout << "\n";
            std::cout << "\n";
            position = (position->next);
            previous->next = position;
        }
    }
    #ifdef DEBUG
    std::cout << "Variable after running findRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "\n";
    #endif
    return result;
}

/*****************************************************************
//  Function name: printAllRecords
//
//  DESCRIPTION:   This function prints all the Records stored in 
//                 memory
//
//  Parameters:    start (struct record *): the address to which 
//                 the first record is located.
//
//  Return values:  N/A
****************************************************************/

void llist::printAllRecords()
{
    struct record * position;
    position = start;
    if ( start == 0)
    {
        #ifdef DEBUG
        std::cout << "Variable used with printall start: ";
        std::cout << (void*)start;
        std::cout << "\n";
        #endif
        std::cout <<"There are no Records to print.\n";
    }
    else
    {
        #ifdef DEBUG
        std::cout << "Variable used with printall start: ";
        std::cout << (void*)start;
        std::cout << "\n";
        #endif
        while ( position != 0)
        {
            std::cout << "Account Number:";
            std::cout << position->accountno;
            std::cout << "\n";
            std::cout <<"Name: ";
            std::cout << position->name;
            std::cout << "\n";
            std::cout << "Address: ";
            std::cout << position->address;
            std::cout << "\n";
            std::cout << "\n";
            position = position->next;
        }
    }
    #ifdef DEBUG
    std::cout << "Variable used with printall start: ";
    std::cout << (void*)start;
    std::cout << "\n";
    #endif
}

/*****************************************************************
//  Function name: deleteRecord
//
//  DESCRIPTION:   This function searches for the record in memory
//                 according to the entered account number and 
//                 deletes the record/records if found.
//
//  Parameters:    uaccountno: the account number of the record
//                             the user entered to delete that 
//                             record
//
//  Return values:  0 : success
//                 -1 : Record was not deleted because it was not 
//                      in memory
****************************************************************/

int llist::deleteRecord(int uaccountno)
{
    struct record * position;
    struct record * previous;
    int result;
    #ifdef DEBUG
    std::cout << "Variable used with deleteRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "\n";
    #endif
    position = start;
    previous = NULL;
    result = 0;
    if (start == NULL)
    {
        result = -1;
        #ifdef DEBUG
        std::cout << "Variable used with deleteRecord accountno: ";
        std::cout << uaccountno;
        std::cout << "\n";
        #endif
        return result;
    }
    while ( uaccountno > (position->accountno) && (position->next) != NULL )
    {
        previous = position;
        position = (position->next);
    }
    if ( uaccountno < (position->accountno) )
    {
        result = -1;
        #ifdef DEBUG
        std::cout << "Variable used with deleteRecord accountno: ";
        std::cout << uaccountno;
        std::cout << "\n";
        #endif
        return result;
    }
    if ( previous == NULL )
    {
        while ((!(position == NULL)&& uaccountno == (position->accountno) ))
        {
            previous = position;
            position = (position->next);
            delete(previous);
        }
        start = position;
    }
    else
    {
        while ( (position) != NULL && uaccountno == (position->accountno) )
        {
            position = (position->next);
            delete(previous->next);
            previous->next = position;
        }
    }
    #ifdef DEBUG
    std::cout << "Variable after running deleteRecord accountno: ";
    std::cout << uaccountno;
    std::cout << "\n";
    #endif
    return result;
}

/*****************************************************************
//  Function name: cleanup
//
//  DESCRIPTION:   This function erases all records from memory
//                 and sets start to be equal to NULL.
//
//  Parameters:   N/A
//
//  Return values: N/A
****************************************************************/

void llist::cleanup()
{
    struct record * position;
    struct record * previous;
    #ifdef DEBUG
    std::cout << "Variable used with cleanup start: ";
    std::cout << (void*)start;
    std::cout << "\n";
    #endif
    position = start;
    while (position != NULL)
    {
        previous = position;
        position = (position->next);
        delete(previous);
    }
    start = NULL;
    #ifdef DEBUG
    std::cout << "Variable after running cleanup cleanup start: ";
    std::cout << (void*)start;
    std::cout << "\n";
    #endif
}
