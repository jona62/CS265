#include <iostream>

void countDown(int);

int main(){
	countDown(10);
}

void countDown(int count) {

	while(count > 0) {
		std::cout<<count-- <<"\n";
	}
	std::cout<<"BLAST off!\n";
}
