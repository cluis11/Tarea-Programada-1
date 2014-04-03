#include <stdio.h> //es la biblioteca estándar en C
#include <string.h> //incluye una libreria para manejo de strings
#include <stdlib.h>//archivo de cabecera de la biblioteca estándar
#include <strings.h>//libreria que incluye funciones para el manejo de strings
#include <sys/socket.h>//libreria principal para el manejo de sockets 
#include <unistd.h>//es el header file que provee acceso al API POSIX de los sistemas operativos Linux/Unix.
#include <sys/types.h>//manejo del tipo de datos
#include <netinet/in.h>//libreria para el manejo de IPs entre otras funciones
#include <netdb.h>//definiciones para el manejo de operaciones en informacion de la red
#define ARCHIVO "fichero.txt"
#define rayas printf("---------------------------------------------------------\n");//macro que incluye un conjunto de lineas para separar los textos

extern sockets (char* IP, char* Porto);
extern int lee_msj(int accept);
extern int salida(char msj[]);

/*--------------------------------------------------------------------------
Autores: Luis Eladio Castro
         Randall Jimenez
         Josue Fernandez
I Tarea Programada
----------------------------------------------------------------------------*/
//Funciones Usadas
int Validar_Usuario(int boolean,char *_usuario,char *_ip,char * _puerto);//valida que el usuario exista
int Agrega_Usuario();//funcion que agrega un nuevo usuario
void Leer_Archivo();//funcion que lee el archivo
void Imprime();
int Menu();//funcion del menu del programa, imprime opciones y recibe numeros para estar mas ordenado
int busca_pos();

typedef struct{
    char nombre[20];
    char ip[20];
    char puerto[20];
    int largo;
}Users;
Users Usuario[20];
int LARGO=0;

int main (int argc,char **argv){
    Leer_Archivo();
    if(LARGO==0) {
		printf("Su lista de contactos actual esta vacia\n");rayas;rayas;  }
    else {
		printf("La cantidad de contactos es de %d\n",LARGO-1);rayas;rayas }
    int opcion;rayas;
    char USUARIO[50];//variables que guardaran informacion
    char IP[50];//variables que guardaran informacion
    char PUERTO[50];//variables que guardaran informacion
    char* ptrUSUARIO;//punteros a dichas variables
    char* ptrIP;//punteros a dichas variables
    char* ptrPUERTO; //punteros a dichas variables
    ptrUSUARIO=USUARIO;//se asigna cada puntero a cada variable
    ptrIP=IP;//se asigna cada puntero a cada variable
    ptrPUERTO=PUERTO;//se asigna cada puntero a cada variable
    int flag;
    while (1){
		flag=Menu();
		if (flag==3) break;
		if (flag==0)break;
		}
	if (flag==3){
		Validar_Usuario(0,ptrUSUARIO,ptrIP,ptrPUERTO);
		sockets(ptrIP, ptrPUERTO); }
    return 0;
}

void Imprime(){
    FILE *ar;//inicializa a variable
    ar=fopen(ARCHIVO,"r");//abre e archivo para si lectura
    char actual[100];//variable que guardará os datos
    while(!feof(ar)){//mientras el archivo no llegue al final
        fflush(stdin);//Limpia el buffer de entrada para evitar errores
        fscanf(ar,"%s",actual);//lee la primera palabra en el archivo
        printf("Nombre: %s -- ",actual);
        fflush(stdin);//Limpia el buffer de entrada para evitar errores
        fscanf(ar,"%s",actual);//lee la primera palabra en el archivo
        printf("IP: %s -- ",actual);
        fflush(stdin);//Limpia el buffer de entrada para evitar errores
        fscanf(ar,"%s",actual);//lee la primera palabra en el archivo
        printf("Puerto: %s\n",actual);
    }
        rayas;//conjunto de lineas que indica que el proceso actual ha finalizado
}

int Agrega_Usuario(){//funcion que agrega un usuario nuevo
    FILE *fp;//crea a variabe que alvergara al archivo
    char ip[100];//inicializa las variabes para guardar los datos
    char puerto[100];//inicializa las variabes para guardar los datos
    char usuario[100];//inicializa las variabes para guardar los datos

    fp = fopen ( ARCHIVO, "a" );//abre el archivo para escribir en el, si no existe se crea
    printf("\n Introduce el ip: ");//mensaje para el usuario
    fflush(stdin);//limpia el buffer de entrada para evitar errores en el manejo de información
    scanf("%s",&ip);//recibe los datos en la memoria
    strcpy(Usuario[LARGO].ip,ip);//da el valor del ip al usuario en la posicion pos
    strcat(ip," ");//añade un espacio para ordenarlos de mejor forma

    printf ("\n Introduce el puerto: " );//mensaje para el usuario
    fflush(stdin);//limpia el buffer de entrada para evitar errores en el manejo de información
    scanf("%s",&puerto);//recibe los datos en la memoria
    strcpy(Usuario[LARGO].puerto,puerto);//da el valor del puerto al usuario en la posicion pos

    printf ("\n Introduzca el nombre de usuario(Reconoce mayusculas): ");//mensaje para el usuario
    fflush(stdin);//limpia el buffer de entrada para evitar errores en el manejo de información
    scanf("%s",&usuario);//recibe los datos en la memoria
    strcpy(Usuario[LARGO].nombre,usuario);//da el nombre de usuario al usuario en la posicion pos
    strcat(usuario," ");//añade un espacio para ordenarlos de mejor forma

    rayas;//conjunto de lineas que indica que el proceso actual ha finalizado

    strcat (usuario,ip);//juntar los datos en una sola linea
    strcat (usuario,puerto);//junta los datos en una sola linea
    strcat(usuario,"\n"); //hace salt de linea en el archivo .txt
    LARGO++;
    fprintf (fp,usuario);//escribe los datos en el archivo txt

    fclose ( fp );//cierra el archivo de texto para evitar errores

    return 0;//retorna 0 si todos los procesos se completaron de forma correcta
}

int Validar_Usuario(int boolean, char* _usuario,char* _ip,char * _puerto){
    FILE *file;//inicia el valor que contendrá el archivo
    printf("Ingrese el nombre de contacto: ");//mensaje para el usuario
    char palabra[50];
    char* ptrpalabra;char* pos;
    ptrpalabra=palabra;
    fflush(stdin);//Limpia el buffer de entrada para evitar errores
    scanf("%s",ptrpalabra);
    printf("el usuario es: %s\n",ptrpalabra);
    pos=ptrpalabra;
    //variable donde se guardará el valor
    file=fopen(ARCHIVO,"r");//abre el achivo de texto.
    while(!feof(file)){//mientras el archivo no llegue al final
        fflush(stdin);//Limpia el buffer de entrada para evitar errores
        fscanf(file,"%s",_usuario);//lee la primera palabra en el archivo
        printf("el usuario a comparar es: %s\n",_usuario);
        ptrpalabra=pos;
        while(((*ptrpalabra!= '\0')||(*_usuario!='\0'))&&(!strcmp(ptrpalabra,_usuario))){
                if(!strcmp(ptrpalabra,_usuario)){
                       // printf("los strings de la concha fueron %s y %s\n",ptrpalabra,_usuario);
                        ptrpalabra++;
                        _usuario++;
                }
        }
        if((*ptrpalabra=='\0')&&(*_usuario=='\0')){

            fflush(stdin);//Limpia el buffer de entrada para evitar errores
            fscanf(file,"%s",_ip);// guarda el siguiente valor en el archivo en ip

            fflush(stdin);//Limpia el buffer de entrada para evitar errores
            fscanf(file,"%s",_puerto);break;//guarda el siguiente valor en el archivo en puerto
           break;
        }else{//si el valor no era el que se buscaba, pasa a la siguiente linea del archivo
            fscanf(file,"%s",_usuario);fscanf(file,"%s",_usuario);}//se mueve a la siguiente linea para evitar errores
    }
    if(boolean){
        printf("Nombre de contacto: %s\n",palabra);
        printf("Numero de IP: %s\n",_ip);
        printf("Numero de puerto: %s\n",_puerto);
        rayas;//conjunto de lineas que indica que el proceso actual ha finalizado
    }
    fclose(file);//cierra el achivo
    return 0;//retorna 0 si todo se realizó sin errores
}


void Leer_Archivo(){//Funcion que lee el archivo e ingresa su contenido en el struct
    FILE *archivo;//variable que contrendra la posicion del archivo
    archivo=fopen(ARCHIVO,"r");//abre el archivo para lectura
    if(archivo==NULL){//si el archivo no existe
        archivo=fopen(ARCHIVO,"a+");//se crea el archivo con nombre ARCHIVO
    }
    char palabra[100];//variable que guarda un archivo
    while(!feof(archivo)){//mientras que no se llega al final del archivo
        char o=getc(archivo);
        if(o==EOF){
            break;
        }
        fflush(stdin);//Se limpia el buffer de entrada para evitar errores
        fscanf(archivo,"%s",palabra);//guarda el valor de %s en palabra
        strcpy(Usuario[LARGO].nombre,palabra);//copia el cntenido de palabra en Usuario[LARGO]
        fflush(stdin);//Se limpia el buffer de entrada para evitar errores
        fscanf(archivo,"%s",palabra);//guarda el valor de %s en palabra
        strcpy(Usuario[LARGO].ip,palabra);//copia el cntenido de palabra en Usuario[LARGO]
        fflush(stdin);//Se limpia el buffer de entrada para evitar errores
        fscanf(archivo,"%s",palabra);//guarda el valor de %s en palabra
        strcpy(Usuario[LARGO].puerto,palabra);//copia el cntenido de palabra en Usuario[LARGO]
        LARGO++;
    }
    printf("Los contactos fueron cargados con exito\n");
    fclose(archivo);
}

//Función para que el usuario indique que desea realizar, no recibe nada y en caso de querer usar el chat retorna 3, si desea salir retorna 0 en cualquier otro caso retorna 1
int Menu(){
    int opcion;rayas;
    char USUARIO[50];//variables que guardaran informacion
    char IP[50];//variables que guardaran informacion
    char PUERTO[50];//variables que guardaran informacion
    char* ptrUSUARIO;//punteros a dichas variables
    char* ptrIP;//punteros a dichas variables
    char* ptrPUERTO; //punteros a dichas variables
    ptrUSUARIO=USUARIO;//se asigna cada puntero a cada variable
    ptrIP=IP;//se asigna cada puntero a cada variable
    ptrPUERTO=PUERTO;//se asigna cada puntero a cada variable
    printf("Se encuentra en el menu del sistema\n");//mensaje para el usuario
    printf("1- Agregar un nuevo contacto\n2- Busqueda de un contacto\n3- Enviar mensajes\n4- Imprimir Contactos\n0: Salir\n");rayas;
    printf("\tIngrese la opcion a la que desea acceder: ");
    scanf("\t%d",&opcion);//scanea la oopcion dada por el usuario
    while((opcion<0)||(opcion>4)){
        printf("Ingrese uno de los numeros establecidos: ");
        scanf("\t%d",&opcion);
    }rayas;
    switch(opcion){//verifica cada opcion hasta que una se cumpla,ejecuta el codigo enterno y vuelve a preguntar
        case 0:
            return 0;//si el usuario indica 0, el menu se sale y termina el while
            break;
        case 1:
            Agrega_Usuario();//si ejecuta 1, agrega un nuevo contacto a la lista
            break;
        case 2:
            Validar_Usuario(0,ptrUSUARIO,ptrIP,ptrPUERTO);// Busca usuario y devuelve los datos de este
            printf("Salio de validar usuario con exito\n");
            printf("Actualmente el nombre es: %s\n",ptrUSUARIO);
            printf("Actualmente el IP es: %s\n",ptrIP);
            printf("Actualmente el puerto es: %s\n\n",ptrPUERTO);
            break;
        case 3:
			return 3;// Retorna un 3 para entrar al chat
            break;
        case 4:
			if(LARGO==0)printf("Usted no tiene contactos para imprimir\n");
            else{
            Imprime();}
            break;
    }
    return 1;
}
