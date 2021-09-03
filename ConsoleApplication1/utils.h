#pragma once
#include<string>;
#include "book.h";
#include "library.h";
extern char first_command;
extern char second_command;

extern std::string books_db_name;
extern std::string libraries_db_name;
extern std::string books_and_libraries_db_name;
extern std::string first_command_list;
extern std::string add_command_list;
extern std::string list_command_list;



std::string build_book_line(book new_book);
std::string build_library_line(library lib);
std::string build_book_and_library_line(std::string lib_name, std::string bookline, std::string num_copies);
void pop_char(std::string& str);
void remove_newLine(std::string& str);
std::string get_next_word(std::string& str);
void add_book_to_library(std::string command);
int get_copy_number(std::string isbn, std::string lib_name);
int update_database(std::string line, std::string db_name);
int create_database(std::string db_name);
bool open_database(std::string db_name);
int read_database(std::string db_name);
book get_book_by_isbn(std::string isbn);
book get_books_in_libs(std::string isbn);
bool valid_command(std::string valid_commands, char command, int exec_count);
bool library_already_in_db(std::string name);
void trim_command_string(std::string& sub);


bool should_expect_second_command();
bool add_book_command();
bool add_library_command();
bool add_book_to_library_command();
bool list_books_command();
bool list_libraries_command();
bool find_books_command();
bool quit_command();

