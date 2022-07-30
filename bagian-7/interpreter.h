class Interpreter {
	public :
		Interpreter(Parser * parser){
			this->parser = parser;
		}

		double interpret(){
			this->tree = this->parser->parse();
			return this->parseTree(this->tree);
		}

	private :
		Parser * parser;
		BinOPNumMerge * tree;

		double parseTree(BinOPNumMerge * node){
			if(node->num != NULL){
				return double(node->num->value);
			}
			else{
				if(node->binop->op->type == PLUS){
					return this->parseTree(node->binop->left) + this->parseTree(node->binop->right);
				}
				else if(node->binop->op->type == MINUS){
					return this->parseTree(node->binop->left) - this->parseTree(node->binop->right);
				}
				else if(node->binop->op->type == MUL){
					return this->parseTree(node->binop->left) * this->parseTree(node->binop->right);
				}
				else if(node->binop->op->type == DIV){
					return this->parseTree(node->binop->left) / this->parseTree(node->binop->right);
				}
				else
					this->parser->error();

				return 0;
			}
		}
};