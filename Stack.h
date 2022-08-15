#pragma once
#include <vector>


template<typename type>
class Stack
{
private:
	std::vector<type> dataStack;
	int index = -1;
	//READ ME:
	//index is set up so it always points to some piece of data, it starts at -1 so when adding the first data it is incremented to 0
	//This makes it so no if statements or etc is needed in add data and remove data is also alot easier to setup because of this
public:

	~Stack() {
		//deallocate any allocated memory
		dataStack.clear();
	}
	
	int getCurrentIndex() {
		return index;
	}

	type getCurrent() {
		return dataStack[index];
	}

	void in(type data) {
		index++;
		dataStack.push_back(data); //increases size of vector by one and pushes the element into it
	}

	type out() {
		type returning = dataStack[index];
		index--;
		dataStack.pop_back(); //removes last element and reduces size by one
		return returning;
	}
	
};

