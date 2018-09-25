#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main() {
  string userInput; //string to hold the user's input

  while(true) {     //loop to continue prompting for commands
    cout << "uofmsh> "; //printing out to the console
    cin >> userInput; //accepting user input to store in userInput

    if(userInput == "exit") {   //conditional for the exit command
      break;
    }
  }
  return 0;
}
