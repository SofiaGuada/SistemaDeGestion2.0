# include<iostream>
#include <iomanip>
#include "ManagerEventoServicios.h"
#include "ArchivoEvento.h"
#include "Eventos.h"
#include "ArchivoServicios.h"
#include "Servicios.h"
#include "ArcPagos.h"
#include "rlutil.h"
#include "Necesario.h"

using namespace std;
using namespace rlutil;

ManagerEventoServicios::ManagerEventoServicio()
{
    //ctor
}

void ManagerEventoServicios::cargarEventosyServicios(){
    int idE,idS,cantidad;

    ArchivoEvento arcE;
    int cant = arcE.getCantidadRegistros();

      if (cant==0){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS REGISTRADOS. "<<endl;
        setColor(WHITE);
        return;
      }

     setColor(LIGHTCYAN);
     cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
     setColor(WHITE);

     bool encontrado=false;
      for(int i=0;i<cant;i++){
        Eventos evento=arcE.leer(i);
        if(!evento.getEliminado() && evento.getConfirmado()){
            encontrado=true;
            cout<<"ID EVENTO: #"<<evento.getIdEvento()<<"| ID CLIENTE: #"<<evento.getidCliente()<<"|"<<endl;
            cout<<"TIPO DE EVENTO: ";
              switch(evento.getTipoEvento()){
                 case 0: cout<<"Boda"; break;
                 case 1: cout<<"Cumpleanios"; break;
                 case 2: cout<<"Empresarial"; break;
                 case 3: cout<<"Bautismos, Comunion"; break;
                 case 4: cout<<"Graduacion"; break;
                 }
            cout<<endl;
            cout<<"CANTIDAD DE INVITADOS: "<<evento.getcantidadInvitados()<<endl;
            setColor(LIGHTCYAN);
            cout<<"-------------------------------"<<endl;
            setColor(WHITE);
        }
      }

      if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS DISPONIBLES PARA AGREGAR SERVICIOS "<<endl;
        return;
      }
		system("pause");
		system("cls");

		int cantLinea=0, errorLinea=cantLinea+4;

		setColor(LIGHTCYAN);
        cout<<"INGRESAR EL ID EVENTO(0 para volver): ";
        setColor(WHITE);

    while(true){
        gotoxy(38,cantLinea+1);
        cout<<"       ";
        gotoxy(38,cantLinea+1);

        idE=cargarEntero(38,cantLinea+1,errorLinea);

		if(idE==0){
            return;
		}

		bool Eventoexistente=false;

		for(int i=0;i<cant;i++){
            Eventos evento=arcE.leer(i);
            if(evento.getIdEvento()==idE && !evento.getEliminado() && evento.getConfirmado()){
                Eventoexistente=true;
                break;
            }
		}
		if(!Eventoexistente){
            mostrarError("EL EVENTO NO EXISTE ",errorLinea);
            continue;
		}
		break;
    }
		bool hayserviciosEv=false;

		int CantEvS=_repo.getCantidadRegistros();
		setColor(LIGHTCYAN);
        cout<<"---- SERVICIOS DEL EVENTO ----"<<endl;
        setColor(WHITE);

		for(int i=0;i<CantEvS;i++){
            EventoServicios EvenSer=_repo.leer(i);
            if(EvenSer.getIdEvento()==idE && !EvenSer.getEliminado()){
                cout << fixed << setprecision(2);
                cout<<"ID SERVICIO:#"<<EvenSer.getIdServicio()<<" (CANTIDAD: "<<EvenSer.getCantidadContratado()<<") $"<<EvenSer.getPrecioUnitario()<<endl;
                hayserviciosEv=true;
            }
		}
		if(!hayserviciosEv){
            setColor(LIGHTRED);
            cout<<"ESTE EVENTO NO TIENE SERVICIOS ASOCIADOS "<<endl<<endl;
            setColor(WHITE);
		}

		cout<<endl;
///---------------------
		char continuar;

		setColor(LIGHTCYAN);
        cout<<"QUIERE AGREGAR SERVICIOS AL EVENTO ? (s/n) ";
        setColor(WHITE);
		cin>>continuar;


        if(continuar=='n'|| continuar=='N'){
            setColor(RED);
            cout<<"NO SE AGREGAN SERVICIOS AL EVENTO "<<endl;
            return;
            }

         ArchivoServicios arcS;

		int Cant= arcS.getCantidadRegistros();

		if (Cant==0){
            setColor(LIGHTRED);
			cout<<"NO HAY SERVICIOS REGISTRADOS "<<endl;
			return;
		}

		while (continuar=='s'||continuar=='S'){

		setColor(LIGHTCYAN);
		cout<<"--- SERVICIOS DISPONIBLES ---"<<endl;

		setColor(WHITE);
		for(int i=0;i<Cant;i++){
			Servicios servis=arcS.leer(i);
			if(!servis.getEliminado()){
				cout<<"ID SERVICIO: #"<<servis.getIdServicio()<<endl;
				cout<<"NOMBRE: "<<servis.getNombreServicio()<<endl;
				cout<<"DESCRIPCION: "<<servis.getDescripcion()<<endl;
				cout<<"PROVEEDOR: "<<servis.getProveedor()<<endl;
                cout<<fixed<<setprecision(2);
				cout<<"PRECIO: $"<<servis.getPrecio()<<endl;
				setColor(LIGHTCYAN);
				cout<<"-------------------------------"<<endl;
				setColor(WHITE);
			}
		}
        system("pause");
		system("cls");

		setColor(LIGHTGREEN);
		cout<<"~~~~ AGREGAR SERVICIOS AL EVENTO ~~~~"<<endl;
		setColor(WHITE);

     gotoxy(1,cantLinea+2); cout<<"ID SERVICIO: #";

   while (true) {
        gotoxy(13,cantLinea+2);
        cout<<"    ";
        gotoxy(13,cantLinea+2);

        idS=cargarEntero(13,cantLinea+2,errorLinea);


    bool existe=false;

    for (int i=0; i<Cant; i++) {
        Servicios ser=arcS.leer(i);
        if (ser.getIdServicio()==idS && !ser.getEliminado()){
            existe=true;
            break;
        }
    }
    if (!existe) {
        setColor(LIGHTRED);
        cout<<"Intente nuevamente "<<endl;
        setColor(WHITE);
        continue;
    }
    break;
}

 gotoxy(1,cantLinea+3); cout<<"CANTIDAD: ";

    while(true){
        gotoxy(10,cantLinea+3);
        cout<<"      ";
        gotoxy(10,cantLinea+3);

        cantidad=cargarEntero(10,cantLinea+3,errorLinea);

        break;
    }

    bool duplicado=false;

    int canti=_repo.getCantidadRegistros();

    for(int i=0; i<canti; i++) {
         EventoServicios ev = _repo.leer(i);
      if(!ev.getEliminado()&&ev.getIdEvento()==idE &&ev.getIdServicio()==idS){
         duplicado=true;
         break;
       }
    }

    if(duplicado){
       setColor(LIGHTRED);
       cout<<" ESTE SERVICIO YA ESTA ASOCIADO AL EVENTO "<<endl;

       setColor(LIGHTCYAN);
       cout<<"Desea intentar con otro servicio? (s/n): ";
       setColor(WHITE);
       cin>>continuar;

    if(continuar =='s' || continuar == 'S')
           continue;
    else{
        return;
        }
    }
        float precioUnitario=0;
		string nombreEvento,nombreServicio;

		for(int i=0;i<Cant;i++){
			Servicios servi =arcS.leer(i);
			if(servi.getIdServicio()==idS ){
                cout<<fixed<<setprecision(2);
				precioUnitario=servi.getPrecio();
				nombreServicio=servi.getNombreServicio();
			}
		}
		for(int i=0;i<cant;i++){
			Eventos eve =arcE.leer(i);
			if(eve.getIdEvento()==idE){
				nombreEvento=eve.getNombreEvento();
			}
		}

    EventoServicios eventoServis(idE,idS,cantidad,precioUnitario,nombreEvento,nombreServicio);

		if(_repo.guardar(eventoServis)){
            setColor(GREEN);
			cout<<" GUARDADO CORRECTAMENTE "<<endl;
		}
		else {
		    setColor(RED);
			cout<<" HUBO UN ERROR AL GUARDAR "<<endl;
			setColor(WHITE);
		}

		setColor(LIGHTCYAN);
		cout<<"QUIERE AGREGAR MAS SERVICIOS AL EVENTO ? (s/n) ";
		setColor(WHITE);
		cin>>continuar;
}
}


void ManagerEventoServicios::mostrarEventoyServicios(EventoServicios Evenservis){
    float total= Evenservis.getCantidadContratado()*Evenservis.getPrecioUnitario();
      cout<<"ID EVENTO: #"<<Evenservis.getIdEvento()<<" "<<Evenservis.getNombreEvento()<<endl;
      cout<<"ID SERVICIO: #"<<Evenservis.getIdServicio()<<" "<<Evenservis.getNombreServicios()<<endl;
      cout<<"CANTIDAD: "<<Evenservis.getCantidadContratado()<<endl;
      cout<<"PRECIO: $"<<Evenservis.getPrecioUnitario()<<endl;
      cout<<fixed<<setprecision(2);
      cout<<"TOTAL DEL SERVICIOS: $"<<total<<endl;
      if(Evenservis.getEliminado()){
        setColor(LIGHTRED);
        cout<<"[ELIMINADO] "<<endl;
        setColor(WHITE);
      }
}

void ManagerEventoServicios::mostrarEventoCompleto(int idEvento){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    setColor(LIGHTCYAN);
    cout<<"~~~~ EVENTO #"<<idEvento<<" ~~~~"<<endl;
    setColor(WHITE);

    for (int i=0; i<cantidad; i++) {
        EventoServicios es=_repo.leer(i);
        if(es.getIdEvento()==idEvento && es.getEliminado()){
            if(!encontrado){
                setColor(LIGHTCYAN);
                cout<<"Servicios eliminados del evento:"<<endl;
                setColor(WHITE);
                encontrado=true;
            }
            cout<<" - Servicio #"<<es.getIdServicio()<<" "<<es.getNombreServicios()<<" x "<< es.getCantidadContratado();
            cout<<" ($"<<es.getPrecioUnitario()*es.getCantidadContratado()<< ")"<<endl;
        }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout<<"Este evento no tiene servicios eliminados "<<endl;
        setColor(WHITE);
    }
}

void ManagerEventoServicios::listarEventoyServicios(){
    int cantidad=_repo.getCantidadRegistros();

    if(cantidad==0){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS CARGADOS EN EVENTOS "<<endl;
        return;
    }

    int i = 0;
    int eventoActual=-1;
    float totalEvento=0;
    bool hayServicios=false;

    while(i<cantidad){
        EventoServicios es=_repo.leer(i);
        if(!es.getEliminado()){
            hayServicios=true;
            if(es.getIdEvento()!=eventoActual){
                if(eventoActual!=-1){
                    cout<<fixed << setprecision(2);
                    cout<<" TOTAL SERVICIOS DEL EVENTO: $"<<totalEvento<<endl;
                    setColor(LIGHTCYAN);
                    cout<<"--------------------------"<<endl;
                    setColor(WHITE);
                }

                eventoActual=es.getIdEvento();
                totalEvento=0;
                setColor(LIGHTCYAN);
                cout<<"EVENTO #"<<es.getIdEvento()<<" - "<<es.getNombreEvento()<<endl;
                setColor(WHITE);
            }

            cout<<" - SERVICIO: "<<es.getNombreServicios()<<endl;
            cout<<"    CANTIDAD: "<<es.getCantidadContratado()<<endl;
            cout<<fixed << setprecision(2);
            cout<<"    UNITARIO: $"<<es.getPrecioUnitario()<<endl;
            totalEvento+=es.getPrecioUnitario() * es.getCantidadContratado();
        }
        i++;
    }
    if(eventoActual!=-1) {
        setColor(LIGHTBLUE);
        cout<<fixed << setprecision(2);
        cout<<" TOTAL SERVICIOS DEL EVENTO: $"<<totalEvento<<endl;
        setColor(LIGHTCYAN);
        cout<<"--------------------------"<<endl;
        setColor(WHITE);
    }
    if(!hayServicios) {
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS ACTIVOS EN LOS EVENTOS "<<endl;
        setColor(WHITE);
    }
}

void ManagerEventoServicios::buscarIdEventoServicios(){
    int idE;
    int cantLinea=0, errorLinea=cantLinea+4;

    setColor(LIGHTCYAN);
    cout << "---BUSCAR EL EVENTO POR ID--- " << endl;

    cout << "INGRESAR ID EVENTO:(0 para cancelar)#: ";
    setColor(WHITE);

   while(true){
       gotoxy(39,cantLinea+2);
       cout<<"        "<<endl;
       gotoxy(39,cantLinea+2);

       idE=cargarEntero(39,cantLinea+2,errorLinea);

    if(idE==0){
            return;
    }
    break;
}

    int cantidad=_repo.getCantidadRegistros();

    bool encontrado=false;
    float totalEvento=0;

    for(int i=0; i<cantidad; i++) {
        EventoServicios Es=_repo.leer(i);
        if(!Es.getEliminado()&&Es.getIdEvento()==idE){
            setColor(LIGHTCYAN);
            cout<<"----- EVENTO #"<<idE<<" - "<<Es.getNombreEvento()<<" -----"<<endl;
            setColor(WHITE);
            encontrado=true;
            break;
        }
    }
    if(!encontrado) {
        setColor(LIGHTRED);
        cout<<"NO SE ENCONTRO EL EVENTO "<<endl;
        return;
    }

    for(int i=0; i<cantidad; i++){
        EventoServicios Es=_repo.leer(i);
        if(!Es.getEliminado() && Es.getIdEvento()==idE){
            cout<<"~ Servicio: "<<Es.getNombreServicios()<<endl;
            cout<<"~ Cantidad: "<<Es.getCantidadContratado()<<endl;
            cout<<"~ Unitario: $"<<Es.getPrecioUnitario()<<endl;
            setColor(LIGHTCYAN);
            cout<<"---------------------------"<<endl;
            setColor(WHITE);
            totalEvento += Es.getPrecioUnitario()*Es.getCantidadContratado();
        }
    }
    cout<<fixed<<setprecision(2);
    setColor(LIGHTBLUE);
    cout<<"TOTAL DE SERVICIOS CONTRATADOS: $"<<totalEvento<<endl<<endl;
    setColor(WHITE);
}

float ManagerEventoServicios::calcularTotalEvento(int idEvento){
    float total= 0;
    int cantidad=_repo.getCantidadRegistros();

    for(int i=0; i<cantidad; i++){
        EventoServicios es=_repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            total+=es.getPrecioUnitario()* es.getCantidadContratado();
        }
    }
    return total;
}

void ManagerEventoServicios::eliminar(){
  int opcion;
  do {
  system("cls");

  setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);
  cout<<"1. ELIMINAR  "<<endl;
  cout<<"2. ELIMINAR SERVICIO DEL EVENTO "<<endl;
  cout<<"3. MOSTRAR ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  setColor(LIGHTCYAN);
  cout<<"------------------------------"<<endl;
  setColor(WHITE);
  cout<<"OPCION: ";
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      eliminarEventoServicio();
      break;
  case 2:
      eliminarServicioDelEvento();
    break;
  case 3:
      mostrarEliminados();
    break;
  case 0:
    return;
default:
    cout<<"Opcion invalida, volve a intentar "<<endl;
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerEventoServicios::eliminarEventoServicio() {
    ArchivoEvento arcE;
    int cantE = arcE.getCantidadRegistros();

    if(cantE==0){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS REGISTRADOS"<<endl;
        return;
    }

    setColor(LIGHTCYAN);
    cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
    setColor(WHITE);
    bool hay=false;

    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(!ev.getEliminado() && ev.getConfirmado()){
            cout<<"ID EVENTO: #"<<ev.getIdEvento()<<" "<<ev.getNombreEvento()<<endl;
            hay=true;
        }
    }

    if(!hay){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS DISPONIBLES"<<endl;
        return;
    }

    system("pause");
    system("cls");

    int idEvento;
    int cantLinea=0, errorLinea=cantLinea+4;

    setColor(LIGHTCYAN);
    gotoxy(1,cantLinea+2); cout<<"INGRESE ID EVENTO:(0 para cancelar):# ";
    setColor(WHITE);

    while(true){
        gotoxy(38,cantLinea+2);
        cout<<"        "<<endl;
        gotoxy(38,cantLinea+2);

        idEvento=cargarEntero(38,cantLinea+2,errorLinea);

        if(idEvento==0) return;

        bool existe=false;
        Eventos evento;

        for(int i=0;i<cantE;i++){
            Eventos ev = arcE.leer(i);
            if(!ev.getEliminado() &&
               ev.getConfirmado() &&
               ev.getIdEvento()==idEvento){
                evento = ev;
                existe=true;
                break;
            }
        }

        if(!existe){
            setColor(LIGHTRED);
            cout<<"EL EVENTO NO EXISTE O ESTA CANCELADO"<<endl;
            continue;
        }

        if(eventoPagado(idEvento)){
            setColor(LIGHTRED);
            cout<<"NO SE PUEDE ELIMINAR: EVENTO PAGADO"<<endl;
            return;
        }

        break;
    }

    int totalES = _repo.getCantidadRegistros();
    bool tieneServicios=false;

    setColor(LIGHTCYAN);
    cout<<"--- SERVICIOS ASOCIADOS ---"<<endl;
    setColor(WHITE);

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            cout<<"- "<<es.getNombreServicios()<<endl;
            tieneServicios=true;
        }
    }

    if(!tieneServicios){
        setColor(LIGHTRED);
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS"<<endl;
        setColor(WHITE);
    }

    char eliminar;

    setColor(LIGHTCYAN);
    cout<<"CONFIRMA ELIMINAR EVENTO Y SUS SERVICIOS? (S/N): ";
    setColor(WHITE);
    cin>>eliminar;

    if(eliminar!='S' && eliminar!='s'){
        setColor(LIGHTRED);
        cout<<"OPERACION CANCELADA"<<endl;
        return;
    }

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            es.setEliminado(true);
            _repo.guardar(i,es);
        }
    }

    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(ev.getIdEvento()==idEvento){
            ev.setEliminado(true);
            arcE.guardar(i,ev);
            break;
        }
    }

    setColor(LIGHTGREEN);
    cout<<"EVENTO Y SERVICIOS ELIMINADOS CORRECTAMENTE"<<endl;
    setColor(WHITE);
}


void ManagerEventoServicios::eliminarServicioDelEvento() {
    ArchivoEvento arcE;
    int cantE = arcE.getCantidadRegistros();

    if(cantE == 0){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS REGISTRADOS"<<endl;
        return;
    }

    setColor(LIGHTCYAN);
    cout<<"--- EVENTOS DISPONIBLES ---"<<endl;
    bool hayEventos=false;

    setColor(WHITE);
    for(int i=0;i<cantE;i++){
        Eventos ev = arcE.leer(i);
        if(!ev.getEliminado() && ev.getConfirmado()){
            cout<<"ID EVENTO: #"<<ev.getIdEvento() <<" "<<ev.getNombreEvento()<<endl;
            hayEventos=true;
        }
    }

    if(!hayEventos){
        setColor(LIGHTRED);
        cout<<"NO HAY EVENTOS DISPONIBLES"<<endl;
        return;
    }

    system("pause");
    system("cls");

    int idEvento;
    int cantLinea=0,errorLinea=cantLinea+4;

    setColor(LIGHTCYAN);
    cout<<"INGRESE EL ID EVENTO:(0 para volver):# ";
    setColor(WHITE);

    while(true){
        gotoxy(40,cantLinea+1);
        cout<<"    "<<endl;
        gotoxy(40,cantLinea+1);

        idEvento=cargarEntero(40,cantLinea+1,errorLinea);


        if(idEvento==0) return;

        bool existe=false;
        Eventos evento;

        for(int i=0;i<cantE;i++){
            Eventos ev = arcE.leer(i);
            if(!ev.getEliminado() &&ev.getConfirmado() &&ev.getIdEvento()==idEvento){
                evento = ev;
                existe=true;
                break;
            }
        }

        if(!existe){
            setColor(LIGHTRED);
            cout<<"EL EVENTO NO EXISTE O NO ESTA ACTIVO"<<endl;
            continue;
        }

        if(eventoPagado(idEvento)){
            setColor(LIGHTRED);
            cout<<"NO SE PUEDEN MODIFICAR SERVICIOS: EVENTO PAGADO"<<endl;
            return;
        }

        break;
    }

    int totalES = _repo.getCantidadRegistros();
    bool hayServicios=false;

    setColor(LIGHTCYAN);
    cout<<"--- SERVICIOS DEL EVENTO ---"<<endl;
    setColor(WHITE);

    for(int i=0;i<totalES;i++){
        EventoServicios es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento()==idEvento){
            cout<<"ID SERVICIO: #"<<es.getIdServicio()<<" | CANT: "<<es.getCantidadContratado()<<endl;
            hayServicios=true;
        }
    }

    if(!hayServicios){
        setColor(LIGHTRED);
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS"<<endl;
        return;
    }

    system("pause");
    system("cls");

    int idServicio;
    setColor(LIGHTCYAN);
    cout<<"INGRESE EL ID DEL SERVICIO A ELIMINAR: ";
    setColor(WHITE);

    while(true){
        gotoxy(40,cantLinea+1);
        cout<<"    "<<endl;
        gotoxy(40,cantLinea+1);

        idServicio=cargarEntero(40,cantLinea+1,errorLinea);

        if(idServicio==0){
            mostrarError("Tiene que ser mayor a 0",errorLinea);
            continue;
        }

        bool encontrado=false;

        for(int i=0;i<totalES;i++){
            EventoServicios es = _repo.leer(i);
            if(!es.getEliminado() &&es.getIdEvento()==idEvento && es.getIdServicio()==idServicio){
                es.setEliminado(true);
                if(_repo.guardar(i,es)){
                    setColor(LIGHTMAGENTA);
                    cout<<"SERVICIO ELIMINADO CORRECTAMENTE"<<endl;
                    setColor(WHITE);
                } else {
                    setColor(LIGHTRED);
                    cout<<"ERROR AL ELIMINAR"<<endl;
                    setColor(WHITE);
                }
                encontrado=true;
                break;
            }
        }
        if(!encontrado){
            setColor(LIGHTRED);
            cout<<"ESE SERVICIO NO ESTA ASOCIADO AL EVENTO"<<endl;
            setColor(WHITE);
            continue;
        }

        break;
    }
}

void ManagerEventoServicios::mostrarEliminados() {
    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;
    int eventoActual=-1;

    setColor(LIGHTCYAN);
    cout<<"--- EVENTOS/SERVICIOS ELIMINADOS ---"<<endl<<endl;
    setColor(WHITE);

    for(int i=0; i<cantidad; i++) {
        EventoServicios Evservis = _repo.leer(i);
        if(Evservis.getEliminado()){
            encontrado = true;
            if(Evservis.getIdEvento()!=eventoActual){
                eventoActual=Evservis.getIdEvento();
                setColor(LIGHTCYAN);
                cout<<"---- EVENTO #"<<eventoActual<<" ----"<<endl;
                setColor(WHITE);
            }
            cout<<"~ Servicio #"<<Evservis.getIdServicio()<<" "<<Evservis.getNombreServicios()<<endl;
            cout<<" Cantidad "<<Evservis.getCantidadContratado()<<" ($"<<Evservis.getPrecioUnitario()*Evservis.getCantidadContratado()<<") "<<endl<<endl;
        }
    }
    if(!encontrado){
        setColor(LIGHTRED);
        cout << "NO HAY EVENTOS/SERVICIOS ELIMINADOS" << endl;
        setColor(WHITE);
    }
}

void ManagerEventoServicios::modificarEventoyServicio() {
    setColor(LIGHTCYAN);
    cout<<"=== EVENTOS Y SERVICIOS CARGADOS ==="<<endl;
    setColor(WHITE);
    listarEventoyServicios();
    setColor(LIGHTCYAN);
    cout<<"===================================="<<endl;

    system("pause");
    system("cls");

    int idEvento;
    int cantLinea=0,errorLinea=cantLinea+4;

   gotoxy(1,cantLinea+1); cout<<"INGRESE EL ID EVENTO:#";
    setColor(WHITE);

  while(true){
        gotoxy(24,cantLinea + 1);
        cout<<"       "<<endl;
        gotoxy(24,cantLinea + 1);

        idEvento=cargarEntero(24,cantLinea + 1,errorLinea);

    break;
 }

   if (eventoPagado(idEvento)) {
     setColor(LIGHTRED);
     cout << "EL EVENTO YA ESTA PAGADO. NO SE PUEDE MODIFICAR." << endl;
     setColor(WHITE);

    system("pause");
    return;
}

    int cant = _repo.getCantidadRegistros();
    EventoServicios es;
    bool hayServicios = false;

    system("pause");
    system("cls");

   setColor(LIGHTCYAN);
    cout<<"--- SERVICIOS DEL EVENTO:#"<<idEvento<<" ---"<<endl;
   setColor(WHITE);
    for(int i = 0; i < cant; i++) {
        es = _repo.leer(i);
        if(!es.getEliminado() && es.getIdEvento() == idEvento) {
            cout<<"Servicio ID: #" << es.getIdServicio()<<" "<<es.getNombreServicios()<<",  Cantidad: "<<es.getCantidadContratado()<<endl;
            hayServicios = true;
        }
    }
    if(!hayServicios) {
        setColor(LIGHTRED);
        cout<<"EL EVENTO NO TIENE SERVICIOS ASOCIADOS." << endl;
        return;
    }

     system("pause");
     system("cls");


    int idServicioElegido;
    setColor(LIGHTCYAN);
    cout<<"INGRESE EL ID SERVICIO A MODIFICAR:#";
    setColor(WHITE);


  while(true){
        gotoxy(38,cantLinea + 1);
        cout<<"       "<<endl;
        gotoxy(38,cantLinea + 1);

        idServicioElegido=cargarEntero(38,cantLinea + 1,errorLinea);

        break;
  }

    int posReal = -1;

    for(int i=0; i<cant; i++) {
        es=_repo.leer(i);
        if(!es.getEliminado()&& es.getIdEvento() == idEvento&& es.getIdServicio() == idServicioElegido) {
            posReal=i;
            break;
        }
    }
    if(posReal==-1) {
        setColor(LIGHTRED);
        cout<<"SERVICIO NO ENCONTRADO PARA ESE EVENTO "<<endl;
        return;
    }

    EventoServicios eventoServi =_repo.leer(posReal);

    system("pause");
    system("cls");

    int opcion;
    do {
        system("cls");
        setColor(LIGHTCYAN);
        cout<<"MODIFICAR SERVICIO DEL EVENTO "<<endl;
        cout<<"1. CAMBIAR ID SERVICIO "<<endl;
        cout<<"2. CAMBIAR CANTIDAD "<<endl;
        cout<<"0. GUARDAR Y SALIR "<<endl;
        cout<<"OPCION: ";
        setColor(WHITE);
        cin>>opcion;
        system("cls");

 switch(opcion){
   case 1:{
    ArchivoServicios arcS;
    int cantS = arcS.getCantidadRegistros();

    setColor(LIGHTCYAN);
    cout<<"SERVICIOS DISPONIBLES:"<<endl;
    for (int i = 0; i < cantS; i++) {
        Servicios s = arcS.leer(i);
        if (!s.getEliminado()) {
            cout<<"#"<<s.getIdServicio()<<" - "<<s.getNombreServicio()<<" $ "<<s.getPrecio()<<endl;
        }
    }
    cout<<endl;

    system("pause");
    system("cls");

    setColor(LIGHTGREEN);
    cout<<"ID actual: #"<<eventoServi.getIdServicio()<<endl;
    setColor(LIGHTCYAN);
    int nuevoId;
    cout<<"Nuevo ID:#";

   while(true){
        gotoxy(12,cantLinea + 2);
        cout<<"       "<<endl;
        gotoxy(12,cantLinea + 2);

        nuevoId=cargarEntero(12,cantLinea + 2,errorLinea);

    if (nuevoId == 0) {
        cout<<"Operación cancelada "<<endl;
        break;
    }

    break;
}


    bool existeNuevo = false;

    Servicios nuevo;
    for (int i = 0; i < cantS; i++) {
        Servicios ser = arcS.leer(i);
        if (ser.getIdServicio() == nuevoId && !ser.getEliminado()) {
            nuevo = ser;
            existeNuevo = true;
            break;
        }
    }

    if (!existeNuevo) {
        setColor(LIGHTRED);
        cout<<"El ID servicio no existe "<<endl;
        break;
    }

    for (int i = 0; i < cant; i++) {
        EventoServicios aux = _repo.leer(i);
        if (!aux.getEliminado() &&
            aux.getIdEvento() == idEvento &&
            aux.getIdServicio() == nuevoId &&
            i != posReal) { /// para evitar compararse con sí mismo
            setColor(LIGHTRED);
            cout<<"Ese servicio ya esta agregado a este evento. No se puede duplicar "<<endl;
            setColor(WHITE);
            existeNuevo = false;
            break;
        }
    }
    if (!existeNuevo) {
        break;
    }

    eventoServi.setIdServicio(nuevoId);
    eventoServi.setNombreServicio(nuevo.getNombreServicio());
    eventoServi.setPrecioUnitario(nuevo.getPrecio());

    break;
}
   case 2:{
        setColor(LIGHTGREEN);
        cout<<"Cantidad actual: "<<eventoServi.getCantidadContratado()<<endl;
        int nuevaCant;
        setColor(LIGHTCYAN);
        cout<<"Nueva cantidad: ";
        setColor(WHITE);

    while (true) {
        gotoxy(16,cantLinea+2);
        cout<<"    "<<endl;
        gotoxy(16,cantLinea+2);

        nuevaCant=cargarEntero(16,cantLinea+2,errorLinea);

        if(nuevaCant == 0){
            mostrarError("Tiene que ser mayor a 0",errorLinea);
            continue;
        }
    break;
}

    eventoServi.setCantidadContratado(nuevaCant);

 break;
}
    case 0:
        _repo.guardar(posReal, eventoServi);
        setColor(LIGHTGREEN);
        cout<<"CAMBIOS GUARDADOS "<<endl;
        break;
        }
    system("pause");
    } while(opcion != 0);
}

void ManagerEventoServicios::Activar(){
  int id, pos;
  char activar;
  int cantidad=_repo.getCantidadRegistros();

  bool encontrado=false;
    setColor(LIGHTCYAN);
    cout<<"EVENTO/SERVICIOS ELIMINADOS "<<endl;
    setColor(WHITE);

    for(int i=0;i<cantidad;i++){
    EventoServicios eveSer=_repo.leer(i);
    if(eveSer.getEliminado()){
        cout<<"~ID: #"<<eveSer.getIdEvento()<<" "<<eveSer.getNombreEvento()<<" | "<<eveSer.getNombreServicios()<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    setColor(LIGHTRED);
    cout<<"NO HAY EVENTO/SERVICIOS ELIMINADOS "<<endl;
    return;
  }

  system("pause");
  system("cls");

  int cantLinea=0,errorLinea=cantLinea+4;

  setColor(LIGHTCYAN);
  cout<<"~~~~ ACTIVAR EVENTOS/SERVICIOS ~~~~"<<endl;
  cout<<"ID EVENTO: ";
  setColor(WHITE);

 while(true){
        gotoxy(12,cantLinea + 2);
        cout<<"     "<<endl;
        gotoxy(12,cantLinea + 2);

        id=cargarEntero(12,cantLinea+2,errorLinea);

    if(id<=0){
       mostrarError ("NO PUEDE SER MENOR O IGUAL A 0",errorLinea);
        continue;
    }
    break;
 }
  pos=_repo.buscarID(id);

  if(pos==-1){
    setColor(LIGHTRED);
    cout<<"EL EVENTOS/SERVICIO NO EXISTE "<<endl;
    return;
  }
  EventoServicios Evservis;
  Evservis= _repo.leer(pos);

    if(!Evservis.getEliminado()){
       setColor(LIGHTRED);
       cout<<"HAY UN ERROR: EL EVENTO/SERVICIO NO ESTA ELIMINADO "<<endl;
       cout<<"No es necesario activar "<<endl;
       setColor(WHITE);
       return;
  }

  system("pause");
  system("cls");

  setColor(LIGHTCYAN);
  cout<<"INFORMACION DEL EVENTO/SERVICIO ELIMINADO "<<endl;
  setColor(WHITE);
  cout<<endl;
  mostrarEventoCompleto(id);
  cout<<endl;

  setColor(LIGHTCYAN);
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  setColor(WHITE);
  cin >> activar;

  if (activar != 's' && activar != 'S') {
       setColor(LIGHTRED);
       cout << "OPERACION CANCELADA." << endl;
       setColor(WHITE);
       return;
   }

    int activarS=0;

    for(int i=0;i<cantidad;i++){
        EventoServicios evse=_repo.leer(i);
        if(evse.getIdEvento()==id && evse.getEliminado()){
            evse.setEliminado(false);
            _repo.guardar(i,evse);
            activarS++;
        }
    }
    setColor(LIGHTCYAN);
    cout<<"SE ACTIVARON "<<activarS<<" SERVICIOS DEL EVENTO: #"<<id<<endl;
    setColor(WHITE);
}

void ManagerEventoServicios::serviciosMasContratados(){
    int cantidadES=_repo.getCantidadRegistros();
    if(cantidadES==0){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS CONTRATADOS "<<endl;
        return;
    }
    ArchivoServicios arcServis;
    int cantServicios=arcServis.getCantidadRegistros();

    int *Id= new int[cantServicios];
    string *nombres= new string[cantServicios];
    int *cant= new int [cantServicios];

    int totalEncontrado=0;

    for(int i=0;i<cantServicios;i++){
        Servicios ser= arcServis.leer(i);
        int buscarId=ser.getIdServicio();
        int acumulador=0;

         for(int x=0; x<cantidadES;x++){
            EventoServicios eves=_repo.leer(x);
            if(eves.getEliminado()) continue;
            if(eves.getIdServicio()==buscarId){
                acumulador +=eves.getCantidadContratado();
            }
         }
         if(acumulador>0){
            Id[totalEncontrado]=buscarId;
            nombres[totalEncontrado]=ser.getNombreServicio();
            cant[totalEncontrado]=acumulador;
            totalEncontrado++;
         }
    }
    if(totalEncontrado==0){
        setColor(LIGHTRED);
        cout<<"NO HAY SERVICIOS CONTRATADOS "<<endl;
        delete[] Id;
        delete[] nombres;
        delete[] cant;
        return;
    }
     for(int i=0;i<totalEncontrado-1;i++){
        for(int x=0; x<totalEncontrado -i-1;x++){
            if(cant[x]<cant[x+1]){
                int AuxCant= cant[x];
                cant[x]=cant[x+1];
                cant[x+1]=AuxCant;
                int AuxId=Id[x];
                Id[x]=Id[x+1];
                Id[x+1]=AuxId;
                string AuxNom= nombres[x];
                nombres[x]=nombres[x+1];
                nombres[x+1]=AuxNom;
            }
        }
     }
     setColor(LIGHTCYAN);
     cout<<"~~~~~ SERVICIOS MAS CONTRATADOS ~~~~~"<<endl;
     setColor(WHITE);
     for(int i=0;i<totalEncontrado;i++){
        cout<<"#"<<Id[i]<<" "<<nombres[i]<<" (CANTIDAD CONTRATADOS: "<<cant[i]<<") "<<endl;
     }
     setColor(LIGHTCYAN);
     cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
     setColor(WHITE);

    delete[] Id;
    delete[] nombres;
    delete[] cant;
}


void ManagerEventoServicios::cancelarServiciosPorEvento(int idEvento) {
    int cant = _repo.getCantidadRegistros();
    for (int i=0; i<cant; i++) {
        EventoServicios es=_repo.leer(i);
        if(es.getIdEvento() ==idEvento && !es.getEliminado()){
            es.setActivo(false);     /// servicio cancelado
            _repo.guardar(i,es);
        }
    }
}

bool ManagerEventoServicios::eventoPagado(int idEvento){
   ArcPagos arc;
    int cant = arc.getCantidadRegistros();
    for(int i=0;i<cant;i++){
        Pagos pago = arc.leer(i);
        if(!pago.getEliminado() &&pago.getIdEvento()==idEvento &&pago.getPagado()){
            return true;
        }
    }
    return false;
}

