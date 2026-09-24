#pragma once
#include "ArcPagos.h"

class ManagerPago
{
    public:
        ManagerPago();
        void cargarPagos();
        void mostrarPagos(Pagos pago);
        void listarPagos();
        void buscarIdPagos();
        void buscarPorCliente();
        void buscarXfecha();

        void eliminar();
        void eliminarPago();
        void mostrarEliminados();
        void Activar();

        float CalcularElTotal(int idevento);

        void modificarPago();
        void marcarPago();

        void calcularTotalAnual();
        void mostrarRecaudacionxCliente();
       void recaudacionTipoEvento();
        void mostrarPagosxEstados();

        void listarPendientes();
        void listarAtrasados();


        void submenuPago();
        void buscar();

        float calcularRecaudacionCliente(int idCliente);


    private:
         ArcPagos _repo;
};

/**
 Hacer un descuento o recargo dependiendo de como se pague

*/

