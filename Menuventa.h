#ifndef MENUVENTA_H_INCLUDED
#define MENUVENTA_H_INCLUDED
///MENU VENTAS
///-------------------------------------------------------///
bool verificarstock(int cantidad, int idarticulo){
    Articulo art;
    int pos;
    pos=buscarArticulo(idarticulo);
    if(pos<0){return false;}
    art.leerDeDisco(pos);

    if(cantidad<1 || cantidad>art.getStock()){
        cout<<"SIN STOCK. LA CANTIDAD VENDIDA DEBE SER MAYOR A CERO Y MENOR  A: "<<art.getStock()<<endl;
        return false;
    }
    else{return true;}
}

bool controlstock(int cantidad, int idarticulo, bool mod){
     Articulo art;
     int pos=0,stockoriginal=0;
     pos=buscarArticulo(idarticulo);
     art.leerDeDisco(pos);
     stockoriginal=art.getStock();
     if(mod==true){
         art.setStock(stockoriginal-cantidad);
         if (art.getStock() == 0){
            art.setEstado(false);
         }

     }
     else{
        art.setStock(stockoriginal+cantidad);
        art.setEstado(true);
     }
     bool modifico=art.modificarEnDisco(pos);

     return modifico;
}

float calcularimporte(int cantidad,int idarticulo){
     Articulo art;
     int pos=0;
     float pu=0;
     int importe=0;
     pos=buscarArticulo(idarticulo);
     art.leerDeDisco(pos);
     pu=art.getPu();
     importe=cantidad*pu;
     return importe;
}

int buscarVenta(int Nventa){//recibe "id" del registro y devuelve la posicion donde se encuentra el registro
    Venta ven;
    int pos=0;
    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"rb");
    if(pVenta==NULL){return -1;}
    while((ven.leerDeDisco(pos))==1){
        if(ven.getNventa()==Nventa){
            fclose(pVenta);
            return pos;
        }
        pos++;
    }
    fclose(pVenta);
    return -2;
}

void AsignacionNumeroVenta (Venta &ven){

    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"rb");
    fseek(pVenta,-sizeof (Venta),2);
    fread(&ven,sizeof ven,1,pVenta);
    ven.setNventa(ven.getNventa()+1);
    fclose(pVenta);

}

int agregarVenta(){
    int r,contador=0;
    do{
    Venta ven;
    cout<<"REGISTAR VENTA"<<endl;

            AsignacionNumeroVenta(ven);
            cout<<"ESTE ES SU NUMERO DE VENTA: "<<ven.getNventa()<<endl;
            cout<<"COMPLETE LOS SIGUIENTES CAMPOS: "<<endl;

            ven.cargar();

            if(!ven.grabarEnDisco()){
            cout << "Error al guardar el archivo.";
            system("pause");
            return contador;
        }
        contador++;
        cout<<"DESEA AGREGAR OTRA VENTA? (y/n)?"<<endl;
        r=getch();
        system("cls");
    }while(r==121||r==89);
    return contador;
}

int BuscarVentaporNumero(int venta){//busca articulo por id y lo muestra si "estado" esta en true
    Venta ven;
    int pos=0;
    FILE *pVenta;
    pVenta=fopen(ARCHIVOVENTAS,"rb");
    if(pVenta==NULL){return -1;}
    pos=buscarVenta(venta);
    if(pos<0){return -2;}
    ven.leerDeDisco(pos);
    if(ven.getEstado()==true){ven.mostrar();}
    else{return -2;}
    fclose(pVenta);
}

int contarRegistrosVentas(){//Devuelve la cantidad de registros
    int c=0, tam;
    FILE *pVentas;
    pVentas=fopen(ARCHIVOVENTAS, "rb");
    if(pVentas==NULL){return -1;}
    fseek(pVentas, 0, 2);
    tam=ftell(pVentas);
    fclose(pVentas);
    c=tam/sizeof(Venta);
    return c;
}

void listarVentas(int linea){//lista todo el registro siempre y cuando "estado" este en true
    Venta registro;
    int pos=0;
    cartelListarVentas(++linea);
    while(registro.leerDeDisco(pos++)){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;

    }
}

void listarVentasDisp(int linea){//lista todo el registro siempre y cuando "estado" este en true
    Venta registro;
    int pos=0;
    cartelListarVentas(++linea);
    while(registro.leerDeDisco(pos++)){
        if(registro.getEstado()){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;
        }
    }
}

void listarVentasNODisp(int linea){//lista todo el registro siempre y cuando "estado" este en true
    Venta registro;
    int pos=0;
    cartelListarVentas(1);
    while(registro.leerDeDisco(pos++)){
        if(!registro.getEstado()){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;
        }
    }
}

bool devolverVenta(){//pone en false el estado de la venta y repone la cantidad de articulos vendida
    bool nodisponible=false;
    int r;
    int Nventa;
    Venta ven;
    cout<<"INGRESE ID DE VENTA: ";
    cin>>Nventa;

    int pos=buscarVenta(Nventa);
    if(pos<0){return false;}

    ven.leerDeDisco(pos);
    if(!ven.getEstado()){
        cout << "LA DEVOLUCION DE LA VENTA, YA FUE REALIZADA." << endl;
        return false;
    }
    ven.mostrar();
    cout<<"DEVOLVER VENTA (Y/N)?" <<endl;
    r=getch();
    if(r==121||r==89){
        ven.setestado(nodisponible);
        if((controlstock(ven.getCantidadVendida(),ven.getIDarticulo(),false))==0){cout<<"NO SE PUDO MODIFICAR STOCK"<<endl;}
        else{
            bool modifico=ven.modificarEnDisco(ven,pos);
            return modifico;
        }
    }
    else{return false;}
}

void seccionVenta(){
    int opc;
    do{
        opc=Menuventas();
        switch(opc){
        case 12:
            {
                int agregados=0;
                system("cls");
                agregados = agregarVenta();
                cout << agregados <<" VENTA/s CARGADA/s CON EXITO!"<<endl;
                system("pause");
                break;
            }
        case 13:
                system("cls");
                int nventa;
                cout<<"INGRESE NUMERO DE VENTA: "<<endl;
                cin>>nventa;
                if (BuscarVentaporNumero(nventa)==-2){cout<<endl<<"VENTA INEXISTENTE O ELIMINADA"<<endl;}
                system("pause");
                break;
        case 14:
                system("cls");
                elegirTipoListadoVentas();
                break;
        case 15:
                system("cls");
                if(devolverVenta()==false){cout<<endl<<"ERROR AL RECUPERAR VENTA"<<endl;}
                system("pause");
                break;
        }
    }while(opc!=16);
}

///-------------------------------------------------------///

void mostrarVectorVentas(Venta *pVentas, int cantVentas){
    int i;
    cartelListarVentas(1);
    int linea=0;
    for(i=0;i<cantVentas;i++){
        if(pVentas[i].getEstado()){
            pVentas[i].mostrar(linea+3);
            linea++;
        }

    }
}

void copiarAVectorVentas(Venta *pVentas, int cantVentas){
    int i;
    for(i=0;i<cantVentas;i++){
        pVentas[i].leerDeDisco(i);
    }
}

void ordenarIDVentas (Venta *pVentas, int cantVentas){
    int i, j, posMax;
    Venta aux;
    for(i=0;i<cantVentas-1;i++){
        posMax=i;
        for(j=i+1;j<cantVentas;j++){
            if(pVentas[j].getNventa()<pVentas[posMax].getNventa()){
                posMax=j;
            }
        }
        aux=pVentas[i];
        pVentas[i]=pVentas[posMax];
        pVentas[posMax]=aux;
    }



}

void ordenarImporteVentas ( Venta *pVentas, int cantVentas){
    int i, j, posMax;
    Venta aux;
    for(i=0;i<cantVentas-1;i++){
        posMax=i;
        for(j=i+1;j<cantVentas;j++){
            if(pVentas[j].getImporte()<pVentas[posMax].getImporte()){
                posMax=j;
            }
        }
        aux=pVentas[i];
        pVentas[i]=pVentas[posMax];
        pVentas[posMax]=aux;
    }

}

void ordenarUnidadesVendidas(Venta *pVentas, int cantVentas){
    int i, j, posMax;
    Venta aux;
    for(i=0;i<cantVentas-1;i++){
        posMax=i;
        for(j=i+1;j<cantVentas;j++){
            if(pVentas[j].getCantidadVendida()<pVentas[posMax].getCantidadVendida()){
                posMax=j;
            }
        }
        aux=pVentas[i];
        pVentas[i]=pVentas[posMax];
        pVentas[posMax]=aux;
    }

}

void listarVentasOrdenadas(int orden){
    int cantVentas=contarRegistrosVentas();
    Venta *pVentas;
    pVentas=new Venta[cantVentas];
    if(pVentas==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }
    copiarAVectorVentas(pVentas,cantVentas);
    switch(orden){
    case 1:
        ordenarIDVentas(pVentas, cantVentas);
        break;
    case 2:
        ordenarImporteVentas(pVentas, cantVentas);
        break;
    case 3:
        ordenarUnidadesVendidas(pVentas, cantVentas);
        break;
    }
    mostrarVectorVentas(pVentas, cantVentas);
    delete pVentas;
}

void elegirTipoListadoVentas(){
    int opc;
    do{
        opc=MenuListarVentas();
        switch(opc){
        case 12: ///Por defecto
            system("cls");
            listarVentas(1);
            system("pause");
            break;
        case 13: ///POR ID
            system("cls;");
            listarVentasOrdenadas(1);
            system("pause");
            break;
        case 14: ///POR IMPORTE
            system("cls;");
            listarVentasOrdenadas(2);
            system("pause");
            break;
        case 15: ///POR CANT VENDIDA
            system("cls;");
            listarVentasOrdenadas(3);
            system("pause");
            break;
        case 16:
            system("cls;");
            listarVentasDisp(1);
            system("pause");
            break;
        case 17:
            system("cls;");
            listarVentasNODisp(1);
            system("pause");
            break;
        }
    }while(opc!=18);
}

///-------------------------------------------------------///
#endif // MENUVENTA_H_INCLUDED
