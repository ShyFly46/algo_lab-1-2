#include <iostream>
#include <string>

using namespace std;

struct Person{
	
	int id;
	std::string name,
	       surname;
	int postalcode;
	std::string phonenumber;
	
	Person() = default;
	
	Person(int id,
	       std::string name = "Ivan",
		   std::string sname = "Ivanov",
		   std::string phone = "89991234567",
		   int postal = 123456)
	{
		setId(id);
		setName(name);
		setSurname(sname);
		setPhone(phone);
		setPostal(postal);
	}
	
	void setId(int id)            {this->id = id;}
	void setName(string name)     {this->name = name;}
	void setSurname(string sname) {this->surname = sname;}
	void setPostal(int code)      {this->postalcode = code;}
	
	void setPhone(string &numstr){
		string num;
		
		auto _end = numstr.end();
		for(auto i = numstr.begin();
		    i < _end && num.size() <= 11;
			++i)
		{
			char c = *i;
			if(c >= '0' && c <= '9'){
				num += c;
			}
		}
		
		num.resize(11, '0');
		phonenumber = num; // какая-то строчка из 11 цифр гарантированно
	}
	
	int getId()     const {return id;}
	int getPostal() const {return postalcode;}
	const string strId()      const {return to_string(id);}
	const string& strName()    const {return name;}
	const string& strSurname() const {return surname;}
	const string strPostal()  const {return to_string(postalcode);}
	const string& strPhone()   const {return phonenumber;}
	
	string toString() const {
		string str;
		str += strId() + " ";
		str += name + " ";
		str += surname + " ";
		str += phonenumber + " ";
		str += strPostal();
		return str;
	}
	
	Person* copy(){
		Person* p = new Person(id, name, surname, phonenumber, postalcode);
		return p;
	}
};

ostream& operator<<(ostream &out, const Person &p){
	out << p.toString();
	return out;
}

istream& operator>>(istream &in, Person &p){
	string name, sname, phone;
	int id, postal;
	
	in >> id >> name >> sname >> phone >> postal;
	p.setId(id);
	p.setName(name);
	p.setSurname(sname);
	p.setPhone(phone);
	p.setPostal(postal);
	
	return in;
}

struct PersonCompare{
	virtual int operator()(Person *a, Person *b) = 0;
};

struct CompID : public PersonCompare{
	int operator()(Person *a, Person *b){
		return a->getId() - b->getId();
	}
};
struct CompName : public PersonCompare{
	int operator()(Person *a, Person *b){
		return a->strName().compare(b->strName());
	}
};
struct CompSurname : public PersonCompare{
	int operator()(Person *a, Person *b){
		return a->strSurname().compare(b->strSurname());
	}
};
struct CompPhone : public PersonCompare{
	int operator()(Person *a, Person *b){
		return a->strPhone().compare(b->strPhone());
	}
};
struct CompPostal : public PersonCompare{
	int operator()(Person *a, Person *b){
		return a->getPostal() - b->getPostal();
	}
};


class PersonArray{
	Person **arr;
	size_t size;
	size_t capacity;
	
	void doubleCap(){
		size_t newcap = capacity * 2;
		Person **newar = new Person*[newcap];
		for(size_t i = 0; i < size; ++i){
			newar[i] = arr[i];
		}
		delete[] arr;
		arr = newar;
		capacity = newcap;
	}
	
  public:
	
	PersonArray(size_t cap = 16){
		capacity = cap;
		size = 0;
		arr = new Person*[cap];
	}
	
	~PersonArray(){
		for(Person *p : *this)
			delete p;
		delete[] arr;
	}
	
	Person** begin() {return arr;}
	Person** end()   {return arr + size;}
	
	PersonArray& push(Person *p){
		if(size >= capacity)
			doubleCap();
		
		arr[size++] = p;
		return *this;
	}
	
	PersonArray& operator+=(Person *p) {return push(p);}
	
	Person*& operator[](size_t i){
		if(i >= size) throw 1;
		
		return arr[i];
	}
	
	PersonArray* copy(){
		PersonArray *a = new PersonArray(capacity);
		for(Person* p : *this){
			a->push(p->copy());
		}
		return a;
	}
	
	void sort(PersonCompare *comp){
		Person** b = begin();
		Person** bb = begin();
		Person** e = end();
		
		for(++b; b < e; ++b){
			Person** i = b;
			Person* t = *b;
			for(--i; i >= bb; --i){
				if((*comp)(*i, t) > 0)
					*(i+1) = *i;
				else
					break;
			}
			*(i+1) = t;
		}
	}
};

ostream& operator<<(ostream &out, PersonArray &pa){
	out << "[\n";
	for(Person* p : pa){
		out << "    " << *p << "\n";
	}
	out << "]\n";
	return out;
}

void fillarr(PersonArray &arr){
	cout << "size? ";
	size_t size;
	cin >> size;
	
	for(size_t i = 0; i < size; ++i){
		Person *p = new Person();
		cin >> *p;
		arr.push(p);
	}
}

void printhelp(){
	cout << "\ni number -- print person\n"
	     << "s 0 -- sort by id\n"
		 << "s 1 --      by name\n"
		 << "s 2 --      by surname\n"
		 << "s 3 --      by phone\n"
		 << "s 4 --      by postal\n";
}

int main(){
	PersonArray a;
	
	fillarr(a);

	cout << a;
	printhelp();
	
	PersonCompare *comps[5]{
		new CompID(),
		new CompName(),
		new CompSurname(),
		new CompPhone(),
		new CompPostal()
	};
	
	char op;
	size_t op1;
	while(true){
		cin >> op >> op1;
		switch(op){
			case 'i':
				try{
					cout << *a[op1] << "\n";
				} catch (int e){
					cout << "error\n";
				}
				break;
			case 's':
				{
				PersonCompare *comp = comps[op1 % 5];
				PersonArray *copy = a.copy();
				copy->sort(comp);
				cout << *copy;
				delete copy;
				break;
				}
			default:
				return 0;
		}
	}
}