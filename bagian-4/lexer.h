class Lexer {
	public :
		Lexer(string text){
			this->text = text;
			this->pos = 0;
			this->current_char = new charMy(this->text[this->pos]);
		}

		void error(){
			throw Error("Invalid character");
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

				if (this->current_char->val == '*')
				{
					this->advance();
					Token * token = new Token(MUL, 0);
					return token;
				}

				if (this->current_char->val == '/')
				{
					this->advance();
					Token * token = new Token(DIV, 0);
					return token;
				}

				this->error();
				break;
			}

			Token * token = new Token(EOFMY, 0);
			return token;
		}

	private :
		string text;
		int pos;
		charMy * current_char;
};