#pragma once
#include <string>
#include "Fecha.h"

class Pagos
{
    public:
        Pagos();
        Pagos(int idPago,int idCliente,int idEvento, Fecha fecha,float monto,std::string metodo,bool pagado,bool atrasado);
        int getIdPago(){return _idPago;}
        void setIdPago(int idPago){_idPago=idPago;}
        int getIdCliente(){return _idCliente;}
        void setIdCliente(int idCliente){_idCliente=idCliente;}
        int getIdEvento(){return _idEvento;}
        void setIdEvento(int idEvento){_idEvento=idEvento;}
        Fecha getFechaPago(){return _fechaPago;}
        void setFechaPago(Fecha fecha){_fechaPago=fecha;}

        float getMontoTotal(){return _montoTotal;}
        void setMontoTotal(float monto){_montoTotal=monto;}
        std::string getMetodoPago(){return _metodoPago;}
        void setMetodoPago(std::string metodo);
        bool getPagado(){return _pagado;}
        void setPagado(bool pagado){_pagado=pagado;}
        bool getAtrasados(){return _atrasados;}
        void setAtrasados(bool atrasado){_atrasados=atrasado;}
        bool getEliminado(){return _eliminado;}
        void setEliminado(bool eliminado){_eliminado=eliminado;}

    private:
        int _idPago;
        int _idCliente;
        int _idEvento;
        Fecha _fechaPago;  ///composición: cuando una clase tiene como propiedad un objeto de otra clase
        float _montoTotal;
        char _metodoPago[50];
        bool _atrasados;
        bool _pagado;
        bool _eliminado;

};
