#include <iostream>
#include <sstream>
using namespace std;

string INTEGER = "INTEGER";
string PLUS = "PLUS";
string MINUS = "MINUS";
string EOFMY = "EOF";

int chartoInt(char x){
	int y;

	stringstream s;
	s << x;
	s >> y;
	return y;
}

int chartoInt(string x){
	int y;

	stringstream s;
	s << x;
	s >> y;
	return y;
}

class charMy {
	public :
		charMy(char val){
			this->val = val;
		}

		char val;
};