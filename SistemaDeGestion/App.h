#pragma once
#include "MenuCliente.h"
#include "MenuEventos.h"
#include "MenuPagos.h"

class App
{
    public:
        App();
    void run();

    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    MenuCliente _menuCliente;
    MenuEventos _menuEvento;
    MenuPagos _menuPagos;

    private:
        int _cantidadOpciones;
};
