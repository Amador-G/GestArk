#ifndef MENUCLIENTES_H_INCLUDED
#define MENUCLIENTES_H_INCLUDED
///MENU CLIENTE
///-------------------------------------------------------///
int buscarDNICliente(int dniBuscado){
    int posicion=0;
    Cliente registro;

    while(registro.leerDeDisco(posicion)){
        if(dniBuscado==registro.getDni()){
            return posicion;
        }
        posicion++;
    }
    return -1;
}

bool verificarCliente(int d){
    int posicion=0;
    Cliente registro;

    while(registro.leerDeDisco(posicion)){
        if(d==registro.getDni()){
            return true;
        }
        posicion++;
    }
    return false;
}

void AsignacionIDCliente (Cliente &cli){

    FILE *pCliente;
    pCliente=fopen(ARCHIVOCLIENTE,"rb");
    fseek(pCliente,-sizeof (Cliente),2);
    fread(&cli,sizeof cli,1,pCliente);
    cli.setIDcliente(cli.getIDcliente()+1);
    fclose(pCliente);

}

int agregarCliente(){//crea o agrega un registro cliente al final de los que esten hechos
    int r;
    int contador=0;
    do{
        Cliente cli;
        AsignacionIDCliente (cli);

        cli.cargar();
        if(!cli.grabarEnDisco()){
            cout << "Error al guardar el archivo.";
            system("pause");
            return contador;
        }
        contador++;
        cout<<"DESEA AGREGAR OTRO CLIENTE (y/n)?"<<endl;
        r=getch();
        system("cls");
    }while(r==121||r==89);
    return contador;
}

int mostrarClientePorDNI(int dni){//busca cliente por DNI y lo muestra si "estado" esta en true
    Cliente cli;
    int pos=0;

    pos=buscarDNICliente(dni);
    if(pos<0){return -2;}

    if(!cli.leerDeDisco(pos)){return -3;}

    if(!cli.GetEstado()){return -1;}

    cli.mostrar();
}

int modificarMailCliente(){
    int dni, pos;
    bool modifico=false;
    Cliente cli;

    cout<<"INGRESE DNI DEL CLIENTE: ";
    cin>>dni;

    pos=buscarDNICliente(dni);
    if(pos<0){return -2;}


    if(!cli.leerDeDisco(pos)){return -3;}
    if(cli.GetEstado()==true){
        cli.mostrar();
        char mailNuevo[30];
        cout<< endl <<"INGRESE NUEVO MAIL: ";
        cin.ignore();
        cin.getline(mailNuevo, 30);
        cli.setEmail(mailNuevo);
        modifico=cli.modificarEnDisco(pos);
    }
    else{
        return -1;
    }
    return modifico;
}

int eliminarCliente(){//cambia el estado de true a false
    int r;
    int dni, pos;
    bool modifico=false;
    Cliente cli;

    cout<<"INGRESE DNI DEL CLIENTE: ";
    cin>>dni;

    pos=buscarDNICliente(dni);
    if(pos<0){return -2;}

    if(!cli.leerDeDisco(pos)){return -3;}
    cli.mostrar();
    cout<< endl <<"ELIMINAR CLIENTE (Y/N)?";
    r=getch();
    if(r!=121 && r!=89){
        return -1;
    }
    cli.setEstado(false);
    modifico=cli.modificarEnDisco(pos);
    return modifico;
}

int altaCliente(){// cambia el estado de false a true
    int r;
    int dni, pos;
    Cliente cli;
    bool modifico=false;

    cout<<"INGRESE DNI DEL CLIENTE: ";
    cin>>dni;

    pos=buscarDNICliente(dni);
    if(pos<0){return -2;}

    if(!cli.leerDeDisco(pos)){return -3;}

    cli.mostrar();
    cout << endl <<"DAR EL ALTA CLIENTE (Y/N)?" << endl;
    r=getch();
    if(r!=121 && r!=89){
        return -1;
    }
    cli.setEstado(true);
    modifico=cli.modificarEnDisco(pos);
    return modifico;
}

void seccionClientes(){
    int opc;
    do{
        int checkeo=0;
        opc=Menucliente();
        switch(opc){
        case 12:
            {
                int agregados=0;
                system("cls");
                agregados = agregarCliente();
                cout << agregados <<"CLIENTE/s CARGADO/s CON EXITO!"<<endl;
                system("pause");
                break;
            }
        case 13:
            {
                system("cls");
                int dni;
                cout<<"INGRESE DNI DEL CLIENTE: "<<endl;
                cin>>dni;
               // system("pause");
                checkeo=mostrarClientePorDNI(dni);
                if(checkeo==-1){cout<<endl<<"El cliente esta dado de baja."<<endl;}
                if(checkeo==-2){cout<<endl<<"El cliente no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl<<"Error al leer el archivo."<<endl;}
                system("pause");
                break;
            }
        case 14:
            {
                system("cls");
                elegirTipoListadoClientes();
                break;
            }
        case 15:
            {
                system("cls");
                checkeo=modificarMailCliente();
                if(checkeo==-2){cout<<endl<<"El cliente no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl<<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl<<"Email modificado con exito."<<endl;}
                if(checkeo==0){cout<<endl<<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        case 16:
            {
                system("cls");
                checkeo=eliminarCliente();
                if(checkeo==-1){cout<<endl<<"El cliente no fue dado de baja."<<endl;}
                if(checkeo==-2){cout<<endl<<"El cliente no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl<<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl<<"Cliente dado de baja con exito."<<endl;}
                if(checkeo==0){cout<<endl<<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        case 17:
            {
                system("cls");
                checkeo=altaCliente();
                if(checkeo==-1){cout<<endl<<"El cliente no fue dado de alta."<<endl;}
                if(checkeo==-2){cout<<endl<<"El cliente no se encuentra registrado."<<endl;}
                if(checkeo==-3){cout<<endl<<"Error al leer el archivo."<<endl;}
                if(checkeo==1){cout<<endl<<"Cliente dado de alta con exito."<<endl;}
                if(checkeo==0){cout<<endl<<"Error al guardar los nuevos datos en el archivo."<<endl;}
                system("pause");
                break;
            }
        }
    }while(opc!=18);
}

///-------------------------------------------------------///
///FUNCIONES DE ORDENAMIENTO///
void porApellidoAscendente(Cliente *vectorCliente, int totalRegistros){
    int i, j, posMin;
    Cliente aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(strcmp(vectorCliente[j].getApellido(), vectorCliente[posMin].getApellido())<0){
                        posMin=j;
                }
        }
        aux=vectorCliente[i];
        vectorCliente[i]=vectorCliente[posMin];
        vectorCliente[posMin]=aux;
    }
}

void porApellidoDescendente(Cliente *vectorCliente, int totalRegistros){
    int i, j, posMin;
    Cliente aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(strcmp(vectorCliente[j].getApellido(), vectorCliente[posMin].getApellido())>0){
                        posMin=j;
                }
        }
        aux=vectorCliente[i];
        vectorCliente[i]=vectorCliente[posMin];
        vectorCliente[posMin]=aux;
    }
}

void porFechaAscendente(Cliente *vectorCliente, int totalRegistros){
    int i, j, posMin;
    Cliente aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(vectorCliente[j].getFecha()>vectorCliente[posMin].getFecha()){
                        posMin=j;
                }
        }
        aux=vectorCliente[i];
        vectorCliente[i]=vectorCliente[posMin];
        vectorCliente[posMin]=aux;
    }
}

void porFechaDescendente(Cliente *vectorCliente, int totalRegistros){
    int i, j, posMin;
    Cliente aux;
    for(i=0;i<totalRegistros-1;i++){
        posMin=i;
        for(j=i+1;j<totalRegistros;j++){
                if(( vectorCliente[j].getFecha()>vectorCliente[posMin].getFecha() )==false){
                        posMin=j;
                }
        }
        aux=vectorCliente[i];
        vectorCliente[i]=vectorCliente[posMin];
        vectorCliente[posMin]=aux;
    }
}

int contarRegistrosClientes(){//Devuelve la cantidad de registros
    int c=0, tam;
    FILE *pClientes;
    pClientes=fopen(ARCHIVOCLIENTE, "rb");
    if(pClientes==NULL){return -1;}
    fseek(pClientes, 0, 2);
    tam=ftell(pClientes);
    fclose(pClientes);
    c=tam/sizeof(Cliente);
    return c;
}

void copiarAVectorCliente(Cliente *vectorCliente, int totalRegistros){
    for(int i=0;i<totalRegistros;i++){
        vectorCliente[i].leerDeDisco(i);
    }
}

void listarClientes(int linea){//lista todo el registro siempre y cuando "estado" este en true
    Cliente registro;
    int pos=0;
    cartelListarClientes(++linea);
    while(registro.leerDeDisco(pos++)){
        if(registro.GetEstado()){
            registro.mostrar(linea+3);
            cout << endl;
            linea++;
        }
    }
}

void mostrarVectorOrdenado(Cliente *vectorCliente, int totalRegistros){
    int i;
    cartelListarClientes(2);
    for(i=0;i<totalRegistros;i++){
        vectorCliente[i].mostrar(i+4);
        cout<<endl;
    }

}

void listarClientesOrdenados(int tipoOrden){
    int totalRegistros=contarRegistrosClientes();
    Cliente *vectorCliente;
    vectorCliente=new Cliente[totalRegistros];
    if(vectorCliente==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }
    copiarAVectorCliente(vectorCliente,totalRegistros);

    switch(tipoOrden){
    case 1:
        porApellidoAscendente(vectorCliente, totalRegistros);
        break;
    case 2:
        porApellidoDescendente(vectorCliente, totalRegistros);
        break;
    case 3:
        porFechaAscendente(vectorCliente, totalRegistros);
        break;
    case 4:
        porFechaDescendente(vectorCliente, totalRegistros);
        break;

    }
    mostrarVectorOrdenado(vectorCliente, totalRegistros);
    delete vectorCliente;
}

void elegirTipoListadoClientes(){
    int opc;
    do{
        opc=MenuListarClientes();
        switch(opc){
        case 12:
            system("cls;");
            listarClientes(1);
            system("pause");
            break;
        case 14:
            system("cls;");
            listarClientesOrdenados(1);
            system("pause");
            break;
        case 15:
            system("cls;");
            listarClientesOrdenados(2);
            system("pause");
            break;
        case 17:
            system("cls;");
            listarClientesOrdenados(3);
            system("pause");
            break;
        case 18:
            system("cls;");
            listarClientesOrdenados(4);
            system("pause");
            break;
        }
    }while(opc!=19);
}

///-------------------------------------------------------///






#endif // MENUCLIENTES_H_INCLUDED
