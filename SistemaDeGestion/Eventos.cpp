# include<iostream>
#include <cstring>
#include "Eventos.h"
using namespace std;

//Eventos::Eventos(){
//    _idEvento=0;
//    _idCliente=0;
//    _nombreEvento[0]={'-'};
//    _cantidadInvitados=0;
//    _eliminado=false;
//}

Eventos::Eventos(int idEven,int idClien,string nombre,Fecha fechaEvento,int cant,bool confirmado)
{
     setIdEvento(idEven);
     setidCliente(idClien);
     setNombreEvento(nombre);
     setFechaEvento(fechaEvento);
     setCantidad(cant);
     setConfirmado(confirmado);
     setEstado(false);

}
int Eventos::getIdEvento(){
   return _idEvento;
}
void Eventos::setIdEvento(int idEvento){
    _idEvento=idEvento;
}
int Eventos::getidCliente() {
     return _idCliente;
}
void Eventos::setidCliente(int id) {
     _idCliente = id;
}
string Eventos::getNombreEvento(){
   return _nombreEvento;
}
void Eventos::setNombreEvento(string nombreEvento){
strncpy(_nombreEvento, nombreEvento.c_str(),299);
  _nombreEvento [299] = '\0';

}
Fecha Eventos::getFechaEvento(){
    return _fechaEvento;
}
void Eventos::setFechaEvento(Fecha fechaEvento){
    _fechaEvento=fechaEvento;
}

int Eventos::getcantidadInvitados(){
   return _cantidadInvitados;
}
void Eventos::setCantidad(int cantidad){
    if (cantidad>=50){
        _cantidadInvitados=cantidad;
    }
}
bool Eventos::getConfirmado(){
   return _confirmado;
}
void Eventos::setConfirmado(bool confirmado){
   _confirmado=confirmado;
}
bool Eventos::getEliminado(){
    return _eliminado;
}
void Eventos::setEliminado(bool eliminado){
    _eliminado=eliminado;
}

float Eventos::calcularPrecioInicial(int cantidadInvitados){
    float precioInicial=0;
    if (cantidadInvitados >= 500) precioInicial = 300000;
    else if (cantidadInvitados >= 200) precioInicial = 170000;
    else if (cantidadInvitados >= 100) precioInicial = 90000;
    else precioInicial = 60000;
}
