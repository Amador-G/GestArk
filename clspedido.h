#ifndef CLSPEDIDO_H_INCLUDED
#define CLSPEDIDO_H_INCLUDED

class Pedido{
private:
    int nPedido;
    char producto[25];
    int cantSolicitada;
    char ProvaSolicitar[25];
    char envioMail[30];
public:
    Pedido(int d=0,const char *e="0000"){
        nPedido=d;
        strcpy(producto,e);
        cantSolicitada=d;
        strcpy(ProvaSolicitar,e);
        strcpy(envioMail,e);
    }
    //sets
    void setnPedido(int d){nPedido=d;}
    void setProducto(char *d){strcpy(producto,d);}
    void setCantSolicitada(int d){cantSolicitada=d;}
    void setProvasolicitar(char *d){strcpy(ProvaSolicitar,d);}
    void setEnvioMail(char *d){strcpy(envioMail,d);}
    //gets
    int getnPedido(){return nPedido;}
    char *getProducto(){return producto;}
    int getcantSolicitada(){return cantSolicitada;}
    char *getProvaSolicitar(){return ProvaSolicitar;}
    char *getEnvioMail(){return envioMail;}
    //metodos
    void mostrar();
    void mostrar(int y);
    bool leerDeDisco(int i);
    bool grabarEnDisco();
    bool modificarEnDisco(Pedido reg, int pos);
};

void Pedido::mostrar(){
    cout<<"NUMERO DE PEDIDO: "<<nPedido<<endl;
    cout<<"PRODUCTO: "<<producto<<endl;
    cout<<"CANTIDAD SOLICITADA: "<<cantSolicitada<<endl;
    cout<<"PROVEEDOR: "<<ProvaSolicitar<<endl;
    cout<<"MAIL: "<<envioMail<<endl;
}

void Pedido::mostrar(int y){
    gotoxy(4,y);
    cout<<nPedido<<"\t";
    gotoxy(20,y);
    cout<<producto<<"\t";
    gotoxy(45,y);
    cout<<cantSolicitada<<"\t";
    gotoxy(60,y);
    cout<<ProvaSolicitar<<"\t";
    gotoxy(82,y);
    cout<<envioMail;
}

bool Pedido::leerDeDisco(int pos){
    FILE *pPedido;
    pPedido=fopen(ARCHIVOPEDIDO,"rb");
    if(pPedido==NULL){return false;}
    fseek(pPedido,pos*sizeof(Pedido),0);
    bool leyo=fread(this,sizeof (Pedido),1,pPedido);
    fclose(pPedido);
    return leyo;
}

bool Pedido::grabarEnDisco(){
    FILE *pPedido;
    pPedido=fopen(ARCHIVOPEDIDO,"ab");
    if(pPedido==NULL){return false;}
    bool escribio=fwrite(this,sizeof (Pedido),1,pPedido);
    fclose(pPedido);
    return escribio;
}

bool Pedido::modificarEnDisco(Pedido reg, int pos){
    FILE *pPedido;
    pPedido=fopen(ARCHIVOPEDIDO,"rb+");
    if(pPedido==NULL){return false;}
    fseek(pPedido,pos*sizeof reg,0);
    bool escribio=fwrite(&reg,sizeof reg,1,pPedido);
    fclose(pPedido);
    return escribio;
}

void AsignacionNumeroPedido (Pedido &ven){
    FILE *pPedido;
    pPedido=fopen(ARCHIVOPEDIDO,"rb");
    fseek(pPedido,-sizeof (Pedido),2);
    fread(&ven,sizeof ven,1,pPedido);
    ven.setnPedido(ven.getnPedido()+1);
    fclose(pPedido);
}

bool generarPedido(Articulo &aux, int cantvendida){
    int i=0,v=0,ap=0,cantapedir=0;
    Pedido regp;
    Proveedor regpr;
    Venta regv;

    while(regp.leerDeDisco(i++)){
                //aca busca que el producto no este pedido
        if(strcmp(aux.getDescripcion(),regp.getProducto())== 0){
            return false;
        }
    }

        //asigna numero de pedido
        AsignacionNumeroPedido(regp);

        //aca le graba el nombre del producto
        regp.setProducto(aux.getDescripcion());

        while(regv.leerDeDisco(v++)){

                //aca recorre el archivo ventas y acumula cantvendida
            if(aux.getID()==regv.getIDarticulo()){
              cantapedir+=regv.getCantidadVendida();
            }

        }

        cantapedir+=cantvendida;

        regp.setCantSolicitada(cantapedir);
            bool Encontrado=false;

        while(regpr.leerDeDisco(ap++) && Encontrado == 0){
            if(aux.getIdProveedor()==regpr.getCodigoProv()){
                regp.setEnvioMail(regpr.getMailProv());
                regp.setProvasolicitar(regpr.getNombreProv());
                    Encontrado = true;
                    rlutil::locate(1,25);
            }

        }

        if (Encontrado == false){
                rlutil::locate(1,25);
            return false;

        }


        if(!regp.grabarEnDisco()){cout<<"ERROR AL GENERAR PEDIDO"<<endl; return false;}

        return true;
}

#endif // CLSPEDIDO_H_INCLUDED
