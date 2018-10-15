//Programming Assignment 1 - Simple Shell
//Nathan Martin
//Daniel Chamberlin

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <limits.h>
#include <cstdio>
#include <cstdlib>

#define SHELL "/bin/sh"

using namespace std;


string GetCurrent(void){//get current directory for prompt
  char buffer[FILENAME_MAX];//buffer for path returned by getcwd
  getcwd(buffer,FILENAME_MAX);//get the current working directory
  string currentDir(buffer);//put cwd in string
  return currentDir;//return string
}
int shellcmd(char *cmd){
      pid_t pid = fork(); //fork process
      if (pid == -1){
          cout << "Failed to fork!"; // error, failed to fork()
      }else if (pid > 0){
          // parent

        int status;
        waitpid(pid, &status, 0); //wait for status
      }else if (pid==0){
          // child
          execl(SHELL, SHELL, "-c", cmd, NULL); //execute the command with its arguments
        }
    return 0;
}
//main method
int main() {
  string userInput;//string to hold the user's input


  while(true) {     //loop to continue prompting for commands
    cout << GetCurrent()+"]uofmsh> "; //printing out to the console

    getline(cin, userInput,'\n'); //accepting user input to store in userInput

    char *command = new char[userInput.size()+1]; //create char array to hold userInput copy
    strcpy(command,userInput.c_str()); //copy userIput to c-style string named command
    char* token;  //define our token variable

    if(strstr(command,"exit")) {   //conditional for the exit command
      exit(0);  //equivalent of setting status to 0 (false) to end the loop
    }

    // CD COMMAND
     else if(strstr(command,"cd")!=NULL){ //conditional for cd command
       int pid = fork();
       if (pid == 0){
        token = strtok(command, " "); //get the first token again
        token = strtok(NULL, " "); //get the 2nd token - the argument
        if(token != NULL) {
            chdir(token); //pass argument to chdir() function
        }
        else { //else the token is empty and we want to go to the home directory
            chdir(getenv("HOME"));
        }
       }
       else if(pid > 0){
         wait(NULL);
       }
     }
     else if(strstr(command,">")!=NULL || strstr(command,"<")!=NULL || strstr(command,"|")!=NULL){
      pid_t pid = fork();

      if (pid == -1){
        cout << "Failed to fork!";  // error, failed to fork()
      }else if (pid > 0){
        int status;
        waitpid(pid, &status, 0);
      }else if (pid==0){
        fflush(stdout); // clear stdout
        char* redirectToken; //variable for tokenizing parts of redirection

        //redirect from command to file
        if(strstr(command,">")!=NULL){
          // following commands tokenize string into:
          // left side of redirect symbol
          // the redirect symbol
          // right side of redirect symbol
          redirectToken = strtok(command, ">");//tokenize string
          char* left = redirectToken; //left side token
          redirectToken = strtok(NULL, ">");
          redirectToken = strtok(redirectToken, " ");
          redirectToken = strtok(redirectToken, "\n");
          char* right = redirectToken;//right size token (filename)

          // redirect to file
          FILE *fileptr = fopen(right, "w");// open file
          int filedescriptor = fileno(fileptr);//get file descrptor
          dup2(filedescriptor, 1); //use file descriptor
          execl(SHELL, SHELL, "-c", left, NULL); //execute command

        //redirect from file to command
        }else if(strstr(command,"<")!=NULL){
          // following commands tokenize string into:
          // left side of redirect symbol
          // the redirect symbol
          // right side of redirect symbol
          redirectToken = strtok(command, "<");//tokenize string
          char* left = redirectToken; //left side token
          redirectToken = strtok(NULL, "<");
          redirectToken = strtok(redirectToken, " ");
          redirectToken = strtok(redirectToken, "\n");
          char* right = redirectToken;//right size token (filename)

          // redirect
          FILE *fileptr = fopen(right, "r");//open file
          int filedescriptor = fileno(fileptr); //get file descriptor
          dup2(filedescriptor, 0); //dup file descriptor
          execl(SHELL, SHELL, "-c", left, NULL); //execute command

        }
        /* else if(strstr(command,"|")!=NULL){
           // pipe output from first command to second command
           // following commands tokenize string into:
          // left side of redirect symbol
          // the redirect symbol
          // right side of redirect symbol
          redirectToken = strtok(command, "|");//tokenize string
          char* left = redirectToken; //left side token
          redirectToken = strtok(NULL, "|");
          redirectToken = strtok(redirectToken, " ");
          redirectToken = strtok(redirectToken, "\n");
          char* right = redirectToken;//right size token (second command)
        } */
        }
      }
    else shellcmd(command);
    }
  return 0;
}
