#include <iostream>
#include <iomanip>
#include "ManagerEvento.h"
#include "Fecha.h"
#include "ArchivoClientes.h"
#include "Clientes.h"
#include "Necesario.h"
#include "ManagerEventoServicios.h"
#include "ArcPagos.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;


ManagerEvento::ManagerEvento()
{
    //ctor
}

void ManagerEvento::cargarEvento(){
    int idE, idC, cant;
    string nombre;
    Fecha fechaEvento, fechaPagoR;

    ArchivoClientes arcC;
    int cantClientes = arcC.getCantidadRegistros();

    if (cantClientes == 0){
        setColor(RED);
        cout << "NO HAY CLIENTES REGISTRADOS " << endl;
        anykey();
        setColor(WHITE);
        return;
    }

    setColor(LIGHTCYAN);
    cout <<"-------------------------";
    cout <<"--- CLIENTES DISPONIBLES ---";
    cout <<"-------------------------"<< endl;
    setColor(WHITE);

    for(int i = 0; i < cantClientes; i++){
        Clientes cliente = arcC.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID CLIENTE: #"<<cliente.getIdCliente()<<"  ";
            cout<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ";
            cout<<"( "<< cliente.getDNI()<<" )"<<endl;
            setColor(LIGHTCYAN);
            cout<<"-------------------------"<< endl;
            setColor(WHITE);
        }
    }
    cout<<endl;
    system("pause");
    system("cls");

    int cantLinea=4,lineaError=cantLinea+20;

    /// Comienzo de la carga
    setColor(LIGHTRED);
    cout<<"------------------------";
    cout<<"------ CARGAR EVENTO -------";
    cout<<"------------------------"<<endl;
    setColor(WHITE);

    int tipoEvento;
    idE = _repo.getNuevoIdEvento();

    gotoxy(1, cantLinea + 1); cout << "ID EVENTO: #"<<idE;
    gotoxy(1, cantLinea + 2); cout << "ID CLIENTE:(0 para cancelar)#";

    gotoxy(1, cantLinea + 4); cout << " --- TIPO DE EVENTO --- ";
    gotoxy(1, cantLinea + 5); cout << "0. Boda ";
    gotoxy(1, cantLinea + 6); cout << "1. Cumpleanios ";
    gotoxy(1, cantLinea + 7); cout << "2. Empresarial ";
    gotoxy(1, cantLinea + 8); cout << "3. Bautismos, Comunion ";
    gotoxy(1, cantLinea + 9); cout << "4. Graduacion ";
    gotoxy(1, cantLinea + 10); cout <<"SELECCIONE TIPO (0-4): ";

    gotoxy(1, cantLinea + 12); cout << "NOMBRE DEL EVENTO: ";
    gotoxy(1, cantLinea + 13); cout << "CANTIDAD DE INVITADOS: ";
    gotoxy(1, cantLinea + 14); cout << "PRECIO DE LA RESERVA: $";
    gotoxy(1, cantLinea + 15); cout << "FECHA DEL EVENTO:";

    while (true) {
        gotoxy(31, cantLinea + 2);
        cout << "               ";
        gotoxy(31, cantLinea + 2);


        idC=cargarEntero(31,cantLinea+2,lineaError);

        if (idC == 0) {
            setColor(RED);
            mostrarError ("OPERACION CANCELADA ",lineaError);
            setColor(WHITE);
            cout<<endl;
            return;
        }

        bool existe = false;

        for (int i = 0; i < cantClientes; i++){
            Clientes cli = arcC.leer(i);
            if (cli.getIdCliente() == idC && !cli.getEliminado()){
                existe = true;
                break;
            }
        }
        if (!existe) {
            mostrarError ("No Existe ID, Intente Nuevamente",lineaError);
            continue;
        }
        break;
    }

    cout<<endl;

     mostrarHistorial(idC);

    while (true) {
        gotoxy(23, cantLinea + 10);
        cout << "        ";
        gotoxy(23, cantLinea + 10);

        tipoEvento=cargarEntero(23,cantLinea+10,lineaError);

        if (tipoEvento < 0 || tipoEvento > 4) {
            setColor(RED);
           mostrarError ("Tipo invalido, Elija entre 0 y 4 ",lineaError);
           setColor(WHITE);
           continue;
        }
        break;
    }

    cin.ignore();

        gotoxy(20, cantLinea + 12);

        nombre=cargarCadena();

    while (!Valido(nombre)) {
        mostrarError("ERROR:(solo letras)", lineaError);
        gotoxy(20, cantLinea + 12);
        cout << "                           ";
        gotoxy(20, cantLinea + 12);
        nombre = cargarCadena();
    }

    mostrarError("", lineaError);

    while (true) {
        gotoxy(23, cantLinea + 13);
        cout << "        ";
        gotoxy(23, cantLinea + 13);


        cant=cargarEntero(23,cantLinea+13,lineaError);

        if (cant <= 0) {
            mostrarError ("La cantidad debe ser mayor a 0 ",lineaError);
          continue;
        }
        break;
    }

    mostrarError("",lineaError);

    Eventos even;

    gotoxy(24,cantLinea+14);
    float precio = even.calcularPrecioInicial(cant);
    cout <<fixed << setprecision(2) << precio << endl;

    gotoxy(1,cantLinea+16);
    fechaEvento.cargarFecha();

/// se quito el pago se paga todo junto con los servicios y en manager de pago

    Eventos evento(idE, idC, nombre, fechaEvento, cant, true);
    evento.setPrecioInicial(precio);
    evento.setTipoEvento(tipoEvento);///colocar en el constructor
    evento.setEstado(false);
    evento.setEliminado(false);

    if(_repo.guardar(evento)){
        setColor(GREEN);
        cout << "EVENTO GUARDADO CORRECTAMENTE." << endl;
        setColor(WHITE);
    }
    else {
        setColor(RED);
        cout << "ERROR AL GUARDAR EL EVENTO." << endl;
        setColor(WHITE);
    }
}

void ManagerEvento::mostrarEvento(Eventos evento){

    cout<<"ID EVENTO: #"<<evento.getIdEvento()<<endl;
    cout<<"ID CLIENTE: #" <<evento.getidCliente()<<endl;
    cout<<"TIPO DE EVENTO: ";
    switch(evento.getTipoEvento()){
         case 0: cout<<"Boda"; break;
         case 1: cout<<"Cumpleanios"; break;
         case 2: cout<<"Empresarial"; break;
         case 3: cout<<"Bautismos, Comunion"; break;
         case 4: cout<<"Graduacion"; break;
    }
  cout<<endl;

   cout<<"NOMBRE DE EVENTO: "<<evento.getNombreEvento()<<endl;
   cout<<"CANTIDAD DE INVITADOS: "<<evento.getcantidadInvitados()<<endl;
   cout<<"PRECIO RESERVA: $"<<evento.getPrecioInicial()<<endl;
   cout<<"FECHA DEL EVENTO: ";

   evento.getFechaEvento().mostrarFecha();

   // cout<<"ESTADO: "<< (evento.getConfirmado() ? " ACTIVO":" CANCELADO")<<endl;
   cout << "ESTADO: ";

     if (evento.getConfirmado()) {
        setColor(LIGHTGREEN);
       cout << "ACTIVO";
        }
     else {
       setColor(LIGHTRED);
       cout << "CANCELADO";
    }

setColor(WHITE);
cout << endl;

  if(evento.getEliminado()){
    setColor(LIGHTRED);
    cout<<"EVENTO ELIMINADO  "<<endl;
     anykey();
     setColor(WHITE);
  }
  cout<<endl;
}

///LISTAR TODOS LOS EVENTOS
void ManagerEvento::listarEvento(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;
  setColor(LIGHTCYAN);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~";
  cout<<"~~~~~ EVENTOS REGISTRADOS ~~~~~";
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  setColor(WHITE);

  for (int i = 0; i < cantidad; i++){
    Eventos evento = _repo.leer(i);
    if(!evento.getEliminado()){
    mostrarEvento(evento);
    encontrado=true;
    setColor(LIGHTCYAN);
    cout << "--------------------------" << endl;
    setColor(WHITE);
  }
}
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
    setColor(WHITE);
  }
}

///BUSCAR ID EVENTO
void ManagerEvento::buscarIdEvento(){
    int id, cantLinea=0, errorLinea=cantLinea + 4;
   ArchivoEvento ArcE;
    int cantE = _repo.getCantidadRegistros();

    if(cantE == 0){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
    }

    setColor(LIGHTCYAN);
    cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
    setColor(WHITE);
    for(int i=0;i<cantE;i++){
        Eventos evento = _repo.leer(i);
        if(!evento.getEliminado()){
            cout<<"ID: #"<<evento.getIdEvento()<<" "<<evento.getNombreEvento()<<endl;
        }
        cout<<endl;
    }
    system("pause");
    system("cls");


    setColor(LIGHTCYAN);
    cout<<"**** BUSCAR POR ID ****"<<endl;
    setColor(WHITE);
    cout<<"ID EVENTO: #";

 while(true){

        gotoxy(13,cantLinea+2);
        cout<<"     "<<endl;
        gotoxy(13,cantLinea+2);

        id=cargarEntero(13,cantLinea+2,errorLinea);

    if(id==0){
       mostrarError ("VUELVE AL MENU ANTERIOR ",errorLinea);
        return;
    }
    break;
}
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;

    ///muestra el evento
    for (int i = 0; i < cantidad; i++) {
        Eventos h = _repo.leer(i);
        if (!h.getEliminado() && h.getIdEvento() == id) {
            setColor(LIGHTCYAN);
            cout<<"-----EVENTO ENCONTRADO-----"<<endl;
            setColor(WHITE);
            mostrarEvento(h);
            setColor(LIGHTCYAN);
            cout<<"---------------------------" << endl;
            setColor(WHITE);
            encontrado = true;
        }
    }
    if (!encontrado) {
        mostrarError("NO SE ENCONTRO EL EVENTO.", errorLinea);
    }
}

void ManagerEvento::buscarEventoDeCliente(){
    ArchivoClientes arcC;

    int cantLinea=0, lineaError = cantLinea +2;

    int cantC = arcC.getCantidadRegistros();
    int cantE = _repo.getCantidadRegistros();

    if(cantC == 0){
        setColor(LIGHTRED);
        cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
    }

    setColor(LIGHTCYAN);
    cout<<"--- CLIENTES DISPONIBLES ---"<<endl;
    setColor(WHITE);
    for(int i=0;i<cantC;i++){
        Clientes cliente = arcC.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID: #"<<cliente.getIdCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDNI()<<") "<<endl;
        }
    }

    system("pause");
    system("cls");

    int idCliente;

    cout<<"INGRESE ID CLIENTE (0 para volver): ";
    setColor(WHITE);

 while(true){
        gotoxy(36,cantLinea + 1);
        cout<<"       "<<endl;
        gotoxy(36,cantLinea + 1);

       idCliente=cargarEntero(36,cantLinea+1,lineaError);

    if(idCliente==0){
      mostrarError ("VUELVE AL MENU ANTERIOR",lineaError);
        return;
    }
    break;
}

    bool hayEventos=false;

    system("pause");
    system("cls");

    setColor(LIGHTCYAN);
    cout<<"--- EVENTOS REALIZADOS DEL CLIENTE #" << idCliente << " ---"<<endl;
    setColor(WHITE);

    for(int i=0;i<cantE;i++){
        Eventos evento = _repo.leer(i);
        if(!evento.getEliminado() &&evento.getConfirmado() &&evento.getidCliente() == idCliente){
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<endl;
            cout<<"NOMBRE DEL EVENTO: "<<evento.getNombreEvento()<<endl;
            cout<<"INVITADOS: "<<evento.getcantidadInvitados()<<endl;
            cout<<"---------------------------"<<endl;
            hayEventos=true;
        }
    }

cout<<endl;

    if(!hayEventos){
        setColor(LIGHTRED);
        cout<<"EL CLIENTE NO TIENE EVENTOS REALIZADOS"<<endl;
        setColor(WHITE);
    }
}


///ELIMINAR
void ManagerEvento::eliminarEvento(){
   int id,pos;
   char eliminar;

   setColor(LIGHTCYAN);
   cout<<"----EVENTOS DISPONIBLES----"<<endl;
   setColor(WHITE);
   ArchivoEvento arcE;

   int cantE=arcE.getCantidadRegistros();

   bool encontrado=false;

   for(int i=0;i<cantE;i++){
    Eventos evento=arcE.leer(i);
    if(!evento.getEliminado()){
        cout<<"~ ID: #"<<evento.getIdEvento()<<" "<<evento.getNombreEvento()<<endl;
        encontrado=true;
    }
   }
   if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
    setColor(WHITE);
    return;
   }

   system("pause");
   system("cls");

   int canLinea=0, errorLinea=canLinea+4;

   setColor(RED);
   cout<<"---- ELIMINAR EVENTO ----"<<endl;
   setColor(WHITE);

   cout<<"INGRESE ID EVENTO: # (0 para cancelar):";

 while(true){
        gotoxy(41,canLinea +2);
        cout<<"     ";
        gotoxy(41,canLinea +2);

     id=cargarEntero(41,canLinea+2,errorLinea);

    if(id==0){
            mostrarError("vuelve al menu anterior ",errorLinea);
        return;
    }
    break;
 }
    pos=_repo.buscarIDEvento(id);

   if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL EVENTO NO EXISTE! "<<endl;
    setColor(WHITE);
    return ;
  }

   Eventos evento = _repo.leer(pos);
   ManagerEventoServicios manager;


   if (manager.eventoPagado(evento.getIdEvento())) {
       setColor(LIGHTRED);
       cout << "EL EVENTO YA ESTA PAGADO. NO SE PUEDE ELIMINAR." << endl;
       return;
}

  setColor(LIGHTCYAN);
  cout<<"INFORMACION DEL EVENTO "<<endl;
  setColor(WHITE);
  cout<<endl;
  mostrarEvento(evento);

  cout<<endl;
  setColor(LIGHTRED);
  cout<<"QUIERE ELIMINAR? S/N ";
  setColor(WHITE);
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    setColor(RED);
    cout<<"EL EVENTO FUE ELIMINADO"<<endl;
    setColor(WHITE);
  }
  else {
    setColor(LIGHTRED);
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL EVENTO "<<endl;
    setColor(WHITE);
   }
 }
}

///ACTIVAR EL EVENTO ELIMINADO
void ManagerEvento::ActivarEvento(){
  int id, pos;
  char activar;

  ArchivoEvento arcE;

  int cantE=arcE.getCantidadRegistros();
  bool encontrado=false;

  setColor(LIGHTCYAN);
  cout<<"~~~~ EVENTOS ELIMINADOS ~~~~"<<endl;
  setColor(WHITE);

  for(int i=0;i<cantE;i++){
    Eventos eve=arcE.leer(i);
    if(eve.getEliminado()){
        cout<<"~ID: #"<<eve.getIdEvento()<<" "<<eve.getNombreEvento()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY EVENTOS ELIMINADOS "<<endl;
    setColor(WHITE);
    return;
  }

  system("pause");
  system("cls");

  int canLinea=1,errorLinea=canLinea+4;

  setColor(LIGHTCYAN);
  cout<<"~~~~ ACTIVAR EVENTO ~~~~"<<endl;
  setColor(WHITE);

  cout<<"ID EVENTO: # (0 para cancelar):";

  while(true){

        id=cargarEntero(33,canLinea+1,errorLinea);

    if(id==0){
        mostrarError("vuelve al menu anterior ",errorLinea);
        return;
    }
    break;
 }

  pos=_repo.buscarIDEvento(id);

  if(pos==-1){
    mostrarError ("EL EVENTO NO EXISTE ",errorLinea);
    return;
  }

  Eventos evento;

  evento= _repo.leer(pos);

    if(!evento.getEliminado()){
    setColor(GREY);
    cout<<" EL EVENTO NO ESTA ELIMINADO "<<endl;
    setColor(WHITE);
    return;
  }

  setColor(LIGHTCYAN);
  cout<<"INFORMACION DEL EVENTO ELIMINADO "<<endl;
  cout<<endl;
  setColor(WHITE);
  mostrarEvento(evento);
  cout<<endl;

  setColor(LIGHTCYAN);
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  setColor(WHITE);
  cin>>activar;


   if(activar=='s' or activar=='S'){
    evento.setEliminado(false);
    evento.setConfirmado(true);
   }

   if(_repo.guardar(pos,evento)){
    setColor(LIGHTGREEN);
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
    setColor(WHITE);
   }
   else {
    setColor(RED);
    cout<<"OCURRIO UN ERROR "<<endl;
    setColor(WHITE);
   }
}

///MOSTRAR ELIMINADOS
void ManagerEvento::mostrarEventosEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Eventos evento=_repo.leer(i);
       if(evento.getEliminado()){
        mostrarEvento(evento);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS ELIMINADOS "<<endl;
        setColor(WHITE);
        return;
    }
}

///ordenado por mes/ anio
void ManagerEvento::ordanadosPorFecha(){
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~";
    cout<<"~~~~ORDENADOS POR FECHA~~~~";
    cout<<"~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);

  int cantidad = _repo.getCantidadRegistros();

  Eventos*evento;

  evento=new Eventos[cantidad];

  _repo.leerTodos(evento,cantidad);

  for(int i=0;i<cantidad;i++){ ///metodo burbuja
        bool intercambio=false;
    for(int j=0;j<cantidad -1-i;j++){
        Fecha f1=evento[j].getFechaEvento();
        Fecha f2=evento[j+1].getFechaEvento();
        bool f1esMaayor=false;
      if (f1.getAnio() > f2.getAnio()) {
            f1esMaayor=true;
       } else if (f1.getAnio() == f2.getAnio()) {
      if (f1.getMes() > f2.getMes()) {
          f1esMaayor=true;
      } else if (f1.getMes() == f2.getMes()) {
        if (f1.getDia() > f2.getDia()) {
            f1esMaayor=true;
        }
    }
}
if(f1esMaayor){
        Eventos aux= evento[j];
        evento[j]=evento[j+1];
        evento[j+1]=aux;
        intercambio=true;
       }
    }
    if(!intercambio){
        break;
    }
}

  for (int i = 0; i < cantidad; i++)
  {
    mostrarEvento(evento[i]);
    setColor(LIGHTCYAN);
    cout << "------------------------" << endl;
    setColor(WHITE);
  }
  delete[] evento;
}

///EDITAR EL EVENTO...

void ManagerEvento::modificarEvento() {
	int id, CantLinea=0,errorLinea=CantLinea+3;
	int cant=_repo.getCantidadRegistros();
	bool encontrado=false;

	setColor(LIGHTCYAN);
	cout<<"~~~~~~~~~~~~~ EVENTOS DISPONIBLES ~~~~~~~~~~~~~"<<endl;
	setColor(WHITE);
	for(int i=0; i<cant; i++){
        Eventos evento=_repo.leer(i);
        if(!evento.getEliminado() && evento.getConfirmado() ){
            setColor(LIGHTGREEN);
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<", ";
            setColor(WHITE);
            cout<<" ID CLIENTE: #"<<evento.getidCliente()<<" |Nombre del Evento: "<<evento.getNombreEvento()<<endl;
            encontrado=true;
        }
        cout<<endl;
	}

	if(!encontrado) {
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
	}
	setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
    setColor(WHITE);

    system("pause");
    system("cls");

    setColor(LIGHTCYAN);
	gotoxy(1, CantLinea + 2); cout<<"INGRESE EL ID EVENTO A MODIFICAR: #";
	setColor(WHITE);

 while(true){

        gotoxy(37,CantLinea + 2);
        cout << "        ";
        gotoxy(37, CantLinea + 2);

     id=cargarEntero(37,CantLinea+2,errorLinea);

    if(id==0){
       mostrarError ("Error: Intente Nuevamente ",errorLinea);
        continue;
    }
    break;
 }

    int pos = _repo.buscarIDEvento(id);

	if (pos == -1) {
     setColor(LIGHTRED);
		cout<<"EVENTO NO ENCONTRADO" << endl;
		setColor(WHITE);
		return;
	}

	Eventos evento = _repo.leer(pos);
    ManagerEventoServicios manager;

   if(manager.eventoPagado(evento.getIdEvento())) {
     setColor(LIGHTRED);
      cout<<"ESTE EVENTO YA ESTA PAGADO, NO SE PUEDE MODIFICAR "<<endl;
      setColor(WHITE);
      return;
}

	if(!evento.getEliminado()){
	mostrarEvento(evento);
	}
	else {
        setColor(LIGHTRED);
        cout<<"Esta Eliminado "<<endl;
        setColor(WHITE);
        return;
	}

    system("pause");
	system("cls");

    int opcion;

    do{
      system("cls");
      setColor(LIGHTCYAN);
      cout<<"QUE QUIERE MODIFICAR? "<<endl;
      setColor(WHITE);
      cout<<"1. CLIENTE "<<endl;
      cout<<"2. TIPO DE EVENTO "<<endl;
      cout<<"3. NOMBRE DEL EVENTO "<<endl;
      cout<<"4. CANTIDAD DE INVITADOS "<<endl;
      cout<<"5. FECHA EVENTO "<<endl;
      cout<<"0. SALIR Y GUARDAR "<<endl;
      setColor(LIGHTCYAN);
      cout<<"----------------------"<<endl;
      setColor(WHITE);

      cout<<"OPCION: ";
      cin>>opcion;

      system("cls");

      switch(opcion){

  case 1:{
      ArchivoClientes arcCli;
      int cantC=arcCli.getCantidadRegistros();

      setColor(LIGHTCYAN);
      cout<<"CLIENTES DISPONIBLES "<<endl;
      setColor(WHITE);
      for(int i=0;i<cantC;i++){
        Clientes cliente=arcCli.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID CLIENTE: #"<<cliente.getIdCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<endl;
        }
      }

    system("pause");
	system("cls");


      int nuevoIdCliente;
      setColor(LIGHTCYAN);
      cout<<"INGRESE NUEVO ID CLIENTE: ";
      setColor(WHITE);

   while(true){
        gotoxy(27, CantLinea + 1);

        nuevoIdCliente=cargarEntero(27,CantLinea+1,errorLinea);

    if(nuevoIdCliente==0){
       mostrarError ("VUELVE AL MENU ANTERIOR ",errorLinea);
        return;
    }
    break;
 }
      bool existe=false;
      for(int i=0;i<cantC;i++){
        Clientes cliente=arcCli.leer(i);
        if(cliente.getIdCliente()==nuevoIdCliente && !cliente.getEliminado()){
            existe=true;
            break;
        }
      }
      if(!existe){
        mostrarError("El cliente no existe ",errorLinea);
        break;
      }
      evento.setidCliente(nuevoIdCliente);
      setColor(GREEN);
      cout<<"CLIENTE MODIFICADO "<<endl;
      setColor(WHITE);
    break;
      }

 case 2:{
    int tipoEvento;
  setColor(LIGHTCYAN);
  gotoxy(1, CantLinea + 1);  cout << " --- TIPO DE EVENTO --- "<<endl;
  gotoxy(1, CantLinea + 2); cout << "0. Boda "<<endl;
  gotoxy(1, CantLinea + 3); cout << "1. Cumpleanios "<<endl;
  gotoxy(1, CantLinea + 4); cout << "2. Empresarial "<<endl;
  gotoxy(1, CantLinea + 5); cout << "3. Bautismos, Comunion "<<endl;
  gotoxy(1, CantLinea + 6); cout << "4. Graduacion "<<endl;


    system("pause");
    system("cls");

    cout << "Seleccione tipo de evento (0-4): ";

    while (true) {
        setColor(WHITE);

        gotoxy(34,CantLinea + 1);
        cout << "            ";
        gotoxy(34, CantLinea + 1);


        tipoEvento=cargarEntero(34,CantLinea + 1,errorLinea);

        if (tipoEvento < 0 || tipoEvento > 4) {
           mostrarError ("ERROR: Elija entre 0 y 4",errorLinea);
            continue;
        }
        break;
    }
    evento.setTipoEvento(tipoEvento);
    setColor(GREEN);
    cout<<"Tipo de Evento Modificado Correctamente"<<endl;
    setColor(WHITE);
     break;
      }

  case 3:{
      string nombre;
      setColor(LIGHTCYAN);
      cout<<"NOMBRE DEL EVENTO ACTUAL: "<<evento.getNombreEvento()<<endl;
      setColor(WHITE);

      cout<<"INGRESE NOMBRE DEL EVENTO:";
      nombre=cargarCadena();

    while (!Valido(nombre)) {
        mostrarError("ERROR:(solo letras)", errorLinea);
        gotoxy(27, CantLinea + 2);
        cout << "                           ";
        gotoxy(27, CantLinea + 2);
        nombre = cargarCadena();
    }
      evento.setNombreEvento(nombre);
      setColor(GREEN);
      cout<<"NOMBRE DEL EVENTO MODIFICADO "<<endl;
      setColor(WHITE);

    break;
      }
  case 4:{
      int cantIn;
      setColor(LIGHTCYAN);
      cout<<"CANTIDAD DE INVITADOS ACTUAL: "<<evento.getcantidadInvitados()<<endl;
      setColor(WHITE);
      cout<<"CANTIDAD DE INVITADOS: ";

    while(true){
        gotoxy(23, CantLinea + 2);
        cout << "                           ";
        gotoxy(23, CantLinea + 2);

       cantIn=cargarEntero(23,CantLinea + 2,errorLinea);

       if(cantIn <= 0){
        mostrarError ("ERROR: La cantidad debe ser mayor a 0: ",errorLinea);
        continue;
       }
       break;
    }

      float precio=evento.calcularPrecioInicial(cantIn);

      evento.setPrecioInicial(precio);
      setColor(LIGHTCYAN);
      cout<<"PRECIO DE LA RESERVA: $"<<evento.getPrecioInicial()<<endl;
      setColor(WHITE);
      evento.setCantidad(cantIn);

    break;
  }
  case 5:{
      Fecha f;
      setColor(LIGHTCYAN);
      cout<<"FECHA DEL EVENTO ACTUAL: ";
      setColor(WHITE);
      evento.getFechaEvento().mostrarFecha();
      cout<<"FECHA DEL EVENTO: "<<endl;
      f.cargarFecha();

      evento.setFechaEvento(f);

      setColor(GREEN);
      cout<<"Fecha Modificada Correctamente"<<endl;
      setColor(WHITE);

    break;
  }
  case 0:
   break;
  default:
      setColor(RED);
      cout<<"Opcion Incorrecta, intente nuevamente "<<endl;
      setColor(WHITE);
    break;

      }
system("pause");

}while(opcion!=0);

	if (_repo.guardar(pos, evento)) {
        setColor(GREEN);
		cout << "EVENTO MODIFICADO CORRECTAMENTE." << endl;
        setColor(WHITE);
	} else {
	    setColor(LIGHTRED);
		cout << "ERROR AL MODIFICAR EL EVENTO." << endl;
		setColor(WHITE);
	}
}

///MENU ELIMINAR LOGICA
void ManagerEvento::eliminar(){
  int opcion;
  do {
    system("cls");
  setColor(LIGHTRED);
  cout<<"------------------------------"<<endl;
  setColor(GREY);
  cout<<"1. ELIMINAR EVENTOS "<<endl;
  cout<<"2. MOSTRAR EVENTOS ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  setColor(LIGHTRED);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);

  cout<<"OPCION: ";
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      eliminarEvento();
      break;
  case 2:
      mostrarEventosEliminados();
      break;
  case 0:
    return;
default:
    setColor(LIGHTRED);
    cout<<"Opcion invalida "<<endl;
    setColor(WHITE);
    break;
   }
   system("pause");
}while(opcion!=0);
}

///evento mas frecuentes
void ManagerEvento::eventosPorTipo() {
    ArchivoEvento arc;
    int cant = arc.getCantidadRegistros();

    if (cant == 0) {
        setColor(LIGHTRED);
        cout << "NO HAY EVENTOS REGISTRADOS." << endl;
        setColor(WHITE);
        return;
    }
    int contador[5] = {};
        string nombresTipos[5] = {"Boda","Cumpleanios","Empresarial","Bautismo/ Comunion","Graduacion"};

    for (int i = 0; i < cant; i++) {
        Eventos e = arc.leer(i);

        if (!e.getEliminado()) {
            int tipo = e.getTipoEvento();
                contador[tipo]++;
            }
        }
    setColor(LIGHTCYAN);
    cout << "--- CANTIDAD DE EVENTOS POR TIPO ---" << endl;
    setColor(WHITE);

    for (int i = 0; i < 5; i++) {
        if(contador[i] > 0){
        cout <<nombresTipos[i] << ":  " << contador[i] << " evento(s)" << endl;
        }
    }
    cout<<endl;
}

///historial del cliente
void ManagerEvento::mostrarHistorial(int idCliente) {
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;

    int col = 50;
    int fila = 4;

    setColor(LIGHTCYAN);
    gotoxy(col, fila++); cout << "===== HISTORIAL DE EVENTOS =====";
    setColor(WHITE);
    gotoxy(col, fila++); cout << "CLIENTE ID: #" << idCliente;
    gotoxy(col, fila++); cout << "-------------------------------";

    for (int i = 0; i < cantidad; i++) {
        Eventos evento = _repo.leer(i);

        if (!evento.getEliminado() && evento.getidCliente() == idCliente) {
            encontrado = true;

            gotoxy(col, fila++);
            cout << "ID EVENTO: #" << evento.getIdEvento();

            gotoxy(col, fila++);
            cout << "TIPO: ";
            switch (evento.getTipoEvento()) {
                case 0: cout << "Boda"; break;
                case 1: cout << "Cumpleanios"; break;
                case 2: cout << "Empresarial"; break;
                case 3: cout << "Bautismos / Comunion"; break;
                case 4: cout << "Graduacion"; break;
                default: break;
            }

            gotoxy(col, fila++);
            cout << "FECHA: ";
            evento.getFechaEvento().mostrarFecha();

            gotoxy(col, fila++);
            cout << "INVITADOS: " << evento.getcantidadInvitados();

            gotoxy(col, fila++);
            cout << "-------------------------------";

            if (fila > 22) break;
        }
    }

    if (!encontrado) {
        setColor(YELLOW);
        gotoxy(col, fila++);
        cout << "SIN EVENTOS REGISTRADOS";
        setColor(WHITE);
    }
}

///cancelar evento

void ManagerEvento::cancelarEventos() {
    int id;

    int CantLinea = 0, errorLinea = CantLinea + 4;

    setColor(LIGHTCYAN);
    cout << "----EVENTOS DISPONIBLES----" << endl;
    setColor(WHITE);

    ArchivoEvento arcE;
    Eventos eventos;

    int cantE = arcE.getCantidadRegistros();
    bool encontrado = false;

    for (int i = 0; i < cantE; i++) {
        eventos = arcE.leer(i);

        if (!eventos.getEliminado()) {
            cout << "~ ID: #" << eventos.getIdEvento()
                 << " " << eventos.getNombreEvento() << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        setColor(LIGHTRED);
        cout << "NO HAY EVENTOS REGISTRADOS." << endl;
        setColor(WHITE);
        return;
    }

    system("pause");
    system("cls");

    setColor(LIGHTCYAN);
    gotoxy(1, CantLinea + 1);
    cout << "INGRESAR ID EVENTO: ";
    setColor(WHITE);

    while (true) {

        gotoxy(21, CantLinea + 1);
        cout << "           ";
        gotoxy(21, CantLinea + 1);

        id = cargarEntero(21, CantLinea + 1, errorLinea);

        if (id == 0) {
            mostrarError("VUELVE AL MENU ANTERIOR", errorLinea);
            return;
        }

        break;
    }

    int pos = _repo.buscarIDEvento(id);

    if (pos == -1) {
        setColor(LIGHTRED);
        cout << "NO SE ENCONTRO EL EVENTO." << endl;
        setColor(WHITE);
        return;
    }

    eventos = _repo.leer(pos);

    if (eventos.getEliminado()) {
        setColor(LIGHTRED);
        cout << "NO SE PUEDE CANCELAR: EL EVENTO ESTA ELIMINADO." << endl;
        setColor(WHITE);
        return;
    }

    if (!eventos.getConfirmado()) {
        setColor(LIGHTRED);
        cout << "EL EVENTO YA ESTA CANCELADO." << endl;
        setColor(WHITE);
        return;
    }

    setColor(LIGHTCYAN);
    cout << "~~~~ INFORMACION DEL EVENTO ~~~~" << endl;
    setColor(WHITE);

    mostrarEvento(eventos);

    int opcion;
    setColor(LIGHTRED);
    cout << "QUIERE CANCELAR EL EVENTO? (1.SI 0.NO): ";
    setColor(WHITE);
    cin >> opcion;

    if (opcion != 1) {
        setColor(LIGHTRED);
        cout << "OPERACION CANCELADA." << endl;
        setColor(WHITE);
        return;
    }

    /// Verifica si el evento fue pagado
    ArcPagos arcPago;

    int cantPagos = arcPago.getCantidadRegistros();

    for (int i = 0; i < cantPagos; i++) {

        Pagos pago = arcPago.leer(i);

        if (!pago.getEliminado() &&
            pago.getPagado() &&
            pago.getIdEvento() == id) {

            float devolucion = pago.getMontoTotal() * 0.50f;

            setColor(YELLOW);
            cout << fixed << setprecision(2);
            cout<<endl;
            cout<<"EL EVENTO YA FUE PAGADO"<<endl;
            cout<<"SE DEVOLVERA EL 50% DEL IMPORTE"<<endl;
            cout<<"MONTO A DEVOLVER: $"<<devolucion<<endl;
            setColor(WHITE);
            break;
        }
    }

    ///cancela
    eventos.setConfirmado(false);

    if (_repo.guardar(pos, eventos)) {
        ManagerEventoServicios evs;
        evs.cancelarServiciosPorEvento(id);
        setColor(GREEN);
        cout<<"EVENTO CANCELADO CORRECTAMENTE"<<endl;
        setColor(WHITE);
    }
    else {
        setColor(LIGHTRED);
        cout<<"ERROR AL CANCELAR EL EVENTO"<<endl;
        setColor(WHITE);
    }
}

void ManagerEvento::activarEventoCancelado(){
    int id;
    int cantidad=_repo.getCantidadRegistros();

    bool encontrado=false;
    setColor(LIGHTCYAN);
    cout<<"~~~~~~ EVENTOS CANCELADOS ~~~~~~"<<endl;
    setColor(WHITE);
    for(int i=0; i<cantidad; i++){
        Eventos evento=_repo.leer(i);
        if(!evento.getConfirmado()){
            cout<<"ID: #"<<evento.getIdEvento()<<" "<<evento.getNombreEvento()<<endl;
            encontrado=true;
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
    }

    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS CANCELADOS "<<endl;
        setColor(WHITE);
        return;
    }

    system("pause");
    system("cls");

    int CantLinea=0, errorLinea=CantLinea+3;

    setColor(LIGHTCYAN);
    gotoxy(1,CantLinea+1); cout<<"INGRESAR ID EVENTO: ";

 while(true){
     setColor(WHITE);

      gotoxy(21, CantLinea + 1);
      cout << "             ";
      gotoxy(21, CantLinea + 1);

    id=cargarEntero(21,CantLinea+1,errorLinea);

    if(id==0){
       mostrarError("VUELVE AL MENU ANTERIOR ",errorLinea);
        return;
    }
    break;
 }
    int pos=_repo.buscarIDEvento(id);

    if(pos==-1){
        setColor(LIGHTRED);
        cout<<"NO SE ENCONTRO EL EVENTO "<<endl;
        setColor(WHITE);
        return;
    }

    Eventos eventos=_repo.leer(pos);

    if(eventos.getEliminado()){
        setColor(LIGHTRED);
        cout<<"NO SE PUEDE ACTIVAR: ESTA ELIMINADO "<<endl;
        setColor(WHITE);
        return;
    }

    if(eventos.getConfirmado()){
        setColor(GREEN);
        cout<<"EL EVENTO YA ESTA ACTIVO "<<endl;
        setColor(WHITE);
        return;
    }

    setColor(LIGHTCYAN);
    cout<<"~~~~ INFORMACION DEL EVENTO CANCELADO ~~~~"<<endl;
    setColor(WHITE);
    mostrarEvento(eventos);

    int opcion;
    setColor(LIGHTRED);
    cout<<"QUIERE ACTIVARLO? (1.SI / 0.NO): ";
    setColor(WHITE);
    cin>>opcion;

    if(opcion!=1){
        setColor(RED);
        cout<<"OPERACION CANCELADA"<<endl;
        setColor(WHITE);
        return;
    }

    eventos.setConfirmado(true);

    if(_repo.guardar(pos,eventos)){
        setColor(GREEN);
        cout<<"EVENTO ACTIVADO CORRECTAMENTE "<<endl;
        setColor(WHITE);
    }
}


void ManagerEvento::submenuCancelarActivar(){
  int opcion;
  do {
    system("cls");
    setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);
  cout<<"1. CANCELAR EVENTOS "<<endl;
  cout<<"2. ACTIVAR EVENTOS CANCELADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);

  cout<<"OPCION: ";
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      cancelarEventos();
      break;
  case 2:
      activarEventoCancelado();
      break;
  case 0:
    return;
default:
    setColor(RED);
    cout<<"Opcion invalida "<<endl;
    setColor(WHITE);
    break;
   }
   system("pause");
}while(opcion!=0);
}


void ManagerEvento::buscar(){
  int opcion;
  do {
    system("cls");
  setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);
  cout<<"1. BUSCAR POR ID "<<endl;
  cout<<"2. BUSCAR POR ID CLIENTE "<<endl;
  cout<<"0. SALIR "<<endl;
  setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);

  cout<<"OPCION: ";
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      buscarIdEvento();
      break;
  case 2:
      buscarEventoDeCliente();
      break;
  case 0:
    return;
default:
    setColor(RED);
    cout<<"Opcion invalida "<<endl;
    setColor(WHITE);
    break;
   }
   system("pause");
}while(opcion!=0);
}
