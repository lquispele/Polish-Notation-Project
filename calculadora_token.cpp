#include "menus/fmenu.h"

using namespace std;

#define COLOR_RESET     "\033[0m"
#define COLOR_SELECTED  "\033[1;97;44m"  
#define COLOR_NORMAL    "\033[0;37m"
#define MAX 100
char* PostfijaTokens(char tokens[][MAX], int ntokens, char* epos);
char* PrefijaTokens(char tokens[][MAX], int ntokens, char* epre);
void tokenizar(const char* expr, char tokens[][MAX], int& ntokens);
double operaPosTokens(char tokens[][MAX], int ntokens);
int ntokens = 0;

char pila[MAX]; 
struct menu {
    string opcion;
    menu* sig;
};

menu* crear_opcion(string op) {
    menu* nueva_opcion = new menu;
    nueva_opcion->opcion = op;
    nueva_opcion->sig = nullptr;
    return nueva_opcion;
}

int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void vermenu(menu* cabeza, int seleccion) {
    int i = 0;
    menu* actual_op = cabeza;
    const int ancho = 60;
    system("clear");
    cout << "\n\t";
    for (int i = 0; i < ancho; i++){
        cout << "-";
    }
    cout << "\n\t|  MENU DE OPERACIONES COMBINADAS: POSTFIJA Y PREFIJA       |\n\t";
    for (int i = 0; i < ancho; i++){
        cout << "-";
    }
    cout << "\n";
    do {
        cout << "\t| ";
        if (i == seleccion) {
            cout << COLOR_SELECTED << "> " << actual_op->opcion << COLOR_RESET;
        } else {
            cout << "  " << actual_op->opcion;
        }

        int espacios = ancho - 4 - actual_op->opcion.length(); // -4: "| ", "> ", " |"
        for (int j = 0; j < espacios; j++) cout << " ";
        cout << "|\n";

        actual_op = actual_op->sig;
        i++;
    } while (actual_op != cabeza);

    cout << "\t";
    for (int i = 0; i < ancho; i++)
    {
        cout << "-";
    }
    cout << "\n\tUsa las flechas para moverte y ENTER para seleccionar.\n";
}

int items(menu* inicio) {
    int i = 0;
    menu* actual = inicio;
    do {
        i++;
        actual = actual->sig;
    } while (actual != inicio);
    return i;
}

void mostrar_menu() {
    int ntokensPost = 0;
    int resultado;
    system("clear");
    char expresion[MAX]={};
    menu* op1 = crear_opcion("Ingrese la operacion combinada(Infija o normal)");
    menu* op2 = crear_opcion("Mostrar la operacion en Postfija");
    menu* op3 = crear_opcion("Mostrar la operacion en Prefija");
    menu* op4 = crear_opcion("Salir");
    menu* op5 = crear_opcion("Evaluar expresion en Postfija");
    menu* op6 = crear_opcion("Evaluar expresion en Prefija");


    op1->sig = op2;
    op2->sig = op3;
    op3->sig = op4;
    op4->sig = op5;
    op5->sig = op6;
    op6->sig = op1;


    int seleccion = 0;
    int total = items(op1);

    while (true) {
        system("clear");
        vermenu(op1, seleccion);

        int tecla = getch();
        if (tecla == 27) {
            if (getch() == 91) {
                int direccion = getch();
                if (direccion == ARRIBA && seleccion > 0) {
                    seleccion--;
                } else if (direccion == ABAJO) {
                    seleccion = (seleccion + 1) % total;
                }
            }
        } else if (tecla == ENTER) {
            switch (seleccion) {
                case 0:
                    system("clear");
                    
                    
                    cout << "Ingrese una expresion infija :\n> ";
                    
                    cin.getline(expresion, MAX);
                    char tokens[100][MAX];
                        ntokens = 0;
                        tokenizar(expresion, tokens, ntokens);

                        // Mostrar tokens al usuario
                        cout << "\nTokens detectados:\n";
                        for (int i = 0; i < ntokens; i++) {
                            cout << "[" << tokens[i] << "] ";
                        }
                        cout << endl;

                    if (cin.fail()) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "La expresion ingresada es demasiado larga.\nMáximo permitido: [" << MAX - 1 << "] caracteres.\n";
                    system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                    cin.get();
                    cin.clear();
                    break;
                    }
                    system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                    break;
                case 1:
                    system("clear");
                    if(strlen(expresion)==0){
                        cout<<"No hay datos para procesar"<<endl;
                        cout<<"Ingrese los datos en la opcion 1 del menu.\n"<<flush;
                        system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                        break;
                    }
                    if (!parentesis_balanceados(tokens, ntokens)) {
                        cout << "\nError: Paréntesis no balanceados.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    if (!sintaxis_valida(tokens, ntokens)) {
                        cout << "\nError: Sintaxis inválida en la expresión.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    char postfija[MAX];
                    cout << "Ejecutando: Mostrar en Postfija\n";
                    Postfija(expresion, postfija);
                    cout << "\nPostfija: " << postfija << endl;
                    system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                    break;
                case 2:
                    system("clear");
                    if(strlen(expresion)==0){
                        cout<<"No hay datos para procesar"<<endl;
                        cout<<"Ingrese los datos en la opcion 1 del menu.\n"<<flush;
                        system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                        break;
                    }
                    char prefija[100];
                    cout << "Ejecutando: Mostrar en Prefija\n";
                    Prefija(expresion, prefija);
                    cout << "\nPrefija: " << prefija << endl;
                    system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                    break;
                case 3:
                    system("clear");
                    cout << "Saliendo...\n";
                    sleep(1);
                    return;
                case 4:
                    system("clear");
                    if (strlen(expresion) == 0) {
                        cout << "No hay datos para procesar\n";
                        cout << "Ingrese los datos en la opcion 1 del menu.\n";
                        system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                        break;
                    }
                    if (!parentesis_balanceados(tokens, ntokens)) {
                        cout << "\nError: Paréntesis no balanceados.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    if (!sintaxis_valida(tokens, ntokens)) {
                        cout << "\nError: Sintaxis inválida en la expresión.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    char epos[100];
                        char tokensPost[100][MAX];
                        ntokensPost = 0;

                        PostfijaTokens(tokens, ntokens, epos);
                        tokenizar(epos, tokensPost, ntokensPost);  // Tokenizamos la postfija
                        resultado = operaPosTokens(tokensPost, ntokensPost);

                        cout << "Expresion Postfija: " << epos << endl;
                        cout << "Resultado: " << resultado << endl;
                        system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                        break;
                case 5:
                system("clear");
                    if (strlen(expresion) == 0) {
                        cout << "No hay datos para procesar\n";
                        cout << "Ingrese los datos en la opcion 1 del menu.\n";
                        system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                        break;
                    }
                    if (!parentesis_balanceados(tokens, ntokens)) {
                        cout << "\nError: Paréntesis no balanceados.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    if (!sintaxis_valida(tokens, ntokens)) {
                        cout << "\nError: Sintaxis inválida en la expresión.\n";
                        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        break;
                    }

                    char epref[100];
                    PrefijaTokens(tokens, ntokens, epref);                      cout << "Expresion Prefija: " << epref << endl;
                    resultado = operaPre(epref);
                    cout << "Resultado: " << resultado << endl;
                    system("read -n 1 -s -p \"Presiona cualquier tecla para continuar...\"");
                    break;
                default:
                    system("clear");
                    cout << "Opción inválida\n";
                    system("read -n 1 -s -p \"Presiona cualquier teclara para continuar y elija la opcion correcta porfavor.\"");
                    break;
            }
        }
        system("clear");
            
    }
}
//FUNCIONES PARA POST FIJA 
bool operando(char c) {
    return isalpha(c) || isdigit(c);
}


int prioridad(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int strlength(const char* s) {
    return strlen(s);
}

char* Postfija(const char* ei, char* epos) {
    int tope = 0;
    int n = strlength(ei);
    int i = -1, j = 0;

    while (j <= n) {
        if (ei[j] == '(') {
            tope++;
            pila[tope] = ei[j];
        } 
        else if (ei[j] == ')') {
            while (pila[tope] != '(') {
                i++;
                epos[i] = pila[tope];
                tope--;
            }
            tope--;
        } else if (operando(ei[j])) {  
            i++;
            epos[i] = ei[j];
        } 
        else {
            while (tope > 0 && prioridad(ei[j]) <= prioridad(pila[tope])) {
                i++;
                epos[i] = pila[tope];
                tope--;
            }
            tope++;
            pila[tope] = ei[j];
        }
        j++;
    }

    while (tope > 0) {
        i++;
        epos[i] = pila[tope];
        tope--;
    }

    return epos;
}
//FUNCIONES PARA PRE FIJA
char* Prefija(const char* ei, char* epre) {
    char pila[MAX];
    int k, n, tope, i;

    tope = -1;
    n = strlen(ei);
    i = -1;

    for (k = n - 1; k >= 0; k--) {
        if (ei[k] == ')') {
            tope++;
            pila[tope] = ei[k];
        } else if (ei[k] == '(') {
            while (tope >= 0 && pila[tope] != ')') {
                i++;
                epre[i] = pila[tope];
                tope--;
            }
            tope--; 
        } else if (prioridad(ei[k]) == 0) {
            i++;
            epre[i] = ei[k];
        } else {
            while (tope > -1 && prioridad(ei[k]) < prioridad(pila[tope])) {
                i++;
                epre[i] = pila[tope];
                tope--;
            }
            tope++;
            pila[tope] = ei[k];
        }
    }

    while (tope > -1) {
        i++;
        epre[i] = pila[tope];
        tope--;
    }

    tope = -1;
    for (k = 0; k <= i; k++) {
        tope++;
        pila[tope] = epre[k];
    }
    for (k = 0; k <= i; k++) {
        epre[k] = pila[tope];
        tope--;
    }
    epre[i + 1] = '\0'; 
    return epre;
}

int main() {
    system("clear");
    mostrar_menu();
    return 0;
    
}
double operaPre(const char* epre) {
    double pila_eval[MAX];
    int tope = -1;

    char expr[500];
    strcpy(expr, epre);

    char* token = strtok(expr, " ");
    vector<string> v;
    while (token) {
        v.push_back(token);
        token = strtok(nullptr, " ");
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        string t = v[i];
        if (isdigit(t[0]) || (t[0] == '-' && isdigit(t[1]))) {
            pila_eval[++tope] = stod(t);  // ✅ ahora acepta decimales
        } else {
            double op1 = pila_eval[tope--];
            double op2 = pila_eval[tope--];
            double resultado = 0;

            if (t == "+") resultado = op1 + op2;
            else if (t == "-") resultado = op1 - op2;
            else if (t == "*") resultado = op1 * op2;
            else if (t == "/") resultado = op1 / op2;
            else if (t == "^") resultado = pow(op1, op2);
            else {
                cout << "Operador inválido: " << t << endl;
                return 0;
            }

            pila_eval[++tope] = resultado;
        }
    }

    return pila_eval[tope];
}



// Tokenización sin vectores, solo con arreglos de C
void tokenizar(const char* expr, char tokens[][MAX], int& ntokens) {
    ntokens = 0;
    int i = 0, j = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '.') {
            j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                tokens[ntokens][j++] = expr[i++];
            }
            tokens[ntokens][j] = '\0';
            ntokens++;
        } else if (isalpha(expr[i])) {
            j = 0;
            while (isalnum(expr[i])) {
                tokens[ntokens][j++] = expr[i++];
            }
            tokens[ntokens][j] = '\0';
            ntokens++;
        } else if (strchr("+-*/^()", expr[i])) {
            tokens[ntokens][0] = expr[i++];
            tokens[ntokens][1] = '\0';
            ntokens++;
        } else {
            // Caracter no reconocido
            cout << "Error: caracter invalido '" << expr[i] << "'\n";
            return;
        }
    }
}

double operaPosTokens(char tokens[][MAX], int ntokens) {
    double pila[MAX];
    int tope = -1;

    for (int i = 0; i < ntokens; i++) {
        if (isdigit(tokens[i][0]) || (tokens[i][0] == '-' && isdigit(tokens[i][1]))) {
            pila[++tope] = atof(tokens[i]);  // ✅ ahora acepta decimales
        } else {
            double op2 = pila[tope--];
            double op1 = pila[tope--];
            double resultado = 0;

            if (strcmp(tokens[i], "+") == 0) resultado = op1 + op2;
            else if (strcmp(tokens[i], "-") == 0) resultado = op1 - op2;
            else if (strcmp(tokens[i], "*") == 0) resultado = op1 * op2;
            else if (strcmp(tokens[i], "/") == 0) resultado = op1 / op2;
            else if (strcmp(tokens[i], "^") == 0) resultado = pow(op1, op2);

            pila[++tope] = resultado;
        }
    }

    return pila[tope];
}


char* PostfijaTokens(char tokens[][MAX], int ntokens, char* epos) {
    char pilaOp[MAX][MAX];
    int tope = -1;
    epos[0] = '\0'; // iniciar cadena vacía

    for (int i = 0; i < ntokens; i++) {
        if (isdigit(tokens[i][0]) || isalpha(tokens[i][0])) {
            strcat(epos, tokens[i]);
            strcat(epos, " ");
        } else if (strcmp(tokens[i], "(") == 0) {
            strcpy(pilaOp[++tope], tokens[i]);
        } else if (strcmp(tokens[i], ")") == 0) {
            while (tope >= 0 && strcmp(pilaOp[tope], "(") != 0) {
                strcat(epos, pilaOp[tope--]);
                strcat(epos, " ");
            }
            if (tope >= 0) tope--; // eliminar '('
        } else {
            while (tope >= 0 && prioridad(pilaOp[tope][0]) >= prioridad(tokens[i][0])) {
                strcat(epos, pilaOp[tope--]);
                strcat(epos, " ");
            }
            strcpy(pilaOp[++tope], tokens[i]);
        }
    }

    while (tope >= 0) {
        strcat(epos, pilaOp[tope--]);
        strcat(epos, " ");
    }

    return epos;
}

char* PrefijaTokens(char tokens[][MAX], int ntokens, char* epref) {
    char pilaOp[MAX][MAX];
    char salida[MAX][MAX];
    int topeOp = -1;
    int topeSal = -1;

    for (int i = ntokens - 1; i >= 0; i--) {
        if (isdigit(tokens[i][0]) || isalpha(tokens[i][0])) {
            strcpy(salida[++topeSal], tokens[i]);
        } else if (strcmp(tokens[i], ")") == 0) {
            strcpy(pilaOp[++topeOp], tokens[i]);
        } else if (strcmp(tokens[i], "(") == 0) {
            while (topeOp >= 0 && strcmp(pilaOp[topeOp], ")") != 0) {
                strcpy(salida[++topeSal], pilaOp[topeOp--]);
            }
            topeOp--; // quitar ")"
        } else {
            while (topeOp >= 0 && prioridad(tokens[i][0]) < prioridad(pilaOp[topeOp][0])) {
                strcpy(salida[++topeSal], pilaOp[topeOp--]);
            }
            strcpy(pilaOp[++topeOp], tokens[i]);
        }
    }

    while (topeOp >= 0) {
        strcpy(salida[++topeSal], pilaOp[topeOp--]);
    }

    // Construimos epref en orden inverso
    epref[0] = '\0';
    for (int i = topeSal; i >= 0; i--) {
        strcat(epref, salida[i]);
        strcat(epref, " ");
    }

    return epref;
}

bool parentesis_balanceados(char tokens[][MAX], int ntokens) {
    int balance = 0;
    for (int i = 0; i < ntokens; i++) {
        if (strcmp(tokens[i], "(") == 0) balance++;
        else if (strcmp(tokens[i], ")") == 0) balance--;
        if (balance < 0) return false; // se cerró sin abrir
    }
    return balance == 0;
}

bool sintaxis_valida(char tokens[][MAX], int ntokens) {
    for (int i = 0; i < ntokens; i++) {
        // Verificar operador al inicio o fin
        if ((i == 0 || i == ntokens - 1) && strchr("+-*/^", tokens[i][0]))
            return false;

        // Dos operadores seguidos
        if (i > 0 && strchr("+-*/^", tokens[i][0]) && strchr("+-*/^", tokens[i - 1][0]))
            return false;

        // Dos operandos seguidos (sin operador)
        if (i > 0 &&
            (isdigit(tokens[i][0]) || isalpha(tokens[i][0])) &&
            (isdigit(tokens[i - 1][0]) || isalpha(tokens[i - 1][0])))
            return false;
    }
    return true;
}
