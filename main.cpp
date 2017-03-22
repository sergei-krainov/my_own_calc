#include <iostream>
#include <map>
using namespace std;

double num_value;
string string_value;
map<string,double> table;

enum Token_value {
	END, NAME, NUMBER,
	PLUS = '+', MINUS = '-', MUL = '*', DIV = '/', PRINT = ';'
};
Token_value curr_tok = PRINT;

Token_value get_token()
{
	cout << "get_token" << endl;
	char c;
	
	do {
		if (!cin.get(c)) return curr_tok = END;
	} while (c != '\n' && isspace(c));
	
	switch(c) {
	case '\n':
	case ';':
		return curr_tok = PRINT;
	case '+':case '-':case '*':case '/':
			return curr_tok = Token_value(c);
	
	case '0':case '1':case '2':case '3':case '4':case '5':
	case '6':case '7':case '8':case '9':case '.':
		cin.putback(c);
		cin >> num_value;
		return curr_tok = NUMBER;
	
	default:
		return curr_tok = PRINT;
	}
}

double prim() {
	//if (get) get_token();
	cout << "prim" << curr_tok << endl;
	
	switch(curr_tok) {
	case NUMBER: {
		double v = num_value;
		get_token();
		return v;
	}
	case NAME: {
		double& v = table[string_value];
		get_token();
		return v;
	}
	default:
		return curr_tok;
	}
}

double term() {
	cout << "term" << curr_tok << endl;
	double left = prim();
	
	for (;;) {
		switch(curr_tok) {
		case MUL:
			left *= prim();
			break;
		case DIV:
			left /= prim();
			break;
		default:
			return left;
		}
	}
}

double expr() {
	cout << "expr" << curr_tok << endl;
	
	double left = term();
	
	for (;;) {
		switch(curr_tok) {
		case PLUS:
			left += term();
			break;
		case MINUS:
			left -= term();
			break;
		default:
			return left;
		}
	}
}

int main()
{	
	while (get_token()) {
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr() << endl;
		cout << num_value << endl;
	}
	
	return 0;
}
