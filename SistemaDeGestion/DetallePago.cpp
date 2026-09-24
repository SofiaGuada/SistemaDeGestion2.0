#include<iostream>
#include "DetallePago.h"

using namespace std;

DetallePago::DetallePago()
:_IdPago(0),_IdServicio(0),_Cantidad(0),_Monto(0){

}

void DetallePago::setMonto(float monto){
    _Monto=monto;
}

DetallePago::DetallePago(int idPago, int idServicio, int cantidad, float monto){
  setIdPago(idPago);
  setIdServicio(idServicio);
  setCantidad(cantidad);
  setMonto(monto);
}
