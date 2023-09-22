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
/// 1) --------------------------------------------------------------
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
void totalesxContinente();          // Leo el archivo Paises. Dentro de la función se debe pedir al Usuario que ingrese el nombre del Pais.
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

int contarPoblacionMundial();

/// PUNTOS 11 y 12 (OPCIONALES)
/// COLOCAR AQUÍ LOS PROTOTIPOS DE LAS FUNCIONES

bool SalirDeFuncion();

/// --------------------------- DESARROLLO DE LAS FUNCIONES ---------------------------

/// 1) --------------------------------------------------------------
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
    ///apertura
    archivo = fopen(ARCHIVO_PAISES,"ab");
    ///carga de registros
    fwrite(&reg,sizeof(Pais),1,archivo);
    ///cierro el archivo
    fclose(archivo);
}

// 3) --------------------------------------------------------------
void leerPaises()
{
    setlocale(LC_ALL, ""); // mostrar caracteres en español
    // abro el archivo en modo lectura
    FILE *archivo;

    Pais leer;// variable tipo struct Pais donde guardo el contenido a mostrar
    //apertura del archivo "MODO: Lectura"
    archivo = fopen(ARCHIVO_PAISES,"rb");
    // leo el archivo
    while(fread(&leer, sizeof(Pais),1,archivo)==1)
    {
        mostrarPais(leer);
        system ("pause");
    }
    // cierro archivo
    fclose(archivo);
}

void mostrarPais(Pais mostrar)
{
    cout << "   Codigo de Pais:\t "<<mostrar._codigo<<endl;
    cout << "   Codigo 2:\t "<<mostrar._codigo2<<endl;
    cout << "   Nombre:\t "<<mostrar._nombre<<endl;
    cout << "   Continente:\t "<<mostrar._continente<<endl;
    cout << "   Superficie:\t "<<mostrar._superficie<< " Km cuadrados"<<endl;
    cout << "   Poblacion:\t "<<mostrar._poblacion<<" habitantes"<<endl;
    cout << "   Año de Independencia:\t "<<mostrar._independencia<<endl;
    cout << "   Expectativa de vida:\t "<<mostrar._expectativaDeVida<<" años"<<endl;
    cout << "   Capital:\t "<<mostrar._capital<<endl;
    cout <<endl;
}

// 4) --------------------------------------------------------------
void mostrarCiudadesxPais()
{
    FILE* archivo;
    Ciudad leer;
    Pais retorno;
    char codigo[4];
    cin.ignore();
    archivo = fopen(ARCHIVO_CIUDADES,"rb");
    bool salir=false;
    while(salir==false)
    {
        cin.getline(codigo,4);
        clrscr();
        if (existeRegistro(codigo)==true)
        {
            retorno = obtenerRegistroPais(codigo);
            while(fread(&leer,sizeof(Ciudad),1,archivo)==1)
            {
                if (strcmp(leer._idpais,retorno._codigo)==0)
                {
                    cout << leer._ID << endl;
                    cout << leer._nombre << endl;
                    cout << leer._idpais << endl;
                    cout << leer._poblacion << endl;
                    cout << "------------------------------" << endl;
                }
            }
            salir = SalirDeFuncion();
        }
        else
        {
            cout << "ERROR: Codigo Inexistente" << endl;
        }

    }
}

struct Pais obtenerRegistroPais(char *pais)
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

void listarPaises_Superficies()
{
    const int tam = contarPaises();
    float porc=0,sumaSuperficies=0;
    Pais sumar, leer[tam];
    FILE* archivo;
    //abro archivo
    archivo=fopen(ARCHIVO_PAISES,"rb");
    if (archivo==NULL)
    {
        cout << "Error: Archivo no existente" << endl;
    }
    fread(leer,sizeof(Pais),tam,archivo);
    //leo el archivo
    while(fread(&sumar,sizeof(Pais),1,archivo)==1)
    {
        //sumo para obtener la superficie mundial
        sumaSuperficies =+ sumar._superficie;

    }
    for (int x=0; x<tam; x++)
    {
        porc = ((leer[x]._superficie*100)/sumaSuperficies);
        cout << "La superficie de " << leer[x]._nombre << "\trepresenta el : " << porc << endl;
        cout << "------------------------------------------------------------------------" << endl;
    }
    fclose(archivo);
    system("pause");
}


// 9) --------------------------------------------------------------

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

/// ADICIONALES IMPORTANTES
int contarPaises()
{
    // abro el archivo en modo lectura
    FILE *archivo;
    int totalPaises=0;
    Pais contarP;
    //Pais contarPais;// variable tipo struct Pais donde guardo el contenido a mostrar
    archivo = fopen(ARCHIVO_PAISES,"rb");
    // leo el archivo
    while(fread(&contarP, sizeof(Pais),1,archivo)==1)
    {
        totalPaises++;
    }
    // cierro archivo
    fclose(archivo);

    return totalPaises;
}

/// ADICIONALES IMPORTANTES
int contarPoblacionMundial()
{
    FILE *archivo;
    int totalPobMundial=0;
    Pais poblacionMundial;
    archivo = fopen(ARCHIVO_PAISES,"rb");
    while(fread(&poblacionMundial, sizeof(Pais),1,archivo)==1)
    {
        totalPobMundial+=poblacionMundial._poblacion;
    }
    fclose(archivo);
    return totalPobMundial;
}

/// ADICIONALES IMPORTANTES
void totalesPais_Poblacion()
{
    //setlocale(LC_ALL, ""); // mostrar caracteres en español

    cout<<""<<endl;
    cout<<" El total de piíses es: "<<contarPaises()<<endl;
    cout<<""<<endl;
    cout<<" El total de la poblacion mundial es: "<<contarPoblacionMundial()<<endl;
    cout<<""<<endl;
    system ("pause");
}
bool SalirDeFuncion()
{
    bool salir;
    int opc;
    cout << endl;
    cout << "1- Continuar en la funcion" << endl;
    cout << "0- Volver al menu principal" << endl;
    cin >> opc;
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
