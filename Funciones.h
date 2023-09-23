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
    // abro el archivo en modo lectura
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
    cout << "   Capital:\t "<<mostrar._capital<<endl;
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
        cout <<" \nIngrese el codigo de pais, por ejemplo ARG" << endl;
        cin.getline(codigo,4);
        clrscr();
        if (existeRegistro(codigo)==true) //fvalido el codigo ingresado
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

void listarPaises_Superficies()
{
    const int tam = contarPaises();
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

void totalesxContinente()// Leo el archivo Paises. Dentro de la función se debe pedir al Usuario que
//ingrese el nombre del Pais. Guardo en un vector los registros.
// Luego calculo los totales y promedios.
{
    FILE *archivo;
    const int tam = contarPaises();
    double sumaSuperficieContinente=0;
//    else
//    {
//    fread(leer,sizeof(Pais),tam,archivo); //leo el archivo
//    for (int i=0; i<tam; i++)
//    {
//        //sumo para obtener la superficie mundial
//        sumaSuperficieContinente += leer[i]._superficie;
//
//    }
//    for (int x=0; x<tam; x++)
//    {
//        porc = (leer[x]._superficie/sumaSuperficies)*100;
//        cout << "PAIS:          " << leer[x]._nombre <<endl;
//        cout << "Superficie:    " << leer[x]._superficie << " Km cuadrados" <<endl;
//        cout << "Representa el: " << porc <<" % de la superficie mundial." << endl;
//        cout << "------------------------------------------------------------------------" << endl;
//    }
//    cout << "La superficie mundial es "<< sumaSuperficies<<endl;
//    fclose(archivo);
//    system("pause");





//    }
//    system ("pause");
//    // cierro archivo
//    fclose(archivo);
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
