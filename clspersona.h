#ifndef CLSPERSONA_H_INCLUDED
#define CLSPERSONA_H_INCLUDED

///CLASE PERSONA
///-------------------------------------------------------///


class Persona{

protected:
    int Dni;
    char Nombre[25];
    char Apellido[25];
    char Email[30];
    char Telefono[20];
    Fecha FechaDeNacimiento;

public:

    Persona (const int D=0, const char *n="0000", const char *a="0000", const char *e="0000", const char* T="0000"){
        Dni=D;
        strcpy(Nombre, n);
        strcpy(Apellido, a);
        strcpy(Email, e);
        strcpy(Telefono, T);
    }

    void Cargar();
    void MostrarCliente();
    void MostrarVendedor();
    void MostrarVendedor(int);
    void mostrarCliente(int);

    void setNombre(const char *n){strcpy(Nombre, n);}
    void setApellido(const char *a){strcpy(Apellido, a);}
    void setEmail(const char* e){strcpy(Email, e);}
    void setDni(const int d){Dni=d;}
    void setTel(const char * T){strcpy(Telefono, T);}
    void setFechaDeNacimiento(Fecha f){FechaDeNacimiento=f;}


    int getDni() {return Dni;}
    char * getNombre() {return Nombre;}
    char * getApellido() {return Apellido;}
    char * getEmail() {return Email;}
    char * getTel() {return Telefono;}
    Fecha getFecha() {return FechaDeNacimiento;}

};

void Persona::Cargar(){
    bool vCli=false, vVen=false;
    cout << "DNI: ";
    cin >> Dni;
    while (Dni < 0) {
        cout << "INGRESE UN DNI VALIDO: ";
        cin >> Dni;
    }
    vCli=verificarCliente(Dni);
    vVen=verificarVendedor(Dni);
    while(vCli==true || vVen==true){
        if (vCli){
            cout<<"EL DNI DEL CLIENTE YA SE ENCUENTRA REGISTRADO."<<endl;
            cout << "Ingrese un DNI valido: ";
            cin >> Dni;
        }
        if (vVen){
            cout<<"EL DNI DEL VENDEDOR YA SE ENCUENTRA REGISTRADO."<<endl;
            cout << "Ingrese un DNI valido: ";
            cin >> Dni;
        }
        vCli=verificarCliente(Dni);
        vVen=verificarVendedor(Dni);
    }

    BorrarArea(1,1);
    rlutil::locate(1,1);
    cout << "EL DNI INGRESADO FUE: " << Dni;

    rlutil::locate(1,2);
    cout << "NOMBRE: ";
    cin.ignore();
    cin.getline(Nombre, 25);
    rlutil::locate(1,3);
    cout << "APELLIDO: ";
    cin.getline(Apellido, 25);
    rlutil::locate(1,4);
    cout << "FECHA DE NACIMIENTO: ";
    FechaDeNacimiento.cargar();
    BorrarArea(1,4);
    rlutil::locate(1,4);
    cout << "FECHA DE NACIMIENTO INGRESADA: ";
    rlutil::locate(1,5);
    FechaDeNacimiento.mostrar();
    rlutil::locate(1,6);
    cout << "EMAIL: ";
    cin.ignore();
    cin.getline(Email, 30);
    rlutil::locate(1,7);
    cout << "TELEFONO: ";
    cin.getline(Telefono, 20);

}

void Persona::MostrarCliente(){

    cout << "DNI: " << Dni << endl;
    cout << "NOMBRE: " << Nombre << endl;
    cout << "APELLIDO: " << Apellido << endl;
    cout << "FECHA DE NACIMIENTO: ";
    FechaDeNacimiento.mostrar();
    cout << endl;
    cout << "EMAIL: " << Email << endl;
    cout << "TELEFONO: " << Telefono << endl;
}

void Persona::MostrarVendedor(){

    cout << "DNI: " << Dni << endl;
    cout << "NOMBRE: " << Nombre << endl;
    cout << "APELLIDO: " << Apellido << endl;
    cout << "FECHA DE NACIMIENTO: ";
    FechaDeNacimiento.mostrar();
    cout << endl;
    cout << "EMAIL: " << Email << endl;
    cout << "TELEFONO: " << Telefono << endl;
}

void Persona::MostrarVendedor(int y){

    cout << Dni;
    gotoxy(34,y);
    cout << Nombre;
    gotoxy(59,y);
    cout << Apellido;
    gotoxy(84,y);
    FechaDeNacimiento.mostrar();
    gotoxy(100,y);
    cout << Email;
    gotoxy(145,y);
    cout << Telefono<<endl;
}

void Persona::mostrarCliente(int y){
    gotoxy(4,y);
    cout << Dni;
    gotoxy(19,y);
    cout << Nombre;
    gotoxy(38,y);
    cout << Apellido;
    gotoxy(57,y);
    FechaDeNacimiento.mostrar();
    gotoxy(72,y);
    cout << Email;
    gotoxy(106,y);
    cout << Telefono<<endl;
}


///-------------------------------------------------------///
#endif // CLSPERSONA_H_INCLUDED
