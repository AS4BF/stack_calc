#include "stack.h"
#include "solver.h"
#include <iostream>

int main(){
	char expr[] = "1+1/2*10-1";
	stack<char> sexpr(20);

	for(int i = 0; i != 10; ++i){
		sexpr.push(expr[i]);
	};
	
	stack<char> solved(20);
	
	solve(sexpr, solved);

	while(!solved.empty()){
		std::cout << solved.top() << std::endl;
		solved.pop();
	};

};
