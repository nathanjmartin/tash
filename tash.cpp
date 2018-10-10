#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

//main method
int main() {
  string userInput; //string to hold the user's input

  while(true) {     //loop to continue prompting for commands
    cout << "uofmsh> "; //printing out to the console
    getline(cin, userInput,'\n'); //accepting user input to store in userInput

    if(userInput == "exit") {   //conditional for the exit command
      break;  //equivalent of setting status to 0 (false) to end the loop
    }

    if(userInput == "ls") {
      int pid = fork();

      if (pid == 0){  //in the child process
        execl("/bin/ls", "ls", "-r", "-t", "-l", (char *) 0);
        }
      else if(pid > 0) {   //in the parent process
        wait(NULL);     //waiting for the child process to finish before continuing execution of the parent process
        }
      }
    }
  return 0;
}
