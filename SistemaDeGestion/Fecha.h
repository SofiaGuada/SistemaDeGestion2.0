#pragma once
#include <string>

class Fecha
{
    public:
        Fecha();
        Fecha(int dia, int mes, int anio);

        int getDia();
        void setDia(int dia);
        int getMes();
        void setMes(int mes);
        int getAnio();
        void setAnio(int anio);

        bool Bisiesto(int anio){
          return (anio%4==0&&(anio%100!=0||anio%400==0));
        }

        bool validarFecha(int dia, int mes, int anio);
        void cargarFechaActual();

        void cargarFecha();
        void mostrarFecha();

  /// sobrecarga de operadores
       bool operator >(Fecha& f2);
       bool operator==(Fecha& f2);

    private:
        int _dia,_mes,_anio;
};

