#pragma once
#include "ArchivoServicios.h"

class ManagerServicios
{
    public:
        ManagerServicios();
        void cargarServicios();
        void mostrarServicios(Servicios servis);
        void listarServicios();
        void buscarIdServicios();
        void eliminar();
        void MostrarServiciosEliminados();
        void eliminarServicios();
        void menuServicios();
        void serviciosXproveedor();
        void buscar();

        void modificarServicio();
        void ActivarServicios();

    private:
        ArchivoServicios _repo;
};
