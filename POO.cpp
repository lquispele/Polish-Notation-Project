//este es mi primer commit
//14/06/2025

#include <iostream>

using namespace std;

class Expression
{
    public:
        Expression();
        Expression(const Espression &original);
        Error_code evalute_prefix(Value &result);
        Error_code get_token(Token &result);
        void put_token(const Token &next);
        Expression infix_to_prefix(Value &result);
        void read();
        void clear();
        void write ();
        Error_code valid_infix();
        int size();
        void rewind();
        //se anadiran mas metodos
    private:
        List<Token> terms;
        int current_term;
        Error_code recursive_evaluate(const Token &first_token, Value &result, Token &final_token);
};

int main ()
{
    cout << "Hello world" << "\n";

    //Solicita al usuario la expresion infija
    //Funcion que cambia la expresion de infija a prefija 

    //introduccion();
    //Expresion infix;
    //Expresion prefix;
    //Plot graph; <- todavia en desarrollo
    //char ch;

    //while ((ch = get_command()) != 'q') do_command(ch, infix, prefix, graph);

    return 0;
}