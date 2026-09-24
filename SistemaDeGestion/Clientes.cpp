# include<iostream>
#include <cstring>
#include "Clientes.h"
using namespace std;

Clientes::Clientes()
:_IdCliente(0),_Nombre("-"),_Apellido("-"),_DNI(0),_Email("-"),_Telefono(0){

}

Clientes::Clientes(int idCliente,string nombre, string apellido,int dni,string email,int telefono,bool estado)
{
    setIdCliente(idCliente);
    setNombre(nombre);
    setApellido(apellido);
    setDNI(dni);
    setEmail(email);
    setTelefono(telefono);
    setEstado(estado);
    setEliminado(false);
}


int Clientes::getIdCliente() {
     return _IdCliente;
}

void Clientes::setIdCliente(int id) {
     _IdCliente = id;
}

string Clientes::getNombre(){
   return _Nombre;
}
void Clientes::setNombre (string nombre){
strncpy(_Nombre, nombre.c_str(), 299);
  _Nombre[299] = '\0';
}

string Clientes::getApellido(){
   return _Apellido;
}
void Clientes::setApellido (string apellido){
strncpy(_Apellido, apellido.c_str(), 299);
  _Apellido [299] = '\0';

}
int Clientes::getDNI(){
   return _DNI;
}
void Clientes::setDNI(int dni){
  _DNI=dni;
}

string Clientes::getEmail(){
   return _Email;
}
void Clientes::setEmail(string email){
strncpy(_Email, email.c_str(), 299);
  _Email[299] = '\0';

}

int Clientes::getTelefono(){
   return _Telefono;
}
void Clientes::setTelefono (int telefono){
   _Telefono=telefono;
}
bool Clientes::getEstado(){
   return _Estado;
}
void Clientes::setEstado(bool estado){
  _Estado=estado;
}
bool Clientes::getEliminado(){
     return _Eliminado;
}
void Clientes::setEliminado(bool eliminado){
    _Eliminado=eliminado;
}

