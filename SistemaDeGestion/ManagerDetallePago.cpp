# include<iostream>
#include <iomanip>
#include "ManagerDetallePago.h"
#include "ArcEventoServicios.h"
#include "EventoServicios.h"
#include "ArchivoServicios.h"
#include "Servicios.h"
#include "ArcPagos.h"
#include "Pagos.h"
#include "rlutil.h"
#include "Necesario.h"
#include "ArchivoEvento.h"
using namespace std;
using namespace rlutil;

ManagerDetallePago::ManagerDetallePago()
{
    //ctor
}

void ManagerDetallePago::cargarDetallePagos(int idEvento,int idPago){
     ArcEventoServicios ArcEvS;
     ArchivoServicios ArcSer;

     int cantidad=ArcEvS.getCantidadRegistros();

     for(int i=0;i<cantidad;i++){
        EventoServicios eventos=ArcEvS.leer(i);
        if(!eventos.getEliminado() && eventos.getIdEvento()==idEvento){
        int cantServicios = ArcSer.getCantidadRegistros();
        for (int j = 0; j < cantServicios; j++) {
            Servicios servis = ArcSer.leer(j);

        if(!servis.getEliminado() && eventos.getIdServicio()==servis.getIdServicio()){
            DetallePago Dpago;
            Dpago.setIdPago(idPago);
            Dpago.setIdServicio(servis.getIdServicio());
            Dpago.setCantidad(eventos.getCantidadContratado());
            Dpago.setMonto(servis.getPrecio());
            _repo.guardar(Dpago);
        }
        }
     }
}
}

void ManagerDetallePago::mostrarDetallePagos() {
    int idPago;
    int cantLinea = 0, errorLinea = cantLinea + 4;

    setColor(LIGHTMAGENTA);
    cout << "INGRESE ID PAGO:#";
    setColor(YELLOW);

    while (true) {
        gotoxy(19, cantLinea + 1);
        cout << "      ";
        gotoxy(19, cantLinea + 1);

        idPago = cargarEntero(19, cantLinea + 1, errorLinea);

        if (idPago <= 0) {
            mostrarError("INGRESE UN ID VALIDO", errorLinea);
            continue;
        }
        break;
    }

    ArcPagos arc;
    int pos = arc.buscarIdPago(idPago);

    if (pos == -1) {
        setColor(LIGHTRED);
        cout<<"NO HAY PAGOS CON ESE ID"<<endl;
        return;
    }

    Pagos pago = arc.leer(pos);

    if (!pago.getPagado()) {
        setColor(LIGHTRED);
        cout<<"ESTE PAGO AUN ESTA PENDIENTE"<<endl;
        return;
    }

    int cantidad = _repo.getCantidadRegistros();
    float totalServicios = 0;

    setColor(LIGHTMAGENTA);
    cout<<"----- DETALLE DE PAGO -----"<<endl;
    setColor(YELLOW);
    cout<<"ID PAGO: #"<<idPago<<endl;
    cout<<"ID EVENTO: #" << pago.getIdEvento()<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"| ID SERVICIO | CANTIDAD |    MONTO   |"<<endl;

    for (int i = 0; i < cantidad; i++) {
        DetallePago detalle = _repo.leer(i);
        if (detalle.getIdPago() == idPago) {
            cout<<"|      "<<detalle.getIdServicio()<<"      |    "<<detalle.getCantidad()<<"     | $"<<fixed<<setprecision(2)<<detalle.getMonto()<<" |"<<endl;
            totalServicios += detalle.getMonto() * detalle.getCantidad();
        }
    }
    cout << "----------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "TOTAL SERVICIOS: $" << totalServicios << endl;
    cout << "MONTO TOTAL PAGADO: $" << pago.getMontoTotal() << endl;
    ArchivoEvento arcEvento;
    int posEvento = arcEvento.buscarIDEvento(pago.getIdEvento());
    if (posEvento != -1) {
        Eventos evento = arcEvento.leer(posEvento);
        if (!evento.getConfirmado()) {
            float devolucion = pago.getMontoTotal() * 0.50f;
            setColor(LIGHTRED);
            cout << "\n*** EVENTO CANCELADO ***" << endl;
            cout << "DEVOLUCION (50%): $" << devolucion << endl;
            setColor(LIGHTGREEN);
            cout << "RECAUDACION FINAL: $"
                 << pago.getMontoTotal() - devolucion << endl;
        }
    }
    setColor(WHITE);
}
