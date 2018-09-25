#include <iostream>
#include <cstdlib>

using namespace std;

void menu_item();
void systemCalls(int);
bool isGood(int);

int main(){
	menu_item();
	return 0;
}

void menu_item() {
	int choice;
	do {
		cout<<"1) Display your current Directory\n";
		cout<<"2) Display your Home Directory\n";
		cout<<"3) List the contents of the current Directory\n";
		cout<<"4) Exit\n";
		cin>>choice;
		if(!isGood) {
			cout<<"Choice from the options above.\n";
			continue;
		}
		cout<<"\n";
		systemCalls(choice);

	} while(choice != 4);
}

bool isGood(int choice) {
	return (choice <= 4 || choice >= 0);
}

void systemCalls(int choice) {
	switch(choice) {
		case 1:
			system("pwd");
			cout<<"\n";
			cout<<"\n";
			break;
		case 2:
			system("echo $HOME");
			cout<<"\n";
			cout<<"\n";
			break;
		case 3:
			system("ls -al");
			cout<<"\n";
			cout<<"\n";
			break;
		case 4:
			return;
	}
}
