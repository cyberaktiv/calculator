#include "calculator.h"

void error(const std::string &s)
{
	throw std::runtime_error(s);
}

Token TokenStream::get()
{
	if (fullBuffer)
	{
		fullBuffer = false;
		return buffer;
	}

	switch (source[0])
	{
	case '(': case ')':
	case '-': case '*': case '/': case '+':
	{
		char t = source[0];
		source = source.substr(1);
		return Token(t);
	}
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return Token(num, readNumber());
	case ' ':
		source = source.substr(1);
		return get();
	default:
		return Token(end);
	}
}

double TokenStream::readNumber()
{
	unsigned int pos = 0;
	int cntPnt = 0;
	int cntNum = 0;
	std::string num;

	while (isdigit(source.at(pos)) || source[pos] == '.')
	{
		if (source[pos] == '.') cntPnt++;
		if (isdigit(source[pos])) cntNum++;

		num += source[pos];
		pos++;
		if (pos == source.size()) break;
	}

	if (cntPnt > 1 || cntNum == 0)
		error("incorrect number format");

	source = source.substr(pos);
	return stod(num);
}

bool TokenStream::isEmpty()
{
	return (source.size() == 0 && buffer.kind == end);
}

void TokenStream::clear()
{
	source = "";
	fullBuffer = false;
}

void TokenStream::putInBuffer(const Token &t)
{
	buffer = t;
	fullBuffer = true;
}

double Calculator::primary()
{
	Token t = stream.get();
	switch (t.kind) {
	case '(':
	{
		double e = expression();
		t = stream.get();
		if (t.kind != ')') error("')' expected");
		return e;
	}
	case '-': case '+':
	{
		char sign = t.kind;
		t = stream.get();
		if (t.kind == '+' || t.kind == '-') error("multiple sign");
		stream.putInBuffer(t);
		return (sign == '-') ? -primary() : primary();
	}
	case stream.kind::num:
		return t.value;
	default:
		error("incorrect input expression");
	}
	return 0;
}

double Calculator::term()
{
	double left = primary();
	while (true)
	{
		Token t = stream.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double right = primary();
			if (right == 0)
				error("division by zero");
			left /= right;
			break;
		}
		default:
			stream.putInBuffer(t);
			return left;
		}
	}
}

double Calculator::expression()
{
	double left = term();
	while (true)
	{
		Token t = stream.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			stream.putInBuffer(t);
			return left;
		}
	}
}

Result Calculator::getResult(const std::string &s)
{
	stream = s;
	double res;
	try {
		res = expression();
		if (!stream.isEmpty())
		{
			stream.clear();
			return Result("incorrect input expression");
		}
	}
	catch (std::runtime_error& e)
	{
		return Result(e.what());
	}
	return Result(res);
};