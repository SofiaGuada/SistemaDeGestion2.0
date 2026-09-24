#pragma once
#include <string>
#include "ArchivoClientes.h"

class ManagerClientes
{
    public:
        ManagerClientes();
        void CargarCliente();
        void ListarClientes();
        void buscarClientes();
        void buscarClientesID();
        void buscarClientesDNI();
        void buscarClientesApellido();
        void eliminarClientes();
        void mostrarClientes(Clientes cliente);
        void eliminar();
        void ActivarCliente();
        void modificarClientes();
        void mostrarClientesEliminados();
        void ordanadosAlfabeticamente();
        bool validadDNI(int dni);

    protected:

    private:
        ArchivoClientes _repo;
};
