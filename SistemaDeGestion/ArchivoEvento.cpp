# include<iostream>
#include "ArchivoEvento.h"

using namespace std;

ArchivoEvento::ArchivoEvento(string nombreArchivo)
    :_nombreArchivo(nombreArchivo){
}

bool ArchivoEvento::guardar (Eventos registro){
  FILE *pFile;
   bool result;

   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(Eventos),1,pFile);

   fclose(pFile);
   return result;
}

bool ArchivoEvento::guardar (int pos, Eventos registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(Eventos) , SEEK_SET);

  result = fwrite(&registro, sizeof(Eventos), 1, pFile);

  fclose(pFile);

  return result;
}

int ArchivoEvento::buscarIDEvento(int id){
      FILE*pFile;
      Eventos evento;
      int pos=-1;
     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }
     while (fread(&evento,sizeof(Eventos),1,pFile)){
        if (evento.getIdEvento()== id){
            pos=ftell(pFile)/sizeof (Eventos)-1;
            break;
        }
     }
     fclose(pFile);
     return pos;

}

Eventos ArchivoEvento::leer(int pos){
    FILE*pFile;
    Eventos evento;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return evento;
    }
    fseek(pFile, pos * sizeof(Eventos) , SEEK_SET);

  if(!fread(&evento, sizeof(Eventos), 1, pFile)){
    evento.setIdEvento(-1);
  }
    fclose(pFile);
    return evento;

}

int ArchivoEvento::leerTodos(Eventos evento[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }

   result=fread(evento,sizeof(Eventos),cantidad,pFile);
   fclose(pFile);
   return result;
}

int ArchivoEvento::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(Eventos);
   fclose(pFile);
   return cantidad;

}

int ArchivoEvento::getNuevoIdEvento(){

 if(getCantidadRegistros() == 0){
  return 1;
 }
 return leer(getCantidadRegistros() - 1).getIdEvento() + 1;
}

bool ArchivoEvento::eliminar(int pos){
    Eventos evento = leer(pos);

   if(evento.getIdEvento()!=-1){
    evento.setConfirmado(false);
    evento.setEliminado(true);
    return guardar(pos,evento);
   }
   return false;
}
