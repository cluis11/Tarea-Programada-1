#include <stdio.h> //es la biblioteca estándar en C
#include <string.h> //incluye una libreria para manejo de strings
#include <stdlib.h>//archivo de cabecera de la biblioteca estándar
#include <strings.h>//libreria que incluye funciones para el manejo de strings
#include <sys/socket.h>//libreria principal para el manejo de sockets 
#include <unistd.h>//es el header file que provee acceso al API POSIX de los sistemas operativos Linux/Unix.
#include <sys/types.h>//manejo del tipo de datos
#include <netinet/in.h>//libreria para el manejo de IPs entre otras funciones
#include <netdb.h>//definiciones para el manejo de operaciones en informacion de la red

//verifica si el mensaje es un adios para cerrar la conexion
int salida(char msj[]){
	char adios[]={'a','d','i','o','s'};
	int i;					//variable para el for
	for(i=0;i<5;i++){
		if (msj[i]!=adios[i])
			return 0;
	}
	return 1;
}

//Lee el mensaje para poder imprimirlo en pantalla
int lee_msj(int accept){
	int m;
	char buffer[256];
	char* scaneo;

	m= read(accept, buffer, 255);
	if (m<0) printf("error leyendo\n");
	printf("\x1b[31m\n\n: %s\n\x1b[36m: ",buffer);
	if (salida(buffer) == 1){	   
	   return 1;
	}
   	return 0;
}

//Funcion que se encarga de la creacion de los sockets y el envio de mensajes, recibe el IP y puerto de un contacto
sockets (char* IP, char* Porto) {
	int conexion, conexion_verif;//verificador de conexion y variable para para el ciclo cuando esta intentando conectar
	int servidor_socket;// Nombre del socket servidor
	int cliente_socket;// Nombre del socket cliente
	int flag_accept;//para la funcion accept
	int pid, pid2;//para los fork
	int Puerto_servidor, Puerto_cliente;//almacenaran los puertos de servidor y cliente
	int temp, salir_chat;//temp es una variable temporal para escribir en el socket y salida_chat indica si es un adios 1 si lo es , 0 contrario.
	char msj_enviar[256];//arreglo para los mensajes
	//int n;		
	struct sockaddr_in Direccion,Direccion_srv, cliente;//crea la estructura para contener las ip que se quieren atender 
	struct hostent *servidor;//estructura para contener la ip del servidor
	socklen_t Longitud_cliente;
	pid=fork();

	if (pid==0){ 	

		//se crea el socket para el servidor
		servidor_socket = socket(AF_INET, SOCK_STREAM,0);//crea el socket servidor
		if (servidor_socket == -1) printf ("Error\n");
		bzero((char *) &Direccion, sizeof(Direccion));
		//crea el del bind del socket
		Puerto_servidor=(5001);//puerto por el cual escuchara al servidor
		Direccion.sin_family = AF_INET;//Toma el IP para el seridor
		Direccion.sin_port = htons(Puerto_servidor);// indica el puerto por el cual va a escuchar
		Direccion.sin_addr.s_addr = INADDR_ANY;//indica que atendera a cualquier ip que solicite el servicio
		//hace el bind  del socket servidor_socket con las solicitudes que entren , -1 en caso de error
		if (bind (servidor_socket, (struct sockaddr *) &Direccion, sizeof (Direccion))==-1)
			printf("Error en el bind\n");
		else printf("\nChat abierto\n\n");

		if (listen(servidor_socket,10)==-1)//indica al servidor que empiece a escuchar por cleintes.
			printf("error listening\n");
			
		Longitud_cliente = sizeof (cliente);//almacena la longitud del mensaje
		while (1){

			flag_accept = accept(servidor_socket, (struct sockaddr *) &cliente, &Longitud_cliente);
			if (flag_accept<0)
				printf("error en la aceptacion \n");
			pid2=fork();
			if (pid2<0)printf("error en el pid2 \n");
			if (pid2==0){
				close(servidor_socket);//cierra la copia del socket creado por el fork()
				salir_chat=lee_msj(flag_accept);//verifica si el msj en el accept es un adios
				if (salir_chat==1) break;
					return 0;
					exit(0);
			}
			else	close(flag_accept);			
		}//fin del while
		close(servidor_socket);//cierra el socket cliente
		return 0;
	}
	else{
	while(1){

		Puerto_cliente =atoi(Porto);// este puerto es por el cual hara el conect
		cliente_socket = socket (AF_INET, SOCK_STREAM, 0);//crea el socket cliente
		if (cliente_socket == -1)
			printf ("error creando el socket cliente\n");		
		servidor = gethostbyname (IP);//crea la estructua que contiene la direccion ip del servidor 

		if (servidor == NULL)
			printf ("error en la direccion ip del servidor\n");		
		bzero((char *) &Direccion_srv, sizeof(Direccion_srv));//reinicia la estructura Direccion_srv
		Direccion_srv.sin_family = AF_INET;//indica que el socket servira en computadores diferentes
		bcopy((char *)servidor	->h_addr, (char *)&Direccion_srv.sin_addr.s_addr,servidor->h_length);//asigna la direccion ip al socket
		Direccion_srv.sin_port = htons(Puerto_cliente);//convierte el int Puerto_cliente en una estructura de puerto

		conexion_verif=0;//indica si ya se establecio la conexion con el srv, 1 si ya lo logro, 0 de lo contrario
		while(conexion_verif==0){//termina cuando conexion_verif sea = 1
			conexion=connect (cliente_socket,(struct sockaddr *) &Direccion_srv, sizeof(Direccion_srv)) ;
			if(conexion<0)printf(""); 
			else {conexion_verif=1;//indica que hubo una conexion satisfactoria
				printf("\x1b[36m\n: ");}
		}
		conexion_verif=0;
		bzero(msj_enviar, 256);//borra el mensaje anterior
		fgets(msj_enviar, 255, stdin);//funcion para leer del stdin el msj del usuario

		//verifica si es adios
		if(salida(msj_enviar)==1)
			salir_chat=1;

		temp=write(cliente_socket, msj_enviar, sizeof(msj_enviar));//escribe en el socket para enviar al servidor

		if (temp<0) printf("error al escribir\n");

		temp=read(cliente_socket, msj_enviar, 255);

		if (salir_chat == 1) return 0;//condicion para del while
	}
	close(cliente_socket);//cierra el socket cliente
	return 0;
} 	
		return cliente_socket;	//fin de la funcion socket
}

