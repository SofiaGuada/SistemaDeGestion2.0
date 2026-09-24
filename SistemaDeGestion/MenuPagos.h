#pragma once
#include "ManagerPago.h"
#include "ManagerDetallePago.h"


class MenuPagos
{
    public:
        MenuPagos();
        void mostrar();
        void mostrarOpciones();
        int seleccionarOpcion();
        void ejecutarOpcion(int opcion);
        ManagerPago _managerPagos;
        ManagerDetallePago _detallePago;

    private:
        int _cantOpciones;
};
