class Error : public invalid_argument{
	public :
		explicit Error(const string& what_arg) : invalid_argument( what_arg ){
			
		}
};