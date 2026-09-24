# include<iostream>
#include "MenuPagos.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

MenuPagos::MenuPagos()
{
   _cantOpciones=10;
}

void MenuPagos::mostrar(){
   int opcion;

   do{
    system("cls");
    opcion=seleccionarOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");

   }while (opcion!=0);
}
void MenuPagos::mostrarOpciones(){
   setColor(LIGHTCYAN);
   cout<<"==========================="<<endl;
   cout<<"     MENU PAGOS    "<<endl;
   cout<<"==========================="<<endl;
   setColor(WHITE);
   cout<<" 1. CARGAR PAGOS"<<endl;
   cout<<" 2. MOSTRAR PAGOS "<<endl;
   cout<<" 3. BUSCAR PAGOS "<<endl;
   cout<<" 4. MODIFICAR PAGOS "<<endl;
   cout<<" 5. ELIMINAR "<<endl;
   cout<<" 6. ACTIVAR "<<endl;
   cout<<" 7. DETALLE DE PAGO "<<endl;
   cout<<" 8. REPORTES "<<endl;
   cout<<" 9. ESTADOS DE PAGOS "<<endl;
   setColor(LIGHTCYAN);
   cout<<"---------------------------"<<endl;
   setColor(WHITE);
   cout<<" 0. SALIR "<<endl;

}
int MenuPagos::seleccionarOpcion(){
    int opcion;
   mostrarOpciones();
   setColor(LIGHTCYAN);
   cout<<"==========================="<<endl;
   setColor(WHITE);
   cout<<"OPCION: ";
   cin>>opcion;

   while(opcion<0|| opcion>_cantOpciones){
    cout<<"OPCION INCORRECTA...."<<endl;
       cout<<"OPCION: ";
       cin>>opcion;

   }
   return opcion;

}
void MenuPagos::ejecutarOpcion(int opcion){
    switch(opcion){
case 1:
    _managerPagos.cargarPagos();
    break;
 case 2:
     _managerPagos.listarPagos();
    break;
case 3:
    _managerPagos.buscar();
    break;

case 4:
    _managerPagos.modificarPago();
    break;
case 5:
    _managerPagos.eliminar();
    break;
case 6:
    _managerPagos.Activar();
    break;
case 7:
    _detallePago.mostrarDetallePagos();
    break;
case 8:
    _managerPagos.submenuPago();
    break;
case 9:
    _managerPagos.mostrarPagosxEstados();
    break;
case 0:
//    break;
return;
default:
    cout<<"OPCION INCORRECTA, VOLVE A INTENTAR "<<endl;
    break;
    }
}

