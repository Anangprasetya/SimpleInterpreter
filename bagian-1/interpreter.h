class Interpreter {
	public :
		Interpreter(string text){
			this->text = text;
			this->pos = 0;
			this->current_token = NULL;
			this->errortmp = NULL;

		}

		void error(){
			this->errortmp = new Error("Error parsing input");
		}

		Error * getError(){
			return this->errortmp;
		}

		Token * get_next_token(){
			string text = this->text;

			if (this->pos > text.length() - 1){
				Token * token;
				token = new Token(EOFMY, 0);
				return token;
			}

			char current_char = text[this->pos];

			if (current_char >= '0' && current_char <= '9')
			{
				Token * token;
				token = new Token(INTEGER, chartoInt(current_char));
				this->pos += 1;
				return token;
			}

			if (current_char == '+')
			{
				Token * token;
				token = new Token(PLUS, 0);
				this->pos += 1;
				return token;
			}

			this->error();

			return NULL;
		}

		int expr(){
			this->current_token = this->get_next_token();

			Token * left = this->current_token;
			this->eat(INTEGER);

			Token * op = this->current_token;
			this->eat(PLUS);

			Token * right = this->current_token;
			this->eat(INTEGER);

			if (this->current_token != NULL){
				int result = left->value + right->value;
				return result;
			}
			else
				return 0;
		
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
		Error * errortmp;
};