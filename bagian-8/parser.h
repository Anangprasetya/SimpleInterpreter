class BinOPNumMerge;

class BinOp {
	public :
		BinOp(BinOPNumMerge * left, Token * op, BinOPNumMerge * right){
			this->left = left;
			this->op = op;
			this->token = this->op;
			this->right = right;
		}

		BinOPNumMerge * left,  * right;
		Token * op, * token;
};

class Num {
	public :
		Num(Token * token){
			this->token = token;
			this->value = token->value;
		}

		Token * token;
		double value;
};

class UnaryOP {
	public :
		UnaryOP(Token * op, BinOPNumMerge * expr){
			this->op = op;
			this->token = this->op;
			this->expr = expr;
		}

		Token * token, * op;
		BinOPNumMerge * expr;
};

class BinOPNumMerge {
	public :
		BinOPNumMerge(BinOp * binop = NULL, Num * num = NULL){
			this->binop = binop;
			this->num = num;
			this->unaryop = NULL;
		}

		void addUnary(UnaryOP * unaryop){
			this->unaryop = unaryop;
		}

		BinOp * binop;
		Num * num;
		UnaryOP * unaryop;
};

class Parser {
	public :
		Parser(Lexer * lexer){
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

		BinOPNumMerge * factor(){

			Token * token = this->current_token;
			BinOPNumMerge * bnmerge;

			if (token->type == PLUS)
			{
				this->eat(PLUS);
				UnaryOP * un = new UnaryOP(token, this->factor());
				bnmerge = new BinOPNumMerge();
				bnmerge->addUnary(un);
				return bnmerge;
			}

			else if (token->type == MINUS)
			{
				this->eat(MINUS);
				UnaryOP * un = new UnaryOP(token, this->factor());
				bnmerge = new BinOPNumMerge();
				bnmerge->addUnary(un);
				return bnmerge;
			}

			else if (token->type == INTEGER)
			{
				this->eat(INTEGER);
				Num * num = new Num(token);
				bnmerge = new BinOPNumMerge(NULL, num);
				return bnmerge;
			}
			else if (token->type == LPAREN){
				this->eat(LPAREN);
				bnmerge = this->expr();
				this->eat(RPAREN);
				return bnmerge;
			}
			else
				this->error();

			return 0;
		}

		BinOPNumMerge * term(){
			BinOPNumMerge * node;
			node = this->factor();

			Token * token;
			while(this->current_token->type == MUL || this->current_token->type == DIV){
				token = this->current_token;
				if (token->type == MUL)
					this->eat(MUL);
				else if (token->type == DIV)
					this->eat(DIV);

				BinOp * bnop = new BinOp(node, token, this->factor());
				node = new BinOPNumMerge(bnop);
			}

			return node;
		}

		BinOPNumMerge * expr(){
			BinOPNumMerge * node;
			node = this->term();

			Token * token;
			while(this->current_token->type == PLUS || this->current_token->type == MINUS){
				token = this->current_token;
				if (token->type == PLUS)
					this->eat(PLUS);
				else if (token->type == MINUS)
					this->eat(MINUS);

				BinOp * bnop = new BinOp(node, token, this->term());
				node = new BinOPNumMerge(bnop);
			}

			return node;
		}

		BinOPNumMerge * parse(){
			return this->expr();
		}

		Lexer * lexer;
		Token * current_token;
};