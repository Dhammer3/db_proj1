// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string books_db_name = "../database/books.txt";
string libraries_db_name = "../database/libraries.txt";
string books_and_libraries_db_name = "../database/books_and_libraries.txt";

string first_command_list = "alfq";
string add_command_list = "blh";
string list_command_list = "bl";

char first_command;
char second_command;

string c;
char SPACE = ' ';

struct book 
{
	string ISBN;
	int publish_year;
	string author;
	string title;
};

struct library 
{
	string name;
	string city;
	int zip;
};

void pop_char(string& str)
{
	str.erase(0, 1);
}

string get_next_word(string& str)
{
	int i = 0;
	if (str[i] == ' ') 
	{
		pop_char(str);
	}
	char c = str[i];
	string word = "";
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

//START DB OPERATIONS
int create_database(string db_name) {
	ofstream db;
	db.open(db_name);
	db.close();
	return 0;
}

int open_database(string db_name) {
	ifstream db(db_name);
	db.open(db_name);
	if (db.is_open())
	{
		db.close();
		return 1;
	}
	return 0;
}

int read_database(string db_name) {
	string line; 
	ifstream db(db_name);
	if (db.is_open())
	{
		while (getline(db, line))
		{
			cout << line << '\n';

		}
		db.close();
	}
	else 
	{
		cout << "Unable to open the database";
	}
	return 0;
}

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
			if (x==0)
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

book get_books_in_libs(string isbn) {

	book b;
	string line;
	string db_isbn;
	ifstream db(books_and_libraries_db_name);
	if (db.is_open())
	{
		while (getline(db, line))
		{
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
	return b;
}

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
			//cout << line << '\n';
			db_lib_name = get_next_word(line);
			int x = db_lib_name.compare(lib_name+":");
			
			db_isbn = get_next_word(line);
			int y = db_isbn.compare(isbn);

			if (x == 0 && y==0 )
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

//TODO
int delete_database() 
{
	return 0;
}
//END DB OPERATIONS

string build_book_line(book new_book)
{
	string b = new_book.ISBN + SPACE + std::to_string(new_book.publish_year) + SPACE + new_book.author + SPACE + new_book.title + '\n';
	
	return b;
}

string build_library_line(library lib)
{
	string l = lib.name + SPACE + lib.city+ SPACE+ std::to_string(lib.zip)+ "\n";
	return l;
}

string build_book_and_library_line(string lib_name, string bookline,string num_copies)
{
	string l =lib_name + ": "+ bookline + " Copy Number : " + num_copies + "\n";
	return l;
}

//START COMMAND OPERATIONS
int valid_command(string valid_commands, char command)
{
	for (int i = 0; i < valid_commands.size(); i++) {
		if (valid_commands[i] == command) {
			return 1;
		}
	}
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

void remove_newLine(string& str)
{
	str[str.length() - 1] = ' ';
}


int read_command(string command)
{
	string sub = command;
	int valid = 1;
	first_command = command[0];
	if (first_command == 'a'|| first_command =='l') {
		second_command = command[2];
		for (int i = 0; i < 4; i++) {
			pop_char(sub);
		}
	}
	if (first_command == 'f') {
		for (int i = 0; i < 2; i++) {
			pop_char(sub);
		}
	}

	if (valid_command(first_command_list, first_command)) {
		if (first_command == 'a') {

			if (second_command == 'b') {
				book b;
				string ISBN = get_next_word(sub);
				string publish_year = get_next_word(sub);
				string author = get_next_word(sub);
				string title = sub;
				b.ISBN = ISBN;
				b.publish_year = std::stoi(publish_year);
				b.author = author;
				b.title = title;
				string bookline = build_book_line(b);
				update_database(bookline, books_db_name);
				return 0;

			}
			if (second_command == 'l') {
				library l;
				string name= get_next_word(sub);
				string city= get_next_word(sub);
				string zip= get_next_word(sub);
				l.name = name;
				l.city = city;
				l.zip = std::stoi(zip);
				string lib_line = build_library_line(l);
				update_database(lib_line, libraries_db_name);
				return 0;
			}
			if (second_command == 'h') {
				book b;
				string isbn = get_next_word(sub);
				string lib_name = get_next_word(sub);

				b = get_book_by_isbn(isbn);
				string bookline = build_book_line(b);
				remove_newLine(bookline);
				string copies = std::to_string(get_copy_number(isbn, lib_name));
				string book_and_lib_line=build_book_and_library_line(lib_name, bookline, copies);
				update_database(book_and_lib_line, books_and_libraries_db_name);
				return 0;
			}
		
		}
		if (first_command == 'l') {
		
			if (second_command == 'b') {
				read_database(books_db_name);
				return 0;
			}
			if (second_command == 'l') {
				read_database(libraries_db_name);
				return 0;
			}
		}
		if (first_command == 'f') {
			string isbn = get_next_word(sub);
			get_books_in_libs(isbn);
			return 0;
		}
		if (first_command == 'q') {
			cout << "Thanks for using the library system!\n";
			return 1;
		}

	}
	return 0;


}

int start_up() 
{
	int db_created = open_database(books_db_name);
	if (!db_created) {
		create_database(books_db_name);
	}
	db_created = open_database(libraries_db_name);
	if (!db_created) {
		create_database(libraries_db_name);
	}
	db_created = open_database(books_and_libraries_db_name);
	if (!db_created) {
		create_database(books_and_libraries_db_name);
	}
	return 0;
}


int main() {

	string command; 
	int resp = 0;
	start_up();

	while (!resp) {
		std::getline(std::cin,command);
		resp = read_command(command);
		c = command;
		if (resp!=0) {
			cout << "Please enter a valid command \n";
		}
	}



	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
