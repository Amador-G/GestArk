#ifndef MENUPROVEEDORES_H_INCLUDED
#define MENUPROVEEDORES_H_INCLUDED
///MENU PROVEEDOR
///-------------------------------------------------------///
bool agregarProveedor(){//agrega un registro articulo
    int r, contador=0;
    do{
    Proveedor reg;
    reg.IDAutomatico();
    cout<<"CODIGO AUTONUMERICO ASIGNADO: "<<reg.getCodigoProv()<<endl;
    reg.cargar();
    if(!reg.grabarEnDisco()){
            cout << "Error al guardar el archivo.";
            system("pause");
            return contador;
        }
        contador++;
        cout<<"DESEA AGREGAR OTRO PROVEEDOR (y/n)?"<<endl;
        r=getch();
        system("cls");
    }while(r==121||r==89);
    return contador;
}

int buscarProveedor(int codigo){//recibe "id" del registro y devuelve la posicion donde se encuentra el registro
    Proveedor reg;
    int pos=0;
    while((reg.leerDeDisco(pos))==1){
        if(reg.getCodigoProv()==codigo){
            return pos;
        }
        pos++;
        }
    return -1;
}

int BuscarProveedorCod(int id){//busca articulo por id y lo muestra si "estado" esta en true
    Proveedor reg;
    int pos=0;
    pos=buscarProveedor(id);
    if(pos<0){return -2;}
    reg.leerDeDisco(pos);
    if(reg.getEstado()==true){reg.mostrar();}
    else{return -2;}
}

int contarRegistrosProv(){//Devuelve la cantidad de registros
    int c=0, tam;
    FILE *pProveeedor;
    pProveeedor=fopen(ARCHIVOPROVEEDOR,"rb");
    if(pProveeedor==NULL){return -1;}
    fseek(pProveeedor, 0, 2);
    tam=ftell(pProveeedor);
    fclose(pProveeedor);
    c=tam/sizeof(Proveedor);
    return c;
}

void copiarArchivoProveedor(Proveedor *pProveeedor, int cantProveedor){
    int i;
    for(i=0;i<cantProveedor;i++){
        pProveeedor[i].leerDeDisco(i);
    }
}

void mostrarVectorProveedor(Proveedor *pProveedor, int cantProveedor){
    int i, linea=1;
    cartelListarProveedores(linea);
    for(i=0;i<cantProveedor;i++){
        if(pProveedor[i].getEstado()){
            pProveedor[i].mostrar(linea+3);
            cout<<endl;
            linea++;
        }
    }
}

void ordenarAZProveedor(Proveedor *pProveeedor, int cantProveedor){
    int i, j, posMin;
    Proveedor aux;
    for(i=0;i<cantProveedor-1;i++){
        posMin=i;
        for(j=i+1;j<cantProveedor;j++){
                if(strcmp(pProveeedor[j].getNombreProv(), pProveeedor[posMin].getNombreProv())<0){
                        posMin=j;
                }
        }
        aux=pProveeedor[i];
        pProveeedor[i]=pProveeedor[posMin];
        pProveeedor[posMin]=aux;
    }
}

void listarProveedorPorDefecto(int linea){//lista todo el registro como fue cargado siempre y cuando "estado" sea true
    Proveedor registro;
    int pos=0;
    cartelListarProveedores(linea);

    while(registro.leerDeDisco(pos++)){
      if(registro.getEstado()){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;
       }
    }
}

void listarProveedoresOrdenados(int orden){
    int cantProveedores=contarRegistrosProv();
    Proveedor *pProveedor;
    pProveedor=new Proveedor[cantProveedores];
    if(pProveedor==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }
    copiarArchivoProveedor(pProveedor,cantProveedores);
    switch(orden){
    case 1:
        listarProveedorPorDefecto(1);
        break;
    case 2:
        ordenarAZProveedor(pProveedor, cantProveedores);
        break;
    }
    mostrarVectorProveedor(pProveedor, cantProveedores);
    delete pProveedor;
}

void listarProveedores(){
    int opc;
    do{
        opc=MenuListarProveedores();
        switch(opc){
        case 12:
            system("cls;");
            listarProveedoresOrdenados(1);
            cout << endl;
            system("pause");
            break;
        case 13:
            system("cls;");
            listarProveedoresOrdenados(2);
            cout << endl;
            system("pause");
            break;
        }
    }while(opc!=14);
}

bool modificarmailProveedor(){
    char mailProv[30];
    int id;
    Proveedor reg;
    cout<<"INGRESE EL CODIGO DEl PROVEEDOR: ";
    cin>>id;
    int pos=buscarProveedor(id);
    if(pos<0){return false;}
    reg.leerDeDisco(pos);
    if(reg.getEstado()==true){
        reg.mostrar();
        cout<<"INGRESE NUEVO MAIL: ";
        cargarCadena(mailProv,29);
        reg.setMailProv(mailProv);
        bool modifico=reg.modificarEnDisco(reg,pos);
        return modifico;
    }
    else{return false;}
}

bool modificarTelProveedor(){
    char telProv[25];
    int id;
    Proveedor reg;
    cout<<"INGRESE EL CODIGO DEl PROVEEDOR: ";
    cin>>id;
    int pos=buscarProveedor(id);
    if(pos<0){return false;}
    reg.leerDeDisco(pos);
    if(reg.getEstado()==true){
            reg.mostrar();
            cout<<"INGRESE NUEVO TELEFONO: ";
            cargarCadena(telProv,24);
    reg.setTelefonoProv(telProv);
    bool modifico=reg.modificarEnDisco(reg,pos);
    return modifico;
    }
    else{return false;}
}

bool modificarDirProveedor(){
    char calle[35],loc[35];
    int num,id;
    Proveedor reg;
    cout<<"INGRESE EL CODIGO DEl PROVEEDOR: ";
    cin>>id;
    int pos=buscarProveedor(id);
    if(pos<0){return false;}
    reg.leerDeDisco(pos);
    if(reg.getEstado()==true){
        reg.mostrar();
        cout<<"INGRESE NUEVA DIRECCION: "<<endl;
        cout<<"CALLE: ";
        cargarCadena(calle,34);
        reg.setCalleProv(calle);
        cout<<"NUMERACION: ";
        cin>>num;
        while(num<1){
            cout << "LA NUMERACION NO PUEDE SER MENOR A 1" << endl;
            cout << "INGRESE UNA NUMERACION CORRECTA: ";
            cin >> num;
        }
        reg.setNumProv(num);
        cout<<"LOCALIDAD: ";
        cargarCadena(loc,34);
        reg.setLocProv(loc);
        bool modifico=reg.modificarEnDisco(reg,pos);
        return modifico;
    }
    else{return false;}
}

bool modificarDatosProveedor(){
    int opc;
    do{
        opc=MenuModificarProveedores();
        switch(opc){
        case 12:
            system("cls");
            modificarmailProveedor();
            system("pause");
            break;
        case 13:
            system("cls");
            modificarDirProveedor();
            system("pause");
            break;
        case 14:
            system("cls");
            modificarTelProveedor();
            system("pause");
            break;
        }
    }while(opc!=15);
}

bool elmininarProveedor(){
    bool nodisponible=false;
    int r;
    int id;
    Proveedor reg;
    cout<<"INGRESE EL CODIGO DEL PROVEEDOR: ";
    cin>>id;
    int pos=buscarProveedor(id);
    if(pos<0){return false;}
    reg.leerDeDisco(pos);
    reg.mostrar();
    cout<<"ELIMINAR PROVEEDOR (Y/N)?";
    r=getch();
    if(r==121||r==89){
            reg.leerDeDisco(pos);
            reg.setEstado(nodisponible);
            bool modifico=reg.modificarEnDisco(reg,pos);
            return modifico;
    }
    else{
        return false;
    }
}

bool recuperoProveedor(){
    bool disponible=true;
    int r;
    int id;
    Proveedor reg;
    cout<<"INGRESE EL CODIGO DEL ARTICULO: ";
    cin>>id;
    int pos=buscarProveedor(id);
    if(pos<0){return false;}
    reg.leerDeDisco(pos);
    reg.mostrar();
    cout<<"DAR EL ALTA PROVEEDOR (Y/N)?";
    r=getch();
    if(r==121||r==89){
        reg.leerDeDisco(pos);
        reg.setEstado(disponible);
        bool modifico=reg.modificarEnDisco(reg,pos);
        return modifico;
    }
    else{
        return false;
    }
}

void seccionProveedores(){
    int opc;
    do{
        opc=MenuProveedores();
        switch(opc){
           case 12:
               {
                int agregados=0;
                system("cls");
                agregados = agregarProveedor();
                cout << agregados <<" PROVEEDOR/es CARGADO/s CON EXITO!"<<endl;
                system("pause");
                break;
            }
            break;
           case 13:
               system("cls");
               int cod;
               cout<<"INGRESE CODIGO DE PROVEEDOR: "<<endl;
               cin>>cod;
               if(BuscarProveedorCod(cod)==-2){cout<<"PROVEEDOR INEXISTENTE O ELIMINADO"<<endl;}
               system("pause");
            break;
           case 14:
                system("cls");
                listarProveedores();
            break;
           case 15:
               system("cls");
               modificarDatosProveedor();
            break;
           case 16:
               system("cls");
               if(elmininarProveedor()==1){cout<<"PROVEEDOR ELIMINADO"<<endl;}
               else{cout<<"NO SE PUDO ELIMINAR PROVEEDOR."<<endl;}
               system("pause");
            break;
           case 17:
                system("cls");
                if(recuperoProveedor()==1){cout<<"ALTA PROVEEDOR EXITOSA"<<endl;}
                else{cout<<"NO SE PUDO DAR DE ALTA DEL PROVEEDOR."<<endl;}
                system("pause");
            break;
            }
    }while(opc!=18);
}
#endif // MENUPROVEEDORES_H_INCLUDED
