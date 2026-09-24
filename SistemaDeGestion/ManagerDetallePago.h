#pragma once
#include "ArcDetallePago.h"

class ManagerDetallePago
{
    public:
        ManagerDetallePago();
        void cargarDetallePagos(int idEvento, int idPago);
        void mostrarDetallePagos();
//        void listarPagos();
//        void buscarIdPagos();
//        void eliminar();

    private:
         ArcDetallePago _repo;
};
