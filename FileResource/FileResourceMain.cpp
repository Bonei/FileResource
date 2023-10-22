// FileResource.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "MyException.cpp"

using namespace std;
namespace fs = std::filesystem;

void ReadFile(ifstream &file) {

	try {
		string line;
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}
	catch (const MyException& e)
	{
		std::cout << "General exception failed: " << e.what() << '\n';
	}
	
}

void TryToOpenFile(const std::filesystem::path& path) {

	try
	{
		std::ifstream file;
		file.open(path, std::ifstream::in);
		if (file.is_open()) {
			ReadFile(file);
		}
	}
	catch (std::ifstream::failure& e) {
		std::cout << "Caught an ios_base::failure.\n"
			<< "Explanatory string: " << e.what() << '\n'
			<< "Error code: " << e.code() << '\n';
	}
	catch (const std::ios_base::failure& e)
	{
		std::cout << "Caught an ios_base::failure.\n"
			<< "Explanatory string: " << e.what() << '\n'
			<< "Error code: " << e.code() << '\n';

	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Allocation failed: " << e.what() << '\n';
	}
	catch (const MyException& e)
	{
		std::cout << "General exception failed: " << e.what() << '\n';
	}
}

	

int main()
{
	string _fileName;
	cout << "---File Manager Linguage---" << std::endl;
	cout << "Enter the file name with path: " << std::endl;
	getline(std::cin, _fileName);

	try
	{
		
		const std::filesystem::path path =  _fileName;
		bool ret = fs::exists(path);
		if (ret) {
			TryToOpenFile(path);
		}
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		cout << "what():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "path2(): " << ex.path2() << '\n'
			<< "code().value():    " << ex.code().value() << '\n'
			<< "code().message():  " << ex.code().message() << '\n'
			<< "code().category(): " << ex.code().category().name() << '\n';
	}
}
