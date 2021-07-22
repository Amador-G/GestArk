#ifndef CLSPROVEEDOR_H_INCLUDED
#define CLSPROVEEDOR_H_INCLUDED

class Proveedor{
private:
    int codigoProveedor;
    char nombreProveedor[25];
    Direccion dir;
    char mailProveedor[30];
    char telefonoProveedor[25];
    bool estado=true;
public:
    Proveedor (int c=0000,const char *d="00000"){
        codigoProveedor=c;
        strcpy(nombreProveedor,d);
        strcpy(mailProveedor,d);
        strcpy(telefonoProveedor,d);
        estado=false;
    }
    //sets
    void setCodigoProv(int d){codigoProveedor=d;}
    void setNombreProv(char *d){strcpy(nombreProveedor,d);}
    void setCalleProv(char *d){dir.setCalle(d);}
    void setNumProv(int d){dir.setNumero(d);}
    void setLocProv(char *d){dir.setLocalidad(d);}
    void setMailProv(char *d){strcpy(mailProveedor,d);}
    void setTelefonoProv(char *d){strcpy(telefonoProveedor,d);}
    void setEstado(bool e){estado=e;}
    //gets
    int getCodigoProv(){return codigoProveedor;}
    char *getNombreProv(){return nombreProveedor;}
    char *getCalleProv(){return dir.getCalle();}
    int getNumProv(){return dir.getNumero();}
    char *getLocProv(){return dir.getLocalidad();}
    char *getMailProv(){return mailProveedor;}
    char *getTelefonoProv(){return telefonoProveedor;}
    bool getEstado(){return estado;}
    //metodos
    void cargar();
    void mostrar();
    void mostrar(int y);
    bool leerDeDisco(int i);
    bool grabarEnDisco();
    bool modificarEnDisco(Proveedor reg, int pos);
    bool IDAutomatico();
};

void Proveedor::cargar(){
    cout<<"INGRESE NOMBRE DEL PROVEEDOR: ";
    cargarCadena(nombreProveedor,24);
    dir.cargar();
    cout<<"INGRESE MAIL DEL PROVEEDOR: ";
    cargarCadena(mailProveedor,29);
    cout<<"INGRESE TELEFONO DEL PROVEEDOR: ";
    cargarCadena(telefonoProveedor,24);
    estado=true;
}

void Proveedor::mostrar(){
    cout<<"------------------------"<<endl;
    cout<<"CODIGO PROVEEDOR: "<<codigoProveedor<<endl;
    cout<<"NOMBRE PROVEEDOR: "<<nombreProveedor<<endl;
    dir.Mostrar();
    cout<<"MAIL PROVEEDOR: "<<mailProveedor<<endl;
    cout<<"TELEFONO PROVEEDOR: "<<telefonoProveedor<<endl;
}

void Proveedor::mostrar(int y){
    gotoxy(4,y);
    cout<<codigoProveedor<<"\t";
    gotoxy(24,y);
    cout<<nombreProveedor<<"\t";
    gotoxy(60,y);
    cout<<telefonoProveedor<<"\t";
    gotoxy(80,y);
    cout<<mailProveedor<<"\t";
    gotoxy(115,y);
    dir.Mostrar(3);
}

bool Proveedor::leerDeDisco(int pos){
    FILE *pProveedores;
    pProveedores=fopen(ARCHIVOPROVEEDOR,"rb");
    if(pProveedores==NULL){return false;}
    fseek(pProveedores,pos*sizeof(Proveedor),0);
    bool leyo=fread(this,sizeof (Proveedor),1,pProveedores);
    fclose(pProveedores);
    return leyo;
}

bool Proveedor::grabarEnDisco(){
    FILE *pProveedor;
    pProveedor=fopen(ARCHIVOPROVEEDOR,"ab");
    if(pProveedor==NULL){return false;}
    bool escribio=fwrite(this,sizeof (Proveedor),1,pProveedor);
    fclose(pProveedor);
    return escribio;

}

bool Proveedor::modificarEnDisco(Proveedor reg, int pos){
    FILE *pProveedores;
    pProveedores=fopen(ARCHIVOPROVEEDOR,"rb+");
    if(pProveedores==NULL){return false;}
    fseek(pProveedores,pos*sizeof reg,0);
    bool escribio=fwrite(&reg,sizeof reg,1,pProveedores);
    fclose(pProveedores);
    return escribio;
}

bool Proveedor::IDAutomatico(){
    FILE *pProveedor;
    pProveedor=fopen(ARCHIVOPROVEEDOR,"rb");
    fseek(pProveedor,-sizeof (Proveedor),2);
    fread(this,sizeof (Proveedor),1,pProveedor);
    codigoProveedor+=1;
    fclose(pProveedor);
}
#endif // CLSPROVEEDOR_H_INCLUDED
