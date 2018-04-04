#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstddef>
#include <string.h>

#define n 100
#define simbolo_sistema "mi_sh>"
#define MSJ_ERROR "Error de sintaxis\n"

void comando(char cadena[n], int bg);
void Nuevo_Proceso(char* comando_[n], int bg);
void executeCommand(char[]);



using namespace std;
int main()
{ 
char cadena[n];  
int i,bg=0;
int pid, status;
int Stdout = dup(1), Stdin = dup(0);
bool isNotPipe = true;

while(1) // Bucle infinito
	{
        close(1); 
        dup(Stdout);
		isNotPipe = true;
        close(0); 
		dup(Stdin); // Asigno la salida estandar, es decir, la consola.
		
		printf(simbolo_sistema); //Visualizar en pantalla
		scanf("\n%[^\n]",cadena); //recorrido de la cadena hasta encontrar INTRO (ENTER)
		bg=0; //background en cero
		for(i=0;cadena[i] != '\0'; i++)
		{
			if(cadena[i] == '&') //Se revisa la cadena para ver si hay o no un simbolo '&'
			{
				cadena[i] = '\0'; //al encontrar un '&' se asigna un fin de cadena (\0) y se activa el background
				bg = 1;//el background se activa, 1= activado y 0= desactivado
				isNotPipe = true;
	
			} 
			if(cadena[i] == '|'){
				isNotPipe = false;
				if(pid = fork() == 0){
					int pid;
					int pipefds[2];
					char *command1, *command2;

					command1 = strtok(cadena, "|");
					command2 = strtok(NULL, "|");

					cout<<"COMANDO UNO "<<command1<<endl;
					cout<<"COMANDO DOS"<<command2<<endl;
					pipe(pipefds);


					if ((pid = fork()) < 0) {
						cerr << "Fork error al ejecutar el comando pipe" << endl;
						exit(1);
					}

					if (pid == 0) {	//proceso hijo
						close(1);			//cierra la escritura
						dup(pipefds[1]);	

						close(pipefds[0]);	
						close(pipefds[1]);

						executeCommand(command1);	
					}

					else { //preceso padre
						close(0);			//cierra la lectura
						dup(pipefds[0]);	//replace with read side of pipe

						close(pipefds[0]);	
						close(pipefds[1]);

						executeCommand(command2);	
					}
				}else  { 
					int estado=0;
					if (bg == 0) 
					pid=wait(&estado);
				}
			}
		}
		if(isNotPipe==true){
			comando(cadena,bg); //enviamos la cadena y el estado del background al procedimiento "comando"
		}
	}
return(0);
} 

void comando(char cadena[n], int bg)
{ 
int i,j,k;	
char comando[n][n]; 
char *comando_[n];
comando_[0] = NULL;

	 	k = 0;
	    i = 0;
		while(cadena[i] != '\0')
		{
			for(j=0; cadena[i] != ' ' && cadena[i] != '\0' ;j++)
			{ 
				comando[k][j] = cadena[i];// mientras el caracter sea distinto de espacio y terminacion de cadena (\0) añadir al comando el caracter
				i++;
			}
			if (cadena[i] == ' ') // Si el caracter es un espacio, pasar al siguiente caracter e introducir un fin de caracter a cada comando leido
				i++;
				comando[k][j] = '\0';
				comando_[k] = comando[k];
				k++;			
		}
		comando_[k] = NULL; 
			Nuevo_Proceso(comando_,bg); 
		
}

void Nuevo_Proceso(char* comando_[n],int bg)
{	
	int estado=0;
	pid_t pid; 
	pid=fork();
	if (pid<0) 
	printf("ERROR AL CREAR PROCESO"); 
	else if (pid==0) {
			
		execvp(comando_[0],comando_);
		perror("ERROR:");
		exit(estado);
		   }
	else  { 
		if (bg == 0) 
		 pid=wait(&estado);
	      }

} 

void executeCommand(char command[]) {
	int index = 1;
	char *args[30]; 					 
	char *token = strtok(command, " ");	 
	args[0] = strdup(token);			 

	while ((token = strtok(NULL, " ")) != NULL) {
		args[index] = strdup(token);
		++index;
	}
	args[index] = NULL;
	execvp(args[0], args);
}

