#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/// Colocar las Librerías que se utilizarán
//hola
#include "Structs.h" /// Librería con los Structs y constantes de los Archivos
#include "string.h"
#include <cstdio>
#include <iostream>
#include <locale.h> /// Libreria que contiene la funcion setlocale

using namespace std;

/// --------------------------- PROTOTIPOS DE LAS FUNCIONES ---------------------------
// 1) --------------------------------------------------------------
bool existeRegistro(char *codigo);  // Verifico si existe Registro.

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
void grabarModificado(Pais reg);    // Guardar Pais Modificado.

// 8) --------------------------------------------------------------
void modificarCiudad();             // Pido el codigo de la ciudad a modificar.
bool existeRegistro(int id);        // Verifico si existe Registro. (SOBRECARGA DE FUNCIONES)
// Ingreso codigo pais y verifico si existe
void grabarModificado(Ciudad reg);  // Guardar Ciudad Modificada. (SOBRECARGA DE FUNCIONES)

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

bool SalirDeFuncion();

/// --------------------------- DESARROLLO DE LAS FUNCIONES ---------------------------

// 1) --------------------------------------------------------------
//  Agregar una función global que busque un registro de país a partir de su código.
//  La función debe poder devolver si el registro existe o no.

bool existeRegistro(char *codigo)  // Verifico si existe Registro.
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
        if (existeRegistro(codigo)==false)
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
    while(fread(&leer, sizeof(Pais),1,archivo)==1)
    {
        mostrarPais(leer);

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
        if (existeRegistro(codigo)==true) //valido el codigo ingresado
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
    cout << "La superficie mundial es "<< sumaSuperficies<<endl;
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

        if (existeRegistro(codigo)==true) //valido el codigo ingresado
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
///void modificarPais()               // Pido el codigo de pais a modificar.
// Verificar que exista.
// Buscar registro (usar función respectiva).
// Ingresar los nuevos valores y reemplazar.
///void grabarModificado(Pais reg)    // Guardar Pais Modificado.

// 8) --------------------------------------------------------------
///void modificarCiudad()             // Pido el codigo de la ciudad a modificar.
//bool existeRegistro(int id)        // Verifico si existe Registro. (SOBRECARGA DE FUNCIONES)
// Ingreso codigo pais y verifico si existe
///void grabarModificado(Ciudad reg)  // Guardar Ciudad Modificada. (SOBRECARGA DE FUNCIONES)


// 9) --------------------------------------------------------------
// Agregar una función global que nos muestre la cantidad de Países existentes
// y el total de la poblacion mundial.

void totalesPais_Poblacion()
{
    //setlocale(LC_ALL, ""); // mostrar caracteres en español

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

#endif // FUNCIONES_H_INCLUDED
