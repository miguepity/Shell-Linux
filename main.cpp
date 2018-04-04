#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstddef>

#pragma GCC diagnostic ignored "-Wwrite-strings"
#define simbolo_sistema "mi_sh>"
//g++ [archivo cpp] -o [ejecutable] -lreadline
static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);
#define n 100

#define MSJ_ERROR "Error de sintaxis\n"

void comando(char cadena[n], int bg);
void Nuevo_Proceso(char* comando_[n], int bg);
void executeCommand(char[]);

using namespace std;
int main()
{
  char *comand;
  char *param;
  char *oper;
  char *subcom;
  FILE *fd,*fd1;

  char *buf;
  string s="";
  rl_attempted_completion_function = my_completion;
  int i,bg=0;
  int pid, status;
  int Stdout = dup(1), Stdin = dup(0);
  bool isNotPipe = true;
  while((buf = readline(simbolo_sistema))!=NULL)
  {
    close(1);
    dup(Stdout);
    isNotPipe = true;
    close(0);
    dup(Stdin);
    int n_ = s.length();
    char cadena[n_+1];
    rl_bind_key('\t',rl_complete);
    s=buf;
    strcpy(cadena, s.c_str());

    if (strcmp(buf,"exit")==0)
    break;
    if (buf[0]!=0)
    add_history(buf);

    close(1);
    dup(Stdout);
    isNotPipe = true;
    close(0);
    dup(Stdin); // Asigno la salida estandar, es decir, la consola.

    printf(simbolo_sistema); //Visualizar en pantalla
    scanf("\n%[^\n]",cadena); //recorrido de la cadena hasta encontrar INTRO (ENTER)
    bg=0; //background en cero

    string delimitator =" -";
    string cad = cadena;
    size_t found = cad.find(delimitator,0);

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
          }else { //preceso padre
            close(0);			//cierra la lectura
            dup(pipefds[0]);	//replace with read side of pipe

            close(pipefds[0]);
            close(pipefds[1]);

            executeCommand(command2);
          }
        }else{
          int estado=0;
          if (bg == 0)
          pid=wait(&estado);
        }
      }else if( (cadchar cadena[n];
        int i,bg=0;
        int pid, status;
        int Stdout = dup(1), Stdin = dup(0);
        bool isNotPipe = true;

        while(1) // Bucle infinito
        {ena[i]=='>' && cadena[i+1]=='>') && found != 2){
          comand = strtok(cadena," ");
          oper = strtok(NULL," ");
          param = strtok(NULL," ");

          fd = fopen(param,"a");
          int fw = open(param, O_APPEND|O_WRONLY);
          cout << "1" << endl;
          dup2(fw,1);
          cout << "2" << endl;
          execlp(comand, comand, NULL);
          cout << "3" << endl;
          close(fw);
          cout << "4" << endl;
          fclose(fd);
          cout << "5" << endl;
        }else if( (cadena[i]=='>' && cadena[i+1]=='>') && found == 2){
          comand = strtok(cadena," ");
          subcom = strtok(NULL," ");
          oper = strtok(NULL," ");
          param = strtok(NULL," ");

          fd = fopen(param,"a");
          int fw = open(param, O_APPEND|O_WRONLY);
          dup2(fw,1);
          execlp(comand, comand, subcom, NULL);
          close(fw);
          fclose(fd);
        }else if ( cadena[i]== '>' && found == 2){
          comand = strtok(cadena," ");
          subcom = strtok(NULL," ");
          oper = strtok(NULL," ");
          param = strtok(NULL," ");

          fd = fopen(param,"w");
          int fw = open(param, O_APPEND|O_WRONLY);
          dup2(fw,1);
          execlp(comand, comand, subcom, NULL);
          close(fw);
          fclose(fd);
        }else if (cadena[i]== '>' && found != 2){
          comand = strtok(cadena," ");
          oper = strtok(NULL," ");
          param = strtok(NULL," ");

          fd = fopen(param,"w");
          int fw = open(param, O_APPEND|O_WRONLY);
          dup2(fw,1);
          execlp(comand, comand, NULL);
          close(fw);
          fclose(fd);
        }
      }
      if(isNotPipe==true){
        comando(cadena,bg); //enviamos la cadena y el estado del background al procedimiento "comando"
      }
    }
    delet buf;
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
    }else{
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


  static char** my_completion( const char * text , int start,  int end)
  {
    char **matches;

    matches = (char **)NULL;

    if (start == 0)
    matches = rl_completion_matches ((char*)text, &my_generator);
    else
    rl_bind_key('\t',rl_abort);


    return (matches);

  }

  char* my_generator(const char* text, int state)
  {
    static int list_index, len;
    char *name;

    if (!state) {
      list_index = 0;
      len = strlen (text);
    }

    while (name = cmd[list_index]){   //&&strncmp(cmd[list_index],"\r",1)!=0) {
      list_index++;

      if (strncmp (name, text, len) == 0)
      return (dupstr(name));
    }

    /* If no names matched, then return NULL. */
    return ((char *)NULL);

  }

  char * dupstr (char* s) {
    char *r;

    r = (char*) xmalloc ((strlen (s) + 1));
    strcpy (r, s);
    return (r);
  }

  void * xmalloc (int size)
  {
    void *buf;

    buf = malloc (size);
    if (!buf) {
      fprintf (stderr, "Error: Out of memory. Exiting.'n");
      exit (1);
    }

    return buf;
  }
