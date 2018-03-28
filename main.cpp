#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <cstddef>


using namespace std;

int main() {
	int status;
	char linea[20];
	char texto[100];
	char *comando;
	char *param;
	char *oper;
	char *subcom;
	char *comando1;
	int pid;
	FILE *fd,*fd1;
	char c;
	int valor;

	while (1) {
		comando = NULL;
		param = NULL;
		cout << ":>>";
		cin.getline(linea, 20);

		string com = linea;
		string delimitator =" -";
		string delimitator1 = "&";
		size_t found = com.rfind(delimitator);
		size_t found1 = com.rfind(delimitator1);

		if(found == 2 && found1 != 2){
			comando = strtok(linea," ");
			subcom = strtok(NULL," ");
			oper = strtok(NULL," ");
			param = strtok(NULL," ");

			//si el archivo no existe entonces lo crea y escribe, si ya existe solo sobree escribe en el
			if( strcmp(oper,">") == 0){
				fd = fopen(param,"w");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,1);
				execlp(comando, comando, subcom, NULL);
				close(fw);
				fclose(fd);
			}else if (strcmp(oper,">>") == 0){ //si el archivo no existe lo crea y escribe, si ya existe le concatena la salida
				fd = fopen(param,"a");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,1);
				execlp(comando, comando, subcom, NULL);
				close(fw);
				fclose(fd);
			}

		}else if(found != 2 && found1 != 2){

			comando = strtok(linea," ");
			oper = strtok(NULL," ");
			param = strtok(NULL," ");
			//si el archivo no existe entonces lo crea y escribe, si ya existe solo sobree escribe en el
			if( strcmp(oper,">") == 0){
				fd = fopen(param,"w");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,1);
				execlp(comando, comando, NULL);
				close(fw);
				fclose(fd);
			}else if (strcmp(oper,">>") == 0){//si el archivo no existe lo crea y escribe, si ya existe le concatena la salida
				fd = fopen(param,"a");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,1);
				execlp(comando, comando, NULL);
				close(fw);
				fclose(fd);
			}

		}else if(found == 2 && found1 == 2){
			comando = strtok(linea," ");
			subcom = strtok(NULL," ");
			oper = strtok(NULL," ");
			param = strtok(NULL," ");
			comando1 = strtok(NULL," ");

			//si el archivo no existe entonces lo crea y escribe, si ya existe solo sobree escribe en el
			if( strcmp(oper,">") == 0 && strcmp(comando1,"2>&1")){
				fd = fopen(param,"w");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,2);
				execlp(comando, comando, subcom, NULL);
				close(fw);
				fclose(fd);
			}else if (strcmp(oper,">>") == 0 && strcmp(comando1,"2>&1")){ //si el archivo no existe lo crea y escribe, si ya existe le concatena la salida
				fd = fopen(param,"a");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,2);
				execlp(comando, comando, subcom, NULL);
				close(fw);
				fclose(fd);
			}

		}else if(found != 2 && found1 == 2){

			comando = strtok(linea," ");
			oper = strtok(NULL," ");
			param = strtok(NULL," ");
			//si el archivo no existe entonces lo crea y escribe, si ya existe solo sobree escribe en el
			if( strcmp(oper,">") == 0 && strcmp(comando1,"2>&1")){
				fd = fopen(param,"w");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,2);
				execlp(comando, comando, NULL);
				close(fw);
				fclose(fd);
			}else if (strcmp(oper,">>") == 0 && strcmp(comando1,"2>&1")){//si el archivo no existe lo crea y escribe, si ya existe le concatena la salida
				fd = fopen(param,"a");
				int fw = open(param, O_APPEND|O_WRONLY);
				dup2(fw,2);
				execlp(comando, comando, NULL);
				close(fw);
				fclose(fd);
			}

		}

		if ((pid = fork()) == 0) {
			valor = execlp(comando, comando, param, NULL);
		}else if (valor == -1){
			cout << "comando no existe" << endl;
		}
	}
	cout << "Esperando ..." << endl;
	waitpid(pid, &status,0);
	cout << "estado: " << status << endl;
	return 0;
}
