#ifndef MENUVENDEDOR_H_INCLUDED
#define MENUVENDEDOR_H_INCLUDED

int buscarDNIVendedor(int dniBuscado){
    Vendedor registro;
    int pos=0;
    while(registro.leerDeDisco(pos)==1){
        if(dniBuscado==registro.getDni()){
            return pos;
            pos++;
        }
    }
    return -1;
}

int buscarIDvendedor(int id){
    Vendedor registro;
    int pos=0;
    while(registro.leerDeDisco(pos)==1){
        if(id==registro.getIdVendedor()){
            return pos;
            pos++;
        }
    }
    return -1;
}

int BuscarVendedorNumero(int id){//busca articulo por id y lo muestra si "estado" esta en true
    Vendedor reg;
    int pos=0;
    FILE *pVendedor;
    pVendedor=fopen(ARCHIVOVENDEDOR,"rb");
    if(pVendedor==NULL){return -1;}
    pos=buscarIDvendedor(id);
    if(pos<0){return -2;}
    reg.leerDeDisco(pos);
    if(reg.getEstado()==true){reg.mostrar();}
    else{return -2;}
    fclose(pVendedor);
}

bool verificarVendedor(int d){
    int posicion=0;
    Vendedor registro;

    while(registro.leerDeDisco(posicion)){
        if(d==registro.getDni()){
            return true;
        }
        posicion++;
    }
    return false;
}

int agregarVendedor(){
    int r;
    int contador=0;
    Vendedor registro;
    do{
        registro.iDAutomatico();
        cout << "ID del nuevo vendedor, asignado automaticamente: " << registro.getIdVendedor() << endl;
        registro.cargar();
        if(!registro.grabarEnDisco()){
            cout << "Error al guardar el archivo.";
            system("pause");
            return contador;
        }
        contador++;
        cout<<"DESEA AGREGAR OTRO VENDEDOR (y/n)?"<<endl;
        r=getch();
    }while(r==121||r==89);
    return contador;
}

int mostrarVendedorPorDni(int dni){//busca Vendedor por DNI y lo muestra si "estado" esta en true
    Vendedor registro;

    if(!registro.leerDeDisco(dni-1)){return -3;}

    if(!registro.getEstado()){return -1;}

    registro.mostrar();
}

int modificarCategoria(){
    int id;
    bool modifico=false;
    Vendedor registro;

    cout<<"INGRESE ID DEL VENDEDOR: ";
    cin>>id;

    if(!registro.leerDeDisco(id-1)){return -3;}
    if(registro.getEstado()==true){
        registro.mostrar();

        int catNueva;
        cout<< endl << "INGRESE CATEGORIA NUEVA DEL VENDEDOR (1 A 5): ";
        cin >> catNueva;
        while (catNueva<0 || catNueva>5){
            cout << "NO EXISTE CATEGORIA PARA EL NUMERO INGRESADO." << endl;
            cout << "INGRESE UNA CATEGORIA VALIDA (1 A 5): ";
            cin >> catNueva;
        }
        cout << "CATEGORIA NUEVA INGRESADA >" << CATEGORIAS[catNueva-1] << "<" << endl;
        registro.setcategoria(catNueva);
        modifico=registro.modificarEnDisco(id-1);
    }
    return modifico;
}

int eliminarVendedor(){//cambia el estado de true a false
    int r;
    int id;
    bool modifico=false;
    Vendedor registro;

    cout<<"INGRESE ID DEL VENDEDOR: ";
    cin>>id;

    if(!registro.leerDeDisco(id-1)){return -3;}
    registro.mostrar();
    cout<< endl << "ELIMINAR VENDEDOR (Y/N)?";
    r=getch();
    if(r!=121 && r!=89){
        return -1;
    }
    registro.setEstado(false);
    modifico=registro.modificarEnDisco(id-1);
    return modifico;
}

int altaVendedor(){//cambia el estado de true a false
    int r;
    int id;
    bool modifico=false;
    Vendedor registro;

    cout<<"INGRESE ID DEL VENDEDOR: ";
    cin>>id;

    if(!registro.leerDeDisco(id-1)){return -3;}
    registro.mostrar();
    cout<< endl <<"DAR DE ALTA AL VENDEDOR (Y/N)?";
    r=getch();
    if(r!=121 && r!=89){
        return -1;
    }
    registro.setEstado(true);
    modifico=registro.modificarEnDisco(id-1);
    return modifico;
}

void seccionVendedor(){
    int opc;
    do{
        opc=menuVendedor();
        switch(opc){
        case 12:
            {
                int agregados=0;
                system("cls");
                agregados = agregarVendedor();
                cout << agregados <<"VENDEDOR/es CARGADO/s CON EXITO!"<<endl;
                system("pause");
                break;
            }
        case 13:
            {
                system("cls");
                int dni;
                cout<<"INGRESE ID DEL VENDEDOR: "<<endl;
                cin>>dni;
                int checkeo=mostrarVendedorPorDni(dni);
                if(checkeo==-1){cout<< endl << "El vendedor esta dado de baja."<<endl;}
                if(checkeo==-2){cout<< endl <<"El vendedor no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<< endl <<"Error al leer el archivo."<<endl;}
                system("pause");
                break;
            }
        case 14:
            {
                system("cls");
                elegirTipoListadoVendedor();
                break;
            }
        case 15:
            {
                system("cls");
                int checkeo=modificarCategoria();
                if(checkeo==-2){cout<<endl <<"El vendedor no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl <<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl <<"Categoria modificada con exito."<<endl;}
                if(checkeo==0){cout<<endl <<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        case 16:
            {
                system("cls");
                int checkeo=eliminarVendedor();
                if(checkeo==-1){cout<<endl <<"El vendedor no fue dado de baja."<<endl;}
                if(checkeo==-2){cout<<endl <<"El vendedor no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl <<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl <<"Vendedor dado de baja con exito."<<endl;}
                if(checkeo==0){cout<<endl <<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        case 17:
            {
                system("cls");
                int checkeo=altaVendedor();
                if(checkeo==-1){cout<<endl <<"El vendedor no fue dado de alta."<<endl;}
                if(checkeo==-2){cout<<endl <<"El vendedor no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl <<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl <<"Vendedor dado de alta con exito."<<endl;}
                if(checkeo==0){cout<<endl <<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        }
    }while(opc!=18);

}

///-------------------------------------------------------///
///FUNCIONES DE ORDENAMIENTO///

int contarRegistrosVendedores(){//Devuelve la cantidad de registros
    int c=0, tam;
    FILE *pArchivo;
    pArchivo=fopen(ARCHIVOVENDEDOR,"rb");
    if(pArchivo==NULL){return -1;}
    fseek(pArchivo, 0, 2);
    tam=ftell(pArchivo);
    fclose(pArchivo);
    c=tam/sizeof(Vendedor);
    return c;
}

void copiarAVectorVendedor(Vendedor *vectorVendedor, int totalRegistros){
    for(int i=0;i<totalRegistros;i++){
        vectorVendedor[i].leerDeDisco(i);
    }
}

void porApellidoAscendente(Vendedor *vectorVendedor, int totalRegistros){
    int i, j, posMin;
    Vendedor aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(strcmp(vectorVendedor[j].getApellido(), vectorVendedor[posMin].getApellido())<0){
                        posMin=j;
                }
        }
        aux=vectorVendedor[i];
        vectorVendedor[i]=vectorVendedor[posMin];
        vectorVendedor[posMin]=aux;
    }
}

void porApellidoDescendente(Vendedor *vectorVendedor, int totalRegistros){
    int i, j, posMin;
    Vendedor aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(strcmp(vectorVendedor[j].getApellido(), vectorVendedor[posMin].getApellido())>0){
                        posMin=j;
                }
        }
        aux=vectorVendedor[i];
        vectorVendedor[i]=vectorVendedor[posMin];
        vectorVendedor[posMin]=aux;
    }
}

void porFechaAscendente(Vendedor *vectorVendedor, int totalRegistros){
    int i, j, posMin;
    Vendedor aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(vectorVendedor[j].getFecha()>vectorVendedor[posMin].getFecha()){
                        posMin=j;
                }
        }
        aux=vectorVendedor[i];
        vectorVendedor[i]=vectorVendedor[posMin];
        vectorVendedor[posMin]=aux;
    }
}

void porFechaDescendente(Vendedor *vectorVendedor, int totalRegistros){
    int i, j, posMin;
    Vendedor aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(( vectorVendedor[j].getFecha()>vectorVendedor[posMin].getFecha() ) ==false){
                        posMin=j;
                }
        }
        aux=vectorVendedor[i];
        vectorVendedor[i]=vectorVendedor[posMin];
        vectorVendedor[posMin]=aux;
    }
}

void listarVendedores(int linea){
    Vendedor registro;
    int pos=0;
    cartelListarVendedores(linea);

    while(registro.leerDeDisco(pos++)){
      if(registro.getEstado()){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;
       }
    }
}

void mostrarVectorOrdenado(Vendedor *vectorVendedor, int totalRegistros){
    int i;
    cartelListarVendedores(2);
    for(i=0;i<totalRegistros;i++){
        vectorVendedor[i].mostrar(i+4);
        cout<<endl;
    }

}

void listarVendedoresOrdenados(int tipoOrden){
    int totalRegistros=contarRegistrosVendedores();
    Vendedor *vectorVendedor;
    vectorVendedor=new Vendedor[totalRegistros];
    if(vectorVendedor==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }
    copiarAVectorVendedor(vectorVendedor,totalRegistros);

    switch(tipoOrden){
    case 1:
        porApellidoAscendente(vectorVendedor, totalRegistros);
        break;
    case 2:
        porApellidoDescendente(vectorVendedor, totalRegistros);
        break;
    case 3:
        porFechaAscendente(vectorVendedor, totalRegistros);
        break;
    case 4:
        porFechaDescendente(vectorVendedor, totalRegistros);
        break;
    }
    mostrarVectorOrdenado(vectorVendedor, totalRegistros);
    delete vectorVendedor;
}

void elegirTipoListadoVendedor(){
    int opc;
    do{
        opc=MenuListarVendedores();
        switch(opc){
        case 12:
            system("cls;");
            listarVendedores(1);
            system("pause");
            break;
        case 14:
            system("cls;");
            listarVendedoresOrdenados(1);
            system("pause");
            break;
        case 15:
            system("cls;");
            listarVendedoresOrdenados(2);
            system("pause");
            break;
        case 17:
            system("cls;");
            listarVendedoresOrdenados(3);
            system("pause");
            break;
        case 18:
            system("cls;");
            listarVendedoresOrdenados(4);
            system("pause");
            break;
        }
    }while(opc!=19);
}

///-------------------------------------------------------///
#endif // MENUVENDEDOR_H_INCLUDED
