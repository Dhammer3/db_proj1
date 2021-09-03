#include <iostream>
#include <fstream>
#include <string>
#include "book.h";
#include "library.h";
#include "utils.h";
using namespace std;

string error_string = "Error processing input.Please follow the correct format. \n";

bool program_is_executing = true;

//TODO
int delete_database() 
{
	return 0;
}

string get_ISBN(string str)
{
	int i = 0;
	char c = str[i];
	string isbn = "";
	while (c != ' ')
	{
		c = str[i];
		isbn += str[i];
		i++;
	}
	return isbn;
}

string get_publish_year(string str)
{
	int i = 0;
	char c = str[i];
	string pub = "";
	while (c != ' ')
	{
		c = str[i];
		pub += str[i];
		i++;
	}
	return pub;
}

bool isbn_matches(string isbn1, string isbn2)
{
	return isbn1.compare(isbn2) == 0;
}

/*
* 1) do a look up on the current book db
* 2) if there is a match to a book in the db by the name or isbn, do not add it.
* 3) give feedback 'error adding book to system, book already exists!
*/
void add_book(string command)
{
	book new_book;
	try {
		new_book.ISBN = get_next_word(command);
		new_book.publish_year = stoi(get_next_word(command));
		new_book.author = get_next_word(command);
		new_book.title = command;
	}
	catch (...) {
		cout << error_string;
		return;
	}
	
	book possible_copy = get_book_by_isbn(new_book.ISBN);

	if (isbn_matches(new_book.ISBN, possible_copy.ISBN))
	{
		cout << "Error adding book to the system, book already exists! \n";
	}
	else {
		string bookline = build_book_line(new_book);
		update_database(bookline, books_db_name);
		cout << "Successfully added book. \n";
	}


}
/*
* 1) do a look up on the current lib db
* 2) if there is a match to a library in the db by the name, do not add it.
* 3) give feedback 'error adding library to system, library already exists!
*/
void add_library(string command)
{
	library l;
	string name = get_next_word(command);
	string city = get_next_word(command);
	string zip = get_next_word(command);


	try {
		l.name = name;
		l.city = city;
		l.zip = std::stoi(zip);
		string lib_line = build_library_line(l);
		update_database(lib_line, libraries_db_name);
		cout << "Successfully added library. \n";
	}
	catch (...)
	{
	 cout << error_string;
	}



}

bool read_command(string command)
{
	bool valid = true;
	string sub = command;

	trim_command_string(command);

	if (!valid_command(first_command_list, first_command, 0))
	{
		return !valid;
	}

	if(add_book_command())
	{
		add_book(command);
	}

	if (add_library_command())
	{
		add_library(command);
	}
	
	if (add_book_to_library_command())
	{
		add_book_to_library(command);
	}
	
	if (list_books_command())
	{
		read_database(books_db_name);
	}

	if (list_libraries_command())
	{
		read_database(libraries_db_name);
	}

	if (find_books_command()) 
	{
		string isbn = get_next_word(command);
		get_books_in_libs(isbn);
	}
	if (quit_command())
	{
		program_is_executing = false;
	}

	return valid;
}

void start_up() 
{
	string databases[3] = { books_db_name, libraries_db_name, books_and_libraries_db_name };
	bool db_created;
	for (int i = 0; i < size(databases); i++) {
		db_created = open_database(databases[i]);
		if (!db_created)
		{
			create_database(databases[i]);
		}
	}
}

int main() {

	string command; 
	bool valid_input;
	start_up();

	while (program_is_executing) {
		std::getline(std::cin,command);
		valid_input = read_command(command);
		
		if (!valid_input) 
		{
			cout << "Please enter a valid command. \n";
		}
	}


	cout << "Thanks for using the library system!\n";
	return 0;
}
