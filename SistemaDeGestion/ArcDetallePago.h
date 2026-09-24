#pragma once
#include <string>
#include "DetallePago.h"

class ArcDetallePago
{
    public:
        ArcDetallePago(std::string nombreArchivo="DetallePagos.dat");
        bool guardar (DetallePago registro);
        bool guardar (int pos, DetallePago registro);
        int buscarIdPago(int id);
        DetallePago leer(int pos);
        int leerTodos(DetallePago Detallepago[],int cantidad);
        int getCantidadRegistros();

        bool eliminar(int pos);

    private:
        std::string _nombreArchivo;
};
