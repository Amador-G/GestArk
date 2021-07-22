#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED
#include "rlutil.h"
///FUNCIONES GLOBALES
bool verificarCliente(int );
bool verificarVendedor(int );

void cargarCadena(char *pal, int tam){//recibe un char y un int y ajusta la variable con memoria dinamica
  int i;
  fflush(stdin);
  for(i=0;i<tam;i++){
      pal[i]=cin.get();
	  if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}

///CARTELES

void cartelInicial(){
    rlutil::hidecursor();
    Sleep(500);
    rlutil::locate(75,20);
    cout<<"GESTARK";
    Sleep(500);
    rlutil::locate(69,22);
    cout<<"Gestion Empresarial";
    Sleep(1500);
}

void cartelListarArticulos(int y){
    gotoxy(1,y);
    cout<<"INVENTARIO: ";
    y+=2;
    gotoxy(4,y);
    cout<<"ID";
    gotoxy(13,y);
    cout<<"DESCRIPCION";
    gotoxy(28,y);
    cout<<"PRECIO UNITARIO";
    gotoxy(51,y);
    cout<<"STOCK";
    gotoxy(62,y);
    cout<<"ESTADO";
    gotoxy(79,y);
    cout<<"PROVEEDOR";
}

void BorrarArea(int x, int y){
int i,j;
    for (j=x; j < x+200; j++)
    {
        for (i=y; i<y+30; i++)
        {
            rlutil::locate(j,i);
            cout <<" ";
        }
    }
}

void cartelListarProveedores(int y){
    gotoxy(1,y);
    cout<<"PROVEEDORES: ";
    y++;
    gotoxy(4,y);
    cout<<"CODIGO";
    gotoxy(24,y);
    cout<<"PROVEEDOR";
    gotoxy(60,y);
    cout<<"TELEFONO";
    gotoxy(80,y);
    cout<<"MAIL";
    gotoxy(118,y);
    cout<<"DIRECCION";
}

void cartelListarVendedores(int y){
    gotoxy(4,y);
    cout<<"ID";
    gotoxy(8,y);
    cout<<"CATEGORIA";
    gotoxy(22,y);
    cout<<"DNI";
    gotoxy(34,y);
    cout<<"NOMBRE";
    gotoxy(59,y);
    cout<<"APELLIDO";
    gotoxy(84,y);
    cout<<"FECHA ING.";
    gotoxy(100,y);
    cout<<"EMAIL";
    gotoxy(140,y);
    cout<<"TELEFONO";
    gotoxy(160,y);
    cout<<"ESTADO";
}

void cartelListarClientes(int y){
    gotoxy(4,y);
    cout<<"DNI";
    gotoxy(19,y);
    cout<<"NOMBRE";
    gotoxy(40,y);
    cout<<"APELLIDO";
    gotoxy(58,y);
    cout<<"FECHA NAC.";
    gotoxy(80,y);
    cout<<"EMAIL";
    gotoxy(106,y);
    cout<<"TELEFONO";
    gotoxy(126,y);
    cout<<"DOMICILIO";
    gotoxy(165,y);
    cout<<"ESTADO";
}

void cartelListarVentas(int y){
    gotoxy(4,y);
    cout<<"NUM VENTA";
    gotoxy(19,y);
    cout<<"DNI CLIENTE";
    gotoxy(36,y);
    cout<<"ARTICULO";
    gotoxy(50,y);
    cout<<"DESCRIPCION";
    gotoxy(66,y);
    cout <<"ID VENDEDOR";
    gotoxy(83,y);
    cout<<"IMPORTE";
    gotoxy(101,y);
    cout<<"CANT VENDIDA";
    gotoxy(117,y);
    cout<<"FECHA DE VENTA";
    gotoxy(140,y);
    cout<<"ESTADO";
}

void cartelListarPedidos(int y){
    gotoxy(4,y);
    cout<<"NRO DE PEDIDO";
    gotoxy(20,y);
    cout<<"PRODUCTO";
    gotoxy(45,y);
    cout<<"CANT PEDIDA";
    gotoxy(60,y);
    cout<<"PROVEEDOR";
    gotoxy(82,y);
    cout<<"MAIL";
}

void cartelFinal(){
    system("cls");
    rlutil::hidecursor();
    rlutil::locate(75,20);
    cout<<"GESTARK";
    Sleep(500);
    rlutil::locate(69,21);
    cout<<"Gestion Empresarial";
    Sleep(500);
    rlutil::locate(70,24);
    cout<<"Desarrollado por";
    Sleep(500);
    rlutil::locate(70,25);
    cout<<"Eduardo Angel Chavero";
    Sleep(500);
    rlutil::locate(70,26);
    cout<<"Sebastian Re";
    Sleep(500);
    rlutil::locate(70,27);
    cout<<"Amador Gonzalez"<<endl;
    Sleep(900);
    system("cls");
    rlutil::locate(69,22);
    cout<<"Fin del programa";
    Sleep(500);
}



#endif // FUNCIONESGLOBALES_H_INCLUDED
