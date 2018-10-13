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

       token = strtok(command, " "); //get the first token again
       token = strtok(NULL, " "); //get the 2nd token - the argument
       if(token != NULL) {
         chdir(token); //pass argument to chdir() function
       }
       else { //else the token is empty and we want to go to the home directory
         chdir(getenv("HOME"));
       }
     }

    else if(strstr(command,"ls")!=NULL) {//conditional for ls command
      int pid = fork();

      if (pid == 0){  //in the child process
        execl("/bin/ls", "ls", "-r", "-t", "-l", (char *) 0);
        }
      else if(pid > 0) {   //in the parent process
        wait(NULL);     //waiting for the child process  to finish before continuing execution of the parent process
        }
      }
    }
  return 0;
}
