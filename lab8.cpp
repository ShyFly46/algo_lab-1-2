#include <iostream>
#include <string>

class HashTable{
	struct List{
		std::string data;
		int key;
		List *next;
		
		List(std::string data, int key, List *next = nullptr){
			this->data = data;
			this->key  = key;
			this->next = next;
		}
	};
	
	List *arr[256];
	
	int hash(int key){
		return (key * 997) % 256;
	}
	
public:
	HashTable(){
		for(int i = 0; i < 256; ++i){
			arr[i] = nullptr;
		}
	}
	
	bool isOccupied(int key){
		int i = hash(key);
		for(List *r = arr[i]; r; r = r->next){
			if(r->key == key)
				return true;
		}
		return false;
	}
	
	void push(std::string data, int key){
		int i = hash(key);
		if(isOccupied(key))
			return;
		arr[i] = new List(data, key, arr[i]);
	}
	
	std::string pop(int key){
		int i = hash(key);
		List **prev = &arr[i];
		for(List *cur = arr[i]; cur; prev = &(cur->next), cur = cur->next){
			if(cur->key == key){
				*prev = cur->next;
				std::string ret = cur->data;
				delete cur;
				return ret;
			}
		}
			
		return "";
	}
	
	std::string peek(int key){
		int i = hash(key);
		for(List *cur = arr[i]; cur; cur = cur->next){
			if(cur->key == key){
				return cur->data;
			}
		}
			
		return "";
	}
	
	void display(){
		using namespace std;
		
		for(int i = 0; i < 256; ++i){
			for(List *l = arr[i]; l; l = l->next){
				cout << l->key << "\t "
				     << l->data << "\n";
			}
		}
	}
};

int main(){
	using namespace std;
	
	HashTable ht;
	
	char op;
	int ii;
	string str;
	
	while(true){
		cin >> op;
		switch(op){
			case 'i':
			case 'p':
				cin >> ii >> str;
				ht.push(str, ii);
				break;
				
			case 'o':
				cin >> ii;
				str = ht.pop(ii);
				cout << ii << ": "
				     << str << " removed\n";
				break;
				
			case 'q':
				cin >> ii;
				str = ht.peek(ii);
				cout << ii << ": "
				     << str << "\n";
				break;
				
			case 'd':
				ht.display();
				break;
				
			case 'x':
				return 0;
				
			default:
				break;
		}
	}
}