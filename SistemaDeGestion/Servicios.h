#pragma once
#include "Fecha.h"
#include <string>

class Servicios
{
    public:
        Servicios();
        Servicios(int idServicio,std::string nombre,std::string descripcion,std::string proveedor,float costo,bool eliminado);

        int getIdServicio(){return _IdServicio;}
        void setIdServicio(int idServicio){_IdServicio=idServicio;}
        std::string getNombreServicio(){return _NombreServicio;}
        void setNombreServicio(std::string nombre);
        float getPrecio(){return _Costo;}
        void setPrecio(float costo){_Costo=costo;}
        std::string getDescripcion(){return _descripcion;}
        void setDescripcion(std::string descripcion);
        std::string getProveedor(){return _proveedor;}
        void setProveedor(std::string proveedor);
        bool getEliminado(){return _eliminado;}
        void setEliminado(bool eliminado){_eliminado=eliminado;}


    private:
        int _IdServicio;
        char _NombreServicio[300];
        char _descripcion[300];
        char _proveedor[300];
        float _Costo;
        bool _eliminado;
};
