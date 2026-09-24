#pragma once
#include <string>
#include "Servicios.h"

class ArchivoServicios
{
    public:
        ArchivoServicios(std::string nombreArchivo="Servicios.dat");

        bool guardar ( Servicios registro);

        bool guardar (int pos, Servicios registro);

        int buscarIdServicios(int id);

        Servicios leer(int pos);

        int leerTodos(Servicios servis[],int cantidad);

        int getCantidadRegistros();

        int getNuevoIdServicio();

        int buscarPosicionIdServicio(int idBuscado);

        bool eliminar(int pos);


    private:
        std::string _nombreArchivo;
};
