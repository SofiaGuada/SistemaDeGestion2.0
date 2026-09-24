#pragma once
#include <string>
#include "Eventos.h"

class ArchivoEvento
{
    public:
        ArchivoEvento(std::string nombreArchivo="Eventos.dat");
        bool guardar (Eventos registro);
        bool guardar (int pos, Eventos registro);
        int buscarIDEvento(int id);
        Eventos leer(int pos);
        int leerTodos(Eventos evento[],int cantidad);
        int getCantidadRegistros();
        int getNuevoIdEvento();
        bool eliminar(int pos);

    private:
        std::string _nombreArchivo;
};
