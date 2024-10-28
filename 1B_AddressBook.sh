#!/bin/bash

createAddressBook(){
    if [ ! -e Address_Book.txt ]; then 
        touch Address_Book.txt 
        echo "| Name           | Email             | Phone Number     | Address          |" > Address_Book.txt
        echo "Address Book created successfully."
    else
        echo "Address Book already exists."
    fi
}

viewAddressBook(){
    if [ ! -e Address_Book.txt ]; then 
        echo "Address Book is not created yet. Please create the Address Book first."
        return
    fi

    if [ -s Address_Book.txt ]; then
        echo -e "\n--------- Address Book ---------"
        cat Address_Book.txt
        echo "--------------------------------"
    else
        echo "Address Book is empty."
    fi
}

insertRecord(){
    if [ ! -e Address_Book.txt ]; then 
        echo "Address Book is not created yet. Please create the Address Book first."
        return
    fi

    read -p "Enter Name: " name
    read -p "Enter Email: " email
    read -p "Enter Phone Number: " phone
    read -p "Enter Address: " address

    echo "| $name | $email | $phone | $address |" >> Address_Book.txt
    echo "Record added successfully."
}

deleteRecord(){
    if [ ! -e Address_Book.txt ]; then 
        echo "Address Book is not created yet. Please create the Address Book first."
        return
    fi

    read -p "Enter Name of the record to delete: " name
    if grep -qi "$name" Address_Book.txt; then
        sed -i "/$name/Id" Address_Book.txt
        echo "Record deleted successfully."
    else
        echo "Record not found."
    fi
}

searchRecord(){
    if [ ! -e Address_Book.txt ]; then 
        echo "Address Book is not created yet. Please create the Address Book first."
        return
    fi

    read -p "Enter Name to search: " name
    result=$(grep -i "$name" Address_Book.txt)
    if [ -n "$result" ]; then
        echo -e "\nRecord(s) found:\n$result\n"
    else
        echo "Record not found."
    fi
}

updateRecord(){
    if [ ! -e Address_Book.txt ]; then 
        echo "Address Book is not created yet. Please create the Address Book first."
        return
    fi

    read -p "Enter Name of the record to update: " name

    if grep -qi "$name" Address_Book.txt; then
        sed -i "/$name/Id" Address_Book.txt
        read -p "Enter updated Email: " email
        read -p "Enter updated Phone Number: " phone
        read -p "Enter updated Address: " address
        echo "| $name | $email | $phone | $address |" >> Address_Book.txt
        echo "Record updated successfully."
    else
        echo "Record not found."
    fi
}

main(){
    while true; do
        echo -e "\nWelcome to the Address Book\n"
        echo "1. Create Address Book"
        echo "2. View Address Book"
        echo "3. Insert Record"
        echo "4. Delete Record"
        echo "5. Search Record"
        echo "6. Update Record"
        echo "7. Exit"
        echo "----------------------------------"

        read -p "Enter your choice (1-7): " choice

        case $choice in
            1) createAddressBook ;;
            2) viewAddressBook ;;
            3) insertRecord ;;
            4) deleteRecord ;;
            5) searchRecord ;;
            6) updateRecord ;;
            7) echo "Exiting Address Book. Goodbye!"; exit ;;
            *) echo "Invalid choice. Please try again." ;;
        esac
    done
}

main
