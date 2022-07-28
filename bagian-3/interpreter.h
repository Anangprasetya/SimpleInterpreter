class Interpreter {
	public :
		Interpreter(string text){
			this->text = text;
			this->pos = 0;
			this->current_token = NULL;
			this->errortmp = NULL;
			this->current_char = new charMy(this->text[this->pos]);

		}
		/*
		##########################################################
    	# Lexer code                                             #
    	##########################################################
    	*/

		void error(){
			this->errortmp = new Error("Error parsing input");
		}

		Error * getError(){
			return this->errortmp;
		}

		void advance(){
			this->pos += 1;
			if (this->pos > this->text.length() - 1)
				this->current_char = NULL;
			else
				this->current_char = new charMy(this->text[this->pos]);	
		}

		void skip_whitespace(){
			while(this->current_char != NULL && this->current_char->val == ' ')
				this->advance();
		}

		int integer(){
			string result = "";
			while(this->current_char != NULL && this->current_char->val >= '0' && this->current_char->val <= '9'){
				result += this->current_char->val;
				this->advance();
			}

			return chartoInt(result);
		}

		Token * get_next_token(){
			while(this->current_char != NULL){
				if (this->current_char->val == ' ')
				{
					this->skip_whitespace();
					continue;
				}

				if (this->current_char->val >= '0' && this->current_char->val <= '9')
				{
					Token * token = new Token(INTEGER, this->integer());
					return token;
				}

				if (this->current_char->val == '+')
				{
					this->advance();
					Token * token = new Token(PLUS, 0);
					return token;
				}

				if (this->current_char->val == '-')
				{
					this->advance();
					Token * token = new Token(MINUS, 0);
					return token;
				}

				this->error();
				break;
			}

			Token * token = new Token(EOFMY, 0);
			return token;
		}

		/*
		##########################################################
    	# Parser / Interpreter code                              #
    	##########################################################
    	*/

    	int term(){
    		Token * token = this->current_token;
    		this->eat(INTEGER);
    		return token->value;
    	}

		int expr(){
			this->current_token = this->get_next_token();

			int result = this->term();
			while(this->current_token->type == PLUS || this->current_token->type == MINUS){
				Token * token = this->current_token;
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

		void eat(string token_type){
			if (this->current_token != NULL){
				if (this->current_token->type == token_type)
					this->current_token = this->get_next_token();
				else
					this->error();
			}
		}

	private :
		string text;
		int pos;
		Token * current_token;
		charMy * current_char;
		Error * errortmp;
};