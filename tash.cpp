#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

//main method
int main() {
  string userInput; //string to hold the user's input

  while(true) {     //loop to continue prompting for commands
    cout << "uofmsh> "; //printing out to the console
    cin >> userInput; //accepting user input to store in userInput

    if(userInput == "exit") {   //conditional for the exit command
      break;
    }
    if(userInput == "ls") {
      pid_t pid = fork();
    }
  }
  return 0;
}
