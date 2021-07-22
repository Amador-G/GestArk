#ifndef HERRAMIENTAS_H_INCLUDED
#define HERRAMIENTAS_H_INCLUDED
///PROTOTIPOS
///ARTICULO
///-------------------------------------------------------///
bool agregarArticulo();

int buscarArticulo(int );

int BuscarArticuloporId(int );

int contarRegistros();

void copiarArchivoArticulo(Articulo *, int );

void mostrarVectorArticulos(Articulo *, int );

void ordenarAZArticulos(Articulo *, int );

void ordenarIDArticulos(Articulo *, int );

void ordenarPUArticulos(Articulo *, int );

void ordenarStockArticulos(Articulo *, int );

void listarArticulosOrdenados();

bool listarArticulosPorDefecto();

int listarArticulosDisponibles(int );

bool listarArticulosNoDisponibles();

void listarArticulos();

bool modificarPrecioU();

bool elmininarArticulo();

bool altaArticulo();

int Menuarticulos();

void seccionArticulos();
///FIN ARTICULO
///-------------------------------------------------------///
///CLIENTE
///-------------------------------------------------------///
///FUNCIONES DE ORDENAMIENTO CLIENTE///
int contarRegistrosClientes();

void elegirTipoListadoClientes();

void listarClientesOrdenados(int );

void listarClientes(int );

void copiarAVectorCliente(Cliente * , int);

void porApellidoAscendente(Cliente * , int);

void porApellidoDescendente(Cliente * , int);

void porFechaAscendente(Cliente * , int);

void porFechaDescendente(Cliente * , int);

void mostrarVectorOrdenado(Cliente * , int);

int MenuListarClientes();
///*************** FIN ORDENAMIENTO ********************///
int buscarDNICliente(int );

int agregarCliente();

int mostrarClientePorDNI(int );

int modificarMailCliente();

int eliminarCliente();

int altaCliente();

int Menucliente();

void seccionClientes();
///FIN CLIENTE
///-------------------------------------------------------///
///VENTA
///FUNCIONES DE ORDENAMIENTO VENTA///
void listarVentas(int linea);

void listarVentasDisp(int linea);

void listarVentasNODisp(int linea);

void elegirTipoListadoVentas();

///*************** FIN ORDENAMIENTO ********************///

bool verificarstock(int cantidad, int idarticulo);

bool controlstock(int cantidad, int idarticulo, bool mod);

float calcularimporte(int cantidad,int idarticulo);

bool VerificarVenta(int idarticulo, int dni, int cantidad);

int buscarVenta(int Nventa);

int agregarVenta();

int BuscarVentaporNumero(int nventa);

int contarRegistrosVentas();

bool listarVentas();

bool eliminarVenta();

bool altaVenta();

bool devolverVenta();

int Menuventas();

void seccionVenta();
///FIN VENTA
///-------------------------------------------------------///
///PROVEEDOR
bool agregarProveedor();

int buscarProveedor(int codigo);

int BuscarProveedorCod(int id);

int contarRegistrosProv();

void copiarArchivoProveedor(Proveedor *pProveeedor, int cantProveedor);

void mostrarVectorProveedor(Proveedor *pProveedor, int cantProveedor);

void ordenarAZProveedor(Proveedor *pProveeedor, int cantProveedor);

void listarProveedorPorDefecto(int );

void listarProveedoresOrdenados(int orden);

bool modificarmailProveedor();

bool modificarTelProveedor();

bool modificarDirProveedor();

bool elmininarProveedor();

bool recuperoProveedor();

void listarProveedores();

void seccionProveedores();
///FIN PROVEEDOR
///-------------------------------------------------------///
///-------------------------------------------------------///
///VENDEDOR
///-------------------------------------------------------///
///FUNCIONES DE ORDENAMIENTO VENDEDOR///
int contarRegistrosVendedores();

void elegirTipoListadoVendedor();

int MenuListarVendedores();

void listarVendedores(int );

void listarVendedoresOrdenados(int);

void porApellidoAscendente(Vendedor * , int);

void porApellidoDescendente(Vendedor * , int);

void porFechaAscendente(Vendedor *, int );

void porFechaDescendente(Vendedor *, int );

void copiarAVectorVendedor(Vendedor * , int);

void mostrarVectorOrdenado(Vendedor * , int );

///*************** FIN ORDENAMIENTO ********************///

int buscarDNIVendedor(int );

int agregarVendedor();

int mostrarVendedorPorDni(int );

int modificarCategoria();

int eliminarVendedor();

int altaVendedor();

int menuVendedor();

void seccionVendedor();
///FIN VENDEDOR
///-------------------------------------------------------///
///REPORTES
///-------------------------------------------------------///

int menuReportes();

void seccionReportes();

int maximoVector(int *, int );

///PEDIDO
void imprimiPedido();

int buscarPedido(int );

void modificarPedido();

///REPORTES ARTICULO
///-------------------------------------------------------///
void reportePorArticulo();

void reportesArticulos();

void reportePorFechaArticulo();

void articuloMasVendido();

void articuloMasVendidoxFecha();

///-------------------------------------------------------///
///REPORTES VENDEDOR
///-------------------------------------------------------///

void ventasVendedoresEntreFechas();

void mejorEnCantidad();

void mejorEnImporte();

void mejorEnImporteFecha();

void mejorEnCantidadFecha();

void reportePorVendedor();

void reporteVendedores();
///-------------------------------------------------------///
///REPORTES CLIENTE
///-------------------------------------------------------///

void reportePorCliente();

void comprasClientesEntreFechas();

void mejorEnImporteClienteEntreFecha();

void mejorEnCantidadClienteEntreFecha();

void reporteClientes();


///-------------------------------------------------------///
///CONFIGURACION
///-------------------------------------------------------///
void mostrarVentaBackup();

void mostrarVentainicial();

bool hacerBackupVentas();

bool restablecerArchivoVentas();

///ARCHIVO ARTICULO
void mostrarArticuloBackup();

void mostrarArticuloinicial();

bool hacerBackupArticulo();

bool restablecerArchivoArticulo();

///ARCHIVOS CLIENTE
void mostrarClienteBackup();

void mostrarClienteinicial();

bool hacerBackupCliente();

bool restablecerArchivoCliente();

int Menuconfiguracion();

void seccionConfiguracion();
///FIN CONFIGURACION
///-------------------------------------------------------///

///GLOBALES
///-------------------------------------------------------///
void cartelInicial();

int Menuprincipal();

void cargarCadena(char *, int );

void cartelListarArticulos(int );

void cartelListarProveedores(int );

void cartelListarVendedores(int );

void cartelListarClientes(int );

void cartelListarVentas(int y);

void cartelReporteArticulos(int y);

void cartelFinal();

#endif // HERRAMIENTAS_H_INCLUDED
