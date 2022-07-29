class Interpreter {
	public :
		Interpreter(Lexer * lexer){
			this->lexer = lexer;
			this->current_token = this->lexer->get_next_token();
		}

		void error(){
			throw Error("Invalid Syntax");
		}

		void eat(string token_type){
			if (this->current_token != NULL){
				if (this->current_token->type == token_type)
					this->current_token = this->lexer->get_next_token();
				else
					this->error();
			}
		}

		double factor(){
			Token * token = this->current_token;
			if (token->type == INTEGER)
			{
				this->eat(INTEGER);
				return token->value;
			}
			else if (token->type == LPAREN){
				this->eat(LPAREN);
				double result = this->expr();
				this->eat(RPAREN);
				return result;
			}
			else
				this->error();

			return 0;
		}

		double term(){
			double result = double(this->factor());

			Token * token;
			while(this->current_token->type == MUL || this->current_token->type == DIV){
				token = this->current_token;
				if (token->type == MUL)
				{
					this->eat(MUL);
					result = result * double(this->factor());
				}
				else if (token->type == DIV){
					this->eat(DIV);
					result = result / double(this->factor());
				}
			}

			return result;
		}

		double expr(){
			double result = this->term();

			Token * token; 
			while(this->current_token->type == PLUS || this->current_token->type == MINUS){
				token = this->current_token;
				if (token->type == PLUS){
					this->eat(PLUS);
					result = result + this->term();
				}
				else if (token->type == MINUS){
					this->eat(MINUS);
					result = result - this->term();
				}
			}

			return result;
		}

	private :
		Token * current_token;
		Lexer * lexer;
};