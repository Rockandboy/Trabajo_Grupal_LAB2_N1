#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <windows.h>
#include <iostream>
#include "graficos.h"
#include "Funciones.h"

using namespace std;

void menuPaises();
void menuCiudades();
void menuReportes();
void menuConfig();

int MenuPrincipal()
{
    int opc;

    while(true)
    {
        clrscr();
        system("COLOR 0F");
        recuadro(2,1,40,15,cAZUL,cGRIS_CLARO);
        gotoxy(3,2);
        cout << "---------------------------------------" << endl;
        gotoxy(12,3);
        cout << "-  MENU PRINCIPAL  -" << endl;
        gotoxy(3,4);
        cout << "---------------------------------------" << endl;
        gotoxy(13,5);
        cout << "   1 - PAISES" << endl;
        gotoxy(13,6);
        cout << "   2 - CIUDADES" << endl;
        gotoxy(13,7);
        cout << "   3 - REPORTES" << endl;
        gotoxy(13,8);
        cout << "   4 - CONFIGURACIONES" << endl;
        gotoxy(3,9);
        cout << "---------------------------------------" << endl;
        gotoxy(13,10);
        cout << "   0 - SALIR" << endl;
        cout << endl;
        gotoxy(3,12);
        cout << "OPCION: ";
        cin >> opc;

        switch(opc)
        {
        case 1:
            clrscr();
            menuPaises();
            break;
        case 2:
            clrscr();
            menuCiudades();
            break;
        case 3:
            clrscr();
            menuReportes();
            break;
        case 4:
            clrscr();
            menuConfig();
            break;
        case 0:
            cout << endl << endl;
            return 0;
            break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Cambia el color de texto a blanco (12) y el fondo a rojo (4) antes de imprimir el texto.
            int color = 7 | (12 << 4);
            SetConsoleTextAttribute(hConsole, color);
            gotoxy(13,13);
            cout << "OPCION INCORRECTA" << endl;
            pause();
            recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
            break;
        }
    }
}

void menuPaises()
{
    int opc;

    while(true)
    {
        clrscr();
        system("COLOR 0F");
        recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
        gotoxy(3,2);
        cout << "---------------------------------------" << endl;
        gotoxy(12,3);
        cout << "-  MENU PAISES  -" << endl;
        gotoxy(3,4);
        cout << "---------------------------------------" << endl;
        gotoxy(6,5);
        cout << "   1 - Agregar Pais" << endl;
        gotoxy(6,6);
        cout << "   2 - Listar Paises" << endl;
        gotoxy(6,7);
        cout << "   3 - Listar Paises x Superficie" << endl;
        gotoxy(6,8);
        cout << "   4 - Modificar Pais" << endl;
        gotoxy(3,9);
        cout << "---------------------------------------" << endl;
        gotoxy(13,10);
        cout << "   0 - REGRESAR" << endl;
        cout << endl;
        gotoxy(3,12);
        cout << "OPCION: ";
        cin >> opc;

        switch(opc)
        {
        case 1:
            clrscr();
            cargarPais();
            break;
        case 2:
            clrscr();
            leerPaises();
            break;
        case 3:
            clrscr();
            listarPaises_Superficies();
            break;
        case 4:
            clrscr();
            modificarPais();
            break;
        case 0:
            cout << endl << endl;
            return;
            break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Cambia el color de texto a blanco (12) y el fondo a rojo (4) antes de imprimir el texto.
            int color = 7 | (12 << 4);
            SetConsoleTextAttribute(hConsole, color);
            gotoxy(13,13);
            cout << "OPCION INCORRECTA" << endl;
            pause();
            recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
            break;
        }
    }
}

void menuCiudades()
{
    int opc;

    while(true)
    {
        clrscr();
        system("COLOR 0F");
        recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
        gotoxy(3,2);
        cout << "---------------------------------------" << endl;
        gotoxy(12,3);
        cout << "-  MENU CIUDADES  -" << endl;
        gotoxy(3,4);
        cout << "---------------------------------------" << endl;
        gotoxy(6,5);
        cout << "   1 - Listar Ciudades x Pais" << endl;
        gotoxy(6,6);
        cout << "   2 - Modificar Codigo Pais" << endl;
        gotoxy(3,7);
        cout << "---------------------------------------" << endl;
        gotoxy(13,9);
        cout << "   0 - REGRESAR" << endl;
        cout << endl;
        gotoxy(3,12);
        cout << "OPCION: ";
        cin >> opc;

        switch(opc)
        {
        case 1:
            clrscr();
            //contarCiudades();
            mostrarCiudadesxPais();
            break;
        case 2:
            clrscr();
            modificarCiudad();
            break;
        case 0:
            cout << endl << endl;
            return;
            break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Cambia el color de texto a blanco (12) y el fondo a rojo (4) antes de imprimir el texto.
            int color = 7 | (12 << 4);
            SetConsoleTextAttribute(hConsole, color);
            gotoxy(13,13);
            cout << "OPCION INCORRECTA" << endl;
            pause();
            recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
            break;
        }
    }
}

void menuReportes()
{
    int opc;

    while(true)
    {
        clrscr();
        system("COLOR 0F");
        recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
        gotoxy(3,2);
        cout << "---------------------------------------" << endl;
        gotoxy(12,3);
        cout << "-  MENU REPORTES  -" << endl;
        gotoxy(3,4);
        cout << "---------------------------------------" << endl;
        gotoxy(5,5);
        cout << "   1 - Estadisticas x Continente" << endl;
        gotoxy(5,6);
        cout << "   2 - Total de Paises" << endl;
        gotoxy(5,7);
        cout << "   3 - Ciudad con Mayor Poblacion" << endl;
        gotoxy(3,8);
        cout << "---------------------------------------" << endl;
        gotoxy(13,9);
        cout << "   0 - REGRESAR" << endl;
        cout << endl;
        gotoxy(3,12);
        cout << "OPCION: ";
        cin >> opc;

        switch(opc)
        {
        case 1:
            clrscr();
            totalesxContinente();
            break;
        case 2:
            clrscr();
            totalesPais_Poblacion();
            break;
        case 3:
            clrscr();
            buscarMayorPoblacion();
            break;
        case 0:
            cout << endl << endl;
            return;
            break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Cambia el color de texto a blanco (12) y el fondo a rojo (4) antes de imprimir el texto.
            int color = 7 | (12 << 4);
            SetConsoleTextAttribute(hConsole, color);
            gotoxy(13,13);
            cout << "OPCION INCORRECTA" << endl;
            pause();
            recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
            break;
        }
    }
}

void menuConfig()
{
    int opc;

    while(true)
    {
        clrscr();
        system("COLOR 0F");
        recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
        gotoxy(3,2);
        cout << "---------------------------------------" << endl;
        gotoxy(12,3);
        cout << "-  MENU CONFIGURACIONES  -" << endl;
        gotoxy(3,4);
        cout << "---------------------------------------" << endl;
        gotoxy(5,5);
        cout << "   1 - Realizar Backup" << endl;
        gotoxy(5,6);
        cout << "   2 - Restaurar archivos" << endl;
        gotoxy(5,7);
        cout << "   3 - Exportar a Excel" << endl;
        gotoxy(3,8);
        cout << "---------------------------------------" << endl;
        gotoxy(13,9);
        cout << "   0 - REGRESAR" << endl;
        cout << endl;
        gotoxy(3,12);
        cout << "OPCION: ";
        cin >> opc;

        switch(opc)
        {
        case 1:
            clrscr();
            //backupArchivo();
            break;
        case 2:
            clrscr();
            //restaurarArchivo();
            break;
        case 3:
            clrscr();
            exportarAexcel();
            break;
        case 0:
            cout << endl << endl;
            return;
            break;
        default:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Cambia el color de texto a blanco (12) y el fondo a rojo (4) antes de imprimir el texto.
            int color = 7 | (12 << 4);
            SetConsoleTextAttribute(hConsole, color);
            gotoxy(13,13);
            cout << "OPCION INCORRECTA" << endl;
            pause();
            recuadro(2,1,40,13,cAZUL,cGRIS_CLARO);
            break;
        }
    }
}


#endif // MENU_H_INCLUDED
