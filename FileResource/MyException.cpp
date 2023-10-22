#include <exception>
#include <iostream>

class MyException : public std::exception
{

public:
	explicit MyException(const char* message) : msg(message) {}

	MyException(MyException const&) noexcept = default;

	MyException& operator=(MyException const&) noexcept = default;
	~MyException() override = default;

	const char* what() const noexcept override { return msg; }
private:
	const char* msg;

};