#include <iostream>
#include <sstream>
using namespace std;

string INTEGER = "INTEGER";
string PLUS = "PLUS";
string EOFMY = "EOF";

int chartoInt(char x){
	int y;

	stringstream s;
	s << x;
	s >> y;
	return y;
}