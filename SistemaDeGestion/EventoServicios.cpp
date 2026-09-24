#include <iostream>
#include <cstring>
#include "EventoServicios.h"

using namespace std;
EventoServicios::EventoServicios(int idEvento,int idServicio,int cantidad,float precio,string nombreEvento,string nombreServicio)
{
 setIdEvento(idEvento);
 setIdServicio(idServicio);
 setCantidadContratado(cantidad);
 setPrecioUnitario(precio);
 setNombreEvento(nombreEvento);
 setNombreServicio(nombreServicio);
 setActivo(true);
 setEliminado(false);
}
void EventoServicios::setNombreServicio(string nombreServicios){
		strncpy(_NombreServicios, nombreServicios.c_str(),49);
		_NombreServicios[49] = '\0';
}

void EventoServicios::setNombreEvento(string nombre){
		strncpy(_NombreEvento, nombre.c_str(),49);
		_NombreEvento[49] = '\0';
	}
