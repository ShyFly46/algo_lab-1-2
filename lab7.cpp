#include <iostream>

template<typename T>
struct List{
	T v;
	List *n;
	
	List(T v, List<T> *prev = nullptr){
		this->v = v;
		if(prev)
			prev->n = this;
		n = nullptr;
	}
	
	List(){n = nullptr;}
	
	~List(){
		if(n) delete n;
	}
};

class ListMatrix{
	List<List<int>*> *rows;
	
	List<int>* fillrow(size_t w){
		List<int> *ret = new List<int>;
		List<int> *cur = ret;
		
		int t;
		std::cin >> t;
		cur->v = t;
		
		for(size_t i = 1; i < w; ++i){
			std::cin >> t;
			cur = new List<int>(t, cur);
		}
		
		return ret;
	}
	
  public:
	void fill(size_t h, size_t w){
		rows = new List<List<int>*>(fillrow(w));
		
		List<List<int>*> *cur = rows;
		for(size_t i = 1; i < h; ++i){
			cur = new List<List<int>*>(fillrow(w), cur);
		}
	}
	
	void display(){
		List<List<int>*> *ll = rows;
		while(ll){
			List<int> *l = ll->v;
			while(l){
				std::cout << l->v << " ";
				l = l->n;
			}
			std::cout << "\n";
			
			ll = ll->n;
		}
	}
	
	int pop(size_t i, size_t j){
		List<List<int>*>
		for()
	}
};

int main(){
	ListMatrix *a = new ListMatrix;
	
	a->fill(3, 4);
	a->display();
}