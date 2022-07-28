class Interpreter {
	public :
		Interpreter(Lexer * lexer){
			this->lexer = lexer;
			this->current_token = this->lexer->get_next_token();
		}

		void error(){
			throw Error("Invalid Syntax");
		}

		double expr(){
			double result = double(this->factor());
			while(this->current_token->type == MUL || this->current_token->type == DIV){
				Token * token = this->current_token;
				if (token->type == MUL){
					this->eat(MUL);
					result = result * double(this->factor());
				}
				else if (token->type == DIV){
					this->eat(DIV);
					double x = result / double(this->factor());
					result = x;
				}
			}

			return result;
		}

		void eat(string token_type){
			if (this->current_token != NULL){
				if (this->current_token->type == token_type)
					this->current_token = this->lexer->get_next_token();
				else
					this->error();
			}
		}

		int factor(){
			Token * token = this->current_token;
			this->eat(INTEGER);
			return token->value;
		}

	private :
		Token * current_token;
		Lexer * lexer;
};