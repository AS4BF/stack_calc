#ifndef SOLVER_H
#define SOLVER_H
#include "stack.h"


struct token{
	char token_;
	int priority_;

	bool operator>(const token& rhs) const {
		return priority_ > rhs.priority_;
	};

	bool operator>(const int& rhs) const {
		return priority_ > rhs;
	};

	bool operator==(const token& rhs) const {
		return token_ == rhs.token_;	
	};

	bool operator==(const char& rhs) const {
		return token_ == rhs;	
	};

	bool operator>=(const token& rhs) const {
		return priority_ >= rhs.priority_;
	};
};

const token tokens[] = {
	{'1', 0},
	{'2', 0},
	{'3', 0},
	{'4', 0},
	{'5', 0},
	{'6', 0},
	{'7', 0},
	{'8', 0},
	{'9', 0},
	{'0', 0},
	{'.', 0},
	{'+', 1},
	{'-', 2},
	{'*', 3},
	{'/', 4}
};


void solve(stack<char>& input, stack<char>& output){
	
	stack<token> currents(100);

	while(!input.empty()) {
			
		for(int i = 0; i != 15; ++i){
			if(tokens[i] == input.top() && !(tokens[i] > 0)) { 
				output.push(tokens[i].token_);
				input.pop();
				break;
			} else if(tokens[i] == input.top() && tokens[i] > 0) {
				if(currents.empty() || !(currents.top() >= tokens[i])) {
					currents.push(tokens[i]);
					input.pop();
					break;
				} else if (currents.top() >= tokens[i]) {
					output.push(currents.top().token_);
					currents.pop();
					break;
				}; 
			}; 
		};
    	};

	while(!currents.empty()) {
		output.push(currents.top().token_);
		currents.pop();
	};

};


#endif
