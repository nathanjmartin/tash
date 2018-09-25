#include <iostream>
#include <string>
#include <vector>


using namespace std;
vector<string> commands;


//method to add the list of commands to the command vector
void addCommands() {
  commands.push_back("exit");
  commands.push_back("ls");
}

//main method
int main() {
  string userInput; //string to hold the user's input
  addCommands();

  while(true) {     //loop to continue prompting for commands
    cout << "uofmsh> "; //printing out to the console
    cin >> userInput; //accepting user input to store in userInput

    if(userInput == "exit") {   //conditional for the exit command
      break;
    }
    if(userInput == "ls") {
      // code for ls command
    }
    if(userInput == "help") {
      for(int i = 0; i < commands.size(); i++) {
        cout << commands.at(i) << endl; //prints out all the commands in the commands vector.
      }
    }
  }
  return 0;
}
