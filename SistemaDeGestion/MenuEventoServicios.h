#pragma once
#include "ManagerEventoServicios.h"
#include "ManagerServicios.h"

class MenuEventoServicios
{
    public:
        MenuEventoServicios();
        void mostrar();
        void mostrarOpciones();
        int seleccionarOpcion();
        void ejecutarOpcion(int opcion);
        ManagerEventoServicios _managerEventoServicios;
        ManagerServicios _managerServicios;

    private:
       int _cantidadOpciones;
};
