#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

sqlite3* db;

void createTable(std::string tab)
{
	std::string str = "CREATE TABLE IF NOT EXISTS "+tab+"("\
					  "id INT PRIMARY KEY NOT NULL, "\
					  "name TEXT NOT NULL, "\
					  "age INT NOT NULL);";
	char* ermsg;
	sqlite3_open("your directory path/test.db", &db);
	int res = sqlite3_exec(db, str.c_str(), nullptr, nullptr, &ermsg);
	if (res != SQLITE_OK)
	{
		std::cerr << ermsg;
		sqlite3_free(ermsg);
	}
	else
		std::cout << "Table created\n";
	sqlite3_close(db);
}
void insertToTable(unsigned id, std::string name, unsigned age, std::string table)
{
	std::string qry = "INSERT INTO " + table + " (id,name,age) VALUES (" + std::to_string(id) + ", " + name + ", "\
										+ std::to_string(age) + ");";
	//std::string qry = "INSERT INTO " + table + " (id,name,age) VALUES (1,'Idris',23);";
	char* ermsg;
	sqlite3_open("your directory path/test.db", &db);
	int res = sqlite3_exec(db, qry.c_str(), nullptr, nullptr, &ermsg);
	if (res != SQLITE_OK)
	{
		std::cerr << ermsg;
		sqlite3_free(ermsg);
	}
	else
		std::cout << "Insertion ok\n";
	sqlite3_close(db);
}
template<typename...T>
void selectFromTab(std::string tab, T...args) // takes the table name and the different columns (* can be selected), the type is std::string
{
	std::string str = "SELECT ";

	std::vector<std::string>vec;
	(vec.push_back(std::forward<T>(args)), ...);
	for (unsigned i = 0; i < vec.size()-1; i++)
		str +=  vec.at(i) + ", ";  
	str += vec.at(vec.size() - 1);
	str += " FROM " + tab + "; ";

	char* ermsg;
	sqlite3_open("your directory path/test.db", &db);
	auto res = sqlite3_exec(db, str.c_str(), nullptr, nullptr, &ermsg);
	if (res != SQLITE_OK)
	{
		std::cerr << ermsg;
		sqlite3_free(ermsg);
	}
	else
		std::cout << "Table selected\n";
	sqlite3_close(db);
}



int main()
{
	createTable("myTab");
	insertToTable(1, "'Idris'", 21, "myTab");
	insertToTable(2, "'Paul'", 22, "myTab");
	selectFromTab("myTab", "id","name");
	return 0;
}
