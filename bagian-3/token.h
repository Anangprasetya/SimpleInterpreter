class Token 
{
    public:
        Token(string type = "", double value = 0.00)
        {
            this->type = type;
            this->value = value;
        }

        void print(){
            cout << "Token(" << this->type << ", " << this->value << ")\n";
        }

        string type;
        double value;
};