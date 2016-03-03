#include "GenStack.h"
#include <iostream>
#include <fstream>
using namespace std;

void readFile(string file);

int main (int argc, char** argv) {
	
	readFile(argv[1]); //read the second argument of the command line
	return 0;
}

//method to read a file and check correctness of {}, [], and ()
void readFile(string file) {

	GenStack<char>* gs = new GenStack<char>(5); //create new instance of a stack
	
	string line; //keep track of the lines of the file 
	string answer; //get answer of the user
	string nextFile; //use at end of program to get a new file from user 

	int lineCounter = 1; //keep track of line count 
	bool perfect = true; //check for correct syntax
	//CLEANED UP ATTEMPT
	ifstream reader(file); //open connection to the file 
	if (reader.is_open()) {
		bool readCheck = true; //only go through loop is everything is still okay 
		while (getline(reader, line) && readCheck) {
			for (int i = 0; i < line.size(); ++i) { 
				if (line[i] == '{' || line[i] == '[' || line[i] == '(') { //go through each line and push any opening characters
					gs->push(line[i]);
				}
				else if (line[i] == '}' || line[i] == ']' || line[i] == ')') {
					if (line[i] == '}' && gs->peek() == '{') { //check to see if closing characters match top of stack and pop them if they do
						gs->pop();
					}
					else if (line[i] == ']' && gs->peek() == '[') {
						gs->pop();
					}
					else if (line[i] == ')' && gs->peek() == '(') {
						gs->pop();
					}
					else if (gs->isEmpty()) { //if the stack is empty, there is an unexpected closing character
						readCheck = false; //if something is wrong with matching characters, stop going through loop
						perfect = false; //also make perfect = false since the file will have an error 
						cout << "Error at line " << lineCounter << ": unexpected '" << line[i] << "' found." << endl;
					}
					else {
						readCheck = false; //errors stop loop and make for a non-perfect file 
						perfect = false;
						if (line[i] == '}' && gs->peek() == '['){ //check each case, and print out what should be there if the wrong character
							cout << "Error at line " << lineCounter << ": ']' expected but found '" << line[i] << "'" << endl; //is on top 
						}																									   //of stack	
						else if (line[i] == '}' && gs->peek() == '(') {
							cout << "Error at line " << lineCounter << ": ')' expected but found '" << line[i] << "'" << endl;
						}
						else if (line[i] == ']' && gs->peek() == '{') {
							cout << "Error at line " << lineCounter << ": '}' expected but found '" << line[i] << "'" << endl;
						}
						else if (line[i] == ']' && gs->peek() == '(') {
							cout << "Error at line " << lineCounter << ": ')' expected but found '" << line[i] << "'" << endl;
						}
						else if (line[i] == ')' && gs->peek() == '{') {
							cout << "Error at line " << lineCounter << ": '}' expected but found '" << line[i] << "'" << endl;
						}
						else if (line[i] == ')' && gs->peek() == '[') {
							cout << "Error at line " << lineCounter << ": ']' expected but found '" << line[i] << "'" << endl;
						}
					}
				}
			}
			lineCounter++; //increase the line each time you go through the while loop 
		}
		if (!gs->isEmpty() && readCheck) { //checks to see if the end of the file is reached and the stack is not empty 
			readCheck = false;
			perfect = false;
			switch(gs->peek()) { //check the top of the stack and print out what is missing 
				case '{':
					cout << "Reached end of file: missing " << "'}'" << endl; 
					break;
				case '[':
					cout << "Reached end of file: missing " << "']'" << endl;
					break;
				case '(':
					cout << "Reached end of file: missing " << "')'" << endl;
					break;
			}
		}
	}

	if (perfect) { //takes care of perfect files 
		
		cout << "The file contained no errors." << endl;
		cout << "Would you like to process another file? Please enter yes or no." << endl;
			
		bool condition = true;
		while (condition) { //prompt for a yes or no answer until user enters 'yes' or 'no'
			cin >> answer; 
			if (answer == "yes") {
				condition = false;
				cout << "What file would you like to process?" << endl;
				cin >> nextFile; //take in another file and process the file 
				readFile(nextFile);
			}
			else if (answer == "no") {
				condition = false; //break out of the loop if the user enters no
			}
			else {
				cout << "Please enter 'yes' or 'no'." << endl;
			}
		}
	}
	delete gs; //delete allocated pointer to the stack 
}