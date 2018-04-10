#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include <string>
#include <stdexcept>

struct Result {
	bool ok = false;
	double value = 0;
	std::string error;
	Result() {}
	Result(double v) : ok(true), value(v) {}
	Result(const std::string &e) : value(0), error(e) {}
};

struct Token {
	char kind = '~'; // empty
	double value = 0;
	Token() {}
	Token(char k) : kind(k) {}
	Token(char k, double v) : kind(k), value(v) {}
};

class TokenStream {
private:
	bool fullBuffer = false;
	Token buffer = Token();
	std::string source;
	double readNumber();
public:
	enum kind { num = 'n', end = 'e' };
	TokenStream() {}
	TokenStream(const std::string &s) : source(s) {}
	Token get();
	void putInBuffer(const Token &t);
	bool isEmpty();
	void clear();
};

class Calculator {
private:
	TokenStream stream;
	double term();
	double primary();
	double expression();
public:
	Calculator() {}
	Result getResult(const std::string &s);
};
#endif