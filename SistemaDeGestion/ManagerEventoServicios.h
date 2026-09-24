#pragma once
#include "ArcEventoServicios.h"

class ManagerEventoServicios
{
    public:
        ManagerEventoServicio();
        void cargarEventosyServicios();
        void mostrarEventoyServicios(EventoServicios Evenservis);
        void mostrarEventoCompleto(int idEvento);
        void listarEventoyServicios();
        void buscarIdEventoServicios();
        void eliminar();
        void eliminarEventoServicio();
        void eliminarServicioDelEvento();
        void mostrarEliminados();
        void Activar();
        void modificarEventoyServicio();
        float calcularTotalEvento(int idEvento);
        void serviciosMasContratados();

        void cancelarServiciosPorEvento(int idEvento);
        bool eventoPagado(int idEvento);

    private:
        ArcEventoServicios _repo;
};
