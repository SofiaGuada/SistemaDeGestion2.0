#include "ArcDetallePago.h"
using namespace std;

ArcDetallePago::ArcDetallePago(string nombreArchivo)
   :_nombreArchivo(nombreArchivo){
}

bool ArcDetallePago::guardar (DetallePago registro){
   FILE *pFile;
   bool result;

   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(DetallePago),1,pFile);

   fclose(pFile);
   return result;

}

bool ArcDetallePago::guardar (int pos, DetallePago registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(DetallePago) , SEEK_SET);

  result = fwrite(&registro, sizeof(DetallePago), 1, pFile);

  fclose(pFile);

  return result;
}

int ArcDetallePago::buscarIdPago(int id){
      FILE*pFile;
      DetallePago Detallepago;
      int pos=-1;
     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }
     while (fread(&Detallepago,sizeof(DetallePago),1,pFile)){
        if (Detallepago.getIdPago()== id){
            pos=ftell(pFile)/sizeof (DetallePago)-1;
            break;
        }
     }
     fclose(pFile);
     return pos;
}

DetallePago ArcDetallePago::leer(int pos){
    FILE*pFile;
    DetallePago Detallepago;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return Detallepago;
    }
    fseek(pFile, pos * sizeof(DetallePago) , SEEK_SET);

  if(!fread(&Detallepago, sizeof(DetallePago), 1, pFile)){
    Detallepago.setIdPago(-1);
  }
    fclose(pFile);
    return Detallepago;
}

int ArcDetallePago::leerTodos(DetallePago Detallepago[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   result=fread(Detallepago,sizeof(DetallePago),cantidad,pFile);
   fclose(pFile);
   return result;
}

int ArcDetallePago::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(DetallePago);
   fclose(pFile);
   return cantidad;
}

///para eliminar
//
//bool ArcDetallePago::eliminar(int pos){
//    DetallePago Depago = leer(pos);
//
//   if(Depago.getIdPago()!=-1){
//    Depago.setEliminado(true);
//    return guardar(pos,Depago);
//   }
//   return false;
//}

