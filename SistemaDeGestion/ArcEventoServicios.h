#pragma once
#include "string"
#include "EventoServicios.h"

class ArcEventoServicios
{
    public:
        ArcEventoServicios(std::string nombreArchivo ="EventoServicios.dat");

        bool guardar (EventoServicios registro);
        bool guardar (int pos, EventoServicios registro);
        int buscarID(int idES);

        EventoServicios leer(int pos);
        int leerTodos(EventoServicios evenSer[],int cantidad);
        int getCantidadRegistros();
        bool eliminar(int pos);
    protected:

    private:
        std::string _nombreArchivo;
};
