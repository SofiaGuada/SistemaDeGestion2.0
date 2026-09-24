#include <iostream>
#include "rlutil.h"
#include "App.h"
using namespace std;
using namespace rlutil;

App::App(){
  _cantidadOpciones = 3;
}
void App::run(){
  int opcion;

  do{
    system("cls");
    opcion = seleccionOpcion();
    system("cls");
    ejecutarOpcion(opcion);
  }while(opcion != 0);
}

void App::mostrarOpciones(){
    setColor(GREY);
    setColor(LIGHTMAGENTA);
    cout<< "============================"<<endl;
    setColor(YELLOW);
    cout<< "|    GESTION DE EVENTOS    |"<<endl;
    setColor(LIGHTMAGENTA);
    cout<< "============================"<<endl;
    setColor(YELLOW);
    cout<< "|  1- CLIENTES             |"<<endl;
    cout<< "|  2- EVENTOS              |"<<endl;
    cout<< "|  3- PAGOS                |"<<endl;
    setColor(LIGHTMAGENTA);
    cout<< "----------------------------"<<endl;
    setColor(YELLOW);
    cout<< "|  0- SALIR                |"<<endl;
    setColor(LIGHTMAGENTA);
    cout<< "============================"<<endl;
    setColor(YELLOW);

}

int App::seleccionOpcion(){
  int opcion;
  mostrarOpciones();
  cout << "OPCION: ";
  cin >> opcion;

  while(opcion < 0 || opcion > _cantidadOpciones){
    setColor(RED);
    cout << "OPCION INCORRECTA ..."<<endl;
    anykey();
    setColor(LIGHTCYAN);
    cout << "OPCION: ";
    cin >> opcion;
  }
  setColor(WHITE);
  return opcion;
}

void App::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
      _menuCliente.mostrar();
  break;
  case 2:
      _menuEvento.mostrar();
    break;
  case 3:
     _menuPagos.mostrar();
    break;
  case 0:
    setColor(BROWN);
    locate(4,2);
    cout << "GRACIAS POR UTILIZAR APP DE ORGANIZACIÓN :) " << endl;
    break;
  }
}
