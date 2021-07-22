#ifndef MENUREPORTES_H_INCLUDED
#define MENUREPORTES_H_INCLUDED


int maximoVector(int *v, int tam){
    int i, posMax=0;
    for(i=1;i<tam;i++){
        if(v[i]>v[posMax]) {
                posMax=i;
        }
    }
    return posMax;
}

///PEDIDO
void imprimiPedido(){
    Pedido obj;
    int pos=0;
    if(!obj.leerDeDisco(0)){
        cout << "NO HAY PEDIDOS CARGADOS... " << endl << endl;
        return;
    }
    cartelListarPedidos(1);
    while(obj.leerDeDisco(pos++)){
        obj.mostrar(pos+3);
        cout << endl << endl;
    }
}

int buscarPedido(int id){
    Pedido reg;
    int pos=0;
    while((reg.leerDeDisco(pos))){
        if(reg.getnPedido()==id){
            return pos;
        }
        pos++;
        }
    return -1;
}

bool modificarMailPedido(Pedido &aux, int pos){
    char mailPedido[25];
    cout<<"INGRESE NUEVO MAIL DE PROVEEDOR: ";
    cargarCadena(mailPedido,29);
    aux.setEnvioMail(mailPedido);
    bool modifico=aux.modificarEnDisco(aux,pos);
    return modifico;
}

bool modificarCantPedida(Pedido &aux, int pos){
    int cantaPedir;
    cout<<"INGRESE NUEVA CANTIDAD A PEDIR: ";
    cin>>cantaPedir;
    while(cantaPedir<0){
        cout<<"INGRESE UNA CANTIDAD VALIDA" << endl;
        cout<<"INGRESE NUEVA CANTIDAD A PEDIR: ";
        cin>>cantaPedir;
    }
    aux.setCantSolicitada(cantaPedir);
    bool modifico=aux.modificarEnDisco(aux,pos);
    return modifico;
}

void modificarPedido(){
    Pedido reg;
    int id,opc;
    if(!reg.leerDeDisco(0)){
        cout << "NO HAY PEDIDOS CARGADOS... " << endl << endl;
        return;
    }

    cout<<"INGRESE EL NRO DEL PEDIDO: ";
    cin>>id;
    int pos=buscarPedido(id);
    if(pos<0){
        cout<<"NO EXISTE PEDIDO PARA EL NUMERO INGRESADO"<<endl;
        system("pause");
        return;
    }
    reg.leerDeDisco(pos);
    reg.mostrar();
    opc=menumodificarPedido();
    switch(opc){
        case 8:
            system("cls");
            if(modificarMailPedido(reg,pos)){cout<<"SE MODIFICO MAIL PROVEEDOR DE MANERA EXISOTA"<<endl;}
            else{cout<<"NO SE PUDO MODIFICAR MAIL"<<endl;}
            system("pause");
            break;
        case 9:
            system("cls");
            if(modificarCantPedida(reg,pos)){cout<<"SE MODIFICO LA CANTIDAD A PEDIR DE MANERA EXITOSA"<<endl;}
            else {cout<<"NO SE PUDO MODIFICAR CANTIDAD A PEDIR"<<endl;}
            system("pause");
            break;
    }
}

///REPORTES ARTICULO
///-------------------------------------------------------///

void ordenarVentasPorFecha(Venta *vec, int tam){
    int i, j, posMin;
    Venta aux;
    for(i=0;i<tam-1;i++){
        posMin=i;
        for(j=i+1;j<tam;j++){
            if(vec[j].getFe()>vec[posMin].getFe()){
                posMin=j;
            }
        }
        aux=vec[i];
        vec[i]=vec[posMin];
        vec[posMin]=aux;
    }
}

void reportePorArticulo(){
    Venta reg;
    int id,pos=0,canttotal=0,linea=0;
    rlutil::locate(1,30);
    cout << "ARTICULOS DISPONIBLES: ";
    listarArticulosDisponibles(31);
    rlutil::locate(1,4);
    cout<<"INGRESE ID DE ARTICULO: ";
    cin>>id;
    BorrarArea(1,29);
    system("cls");
    cartelListarVentas(1);
    while(reg.leerDeDisco(pos++)){
        if(reg.getIDarticulo()==id){reg.mostrar(linea+3);
           canttotal+=reg.getCantidadVendida();
           linea++;
        }

    }
    if(linea==0){
        rlutil::locate(1,3);
        cout<<"NO HAY REGISTROS PARA ESTE ARTICULO"<<endl;}
    else{
    cout<<"-----------------------"<<endl;
    cout<<"CANTIDAD TOTAL VENDIDA: "<<canttotal<<endl;
    cout<<"-----------------------"<<endl;}
    system("pause");
}

void reportePorFechaArticulo(){
    Venta reg;
    Fecha fecha1,fecha2;
    int id,pos=0,linea=0;
    rlutil::locate(1,30);
    cout << "ARTICULOS DISPONIBLES: ";
    listarArticulosDisponibles(31);
    rlutil::locate(1,4);
    cout<<"INGRESE ID DE ARTICULO: ";
    cin>>id;
    while(buscarArticulo(id)<0){
        cout << "ARTICULO INEXISTENTE O ELIMINADO." << endl;
        cout << "INGRESE ID VALIDO DE ARTICULO: ";
        cin >> id;
    }
    system("cls");
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    cartelListarVentas(1);
    while(reg.leerDeDisco(pos++)){
        if(reg.getIDarticulo()==id && (reg.getFe()>fecha1) && (!(reg.getFe()>fecha2)) && reg.getEstado()){
            reg.mostrar(linea+3);
            linea++;
        }
    }
    system("pause");
}

void articuloMasVendido(){
    Venta regv;
    int cantArticulos=contarRegistros();
    int *cantvendida,pos=0;
    cantvendida= new int[cantArticulos];
    for(int i=0;i<cantArticulos;i++){
        cantvendida[i]=0;
    }
    while(regv.leerDeDisco(pos++)){
            cantvendida[regv.getIDarticulo()-1]+=regv.getCantidadVendida();
        }
    cout<<"CODIGO ARTICULO MAS VENDIDO :"<<maximoVector(cantvendida,cantArticulos)+1<<endl;
    BuscarArticuloporId(maximoVector(cantvendida,cantArticulos)+1);
    cout<<"CANTIDAD VENDIDA: "<<cantvendida[maximoVector(cantvendida,cantArticulos)]<<endl;
    cout<<"------------------------"<<endl;
    delete cantvendida;
    system("pause");
}

void articuloMasVendidoxFecha(){
    Venta reg;
    Fecha fecha1,fecha2;
    int cantArticulos=contarRegistros();
    int *cantvendida,pos=0;
    cantvendida= new int[cantArticulos];
    for(int i=0;i<cantArticulos;i++){
        cantvendida[i]=0;
    }
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    while(reg.leerDeDisco(pos++)){
            if((reg.getFe()>fecha1) && (!(reg.getFe()>fecha2))) {
                if(reg.getEstado()){
                    cantvendida[reg.getIDarticulo()-1]+=reg.getCantidadVendida();
                }
            }
        }

    cout<<"CODIGO ARTICULO MAS VENDIDO :"<<maximoVector(cantvendida,cantArticulos)+1<<endl;
    BuscarArticuloporId(maximoVector(cantvendida,cantArticulos)+1);
    cout<<"CANTIDAD VENDIDA: "<<cantvendida[maximoVector(cantvendida,cantArticulos)]<<endl;
    cout<<"------------------------"<<endl;
    system("pause");
}

void reportesArticulos(){
    int opc;
    do{
        opc=menuReporteArticulos();
            switch(opc){
                case 12:
                    system("cls");
                    reportePorArticulo();
                    break;
                case 13:
                    system("cls");
                    reportePorFechaArticulo();
                    break;
                case 14:
                    system("cls");
                    articuloMasVendido();
                    break;
                case 15:
                    system("cls");
                    articuloMasVendidoxFecha();
                    break;
            }
        }while(opc!=16);
}
///-------------------------------------------------------///
///REPORTES VENDEDOR
///-------------------------------------------------------///

void reportePorVendedor(){
    Venta reg;
    int id,pos=0,canttotal=0,linea=0;
    rlutil::locate(1,30);
    cout << "VENDEDORES DISPONIBLES: ";
    listarVendedores(31);
    rlutil::locate(1,1);
    cout << "INGRESE ID DEL VENDEDOR: ";
    cin >> id;
    BorrarArea(1,29);
    system("cls");
    cartelListarVentas(1);
    while(reg.leerDeDisco(pos++)){
        if(reg.getIDvendedor()==id){reg.mostrar(linea+3);
           canttotal+=reg.getCantidadVendida();
           linea++;
        }

    }
    if(linea==0){
        rlutil::locate(1,3);
        cout<<"NO HAY REGISTROS PARA ESTE VENDEDOR"<<endl;}
    else{
    cout<<"-----------------------"<<endl;
    cout<<endl;
    cout<<"CANTIDAD TOTAL VENDIDA: "<<canttotal<<endl;
    cout<<"-----------------------"<<endl;
    }
    system("pause");
}

void mejorEnCantidadFecha(){
    Vendedor aux;
    Venta reg;
    Fecha fecha1,fecha2;
    int contarVendedores=contarRegistrosVendedores();
    int *cantVendedores,pos=0;
    cantVendedores= new int[contarVendedores];
    for(int i=0;i<contarVendedores;i++){
        cantVendedores[i]=0;
    }
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    while(reg.leerDeDisco(pos++)){
            if((reg.getFe()>fecha1) && (!(reg.getFe()>fecha2)) && reg.getEstado()){
                if(reg.getEstado()){
                    cantVendedores[reg.getIDvendedor()-1]+=reg.getCantidadVendida();
                }
            }
        }

    cout<<"NUMERO DE  VENDEDOR CON MAYOR CANTIDAD DE VENTAS: "<<maximoVector(cantVendedores,contarVendedores)+1<<endl;
    aux.leerDeDisco(maximoVector(cantVendedores,contarVendedores));
    aux.mostrar();
    cout<<"MAXIMA CANTIDAD VENDIDA: "<<cantVendedores[maximoVector(cantVendedores,contarVendedores)]<<endl;
    cout<<"------------------------"<<endl;
    system("pause");
}

void mejorEnImporteFecha(){
    Vendedor aux;
    Venta reg;
    Fecha fecha1,fecha2;
    int contarVendedores=contarRegistrosVendedores();
    int *cantVendedores,pos=0;
    cantVendedores= new int[contarVendedores];
    for(int i=0;i<contarVendedores;i++){
        cantVendedores[i]=0;
    }
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    while(reg.leerDeDisco(pos++)){
        if((reg.getFe()>fecha1) && (!(reg.getFe()>fecha2)) && reg.getEstado()){
                cantVendedores[reg.getIDvendedor()-1]+=reg.getImporte();
        }
    }
    cout<<"NUMERO DE  VENDEDOR CON MAYOR RECAUDACION  :"<<maximoVector(cantVendedores,contarVendedores)+1<<endl;
    aux.leerDeDisco(maximoVector(cantVendedores,contarVendedores));
    aux.mostrar();
    cout<<"RECAUDADO: "<<cantVendedores[maximoVector(cantVendedores,contarVendedores)]<<endl;
    cout<<"------------------------"<<endl;
    system("pause");
}

void ventasVendedoresEntreFechas(){
    Fecha fecha1,fecha2;
    int comprasRealizadas=contarRegistrosVentas();
    Venta *compras;
    int ID=0;
    compras = new Venta[comprasRealizadas];
    copiarAVectorVentas(compras, comprasRealizadas);
    cout<<"INGRESE EL ID DEL VENDEDOR: ";
    cin >> ID;
    while(buscarIDvendedor(ID) < 0){
        cout << "EL VENDEDOR NO EXISTE" << endl;
        cout << "INGRESE EL ID DEL VENDEDOR: ";
        cin >> ID;
    }
    cout<<"INGRESE LAS FECHAS: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    int contador=0;
    for(int i=0; i<comprasRealizadas; i++){
        if( !(compras[i].getIDvendedor()==ID) ){
            compras[i].setestado(false);
            contador++;
        }
        if(!( (compras[i].getFe()>fecha1) && (!(compras[i].getFe()>fecha2)) )){
            compras[i].setestado(false);
        }

    }
    if(contador==comprasRealizadas){
        cout << "NO HAY VENTAS REGISTRADAS PARA ESTE VENDEDOR" << endl;
        return;
    }

    ordenarVentasPorFecha(compras, comprasRealizadas);

    cartelListarVentas(1);
    int linea=0;
    for(int i=0; i<comprasRealizadas; i++){
        if(compras[i].getEstado()){
            compras[i].mostrar(linea+3);
            linea++;
        }
    }


    system("pause");
    delete compras;
}

void mejorEnCantidad(){
    Venta regv;
    int cantVendedores=contarRegistrosVendedores();
    int *ventas,pos=0;
    ventas= new int[cantVendedores];
    for(int i=0;i<cantVendedores;i++){
        ventas[i]=0;
    }
    while(regv.leerDeDisco(pos++)){
            if(regv.getEstado()){
                ventas[regv.getIDvendedor()-1]+=regv.getCantidadVendida();
            }
    }
    cout<<"ID DEL MEJOR VENDEDOR: "<<maximoVector(ventas,cantVendedores)+1<<endl;
    BuscarVendedorNumero(maximoVector(ventas,cantVendedores)+1);
    cout<<"CON UN TOTAL VENDIDO DE: "<<ventas[maximoVector(ventas,cantVendedores)]<< " UNIDADES." << endl;
    cout<<"------------------------"<<endl;
    delete ventas;
    system("pause");
}

void mejorEnImporte(){
    Venta regv;
    int cantVendedores=contarRegistrosVendedores();
    int *ventas,pos=0;
    ventas= new int[cantVendedores];
    for(int i=0;i<cantVendedores;i++){
        ventas[i]=0;
    }
    while(regv.leerDeDisco(pos++)){
            if(regv.getEstado()){
                ventas[regv.getIDvendedor()-1]+=regv.getImporte();
            }
    }
    cout<<"ID DEL MEJOR VENDEDOR: "<<maximoVector(ventas,cantVendedores)+1<<endl;
    BuscarVendedorNumero(maximoVector(ventas,cantVendedores)+1);
    cout<<"CON UN TOTAL RECAUDADO DE: $"<<ventas[maximoVector(ventas,cantVendedores)]<< endl;
    cout<<"------------------------"<<endl;
    delete ventas;
    system("pause");
}

void reporteVendedores(){
    int opc;
    do{
        opc=menuReportesVendedores();
        switch(opc){
        case 12:
            system("cls");
            reportePorVendedor();
            break;
        case 13:
            system("cls");
            ventasVendedoresEntreFechas();
            break;
        case 15:
            system("cls");
            mejorEnCantidad();
            break;
        case 16:
            system("cls");
            mejorEnImporte();
            break;
        case 18:
            system("cls");
            mejorEnCantidadFecha();
            break;
        case 19:
            system("cls");
            mejorEnImporteFecha();
            break;

        }
    }while(opc!=20);
}
///-------------------------------------------------------///
///REPORTES CLIENTE
///-------------------------------------------------------///
void reportePorCliente(){
    Venta reg;
    int dni,pos=0,canttotal=0,linea=0;

    rlutil::locate(1,30);
    cout << "CLIENTES DISPONIBLES: ";
    listarClientes(31);

    rlutil::locate(1,1);
    cout << "INGRESE DNI DEL CLIENTE: ";
    cin >> dni;
    BorrarArea(1,29);
    system("cls");
    cartelListarVentas(1);
    while(reg.leerDeDisco(pos++)){
        if(reg.getDNIcliente()==dni){reg.mostrar(linea+3);
           canttotal+=reg.getImporte();
           linea++;
        }

    }
    if(linea==0){
        rlutil::locate(1,3);
        cout<<"NO HAY REGISTROS PARA ESTE CLIENTE"<<endl;
    }
    else{
        cout<<"-----------------------"<<endl;
        cout<<endl;
        cout<<"TOTAL EN $ DE COMPRAS REALIZADAS: "<<canttotal<<endl;
        cout<<"-----------------------"<<endl;
    }
    system("pause");
}

void mejorEnCantidadClienteEntreFecha(){
    Venta reg;
    Cliente regc;
    Fecha fecha1,fecha2;
    int contarClientes=contarRegistrosClientes();
    int *cantClientes,pos=0;
    cantClientes= new int[contarClientes];
    for(int i=0;i<contarClientes;i++){
        cantClientes[i]=0;
    }
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"DESDE: "<<endl;
    fecha1.cargar();
    cout<<"HASTA: "<<endl;
    fecha2.cargar();
    system("cls");


    while(reg.leerDeDisco(pos++)){
        if((reg.getFe()>fecha1) && (!(reg.getFe()>fecha2))){
            if(reg.getEstado()){
                regc.leerDeDisco(buscarDNICliente(reg.getDNIcliente()));
                cantClientes[regc.getIDcliente()-1]+=reg.getCantidadVendida();
            }
        }
    }

    regc.leerDeDisco(maximoVector(cantClientes,contarClientes));
    cout<<"DNI DEL CLIENTE CON MAYOR CANTIDAD DE UNIDADES COMPRADAS: " << regc.getDni()<<endl;
    regc.mostrar();
    cout << endl;
    cout << "MAXIMA CANTIDAD COMPRADA: " <<cantClientes[maximoVector(cantClientes,contarClientes)]<<endl;
    cout<<"------------------------"<<endl;
    delete cantClientes;
    system("pause");

}

void mejorEnImporteClienteEntreFecha(){
    Venta reg;
    Cliente regc;

    Fecha fecha1,fecha2;
    int contarClientes=contarRegistrosVendedores();
    int *cantClientes,pos=0;
    cantClientes= new int[contarClientes];
    for(int i=0;i<contarClientes;i++){
        cantClientes[i]=0;
    }
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");
    while(reg.leerDeDisco(pos++)){
            if((reg.getFe()>fecha1) && (!(reg.getFe()>fecha2))){
                if(reg.getEstado()){
                    regc.leerDeDisco(buscarDNICliente(reg.getDNIcliente()));
                    cantClientes[regc.getIDcliente()-1]+=reg.getImporte();
                }
            }
    }
    regc.leerDeDisco(maximoVector(cantClientes,contarClientes) );
    cout<<"DNI DEL CLIENTE CON MAYOR CANTIDAD DE COMPRAS: " << regc.getDni()<<endl;
    regc.mostrar();
    cout << endl;
    cout << "IMPORTE TOTAL COMPRADO: $" <<cantClientes[maximoVector(cantClientes,contarClientes)]<<endl;
    cout<<"------------------------"<<endl;
    system("pause");
}

void comprasClientesEntreFechas(){
    Fecha fecha1,fecha2;
    int comprasRealizadas=contarRegistrosVentas();
    Venta *compras;
    int dniBuscado=0;
    compras = new Venta[comprasRealizadas];
    copiarAVectorVentas(compras, comprasRealizadas);
    cout<<"INGRESE EL DNI DEL CLIENTE: ";
    cin >> dniBuscado;
    cout<<"INGRESE RANGO O FECHA DE CONSULTA: "<<endl;
    cout<<"PRIMER PARAMETRO: "<<endl;
    fecha1.cargar();
    cout<<"SEGUNDO PARAMETRO: "<<endl;
    fecha2.cargar();
    system("cls");

    for(int i=0; i<comprasRealizadas; i++){
        if(!( (compras[i].getFe()>fecha1) && (!(compras[i].getFe()>fecha2)) )){
            compras[i].setestado(false);
        }
    }

    ordenarVentasPorFecha(compras, comprasRealizadas);

    for(int i=0; i<comprasRealizadas; i++){
        if(compras[i].getEstado() && compras[i].getDNIcliente()==dniBuscado){
            compras[i].mostrar();
        }
    }


    system("pause");
    delete compras;
}

void mejorClienteEnCantidad(){
    Venta regv;
    Cliente regCliente;
    int cantClientes=contarRegistrosClientes();
    int *compras,pos=0;
    compras= new int[cantClientes];
    for(int i=0;i<cantClientes;i++){
        compras[i]=0;
    }

    while(regv.leerDeDisco(pos++)){
            if(regv.getEstado()){
                if(regv.getEstado()){
                    compras[buscarDNICliente(regv.getDNIcliente())]+=regv.getCantidadVendida();
                }
            }
    }

    cout<<">>>EL MEJOR CLIENTE HISTORICO ES<<<"<<endl << endl;
    regCliente.leerDeDisco(maximoVector(compras,cantClientes));
    regCliente.mostrar();
    cout<<"CON UN TOTAL COMPRADO DE: "<<compras[maximoVector(compras,cantClientes)]<< " UNIDADES." << endl;
    cout<<"------------------------"<<endl;
    delete compras;
    system("pause");
}

void mejorClienteEnImporte(){
    Venta regv;
    Cliente regCliente;
    int cantClientes=contarRegistrosClientes();
    int *compras,pos=0;
    compras= new int[cantClientes];
    for(int i=0;i<cantClientes;i++){
        compras[i]=0;
    }

    while(regv.leerDeDisco(pos++)){
            if(regv.getEstado()){
                if(regv.getEstado()){
                    compras[buscarDNICliente(regv.getDNIcliente())]+=regv.getImporte();
                }
            }
    }

    cout<<">>>EL MEJOR CLIENTE HISTORICO ES<<<"<<endl << endl;
    regCliente.leerDeDisco(maximoVector(compras,cantClientes));
    regCliente.mostrar();
    cout<<"CON UN TOTAL COMPRADO DE: $"<<compras[maximoVector(compras,cantClientes)]<< endl;
    cout<<"------------------------"<<endl;
    delete compras;
    system("pause");
}

void reporteClientes(){
    int opc;
    do{
        opc=menuReportesClientes();
        switch(opc){
        case 12:
            system("cls");
            reportePorCliente();
            break;
        case 13:
            system("cls");
            comprasClientesEntreFechas();
            break;
        case 15:
            system("cls");
            mejorClienteEnCantidad();
            break;
        case 16:
            system("cls");
            mejorClienteEnImporte();
            break;
        case 18:
            system("cls");
            mejorEnCantidadClienteEntreFecha();
            break;
        case 19:
            system("cls");
            mejorEnImporteClienteEntreFecha();
            break;
        }
    }while(opc!=20);
}

///-------------------------------------------------------///
void seccionReportes(){

    int opc;
    do{
        opc=menuReportes();
        switch(opc){
            case 12:
                system("cls");
                imprimiPedido();
                system("pause");
                break;
            case 13:
                system("cls");
                modificarPedido();
                break;
            case 14:
                system("cls");
                reportesArticulos();
                break;
            case 15:
                system("cls");
                reporteVendedores();
                break;
            case 16:
                system("cls");
                reporteClientes();
                break;

        }
    }while(opc!=17);
}

#endif // MENUREPORTES_H_INCLUDED
