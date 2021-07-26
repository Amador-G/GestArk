#include <iostream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <windows.h>
using namespace std;

///-------------------------------------------------------///
///ARCHVOS ARTICULO///
const char ARCHIVOARTICULO[] = "ArchivoArticulo.dat";
const char ARCHIVOARTICULO_BKP[] = "Archivoarticulo_bkp.dat";
const char ARCHIVOINICIAL[] = "Archivoinicial.dat";
///-------------------------------------------------------///
///ARCHIVOS CLIENTE
const char ARCHIVOCLIENTE[] = "ArchivoCliente.dat";
const char ARCHIVOCLIENTE_BKP[] = "Archivocliente_bkp.dat";
const char ARCHIVOINICIALCLIENTE[] = "Archivoclienteinicial.dat";
///-------------------------------------------------------///
///ARCHVOS VENDEDOR///
const char ARCHIVOVENDEDOR[] = "ArchivoVendedor.dat";
const char ARCHIVOVENDEDOR_BKP[] = "ArchivoVendedor_bkp.dat";
const char ARCHIVOINICIALVENDEDOR[] = "ArchivoVendedorinicial.dat";
///-------------------------------------------------------///
///ARCHIVOS VENTA///
const char ARCHIVOVENTAS[] = "Archivoventa.dat";
const char ARCHIVOVENTAS_BKP[] = "Archivoventa_bkp.dat";
const char ARCHIVOVENTASINICIAL[] = "Archivoventainicial.dat";
///-------------------------------------------------------///
///ARCHIVOS PROVEEDOR///
const char ARCHIVOPROVEEDOR[] = "ArchivoProveedor.dat";
const char ARCHIVOPROVEEDOR_BKP[] = "ArchivoProveedor_bkp.dat";
const char ARCHIVOPROVEEDORINICIAL[] = "ArchivoProveedorinicial.dat";
///-------------------------------------------------------///
///ARCHIVOS PEDIDO///
const char ARCHIVOPEDIDO[] = "ArchivoPedido.dat";
///-------------------------------------------------------///
///CONSTANTES GLOBALES///
const char ESTADOS[3][15] = {
    "NO DISPONIBLE",
    "DISPONIBLE",
};

const char CATEGORIAS[10][10] = {
    "TRAINEE",
    "JUNIOR",
    "S. SENIOR",
    "SENIOR",
    "MASTER",
};
///-------------------------------------------------------///

#include "rlutil.h"
#include "FuncionesGlobales.h"
#include "clsfecha.h"
#include "clsdirrecion.h"
#include "clsproveedor.h"
#include "Menus.h"
#include "MenuProveedores.h"
#include "clsarticulo.h"
#include "clspersona.h"
#include "clsvendedor.h"
#include "clscliente.h"
#include "herramientas.h"
#include "clsventa.h"
#include "clspedido.h"
#include "MenuArticulos.h"
#include "MenuClientes.h"
#include "Menuventa.h"
#include "MenuConfiguracion.h"
#include "menuVendedor.h"
#include "menuReportes.h"

int main()
{
    rlutil::setColor(0);
    rlutil::setBackgroundColor(15);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    system("TITLE GestArk - gestion empresarial");
    cartelInicial();
    int opc;
    do
    {
        
        system("pause");
        opc = Menuprincipal();
        switch (opc)
        {
        case 12:
            if (contarRegistrosProv() > 0)
            {
                seccionArticulos();
            }
            else
            {
                rlutil::locate(60, 22);
                cout << "PRIMERO DEBER GENERAR UN REGISTRO DE PROVEEDORES..." << endl;
                rlutil::locate(60, 23);
                system("pause");
            }
            break;
        case 13:
            seccionClientes();
            break;
        case 14:
            if (contarRegistros() > 0 && contarRegistrosClientes() > 0 && contarRegistrosVendedores() > 0)
            {
                seccionVenta();
            }
            else
            {
                rlutil::locate(50, 22);
                cout << "PRIMERO DEBER GENERAR REGISTROS DE CLIENTES, VENDORES Y ARTICULOS..." << endl;
                rlutil::locate(50, 23);
                system("pause");
            }
            break;
        case 15:
            seccionVendedor();
            break;
        case 16:
            seccionProveedores();
            break;
        case 17:
            seccionReportes();
            break;
        case 18:
            seccionConfiguracion();
            break;
        case 19:
            rlutil::locate(1, 25);
            cartelFinal();

            return 0;
            break;
        }
    } while (opc != 19);
}
