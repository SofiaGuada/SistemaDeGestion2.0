#include "ArcEventoServicios.h"
using namespace std;

ArcEventoServicios::ArcEventoServicios(string nombreArchivo)
   :_nombreArchivo(nombreArchivo){
}

bool ArcEventoServicios::guardar (EventoServicios registro){
  FILE *pFile;
   bool result;

   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(EventoServicios),1,pFile);

   fclose(pFile);
   return result;
}

bool ArcEventoServicios::guardar (int pos, EventoServicios registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(EventoServicios) , SEEK_SET);

  result = fwrite(&registro, sizeof(EventoServicios), 1, pFile);

  fclose(pFile);

  return result;

}

int ArcEventoServicios::buscarID(int idES){
      FILE*pFile;
      EventoServicios even;
      int pos=-1;
     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }
     while (fread(&even,sizeof(EventoServicios),1,pFile)){
        if (even.getIdEvento()== idES){
            pos=ftell(pFile)/sizeof (EventoServicios)-1;
            break;
        }
     }
     fclose(pFile);
     return pos;

}

EventoServicios ArcEventoServicios::leer(int pos){
  FILE*pFile;
    EventoServicios es;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return es;
    }
    fseek(pFile, pos * sizeof(EventoServicios) , SEEK_SET);

  if(!fread(&es, sizeof(EventoServicios), 1, pFile)){
    es.setEliminado(-1);
  }
    fclose(pFile);
    return es;

}
int ArcEventoServicios::leerTodos(EventoServicios evenSer[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }

   result=fread(evenSer,sizeof(EventoServicios),cantidad,pFile);
   fclose(pFile);
   return result;

}
int ArcEventoServicios::getCantidadRegistros(){
    FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(EventoServicios);
   fclose(pFile);
   return cantidad;

}
bool ArcEventoServicios::eliminar(int pos){
    EventoServicios Eservis = leer(pos);

   if(Eservis.getIdEvento()!=-1){
    Eservis.setEliminado(true);
    return guardar(pos,Eservis);
   }
   return false;
}
