ECE2524-ExpenseTracker
======================
**ECE2524 Final Project (Roommate Expense Tracker)**

*Tyler Adams, Teja Chiluvuri, Sasha Gluzinski, Sungha Song*

## Description
This project is an expense tracker that keeps track of expenses between roommates. The *python* directory contains the command line source files in python that implement the roomate expense tracker. The *qt-gui* directory contains a GUI interface designed in Qt that runs the executes the python processes.

## Build Directions
### Dependencies
Please ensure that the following packages are installed in your Linux distribution:
> Python 2.0 (python2)

> Qt Framework (libqt4-dev qt4-qmake)

In order to build the program, run **make** in the base directory (this directory).

## Contributions
> **Tyler Adams**: setup the framework for the GUI and figured out the code to easily and effectively execute the python processes using QProcess

> **Teja Chiluvuri**: Implemented the python processes on the GUI and made minor tweaks to the python files to work well with the Qt code

> **Sasha Gluzinski**: Implemented the expenses.py python code and got the view expenses and add expenses functionality to work

> **Sungha Song**: Implemented the roommates.py python code and got the add roommates, view roommates, and remove roommates functionality to work

## GUI Usage
After the project is built using the **make** command, open the executable file **ExpenseTracker** either from the terminal or by double clicking on it. The GUI is broken down into three section:

>Roommates

>>Manages the roommates by allowing you to add or remove roommates. The top field adds roommates and the bottom check boxes allow you to select roommates to remove.

>Add Expense

>>Allows users to add expenses. The first combo box allows user to chose the roommate who made the expense. Then, the amount of the expense can be entered in the line edit. Lastly, the user must choose all of the other roommates who owe the paid roommate for that expense. The program will automatically devide and calculate how much each individual owes the roommate. Also note that this application does not have a remove expense feature. Rather, every expense is considered an addition and expenses made against two people cancel eachother out when viewing the expenses.

>View Expense

>>Allows the user to select the roommate for which he or she would like to view the expense summary. When View is pressed for a selected roommate, the application displays how much everyone owes that particular roommate. A negative number means that the selected roommate owes the other person that much money.

## Python Usage
./roommate [-a] ROOMMATE_NAME [-r] ROOMMATE_NAME
>-a, --add ROOMMATE_NAME
>>adds a new roommate to the roommates data file

>>EXAMPLE: ./roommate --add "John Smith"

>-r, --remove ROOMATE_NAME
>>removes a roommate from the roommates data file

>>EXAMPLE: ./roommate --remove "John Smith"

./expense add PAID_ROOMATE AMOUNT DEBTED_ROOMATES... --view ROOMATE_NAME
>add
>>adds a new payment

>>EXAMPLE: ./expense add "John Smith" 24.92 "Joe Shmoe" "Bob Adams"

>view ROOMATE_NAME
>>View the debts and owed money for the roomate

>>EXAMPLE: ./expense view "John Smith"