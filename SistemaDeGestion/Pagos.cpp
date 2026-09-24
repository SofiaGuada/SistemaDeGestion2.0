#include <cstring>
#include "Pagos.h"

Pagos::Pagos()
{
}
Pagos::Pagos(int idPago,int idCliente,int idEvento, Fecha fecha,float monto,std::string metodo,bool pagado,bool atrasado){
   setIdPago(idPago);
   setIdCliente(idCliente);
   setIdEvento(idEvento);
   setFechaPago(fecha);
   setMontoTotal(monto);
   setMetodoPago(metodo);
   setPagado(pagado);
   setAtrasados(atrasado);
   _eliminado=false;
}

void Pagos::setMetodoPago(std::string metodo){
 strncpy(_metodoPago, metodo.c_str(),49);
 _metodoPago[49] = '\0';

}
