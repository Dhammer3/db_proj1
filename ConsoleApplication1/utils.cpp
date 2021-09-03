#include <iostream>
#include <fstream>
#include <string>
#include "book.h";
#include "utils.h";

using namespace std;
/*
This file contains many of the utility and helper functions used in the main program. 
*/

//global vars. 
char SPACE = ' ';
char first_command = ' ';
char second_command = ' ';

string books_db_name = "../database/books.txt";
string libraries_db_name = "../database/libraries.txt";
string books_and_libraries_db_name = "../database/books_and_libraries.txt";


//valid command strings.
string first_command_list = "alfq";
string add_command_list = "blh";
string list_command_list = "bl";


/*
This function looks at the first two commands. It uses recursion, rather unnecessarily, just wanted to keep my recursion skills sharp. 
returns false if the either of the first two commands are not valid; else it returns true. 
*/
bool valid_command(string valid_commands, char command, int exec_count)
{
	bool valid = 0;
	for (int i = 0; i < valid_commands.size(); i++) {
		if (valid_commands[i] == command) {
			valid= 1;
		}
	}
	if (valid)
	{
		if (command == 'a' && !exec_count)
		{
			return valid_command(add_command_list, second_command, exec_count + 1);
		}
		if (command == 'l'&& !exec_count)
		{
			return valid_command(list_command_list, second_command, exec_count + 1);
		}
		return valid;
	}
	return 0;
}
/*
This function sets the global first_command and second_command chars 
*/
void trim_command_string(string &sub)
{
	first_command = sub[0];
	if (should_expect_second_command()) {
		second_command = sub[2];
		for (int i = 0; i < 4; i++) {
			pop_char(sub);
		}
	}
	if (first_command == 'f') {
		for (int i = 0; i < 2; i++) {
			pop_char(sub);
		}
	}
}

/*
When the user wants to add a book. It takes in the book and returns a book string ready to be put into the database. 
*/
std::string build_book_line(book new_book)
{
	std::string b = new_book.ISBN + SPACE + std::to_string(new_book.publish_year) + SPACE + new_book.author + SPACE + new_book.title + '\n';

	return b;
}
/*
When the user wants to add a library. It takes in the library and returns a library string ready to be put into the database. 
*/
std::string build_library_line(library lib)
{
	std::string l = lib.name + SPACE + lib.city + SPACE + std::to_string(lib.zip) + "\n";
	return l;
}
/*
When the user wants to add a book to a library. It takes in a book and library  and returns a book-library string ready to be put into the database. 
*/
std::string build_book_and_library_line(std::string lib_name, std::string bookline, std::string num_copies)
{
	std::string l = lib_name + ": " + bookline + " Copy Number : " + num_copies + "\n";
	return l;
}

/*
removes a char from @param str
*/

void pop_char(std::string& str)
{
	str.erase(0, 1);
}

/*
removes a \n from @param str
*/

void remove_newLine(std::string& str)
{
	str[str.length() - 1] = ' ';
}

/*
creates a database given @param db_name
*/

int create_database(string db_name) {
	ofstream db;
	db.open(db_name);
	db.close();
	return 0;
}

/*
opens the database given @param db_name
*/

bool open_database(string db_name) {
	ifstream db(db_name);
	db.open(db_name);
	if (db.is_open())
	{
		db.close();
		return 1;
	}
	return 0;
}

/*
prints every line in the database given @param db_name
*/

int read_database(string db_name) {
	string line;
	ifstream db(db_name);
	int line_count = 0;

	if (db.is_open())
	{
		while (getline(db, line))
		{
			cout << line << '\n';
			line_count += 1;

		}
		db.close();
	}
	else
	{
		cout << "Unable to open the database";
	}
	if (!line_count)
	{
		cout << "There are no records for " + db_name + " in the system. \n";
	}
	return 0;
}
/*
looks for a book in the book database and matches it based on the @isbn
returns the book containing the information based on the isbn. 
*/
book get_book_by_isbn(string isbn) {

	book b;
	string line;
	string db_isbn;
	ifstream db(books_db_name);
	if (db.is_open())
	{
		while (getline(db, line))
		{
			db_isbn = get_next_word(line);

			int x = db_isbn.compare(isbn);
			if (x == 0)
			{
				//cout << lib_name + SPACE + line;
				string ISBN = db_isbn;
				string publish_year = get_next_word(line);
				string author = get_next_word(line);
				string title = line;
				b.ISBN = ISBN;
				b.publish_year = std::stoi(publish_year);
				b.author = author;
				b.title = title;
				return b;
			}

		}
		db.close();
	}
	else
	{
		cout << "Unable to open the database";
	}
	return b;
}
bool library_already_in_db(string name) {

	library l;
	string line;
	string db_lib_name;
	ifstream db(libraries_db_name);

	if (db.is_open())
	{
		while (getline(db, line))
		{
			db_lib_name = get_next_word(line);

			int x = db_lib_name.compare(name);
			if (x == 0)
			{

				return 1;
			}

		}
		db.close();
	}
	else
	{
		cout << "Unable to open the database";
	}
	return 0;
}
/*
builds a string based on the next word in the @param str. 
returns the next word in the @param str
*/
std::string get_next_word(std::string& str)
{
	int i = 0;
	if (str[i] == ' ')
	{
		pop_char(str);
	}
	char c = str[i];
	std::string word = "";
	while (c != ' ' && i < str.length())
	{
		c = str[i];
		if (c != ' ')
		{
			word += str[i];
		}
		i++;

	}
	for (int j = 0; j < i; j++)
	{
		pop_char(str);

	}
	return word;
}
/*
prints all books matching the isbn in the holdings library. 
*/
book get_books_in_libs(string isbn) {

	book b;
	string line;
	string db_isbn;
	int line_count = 0;
	ifstream db(books_and_libraries_db_name);
	if (db.is_open())
	{
		while (getline(db, line))
		{
			line_count += 1;
			string temp = line;
			string lib_name = get_next_word(temp);
			db_isbn = get_next_word(temp);

			int x = db_isbn.compare(isbn);
			if (x == 0)
			{
				cout << line+'\n';
			}

		}
		db.close();
	}
	else
	{
		cout << "Unable to open the database";
	}
	if (!line_count)
	{
		cout << "There are no records for " + isbn + " in the system. \n";
	}
	return b;
}
/*
figures out the number of copies that are in the holdings library. 
returns the number of copies of a book. 
*/
int get_copy_number(string isbn, string lib_name)
{
	string line;
	string db_lib_name;
	string db_isbn;

	ifstream db(books_and_libraries_db_name);
	int num_copies = 1;

	if (db.is_open())
	{
		while (getline(db, line))
		{
			db_lib_name = get_next_word(line);
			int x = db_lib_name.compare(lib_name + ":");

			db_isbn = get_next_word(line);
			int y = db_isbn.compare(isbn);

			if (x == 0 && y == 0)
			{
				num_copies += 1;
			}

		}
		db.close();
	}
	else
	{
		cout << "Unable to open the database";
	}
	return num_copies;
}
/*
@param line is the line to be added to the database. 
@param db_name is the database to add the line to 
adds the line to the db
should be a void function. 
*/
int update_database(string line, string db_name)
{
	ofstream db;
	db.open(db_name, std::ios::app);

	if (db.is_open())
	{
		db << line;
	}
	else {
		cout << "Unable to open file";
	}

	return 0;
}
/*
adds a holding to the holdings library. @param command is a trimmed portion of the commmand string containing relevant information. 
*/
void add_book_to_library(std::string command)
{
	book b;
	std::string isbn = get_next_word(command);
	std::string lib_name = get_next_word(command);
	b = get_book_by_isbn(isbn);

	if (b.ISBN == "")
	{
		cout << "Error Adding Holding. This book does not exist!\n";
	}
	else if (!library_already_in_db(lib_name))
	{
		cout << "Error Adding Holding. This library does not exist!\n";
	}
	else 
	{
		std::string bookline = build_book_line(b);
		remove_newLine(bookline);
		std::string copies = std::to_string(get_copy_number(isbn, lib_name));
		std::string book_and_lib_line = build_book_and_library_line(lib_name, bookline, copies);
		update_database(book_and_lib_line, books_and_libraries_db_name);
		cout << "Successfully added book to library. \n";
	}


}

//helper functions for the read_command function. Used in routing the command to the appropriate function. 
bool should_expect_second_command()
{
	return (first_command == 'a' || first_command == 'l');
}
bool add_book_command()
{
	return first_command == 'a' && second_command == 'b';
}
bool add_library_command()
{
	return first_command == 'a' && second_command == 'l';
}
bool add_book_to_library_command()
{
	return first_command == 'a' && second_command == 'h';

}
bool list_books_command()
{
	return first_command == 'l' && second_command == 'b';
}
bool list_libraries_command()
{
	return first_command == 'l' && second_command == 'l';
}
bool find_books_command()
{
	return first_command == 'f';
}
bool quit_command()
{
	return first_command == 'q';

}

