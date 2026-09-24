#include "ArcPagos.h"
using namespace std;

ArcPagos::ArcPagos(string nombreArchivo)
   :_nombreArchivo(nombreArchivo){
}

bool ArcPagos::guardar (Pagos registro){
   FILE *pFile;
   bool result;

   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(Pagos),1,pFile);

   fclose(pFile);
   return result;

}

bool ArcPagos::guardar (int pos, Pagos registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(Pagos) , SEEK_SET);

  result = fwrite(&registro, sizeof(Pagos), 1, pFile);

  fclose(pFile);

  return result;
}

int ArcPagos::buscarIdPago(int id){
      FILE*pFile;
      Pagos pago;
      int pos=-1;
     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }
     while (fread(&pago,sizeof(Pagos),1,pFile)){
        if (pago.getIdPago()== id){
            pos=ftell(pFile)/sizeof (Pagos)-1;
            break;
        }
     }
     fclose(pFile);
     return pos;
}

Pagos ArcPagos::leer(int pos){
    FILE*pFile;
    Pagos pago;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return pago;
    }
    fseek(pFile, pos * sizeof(Pagos) , SEEK_SET);

  if(!fread(&pago, sizeof(Pagos), 1, pFile)){
    pago.setIdPago(-1);
  }
    fclose(pFile);
    return pago;
}

int ArcPagos::leerTodos(Pagos pago[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   result=fread(pago,sizeof(Pagos),cantidad,pFile);
   fclose(pFile);
   return result;
}

int ArcPagos::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(Pagos);
   fclose(pFile);
   return cantidad;

}
int ArcPagos::getNuevoIdPago(){

 if(getCantidadRegistros() == 0){
  return 1;
 }

 return leer(getCantidadRegistros() - 1).getIdPago() + 1;
}

bool ArcPagos::eliminar(int pos){
    Pagos pago = leer(pos);

   if(pago.getIdPago()!=-1){
    pago.setEliminado(true);
    return guardar(pos,pago);
   }
   return false;

}
