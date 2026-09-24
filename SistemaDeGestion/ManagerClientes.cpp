# include<iostream>
#include "ManagerClientes.h"
#include "Necesario.h"
#include "rlutil.h"
using namespace std;
using namespace rlutil;


ManagerClientes::ManagerClientes()
{
    //ctor
}


void ManagerClientes::CargarCliente() {
    int idClientes, dni, telefono;
    string nombre, apellido, email;
    bool estado = false;
    bool eliminar = false;

    int cantLinea = 2;
    int lineaError = cantLinea + 8;

    setColor(LIGHTMAGENTA);
    cout << "********* CARGAR CLIENTE **********" << endl << endl;
    setColor(WHITE);

    idClientes = _repo.getNuevoID();

    gotoxy(1, cantLinea + 1); cout << "ID CLIENTE: #" << idClientes;
    gotoxy(1, cantLinea + 2); cout << "NOMBRE: ";
    gotoxy(1, cantLinea + 3); cout << "APELLIDO:";
    gotoxy(1, cantLinea + 4); cout << "DNI: ";
    gotoxy(1, cantLinea + 5); cout << "EMAIL: ";
    gotoxy(1, cantLinea + 6); cout << "TELEFONO: ";

    gotoxy(9, cantLinea + 2);
    nombre = cargarCadena();

    while (!Valido(nombre)) {
        mostrarError("ERROR: Nombre invalido (solo letras)", lineaError);
        gotoxy(9, cantLinea + 2);
        cout << "                    ";
        gotoxy(9, cantLinea + 2);
        nombre = cargarCadena();
    }

    mostrarError("", lineaError);

    gotoxy(10, cantLinea + 3);
    apellido = cargarCadena();

    while (!Valido(apellido)) {
        mostrarError("ERROR: Apellido invalido (solo letras)", lineaError);
        gotoxy(10, cantLinea + 3);
        cout << "                    ";
        gotoxy(10, cantLinea + 3);
        apellido = cargarCadena();
    }

    mostrarError("", lineaError);

    while (true) {
        gotoxy(5, cantLinea + 4);
        cout << "        ";
        gotoxy(5, cantLinea + 4);

        dni=cargarEntero(5,cantLinea + 4,lineaError);

        if (validadDNI(dni)) {
            mostrarError("ESTE DNI YA EXISTE", lineaError);
            continue;
        }
        break;
    }
    mostrarError("", lineaError);

    gotoxy(8, cantLinea + 5);

    email = cargarCadena();

    while (!emailValido(email)) {
        mostrarError("EMAIL INVALIDO", lineaError);
        gotoxy(8, cantLinea + 5);
        cout << "                         ";
        gotoxy(8, cantLinea + 5);
        email = cargarCadena();
    }

    mostrarError("", lineaError);

    while (true) {
        gotoxy(10, cantLinea + 6);
        cout << "           ";
        gotoxy(10, cantLinea + 6);

        telefono=cargarEntero(10, cantLinea +6,lineaError);

    if (telefono <= 0) {
        mostrarError("El telefono debe ser un numero positivo", lineaError);
        continue;
    }
    if (telefono < 10000000) {
    mostrarError("Telefono demasiado corto", lineaError);
    continue;
    }
    break;
}

    system("pause");
    system("cls");

    setColor(YELLOW);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "ID: #" << idClientes << endl;
    cout << "NOMBRE: " << nombre << endl;
    cout << "APELLIDO: " << apellido << endl;
    cout << "DNI: " << dni << endl;
    cout << "EMAIL: " << email << endl;
    cout << "TELEFONO: " << telefono << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    setColor(WHITE);

    int opcion;
    cout << "CONFIRMAR ? (1-Si / 0-No): ";

    while (true) {
        cin >> opcion;
        if (cin.fail() || (opcion != 0 && opcion != 1)) {
            cin.clear();
            cin.ignore(9999, '\n');
            setColor(RED);
            cout << "OPCION INVALIDA, INGRESE (1-Si / 0-No): ";
            setColor(WHITE);
            continue;
        }
        break;
    }

    if (opcion == 0) {
        setColor(RED);
        cout << "REGISTRO CANCELADO" << endl;
        setColor(WHITE);
        return;
    }

    estado = true;

    Clientes cliente(idClientes, nombre, apellido, dni, email, telefono, estado);
    cliente.setEliminado(eliminar);

    if (_repo.guardar(cliente)) {
        setColor(GREEN);
        cout << "CLIENTE GUARDADO CORRECTAMENTE" << endl;
        setColor(WHITE);
    } else {
        setColor(RED);
        cout << "ERROR AL GUARDAR AL CLIENTE" << endl;
        setColor(WHITE);
    }
}

void ManagerClientes::mostrarClientes(Clientes cliente){
   cout<<"ID CLIENTE: #" <<cliente.getIdCliente()<<endl;
   cout<<"NOMBRE: "<<cliente.getNombre()<<endl;
   cout<<"APELLIDO: "<<cliente.getApellido()<<endl;
   cout<<"DNI: "<<cliente.getDNI()<<endl;
   cout<<"EMAIL: "<<cliente.getEmail()<<endl;
   cout<<"TELEFONO / CELULAR: "<<cliente.getTelefono()<<endl;
   cout<<"ESTADO: "<< (cliente.getEstado() ? "REGISTRADO ":"NO REGISTRADO ")<<endl;
  if(cliente.getEliminado()){
    setColor(RED);
   cout<<" [ELIMINADO] "<<endl;
    setColor(WHITE);
  }
  cout<<endl;
}

void ManagerClientes::ListarClientes(){
  int cantidad = _repo.getCantidadRegistros();
  bool encontrado=false;

    setColor(LIGHTMAGENTA);
    cout<<"-------------------------------";
    cout<<"------HISTORIAL DE CLIENTES------";
    cout<<"-------------------------------"<<endl;
    setColor(WHITE);
  for (int i = 0; i < cantidad; i++){
    Clientes cliente = _repo.leer(i);
    if(!cliente.getEliminado()){
      setColor(YELLOW);
      mostrarClientes(cliente);
      encontrado=true;
      setColor(LIGHTMAGENTA);
      cout << "--------------------------" << endl;
      setColor(WHITE);
  }
}
  if(!encontrado){
    setColor(RED);
    cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
    setColor(WHITE);
  }
}

void ManagerClientes::buscarClientesID(){
    int id,cantLinea=0, lineaError=cantLinea+4;
    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~";
    cout<<"~~~~~BUSCAR ID CLIENTE~~~~~";
    cout<<"~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(YELLOW);

    cout<<"ID DE CLIENTE: #";
 while (true) {
        gotoxy(18, cantLinea + 2);
        cout << "        ";
        gotoxy(18, cantLinea + 2);

     id=cargarEntero(18, cantLinea + 2,lineaError);

    if(id<0){
        mostrarError("EL ID NO PUEDE SER MENOR A 0 ", lineaError);
        setColor(YELLOW);
        continue;
    }
    if(id==0){
        mostrarError("Vuelve al menu anterior",lineaError);
        cout<<endl;
        return;
    }
    break;
}

    int cantidad = _repo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        Clientes cliente = _repo.leer(i);
        if (cliente.getIdCliente() == id) {
            setColor(GREEN);
            cout<<"-----CLIENTE ENCONTRADO-----"<<endl;
            setColor(WHITE);
            mostrarClientes(cliente);
            setColor(GREEN);
            cout<<"---------------------------" << endl;
            setColor(WHITE);
            encontrado = true;
        }
    }
    if (!encontrado) {
    setColor(RED);
    cout<<"NO SE ENCONTRO AL CLIENTE "<<endl;
    setColor(WHITE);
    }
}

void ManagerClientes::buscarClientesDNI(){
    int dni,cantLinea=0,lineaError= cantLinea+4;
    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~";
    cout<<"~~~~BUSCAR POR DNI~~~~";
    cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(WHITE);

    cout<<"DNI CLIENTE: ";

  while (true) {
        gotoxy(14, cantLinea + 2);
        cout << "        ";
        gotoxy(14, cantLinea + 2);

        dni=cargarEntero(14, cantLinea +2,lineaError);

        if(dni<0){
            mostrarError("Tiene que ser un numero positivo",lineaError);
            continue;
        }
        break;
    }

    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    for (int i=0;i<cantidad;i++){
        Clientes cliente=_repo.leer(i);
        if(cliente.getDNI()== dni){
            setColor(GREEN);
            cout<<"-----CLIENTE ENCONTRADO-----"<<endl;
            setColor(WHITE);
            mostrarClientes(cliente);
            setColor(GREEN);
            cout<<"---------------------------" << endl;
            encontrado = true;
        }
     }
    if(!encontrado){
    setColor(RED);
    cout<<"NO SE ENCONTRO AL CLIENTE "<<endl;
    setColor(WHITE);
    }
}

void ManagerClientes::buscarClientesApellido(){
   string apellido;
   int cantLinea=0,lineaError=cantLinea+4;

   setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~";
   cout<<"~~~~BUSCAR POR APELLIDO~~~~";
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   setColor(WHITE);

    cout<<"APELLIDO: ";

     gotoxy(11, cantLinea + 2);
     apellido = cargarCadena();

    while (!Valido(apellido)) {
        mostrarError("ERROR: Apellido invalido (solo letras)", lineaError);
        gotoxy(11, cantLinea + 2);
        cout << "                    ";
        gotoxy(11, cantLinea + 2);
        apellido = cargarCadena();
    }

   int cantidad=_repo.getCantidadRegistros();
   bool encontrado=false;

   for(int i=0;i<cantidad;i++){
    Clientes cliente =_repo.leer(i);
    if(cliente.getApellido()==apellido){
        setColor(GREEN);
        cout<<"-----CLIENTE ENCONTRADO-----"<<endl<<endl;
        setColor(WHITE);
        mostrarClientes(cliente);
        setColor(GREEN);
        cout<<"---------------------------" << endl;
        encontrado = true;
        }
    }

    if(!encontrado){
        setColor(RED);
        cout<<"NO SE ENCONTRO AL CLIENTE "<<endl;
        setColor(WHITE);
    }
}

void ManagerClientes::buscarClientes(){
    int opcion;
    do {
    system("cls");
    setColor(YELLOW);
    cout<<"~~~ BUSCAR CLIENTE ~~~"<<endl;
    cout<<"1. BUSCAR POR ID "<<endl;
    cout<<"2. BUSCAR POR DNI "<<endl;
    cout<<"3. BUSCAR POR APELLIDO"<<endl;
    cout<<"0. SALIR "<<endl;
    cout<<"OPCION: ";
    cin>>opcion;
    setColor(WHITE);
    system("cls");

switch (opcion){
   case 1:
      buscarClientesID();
      break;
   case 2:
    buscarClientesDNI();
    break;
   case 3:
    buscarClientesApellido();
   case 0:
    break;
  default:
    setColor(RED);
    cout<<"Opcion invalida, intente nuevamente "<<endl;
    setColor(WHITE);
    break;
   }
   system("pause");

}while(opcion!=0);
}

void ManagerClientes::eliminar(){
  int opcion;
  do{
    system("cls");
    setColor(LIGHTRED);
  cout<<"------------------------------"<<endl;
  cout<<"1. ELIMINAR CLIENTE "<<endl;
  cout<<"2. MOSTRAR CLIENTES ELIMINADOS "<<endl;
  cout<<"0. SALIR "<<endl;
  cout<<"------------------------------"<<endl;
  cout<<"OPCION: ";
  setColor(WHITE);
  cin>>opcion;

  system("cls");
  switch(opcion){
  case 1:
      eliminarClientes();
      break;
  case 2:
    mostrarClientesEliminados();
    break;
  case 0:
    return;
default:
    setColor(RED);
    cout<<"Opcion invalida, intente nuevamente "<<endl;
    setColor(WHITE);
    break;
   }
   system("pause");
  }while(opcion!=0);
}

void ManagerClientes::eliminarClientes(){
  int id,pos;
   Clientes cliente;
   char eliminar;
   bool encontrado=false;
   int cantidad=_repo.getCantidadRegistros();
   setColor(LIGHTMAGENTA);
   cout<<"==============================";
   cout<<"=====CLIENTES DISPONIBLES=====";
   cout<<"=============================="<<endl;
   setColor(YELLOW);

   for(int i=0;i<cantidad;i++){
    cliente=_repo.leer(i);
    if(!cliente.getEliminado()){
      cout<<"#"<<cliente.getIdCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDNI()<<")"<<endl;
      encontrado=true;
    }
   }
   if(!encontrado){
    setColor(RED);
    cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
    setColor(WHITE);
    return;
   }
   cout<<endl;
   system("pause");
   system("cls");

   int cantLinea=0;
   int lineaError=cantLinea+3;

   setColor(LIGHTCYAN);
   gotoxy(1, 1); cout<<"---- ELIMINAR CLIENTE ----";
   setColor(WHITE);
   gotoxy(1, 2); cout<<"INGRESE ID DE CLIENTE:#";

  while (true) {
        gotoxy(24, cantLinea + 2);
        cout<< "                ";
        gotoxy(24, cantLinea + 2);

       id=cargarEntero(24,cantLinea + 2,lineaError);

    if(id==0){
        mostrarError("VUELVE AL MENU ANTERIOR ",lineaError);
        return;
    }
    break;
}

    pos=_repo.buscarIDcliente(id);

   if(pos==-1){
    mostrarError("EL CLIENTE NO EXISTE!",lineaError);
    return ;
  }

  system("pause");
  system("cls");

  cliente= _repo.leer(pos);

  setColor(LIGHTMAGENTA);
  gotoxy(1, 2); cout<<"INFORMACION DEL CLIENTE ";

  cout<<endl<<endl;

  setColor(YELLOW);

  mostrarClientes(cliente);

  cout<<endl;
  setColor(GREY);
  cout<<"QUIERE ELIMINAR? S/N ";
  cin>>eliminar;

  if (eliminar== 's' or eliminar == 'S'){

  if(_repo.eliminar(pos)){
    setColor(GREEN);
    cout<<"EL CLIENTE FUE ELIMINADO"<<endl;
    setColor(WHITE);
  }
  else {
    setColor(RED);
    cout<<"OCURRIO UN ERROR AL ELIMINAR AL CLIENTE "<<endl;
    setColor(WHITE);
  }
  }
}

void ManagerClientes::mostrarClientesEliminados(){
    int cantidad=_repo.getCantidadRegistros();
    bool encontrado=false;

    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(YELLOW);
    for(int i=0;i<cantidad;i++){
        Clientes cliente=_repo.leer(i);
       if(cliente.getEliminado()){
        mostrarClientes(cliente);
        encontrado=true;
        setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        setColor(WHITE);
        return;
       }
    }
    if(!encontrado){
        setColor(RED);
        cout<<"NO HAY CLIENTES ELIMINADOS "<<endl;
        setColor(WHITE);
        return;
    }
}

void ManagerClientes::ActivarCliente(){
  int id, pos;
  char eliminar;
  int cantC=_repo.getCantidadRegistros();
  bool encontrado=false;
    setColor(LIGHTMAGENTA);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~";
    cout<<"~~~~ CLIENTES ELIMINADOS ~~~~";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    setColor(YELLOW);

    for(int i=0;i<cantC;i++){
    Clientes cliente=_repo.leer(i);
    if(cliente.getEliminado()){
        cout<<"~ID: #"<<cliente.getIdCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDNI()<<") "<<endl;
        encontrado=true;
    }
  }
  if(!encontrado){
    setColor(RED);
    cout<<"NO HAY CLIENTES ELIMINADOS "<<endl;
    setColor(WHITE);
    return;
  }
  cout<<endl;

  system("pause");
  system("cls");

  int cantLinea=0,lineaError=cantLinea+6;

   setColor(LIGHTMAGENTA);
       cout<<"~~~~~~~~~~~~~~~~~~~~~~";
       cout<<"~~~~ ACTIVAR CLIENTE ~~~~";
       cout<<"~~~~~~~~~~~~~~~~~~~~~~";
   setColor(WHITE);
   gotoxy(1,3); cout<<"ID CLIENTE:#";

   while(true){
      gotoxy(14, cantLinea + 3);
      cout << "               ";
      gotoxy(14, cantLinea + 3);

     id=cargarEntero(14,cantLinea + 3,lineaError);

    if(id==0){
        mostrarError("VUELVE AL MENU ANTERIOR ",lineaError);
        return;
    }
    break;
 }
  pos=_repo.buscarIDcliente(id);

  if(pos==-1){
    mostrarError("EL CLIENTE NO EXISTE ",lineaError);
    return;
  }

  Clientes cliente =_repo.leer(pos);

  if(!cliente.getEliminado()){
    mostrarError("EL CLIENTE NO ESTA ELIMINADO ",lineaError);
    return;
  }


  setColor(YELLOW);
  gotoxy(1,7);cout<<"INFORMACION DEL CLIENTE ELIMINADO ";
  cout<<endl<<endl;

  mostrarClientes(cliente);

  cout<<endl;
  setColor(GREY);
  cout<<"QUIERE VOLVER ACTIVAR? S/N: ";
  setColor(WHITE);

  cin>>eliminar;

   if(eliminar=='s' or eliminar=='S'){
    cliente.setEliminado(false);
    cliente.setEstado(true);
   }

   if(_repo.guardar(pos,cliente)){
    setColor(GREEN);
    cout<<" CLIENTE ACTIVO NUEVAMENTE "<<endl;
    setColor(WHITE);
   }
   else {
    setColor(RED);
    cout<<"OCURRIO UN ERROR AL ACTIVAR "<<endl;
    setColor(WHITE);
   }
}


void ManagerClientes::ordanadosAlfabeticamente(){
    setColor(LIGHTMAGENTA);
    cout<<"-----------------------";
    cout<<"----ORDENADOS ALFABETICAMENTE----";
    cout<<"-----------------------"<<endl;
    setColor(YELLOW);

  int cantidad = _repo.getCantidadRegistros();
//memoria dinamica

  Clientes*cliente;

  cliente=new Clientes[cantidad];

  _repo.leerTodos(cliente,cantidad);

  for(int i=0;i<cantidad;i++){ ///metodo burbuja
        bool intercambio=false;
    for(int j=0;j<cantidad -1-i;j++){
       if(cliente[j].getApellido()>cliente[j+1].getApellido()){
        Clientes aux= cliente[j];
        cliente[j]=cliente[j+1];
        cliente[j+1]=aux;
        intercambio=true;
       }
    }
    if(!intercambio){
        break;
    }
  }
  for (int i = 0; i < cantidad; i++)
  {
    Clientes clientes=_repo.leer(i);
    if(!clientes.getEliminado()){
    mostrarClientes(cliente[i]);
    setColor(LIGHTMAGENTA);
    cout << "------------------------" << endl;
    setColor(YELLOW);
  }
  }
  setColor(WHITE);
  delete[] cliente;
}

void ManagerClientes::modificarClientes() {
	int id;
	int cant=_repo.getCantidadRegistros();
	bool encontrado=false;
	setColor(LIGHTMAGENTA);
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~";
   cout<<"~~~~ CLIENTES PARA MODIFICAR ~~~~";
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   setColor(YELLOW);

	for(int i=0; i<cant; i++){
        Clientes cliente=_repo.leer(i);
        if(!cliente.getEliminado()){
            cout<<"ID: #"<<cliente.getIdCliente()<<" "<<cliente.getNombre()<<" "<<cliente.getApellido()<<" ("<<cliente.getDNI()<<") "<<endl;
            encontrado=true;
        }
	}
	if(!encontrado){
        setColor(LIGHTRED);
        cout<<"NO HAY CLIENTES REGISTRADOS "<<endl;
        setColor(WHITE);
        return;
	}
	cout<<endl;
	system("pause");
	system("cls");

  int cantLinea=0;
  int lineaError=cantLinea+4;

   setColor(LIGHTMAGENTA);
   gotoxy(1,1); cout<<"-----------------------------------"<<endl;
   gotoxy(1,2); cout<<"INGRESE EL ID CLIENTE A MODIFICAR: #";
   gotoxy(1,3); cout<<"-----------------------------------"<<endl;
   setColor(WHITE);

   while(true){
          gotoxy(38, cantLinea + 2);
          cout << "                                         ";
          gotoxy(38, cantLinea + 2);

          id=cargarEntero(38,cantLinea +2,lineaError);

    if(id==0){
        gotoxy(1,lineaError);
        mostrarError("Vuelve al menu anterior",lineaError);
        return;
    }
    break;
 }

	int pos = _repo.buscarIDcliente(id);

	if (pos == -1) {
        mostrarError("Cliente No encontrado",lineaError);
        cout<<endl;
		return;
	}

	Clientes cliente = _repo.leer(pos);

    system("pause");
	system("cls");

	if(!cliente.getEliminado()){
    setColor(YELLOW);
	mostrarClientes(cliente);
	setColor(WHITE);
	}
	else{
        setColor(RED);
        cout<<" ESTE REGISTRO ESTA ELIMINADO "<<endl;
        setColor(WHITE);
        return;
	}

	system("pause");
	system("cls");

    int opcion;
do {
    system("cls");
    setColor(LIGHTMAGENTA);
    cout<<"QUE QUIERE MODIFICAR? "<<endl;
    setColor(YELLOW);
    cout<<endl;
    cout<<"1. NOMBRE: "<<endl;
    cout<<"2. APELLIDO: "<<endl;
    cout<<"3. DNI: "<<endl;
    cout<<"4. EMAIL: "<<endl;
    cout<<"5. TELEFONO / CELULAR: "<<endl;
    cout<<"0. SALIR Y GUARDAR "<<endl<<endl;
    cout<<"INGRESE LA OPCION DESEADA: ";
    setColor(WHITE);


    while(!(cin>>opcion)){
    cin.clear();
    cin.ignore(9999,'\n');
    setColor(RED);
    cout<<"Debe ingresar un numero: ";
    setColor(WHITE);
}
	system("cls");

    switch (opcion) {
     case 1: {
            string nombre;
            int cantLinea=0;
            int lineaError=cantLinea+4;

           setColor(LIGHTCYAN);
           gotoxy(1,1); cout<<"NOMBRE ACTUAL: "<<cliente.getNombre()<<endl;
           setColor(WHITE);
           gotoxy(1,2); cout<<"INGRESE NUEVO NOMBRE: ";
           gotoxy(22, cantLinea + 2); nombre = cargarCadena();

      while (!Valido(nombre)) {
          mostrarError("ERROR: Nombre invalido (solo letras)", lineaError);
          gotoxy(22, cantLinea + 2);
          cout << "                    ";
          gotoxy(22, cantLinea + 2);
          nombre = cargarCadena();
        }

          mostrarError("", lineaError);

          cliente.setNombre(nombre);

        break;
        }
    case 2: {
            string apellido;
            int cantLinea=0;
            int lineaError=cantLinea+4;

            setColor(LIGHTCYAN);
            gotoxy(1,1); cout<<"APELLIDO ACTUAL: "<<cliente.getApellido()<<endl;
            setColor(WHITE);
            gotoxy(1,2); cout<<"INGRESE APELLIDO: ";
            gotoxy(19,cantLinea+2); apellido = cargarCadena();

       while (!Valido(apellido)) {
           mostrarError("ERROR: Apellido invalido (solo letras)", lineaError);
           gotoxy(19, cantLinea + 2);
           cout << "                    ";
           gotoxy(19, cantLinea + 2);
           apellido = cargarCadena();
        }

             cliente.setApellido(apellido);

            break;
        }
    case 3: {
            int dni;
            int cantLinea=0;
            int lineaError=cantLinea+4;
            gotoxy(1,1);
            setColor(LIGHTCYAN);
            cout<<"DNI ACTUAL: "<<cliente.getDNI();
            setColor(WHITE);
            gotoxy(1,2);cout<<"INGRESE DNI: ";

         while (true) {
            gotoxy(14, cantLinea + 2);
            cout << "        ";
            gotoxy(14, cantLinea + 2);

            dni = cargarEntero(14, cantLinea + 2, lineaError);

           if (validadDNI(dni)) {
              mostrarError("ESTE DNI YA EXISTE", lineaError);
              continue;
            }

             break;
             }

         cliente.setDNI(dni);

       break;
      }
    case 4: {
            string email;
            int cantLinea=0;
            int lineaError=cantLinea+4;

            setColor(LIGHTCYAN);
            gotoxy(1,1); cout<<"EMAIL ACTUAL: "<<cliente.getEmail();
            setColor(WHITE);
            gotoxy(1,2); cout<<"INGRESE EMAIL: ";
            gotoxy(15,cantLinea+2); email = cargarCadena();

     while (!emailValido(email)) {
            mostrarError("EMAIL INVALIDO", lineaError);
            gotoxy(15, cantLinea + 2);
            cout << "                         ";
            gotoxy(15, cantLinea + 2);
            email = cargarCadena();
       }

        cliente.setEmail(email);

        break;
        }
    case 5: {
            int cel;
            int cantLinea=0;
            int lineaError=cantLinea+4;

            setColor(LIGHTCYAN);
            gotoxy(1,1); cout<<"NRO DE CELULAR ACTUAL: "<<cliente.getTelefono();
            setColor(WHITE);
            gotoxy(1,2); cout<<"INGRESE NUMERO DE CELULAR: ";

        while (true) {
            gotoxy(28, cantLinea + 2);
            cout << "           ";
            gotoxy(28, cantLinea + 2);

        cel = cargarEntero(28, cantLinea + 2, lineaError);

            if (cel < 10000000) {
                mostrarError("Telefono demasiado corto", lineaError);
         continue;
    }
        break;
    }

    cliente.setTelefono(cel);

    break;
        }
    case 0:
            break;
    default:
            setColor(RED);
            cout<<"OPCION INVALIDA."<<endl;
            setColor(WHITE);
            break;
    }
	system("pause");

} while(opcion!=0);

	if (_repo.guardar(pos, cliente)) {
        setColor(GREEN);
		cout<< "CLIENTE MODIFICADO CORRECTAMENTE."<<endl;
        setColor(WHITE);
	} else {
	    setColor(RED);
		cout<< "ERROR AL MODIFICAR EL CLIENTE."<<endl;
		setColor(WHITE);
	}
}

///validar que no haya dos clientes con un mismo DNI

bool ManagerClientes::validadDNI(int dni){
  int cantidad=_repo.getCantidadRegistros();

  for(int i=0;i<cantidad;i++){
    Clientes cliente=_repo.leer(i);
    if(!cliente.getEliminado() && cliente.getDNI()==dni){
        return true;
    }
  }
  return false;
}

