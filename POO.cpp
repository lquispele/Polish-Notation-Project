//este es mi primer commit
//14/06/2025
//16/06/2025

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

enum Error_code {success, fail};
enum Token_type {operand, unaryop, binaryop};

typedef double Value;
class Expression
{
    public:
        Expression();
        Expression(const Expression &original);
        Error_code evalute_prefix(Value &result);
        Error_code get_token(Token &result);
        void put_token(const Token &next);
        Expression infix_to_prefix(Value &result);
        Error_code valid_infix();

        /*void read();
        void clear();
        void write ();
        int size();
        void rewind();
        Token Expression::get_token();
        //se anadiran mas metodos*/
    private:
        vector<Token> terms;
        int current_term;
        Error_code recursive_evaluate(const Token &first_token, Value &result, Token &final_token);
};

class Token
{
    public:
        Token() {}
        Token (const string &x);
        Token_type kind() const;
        int priority() const;
        double value() const;


        /*string name() const;
        int code_number() const;
        static void set_parameters();
        static void print_parameters();
        static void set_x(double x_val);*/
    
    private:

        /*int code;
        static Lexicon symbol_table;
        static List<int> parameters;*/
};

int main ()
{
    cout << "Hello world" << "\n";

    //Solicita al usuario la expresion infija
    //Funcion que cambia la expresion de infija a prefija 

    //introduccion();
    Expression infix;
    Expression prefix;
    //Plot graph; <- todavia en desarrollo
    //char ch;

    //while ((ch = get_command()) != 'q') do_command(ch, infix, prefix, graph);

    return 0;
}

//Error_code Expression::evaluate_prefix(Value &result)