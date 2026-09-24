#include "ArchivoServicios.h"

using namespace std;


ArchivoServicios::ArchivoServicios(string nombreArchivo)
  :_nombreArchivo(nombreArchivo){
}

bool ArchivoServicios::guardar (Servicios registro){
  FILE *pFile;
   bool result;

   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(Servicios),1,pFile);

   fclose(pFile);
   return result;
}

bool ArchivoServicios::guardar (int pos, Servicios registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(Servicios) , SEEK_SET);

  result = fwrite(&registro, sizeof(Servicios), 1, pFile);

  fclose(pFile);

  return result;
}

int ArchivoServicios::buscarIdServicios(int id){
      FILE*pFile;
      Servicios servis;
      int pos=-1;
     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }
     while (fread(&servis,sizeof(Servicios),1,pFile)){
        if (servis.getIdServicio()== id){
            pos=ftell(pFile)/sizeof (Servicios)-1;
            break;
        }
     }
     fclose(pFile);
     return pos;
}

Servicios ArchivoServicios::leer(int pos){
    FILE*pFile;
    Servicios servis;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return servis;
    }
    fseek(pFile, pos * sizeof(Servicios) , SEEK_SET);

  if(!fread(&servis, sizeof(Servicios), 1, pFile)){
    servis.setEliminado(-1);
  }
    fclose(pFile);
    return servis;

}

int ArchivoServicios::leerTodos(Servicios servis[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }

   result=fread(servis,sizeof(Servicios),cantidad,pFile);
   fclose(pFile);
   return result;
}

int ArchivoServicios::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(Servicios);
   fclose(pFile);
   return cantidad;
}

int ArchivoServicios::getNuevoIdServicio(){

 if(getCantidadRegistros() == 0){
  return 1;
 }

 return leer(getCantidadRegistros() - 1).getIdServicio() + 1;
}
int ArchivoServicios::buscarPosicionIdServicio(int idBuscado) {
    ArchivoServicios repo;
    int cantidad = repo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Servicios s = repo.leer(i);
        if (s.getIdServicio() == idBuscado) {
            return i;
        }
    }
    return -1;
}



bool ArchivoServicios::eliminar(int pos){
    Servicios servis = leer(pos);

   if(servis.getIdServicio()!=-1){
    servis.setEliminado(true);
    return guardar(pos,servis);
   }
   return false;
}
