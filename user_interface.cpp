/****************************************************************
//  NAME:        Lucas Corriero
// 
//  HOMEWORK:    Project1
//
//  CLASS:       ICS 212
// 
//  INSTRUCTOR:  Ravi Narayan
// 
//  DATE:        April 20, 2023
// 
//  FILE:        user_interface.c
//  
//  DESCRIPTION:
//     This file contains the user-interface for a banking system
//     the banker interacts with this file, which displays data and
//     accepts inputs while accessing the database. There is four main
//     things the banker can access with this user-interface, adding 
//     a record, printing all the records, finding a record and 
//     deleting a record. When the file is opened it calls the Read
//     file function to see what records are in the .txt file.
//     When this file is closed it calls the Writefile function
//     writes all records to a .txt file and then calls the cleanup
//     function which clears all Records from memory.
//     
//  
// 
****************************************************************/
#include "record.h"
#include "llist.h"
#include <iostream>
#include <cstring>
/*****************************************************************
//  Function name: main
//
//  DESCRIPTION:   This function serves as the user-interface for a bank
//  		   it allows the user to find records, add a record, delete
//  		   a record or print all records.
//
//  Parameters:    argc (int) : contains the number of command-line 
//  		                    arguments
//
//		           argv (char*): contains the command-line arguments
//
//  Return values:  0 : success
//
****************************************************************/
int main() {
    char input[500];
    char address[50];
    char name[30];
    int acc_num;
    int cont = 0;
    int temp = 0;
    int found = 0;
    llist mylist;
    do
    {
        std::cout << "\nHello valued customer welcome to LucasBanking 'Don't Have a Good Day, Have a Great Day' \n\n\n";
        std::cout << "How can I help you today? (Please choose a menu option) \n";
        std::cout << "add: Please type 'add' to add a record to the system.\n";
        std::cout <<"printall: Please type 'printall' to printall records in the system.\n";
        std::cout << "find: Please type 'find' to find a record. \n";
        std::cout << "delete: Please type 'delete' to delete a record from the system\n";
        std::cout << "quit: Please type 'quit' when you would like to exit\n";
        std::cin.getline(input,500);
        if (strcmp(input,"add") == 0||strcmp(input,"ad") == 0||strcmp(input,"a") == 0)
        {
	    found = 1;
            std::cout << "Please enter your account number\n";
            do
            {
                if(std::cin.fail())
                {
                    std::cout << "Please enter a valid account number\n";
                    std::cin.clear();
                    std::cin.ignore();
                    while (std::cin.get()!='\n');    
                }
                std::cin >> acc_num;
            }while (std::cin.fail()||acc_num < 0);
            std::cout << "Please enter your full name\n";
            while (std::cin.get()!='\n'); 
            std::cin.getline(name,30);
            std::cout <<"Please enter your address.";
            std::cout << "\nWhen you're finished typing please press enter ';' on your keyboard.\n";
            std::cin.getline(address,50,';');
            while (std::cin.get()!='\n'); 
            mylist.addRecord(acc_num, name, address);
        }
        if(strcmp(input,"printall") == 0||strcmp(input,"printal") == 0||strcmp(input,"printa") == 0||strcmp(input,"print") == 0||strcmp(input,"prin") == 0||strcmp(input,"pri" )== 0||strcmp(input,"pr") == 0||strcmp(input,"p") == 0)
        {
	    found = 1;
            mylist.printAllRecords();
        }
        if(strcmp(input,"delete") == 0||strcmp(input,"delet") == 0||strcmp(input,"dele") == 0||strcmp(input,"del") == 0||strcmp(input,"de") == 0||strcmp(input,"d") == 0)
        {
	        found=1;
            std::cout << "Please enter your account number\n";
            do
            {
                if(std::cin.fail())
                {
                    std::cout << "Please enter a valid account number\n";
                    std::cin.clear();
                    std::cin.ignore();
                    while (std::cin.get()!='\n');    
                }
                std::cin >> acc_num;
            }while (std::cin.fail()||acc_num < 0);
            while (std::cin.get()!='\n');    
            temp = mylist.deleteRecord(acc_num);
            if (temp == -1)
            {
                std::cout << "Record is not found";
            }
            else
            {
                std::cout << "\nRecord successfully deleted\n";
            }    
        }
        if(strcmp(input,"find") == 0||strcmp(input,"fin") == 0||strcmp(input,"fi") == 0||strcmp(input,"f") == 0)
        {
	        found = 1;
            std::cout << "Please enter your account number\n";
            do
            {
                if(std::cin.fail())
                {
                    std::cout << "Please enter a valid account number\n";
                    std::cin.clear();
                    std::cin.ignore();
                    while (std::cin.get()!='\n');    
                }
                std::cin >> acc_num;
            }while (std::cin.fail()||acc_num < 0);
            temp = mylist.findRecord(acc_num);
            while (std::cin.get()!='\n'); 
            if(temp == -1)
            {
                std::cout << "\n RECORD NOT FOUND\n";
            }
            
        }
        if(strcmp(input,"quit") == 0||strcmp(input,"qui") == 0||strcmp(input,"qu") == 0||strcmp(input,"q") == 0)
        {
            return 0;
        }
        if (found == 0)
        {
            std::cout << "Please enter a valid option";
        }
        found=0;
    }
    while (cont == 0);
    return 0;
}
/*****************************************************************
// Funciton name: getaddress
//
// Description: a function that returns the address
//   
// Parameters:   char address[]: user's input
//  		 int size: how many lines
//  
// 
********************************************************************/
void getaddress(char address[], int size)
{
    int i=0;
    char temp;
    char tempaddress[50];
    do
    {
        std::cout << "Please enter your address.";
        std::cout << "\nWhen you're finished typing please press enter ';' on your keyboard.\n";
        temp=std::cin.get();
        if(temp!=';')
        {
            tempaddress[i]=address[i];
        }
        i=i+1;
    }while(i<size&&temp!=';');
}