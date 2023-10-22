#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "FileTypeEnum.h"

using namespace std;
namespace fs = std::filesystem;

namespace Resource
{
    template <typename T>
    class FileResource
    {
    public:
        explicit FileResource(const std::string& filename) 
        {
			try
			{
				const std::filesystem::path path = fs::current_path() + "\\" + _fileName;
				bool ret = fs::exists(path);
				if (ret) {
					TryToOpenFile(path);
				}
				else
				{
					cout << "File doesn't exist!!" << std::endl;
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
        };

        ~FileResource() = default;

        void ReadData() 
        {
			if (_fileResource.is_open()) {
				ReadFile(_fileResource);
			}
        };

        void WriteData(const std::string& filename)
        {
            T teste = data;
        };

    private:
        std::unique_ptr<T> _fileResource;

		void TryToOpenFile(const std::filesystem::path& path) {

			try
			{
				(std::ifstream) _fileResource.open(path);
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

		void ReadFile(ifstream& file) {

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
    };
}