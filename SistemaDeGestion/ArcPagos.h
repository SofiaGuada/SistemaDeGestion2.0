#pragma once
#include <string>
#include "Pagos.h"

class ArcPagos
{
    public:
        ArcPagos(std::string nombreArchivo="Pagos.dat");

        bool guardar (Pagos registro);
        bool guardar (int pos, Pagos registro);
        int buscarIdPago(int id);
        Pagos leer(int pos);
        int leerTodos(Pagos pago[],int cantidad);
        int getCantidadRegistros();
        int getNuevoIdPago();
        bool eliminar(int pos);


    protected:

    private:
        std::string _nombreArchivo;
};
