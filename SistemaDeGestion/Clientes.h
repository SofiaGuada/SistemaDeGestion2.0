#pragma once
#include <string>

class Clientes {

   public:
       Clientes();
       Clientes(int idCliente,std::string nombre, std::string apellido, int dni, std::string email, int telefono, bool estado);

       ///get y set id
       int getIdCliente();
       void setIdCliente(int id);
       // get y set nombre y apellido
       std::string getNombre();
       void setNombre(std::string nombre);
       std::string getApellido();
       void setApellido(std::string apellido);
       //get y set dni
       int getDNI();
       void setDNI(int dni);
       //
       std::string getEmail();
       void setEmail(std::string email);
        int getTelefono();
        void setTelefono (int telefono);
        bool getEstado();
        void setEstado(bool estado);
        bool getEliminado();
        void setEliminado(bool eliminado);

        int getCantidadRegistros();

   private:
      int _IdCliente;
      char _Nombre[300];
      char _Apellido[300];
      int _DNI;
      char _Email[300];
      int _Telefono;
      bool _Estado;
      bool _Eliminado;

};
