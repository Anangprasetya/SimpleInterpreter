#include "deklarasi.h"
#include "error.h"
#include "token.h"
#include "interpreter.h"

int main(){
	string text;
	while(true){
		try{
			cout << "  math> ";
			getline(cin, text);

			if (text != ""){
				Interpreter interpreter(text);
				int result = interpreter.expr();
				if (!interpreter.getError())
					cout << "  " << result << endl;
				else
					throw(interpreter.getError()->kal);
			}

		}
		catch(string e){
			cout << "  " << e << endl;
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