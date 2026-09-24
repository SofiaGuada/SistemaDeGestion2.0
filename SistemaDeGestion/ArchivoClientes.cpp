# include<iostream>
#include "ArchivoClientes.h"

using namespace std;

ArchivoClientes::ArchivoClientes(string nombreArchivo)
  :_nombreArchivo(nombreArchivo){
}


bool ArchivoClientes::guardar (Clientes registro){
  FILE *pFile;
  bool result;
 if(buscarDni(registro.getDNI())!=-1){
    return false;
   }
   pFile= fopen(_nombreArchivo.c_str(),"ab");

   if(pFile==nullptr) return false;

   result= fwrite(&registro, sizeof(Clientes),1,pFile);

   fclose(pFile);
   return result;
}



bool ArchivoClientes::guardar (int pos, Clientes registro){
  FILE *pFile;
  bool result;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }
  fseek(pFile, pos * sizeof(Clientes) , SEEK_SET);

  result = fwrite(&registro, sizeof(Clientes), 1, pFile);

  fclose(pFile);

  return result;
}


int ArchivoClientes::buscarIDcliente(int idcliente){
FILE*pFile;
      Clientes cliente;
      int pos=-1;

     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }

     while (fread(&cliente,sizeof(Clientes),1,pFile)){
        if (cliente.getIdCliente()== idcliente){
            pos=ftell(pFile)/sizeof (Clientes)-1;
            break;
        }
     }
     fclose(pFile); ///salgo
     return pos;

}



int ArchivoClientes::buscarDni(int dni){
FILE*pFile;
      Clientes cliente;
      int pos=-1;

     pFile = fopen(_nombreArchivo.c_str(), "rb");

     if(pFile==nullptr){
        return -1;
     }

     while (fread(&cliente,sizeof(Clientes),1,pFile)){
        if (cliente.getDNI()== dni){
            pos=ftell(pFile)/sizeof (Clientes)-1;
            break;
        }
     }
     fclose(pFile); ///salgo
     return pos;
}


///el id se va generando automaticamente

int ArchivoClientes::getNuevoID(){

 if(getCantidadRegistros() == 0){
  return 1;
 }

 return leer(getCantidadRegistros() - 1).getIdCliente() + 1;
}



Clientes ArchivoClientes::leer(int pos){
 FILE*pFile;
    Clientes cliente;

    pFile = fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return cliente;
    }
    fseek(pFile, pos * sizeof(Clientes),SEEK_SET);

  if(!fread(&cliente, sizeof(Clientes), 1, pFile)){
    cliente.setIdCliente(-1);
  }

    fclose(pFile);
    return cliente;
}


///
int ArchivoClientes::leerTodos(Clientes cliente[],int cantidad){
   FILE *pFile;
   int result;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }

   result=fread(cliente,sizeof(Clientes),cantidad,pFile);
   fclose(pFile);
   return result;
}


///
int ArchivoClientes::getCantidadRegistros(){
   FILE *pFile;
   int cantidad;
   pFile=fopen(_nombreArchivo.c_str(),"rb");

   if(pFile==nullptr){
    return 0;
   }
   fseek(pFile,0,SEEK_END);
   cantidad=ftell(pFile)/sizeof(Clientes);
   fclose(pFile);
   return cantidad;
}


///
bool ArchivoClientes::eliminar(int pos){
    Clientes cliente = leer(pos);

   if(cliente.getDNI()!=-1){
    cliente.setEliminado(true);
    return guardar(pos,cliente);
   }
   return false;
}
