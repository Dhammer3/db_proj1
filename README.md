# db_proj1

This program is the first assignment for CSC30500, Databases. 

The main goal of this program is to add books, libraries, and holdings of books to libraries and save them in a database. 
There are 3 databases in total, one for the books, libraries and holdings. 

My main approach to this problem was to keep the code as simple as possible, make small functions that have a single responsibility and try to make the code as self documenting as possible. When the user starts the program, the first function that is called inside the main loop is start_up() which checks to see if the databases are created; if they are not, this function creates the databases. The main loop then takes input from the user and calls the read_input() function which is the main helper function of the program. 

The program uses several helper functions that have responsibilities such as:
o Determining if the input is valid. 
o Determining if the item _should_ even be added to the library 
o Listing out books, libraries, and holdings. 
o creating, reading, printing and saving to a database
o providing feedback to the user if the chosen operation was successful or not. 

The command string is entered by the user and is composed of 2-3 main parts
1) The first command
2) The second command -  not applicable to all commands. 
3) The the item to be added or found. 

I utilized pointers and concepts related to parsers in order to _pop characters_ off the input string, then built upon that to collect words to determine the necessary operation and to store the information in a consistant way. ex:

The input string **a b 654321 1999 Blythe C++ Rocks!** is composed of several parts. 
'a' is the add command
'b' is the book command
'654321' is the isbn
'1999' is the year
'Blythe' is the author
'C++ Rocks!' is the book title

upon recieving this command, the program pops off the first two commands and sets them to global vars _first_command_ and _second_command_ respectively. We are left with the following command string '654321 1999 Blythe C++ Rocks!. The program then routes the command string to the _add_book_ function and proceeds to pop off each word and set them in a book object. Once the object has been created successfully, the program sends the new book to a function to create a string line based on the information. The string line is then sent to another function to write it in the next available space in the database. 

Some relationships of the books, libraries and holdings. 
library 0---> \infty books
books ---> 1 isbn
library 0---> \infty holdings
