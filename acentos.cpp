#include <iostream>
#include <cstdlib> // contiene la funcion system("pause")
#include <locale.h> // Libreria que contiene la funcion setlocale

using namespace std;

int main(){

    setlocale(LC_ALL, ""); // Uso de la funcion setlocale (abajo se explica)


    cout << "Hola, cómo están?" << endl; // Imprimimos por pantalla cualquier caracter hispano

    char letraA = 'á';

    cout << letraA << endl;

    char letraN = 'Ñ';

    cout << letraN << endl;

    system("pause");

}
