#include <iostream>

class MyStack{
	int *buff;
	size_t size;
	size_t capacity;
	
  public:
	MyStack(size_t cap = 32){
		capacity = 32;
		size = 0;
		buff = new int[cap];
	}
	
	~MyStack(){delete[] buff;}
	
	void push(int x){
		if(size >= capacity) throw 1;
		buff[size++] = x;
	}
	
	int pop(){
		if(size == 0) throw 1;
		return buff[--size];
	}
	
	int peek(){
		if(size == 0) throw 1;
		return buff[size-1];
	}
	
	bool isEmpty() {return size == 0;}
	int getSize() {return size;}
	
	void display() const {
		using namespace std;
		cout << "[";
		for(size_t i = 0; i < size; ++i){
			cout << buff[i] << " ";
		}
		cout << "]\n";
	}
};

void help(){
	std::cout
		<< "i xx -- push\n"
		<< "o    -- pop\n"
		<< "q    -- peek\n"
		<< "d    -- display\n"
		<< "x    -- exit\n";
}

int main(){
	using namespace std;
	
	char c;
	int t;
	
	MyStack st;
	
	help();
	
	while(true){
		cin >> c;
		try{
			switch(c){
				case 'i':
					cin >> t;
					st.push(t);
					st.display();
					break;
				case 'o':
					cout << "poped "
						 << st.pop()
						 << "\n";
					break;
				case 'q':
					cout << "peek "
						 << st.peek()
						 << "\n";
					break;
				case 'd':
					st.display();
					break;
				case 'x': return 0;
				default: break;
			}
		} catch (int iii){
			cout << "error\n";
		}
	}
}