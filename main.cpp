#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
	int status;
	char linea[20];
	char texto[100];
	char *comando;
	char *param;
	char *oper;
	char *param1;
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
		param = strtok(NULL," ");
		oper = strtok(NULL," ");
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
