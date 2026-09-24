# include<iostream>
#include <ctime>
#include "Fecha.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;

Fecha::Fecha()
 : _dia(1),_mes(1),_anio(2000){ ///obligatorio para composicion
}

Fecha::Fecha(int dia, int mes, int anio){
   setDia(dia);
   setMes(mes);
   setAnio(anio);
}

int Fecha::getDia(){
   return _dia;
}

int Fecha::getMes(){
   return _mes;
}

int Fecha::getAnio(){
   return _anio;
}

void Fecha::setDia(int dia){
    if(dia>=1 && dia <=31){
     _dia=dia;
    }
     else {
         cout<<"DIA INVALIDO "<<endl;
     }
}

void Fecha::setMes(int mes){
    if(mes>=1 && mes<=12){
          _mes=mes;
}
else {
    cout<<"MES INVALIDO "<<endl;
}
}

void Fecha::setAnio(int anio){
    if(anio>2000){
    _anio=anio;
}
else {
    cout<<"ANIO INVALIDO "<<endl;
}
}

bool Fecha::validarFecha(int dia, int mes, int anio) {

    if (anio < 2026 || anio > 2100)
        return false;

    if (mes < 1 || mes > 12 || dia < 1)
        return false;

    int diasMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if (mes == 2 && Bisiesto(anio))
        return dia <= 29;

    return dia <= diasMes[mes];
}

void Fecha::cargarFecha(){
int dia,mes,anio;
     while (true) {
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
        if (validarFecha(dia,mes,anio)) {
            _dia = dia;
            _mes = mes;
            _anio = anio;
            break;
        }
        setColor(LIGHTRED);
        cout << "FECHA INVALIDA. VUELVA A INTENTAR." << endl;
        setColor(WHITE);
    }
}

void Fecha::mostrarFecha(){
    cout<<_dia<<"/"<<_mes<<"/"<<_anio<<endl;
}


bool Fecha::operator>(Fecha& f2) {
    if (_anio > f2.getAnio()) return true;
    if (_anio < f2.getAnio()) return false;

    if (_mes > f2.getMes()) return true;
    if (_mes < f2.getMes()) return false;

    if (_dia > f2.getDia()) return true;
    return false;
}


bool Fecha::operator==(Fecha& f2) {
    if (_anio == f2.getAnio()&&_mes==f2.getMes()&&_dia==f2.getDia()){return true;}

    return false;
}
