#ifndef CLSDIRRECION_H_INCLUDED
#define CLSDIRRECION_H_INCLUDED
///CLASE DIRECCION
///-------------------------------------------------------///
class Direccion{
private:
    char Calle[35];
    int Numero;
    char Localidad[20];
public:
    Direccion(int n=0, const char *c="0000", const char* l="0000"){
        strcpy(Calle, c);
        Numero=n;
        strcpy(Localidad, l);
    }
      //sets
    void setCalle(char *d){strcpy(Calle, d);}
    void setNumero(int d){Numero=d;}
    void setLocalidad(char *d){strcpy(Localidad, d);}
    //gets
    char * getCalle(){return Calle;}
    int getNumero(){return Numero;}
    char * getLocalidad(){return Localidad;}
    //metodos
    void cargar();
    void Mostrar();
    void Mostrar(int i);
};
///METODOS
void Direccion::cargar(){
    cout<<"DIRECCION: "<<endl;
    cout<<"CALLE : "<<endl;
    cin.getline(Calle, 35);
    cout<<"NUMERACION: "<<endl;
    cin>>Numero;
    while(Numero<1){
        cout << "LA NUMERACION NO PUEDE SER MENOR A 1" << endl;
        cout << "INGRESE UNA NUMERACION CORRECTA: ";
        cin >> Numero;
    }
    cout<<"LOCALIDAD: "<<endl;
    cin.ignore();
    cin.getline(Localidad, 20);
}
void Direccion::Mostrar(){
    cout<<"DIRECCION: "<< endl;
    cout << Calle <<" "<<Numero<<", " << Localidad << endl;
}

void Direccion::Mostrar(int i){
    cout << Calle <<" "<<Numero<<", " << Localidad;
}
///-------------------------------------------------------///
#endif // CLSDIRRECION_H_INCLUDED
