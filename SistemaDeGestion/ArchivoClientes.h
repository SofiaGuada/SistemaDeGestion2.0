#pragma once
#include <string>
#include "Clientes.h"

class ArchivoClientes
{
    public:
        ArchivoClientes(std::string nombreArchivo ="Clientes.dat");
        bool guardar (Clientes registro);
        bool guardar (int pos, Clientes registro);
        int buscarIDcliente(int idcliente);
        int buscarDni(int dni);
        int getNuevoID();
        Clientes leer(int pos);
        int leerTodos(Clientes cliente[],int cantidad);
        int getCantidadRegistros();
        bool eliminar(int pos);
    protected:

    private:
        std::string _nombreArchivo;
};
