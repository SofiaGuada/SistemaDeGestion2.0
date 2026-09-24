#include <iostream>
#include "MenuEventos.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

MenuEventos::MenuEventos()
{
    _cantidadOpciones=10;
}

void MenuEventos::mostrar(){
   int opcion;
//setBackgroundColor(LIGHTRED);
   do{
    system("cls");
    opcion=seleccionarOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");

   }while (opcion!=0);
}

void MenuEventos::mostrarOpciones(){
   setColor(LIGHTCYAN);
   cout<<"============================="<<endl;
   cout<<"     MENU EVENTOS  "<<endl;
   cout<<"============================="<<endl;
   setColor(WHITE);
   cout<<"  1. CARGAR EVENTOS"<<endl;
   cout<<"  2. MOSTRAR EVENTOS "<<endl;
   cout<<"  3. BUSCAR EVENTOS "<<endl;
   cout<<"  4. MODIFICAR EVENTO "<<endl;
   cout<<"  5. ORDENADOS POR MES "<<endl;
   cout<<"  6. EVENTOS Y SERVICIOS "<<endl;
   cout<<"  7. MOSTRAR EVENTOS MAS FRECUENTES "<<endl;
   cout<<"  8. ELIMINAR "<<endl;
   cout<<"  9. ACTIVAR EVENTO "<<endl;
   cout<<"  10. CANCELAR / ACTIVAR EVENTO "<<endl;
   setColor(LIGHTCYAN);
   cout<<"------------------------------"<<endl;
   setColor(WHITE);
   cout<<"  0. SALIR "<<endl;
}

int MenuEventos::seleccionarOpcion(){
    int opcion;
   mostrarOpciones();
   setColor(LIGHTCYAN);
   cout<<"============================="<<endl;
   setColor(WHITE);
   cout<<"OPCION: ";
   cin>>opcion;

   while(opcion<0|| opcion>_cantidadOpciones){
    setColor(RED);
    cout<<"OPCION INCORRECTA...."<<endl;
    anykey();
    setColor(WHITE);
       cout<<"OPCION: ";
       cin>>opcion;
   }
   return opcion;

}
void MenuEventos::ejecutarOpcion(int opcion){
    switch(opcion){
case 1:
//    system("cls");
    _managerEventos.cargarEvento();
    break;
 case 2:
//    system("cls");
     _managerEventos.listarEvento();
    break;
case 3:
//    system("cls");
    _managerEventos.buscar();
    break;
case 4:
//    system("cls");
    _managerEventos.modificarEvento();
    break;
case 5:
//    system("cls");
    _managerEventos.ordanadosPorFecha();
    break;
case 6:
//    system("cls");
    _menuEventoServicios.mostrar();
    break;
case 7:
    _managerEventos.eventosPorTipo();
    break;
case 8:
//    system("cls");
    _managerEventos.eliminar();
    break;
case 9:
//    system("cls");
    _managerEventos.ActivarEvento();
    break;
case 10:
    _managerEventos.submenuCancelarActivar();
    break;
case 0:
//    setBackgroundColor(YELLOW);
//    break;
return ;
    }
}
