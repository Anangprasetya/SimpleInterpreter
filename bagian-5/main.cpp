#include "deklarasi.h"
#include "error.h"
#include "token.h"
#include "lexer.h"
#include "interpreter.h"

int main(){
	string text;
	Lexer * lexer;
	while(true){
		try{
			cout << "  math> ";
			getline(cin, text);

			if (text != ""){
				lexer = new Lexer(text);
				Interpreter interpreter(lexer);
				double result = interpreter.expr();
				cout << "  " << result << endl;
			}

		}
		catch( const Error& e){
			cout << "  " << e.what() << endl;
		}

		

	}
	return 0;
}


/*
// pengecekan token
int main(){
	Interpreter inter("3+5");
	inter.get_next_token()->print();
	inter.get_next_token()->print();
	inter.get_next_token()->print();
	inter.get_next_token()->print();
	return 0;
}
*/