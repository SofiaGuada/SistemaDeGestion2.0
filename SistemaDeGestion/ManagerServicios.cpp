#include <iostream>
#include <iomanip>//libreria para usar los decimales
#include "ManagerServicios.h"
#include "Necesario.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

ManagerServicios::ManagerServicios()
{
    //ctor
}

void ManagerServicios::cargarServicios(){
    int idS;
    string nombre,proveedor,descripcion;
    float costo;
    bool eliminado=false;

    idS=_repo.getNuevoIdServicio();

    setColor(LIGHTMAGENTA);
    cout<<"------------------";
    cout<<"----CARGAR SERVICIOS----";
    cout<<"------------------"<<endl;
    setColor(WHITE);

    int cantLinea=3, errorLinea= cantLinea+8;

    gotoxy(1, cantLinea + 1); cout<<"ID SERVICIOS: #"<<idS<<endl;
    gotoxy(1, cantLinea + 2); cout<<"NOMBRE DE SERVICIO: ";
    gotoxy(1, cantLinea + 3); cout<<"DESCRIPCION: ";
    gotoxy(1, cantLinea + 4); cout<<"PROVEEDOR: ";
    gotoxy(1, cantLinea + 5); cout<<"PRECIO: $";

///nombre

    gotoxy(21, cantLinea + 2);
    nombre=cargarCadena();

    while (!Valido(nombre)) {
        mostrarError("ERROR:(solo letras)", errorLinea);
        gotoxy(21, cantLinea + 2);
        cout << "                           ";
        gotoxy(21, cantLinea + 2);
        nombre = cargarCadena();
    }


///descripcion
    gotoxy(13, cantLinea + 3);
    descripcion=cargarCadena();

    while (!ValidoDescripcion(descripcion)){
            mostrarError("ERROR:(solo letras)",errorLinea);
            gotoxy(13, cantLinea + 3);
            cout << "               ";
            gotoxy(13, cantLinea + 3);
            descripcion=cargarCadena();
        }

///proveedor
    gotoxy(11,cantLinea + 4);
    proveedor=cargarCadena();

    while (!Valido(proveedor)){
        mostrarError("ERROR:(solo letras)",errorLinea);
        gotoxy(11, cantLinea+4);
        cout<<"             ";
        gotoxy(11, cantLinea+4);
        proveedor=cargarCadena();
    }
///precio

    while (true){
            gotoxy(11, cantLinea + 5);
            cout << "               ";
            gotoxy(11, cantLinea + 5);
            costo=cargarEntero(11,cantLinea+5,errorLinea);

    if(costo<=0){
        mostrarError("El precio debe ser mayor a 0 ",errorLinea);
        continue;
    }
    break;
  }


    system("pause");
    system ("cls");

    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(YELLOW);
    cout<<"ID: #"<<idS<<endl;
    cout<<"NOMBRE DE SERVICIO: "<<nombre<<endl;
    cout<<"DESCRIPCION: "<<descripcion<<endl;
    cout<<"PROVEEDOR: "<<proveedor<<endl;
    cout<<"PRECIO: $"<<costo<<endl;
    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;


  int opcion;

  setColor(LIGHTGREEN);
  cout<<"CONFIRMAR ? (1-Si / 0-No): ";
  setColor(WHITE);
  cin>>opcion;

  cout<<endl;

  while (opcion!=0 && opcion!=1){
    setColor(LIGHTRED);
    cout<<"OPCION INVALIDA, INGRESE (1.Si / 0.No): ";
    setColor(WHITE);
    cin>>opcion;
  }
  if(opcion==0){
    setColor(LIGHTRED);
    cout<<"REGISTRO CANCELADO "<<endl;
    setColor(WHITE);
    return;
  }

 Servicios servis(idS,nombre,descripcion,proveedor,costo,eliminado);

 if(_repo.guardar(servis)){
    setColor(GREEN);
    cout<<"SERVICIO GUARDADO CORRECTAMENTE "<<endl;
    setColor(WHITE);
 }
 else {
    setColor(LIGHTRED);
    cout<<"ERROR AL GUARDAR EL SERVICIO "<<endl;
    setColor(WHITE);
 }
}

void ManagerServicios::mostrarServicios(Servicios servis){
    cout<<"ID SERVICIOS: #"<<servis.getIdServicio()<<endl;
    cout<<"TIPO DE SERVICIO: "<<servis.getNombreServicio()<<endl;
    cout<<"DESCRIPCION: "<<servis.getDescripcion()<<endl;
    cout<<"PROVEEDOR: "<<servis.getProveedor()<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"PRECIO: $"<<servis.getPrecio()<<endl;
    if(servis.getEliminado()){
        setColor(LIGHTRED);
        cout<<"ESTE SERVICIOS FUE ELIMINADO "<<endl;
        setColor(WHITE);
    }
}

void ManagerServicios::listarServicios(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;

  setColor(LIGHTMAGENTA);
  cout<<"-----------------";
  cout<<"----SERVICIOS DISPONIBLES----";
  cout<<"-----------------"<<endl;
  setColor(YELLOW);


  for (int i = 0; i < cantidad; i++){
    Servicios servis = _repo.leer(i);
    if(!servis.getEliminado()){
    mostrarServicios(servis);
    encontrado=true;
    setColor(LIGHTMAGENTA);
    cout << "--------------------------------------" << endl;
    setColor(YELLOW);
//    system("pause");
//    system("cls");
  }
}
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
    setColor(WHITE);
  }
}

void ManagerServicios::buscarIdServicios(){
    int idServicio;

    setColor(LIGHTMAGENTA);
    cout<<"----BUSCAR EL SERVICIO POR ID----"<<endl;
    setColor(WHITE);

    int cantLinea=0,errorLinea=cantLinea +4;

    gotoxy(1,cantLinea + 2); cout<<"INGRESAR ID SERVICIOS:#(0 para cancelar):";

    while(true){
        gotoxy(43,cantLinea+2);
        cout<<"              "<<endl;
        gotoxy(43,cantLinea+2);

    idServicio=cargarEntero(43,cantLinea+2,errorLinea);


    if(idServicio==0){
        return;
    }

    break;
}

    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    for (int i=0; i<cantidad; i++) {
        Servicios s = _repo.leer(i);
        if(s.getIdServicio() == idServicio){
            setColor(LIGHTMAGENTA);
            cout<<"-----SERVICIOS ENCONTRADO-----"<<endl;
            setColor(YELLOW);
            mostrarServicios(s);
            setColor(LIGHTMAGENTA);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
    }
    if(!encontrado) {
        setColor(LIGHTRED);
        cout<<"NO SE ENCONTRO EL SERVICIO "<<endl;
        setColor(WHITE);
    }
}


void ManagerServicios::serviciosXproveedor(){
    int cantidad=_repo.getCantidadRegistros();

     if(cantidad==0){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
     }

     int cantLinea=0,errorLinea=cantLinea+3;

     string proveedor;
     setColor(YELLOW);
     cout<<"INGRESE PROVEEDOR: ";
     setColor(WHITE);

     proveedor=cargarCadena();

     while (!Valido(proveedor)) {
        mostrarError("ERROR:(solo letras)",errorLinea);
        gotoxy(20,cantLinea + 1);
        cout<<"               ";
        gotoxy(20,cantLinea + 1);

        proveedor=cargarCadena();

    }
    cout<<endl;

//    system("pause");
//    system("cls");

     bool encontrado=false;
     setColor(LIGHTMAGENTA);
     cout<<"--- INFORMACION DEL SERVICIO ---"<<endl;
     for(int i=0;i<cantidad;i++){
        Servicios servi=_repo.leer(i);
        if(!servi.getEliminado()&&servi.getProveedor()==proveedor){
            setColor(YELLOW);
            cout<<"ID: #"<<servi.getIdServicio()<<" "<<servi.getNombreServicio()<<endl;
            cout<<"DESCRIPCION: "<<servi.getDescripcion()<<endl;
            cout<<" ($"<<servi.getPrecio()<<") "<<endl;
            encontrado=true;
        }
     }
     if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS CON ESE PROVEEDOR "<<endl;
        setColor(WHITE);
     }
     cout<<endl;
}



void ManagerServicios::eliminar(){
  int opcion;
  do{
  system("cls");
  setColor(LIGHTMAGENTA);
  cout<<"------------------------------"<<endl;
  setColor(YELLOW);
  cout<<"1. ELIMINAR SERVICIOS "<<endl;
  cout<<"2. MOSTRAR SERVICIOS ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  setColor(LIGHTMAGENTA);
  cout<<"------------------------------"<<endl;
  setColor(YELLOW);
  cout<<"OPCION: ";
  setColor(WHITE);
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      eliminarServicios();
    break;
  case 2:
      MostrarServiciosEliminados();
    break;
  case 0:
    return;
default:
    cout<<"Opcion Invalida, Intente Nuevamente "<<endl;
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerServicios::eliminarServicios(){
   int idServicio,pos;
   Servicios servis;
   char eliminar;

   setColor(LIGHTMAGENTA);
   cout<<"---SERVICIOS DISPONIBLES---"<<endl;
   ArchivoServicios arcS;
   int cantS=arcS.getCantidadRegistros();
   bool encontrado=false;
   setColor(YELLOW);

   for(int i=0;i<cantS;i++){
    servis=arcS.leer(i);
    if(!servis.getEliminado()){
        cout<<"ID: #"<<servis.getIdServicio()<<" "<<servis.getNombreServicio()<<" ($"<<servis.getPrecio()<<") "<<endl;
        encontrado=true;
    }
   }
   if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
    return;
   }

   system("pause");
   system("cls");

   int cantLinea=0,errorLinea=cantLinea+6;

   setColor(LIGHTRED);
   cout<<"---- ELIMINAR SERVICIO ----"<<endl;
   cout<<"---------------------------"<<endl;
   cout<<"INGRESE ID SERVICIO:#(0 para cancelar): ";
   setColor(WHITE);

   while(true){
            gotoxy(40, cantLinea + 3);
            cout << "               ";
            gotoxy(40, cantLinea + 3);

   idServicio=cargarEntero(40,cantLinea+3,errorLinea);

    if(idServicio==0){
        return;
    }
    break;
 }
    pos=_repo.buscarIdServicios(idServicio);

   if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL SERVICIO NO EXISTE! "<<endl;
    return ;
  }
  servis= _repo.leer(pos);

  setColor(LIGHTMAGENTA);
  cout<<"INFORMACION DEL SERVICIO "<<endl;
  setColor(YELLOW);
  cout<<endl;
  mostrarServicios(servis);

  cout<<endl;
  setColor(LIGHTRED);
  cout<<"QUIERE ELIMINAR? S/N ";
  setColor(WHITE);
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){
    servis.setEliminado(true);

  if(_repo.eliminar(pos)){
      setColor(LIGHTGREEN);
    cout<<"EL SERVICIO FUE ELIMINADO"<<endl;
  }
  else {
      setColor(LIGHTRED);
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL SERVICIO "<<endl;
  }
  }
}

void ManagerServicios::MostrarServiciosEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    setColor(YELLOW);
    for(int i=0;i<cantidad;i++){
        Servicios servis=_repo.leer(i);
       if(servis.getEliminado()){
        mostrarServicios(servis);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS ELIMINADOS "<<endl;
        return;
    }
}

void ManagerServicios::modificarServicio(){
    int id;
    int cantidad=_repo.getCantidadRegistros();

    bool encontrados=false;
    for(int i=0; i<cantidad; i++){
        Servicios servis=_repo.leer(i);
        setColor(YELLOW);
        if(!servis.getEliminado()){
            cout<<"ID: #"<<servis.getIdServicio()<<" "<<servis.getNombreServicio()<<" ($"<<servis.getPrecio()<<") "<<endl;
            encontrados=true;
        }
    }
    if(!encontrados){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
    }

    system("pause");
    system("cls");

    int cantLinea=0, errorLinea=cantLinea+4;

	cout << "INGRESE EL ID SERVICIO A MODIFICAR:# ";
    setColor(WHITE);

 while(true){
        gotoxy(37, cantLinea + 1);
        cout << "           ";
        gotoxy(37, cantLinea + 1);

    id=cargarEntero(37,cantLinea +1, errorLinea);

    if(id==0){
        return;
    }
    break;
 }
	int pos = _repo.buscarIdServicios(id);

	if (pos == -1) {
        setColor(LIGHTRED);
		cout << "SERVICIO NO ENCONTRADO." << endl;
        setColor(WHITE);
		return;
	}
	Servicios servis = _repo.leer(pos);

	if(!servis.getEliminado()){
    setColor(YELLOW);
	mostrarServicios(servis);
	}

int opcion;
do {
    system("cls");
    setColor(LIGHTMAGENTA);
    cout<<" INGRESE NUEVOS DATOS "<<endl;
    setColor(YELLOW);
    cout<<"1. MODIFICAR EL NOMBRE "<<endl;
    cout<<"2. MODIFICAR DESCRIPCION "<<endl;
    cout<<"3. MODIFICAR PROVEEDOR "<<endl;
    cout<<"4. MODIFICAR PRECIO "<<endl;
    cout<<"0. SALIR Y GUARDAR "<<endl;
    cout<<"OPCION: ";
    setColor(WHITE);
    cin>>opcion;

    system("cls");
    switch(opcion){
 case 1:{
     string nombre;
     setColor(LIGHTGREEN);
     cout<<"NOMBRE ACTUAL: "<<servis.getNombreServicio()<<endl;
     setColor(YELLOW);
     cout<<"NUEVO NOMBRE: ";
     setColor(WHITE);
     nombre=cargarCadena();

     while (!Valido(nombre)) {
        mostrarError("ERROR:(solo letras)", errorLinea);
        gotoxy(14, cantLinea + 2);
        cout << "             ";
        gotoxy(14, cantLinea + 2);

        nombre=cargarCadena();
    }
    servis.setNombreServicio(nombre);
    break;
 }
 case 2: {
     string descripcion;
     setColor(LIGHTGREEN);
     cout<<"DESCRIPCION ACTUAL: "<<servis.getDescripcion()<<endl;
     setColor(YELLOW);
     cout<<"NUEVA DESCRIPCION: ";
     setColor(WHITE);
     descripcion=cargarCadena();

        while (!ValidoDescripcion(descripcion)){
        mostrarError("ERROR:(solo letras)", errorLinea);
        gotoxy(19, cantLinea + 2);
        cout << "             ";
        gotoxy(19, cantLinea + 2);
        descripcion=cargarCadena();
    }
     servis.setDescripcion(descripcion);
 break;
 }
 case 3:{
     string proveedor;
     setColor(LIGHTGREEN);
     cout<<"PROVEEDOR ACTUAL: "<<servis.getProveedor()<<endl;
     setColor(YELLOW);
     cout<<"NUEVO PROVEDOR: ";
     setColor(WHITE);
     proveedor=cargarCadena();

        while (!Valido(proveedor)) {
        mostrarError("ERROR:(solo letras)", errorLinea);
        gotoxy(16, cantLinea + 2);
        cout << "             ";
        gotoxy(16, cantLinea + 2);
        proveedor=cargarCadena();
    }
    servis.setProveedor(proveedor);
 break;
 }
 case 4:{
     float precio;
     setColor(LIGHTGREEN);
     cout<<"PRECIO ACTUAL: $"<<servis.getPrecio()<<endl;
     setColor(YELLOW);
     cout<<"NUEVO PRECIO: $";
     setColor(WHITE);

    while (true) {
        gotoxy(16, cantLinea + 2);
        cout << "           ";
        gotoxy(16, cantLinea + 2);

      precio=cargarEntero(16,cantLinea+2,errorLinea);

    break;
     }

    cout<<fixed<<setprecision(2);
    servis.setPrecio(precio);

 break;
 }
 case 0:
    break;
 default:
     setColor(LIGHTRED);
     cout<<"Opcion Invalida, Intente Nuevamente "<<endl;
    break;
    }
system("pause");

}while (opcion!=0);

	if (_repo.guardar(pos, servis)) {
        setColor(LIGHTGREEN);
		cout << "SERVICIO MODIFICADO CORRECTAMENTE." << endl;
	} else {
	    setColor(LIGHTRED);
		cout << "ERROR AL MODIFICAR EL SERVICIO." << endl;
	}
}

void ManagerServicios::ActivarServicios(){
  int id, pos;
  char activar;

  int cantidad=_repo.getCantidadRegistros();
  bool encontrado=false;
  setColor(LIGHTMAGENTA);
  cout<<"SERVICIOS ELIMINADOS "<<endl;
  setColor(YELLOW);
    for(int i=0;i<cantidad;i++){
    Servicios ser=_repo.leer(i);
    if(ser.getEliminado()){
        cout<<"~ID: #"<<ser.getIdServicio()<<" "<<ser.getNombreServicio()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY SERVICIOS ELIMINADOS "<<endl;
    return;
  }
  system("pause");
  system("cls");

  int cantLinea=0,errorLinea=cantLinea+6;

  setColor(LIGHTMAGENTA);
  cout<<"~~~~ ACTIVAR SERVICIOS ~~~~"<<endl;
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
 setColor(YELLOW);
  cout<<"ID SERVICIO:# (0 para cancelar): ";
  setColor(WHITE);
   while(true){
        gotoxy(33,cantLinea+4);
        cout<<"       ";
        gotoxy(33,cantLinea+4);

   id=cargarEntero(33,cantLinea + 4, errorLinea);

    if(id==0){
        return;
    }
    break;
 }

  pos=_repo.buscarIdServicios(id);

  if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL SERVICIO NO EXISTE "<<endl;
    return;
  }

  Servicios servis;
  servis= _repo.leer(pos);

    if(!servis.getEliminado()){
    setColor(RED);
    cout<<"EL SERVICIO NO ESTA ELIMINADO "<<endl;
    return;
  }

  setColor(LIGHTMAGENTA);
  cout<<"~~INFORMACION DEL SERVICIO ELIMINADO~~"<<endl;
  cout<<endl;
  setColor(YELLOW);
  mostrarServicios(servis);
  cout<<endl;

  setColor(LIGHTGREEN);
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  cin>>activar;
   if(activar=='s' or activar=='S'){
    servis.setEliminado(false);
   }
   if(_repo.guardar(pos,servis)){
    setColor(LIGHTGREEN);
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    setColor(RED);
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}

void ManagerServicios::buscar(){
   int opcion;
do {
   system("cls");
   setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~BUSCAR SERVICIOS~~~~~~~~~"<<endl;
   setColor(YELLOW);
   cout<<" 1. BUSCAR POR ID "<<endl;
   cout<<" 2. BUSCAR POR PROVEEDOR "<<endl;
   cout<<" 0. VOLVER AL MENU SERVICIOS "<<endl;
   setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   setColor(YELLOW);
   cout<<"OPCION: ";
   setColor(WHITE);
   cin>>opcion;
       system("cls");

   switch(opcion){
case 1:
    buscarIdServicios();
    break;
case 2:
    serviciosXproveedor();
    break;
case 0:
   break;
default:
    cout<<"Opcion invalida, Intenta Nuevamente "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);

}

void ManagerServicios::menuServicios(){
int opcion;
do {
   system("cls");
   setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~~~~~SERVICIOS~~~~~~~~~~~~~"<<endl;
   setColor(YELLOW);
   cout<<" 1. CARGAR "<<endl;
   cout<<" 2. MOSTRAR "<<endl;
   cout<<" 3. MODIFICAR "<<endl;
   cout<<" 4. ELIMINAR "<<endl;
   cout<<" 5. ACTIVAR "<<endl;
   cout<<" 6. BUSCAR SERVICIOS "<<endl;
   cout<<" 0. VOLVER AL MENU EVENTO/SERVICIOS "<<endl;
   setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   setColor(YELLOW);
   cout<<"OPCION: ";
   setColor(WHITE);
   cin>>opcion;

system("cls");

   switch(opcion){
case 1:
    cargarServicios();
    break;
case 2:
    listarServicios();
    break;
case 3:
    modificarServicio();
    break;
case 4:
    eliminar();
    break;
case 5:
    ActivarServicios();
    break;
case 6:
    buscar();
    break;
case 0:
   break;
default:
    cout<<"Opcion invalida, Intenta Nuevamente "<<endl;
    break;
   }
   system("pause");
}while(opcion!=0);
}
