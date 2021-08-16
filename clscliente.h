#ifndef CLSCLIENTE_H_INCLUDED
#define CLSCLIENTE_H_INCLUDED
///CLASE CLIENTE
///-------------------------------------------------------///

class Cliente: public Persona{

    protected:
        Direccion domicilio;
        bool Estado;
        int IDcliente;
        int iddos;

    public:
        ///constructor
        Cliente (bool e=true){
            Estado=e;
        }
        ///sets
        void setEstado(bool d){Estado=d;}
        void setIDcliente(int d) {IDcliente=d;}
        ///gets
        bool GetEstado(){return Estado;}
        int getIDcliente(){return IDcliente;}
        ///Metodos
        void cargar();
        void mostrar();
        void mostrar(int);
        bool leerDeDisco(int );
        bool grabarEnDisco();
        bool modificarEnDisco(int );
    };



void Cliente::mostrar(){
    cout<<"-----------------------------"<<endl;
    Persona::MostrarCliente();
    domicilio.Mostrar();
    cout<<ESTADOS[Estado] << endl;
}

void Cliente::mostrar(int y){
    Persona::mostrarCliente(y);
    gotoxy(122, y);
    domicilio.Mostrar(y);
    gotoxy(163, y);
    cout<<ESTADOS[Estado];
}

void Cliente::cargar(){
    Persona::Cargar();
    domicilio.cargar();
}



bool Cliente::leerDeDisco(int pos){
    FILE *pArchivo;

    pArchivo=fopen(ARCHIVOCLIENTE, "rb");
    if(pArchivo==NULL){return false;}
    fseek(pArchivo, sizeof (Cliente)*pos, 0); /// Nos ubicamos para leer
    if(fread(this, sizeof (Cliente), 1, pArchivo)){ /// Sacamos el registro del archivo
        fclose(pArchivo);
        return true;
    }
    fclose(pArchivo);
    return false;
}

bool Cliente::grabarEnDisco(){
    FILE *pArchivo;

    pArchivo=fopen(ARCHIVOCLIENTE, "ab");
    if(pArchivo==NULL){return false;}
    if(fwrite(this, sizeof (Cliente), 1, pArchivo)){
        fclose(pArchivo);
        return true;
    }
    fclose(pArchivo);
    return false;

}

bool Cliente::modificarEnDisco(int pos){
    FILE *pArchivo;

    pArchivo=fopen(ARCHIVOCLIENTE, "rb+");
    if (pArchivo==NULL){return false;}

    fseek(pArchivo, sizeof (Cliente)*pos, 0);
    if (fwrite(this, sizeof (Cliente), 1, pArchivo)){
        fclose(pArchivo);
        return true;
    }
    fclose(pArchivo);
    return false;
}
///-------------------------------------------------------///
#endif // CLSCLIENTE_H_INCLUDED
