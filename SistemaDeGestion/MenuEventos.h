#pragma once
#include "ManagerEvento.h"
#include "MenuEventoServicios.h"

class MenuEventos
{
    public:
        MenuEventos();
        void mostrar();
        void mostrarOpciones();
        int seleccionarOpcion();
        void ejecutarOpcion(int opcion);
        ManagerEvento _managerEventos;
        MenuEventoServicios _menuEventoServicios;


    private:
       int _cantidadOpciones;
};
