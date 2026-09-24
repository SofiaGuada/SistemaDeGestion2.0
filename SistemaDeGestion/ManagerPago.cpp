#include <iostream>
#include <iomanip>
#include "Necesario.h"
#include "ManagerPago.h"
#include "Fecha.h"
#include "ArchivoEvento.h"
#include "Eventos.h"
#include "ArcEventoServicios.h"
#include "EventoServicios.h"
#include "ArchivoClientes.h"
#include "Clientes.h"
#include "ManagerDetallePago.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

ManagerPago::ManagerPago()
{
    //ctor
}

float ManagerPago::CalcularElTotal(int idevento){
      float totalServicios=0;
      ArcEventoServicios ArcEventoyServicios;
      int cantEventoServicios = ArcEventoyServicios.getCantidadRegistros();

      for(int i=0;i<cantEventoServicios;i++){
            EventoServicios evSer=ArcEventoyServicios.leer(i);
            if(evSer.getIdEvento()==idevento){
                totalServicios+=evSer.getPrecioUnitario()*evSer.getCantidadContratado();
            }
      }

      ArchivoEvento arce;

      int cant=arce.getCantidadRegistros();
      float precioI=0;

      for(int i = 0; i < cant; i++){
        Eventos evento = arce.leer(i);
        if(evento.getIdEvento() == idevento){
            precioI = evento.getPrecioInicial();
                return totalServicios+precioI;
            }
        }
    return 0;
}

void ManagerPago::cargarPagos(){
    ArchivoEvento ArcEvento;
    ArchivoClientes ArcCliente;

    ///que me muestre los eventos reservados y al cliente
    setColor(LIGHTCYAN);
    cout<<"~~~~~ EVENTOS CON PAGOS PENDIENTES ~~~~~"<<endl;
    setColor(WHITE);

    int cantidad=ArcEvento.getCantidadRegistros();
    int cantClientes = ArcCliente.getCantidadRegistros();

     for(int i=0;i<cantidad;i++){
       Eventos evento = ArcEvento.leer(i);

        if (!evento.getEliminado() && !evento.getEstado()) {
            for (int j = 0; j < cantClientes; j++) {
               Clientes cliente = ArcCliente.leer(j);
                if (cliente.getIdCliente() == evento.getidCliente()) {
                   cout << "EVENTO: #" << evento.getIdEvento() << " " << evento.getNombreEvento() << endl;
                   cout << "CLIENTE: #" << cliente.getIdCliente() << " " << cliente.getNombre() << endl;
                   setColor(LIGHTCYAN);
                   cout<<"--------------------------------"<<endl;
                   setColor(WHITE);
                   break;
            }
        }
    }
}
   system("pause");
   system("cls");


   setColor(LIGHTCYAN);
    cout<<"-----REGISTRAR PAGOS----- "<<endl;

    int idEvento;
    int cantLinea=0,errorLinea=cantLinea+4;

    cout<<"ID EVENTO A PAGAR(0 CANCELAR)#: ";
    setColor(WHITE);

 while(true){
        gotoxy(32,cantLinea+2);
        cout<<"      "<<endl;
        gotoxy(32,cantLinea+2);

        idEvento=cargarEntero(32,cantLinea+2,errorLinea);

    if(idEvento==0){
        cout<<"VUELVE AL MENU ANTERIOR "<<endl;
        return;
    }
    break;
 }
    int posE=ArcEvento.buscarIDEvento(idEvento);

    if(posE==-1){
        setColor(LIGHTRED);
        cout<<"ERROR: el evento no existe "<<endl;
        return;
    }

    Eventos evento=ArcEvento.leer(posE);

    if(evento.getEstado()){
        setColor(LIGHTRED);
        cout<<"ESTE EVENTO YA ESTA PAGADO "<<endl;
        return;
    }

    int posC=ArcCliente.buscarIDcliente(evento.getidCliente());
    Clientes cliente=ArcCliente.leer(posC);

    cout<<"CLIENTE: "<<cliente.getNombre()<<endl;
    cout<<"EVENTO: "<<evento.getNombreEvento()<<endl;

    float total= CalcularElTotal(idEvento);
    cout<<fixed<<setprecision(2);
    setColor(LIGHTBLUE);
    cout<<"TOTAL A PAGAR: $"<<total<<endl;

    int idP=_repo.getNuevoIdPago();
//    cout<<"ID PAGO: #"<< idP <<endl;
    Fecha fechaPago;
    Fecha fechaEvento=evento.getFechaEvento();
    string metodo;

     int opcion;
     setColor(LIGHTCYAN);
     cout<<"ELIJA EL METODO DE PAGO "<<endl;
     cout<<"1. Efectivo "<<endl;
     cout<<"2. Tarjeta "<<endl;
     cout<<"3. Transferencia "<<endl;
     setColor(WHITE);
     cout<<"Opcion: ";
     cin>>opcion;

      switch(opcion){
    case 1:
        metodo="Efectivo";
        break;
    case 2:
        metodo="Tarjeta";
        break;
    case 3:
        metodo="Transferencia";
        break;
    default:
        setColor(LIGHTRED);
        cout<<"OPCION INCORRECTA "<<endl;
        cout<<"SE ASIGNA 'Efectivo' "<<endl;
        metodo="Efectivo";
        break;
      }
    cout<<"FECHA DE PAGO: ";
    fechaPago.cargarFecha();

    bool atrasado=false;
    if(fechaPago > fechaEvento&& !evento.getEliminado()){
        atrasado=true;
        setColor(LIGHTRED);
        cout<<" PAGO ATRASADO "<<endl;
        setColor(WHITE);
    }

     Pagos pagos(idP,cliente.getIdCliente(),idEvento,fechaPago,total,metodo,true,atrasado);
     pagos.setEliminado(false);

  if(_repo.guardar(pagos)){
        evento.setEstado(true);
        ArcEvento.guardar(posE,evento);

        ManagerDetallePago MDPago;
        MDPago.cargarDetallePagos(idEvento,idP);
        setColor(LIGHTGREEN);
        cout<<"PAGO GUARDADO CORRECTAMENTE. "<<endl;
  }
  else{
    setColor(LIGHTRED);
    cout<<"ERROR AL GUARDAR PAGOS. "<<endl;
  }
}

void ManagerPago::mostrarPagos(Pagos pago){
    cout<<"ID PAGO: #"<<pago.getIdPago()<<endl;
    cout<<"ID CLIENTE: #"<<pago.getIdCliente()<<endl;
    cout<<"ID EVENTO: #"<<pago.getIdEvento()<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"TOTAL: $"<<pago.getMontoTotal()<<endl;
    cout<<"METODO DE PAGO: "<<pago.getMetodoPago()<<endl;
    cout<<"FECHA DE PAGO: ";
    pago.getFechaPago().mostrarFecha();
    cout<<"ESTADO: ";

     if(pago.getPagado()) {
        setColor(LIGHTGREEN);
        cout<<" PAGADO ";
        }
     else {
       setColor(LIGHTRED);
       cout<<" PENDIENTE ";
    }

     setColor(WHITE);
     cout<<endl;

    cout<<"ELIMINADO: "<<(pago.getEliminado() ? " Si " : " No ")<< endl;
}

void ManagerPago::listarPagos(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;

  setColor(LIGHTCYAN);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~";
  cout<<"~~~~~ PAGOS REGISTRADOS ~~~~~";
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  setColor(WHITE);


  for (int i = 0; i < cantidad; i++){
    Pagos pago = _repo.leer(i);
  if(!pago.getEliminado()){
      mostrarPagos(pago);
      encontrado=true;
      setColor(LIGHTCYAN);
      cout << "--------------------------" << endl;
      setColor(WHITE);
  }
}
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
  }
}

void ManagerPago::buscarIdPagos(){
    int id;
    int cantLinea=0,errorLinea=cantLinea+4;

    setColor(LIGHTCYAN);
    cout<<"BUSCAR PAGOS POR ID "<<endl;

    cout<<"INGRESAR ID PAGO:# ";
    setColor(WHITE);

 while(true){
     gotoxy(20,cantLinea+2);
     cout<<"     "<<endl;
     gotoxy(20,cantLinea+2);

     id=cargarEntero(20,cantLinea+2,errorLinea);

    if(id<=0){
        mostrarError ("NO PUEDE SER MENOR O IGUAL A 0 ",errorLinea);
        continue;
    }
    break;
 }

    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;

    setColor(LIGHTCYAN);
    cout<<"-----PAGOS ENCONTRADO-----"<<endl;
    setColor(WHITE);

    for(int i = 0; i < cantidad; i++) {
        Pagos p = _repo.leer(i);
        if( p.getIdPago() == id) {
            mostrarPagos(p);
            setColor(LIGHTCYAN);
            cout<<"---------------------------"<<endl;
            setColor(WHITE);
            encontrado = true;
        }
    }
    if(!encontrado) {
        setColor(LIGHTRED);
        cout<<"NO SE ENCONTRO EL PAGO."<<endl;
        setColor(WHITE);
    }
}

void ManagerPago::buscarPorCliente(){
   int id;
   int cantLinea=0,errorLinea=cantLinea+4;

   setColor(LIGHTCYAN);
   cout<<"BUSCAR POR ID CLIENTE "<<endl;
   cout<<"INGRESE ID CLIENTE: ";
   setColor(WHITE);

  while(true){
     gotoxy(20,cantLinea+2);
     cout<<"     "<<endl;
     gotoxy(20,cantLinea+2);

     id=cargarEntero(20,cantLinea+2,errorLinea);

    if(id<=0){
        mostrarError ("NO PUEDE SER MENOR O IGUAL A 0 ",errorLinea);
        continue;
    }
    break;
 }
   int cantidad=_repo.getCantidadRegistros();
   bool encontrado=false;

    setColor(LIGHTCYAN);
    cout<<"-----PAGO ENCONTRADO-----"<<endl;
    setColor(WHITE);

      for(int i=0;i<cantidad;i++){
        Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            if(pago.getIdCliente()==id){
                mostrarPagos(pago);
                setColor(LIGHTCYAN);
                cout<<"-----------------------"<<endl;
                setColor(WHITE);
                encontrado=true;
            }
        }
      }
        if(!encontrado){
            setColor(LIGHTRED);
            cout<<"NO SE ENCONTRO "<<endl;
        }
}

void ManagerPago::buscarXfecha(){
  Fecha abuscar;

   setColor(LIGHTCYAN);
   cout<<"BUSCAR POR FECHA "<<endl;
   cout<<"INGRESE FECHA: ";
   setColor(WHITE);

   abuscar.cargarFecha();

   int cantidad=_repo.getCantidadRegistros();

   bool encontrado=false;

   system("pause");
   system("cls");

   setColor(LIGHTCYAN);
   cout<<"LA FECHA A BUSCAR ES: ";
   setColor(WHITE);
   abuscar.mostrarFecha();
   cout<<endl;

   for(int i=0;i<cantidad;i++){
    Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            if(pago.getFechaPago()==abuscar){
                setColor(LIGHTCYAN);
                cout<<"-----PAGO ENCONTRADO-----"<<endl;
                setColor(WHITE);
                mostrarPagos(pago);
                setColor(LIGHTCYAN);
                cout<<"-----------------------"<<endl;
                setColor(WHITE);
                encontrado=true;
            }
        }
   }
        if(!encontrado){
            setColor(LIGHTRED);
            cout<<"NO HAY PAGOS EN LA FECHA INGRESADA "<<endl;
        }
}

void ManagerPago::eliminar(){
int opcion;
   do{
    system("cls");
    setColor(LIGHTCYAN);
    cout<<"~~~~ ELIMINAR PAGOS ~~~~~"<<endl;
    setColor(WHITE);
    cout<<"1. ELIMINAR "<<endl;
    cout<<"2. MOSTRAR ELIMINADOS "<<endl;
    cout<<"0. VOLVER A MENU PAGOS "<<endl;
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);
    cout<<"OPCION: ";
    cin>>opcion;

    system("cls");
    switch(opcion){
    case 1:
        eliminarPago();
        break;
    case 2:
         mostrarEliminados();
        break;
    case 0:
        break;
    default:
        cout<<"OPCION INCORRECTA, INTENTE NUEVAMENTE "<<endl;
        break;
    }
    system("pause");
   }while(opcion!=0);
}

void ManagerPago::eliminarPago(){
    int id,pos;
   Pagos pago;
   char eliminar;

   setColor(LIGHTCYAN);
   cout<<" ~~PAGOS DISPONIBLES~~ "<<endl;
   setColor(WHITE);

   bool encontrado=false;
   int cantidad=_repo.getCantidadRegistros();

   for(int i=0;i<cantidad;i++){
        pago=_repo.leer(i);
      if(!pago.getEliminado()){
         cout << fixed << setprecision(2);
         cout<<"ID: #"<<pago.getIdPago()<<" ($"<<pago.getMontoTotal()<<")"<<endl;
         encontrado=true;
      }
   }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
        return;
    }

    system("pause");
    system("cls");

    int cantLinea=0,errorLinea=cantLinea+4;

   setColor(LIGHTCYAN);
   cout<<"---- ELIMINAR PAGO ----"<<endl;
   cout<<"INGRESE ID PAGO: #";

 while(true){
       gotoxy(20,cantLinea+2);
       cout<<"       "<<endl;
       gotoxy(20,cantLinea+2);

       id=cargarEntero(20,cantLinea+2,errorLinea);

    if(id==0){
        mostrarError ("VUELVE AL MENU ANTERIOR ",errorLinea);
        return;
    }
    break;
 }
    pos=_repo.buscarIdPago(id);

   if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL PAGO NO EXISTE! "<<endl;
    return ;
  }

  pago= _repo.leer(pos);

  setColor(LIGHTCYAN);
  cout<<"INFORMACION DEL PAGO "<<endl;
  cout<<endl;
  setColor(WHITE);
  mostrarPagos(pago);

  cout<<endl;

  setColor(LIGHTCYAN);
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    setColor(LIGHTGREEN);
    cout<<"EL PAGO FUE ELIMINADO"<<endl;
  }
  else {
    setColor(LIGHTRED);
    cout<<"OCURRIO UN ERROR AL ELIMINAR EL PAGO "<<endl;
  }
  }
}

void ManagerPago::mostrarEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cantidad;i++){
        Pagos pago=_repo.leer(i);
       if(pago.getEliminado()){
        mostrarPagos(pago);
        encontrado=true;
        return;
       }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY PAGOS ELIMINADOS "<<endl;
        return;
    }
}

void ManagerPago::modificarPago() {
    int id;
    int cantLinea=0, errorLinea=cantLinea+4;

    setColor(LIGHTCYAN);
    cout<<"---- PAGOS REALIZADOS ----"<<endl;
    setColor(WHITE);

    int cant=_repo.getCantidadRegistros();
    bool encontrado=false;
    for(int i=0;i<cant;i++){
        Pagos pago=_repo.leer(i);
        if(!pago.getEliminado() && pago.getPagado()){
            cout << fixed << setprecision(2);
            cout<<"ID PAGO: #"<<pago.getIdPago()<<" | ID EVENTO: #"<<pago.getIdEvento()<<" ($"<<pago.getMontoTotal()<<")"<<endl;
            encontrado=true;
        }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY PAGOS REALIZADOS "<<endl;
        return;
    }
    system("pause");
    system("cls");

    setColor(LIGHTCYAN);
    cout<<"INGRESE EL ID PAGO A MODIFICAR:#";
    setColor(WHITE);

  while(true){
        gotoxy(34,cantLinea+1);
        cout<<"     "<<endl;
        gotoxy(34,cantLinea+1);

        id=cargarEntero(34,cantLinea+1,errorLinea);

    if(id<=0){
        mostrarError ("NO PUEDE SER MENOR O IGUAL A 0",errorLinea);
        continue;
    }
    break;
 }
    int pos = _repo.buscarIdPago(id);
    if(pos == -1) {
        setColor(LIGHTRED);
        cout << "PAGO NO ENCONTRADO " << endl;
        return;
    }

    Pagos pago = _repo.leer(pos);

    if(!pago.getEliminado()){
    mostrarPagos(pago);
    }
    else{
        setColor(LIGHTRED);
        cout<<"Este Pago esta Eliminado "<<endl;
        return;
    }

    system("pause");
    system("cls");

    int opcion;

    do {
        setColor(LIGHTCYAN);
        cout << "------ MODIFICAR PAGO ------" << endl;
        setColor(WHITE);
        ///no se puede modificar los id ya que se generan automaticamente
        cout << "1. CAMBIAR METODO DE PAGO" << endl;
        cout << "2. CAMBIAR FECHA DE PAGO" << endl;
        cout << "3. CAMBIAR ESTADO (Pagado / Pendiente)" << endl;
        cout << "0. GUARDAR Y SALIR" << endl;
        cout << "OPCION: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {

        case 1: {
             int opcionM;
             setColor(LIGHTCYAN);
             cout<<"~~~~~METODOS DISPONIBLES~~~~~"<<endl;
             setColor(WHITE);
             cout<<" 1. EFECTIVO "<<endl;
             cout<<" 2. TARJETA "<<endl;
             cout<<" 3. TRANSFERENCIA O MERCADO PAGO "<<endl;
             cout<<" 0. Salir "<<endl;

             cout<<"OPCION: ";

             while (true) {
                cin>>opcionM;

             if (opcionM >= 0 && opcionM <= 3)
                 break;

             setColor(LIGHTRED);
             cout<<"OPCION INCORRECTA"<<endl;
              setColor(WHITE);
           }
             system("cls");
        switch(opcionM){
             case 1:
                 pago.setMetodoPago("Efectivo");
                break;
             case 2:
                pago.setMetodoPago("Tarjeta");
                break;
             case 3:
                pago.setMetodoPago("Transferencia");
                break;
             case 0:
                break;
              }

      break;
        }
    case 2: {
            Fecha nuevaFecha;
            setColor(LIGHTCYAN);
            cout << "NUEVA FECHA DE PAGO: " << endl;
            setColor(WHITE);
            nuevaFecha.cargarFecha();
            pago.setFechaPago(nuevaFecha);

            system("cls");

        continue;
     }

        case 3: {
             int opcionE;
             setColor(LIGHTCYAN);
             cout<<"---ESTADO DEL PAGO--- "<<endl;
             setColor(WHITE);
             cout<<" 1. PAGADO "<<endl;
             cout<<" 2. PENDIENTE "<<endl;
             cout<<" 0. SALIR "<<endl;
             cout<<"OPCION: ";
           while (true) {
              cin >> opcionE;

           if (opcionE >= 0 && opcionE <= 2)
                break;

            setColor(LIGHTRED);
            cout<<"OPCION INCORRECTA"<<endl;
            setColor(WHITE);
        }
             system("cls");

             if(opcionE==1)pago.setPagado(true);
             else if(opcionE==2)pago.setPagado(false);
             else{
                setColor(LIGHTRED);
                cout<<"OPCION INCORRECTA "<<endl;
             }
        break;
 }
        case 0:
            break;

        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
}
    system("pause");

    } while (opcion != 0);

    if (_repo.guardar(pos, pago)) {
        setColor(LIGHTGREEN);
        cout<<"PAGO MODIFICADO CORRECTAMENTE"<<endl;
    } else {
        setColor(LIGHTRED);
        cout<<"ERROR AL GUARDAR CAMBIOS"<<endl;
    }
}

void ManagerPago::Activar(){
  int id, pos;
  char eliminar;
  int cantidad=_repo.getCantidadRegistros();
  bool encontrado=false;

    setColor(LIGHTCYAN);
    cout<<"~~PAGOS ELIMINADOS~~ "<<endl;
    setColor(WHITE);

    for(int i=0;i<cantidad;i++){
    Pagos pago=_repo.leer(i);
    if(pago.getEliminado()){
        cout << fixed << setprecision(2);
        cout<<"~ID: #"<<pago.getIdPago()<<" $"<<pago.getMontoTotal()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY PAGOS ELIMINADOS "<<endl;
    return;
  }
  system("pause");
  system("cls");

  int cantLinea=0, errorLinea=cantLinea+4;

  setColor(LIGHTCYAN);
  cout<<"~~~~ ACTIVAR PAGO ~~~~"<<endl;
  cout<<"ID PAGO:#";
  setColor(WHITE);

 while(true){
     gotoxy(11,cantLinea+2);
     cout<<"     "<<endl;
     gotoxy(11,cantLinea+2);

     id=cargarEntero(11,cantLinea+2,errorLinea);


    if(id<=0){
        mostrarError("NO PUEDE SER MENOR O IGUAL A 0 ",errorLinea);
        continue;
    }
    break;
 }

  pos=_repo.buscarIdPago(id);
  if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL PAGO NO EXISTE "<<endl;
    return;
  }
  Pagos pago;
  pago= _repo.leer(pos);
    if(!pago.getEliminado()){
    setColor(LIGHTRED);
    cout<<"ERROR: EL PAGO NO ESTA ELIMINADO "<<endl;
    cout<<"No es necesario activar "<<endl;
    return;
  }

  setColor(LIGHTCYAN);
  cout<<"INFORMACION DEL PAGO ELIMINADO "<<endl;
  cout<<endl;
  setColor(WHITE);
  mostrarPagos(pago);
  cout<<endl;

  setColor(LIGHTCYAN);
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  setColor(WHITE);
  cin>>eliminar;

   if(eliminar=='s' or eliminar=='S'){
    pago.setEliminado(false);
   }
   if(_repo.guardar(pos,pago)){
    setColor(LIGHTGREEN);
    cout<<"GUARDADO CORRECTAMENTE "<<endl;
   }
   else {
    setColor(LIGHTRED);
    cout<<"OCURRIO UN ERROR "<<endl;
   }
}

void ManagerPago::calcularTotalAnual() {
    int anio;
    int cantLinea = 0, errorLinea = cantLinea + 4;

    setColor(LIGHTCYAN);
    cout << "INGRESAR ANIO: ";

    while (true) {
        gotoxy(16, cantLinea + 1);
        cout << "      ";
        gotoxy(16, cantLinea + 1);

        anio = cargarEntero(16, cantLinea + 1, errorLinea);

        if (anio <= 0) {
            mostrarError("EL ANIO DEBE SER MAYOR A 0", errorLinea);
            continue;
        }
        break;
    }

    int cantPagos = _repo.getCantidadRegistros();

    if (cantPagos == 0) {
        setColor(LIGHTRED);
        cout << "NO HAY PAGOS REGISTRADOS." << endl;
        setColor(WHITE);
        return;
    }

    ArchivoEvento arcEvento;

    float totalAnual = 0;

    for (int i = 0; i < cantPagos; i++) {
        Pagos pago = _repo.leer(i);
        if (pago.getEliminado() || !pago.getPagado())
            continue;
         if (pago.getFechaPago().getAnio() != anio)
             continue;

        int posEvento = arcEvento.buscarIDEvento(pago.getIdEvento());
        if (posEvento == -1)
            continue;
        Eventos evento = arcEvento.leer(posEvento);
           if (evento.getConfirmado()) {
              /// Evento realizado
              totalAnual += pago.getMontoTotal();
          }
           else {
             totalAnual += pago.getMontoTotal() * 0.50f;
        }
    }

    setColor(LIGHTBLUE);
    cout << fixed << setprecision(2);
    cout<<"RECAUDACION TOTAL DEL ANIO "<<anio<<": $"<<totalAnual<<endl;
    setColor(WHITE);
}

float ManagerPago::calcularRecaudacionCliente(int idCliente) {

    ArchivoEvento arcEvento;

    int cantEventos = arcEvento.getCantidadRegistros();
    int cantPagos = _repo.getCantidadRegistros();

    float total = 0;

    for (int i = 0; i < cantEventos; i++) {
        Eventos evento = arcEvento.leer(i);
        if (evento.getEliminado() || evento.getidCliente() != idCliente)
            continue;

        bool pagado = false;

        for (int j = 0; j < cantPagos; j++) {
            Pagos pago = _repo.leer(j);
            if (!pago.getEliminado() &&
                pago.getPagado() &&
                pago.getIdEvento() == evento.getIdEvento()) {
                pagado = true;
                break;
            }
        }
        if (pagado) {
            float totalEvento = CalcularElTotal(evento.getIdEvento());
            if (evento.getConfirmado()) {
                total += totalEvento;
            }
            else {
                total += totalEvento * 0.50f;
            }
        }
    }
    return total;
}

void ManagerPago::mostrarRecaudacionxCliente() {

    ArchivoClientes arcCliente;
    int cantClientes = arcCliente.getCantidadRegistros();

    setColor(LIGHTCYAN);
    cout << "------ RECAUDACION POR CLIENTE ------" << endl;
    setColor(WHITE);

    for (int i = 0; i < cantClientes; i++) {
        Clientes cliente = arcCliente.leer(i);
        if (cliente.getEliminado())
            continue;
        float total = calcularRecaudacionCliente(cliente.getIdCliente());

        if (total > 0) {
            cout<<"CLIENTE: #"<<cliente.getIdCliente()<< " - "<< cliente.getNombre()<< " "<< cliente.getApellido()<<endl;
            cout<<fixed<<setprecision(2);
            setColor(LIGHTCYAN);
            cout<<"TOTAL RECAUDADO: $"<<total<<endl<<endl;
            setColor(WHITE);
        }
    }
}

void ManagerPago::recaudacionTipoEvento() {

    ArchivoEvento arcEventos;

    int cantEventos = arcEventos.getCantidadRegistros();
    int cantPagos = _repo.getCantidadRegistros();

    if (cantEventos == 0 || cantPagos == 0) {
        setColor(LIGHTRED);
        cout<<"NO HAY DATOS PARA GENERAR EL INFORME"<<endl;
        setColor(WHITE);
        return;
    }

    float totalPorTipo[5] = {0};

    for (int i = 0; i < cantPagos; i++) {
        Pagos pago = _repo.leer(i);
        if (!pago.getEliminado() && pago.getPagado()) {
            int posEvento = arcEventos.buscarIDEvento(pago.getIdEvento());
            if (posEvento != -1) {
                Eventos ev = arcEventos.leer(posEvento);
                int tipo = ev.getTipoEvento();
                if (tipo >= 0 && tipo < 5) {
                    if (ev.getConfirmado()) {
                        /// El Evento se realiza
                        totalPorTipo[tipo] += pago.getMontoTotal();
                    }
                    else {
                        /// El Evento es cancelado: se devuelve el 50%
                        totalPorTipo[tipo] += pago.getMontoTotal() * 0.50f;
                    }
                }
            }
        }
    }

    const char* nombres[5] = {
        "BODA",
        "CUMPLEANIOS",
        "EMPRESARIAL",
        "BAUTISMO/COMUNION",
        "GRADUACION"
    };

    bool encontrado = false;

    setColor(LIGHTCYAN);
    cout<<"----- RECAUDACION POR TIPO DE EVENTO -----"<<endl;
    setColor(WHITE);

    for (int i = 0; i < 5; i++) {
        if (totalPorTipo[i] > 0) {
            encontrado = true;
            cout<<nombres[i]<< ": $"<<fixed << setprecision(2)<< totalPorTipo[i]<<endl;
        }
    }

    if (!encontrado) {
        setColor(LIGHTRED);
        cout<<"NO HAY RECAUDACION REGISTRADA"<<endl;
        setColor(WHITE);
    }
}

void ManagerPago::listarPendientes(){
    ArchivoEvento ArcEvento;
    ArchivoClientes ArcCliente;

    setColor(LIGHTCYAN);
    cout<<"~~~~~ EVENTOS CON PAGOS PENDIENTES ~~~~~"<<endl;
    setColor(WHITE);
    int cantidad=ArcEvento.getCantidadRegistros();
    int cantClientes = ArcCliente.getCantidadRegistros();
    bool hay=false;
     for(int i=0;i<cantidad;i++){
       Eventos evento = ArcEvento.leer(i);

        if (!evento.getEliminado() && !evento.getEstado()) {
            for (int j = 0; j < cantClientes; j++) {
               Clientes cliente = ArcCliente.leer(j);
                if (cliente.getIdCliente() == evento.getidCliente()) {
                   cout << "EVENTO: #" << evento.getIdEvento() << " " << evento.getNombreEvento() << endl;
                   cout << "CLIENTE: #" << cliente.getIdCliente() << " " << cliente.getNombre() << endl;
                   setColor(LIGHTCYAN);
                   cout<<"--------------------------------"<<endl;
                   setColor(WHITE);
                   hay=true;
                   break;
            }
        }
    }
}
       if(!hay){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS PENDIENTES "<<endl;
       }
}

void ManagerPago::listarAtrasados(){
    ArchivoEvento arc;
   int cantidadP=_repo.getCantidadRegistros();

   if(cantidadP ==0){
    setColor(LIGHTRED);
    cout<<"NO HAY PAGOS REGISTRADOS "<<endl;
    return;
   }
   setColor(LIGHTCYAN);
   cout<<"------PAGOS ATRASADOS------"<<endl;
   setColor(WHITE);
   bool hay=false;

   for(int i=0;i<cantidadP;i++){
    Pagos pago=_repo.leer(i);
    if(!pago.getEliminado()){
        int posEvento=arc.buscarIDEvento(pago.getIdEvento());
        if(posEvento!=-1){
            Eventos evento=arc.leer(posEvento);
            Fecha FechaPago=pago.getFechaPago();
            Fecha FechaEvento=evento.getFechaEvento();
            if(FechaPago > FechaEvento){
                hay=true;
                cout<<"ID PAGO: #"<<pago.getIdPago()<<endl;
                cout<<" ~ EVENTO: "<<evento.getNombreEvento()<<endl;
                cout<<" ~ MONTO: $"<<pago.getMontoTotal()<<endl;
            }
        }
    }
   }
   if(!hay){
    setColor(LIGHTRED);
    cout<<" NO HAY PAGOS ATRASADOS "<<endl;
   }
}

void ManagerPago::submenuPago(){
 int opcion;
 do{
    system("cls");
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);
    cout<<"1. TOTAL ANUAL "<<endl;
    cout<<"2. TOTAL POR CLIENTE "<<endl;
    cout<<"3. TOTAL POR TIPO DE EVENTO "<<endl;
    cout<<"0. volver al menu pagos"<<endl;
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"OPCION: ";
    setColor(WHITE);
    cin>>opcion;

    system("cls");
    switch(opcion){
    case 1:
        calcularTotalAnual();
        break;
    case 2:
        mostrarRecaudacionxCliente();
        break;
    case 3:
        recaudacionTipoEvento();
        break;
    case 0:
        break;
    default:
        cout<<"Opcion incorrecta, volve a intentar "<<endl;
        break;
    }
    system("pause");
 }while (opcion!=0);
}

void ManagerPago::buscar(){
     int opcion;
 do{
    system("cls");
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);
    cout<<"1. BUSCAR POR ID "<<endl;
    cout<<"2. BUSCAR ID CLIENTE "<<endl;
    cout<<"3. BUSCAR POR FECHA "<<endl;
    cout<<"0. volver al menu anterior"<<endl;
    setColor(LIGHTCYAN);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);
    cout<<"OPCION: ";
    cin>>opcion;

    system("cls");
    switch(opcion){
    case 1:
       buscarIdPagos();
        break;
    case 2:
        buscarPorCliente();
        break;
    case 3:
        buscarXfecha();
        break;

    case 0:
        break;
    default:
        cout<<"Opcion incorrecta, volve a intentar "<<endl;
        break;
    }
    system("pause");
 }while (opcion!=0);
}

void ManagerPago::mostrarPagosxEstados(){
   int opcion;
   do{
    system("cls");
   setColor(LIGHTCYAN);
   cout<<"1. LISTAR PAGADOS "<<endl;
   cout<<"2. LISTAR PENDIENTES "<<endl;
   cout<<"3. LISTAR ATRASADOS "<<endl;
   cout<<"0. SALIR "<<endl;
   cout<<"OPCION: ";
   cin>>opcion;
   system("cls");
   switch(opcion){
   case 1:
       listarPagos();
    break;
   case 2:
    listarPendientes();
    break;
   case 3:
   listarAtrasados();
    break;
   case 0:
    break;
   default:
       cout<<"Opcion incorrecta "<<endl;
    break;
   }

    system("pause");
   }while(opcion!=0);

}

