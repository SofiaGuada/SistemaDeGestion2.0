# include<iostream>
#include "MenuCliente.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

MenuCliente::MenuCliente()
{
   _cantidadOpciones=7;
}

void MenuCliente::mostrar(){
   int opcion;
   do{
    system("cls");
    opcion=seleccionarOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");

   }while (opcion!=0);

}
void MenuCliente::mostrarOpciones(){
   setColor(LIGHTCYAN);
   cout<<"============================="<<endl;
   cout<<"      MENU CLIENTES     "<<endl;
   cout<<"============================="<<endl;
   setColor(WHITE);
   cout<<"1. CARGAR CLIENTE"<<endl;
   cout<<"2. MOSTRAR CLIENTE "<<endl;
   cout<<"3. BUSCAR CLIENTE "<<endl;
   cout<<"4. MODIFICAR CLIENTE "<<endl;
   cout<<"5. ORDENADO ALFABETICAMENTE "<<endl;
   cout<<"6. ELIMINAR "<<endl;
   cout<<"7. VOLVER A ACTIVAR CLIENTE "<<endl;
   setColor(LIGHTCYAN);
   cout<<"-----------------------------"<<endl;
   setColor(WHITE);
   cout<<"0. SALIR "<<endl;

}
int MenuCliente::seleccionarOpcion(){
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
    setColor(WHITE);
       cout<<"OPCION: ";
       cin>>opcion;
   }
   return opcion;
}


void MenuCliente::ejecutarOpcion(int opcion){
    switch(opcion){
case 1:
    _managerCliente.CargarCliente();
    break;
 case 2:
     _managerCliente.ListarClientes();
    break;
case 3:
    _managerCliente.buscarClientes();
    break;
case 4:
    _managerCliente.modificarClientes();
    break;
case 5:
    _managerCliente.ordanadosAlfabeticamente();
    break;
case 6:
    system("cls");
    _managerCliente.eliminar();
    break;
case 7:
    _managerCliente.ActivarCliente();
    break;
case 0:
    cout<<"----------------------------------"<<endl;
    break;
    default:
        setColor(LIGHTRED);
        cout<<"INGRESASTE UNA OPCION INVALIDA, VUELVE A INTENTARLO!"<<endl;
        setColor(WHITE);
    break;
    }
}
