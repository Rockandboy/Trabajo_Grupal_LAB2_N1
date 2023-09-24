#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/// Colocar las Librerías que se utilizarán

#include "Structs.h" /// Librería con los Structs y constantes de los Archivos
#include "string.h"
#include <cstdio>
#include <iostream>
#include "libxl.h"
//#include <locale.h> /// Libreria que contiene la funcion setlocale (rompe el diseño del menú)

using namespace libxl; /// Utiliza el espacio de nombres de libxl para abreviar las referencias
using namespace std;

/// --------------------------- PROTOTIPOS DE LAS FUNCIONES ---------------------------
// 1) --------------------------------------------------------------
bool existeRegistroPais(char *codigo);  // Verifico si existe Registro.

// 2) --------------------------------------------------------------
void cargarPais();          // Cargo un registro de Struct.
void grabarPais(Pais reg);  // Grabo en Archivo.

// 3) --------------------------------------------------------------
void leerPaises();          // Leo el Archivo.
void mostrarPais(Pais reg); // Recibo el Registro leido del archivo y lo muestro. Registro x Registro, sin uso de Vectores.

// 4) --------------------------------------------------------------
void mostrarCiudadesxPais();                  // Leo el archivo Ciudades. Dentro de la función se debe pedir al Usuario que ingrese el nombre del Pais.
struct Pais obtenerRegistroPais(char *pais);  // Recibe el nombre del Pais y busca su registro.
// Revisar la opción de pedir primero el ingreso para obtener el Registro y luego leer el archivo Ciudades.

// 5) --------------------------------------------------------------
void listarPaises_Superficies();    // Leer y guardar los Registros en un Vector.
// Calcular el Total de Superficie Mundial.
// Mostrar dentro de la función misma, NOMBRE - SUPERFICIE - PORCENTAJE %

// 6) --------------------------------------------------------------
void totalesxContinente();
// Leo el archivo Paises. Dentro de la función se debe pedir al Usuario que ingrese el nombre del Pais.
// Guardo en un vector los registros.
// Calculo los totales y promedios. Muestro.

// 7) --------------------------------------------------------------
void modificarPais();               // Pido el codigo de pais a modificar.
// Verificar que exista.
// Buscar registro (usar función respectiva).
// Ingresar los nuevos valores y reemplazar.
void grabarPaisModificado(Pais reg);    // Guardar Pais Modificado.

// 8) --------------------------------------------------------------
void modificarCiudad();             // Pido el codigo de la ciudad a modificar.
bool existeRegistroCiudad(int id);        // Verifico si existe Registro. (SOBRECARGA DE FUNCIONES)
// Ingreso codigo pais y verifico si existe
void grabarCiudadModificado(Ciudad reg);  // Guardar Ciudad Modificada. (SOBRECARGA DE FUNCIONES)

// 9) --------------------------------------------------------------
void totalesPais_Poblacion();

// 10) --------------------------------------------------------------
void buscarMayorPoblacion();

/// ADICIONALES IMPORTANTES
int contarPaises();     // Contar Registros Archivo Paises
int contarCiudades();   // Contar Registros Archivo Ciudades

long long contarPoblacionMundial();

/// PUNTOS 11 y 12 (OPCIONALES)
/// COLOCAR AQUÍ LOS PROTOTIPOS DE LAS FUNCIONES

int exportarAexcel();
void crearExcel(); //void cargarHoja1(Sheet *hoja);
void cargarHoja2(Sheet *hoja, Book *libro);
bool SalirDeFuncion();
void menuModificacionPais();
struct Ciudad obtenerRegistroCiudad(int ciudad);

/// --------------------------- DESARROLLO DE LAS FUNCIONES ---------------------------

// 1) --------------------------------------------------------------
//  Agregar una función global que busque un registro de país a partir de su código.
//  La función debe poder devolver si el registro existe o no.

bool existeRegistroPais(char *codigo)  // Verifico si existe Registro.
{
    bool retorno=false;
    FILE* archivo;
    Pais existe;
    archivo = fopen(ARCHIVO_PAISES,"rb");
    if (archivo==NULL)
    {
        cout << "ERROR DE APERTURA" << endl;
    }
    else
    {
        while(fread(&existe,sizeof(Pais),1,archivo)==1)
        {
            if (strcmp(codigo,existe._codigo)==0)
            {
                retorno=true;
            }
        }
    }
    fclose(archivo);
    return retorno;
}

// 2) --------------------------------------------------------------
//  Agregar una función global que permita agregar un registro de País al archivo de países

void cargarPais()
{
    Pais cargar;
    char codigo[4];
    bool salir=false;
    while (salir==false)
    {
        cin.getline(codigo,4);
        if (existeRegistroPais(codigo)==false)
        {
            strcpy(cargar._codigo,codigo);
            cout << "Cargar Codigo 2 EJ: AR" << endl;
            cin.getline(cargar._codigo2,3);
            cout << "Cargar Nombre de Pais" << endl;
            cin.getline(cargar._nombre,45);
            cout << "Cargar continente" << endl;
            cin.getline(cargar._continente,20);
            cout << "Cargar superficie del pais" << endl;
            cin >> cargar._superficie;
            cout << "Cargar Poblacion del pais" << endl;
            cin >> cargar._poblacion;
            cout << "Cargar año de independencia " << endl;
            cin >> cargar._independencia;
            cout << "Cargar expectativa de vida del pais " << endl;
            cin >> cargar._expectativaDeVida;
            cout << "Cargar ID de la ciudad capital" << endl;
            cin >> cargar._capital;
            grabarPais(cargar);
        }
        else
        {
            cout << "ERROR: Codigo Existente" << endl;
        }
        salir=SalirDeFuncion();
    }
}


void grabarPais(Pais reg)
{
    FILE* archivo;
    //apertura
    archivo = fopen(ARCHIVO_PAISES,"ab");
    //carga de registros
    fwrite(&reg,sizeof(Pais),1,archivo);
    //cierro el archivo
    fclose(archivo);
}


// 3) --------------------------------------------------------------
//   Agregar una función global que permita listar todos los países del archivo de países.

void leerPaises()
{
    //setlocale(LC_ALL, ""); // mostrar caracteres en español
    FILE *archivo;
    Pais leer;// variable tipo struct Pais donde guardo el contenido a mostrar
    //apertura del archivo "MODO: Lectura"
    archivo = fopen(ARCHIVO_PAISES,"rb");
    // leo el archivo
    if (archivo==NULL)
    {
        cout << "ERROR DE APERTURA" << endl;
    }
    else
    {
        while(fread(&leer, sizeof(Pais),1,archivo)==1)
        {
            mostrarPais(leer);
        }
    }
    system ("pause");
    // cierro archivo
    fclose(archivo);
}


void mostrarPais(Pais mostrar)
{
    cout << "   Codigo de Pais:\t"<<mostrar._codigo<<endl;
    cout << "   Codigo 2:\t        "<<mostrar._codigo2<<endl;
    cout << "   Nombre:\t        "<<mostrar._nombre<<endl;
    cout << "   Continente:\t        "<<mostrar._continente<<endl;
    cout << "   Superficie:\t        "<<mostrar._superficie<< " Km cuadrados"<<endl;
    cout << "   Poblacion:\t        "<<mostrar._poblacion<<" habitantes"<<endl;
    cout << "   Independencia:\t"<<mostrar._independencia<<endl;
    cout << "   Expectativa de vida:\t"<<mostrar._expectativaDeVida<<endl;
    cout << "   Capital:\t        "<<mostrar._capital<<endl;
    cout <<endl;
}


// 4) --------------------------------------------------------------
//  Agregar una función global que permita listar todas las ciudades y su población que pertenezcan a un país
//  cuyo código se ingresa previamente por teclado.
//  Mostrar la capital del país, si se tiene registro de ella, al ﬁnal de todo.

void mostrarCiudadesxPais()
{
    FILE* archivo;
    Ciudad leerCiudad,guardarCapital;
    Pais retornoPais;
    char codigo[4];
    cin.ignore();
    bool salir=false;
    while(salir==false)
    {
        archivo = fopen(ARCHIVO_CIUDADES,"rb");
        cout <<" \n Ingrese el codigo de pais, por ejemplo ARG" << endl;
        cin.getline(codigo,4);
        clrscr();
        if (existeRegistroPais(codigo)==true) //valido el codigo ingresado
        {
            retornoPais = obtenerRegistroPais(codigo);
            while(fread(&leerCiudad,sizeof(Ciudad),1,archivo)==1)
            {
                if ((strcmp(leerCiudad._idpais,retornoPais._codigo)==0) && (retornoPais._capital!= leerCiudad._ID))
                {
                    cout << "Codigo de ciudad: " << leerCiudad._ID << endl;
                    cout << "Nombre:           " << leerCiudad._nombre << endl;
                    cout << "Pais:             " << leerCiudad._idpais << endl;
                    cout << "Poblacion:        " << leerCiudad._poblacion <<" habitantes."<< endl;
                    cout << "------------------------------" << endl;
                }
                else if (retornoPais._capital==leerCiudad._ID)
                {
                    guardarCapital._ID = leerCiudad._ID;
                    strcpy(guardarCapital._idpais,leerCiudad._idpais);
                    strcpy(guardarCapital._nombre,leerCiudad._nombre);
                    guardarCapital._poblacion = leerCiudad._poblacion;
                }
            }
            cout << endl;
            cout << "Ciudad Capital de "<< guardarCapital._idpais << endl;
            cout << "Codigo de ciudad: " << guardarCapital._ID << endl;
            cout << "Nombre:           " << guardarCapital._nombre << endl;
            cout << "Poblacion:        " << guardarCapital._poblacion <<" habitantes."<< endl;
            cout << "------------------------------" << endl;
        }
        else
        {
            cout << "ERROR: Codigo Inexistente" << endl;
        }
        fclose(archivo);
        salir = SalirDeFuncion();
        clrscr();
    }
}


struct Pais obtenerRegistroPais(char *pais) // Recibe el nombre del Pais y busca su registro.
// Revisar la opción de pedir primero el ingreso para obtener el Registro y luego leer el archivo Ciudades.
{
    Pais buscar;
    FILE* archivo;
    archivo = fopen(ARCHIVO_PAISES,"rb");
    while(fread(&buscar,sizeof(Pais),1,archivo)==1)
    {
        if(strcmp(buscar._codigo,pais)==0)
        {
            return buscar;
        }
    }
}


// 5) --------------------------------------------------------------
//  Agregar una función global que permita listar todos los países con su nombre y superﬁcie.
//  Además, indicar qué porcentaje representa esa superﬁcie sobre el total mundial.

void listarPaises_Superficies()
{
    const int tam = contarPaises();//cantidad de paises
    double porc=0,sumaSuperficies=0;
    Pais leer[tam];
    FILE* archivo;
    //abro archivo
    archivo=fopen(ARCHIVO_PAISES,"rb");
    if (archivo==NULL)
    {
        cout << "ERROR DE APERTURA" << endl;
    }
    fread(leer,sizeof(Pais),tam,archivo);
    //leo el archivo
    for (int i=0; i<tam; i++)
    {
        //sumo para obtener la superficie mundial
        sumaSuperficies += leer[i]._superficie;

    }
    for (int x=0; x<tam; x++)
    {
        porc = (leer[x]._superficie/sumaSuperficies)*100;
        cout << "PAIS:          " << leer[x]._nombre <<endl;
        cout << "Superficie:    " << leer[x]._superficie << " Km cuadrados" <<endl;
        cout << "Representa el: " << porc <<" % de la superficie mundial." << endl;
        cout << "------------------------------------------------------------------------" << endl;
    }
    cout << "La superficie mundial es "<< sumaSuperficies <<endl;
    cout << "" <<endl;
    fclose(archivo);
    system("pause");
}


// 6) --------------------------------------------------------------
//  Agregar una función global que calcule estadísticas especíﬁcas por Continente,
//  como la población total, y la densidad poblacional promedio de cada continente.

void totalesxContinente()// Leo el archivo Paises. Dentro de la función se debe pedir al Usuario que
// ingrese el nombre del Pais. Guardo en un vector los registros.
// Luego calculo los totales y promedios.
{
    FILE *archivo;
    const int tam = contarPaises();//tam cantidad de paises
    long  supContinente=0, pobContinente=0; //si es double dá resultado con notacion cientifica
    double densPoblacional=0;

    cin.ignore();
    Pais vLeer[tam], continente; //vector donde guardo datos para leer
    Pais retornoPais; //guardo los registros del codigo de pais ingresado
    char codigo[4];
    bool salir=false;
    while(salir==false)
    {
        archivo = fopen(ARCHIVO_PAISES,"rb");
        if (archivo==NULL) // verifico si abrió bien
        {
            cout << "ERROR DE APERTURA" << endl;
        }
        fread(vLeer,sizeof(Pais),tam,archivo); //leo el archivo

        cout <<"\nIngrese el codigo de pais, por ejemplo ARG" << endl;
        cin.getline(codigo,4);
        clrscr();

        if (existeRegistroPais(codigo)==true) //valido el codigo ingresado
        {
            retornoPais = obtenerRegistroPais(codigo);

            cout<<""<<endl;
            cout << "----------------------------------------------------------" << endl;
            cout << "Pais:                 " << retornoPais._nombre << endl;
            cout << "Continente            " << retornoPais._continente << endl;

            for (int i=0; i<tam; i++)
            {
                if(strcmp(retornoPais._continente,vLeer[i]._continente)==0)
                {
                    supContinente+=vLeer[i]._superficie;
                    pobContinente+=vLeer[i]._poblacion;
                    densPoblacional=pobContinente/supContinente;
                }
            }
            cout << "----------------------------------------------------------" << endl;
            cout << "Datos estadisticos de " << retornoPais._continente << ":" <<endl;
            cout << "" << endl;
            cout << "Superficie:           " << supContinente <<" Km cuadrados"<<endl;
            cout << "Poblacion:            "<< pobContinente <<" habitantes"<<endl;
            cout << "Densidad poblacional  "<< densPoblacional <<" habitantes por Km cuadrado"<<endl;
            cout << endl;
        }
        else
        {
            cout << "ERROR: Codigo Inexistente" << endl;
        }
        fclose(archivo);// cierro archivo
        salir = SalirDeFuncion();
        supContinente = 0;
        pobContinente = 0;
        densPoblacional = 0;
    }
}


// 7) --------------------------------------------------------------
void modificarPais()               // Pido el codigo de pais a modificar.
{
    Pais retorno;
    char codigo[4],opc;
    bool salir=false;
    while (salir==false)
    {
        cout << "Ingrese el codigo a modificar" << endl;
        cin.getline(codigo,4);
        cout << endl;
        if (existeRegistroPais(codigo)==true)
        {
            retorno = obtenerRegistroPais(codigo);
            menuModificacionPais();
            cin >> opc;
            cin.ignore();
            switch (opc)
            {
            case '1':
            {
                cout << "Ingrese el Codigo de pais para modificarlo" << endl;
                ///cambiar nombre
                cin.getline(retorno._nombre,45);
                grabarPaisModificado(retorno);
                salir = SalirDeFuncion();
                break;
            }
            case '2':
            {
                cout << "Ingrese el continente para modificarlo" << endl;
                ///Cambiar Continente
                cin.getline(retorno._continente,20);
                grabarPaisModificado(retorno);
                salir = SalirDeFuncion();
                break;
            }
            case '3':
            {
                cout << "Ingrese la poblacion para modificarlo" << endl;
                ///Cambiar Poblacion
                cin >> retorno._poblacion;
                grabarPaisModificado(retorno);
                salir = SalirDeFuncion();
                break;
            }
            case '4':
            {
                cout << "Ingrese la expectativa de vida para modificarlo" << endl;
                ///expectativa de vida
                cin >> retorno._expectativaDeVida;
                grabarPaisModificado(retorno);
                salir = SalirDeFuncion();
                break;
            }
            default:
            {
                cout << "Error: Opcion invalida" << endl;
                //salir = SalirDeFuncion();
                break;
            }
            }
        }
        else
        {
            cout << "ERROR: Codigo Inexistente" << endl;
        }
        clrscr();
    }
}
// Verificar que exista.
// Buscar registro (usar función respectiva).
// Ingresar los nuevos valores y reemplazar.
void grabarPaisModificado(Pais reg)    // Guardar Pais Modificado.
{
    FILE* archivo;
    Pais mod;
    int grabo = 0;
    archivo = fopen(ARCHIVO_PAISES,"rb+");
    if (archivo == NULL)
    {
        cout << "Error: Archivo inexistente" << endl;
    }
    else
    {
        while(fread(&mod,sizeof(Pais),1,archivo)==1)
        {
            if (strcmp(mod._codigo,reg._codigo)==0)
            {
                ///cargo los datos modificados
                strcpy(mod._nombre,reg._nombre);
                strcpy(mod._continente,reg._continente);
                mod._poblacion = reg._poblacion;
                mod._capital = reg._capital;
                ///posiciono al puntero
                fseek(archivo,ftell(archivo)-sizeof(Pais),0);
                ///sobreescribo en el archivo
                grabo = fwrite(&mod,sizeof(Pais),1,archivo);
                if (grabo == 1)
                {
                    cout << "Modificacion exitosa" << endl;
                    fclose(archivo);
                }
                else
                {
                    cout << "Error: Modificacion no lograda" << endl;
                    fclose(archivo);
                }
            }
        }
    }

}


// 8) --------------------------------------------------------------
void modificarCiudad()    // Pido el codigo de la ciudad a modificar.
{
    Ciudad retorno;
    int codigo;
    bool salir=false;
    while (salir==false)
    {
        cout << "Ingrese el codigo a modificar" << endl;
        cin >> codigo;
        if (existeRegistroCiudad(codigo)==true)
        {
            retorno = obtenerRegistroCiudad(codigo);
            cin.ignore();
            cout << "Ingrese el ID de pais para modificarlo" << endl;
            cin.getline(retorno._idpais,4);
            grabarCiudadModificado(retorno);
        }
        else
        {
            cout << "ERROR: Codigo Inexistente" << endl;
        }
        salir = SalirDeFuncion();
        clrscr();

    }
}


bool existeRegistroCiudad(int id)  // Verifico si existe Registro de ciudad y a la vez si el IDPAIS que esta adjunto existe. (SOBRECARGA DE FUNCIONES) // Ingreso codigo pais y verifico si existe
{
    bool retorno=false;
    FILE* archivo;
    Ciudad existe;
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    if (archivo==NULL)
    {
        cout << "ERROR DE APERTURA" << endl;
    }
    else
    {
        while(fread(&existe,sizeof(Ciudad),1,archivo)==1)
        {
            if ((id==existe._ID) && (existeRegistroPais(existe._idpais)==true))
            {
                retorno=true;
            }
        }
    }
    fclose(archivo);
    return retorno;
}

void grabarCiudadModificado(Ciudad reg)  // Guardar Ciudad Modificada. (SOBRECARGA DE FUNCIONES)
{
    FILE* archivo;
    Ciudad mod;
    int grabo = 0;
    archivo = fopen (ARCHIVO_CIUDADES,"rb+");
    if (archivo == NULL)
    {
        cout << "Error: Archivo inexistente" << endl;
    }
    else
    {
        while(fread(&mod,sizeof(Ciudad),1,archivo)==1)
        {
            if (mod._ID==reg._ID)
            {
                ///cargo los datos modificados
                strcpy(mod._idpais,reg._idpais);
                ///posiciono al puntero
                fseek(archivo,ftell(archivo)-sizeof(Ciudad),0);
                ///sobreescribo en el archivo
                grabo = fwrite(&mod,sizeof(Ciudad),1,archivo);
                if (grabo == 1)
                {
                    cout << "Modificacion exitosa" << endl;
                    fclose(archivo);
                }
                else
                {
                    cout << "Error: Modificacion no lograda" << endl;
                    fclose(archivo);
                }
            }
        }
    }

}



// 9) --------------------------------------------------------------
// Agregar una función global que nos muestre la cantidad de Países existentes
// y el total de la poblacion mundial.

void totalesPais_Poblacion()
{
    cout<<""<<endl;
    cout << "----------------------------------------------------------" << endl;
    cout<<" El total de paises es: "<<contarPaises()<<endl;
    cout<<""<<endl;
    cout<<" El total de la poblacion mundial es: "<<contarPoblacionMundial()<<endl;
    cout << "----------------------------------------------------------" << endl;
    cout<<""<<endl;
    system ("pause");
}

int contarCiudades()
{
    FILE *archivo;
    int totalCiudades=0;
    Ciudad contarC;
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    while(fread(&contarC, sizeof(Ciudad),1,archivo)==1)
    {
        totalCiudades++;
    }
    fclose(archivo);

    return totalCiudades;
}


// 10) --------------------------------------------------------------
// Agregar una función global que muestre la ciudad con mayor población en todo el Mundo.
// Mostrando su: Nombre de Ciudad, Población, Nombre de País y Continente al que pertenece.

void buscarMayorPoblacion()
{
    const int tam = contarCiudades(); //cantidad de ciudades
    FILE *archivo;
    bool bandera = false;
    char codigoPais[4]; //guarda codigo de pais de ciudad con mayor poblacion,
    //se usa para enviar a la funcion que devuelve el registro del pais completo
    Pais retornoPais; //variable tio struc Pais que guarda lo que devuelve la funcion obteberRegistroPais.
    Ciudad ciudades[tam], ciudadMax;
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    if (archivo==NULL) // verifico si abrió bien
    {
        cout << "ERROR DE APERTURA" << endl;
    }
    fread(ciudades,sizeof(Ciudad),tam,archivo);
    for (int i=0; i<tam; i++) //comparo mayor poblacion
    {
        if (bandera == false)
        {
            bandera = true;
            ciudadMax._poblacion = ciudades[i]._poblacion;
        }
        else if (ciudadMax._poblacion < ciudades[i]._poblacion)
        {
            ciudadMax._poblacion = ciudades[i]._poblacion;//guardo poblacion maxima
            strcpy(ciudadMax._nombre,ciudades[i]._nombre);//guardo nombre ciudad mayor Pob
            strcpy(ciudadMax._idpais,ciudades[i]._idpais);//guardo id pais de ciudad mayor Pob
        }
    }
    strcpy(codigoPais,ciudadMax._idpais);//guardo en codigoPais el ID de pais de ciudad mayor Pob
    retornoPais = obtenerRegistroPais(codigoPais);//envio a funcion el dato para obtener el codPais
    cout<<""<<endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Ciudad con mayor poblacion mundial: " << ciudadMax._nombre<<endl;
    cout << "Habitantes:                         " << ciudadMax._poblacion<<endl;
    cout << "Pais:                               " << retornoPais._nombre<<endl;
    cout << "Continente:                         " << retornoPais._continente<<endl;
    cout << "----------------------------------------------------------" << endl;
    system("pause");
    fclose(archivo); //cierro archivo
}


/// ADICIONALES IMPORTANTES

int contarPaises()
{
    // abro el archivo en modo lectura
    FILE *archivo;
    int totalPaises=0;
    Pais contarP;//variable tipo struct Pais donde guardo el contenido a mostrar
    archivo = fopen(ARCHIVO_PAISES,"rb");
    // leo el archivo
    while(fread(&contarP, sizeof(Pais),1,archivo)==1)
    {
        totalPaises++;
    }
    fclose(archivo);// cierro archivo
    return totalPaises;//retorno de la funcion (cantidad de paises)
}


long long contarPoblacionMundial()
{
    FILE *archivo;
    long long totalPobMundial=0;
    Pais poblacionMundial;
    archivo = fopen(ARCHIVO_PAISES,"rb");
    while(fread(&poblacionMundial, sizeof(Pais),1,archivo)==1)
    {
        totalPobMundial+=poblacionMundial._poblacion;
    }
    fclose(archivo);
    return totalPobMundial;
}


bool SalirDeFuncion()
{
    bool salir;
    int opc;
    cout << endl;
    cout << "1- Continuar en la funcion" << endl;
    cout << "0- Volver al menu principal" << endl;
    cin >> opc;
    cin.ignore();
    switch (opc)
    {
    case 1:
        return salir = false;
        break;
    case 0:
        return salir = true;
        break;
    }
}

void menuModificacionPais()
{
    cout << "1-Modificar nombre del pais" << endl;
    cout << "2-Modificar continente del pais" << endl;
    cout << "3-Modificar poblacion del pais" << endl;
    cout << "4-Modificar Expectativa de vida del pais" << endl;
}

struct Ciudad obtenerRegistroCiudad(int ciudad)
{
    Ciudad buscar;
    FILE* archivo;
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    while(fread(&buscar,sizeof(Ciudad),1,archivo)==1)
    {
        if(buscar._ID==ciudad)
        {
            return buscar;
        }
    }
}

int exportarAexcel()
{
    //setlocale(LC_ALL, ""); // mostrar caracteres en español
    crearExcel();
    cout << "" << endl;
    cout << "El Libro se ha creado con Exito!" << endl;
    system("pause");
    return 0;
}


void crearExcel()
{
    //setlocale(LC_ALL, ""); // mostrar caracteres en español

    /// Crea un objeto 'Book' que representa un libro de Excel
    Book* book = xlCreateBook(); // xlCreateXMLBook() para formato xlsx

    if (book)   /// Verifica si se creó correctamente el Libro
    {
        /// Crea una hoja en el libro de Excel con el nombre "Sheet1"
        Sheet* hoja1 = book->addSheet("PAISES");
        Sheet* hoja2 = book->addSheet("CIUDADES");
//        Sheet* hoja3 = book->addSheet("Colores y Alineación");

        if (hoja1) // Verifica si se creó correctamente la hoja
        {
            //setlocale(LC_ALL, ""); // mostrar caracteres en español
            /// FILA,COLUMNA, DATO
            /// Escribe una cadena en la celda (1, 1) de la hoja
            hoja1->writeStr(1, 1, "Codigo");    /// writeStr: Para Cadenas
            hoja1->writeStr(1, 2, "Codigo2");   /// Escribe una cadena en la celda (1, 2) de la hoja
            hoja1->writeStr(1, 3, "Nombre");    /// Escribe una cadena en la celda (1, 3) de la hoja
            hoja1->writeStr(1, 4, "Continente");
            hoja1->writeStr(1, 5, "Superficie");
            hoja1->writeStr(1, 6, "Poblacion");
            hoja1->writeStr(1, 7, "Independencia");
            hoja1->writeStr(1, 8, "Expectativa de vida");
            hoja1->writeStr(1, 9, "Capital");

            int i=2;
            FILE* archivo;
            Pais Datos;
            archivo = fopen(ARCHIVO_PAISES,"rb");
            while(fread(&Datos,sizeof(Pais),1,archivo)==1)
            {
                hoja1->writeStr(i, 1, Datos._codigo);  /// writeStr: Para Cadenas
                hoja1->writeStr(i, 2, Datos._codigo2);
                hoja1->writeStr(i, 3, Datos._nombre);
                hoja1->writeStr(i, 4, Datos._continente);
                hoja1->writeNum(i, 5, Datos._superficie);
                hoja1->writeNum(i, 6, Datos._poblacion);
                hoja1->writeNum(i, 7, Datos._independencia);
                hoja1->writeNum(i, 8, Datos._expectativaDeVida);
                hoja1->writeNum(i, 9, Datos._capital);
                i++;
            }
            fclose(archivo);
        }
        if(hoja2)
        {
            cargarHoja2(hoja2, book);
        }


/// Guarda el libro de Excel con el nombre "Datos_paises_y_ciudades.xls"
        book->save("Datos_paises_y_ciudades.xls");

        /// Libera los recursos asociados al objeto 'Book'
        book->release();
    }
}
void cargarHoja2(Sheet *hoja2, Book *libro)
{

    //setlocale(LC_ALL, ""); // mostrar caracteres en español
    hoja2->writeStr(1, 1, "Codigo");    /// writeStr: Para Cadenas
    hoja2->writeStr(1, 2, "Nombre");   /// Escribe una cadena en la celda (1, 2) de la hoja
    hoja2->writeStr(1, 3, "ID Pais");    /// Escribe una cadena en la celda (1, 3) de la hoja
    hoja2->writeStr(1, 4, "Poblacion");


    int i=2;
    FILE* archivo;
    Ciudad Datos;
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    while(fread(&Datos,sizeof(Ciudad),1,archivo)==1)
    {
        //setlocale(LC_ALL, ""); // mostrar caracteres en español
        hoja2->writeNum(i, 1, Datos._ID);  /// writeStr: Para Cadenas
        hoja2->writeStr(i, 2, Datos._nombre);
        hoja2->writeStr(i, 3, Datos._idpais);
        hoja2->writeNum(i, 4, Datos._poblacion);
        i++;
    }
    fclose(archivo);
}


#endif // FUNCIONES_H_INCLUDED
