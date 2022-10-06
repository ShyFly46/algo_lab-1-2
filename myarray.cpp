#include <iostream>
//#include <memory.h>

typedef unsigned int uint;

class MyArray{
protected:
	uint size;
	uint cap; // capacity
	int* arr;
	
	void setcap(uint newcap){
		if(newcap <= cap)
			throw 1;
		
		int* newarr = new int[newcap];
		
		//memcpy(newarr, arr, sizeof(int) * cap);
		for(int i=0; i<cap; ++i)
			newarr[i] = arr[i];
		
		delete[] arr;
		arr = newarr;
		cap = newcap;
	}
	
	void checkcap(){
		if(size < cap)
			return;
		
		setcap(size * 2);
	}
	
	void checkcap(unsigned int x){
		if(size + x < cap)
			return;
		
		setcap(size * 2 + x);
	}
	
  public:
	~MyArray(){
		delete[] arr;
	}
	MyArray(uint capacity = 4){
		cap = capacity;
		size = 0;
		arr = new int[cap];
	}
	
	uint getCapacity() const {return cap;}
	uint getSize()     const {return size;}
	void setCapacity(uint newCap) {setcap(newCap);}
	
	MyArray& push(int x){
		checkcap();
		arr[size] = x;
		++size;
		return *this;
	}
	
	int pop(){
		if(size < 1)
			throw 1;
		--size;
		return arr[size];
	}
	
	int& operator[](uint i){
		if(i < 0 || i >= size)
			throw 1;
		return arr[i];
	}
	
	int at(uint i) const {
		if(i < 0 || i >= size)
			throw 1;
		return arr[i];
	}
	
	void setSize(uint newsize){	
		if(newsize > cap)
			setcap(newsize);
		
		for(int i=size; i<cap; ++i)
			arr[i] = 0;
		size = newsize;
	}
	
	MyArray& insert(int x, unsigned int index){
		if(index < 0 || index > size)
			throw 1;
		
		checkcap();
		++size;
		for(int i = size-1; i>index; --i)
			arr[i] = arr[i-1];
		
		arr[index] = x;
		return *this;
	}
	
	int remove(unsigned int index){
		if(index < 0 || index >= size)
			throw 1;
		
		int ret = arr[index];
		for(int i=index+1; i<size; i++)
			arr[i-1] = arr[i];
		--size;
		return ret;
	}
	
	int min() const {
		int x = arr[0];
		for(int i=1; i<size; ++i){
			if(arr[i] < x)
				x = arr[i];
		}
		return x;
	}
	
	int max() const {
		int x = arr[0];
		for(int i=1; i<size; ++i){
			if(arr[i] > x)
				x = arr[i];
		}
		return x;
	}
};

std::ostream& operator<<(std::ostream &os, const MyArray &ar){
	os << '{';
	uint n = ar.getSize();
	if(n > 0)
		os << ar.at(0);
	for(int i = 1; i < n; ++i)
		os << ", " << ar.at(i);
	os << '}';
	return os;
}

class MyArrayPlus : public MyArray{
public:
	bool has(int x){
		for(int i = 0; i<size; ++i)
			if(arr[i] = x)
				return true;
		return false;
	}
	
	void sort(){
		for(int j = 1; j < size; ++j){
			int x = arr[j];
			int i;
			for(i = j; i > 0; --j){
				if(arr[i-1] > x)
					arr[i] = arr[i-1];
				else
					break;
			arr[i] = x;
			std::cout << *this << '\n';
			}
			
		}
	}
};

void fillarray(MyArray &arr){
	using namespace std;
	cout << "Filling array!\n";
	cout << "Size ?= ";
	unsigned int size;
	cin >> size;
	
	arr.setSize(size);
	
	cout << "array << ...\n     ";
	for(int i=0; i<size; i++){
		cin >> arr[i];
	}
}

void displayhelp(){
	std::cout
	     << "d - display\n"
	     << "i - insert\n"
		 << "r - remove\n"
		 << "p - push\n"
		 << "q - swap\n"
		 << "s - sort\n"
		 << "f - find/has\n"
		 << "h - this help\n"
		 << "x - exit\n\n";
}

int main(){
	using namespace std;
	
	MyArrayPlus myarray;
	
	cout << "Array check: " << myarray << ' '
	     << "capacity = " << myarray.getCapacity() << "\n\n";
		 
	fillarray(myarray);
		   
	cout << "\nMy array is "
		 << myarray
		 << "\n    cap = "
		 << myarray.getCapacity()
		 << "\n    size = "
		 << myarray.getSize();
	cout << "\n    min " << myarray.min()
	     << "\n    max " << myarray.max() << "\n\n";
	
	displayhelp();
	
	while(true){
		char op;
		int x, i;
		
		cout << "> ";
		cin >> op;
		
		switch(op){
			case 'x':
				return 0;
			case 'h':
				displayhelp();
				break;
			case 'd':
				cout << myarray << '\n';
				break;
			case 'p':
				cout << "pushing ?= ";
				cin >> x;
				myarray.push(x);
				break;
			case 'q':
				cout << "arr[?] ";
				cin >> i;
				cout << "  ?= ";
				cin >> x;
				try{
					myarray[i] = x;
				} catch (int ex){
					cout << "ERROR\n";
				}
				break;
			case 's':
				cout << "sorting...\n";
				myarray.sort();
				break;
			case 'f':
				cout << "has ?= ";
				cin >> x;
				cout << myarray.has(x);
				break;
			case 'i':
				cout << "arr[?] ";
				cin >> i;
				cout << "  ?= ";
				cin >> x;
				try{
					myarray.insert(x, i);
				} catch(int ex){
					cout << "ERROR\n";
				}
				break;
			case 'r':
				cout << "rem arr[?] ";
				cin >> i;
				try{
					cout << "removed "
					     << myarray.remove(i);
				} catch(int ex){
					cout << "ERROR\n";
				}
				
		}
	}
}