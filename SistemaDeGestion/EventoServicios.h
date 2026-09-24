#pragma once

class EventoServicios
{
    public:
        EventoServicios(){}
        EventoServicios(int idEvento,int idServicio,int cantidad,float precio,std::string nombreEvento,std::string nombreServicio);
        int getIdEvento(){return _idEvento;}
        void setIdEvento(int idEvento){_idEvento=idEvento;}
        int getIdServicio(){return _idServicio;}
        void setIdServicio(int idServicio){_idServicio=idServicio;}
        int getCantidadContratado(){return _cantidad;}
        void setCantidadContratado(int cantidad){_cantidad=cantidad;}
        float getPrecioUnitario(){return _precioUnitario;}
        void setPrecioUnitario(float precio){_precioUnitario=precio;}
        bool getActivo(){return _activo;}
        void setActivo(bool activo){_activo=activo;}

        bool getEliminado(){return _eliminado;}
        void setEliminado(bool eliminado){_eliminado=eliminado;}
        std::string getNombreServicios(){return _NombreServicios;}
        void setNombreServicio(std::string nombreServicios);
        std::string getNombreEvento(){return _NombreEvento;}
        void setNombreEvento(std::string nombre);

    private:
        int _idEvento;
        int _idServicio;
       	char _NombreEvento[300];
	    char _NombreServicios[300];
        int _cantidad;
        float _precioUnitario;
        bool _activo;
        bool _eliminado;
};
