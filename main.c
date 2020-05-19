#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

//hacer que se pueda seleccionar y cargar un archivo de entrada de formato TXT
//hacer que se pueda por medio de expresiones regulares la clasificación de los numeros de CR
//Guardar esos numeros clasificados en listas
//finalmente mostrar la clasificación final al usuario
/*
2xxx-xxxx = ICE Telefono Fijo --> 0
8xxx-xxxx = Kolbi --> 1
7xxx-xxxx = Movistar --> 2
6xxx-xxxx = Claro -->3
*/

//[+]506-[2]\d{3}-\d{4} sirve para estos casos +506-2550-2558

//(([+]{1}[5]{1}[0]{1}[6]{1})( )([2]{1}[0-9]{7})) Pruebas

/*
//TELEFONOS FIJOS ICE
 (([+]{1}[5][0][6])( )([2]{1}\d{7}))/g sirve para estos casos +506 25502558
 [+]{1}506\s[2]{1}\d{3}\s\d{4} sirve para estos casos +506 2550 2558
 [+]{1}506\s[2]{1}\d{3}-\d{4} sirve para estos casos +506 2550-2558

 [2]\d{3}\d{4} sirve para estos casos 25502558
 [2]\d{3}\s\d{4} sirve para estos casos 2550 2558
 [2]\d{3}-\d{4} sirve para estos casos 2550-2311
*/
//KOLBI
// [+]506\s[8]\d{3}\d{4} sirve para estos casos +506 84565243
// [+]506\s[8]\d{3}\s\d{4} sirve para estos casos +506 8456 5243
// [+]506\s[8]\d{3}-\d{4} sirve para estos casos +506 8456-5243

// [8]\d{3}\d{4} sirve para estos casos 84565243
// [8]\d{3}\s\d{4} sirve para estos casos 8456 5243
// [8]\d{3}-\d{4} sirve para estos casos 8456-5243

//MOVISTAR
// [+]506\s[7]\d{3}\d{4} sirve para estos casos +506 74565243
// [+]506\s[7]\d{3}\s\d{4} sirve para estos casos +506 7456 5243
// [+]506\s[7]\d{3}-\d{4} sirve para estos casos +506 7456-5243

// [7]\d{3}\d{4} sirve para estos casos 74565243
// [7]\d{3}\s\d{4} sirve para estos casos 7456 5243
// [7]\d{3}-\d{4} sirve para estos casos 7456-5243

/*CLARO
 [+]506\s[6]\d{3}\d{4} sirve para estos casos +506 64565243
 [+]506\s[6]\d{3}\s\d{4} sirve para estos casos +506 6456 5243
 [+]506\s[6]\d{3}-\d{4} sirve para estos casos +506 6456-5243

 [6]\d{3}\d{4} sirve para estos casos 64565243
 [6]\d{3}\s\d{4} sirve para estos casos 6556 5243
 [6]\d{3}-\d{4} sirve para estos casos 6456-5243
*/

typedef enum { ICEFijo, Kolbi, Movistar, Claro } Tipo;

struct telefonos{
    char *numero;
};

struct expresiones{
    char *string;
};

struct nodoListaExpresiones{
    void* expresion;
    struct nodoListaExpresiones *sig;
} *cabezaExpresiones = NULL;
/*
struct nodoLista_ICE_FIJO{
  void* telefonos;
  Tipo tipo;
  struct nodoLista_ICE_FIJO *sig;
} *cabezaICE = NULL;

struct nodoLista_Kolbi{
    void* telefonos;
    Tipo tipo;
    struct nodoLista_Kolbi *sig;
} *cabezaKolbi;

struct nodoLista_Movistar{
    void* telefonos;
    Tipo tipo;
    struct nodoLista_Movistar *sig;
} *cabezaMovistar;

struct nodoLista_Claro{
    void* telefonos;
    Tipo tipo;
    struct nodoLista_Claro *sig;
} *cabezaClaro;

void* nuevoNumero (char* num){
    struct telefonos* elTelefono;
    elTelefono = (struct telefonos*) malloc(sizeof(struct telefonos));
    elTelefono->numero = num;

    return elTelefono;
}

void insertarTelefonoICEFijo(void* nuevoTelefono, Tipo tipo){
    struct nodoLista_ICE_FIJO* nn = NULL;
    nn = (struct nodoLista_ICE_FIJO*) malloc(sizeof(struct nodoLista_ICE_FIJO));

    nn->telefonos=nuevoTelefono;
    nn->tipo = tipo;
    nn->sig=NULL;

    if (cabezaICE == NULL)
        cabezaICE = nn;
    else{
        nn->sig = cabezaICE;
        cabezaICE = nn;
    }
}

void insertarTelefonoKolbi(void* nuevoTelefono, Tipo tipo){
    struct nodoLista_Kolbi* nn = NULL;
    nn = (struct nodoLista_Kolbi*) malloc(sizeof(struct nodoLista_Kolbi));

    nn->telefonos=nuevoTelefono;
    nn->tipo = tipo;
    nn->sig=NULL;

    if (cabezaKolbi == NULL)
        cabezaKolbi = nn;
    else{
        nn->sig = cabezaKolbi;
        cabezaKolbi = nn;
    }
}

void insertarTelefonoMovistar(void* nuevoTelefono, Tipo tipo){
    struct nodoLista_Movistar* nn = NULL;
    nn = (struct nodoLista_Movistar*) malloc(sizeof(struct nodoLista_Movistar));

    nn->telefonos=nuevoTelefono;
    nn->tipo = tipo;
    nn->sig=NULL;

    if (cabezaMovistar == NULL)
        cabezaMovistar = nn;
    else{
        nn->sig = cabezaMovistar;
        cabezaMovistar = nn;
    }
}

void insertarTelefonoClaro(void* nuevoTelefono, Tipo tipo){
    struct nodoLista_Claro* nn = NULL;
    nn = (struct nodoLista_Claro*) malloc(sizeof(struct nodoLista_Claro));

    nn->telefonos=nuevoTelefono;
    nn->tipo = tipo;
    nn->sig=NULL;

    if (cabezaClaro == NULL)
        cabezaClaro = nn;
    else{
        nn->sig = cabezaClaro;
        cabezaClaro = nn;
    }
}

void imprimirTelefono(){
    struct nodoLista_ICE_FIJO* act = cabezaICE;
    printf("********* Lista de Telefonos Costa Rica por Operador *********\n");
    if (act == NULL)
        printf("Lista Vacia");
    else
        while(act!=NULL){
            if (act->tipo==0){
                printf("Numero: %s, Tipo: ICE Fijo \n",
                       ((struct telefonos*)act->telefonos)->numero);
            }
            else if(act->tipo==1){
                printf("Numero: %s, Tipo: Kolbi \n",
                       ((struct telefonos*)act->telefonos)->numero);
            }
            else if (act->tipo == 2){
                printf("Numero: %s, Tipo: Movistar \n",
                       ((struct telefonos*)act->telefonos)->numero);
            }
            else if (act->tipo == 3){
                printf("Numero: %s, Tipo: Claro \n",
                       ((struct telefonos*)act->telefonos)->numero);
            }
            act = act->sig;
        }
}
*/
void validarNumero2(char* texto){
    struct nodoListaExpresiones* aux = cabezaExpresiones;
    if(aux == NULL){
        printf("La lista esta vacia");
    }
    else{
        printf("********* Lista de Telefonos Costa Rica por Operador ********* \n");
        int cont = 0;
        char *grp = NULL;
        while (aux != NULL){
            if (cont == 0){
                grp = "ICEFijo";
                /*insertarTelefonoICEFijo(nuevoNumero(cursorCopy + groupArray[g].rm_so), ICEFijo);*/
            }
            else if (cont == 1){
                grp = "Kolbi";
                /*insertarTelefonoICEFijo(nuevoNumero(cursorCopy + groupArray[g].rm_so), Kolbi);
                //insertarTelefonoKolbi(nuevoNumero(cursorCopy + groupArray[g].rm_so), Kolbi);*/
            }
            else if (cont == 2){
                grp = "Movistar";
                /*insertarTelefonoICEFijo(nuevoNumero(cursorCopy + groupArray[g].rm_so), Movistar);
                //insertarTelefonoMovistar(nuevoNumero(cursorCopy + groupArray[g].rm_so), Movistar);*/
            }
            else if(cont == 3){
                grp = "Claro";
                /*insertarTelefonoICEFijo(nuevoNumero(cursorCopy + groupArray[g].rm_so), Claro);
                //insertarTelefonoClaro(nuevoNumero(cursorCopy + groupArray[g].rm_so), Claro);*/
            }

            char * source = texto;
            char *regexString = ((struct expresiones*)aux->expresion)->string;
            size_t maxMatches = 5;
            size_t maxGroups = 1;

            regex_t regexCompiled;
            regmatch_t groupArray[maxGroups];
            unsigned int m;
            char * cursor;

            if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
            {
                printf("Could not compile regular expression.\n");
                return;
            }

            cursor = source;
            for (m = 0; m < maxMatches; m ++)
            {
                if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
                    break;  // No more matches

                unsigned int g = 0;
                unsigned int offset = 0;
                for (g = 0; g < maxGroups; g++)
                {
                    if (groupArray[g].rm_so == (size_t)-1)
                        break;  // No more groups

                    if (g == 0)
                        offset = groupArray[g].rm_eo;

                    char cursorCopy[strlen(cursor) + 1];
                    strcpy(cursorCopy, cursor);
                    cursorCopy[groupArray[g].rm_eo] = 0;
                    printf("Operador: %s, Numero: %s \n", grp, cursorCopy + groupArray[g].rm_so);
                }
                cursor += offset;
            }
            cont += 1;
            aux=aux->sig;
            regfree(&regexCompiled);
        }
    }
}
/*
void validarNumero(char* texto) {

    struct nodoListaExpresiones* aux = cabezaExpresiones;
    //printf("Expresion: %s \n",aux->expresion.string);
    if(aux == NULL){
        printf("La lista esta vacia");
    }
    else{
        int cont = 0;
        char *grp = NULL;
        while (aux != NULL){
            if (cont == 0){
                grp = "ICE Fijo";
            }
            else if (cont == 1){
                grp = "Kolbi";
            }
            else if (cont == 2){
                grp = "Movistar";
            }
            else if(cont == 3){
                grp = "Claro";
            }

            char *regexString = ((struct expresiones*)aux->expresion)->string;
            regex_t regexCompiled;
            regmatch_t groupArray[24];
            char * cursor = texto;

            if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
            {
                printf("Could not compile regular expression.\n");
                return;
            }

            if (regexec(&regexCompiled, cursor, 24, groupArray, 0)){
                printf("%s no tiene parejas para este formato de expresion \n", grp);

                regfree(&regexCompiled);

                cont += 1;
                aux = aux->sig;
                //break;  // No more matches
            }else{

                unsigned int g = 0;
                char cursorCopy[strlen(cursor) + 1];
                strcpy(cursorCopy, cursor);
                cursorCopy[groupArray[g].rm_eo] = 0;

                //aqui ya se el numero //rm_so es el inicio  y rm_eo es el final
                printf( "Group %s: %s\n", grp, cursorCopy + groupArray[g].rm_so);
                //if(){}
                regfree(&regexCompiled);

                cont += 1;
                aux=aux->sig;
            }
        }
    }
}*/
//C:/Users/Emmanuel/Desktop/01. Proyecto C/archivo.txt
char *cargarArchivoTXT(const char *const filename)
{
    size_t size;
    FILE  *file;
    char  *data;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("fopen()\n");
        return NULL;
    }

    // obtener el tamaño del archivo buscando el final y consigo la posicion
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    // resetear la posicion al principio.
    rewind(file);
    // conseguir memoria para la informacion
    data = malloc(1 + size);
    if (data == NULL) {
        perror("malloc()\n");
        fclose(file);
        return NULL;
    }

    // termina el contenido para volverlo un string valido
    data[size] = '\0';
    // intento de leer toda la info del txt
    fread(data, 1, size, file);

    fclose(file);
    return data;
}

void insertarExpresionRegular(void* nuevaExpresion){
    struct nodoListaExpresiones* nn = NULL;
    nn = (struct nodoListaExpresiones*) malloc(sizeof(struct nodoListaExpresiones));

    nn->expresion=nuevaExpresion;
    nn->sig=NULL;

    if (cabezaExpresiones == NULL)
        cabezaExpresiones=nn;
    else{
        nn->sig = cabezaExpresiones;
        cabezaExpresiones = nn;
    }
}
//crear expresiones regulares nuevas
void* nuevaExpreRegu (char *string){
    struct expresiones* laExpresion;
    laExpresion = (struct expresiones*) malloc(sizeof(struct expresiones));
    laExpresion->string = string;
    return laExpresion;
}

//Lectua de archivos
void lectura(char *cadena){
    //cargar archivo para sacar los numeros
    char *content;
    content = cargarArchivoTXT(cadena);
    if (content != NULL)
    {
        printf("%s\n", content);
        validarNumero2(content);
        free(content);
    }
}

void inicioPr(){
    //Leer lo que el usuario coloca en la consola (la direccion del archivo)
    char *cadena = NULL;
    cadena = (char *) malloc(1);
    printf ("Introduzca la ubicacion del archivo: ");
    scanf("%[^\n]", cadena);
    lectura(cadena);
}

int main() {
    //Expresiones quemadas para busqueda de numeros
    //Claro
    //insertarExpresionRegular(nuevaExpreRegu("[+]?[5]?[0]?[6]?[ ]?[-]?(([6]{1}[0-9]{1})[ ]?[-]?([0-9]{2})[ ]?[-]?([0-9]{2}))([ ]?[-]?)([0-9]{2})"));
    //Movistar
    insertarExpresionRegular(nuevaExpreRegu("[+]?[5]?[0]?[6]?[ ]?[-]?(([7]{1}[0-9]{1})[ ]?[-]?([0-9]{2})[ ]?[-]?([0-9]{2}))([ ]?[-]?)([0-9]{2})"));
    //Kolbi
    insertarExpresionRegular(nuevaExpreRegu("[+]?[5]?[0]?[6]?[ ]?[-]?(([8]{1}[0-9]{1})[ ]?[-]?([0-9]{2})[ ]?[-]?([0-9]{2}))([ ]?[-]?)([0-9]{2})"));
    //ICE FIJO
    insertarExpresionRegular(nuevaExpreRegu("[+]?[5]?[0]?[6]?[ ]?[-]?(([2]{1}[0-9]{1})[ ]?[-]?([0-9]{2})[ ]?[-]?([0-9]{2}))([ ]?[-]?)([0-9]{2})"));

    inicioPr();

    return 0;
}