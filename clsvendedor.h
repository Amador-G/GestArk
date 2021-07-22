#ifndef CLSVENDEDOR_H_INCLUDED
#define CLSVENDEDOR_H_INCLUDED

///CLASE VENDEDOR
///-------------------------------------------------------///


class Vendedor: public Persona{
protected:
    int idVendedor;
    int Categoria;
    bool Estado;
public:

    Vendedor(const int i=1,bool e=true){
        idVendedor=i;
        Categoria=i;
        Estado=e;
    }


    //sets

    void setIdVendedor(int d){idVendedor=d;}
    void setcategoria(int d){Categoria=d;}
    void setEstado(bool d){Estado=d;}
    //gets

    int getIdVendedor(){return idVendedor;}
    int getCategoria(){return Categoria;}
    bool getEstado(){return Estado;}
    //metodos
    bool iDAutomatico();
    void cargar();
    void mostrar();
    void mostrar(int);
    void VerificacionID(int ID);
    bool leerDeDisco(int pos);
    bool grabarEnDisco();
    bool modificarEnDisco(int pos);

};

bool Vendedor::iDAutomatico(){
    FILE *pArchivo;
    pArchivo=fopen(ARCHIVOVENDEDOR,"rb");
    if(pArchivo==NULL){return false;}
    fseek(pArchivo,-sizeof (Vendedor),2);
    fread(this, sizeof (Vendedor),1,pArchivo);
    idVendedor+=1;
    fclose(pArchivo);
    return true;
}

void Vendedor::cargar(){
    Persona::Cargar();
    cout<<"CATEGORIA DEL VENDEDOR (1 A 5): ";
    cin>>Categoria;
    while (Categoria<0 || Categoria>5){
        cout << "NO EXISTE CATEGORIA PARA EL NUMERO INGRESADO." << endl;
        cout << "INGRESE UNA CATEGORIA VALIDA (1 A 5): ";
        cin >> Categoria;
    }
    BorrarArea(1, 8);
    rlutil::locate(1, 8);
    cout << "CATEGORIA INGRESADA >" << CATEGORIAS[Categoria-1] << "<" << endl;

}

void Vendedor::mostrar(){
    cout<<"-----------------------------"<<endl;
    cout<<"ID VENDEDOR: "<<idVendedor<<endl;
    cout<<"CATEGORIA VENDEDOR: "<<CATEGORIAS[Categoria-1]<<endl;
    Persona::MostrarVendedor();

}


void Vendedor::mostrar(int y){
    gotoxy(4,y);
    cout<<idVendedor;
    gotoxy(8,y);
    cout<<CATEGORIAS[Categoria-1];
    gotoxy(22,y);
    Persona::MostrarVendedor(y);
    gotoxy(160, y);
    cout<<ESTADOS[Estado];

}

bool Vendedor::leerDeDisco(int pos){
    FILE *pArchivo;

    pArchivo=fopen(ARCHIVOVENDEDOR, "rb");
    if(pArchivo==NULL){return false;}
    fseek(pArchivo, sizeof (Vendedor)*pos, 0); /// Nos ubicamos para leer
    if(fread(this, sizeof (Vendedor), 1, pArchivo)){ /// Sacamos el registro del archivo
        fclose(pArchivo);
        return true;
    }
    fclose(pArchivo);
    return false;
}

bool Vendedor::grabarEnDisco(){
    FILE *pVendedor;
    pVendedor=fopen(ARCHIVOVENDEDOR  ,"ab");
    if(pVendedor==NULL){return false;}
    bool escribio=fwrite(this,sizeof (Vendedor),1,pVendedor);
    fclose(pVendedor);
    return escribio;

}

bool Vendedor::modificarEnDisco(int pos){
    FILE *pArchivo;

    pArchivo=fopen(ARCHIVOVENDEDOR, "rb+");
    if (pArchivo==NULL){return false;}

    fseek(pArchivo, sizeof (Vendedor)*pos, 0);
    if (fwrite(this, sizeof (Vendedor), 1, pArchivo)){
        fclose(pArchivo);
        return true;
    }
    fclose(pArchivo);
    return false;
}


///-------------------------------------------------------///
#endif // CLSVENDEDOR_H_INCLUDED
