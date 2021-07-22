#ifndef CLSVENTA_H_INCLUDED
#define CLSVENTA_H_INCLUDED
///CLASE Venta
///-------------------------------------------------------///
class Venta
{
private:
    int Nventa;
    int IDarticulo;
    int DNIcliente;
    int IDvendedor;
    float importe;
    int cantVendida;
    Fecha fe;
    bool estado;
public:
    //constructor
    Venta(int nv=0, int iart=0, int dc=0, int iv=0, float im=0, int cv=0,bool e=false)
    {
        Nventa=nv;
        IDarticulo=iart;
        DNIcliente=dc;
        IDvendedor=iv;
        importe=im;
        cantVendida=cv;
        estado=e;
    }
    //sets
    void setNventa(int v)
    {
        Nventa=v;
    }
    void setIDarticulo(int v)
    {
        IDarticulo=v;
    }
    void setDNIcliente(int v)
    {
        DNIcliente=v;
    }
    void setimporte(float v)
    {
        importe=v;
    }
    void setcantVendida(int v)
    {
        cantVendida=v;
    }
    void setestado(bool v)
    {
        estado=v;
    }
    //gets
    int getNventa()
    {
        return Nventa;
    }
    int getIDarticulo()
    {
        return IDarticulo;
    }
    int getDNIcliente()
    {
        return DNIcliente;
    }
    int getIDvendedor()
    {
        return IDvendedor;
    }
    float getImporte()
    {
        return importe;
    }
    int getCantidadVendida()
    {
        return cantVendida;
    }
    bool getEstado()
    {
        return estado;
    }
    Fecha getFe()
    {
        return fe;
    }

    //Metodos
    void cargar();
    void mostrar();
    void mostrar(int y);
    void VerificacionIDven (int id);
    void VerificacionIDart (int id);
    void VerificacionDNI(int dni);
    bool leerDeDisco(int pos);
    bool grabarEnDisco();
    bool modificarEnDisco(Venta venta, int pos);

};

#include "clspedido.h"

void Venta::cargar()
{
    int x, pos;
    Articulo aux;

    rlutil::locate(1,30);
    cout << "ARTICULOS DISPONIBLES: ";
    listarArticulosDisponibles(31);
    rlutil::locate(1,4);
    cout<<"INGRESE ID DE ARTICULO: ";cin>>x;
    VerificacionIDart(x);


    BorrarArea(1,29);
    rlutil::locate(1,30);
    cout << "CLIENTES DISPONIBLES: ";
    listarClientes(31);


    rlutil::locate(1,5);
    cout<<"INGRESE DNI DEL CLIENTE: "; cin >> x;
    VerificacionDNI (x);


    BorrarArea(1,29);
    rlutil::locate(1,30);
    cout << "VENDEDORES DISPONIBLES: ";
    listarVendedores(31);
    rlutil::locate(1,6);
    cout << "INGRESE ID DEL VENDEDOR: ";cin >> x;
    VerificacionIDven(x);


    BorrarArea(1,29);
    rlutil::locate(1,7);
    pos=buscarArticulo(IDarticulo);
    aux.leerDeDisco(pos);
   cout << "STOCK DISPONIBLE: "<<aux.getStock();

    rlutil::locate(1,8);
    cout<<"INGRESE CANTIDAD VENDIDA: ";cin>>cantVendida;

    while(verificarstock(cantVendida,IDarticulo)==0){

        cout<<"INGRESE CANTIDAD VENDIDA: ";cin>>cantVendida;
    }


    if((controlstock(cantVendida,IDarticulo,true))==0){cout<<"NO SE PUDO MODIFICAR STOCK"<<endl;}
        else{
            BorrarArea(1,8);

            rlutil::locate(1,8);
            cout << "CANTIDAD INGRESADA: "<<cantVendida;

            rlutil::locate(1,9);
            cout<<"STOCK ACTUALIZADO"<<endl;
        }

    setimporte (calcularimporte(cantVendida,IDarticulo));



    if ((aux.getStock() - cantVendida)< 10){

        if (generarPedido(aux,cantVendida) == true){
                rlutil::locate(1,10);
            cout << "PEDIDO GENERADO.";
        }

    }

    rlutil::locate(1,11);
    cout << "IMPORTE: " << importe << endl;
    rlutil::locate(1,12);
    cout<<"INGRESE FECHA DE VENTA"<<endl;
    rlutil::locate(1,13);
    fe.cargar();
    estado=true;
}


void Venta::VerificacionIDart(int id){

    Articulo reg;
    bool IDexistente = true;
    char Descripcion[25];

    FILE *ArchivoArticulo;
    ArchivoArticulo = fopen(ARCHIVOARTICULO, "rb");


    if (ArchivoArticulo == NULL)
    {
        cout << "ERROR AL ABRIR";
        system("pause");
    }



    do
    {

        if (IDexistente == false)
        {
            cout << "ID NO ENCONTRADO, POR FAVOR INGRESE UN ID EXISTENTE: ";
            cin >> id;
            cout << endl;


        }

        IDexistente = false;
        fseek(ArchivoArticulo, 0 * sizeof reg, 0);

        while (fread(&reg, sizeof reg, 1, ArchivoArticulo) == 1)
        {
            if (reg.getID() == id && reg.getEstado() == true)
            {
                IDexistente = true;
                IDarticulo = id;
                strcpy(Descripcion,reg.getDescripcion());
            }
        }


    }
    while (IDexistente == false);



    BorrarArea(1, 4);
    rlutil::locate(1,4);
    cout << "EL ARTICULO INGRESADO FUE: " << Descripcion;
    fclose(ArchivoArticulo);
}


void Venta::VerificacionDNI(int dni)
{

    Cliente reg;
    bool DNIexistente = true;
    char Nombre[25];

    FILE *ArchivoClientes;
    ArchivoClientes = fopen(ARCHIVOCLIENTE, "rb");
    if (ArchivoClientes == NULL)
    {
        cout << "ERROR AL ABRIR";
        system("pause");
    }

    do
    {

        if (DNIexistente == false)
        {
            cout << "DNI NO ENCONTRADO, POR FAVOR INGRESE UN DNI EXISTENTE: ";
            cin >> dni;
            cout << endl;



        }

        DNIexistente = false;
        fseek(ArchivoClientes, 0 * sizeof reg, 0);

        while (fread(&reg, sizeof reg, 1, ArchivoClientes) == 1)
        {
            if (reg.getDni() == dni && reg.GetEstado() == true)
            {
                DNIexistente = true;
                DNIcliente = dni;
                strcpy(Nombre,reg.getNombre());
            }
        }


    }
    while (DNIexistente == false);



    BorrarArea(1, 5);
    rlutil::locate(1,5);
    cout << "EL CLIENTE INGRESADO FUE: " << Nombre;

    fclose(ArchivoClientes);
}

void Venta::VerificacionIDven(int id)
{

    Vendedor reg;
    bool IDexistente = true;
    char Nombre[25];

    FILE *ArchivoVendedor;
    ArchivoVendedor = fopen(ARCHIVOVENDEDOR, "rb");


    if (ArchivoVendedor == NULL)
    {
        cout << "ERROR AL ABRIR";
        system("pause");
    }



    do
    {

        if (IDexistente == false)
        {
            cout << "ID NO ENCONTRADO, POR FAVOR INGRESE UN ID EXISTENTE: ";
            cin >> id;
            cout << endl;


        }

        IDexistente = false;
        fseek(ArchivoVendedor, 0 * sizeof reg, 0);

        while (fread(&reg, sizeof reg, 1, ArchivoVendedor) == 1)
        {
            if (reg.getIdVendedor() == id && reg.getEstado() == true)
            {
                IDexistente = true;
                IDvendedor = id;
                strcpy(Nombre,reg.getNombre());
            }
        }


    }
    while (IDexistente == false);



    BorrarArea(1, 6);
    rlutil::locate(1,6);
    cout << "EL VENDEDOR INGRESADO FUE: " << Nombre;
    fclose(ArchivoVendedor);
}

void Venta::mostrar()
{
    cout<<"-----------------------------"<<endl;
    cout<<"NUMERO DE VENTA: "<<Nventa<<endl;
    cout<<"CLIENTE DNI: "<<DNIcliente<<endl;
    cout<<"ARTICULO : "<<IDarticulo<<endl;
    cout<<"IMPORTE DE VENTA: "<<importe<<endl;
    cout<<"CANTIDAD VENDIDA: "<<cantVendida<<endl;
    cout<<"FECHA DE VENTA: "<<"\t";
    fe.mostrar();
    cout << endl;
}

void Venta::mostrar(int y){
    Articulo aux;
    int pos;
        gotoxy(4,y);
        cout<<Nventa<<"\t";
        gotoxy(19,y);
        cout<<DNIcliente<<"\t";
        gotoxy(36,y);
        cout<<IDarticulo<<"\t";
        pos=buscarArticulo(IDarticulo);
        aux.leerDeDisco(pos);
        gotoxy(50,y);
        cout<<aux.getDescripcion()<<"\t";
        gotoxy(66,y);
        cout<<IDvendedor<<"\t";
        gotoxy(83,y);
        cout<<importe<<"\t";
        gotoxy(101,y);
        cout<<cantVendida<<"\t";
        gotoxy(117,y);
        fe.mostrar();cout<<"\t";
        gotoxy(140,y);
        if(estado==true){cout<<"DISPONIBLE"<<endl;}
        else{cout<<"NO DISPONIBLE"<<endl;}

}



bool Venta::leerDeDisco(int pos)
{
    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"rb");
    if(pVenta==NULL)
    {
        return false;
    }
    fseek(pVenta,pos*sizeof(Venta),0);
    bool leyo=fread(this,sizeof (Venta),1,pVenta);
    fclose(pVenta);
    return leyo;
}

bool Venta::grabarEnDisco()
{
    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"ab");
    if(pVenta==NULL)
    {
        return false;
    }
    bool escribio=fwrite(this,sizeof (Venta),1,pVenta);
    fclose(pVenta);
    return escribio;

}

bool Venta::modificarEnDisco(Venta v, int pos)
{
    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"rb+");
    if(pVenta==NULL)
    {
        return false;
    }
    fseek(pVenta,pos*sizeof (v),0);
    bool escribio=fwrite(&v,sizeof v,1,pVenta);
    fclose(pVenta);
    return escribio;
}
///-------------------------------------------------------///


#endif // CLSVENTA_H_INCLUDED
