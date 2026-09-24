#include <iostream>
#include  <cstring>
#include "Servicios.h"
using namespace std;

Servicios::Servicios(){}

Servicios::Servicios(int idServicio,string nombre,string descripcion,string proveedor,float costo,bool eliminado){
     setIdServicio(idServicio);
     setNombreServicio(nombre);
     setDescripcion(descripcion);
     setProveedor(proveedor);
     setPrecio(costo);
     setEliminado(eliminado);
}

void Servicios::setNombreServicio(std::string nombre){
 strncpy(_NombreServicio, nombre.c_str(),299);
 _NombreServicio[299] = '\0';
}
void Servicios::setProveedor(std::string proveedor){
 strncpy(_proveedor, proveedor.c_str(),299);
 _proveedor[299] = '\0';
}
void Servicios::setDescripcion(std::string descripcion){
 strncpy(_descripcion, descripcion.c_str(),299);
 _descripcion[299] = '\0';
}

