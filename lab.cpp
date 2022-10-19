#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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
	
	int* begin() {return arr;}
	int* end()   {return arr + size;}
	const int* cbegin() const {return arr;}
	const int* cend()   const {return arr + size;}
	
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
		
//		for(int i=size; i<cap; ++i)
//			arr[i] = 0;
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

void printarr(const int *b, const int *e, std::ostream &out){	
	out << "[";
	
	for(; b < e; ++b){
		out << *b << " ";
	}
	
	out << "]\n";
}

void printarr(const int *b, const int *e){
	printarr(b, e, std::cout);
}

std::ostream& operator<<(std::ostream &out, const MyArray &ar){
	printarr(ar.cbegin(), ar.cend(), out);
	return out;
}

struct Sort{
	virtual void sort(int *begin, int *end) = 0;
	const char* name() {return "null";}
};

struct SortInsertion : public Sort {
	const char* name() {return "Insertion";}
	
	void sort(int *begin, int *end) override {
		for(int *j = begin+1; j < end; ++j){
			int x = *j;
			int *i;
			for(i = j; i > begin; --i){
				if(*(i-1) > x)
					*i = *(i-1);
				else
					break;
			}
			*i = x;
		}
	}
};
Sort* const SORT_INSERT = new SortInsertion();

struct SortFast : public Sort {
	const char* name() {return "Fast";}
	
	void sort(int *begin, int *end) override {
		if(begin >= end-1)
			return;
		
		//printarr(begin, end);
		
		int *b = begin,
		    *e = end - 1;
		bool onright = false;
		
		while(b < e){
			if(*b > *e){
				int t = *e;
				*e = *b;
				*b = t;
				
				onright = !onright;
			}
			
			if(onright){
				// pivot on right, compared against left
				++b;
			} else {
				// pivot on left, compare against right
				--e;
			}
		}
		
		//printarr(begin, end);
		
		// b == e, on pivot
		sort(begin, b);
		sort(b+1, end);
	}
};
Sort* const SORT_FAST = new SortFast();

struct MyArrayPlus : public MyArray {
	bool has(int x){
		for(int i = 0; i<size; ++i)
			if(arr[i] == x)
				return true;
		return false;
	}
	
	bool sorted() const {
		const int *end_ = cend();
		for(const int *i = cbegin()+1; i < end_; ++i){
			if(*(i-1) > *i)
				return false;
		}
		return true;
	}
	
	void removedoubles(){
		if(!sorted())
			return;
		
		int *end_ = end();
		int x = arr[0];
		int *i = begin() + 1;
		
		while(*i != x && i < end_){
				x = *i;
				++i;
			}
		// первый дубликат
			
		int *j = i; // j <= i
		
		while(i < end_){
			while(*i == x)
				++i;
			if(i >= end_)
				break;
			x = *j = *i;
			++j;
			++i;
		}
		
		int newsize = j - begin();
		setSize(newsize);
	}

	friend class Sorter;
	
	void sort(Sort *algo){
		using namespace std;
		
		cout << algo->name() << " sort\n";
		
		clock_t startt, endt;
		startt = clock();
		
		algo->sort(begin(), end());
		
		endt = clock();
		double time_taken = double(endt - startt) / double(CLOCKS_PER_SEC);
		
		cout << "sorted " //<< *this
		     << "\nin " << fixed
			 << time_taken << " seconds\n" << setprecision(5);
	}
	
	void sort(){
		sort(SORT_INSERT);
	}
};




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
		 << "o - random array\n"
		 << "v - remove doubles\n"
		 << "x - exit\n\n";
}

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

void fillarrayrandom(MyArray &arr){
	using namespace std;
	cout << "Filling array!\n";
	
	unsigned int size;
	cout << "Size ?= ";
	cin >> size;
	
	int min, max;
	cout << "Min ?= ";
	cin >> min;
	cout << "Max ?= ";
	cin >> max;
	
	
	arr.setSize(size);
	for(int i=0; i<size; i++){
		arr[i] = min + rand() % max;
	}
}


int main(){
	srand(time(0));
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
			case 'o':
				fillarrayrandom(myarray);
				break;
			case 'v':
				myarray.removedoubles();
				break;
			case 's':
				cout << "how?"
				     << "\n i - insert"
					 << "\n f - fast"
					 << "\n> ";
					 
				Sort *mysort;
				cin >> op;
				switch(op){
					case 'i':
						mysort = SORT_INSERT;
						break;
					case 'f':
						mysort = SORT_FAST;
						break;
				}
				myarray.sort(mysort);
				break;
			case 'f':
				cout << "has ?= ";
				cin >> x;
				cout << ((myarray.has(x)) ? "true\n" : "flase\n");
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