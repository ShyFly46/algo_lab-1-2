#include <iostream>

template<typename T>
struct List{
	T v;
	List *n;
	
	List(T v, List<T> *prev){
		this->v = v;
		if(prev)
			prev->n = this;
		n = nullptr;
	}
	
	List(T v){
		this->v = v;
		n = nullptr;
	}
	
	List(){n = nullptr;}
};

class ListMatrix{
	List<List<int>*> *rows;
	int width, hight;
	
	void initsize(int h, int w){
		if(h < 1 || w < 1) throw 1;
		
		width = w;
		hight = h;
		
		List<List<int>*> *newMatrix, *rr;
		List<int> *c, *cc;
		
		newMatrix = nullptr;
		c = nullptr;
		
		//std::cout << h << " " << w << "\n";
		
		for(int i = 0; i < h; ++i) {
			
			for(int j = 0; j < w; ++j){
				//std::cout << i << " " << j << "\n";
				
				cc = new List<int>(0);
				cc->n = c;
				c = cc;
			}
			
			rr = new List<List<int>*>(c);
			rr->n = newMatrix;
			newMatrix = rr;
			c = nullptr;
		}
		
		rows = newMatrix;
	}
	
  public:
	ListMatrix(int h, int w){
		initsize(h, w);
	}
	
	void fill(){
		List<List<int>*> *r = rows;
		List<int> *c;
		
		while(r){
			c = r->v;
			while(c){
				int x;
				std::cin >> x;
				c->v = x;
				c = c->n;
			}
			
			r = r->n;
		}
	}
	
	void multiply(ListMatrix *a, ListMatrix *b){
		if(a->hight != this->hight ||
		   b->width != this->width ||
		   a->width != b->hight) throw 1;
		   
		int depth = a->width;
		
		for(int i = 0; i < hight; ++i){
			for(int j = 0; j < width; ++j){
				int res = 0;
				
				for(int k = 0; k < depth; ++k){
					res += a->at(i, k) * b->at(k, j);
				}
				
				this->at(i, j) = res;
			}
		}
	}
	
	int& at(int x, int y){
		if(x < 0 || y < 0) throw 1;
		
		List<List<int>*> *r = rows;
		List<int> *c;
		
		for(int i = 0; i < x; ++i){
			r = r->n;
		}
		
		c = r->v;
		
		for(int j = 0; j < y; ++j){
			c = c->n;
		}
		
		return c->v;
	}
	
	void display(){
		List<List<int>*> *r = rows;
		List<int> *c;
		
		while(r){
			c = r->v;
			while(c){
				std::cout << c->v << " ";
				c = c->n;
			}
			std::cout << "\n";
			r = r->n;
		}
	}
};

int main(){
	using namespace std;
	
	int m, n, l;
	cin >> m >> n >> l;
	
	ListMatrix *a = new ListMatrix(m, n);
	ListMatrix *b = new ListMatrix(n, l);
	ListMatrix *c = new ListMatrix(m, l);
	
	a->fill();
	b->fill();
	
	c->multiply(a, b);
	
	c->display();
	
	//cout << a->at(1,1);
}