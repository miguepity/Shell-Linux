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

		comando = strtok(linea," ");
		oper = strtok(NULL," ");
		param = strtok(NULL," ");

		string com1;
		string com = comando;
		string delimitator ="-";
		size_t found = com.rfind(delimitator);
		if (found == 2){ //substring de comando a comando1
			//comando = strtok(com," ");
			//comando1 = strtok(NULL," ");
			cout << com << "  " << com1 << endl;
			//asigno el string com a comando
			strcpy(comando, com.c_str());
		}else	if( strcmp(oper,">") == 0){
			fd = fopen(param,"w");
			int fw = open(param, O_APPEND|O_WRONLY);
			dup2(fw,1);
			execlp(comando, comando, NULL);
			close(fw);
			fclose(fd);
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
