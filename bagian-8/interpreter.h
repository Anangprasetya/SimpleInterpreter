class Interpreter {
	public :
		Interpreter(Parser * parser){
			this->parser = parser;
		}

		double interpret(){
			this->tree = this->parser->parse();
			return this->visit(this->tree);
		}

	private :
		Parser * parser;
		BinOPNumMerge * tree;

		double visit(BinOPNumMerge * node){
			if(node->num != NULL){
				return this->visit_Num(node);
			}
			else if (node->binop != NULL){
				return this->visit_BinOp(node);
			}
			else if (node->unaryop != NULL){
				return this->visit_UnaryOp(node);
			}

			return 0.00;
		}

		double visit_Num(BinOPNumMerge * node){
			return double(node->num->value);
		}

		double visit_BinOp(BinOPNumMerge * node){
			if(node->binop->op->type == PLUS){
				return this->visit(node->binop->left) + this->visit(node->binop->right);
			}
			else if(node->binop->op->type == MINUS){
				return this->visit(node->binop->left) - this->visit(node->binop->right);
			}
			else if(node->binop->op->type == MUL){
				return this->visit(node->binop->left) * this->visit(node->binop->right);
			}
			else if(node->binop->op->type == DIV){
				return this->visit(node->binop->left) / this->visit(node->binop->right);
			}

			return 0.0;
		}

		double visit_UnaryOp(BinOPNumMerge * node){
			string op = node->unaryop->op->type;
			if (op == PLUS)
				return 0.00 + this->visit(node->unaryop->expr);
			else if (op == MINUS)
				return -1 * this->visit(node->unaryop->expr);

			return 0.0;
		}
};