#include <iostream>
#include "MenuEventoServicios.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

MenuEventoServicios::MenuEventoServicios()
{
  _cantidadOpciones=8;
}

void MenuEventoServicios::mostrar(){
 int opcion;

   do{
    system("cls");
    opcion=seleccionarOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");

   }while (opcion!=0);
}

void MenuEventoServicios::mostrarOpciones(){
   setColor(LIGHTCYAN);
   cout<<"==============================="<<endl;
   cout<<"    MENU SERVICIOS ASOCIADOS   "<<endl;
   cout<<"==============================="<<endl;
   setColor(WHITE);
   cout<<"1. CARGAR EVENTOS Y SERVICIOS "<<endl;
   cout<<"2. MOSTRAR EVENTOS Y SERVICIOS"<<endl;
   cout<<"3. BUSCAR EVENTOS Y SERVICIOS "<<endl;
   cout<<"4. MODIFICAR EVENTO Y SERVICIOS"<<endl;
   cout<<"5. ELIMINAR "<<endl;
   cout<<"6. ACTIVAR EVENTO-SERVICIOS "<<endl;
   cout<<"7. SERVICIOS "<<endl;
   cout<<"8. SERVICIOS MAS CONTRATADOS "<<endl;
   setColor(LIGHTCYAN);
   cout<<"-------------------------------"<<endl;
   setColor(WHITE);
   cout<<"0. SALIR "<<endl;
}

int MenuEventoServicios::seleccionarOpcion(){
   int opcion;
   mostrarOpciones();
   setColor(LIGHTCYAN);
   cout<<"==============================="<<endl;
   setColor(WHITE);
   cout<<"OPCION: ";
   cin>>opcion;

   while(opcion<0|| opcion>_cantidadOpciones){
    cout<<"OPCION INCORRECTA...."<<endl;
       cout<<"OPCION: ";
       cin>>opcion;

   }
   return opcion;
}

void MenuEventoServicios::ejecutarOpcion(int opcion){
switch(opcion){
case 1:
    _managerEventoServicios.cargarEventosyServicios();
    break;
 case 2:
    _managerEventoServicios.listarEventoyServicios();
    break;
case 3:
   _managerEventoServicios.buscarIdEventoServicios();
    break;
case 4:
    _managerEventoServicios.modificarEventoyServicio();
    break;
case 5:
    _managerEventoServicios.eliminar();
    break;
case 6:
    _managerEventoServicios.Activar();
    break;
case 7:
    _managerServicios.menuServicios();
    break;
case 8:
    _managerEventoServicios.serviciosMasContratados();
    break;
case 0:
  return;
default:
    break;
    }
}
