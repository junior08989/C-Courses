#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<string>
#include<cstring>
#include <iomanip>
#include <chrono>
#include <ctime>
#include<stdio.h>
using std::setw;
using namespace std;

// Proyecto final Programacion II
// Christian Cusimano

/*
Hacer un programa que un cliente debe loguearse para poder acceder a los productos de la tienda.
El cliente puede incorporar a su carrito cada producto de la tienda que tenga stock y al finalizar se genera una orden de compra.
La tienda ve el stock disminuir en cada puesta de producto en el carrito, volviendo al stock inicial cuando el cliente abandona la compra o saliendo efectivamente cuando el cliente
genera la orden de compra.

Bases de dato:

1- Hacer una base de datos para clientes, con nombre, apellido, cedula y contraseña
2- Hacer una base de datos para productos con numero de item, nombre del producto, cantidad de stock, precio
3- Hacer una base de datos para cada carrito nuevo identificado por el cliente y con cada item que se puso en el carrito

Clases:

1- Hacer una clase para la interface hombre maquina 
    1.1-Logueo de cliente
        1.1.1- Crear cliente nuevo
        1.1.2- Ingresar credenciales

    1.2-Menu principal (informacion del cliente logueado y cantidad de items en carrito con valor total en pesos)
        1.2.1- Seleccionar productos (ver listado de productos y agregar productos)
        1.2.2- Ver y modificar carrito (ver listado de productos y eliminar productos)
        1.2.3- Finalizar compra (generar orden de compra y eliminar carrito)
        1.2.4- Salir (eliminar carrito)

2- Hacer una clase para usuario activo (en el momento que se loguea un usuario, se crea su carrito con el nombre del usuario por lo tanto, si otro usuario esta ingresando con su 
mismo numero de cedula, se ejecuta el mismo carrito osea dos maquinas distintas pueden usar el mismo carrito).
    2.1- Cada item agregado resta de la base de datos del stock y agrega a la base de datos del carrito del cliente
    2.2- Al finalizar la compra
        2.2.1- Se copian los datos del carrito y se hace la orden de compra
        2.2.2- Se elimina el carrito
    2.3- Al salir
        2.3.1- Se restablecen los items del carrito al stock de la tienda
        2.3.2- Se elimina el carrito
    2.4- Al modificar el carrito
        2.4.1- se elimina el item del carrito
        2.4.2- Se agrega al stock de la tienda el item eliminado
Funciones:

1- Crear usuario
    1.1- se solicitan los datos
    1.2- Se verifica que la cedula no esté previamente ingresada
    1.3- Se agrega a la base de datos de clientes

2- Ingresar usuario
    2.1- Se verifican los datos del cliente
        2.1.1-En caso de exito, se muestra el menu principal
        2.1.2-En caso de error, se permanece en el login y se muestra un mensaje de error

*/

void selector(void);
void menu_login();
int menu_registrarse();
int menu_ingresar();
int verificar_registro(int cedula);
int verificar_credenciales(int cedula, string contraseña);
void menu_principal(void);
void menu_gondola();
void menu_carrito();
void menu_finalizar_compra();
void actualizar_gondola(string _cod_producto, int _cantidad);
void actualizar_carrito(string _detalle, int _cantidad, string _precio);
void crear_base_de_datos();

class sesion{
    protected:
        string nombre;
        string apellido;
        int cedula;
        string contraseña;
        int cant_productos = 0;
        string nombre_carrito;
        
    public:
        sesion(){};
        virtual int mostrar(){return 0;}
        virtual void registrar_nombre(string _nombre){
            nombre = _nombre;
        }
        virtual void registrar_apellido(string _apellido){
            apellido = _apellido;
        }
        virtual void registrar_cedula(int _cedula){}
        virtual void registrar_contraseña(string _contraseña){}
        virtual void registrar_carrito(string _usuario){}

        virtual string obtener_nombre(){
            return nombre;
    }
        virtual string obtener_apellido(){
            return apellido;
        }
        virtual int obtener_cedula(){
            return cedula;
        }
        virtual string obtener_contraseña(){
            return contraseña;
        }
        virtual string obtener_carrito(){
            return nombre_carrito;
        }
        virtual void añadir_producto(string _detalle, int _cantidad, string _precio, string _codigo_producto){}
        virtual void modificar(string _codigo_producto, int _cantidad ){}
};

class cliente:public sesion{
    public:
        cliente():sesion(){}
        void registrar_nombre(string _nombre){
            nombre = _nombre;
        }
        void registrar_apellido(string _apellido){
            apellido = _apellido;
        }
        void registrar_cedula(int _cedula){
            cedula = _cedula;
        }
        void registrar_contraseña(string _contraseña){
            contraseña = _contraseña;
        }
        string obtener_nombre(){
            return nombre;
        }
        string obtener_apellido(){
            return apellido;
        }
        int obtener_cedula(){
            return cedula;
        }
        string obtener_contraseña(){
            return contraseña;
        }

};

class carrito:public sesion{

public:
    carrito():sesion(){}
    int mostrar()
    {
        fstream carrito(nombre_carrito, std::ios_base::in | std::ios_base::out);
        if(carrito.fail()){
            cerr << "Error";
            getchar();
            return -1;
        }
        string linea;
        cant_productos = 0;
        while(carrito.peek() != EOF)
        {
            getline(carrito, linea);
            if (linea.find(";000;") == -1)
            {
                cant_productos ++;
            }
        }
        return cant_productos;
    }



    void registrar_carrito(string _usuario){

    nombre_carrito = "carrito" + _usuario;


if(!fopen(nombre_carrito.c_str(), "r")){
ofstream { nombre_carrito };

}

    

    }
        
    string obtener_carrito(){
        return nombre_carrito;
    }

    void añadir_producto(string _detalle, int _cantidad, string _precio, string _cod_producto){


        fstream carrito(nombre_carrito, std::ios_base::in | std::ios_base::out);

        if(carrito.fail())
        {
            cerr << "Error";
            getchar();
            return;
        }


        // hacer un loop para buscar si el producto ya existe, si es afirmativo, sumar la cantidad y sino, agregar toda la linea


        string linea;
        int nuevo_stock;
        string stock;
        string cod_producto;
        string detalle;
        string precio;
        int posicion_anterior;
        posicion_anterior = 0;
        bool es_primer_item = true;




        do
        {
            getline(carrito, cod_producto, ';');
            posicion_anterior += cod_producto.length() + 1;
            if( _cod_producto.compare(cod_producto) == 0)
            {
                getline(carrito, detalle, ';');
                posicion_anterior += detalle.length() + 1;
                getline(carrito, stock, ';');
                es_primer_item = false;
                break;
            }
            getline(carrito, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(carrito, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(carrito, linea, '\n');
            posicion_anterior += linea.length() + 2;
        } while( carrito.eof() == 0);


        if (es_primer_item == true)
        {
            carrito.close();
            fstream carrito(nombre_carrito, ios::app);
            carrito.seekg(0, ios::beg);
            if(_cantidad < 100 && _cantidad > 9)
            {
                carrito << _cod_producto << ";" << _detalle << ";0" << _cantidad << ";" << _precio <<  endl;
            }
            else if(_cantidad < 10 && _cantidad > 0)
            {
                carrito << _cod_producto << ";" << _detalle << ";00" << _cantidad << ";" << _precio <<  endl;
            }
            else if(nuevo_stock > 99)
            {
                    carrito << _cod_producto << ";" << _detalle << ";" << _cantidad << ";" << _precio <<  endl;
            }
        }
        else
        {
            carrito.seekg(posicion_anterior, ios::beg);
            nuevo_stock = stoi(stock) + _cantidad;
            if(nuevo_stock < 100 && nuevo_stock > 9)
            {
                carrito << "0" << nuevo_stock ;
            }
            else if(nuevo_stock < 10 && nuevo_stock > 0)
            {
                carrito << "00" << nuevo_stock ;
            }
            else if(nuevo_stock > 99)
            {
                carrito << nuevo_stock ;
            }
        }
        cout << "Se aniadio al carrito: " << _cantidad << " " << _detalle << " $" << _precio << endl; 
        carrito.close();

    }




void modificar(string _cod_producto, int _cantidad )
    {

        fstream carrito(nombre_carrito, std::ios_base::in | std::ios_base::out);
        string linea;

            if(!(carrito.is_open()))
            {
                cerr << "Error";
                getchar();
                exit(1);
            }

        int cant_a_devolver;
        string cant;
        string cod_producto;
        string detalle;
        string precio;
        int posicion_anterior;
        posicion_anterior = 0;

        do
        {
            getline(carrito, cod_producto, ';');
            posicion_anterior += cod_producto.length() + 1;
            if( _cod_producto.compare(cod_producto) == 0)
            {
                getline(carrito, detalle, ';');
                posicion_anterior += detalle.length() + 1;
                getline(carrito, cant, ';');
                break;
            }
            getline(carrito, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(carrito, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(carrito, linea, '\n');
            posicion_anterior += linea.length() + 2;
        } while( _cod_producto.compare(cod_producto) != 0);

        carrito.seekg(posicion_anterior, ios::beg);

        if ((stoi(cant) - _cantidad) >= 0 ){
        cant_a_devolver = stoi(cant) - _cantidad;
        }
        else{
            _cantidad = stoi(cant);
            cant_a_devolver = stoi(cant);
        }
        if(_cantidad < 100 && _cantidad > 9)
        {
            carrito << "0" << _cantidad ;
        }
        else if(_cantidad < 10 && _cantidad > 0)
        {
            carrito << "00" << _cantidad ;
        }
        else if(_cantidad == 0)
        {
        carrito << "000";
        }

        else if(_cantidad > 99)
        {
            carrito << _cantidad ;
        }
        carrito.close();

        fstream gondola("Base de dato gondola.txt", std::ios_base::in | std::ios_base::out);

        if(!(gondola.is_open()))
        {
            cerr << "Error";
            getchar();
            exit(1);
        }

        int nuevo_stock;
        string stock;
        posicion_anterior = 0;

        do
        {
            getline(gondola, cod_producto, ';');
            posicion_anterior += cod_producto.length() + 1;
            if( _cod_producto.compare(cod_producto) == 0)
            {
                getline(gondola, detalle, ';');
                posicion_anterior += detalle.length() + 1;
                getline(gondola, stock, ';');
                break;
            }
            getline(gondola, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(gondola, linea, ';');
            posicion_anterior += linea.length() + 1;
            getline(gondola, linea, '\n');
            posicion_anterior += linea.length() + 2;
        } while( _cod_producto.compare(cod_producto) != 0);

        gondola.seekg(posicion_anterior, ios::beg);


        nuevo_stock = stoi(stock) + cant_a_devolver;
        if(nuevo_stock < 100 && nuevo_stock > 9)
        {
            gondola << "0" << nuevo_stock ;
        }
        else if(nuevo_stock < 10 && nuevo_stock > 0)
        {
            gondola << "00" << nuevo_stock ;
        }
        else if(nuevo_stock == 0)
        {
        gondola << "000";
        }
        else if(nuevo_stock > 99)
        {
            gondola << nuevo_stock ;
        }

        cout << "Carrito actualizado correctamente" << endl;
        getch();
        return;

    }

};

sesion* usuario_activo = new cliente();
sesion* carro_compra = new carrito();

void menu_login()
{
    int seleccion;
    seleccion = 0;
    system("cls");
    cout << "                Bienvenido a la tienda de componentes electronicos\n" << endl;
    cout << "1- Registrarse como cliente" << endl;
    cout << "2- Ingresar con su usuario" << endl;
    cout << "Indique una opcion: ";
    cin >> seleccion;

           switch (seleccion)
           {
           case 1: menu_registrarse(); break;
           case 2: if(menu_ingresar() == 0){ menu_principal();}; break;
           default: cout << "Ingrese una opcion valida"; getch(); menu_login(); break;
            }
    
}

int menu_registrarse()
{
    string nombre;
    string apellido;
    int cedula;
    string contraseña;
    
    system("cls");
    cout << "Registro de cliente\n";
    cout << "Indique su nombre: ";
    cin >> nombre;
    usuario_activo->registrar_nombre(nombre);
    cout << "Indique su apellido: ";
    cin >> apellido;
    usuario_activo->registrar_apellido(apellido);
    cout << "Indique su numero de cedula: ";
    cin >> cedula;
    usuario_activo->registrar_cedula(cedula);
    cout << "Indique su contrasena: ";
    cin >> contraseña;
    usuario_activo->registrar_contraseña(contraseña);


    if (verificar_registro(usuario_activo->obtener_cedula()) != 0)
    {
        cout << "Cliente ya esta registrado\n";
        system("pause");
        return 1;
    }

fstream cliente;

    cliente.open("base de dato clientes", ios::app);
    if(!(cliente.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }

    cliente << usuario_activo->obtener_cedula() << ";" << usuario_activo->obtener_nombre() << ";" << usuario_activo->obtener_apellido() << ";" << usuario_activo->obtener_contraseña() << ";" << endl;
    
    
    cliente.close();
    system("cls");

    cout << "Registro completado\n";
    getch();
    menu_login();
    return 0;
}

int menu_ingresar()
{
    int usuario;
    usuario = 0;
    string contraseña;
    contraseña = "N/A";
    system("cls");
    cout << "Ingresar a la tienda\n";
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasena: ";
    cin >> contraseña;

    switch (verificar_credenciales(usuario, contraseña))
    {
        case 0: cout << "Cliente ingresado con exito\n"; getch(); break;
        case 1: cout << "Contrasena invalida\n"; system("pause"); return 1;
        case 2: cout << "Usuario invalido\n"; system("pause"); return 2;
    }
    
    string nombre_carrito = "";
    
    carro_compra->registrar_carrito(to_string(usuario));

    return 0;
}

int main(void){

    while(1)
    {
        crear_base_de_datos();
        menu_login();
         
    }
    return 0;
}

int verificar_registro(int cedula){

    fstream cliente;
    string linea;
    cliente.open("Base de dato clientes", ios::in);
    if(!(cliente.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }

    while(getline(cliente, linea))
    {
        if (cedula == stoi(linea.substr(0, linea.find(";"))))
        {
            cliente.close();
            return 1;
        }
    }
    cliente.close();
    return 0;
}

int verificar_credenciales(int cedula, string contraseña){

    fstream cliente;
    string linea;
    cliente.open("Base de dato clientes", ios::in);
    if(!(cliente.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }

    while(cliente.peek() != EOF)
    {
        if (!cliente.eof())
        {
            getline(cliente, linea, ';');   
            if (cedula == stoi(linea.substr(0, linea.find(";"))))
            {
                usuario_activo->registrar_cedula(cedula);
                getline(cliente, linea, ';');
                usuario_activo->registrar_nombre(linea);
                getline(cliente, linea, ';');
                usuario_activo->registrar_apellido(linea);
                getline(cliente, linea, ';');
            if (linea == contraseña)
            {
                cliente.close();
                return 0;
            }
            else
            {
                cliente.close();
                return 1;
            }
           system("pause");
            }
            else 
            {
                getline(cliente, linea, ';');
                getline(cliente, linea, ';');
                getline(cliente, linea, ';');
                getline(cliente, linea, '\n');
            }
        }
    }
    cliente.close();
    return 2;
}

void menu_principal(void)
{
    int seleccion;
    system("cls");
    cout << "Cliente: " << usuario_activo->obtener_nombre() << " " << usuario_activo->obtener_apellido();
    cout << right << setw(80) << "Su carrito tiene " << carro_compra->mostrar() << " productos" << endl;
    cout << "1- Comprar" << endl;
    cout << "2- Ver carrito" << endl;
    cout << "3- Finalizar compra" << endl;
    cout << "4- Salir" << endl;
    cin >> seleccion; 

    switch (seleccion)
    {
        case 1: menu_gondola(); break;
        case 2: menu_carrito(); break;
        case 3: menu_finalizar_compra(); break;
        case 4: exit; break;
        default: cout << "Ingrese una opcion valida"; getch(); menu_login(); break;
    }
  
}

void menu_gondola()
{
    system("cls");
    while(1)
    {
    string cod_producto;
    int cantidad;
    char seguir_comprando;
    int respuesta = 1;
    fstream gondola;
    string linea;
    gondola.open("Base de dato gondola.txt", ios::in);
    if(!(gondola.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }

    cout << left << setw(22) << "Item: " << setw(30) << "Producto: " << setw(22) << "Stock:" << setw(22) << "Precio:" << endl;

    string item;
    string producto;
    string stock;
    string precio;
    getline(gondola, linea, ';');
    item = linea;
    getline(gondola, linea, ';');
    producto = linea;
    getline(gondola, linea, ';');
    stock = linea;
    getline(gondola, linea, '\n');
    precio = linea;

    if (stoi(stock) != 0)
    {
        cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << precio << endl;
    }

    while(gondola.peek() != EOF)
    {
        getline(gondola, linea, ';');
        item = linea;
        getline(gondola, linea, ';');
        producto = linea;
        getline(gondola, linea, ';');
        stock = linea;
        getline(gondola, linea, '\n');
        precio = linea;

        if (stoi(stock) != 0)
        {
            cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << precio << setw(22) << endl;
        }
    }
    
    cout << "Indique el codigo de producto o (S)alir: ";
    cin >> cod_producto;

    switch(toupper(cod_producto[0]))
    {
        case 'S':     respuesta = 0; gondola.close(); system("cls"); menu_principal(); break;
        default: ;break;
    }
    cout << "Cantidad: ";
    cin >> cantidad;
    gondola.close();
    cout << "Desea validar S/N?" << endl;
    cin >> seguir_comprando;
    switch(toupper(seguir_comprando))
    {
        case 'N':     respuesta = 0; gondola.close(); system("cls"); menu_gondola(); break;
        case 'S': break;
        default: cout << "Ingrese una opcion correcta\n";break;
    }
    cod_producto[0] = toupper(cod_producto[0]);
    actualizar_gondola(cod_producto, cantidad);

    do
    {
    cout << "desea seguir comprando? S/N";
    cin >> seguir_comprando;
    
    switch(toupper(seguir_comprando))
    {
        case 'S':     respuesta = 0; gondola.close(); system("cls"); menu_gondola(); break;
        case 'N': menu_principal();
        default: cout << "Ingrese una opcion correcta\n";break;
    }
    }
    while(respuesta = 1);
    }

    menu_principal();
}

void actualizar_gondola(string _cod_producto, int _cantidad)
{

    fstream gondola("Base de dato gondola.txt", std::ios_base::in | std::ios_base::out);
    string linea;

    if(!(gondola.is_open()))
    {
        cerr << "Error";
        getchar();
        exit(1);
    }

    int nuevo_stock;
    string stock;
    string cod_producto;
    string detalle;
    string precio;
    int posicion_anterior;
    posicion_anterior = 0;


    do
    {
        getline(gondola, cod_producto, ';');
        posicion_anterior += cod_producto.length() + 1;
        if( _cod_producto.compare(cod_producto) == 0)
        {
            getline(gondola, detalle, ';');
            posicion_anterior += detalle.length() + 1;
            getline(gondola, stock, ';');
            break;
        }
        getline(gondola, linea, ';');
        posicion_anterior += linea.length() + 1;
        getline(gondola, linea, ';');
        posicion_anterior += linea.length() + 1;
        getline(gondola, linea, '\n');
        posicion_anterior += linea.length() + 2;

    } while( _cod_producto.compare(cod_producto) != 0);

    gondola.seekg(posicion_anterior, ios::beg);

    nuevo_stock = stoi(stock) - _cantidad;
    if(nuevo_stock < 100 && nuevo_stock > 9)
    {
        gondola << "0" << nuevo_stock ;
    }
    else if(nuevo_stock < 10 && nuevo_stock > 0)
    {
        gondola << "00" << nuevo_stock ;
    }
    else if(nuevo_stock == 0)
    {
    gondola << "000";
    }
    else if(nuevo_stock < 0)
    {
    cerr << "Stock insuficiente, elija una cantidad menor\n";
    return ;
    }
    else if(nuevo_stock > 99)
    {
        gondola << nuevo_stock ;
    }
    gondola.seekg(1, ios::cur);
    getline(gondola, precio, '\n');
    gondola.close();
    carro_compra->añadir_producto(detalle, _cantidad, precio, cod_producto);

}

void menu_carrito(){

    int seleccion;
    system("cls");
    cout << "Cliente: " << usuario_activo->obtener_nombre() << " " << usuario_activo->obtener_apellido() << endl;

    fstream carrito;
    string linea;

    carrito.open(carro_compra->obtener_carrito(), ios::in);
    if(!(carrito.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }
    cout << "\n";
    cout << left << setw(22) << "Item: " << setw(30) << "Producto: " << setw(22) << "Cantidad:" << setw(22) << "Precio por unidad:" << "Precio total:" << endl;
    int cant = 0;
    int acumulador = 0;
    int total = 0;
    string item;
    string producto;
    string stock;
    string precio;
    getline(carrito, linea, ';');
    item = linea;
    getline(carrito, linea, ';');
    producto = linea;
    getline(carrito, linea, ';');
    stock = linea;
    getline(carrito, linea, '\n');
    precio = linea;


    if (stoi(stock) != 0)
    {
            cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << "$" + precio << setw(0) << "$" << setw(22) << (stoi(precio) * stoi(stock)) << endl;

    }
    cant = stoi(stock);
    acumulador += cant;
    total = stoi(precio) * cant;



    while(carrito.peek() != EOF)

    {
        getline(carrito, linea, ';');
        item = linea;
        getline(carrito, linea, ';');
        producto = linea;
        getline(carrito, linea, ';');
        stock = linea;
        getline(carrito, linea, '\n');
        precio = linea;

        if (stoi(stock) != 0)
        {
            cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << "$" + precio << setw(22) << setw(0) << "$" << setw(22) << (stoi(precio) * stoi(stock)) << endl;
        }
        cant = stoi(stock);
        acumulador += cant;
        total += stoi(precio) * cant;
    }

    cout << "Su carrito tiene " << acumulador << " productos" << endl;
    cout << "El valor de su carrito es de : $" << total << endl;
    cout << "\n1- Modificar carrito" << endl;
    cout << "2- Pasar por caja" << endl;
    cout << "3- Volver al menu principal" << endl;

    cin >> seleccion; 

    string cod_producto;
    int cantidad;
    
    switch (seleccion)
    {
        case 1: 
        cout << "Indique el codigo del producto que desea modificar: ";
        cin >> cod_producto;
        cout << "Indique la cantidad que desea mantener: ";
        cin >> cantidad;
        cod_producto[0] = toupper(cod_producto[0]);
        carro_compra->modificar(cod_producto, cantidad); break;

        case 2: menu_finalizar_compra(); break;

        case 3: menu_principal(); break;
           default: cout << "Ingrese una opcion valida"; getch(); menu_carrito(); break;
    }
    menu_carrito();

    return;
}

void menu_finalizar_compra(){

    system ("cls");
    time_t fecha;
    fecha = time(NULL);
    tm *pfecha = localtime(&fecha);

    cout << "Empresa: Tienda de componentes electronicos" << endl;
    cout << "Efactura Numero: " << rand() * pfecha->tm_sec << endl;
    cout << "Cliente: " << usuario_activo->obtener_nombre() << " " << usuario_activo->obtener_apellido() << endl;
    cout << "Fecha : " << pfecha->tm_mday << "/" << pfecha->tm_mon << "/" << pfecha->tm_year << " Hora: " << pfecha->tm_hour << ":" << pfecha->tm_min << ":" << pfecha->tm_sec << endl;


    fstream carrito;
    string linea;

    carrito.open(carro_compra->obtener_carrito(), ios::in);
    if(!(carrito.is_open()))
    {
        cout << "Error";
        getchar();
        exit(1);
    }
    cout << "\n";
    cout << left << setw(22) << "Item: " << setw(30) << "Producto: " << setw(22) << "Cantidad:" << setw(22) << "Precio por unidad:" << "Precio total:" << endl;
    int cant = 0;
    int total = 0;
    string item;
    string producto;
    string stock;
    string precio;
    getline(carrito, linea, ';');
    item = linea;
    getline(carrito, linea, ';');
    producto = linea;
    getline(carrito, linea, ';');
    stock = linea;
    getline(carrito, linea, '\n');
    precio = linea;

    cout << "-----------------------------------------------------------------------------------------------------------------"  << endl;
    if (stoi(stock) != 0)
    {
            cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << "$" + precio << setw(0) << "$" << setw(22) << (stoi(precio) * stoi(stock)) << endl;
    }

    cant = stoi(stock);
    total = stoi(precio) * cant;

    while(carrito.peek() != EOF)
    {
        getline(carrito, linea, ';');
        item = linea;
        getline(carrito, linea, ';');
        producto = linea;
        getline(carrito, linea, ';');
        stock = linea;
        getline(carrito, linea, '\n');
        precio = linea;

        if (stoi(stock) != 0)
        {
            cout << left << setw(22) << item << setw(30) << producto << setw(22) << stock << setw(22) << "$" + precio << setw(22) << setw(0) << "$" << setw(22) << (stoi(precio) * stoi(stock)) << endl;
        }
        cant = stoi(stock);
        total += stoi(precio) * cant;
    }

    cout << "-----------------------------------------------------------------------------------------------------------------"  << endl;
    cout << right << setw(11) << "Subtotal : " << right << setw(8) << fixed << setprecision(2) << (float) total  << endl;
    cout << right << setw(11) << "IVA (22%): "  << right << setw(8) << (float) total * 0.22 << endl;
    cout << right << setw(11) << "Total: " << right << setw(8) << (float) total * 1.22 << endl;
    cout << "\n\nGracias por su compra" << endl;


carrito.close();

ofstream {carro_compra->obtener_carrito()};


    getch();
    
    exit(1);

    return;
}

void crear_base_de_datos()
{
    fstream gondola;
   
    gondola.open("Base de dato gondola.txt");
    if(gondola.fail())
    {
        ofstream { "Base de dato gondola.txt" };

        gondola.open("Base de dato gondola.txt", ios:: out);

        gondola << "P110;Resistencia 100 ohm;204;1" << endl;
        gondola << "P111;Resistencia 220 ohm;200;2" << endl;
        gondola << "P112;Resistencia 1.0K omh;207;2" << endl;
        gondola << "P113;Resistencia 2.2K ohm;209;2" << endl;
        gondola << "P114;Resistencia 10K ohm;200;3" << endl;
        gondola << "P115;Resistencia 20K ohm;249;3" << endl;
        gondola << "P116;Resistencia 1M ohm;200;3" << endl;
        gondola << "P117;Led RGB;200;5" << endl;
        gondola << "P118;Led Rojo;200;4" << endl;
        gondola << "P119;Led Azul;195;4" << endl;
        gondola << "P120;Led Verde;200;4" << endl;
        gondola << "P121;Diod;200;3" << endl;
        gondola << "P122;Diodo Zener;200;4" << endl;
        gondola << "P123;Capacitor 1uF;050;3" << endl;
        gondola << "P124;Capacitor 20 uF;200;4" << endl;
        gondola << "P125;Capacitor 200 uF;200;4" << endl;
        gondola << "P126;Inductor 1mH;200;3" << endl;
        gondola << "P127;Inductor 100 mH;200;4" << endl;
        gondola << "P128;Protoboard;200;9" << endl;
        gondola << "P129;Jumpers Macho x10;199;5" << endl;
        gondola << "P130;Jumpers Hembra x10;000;5" << endl;
        gondola << "P131;Jumpers M/H x10;196;5" << endl;
    }

    gondola.close();

    fstream cliente;

    cliente.open("Base de dato clientes", ios::app);
    if(cliente.fail())
    {
        ofstream { "Base de dato clientes" };
    }

    cliente.close();

    return;
}