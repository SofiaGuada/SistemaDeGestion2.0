#pragma once

class DetallePago
{
    public:
        DetallePago();
        DetallePago(int idPago, int idServicio, int cantidad, float monto);
        int getIdPago(){return _IdPago;}
        void setIdPago(int idPago){_IdPago=idPago;}
        int getIdServicio(){return _IdServicio;}
        void setIdServicio(int idServis){_IdServicio=idServis;}
        int getCantidad(){return _Cantidad;}
        void setCantidad(int cant){_Cantidad=cant;}

        float getMonto(){return _Monto;}
        void setMonto(float monto);



    private:
        int _IdPago;
        int _IdServicio;
        int _Cantidad;
        float _Monto;
};
