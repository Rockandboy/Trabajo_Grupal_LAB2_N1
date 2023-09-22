struct Pais{
    char _codigo[4];
    char _codigo2[3];
    char _nombre[45];
    char _continente[20];
    float _superficie;
    //long _superficie;
    int _poblacion;
    short _independencia;
    float _expectativaDeVida;
    int _capital;
};

struct Ciudad
{
    int _ID;
    char _nombre[35];
    char _idpais[4];
    int _poblacion;
};

/// ARCHIVOS
const char *ARCHIVO_PAISES = "paises.dat";
const char *ARCHIVO_CIUDADES = "ciudades.dat";
