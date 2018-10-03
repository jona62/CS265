#include <iostream>
#include <cstdlib>
using namespace std;

void shell_functions(int);
void system_functions() {
	int choice = 0;
	do {
		cout<<"1. Display Current Dir.\n2. Display Home \n3. List Elements\n4. Exit\n";
		cout<<"Enter Choice: ";
		cin>>choice;
		shell_functions(choice);
	}while(choice  != 4); 
}

void shell_functions(int val) {
	system("clear");
	if(val == 1) system("pwd");
	else if(val == 2) system("echo $HOME");
	else if(val == 3) system("ls -l");
	else return;
}

int main() {
	system_functions();
}
