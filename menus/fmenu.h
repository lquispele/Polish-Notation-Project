#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#define ARRIBA 65
#define ABAJO 66
#define ENTER 10
char* Prefija(const char*, char* );
char* Postfija(const char*, char* );
double operaPos(const char*);
double operaPre(const char*);

void mostrar_menu();
int getch();
#endif
