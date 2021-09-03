//#include <iostream>
//#include <fstream>
//#include <string>
//
//#include"utils.h";
//#include"library.h";
//#include"database_operations.h";
//#include "global_vars.h";
//
////#include "database_operations.h";
//
////std::string books_db_name = "../database/books.txt";
////std::string libraries_db_name = "../database/libraries.txt";
////std::string books_and_libraries_db_name = "../database/books_and_libraries.txt";
////
//
//
//
////START DB OPERATIONS
//int create_database(std::string db_name) {
//	std::ofstream db;
//	db.open(db_name);
//	db.close();
//	return 0;
//}
//
//bool open_database(std::string db_name) {
//	std::ifstream db(db_name);
//	db.open(db_name);
//	if (db.is_open())
//	{
//		db.close();
//		return 1;
//	}
//	return 0;
//}
//
//int read_database(std::string db_name) {
//	std::string line;
//	std::ifstream db(db_name);
//	if (db.is_open())
//	{
//		while (getline(db, line))
//		{
//			std::cout << line << '\n';
//
//		}
//		db.close();
//	}
//	else
//	{
//		std::cout << "Unable to open the database";
//	}
//	return 0;
//}
//
//book get_book_by_isbn(std::string isbn) {
//
//	book b;
//	std::string line;
//	std::string db_isbn;
//	std::ifstream db(books_db_name);
//	if (db.is_open())
//	{
//		while (getline(db, line))
//		{
//			db_isbn = get_next_word(line);
//
//			int x = db_isbn.compare(isbn);
//			if (x == 0)
//			{
//				//cout << lib_name + SPACE + line;
//				std::string ISBN = db_isbn;
//				std::string publish_year = get_next_word(line);
//				std::string author = get_next_word(line);
//				std::string title = line;
//				b.ISBN = ISBN;
//				b.publish_year = std::stoi(publish_year);
//				b.author = author;
//				b.title = title;
//				return b;
//			}
//
//		}
//		db.close();
//	}
//	else
//	{
//		std::cout << "Unable to open the database";
//	}
//	return b;
//}
//
//book get_books_in_libs(std::string isbn) {
//
//	book b;
//	std::string line;
//	std::string db_isbn;
//	std::ifstream db(books_and_libraries_db_name);
//	if (db.is_open())
//	{
//		while (getline(db, line))
//		{
//			std::string temp = line;
//			std::string lib_name = get_next_word(temp);
//			db_isbn = get_next_word(temp);
//
//			int x = db_isbn.compare(isbn);
//			if (x == 0)
//			{
//				std::cout << line + '\n';
//			}
//
//		}
//		db.close();
//	}
//	else
//	{
//		std::cout << "Unable to open the database";
//	}
//	return b;
//}
//
//int get_copy_number(std::string isbn, std::string lib_name)
//{
//	std::string line;
//	std::string db_lib_name;
//	std::string db_isbn;
//	std::ifstream db(books_and_libraries_db_name);
//	int num_copies = 1;
//
//	if (db.is_open())
//	{
//		while (getline(db, line))
//		{
//			//cout << line << '\n';
//			db_lib_name = get_next_word(line);
//			int x = db_lib_name.compare(lib_name + ":");
//
//			db_isbn = get_next_word(line);
//			int y = db_isbn.compare(isbn);
//
//			if (x == 0 && y == 0)
//			{
//				num_copies += 1;
//			}
//
//		}
//		db.close();
//	}
//	else
//	{
//		std::cout << "Unable to open the database";
//	}
//	return num_copies;
//}
//
//int update_database(std::string line, std::string db_name)
//{
//	std::ofstream db;
//	db.open(db_name, std::ios::app);
//
//	if (db.is_open())
//	{
//		db << line;
//	}
//	else {
//		std::cout << "Unable to open file";
//	}
//
//	return 0;
//}
//
////TODO
//int delete_database()
//{
//	return 0;
//}
////END DB OPERATIONS