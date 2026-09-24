# include<iostream>
#include <conio.h>
#include <cstdlib> // atoi
#include "Necesario.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

std::string cargarCadena(){
  std::string texto;
  if(std::cin.peek() == '\n'){
    std::cin.ignore();
  }
  std::getline(std::cin, texto);
  return texto;
}

bool Valido(const string& nombre) {
    if (nombre.empty()) return false;

    for (char c : nombre) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool ValidoDescripcion(const string& texto) {
    if (texto.empty()) return false;

    for (char c : texto) {
        if (!isalnum(c) &&
            c != ' ' &&
            c != '.' &&
            c != ',' &&
            c != '-' &&
            c != '(' &&
            c != ')' &&
            c != '/') {
            return false;
        }
    }
    return true;
}

void mostrarError(const string& mensaje, int linea) {
    gotoxy(1, linea);
    cout << "                                        ";
    gotoxy(1, linea);
    setColor(RED);
    cout << mensaje;
    setColor(WHITE);
    cout<<endl;
}


int cargarEntero(int x, int y, int lineaError) {
    char cad[20];
    int i = 0;
    char c;
    bool errorMostrado = false;

    while (true) {
        c = getch();

        if (c >= '0' && c <= '9') {
            cad[i++] = c;
            cout << c;
            errorMostrado = false;
        }
        else if (c == 8) {
            if (i > 0) {
                i--;
                cout << "\b \b";
            }
        }
        else if (c == 13) {
            if (i == 0) {
                mostrarError("Debe ingresar un numero", lineaError);
                gotoxy(x, y);
                continue;
            }
            cad[i] = '\0';
            mostrarError("", lineaError);
            return atoi(cad);
        }
        else {
            if (!errorMostrado) {
                mostrarError("Solo numeros", lineaError);
                errorMostrado = true;
            }
        }
    }
}

bool emailValido(const string& email) {
    if (email.empty()) return false;

    int arrobas = 0;
    int posArroba = -1;
    int posPunto = -1;

    for (int i = 0; i < email.size(); i++) {
        char c = email[i];
        // Verificar caracteres permitidos
        if (!isalnum(c) && c != '@' && c != '.' && c != '_' && c != '-') {
            return false;
        }
        if (c == '@') {
            arrobas++;
            posArroba = i;
        }
        if (c == '.') {
            posPunto = i;
        }
    }
    // Debe haber un solo @
    if (arrobas != 1) return false;
    // Debe haber texto antes del @
    if (posArroba == 0) return false;
    // Debe haber un punto después del @
    if (posPunto < posArroba + 2) return false;
    // Debe haber texto después del punto
    if (posPunto == email.size() - 1) return false;
    return true;
}
