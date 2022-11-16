#include <cstdio>
#include <string>

struct Token{
	int i;
	char t;
};

void setTokeni(Token *t, int i){
	t->i = i;
	t->t = '0';
}
void setToken(Token *t, char op){
	t->t = op;
}



Token infix[128];
Token rpolish[128];
char strin[256];

void tokenize(char *in, Token *out);
void outputTokens(Token *ts);
void toRPolish(Token *tin, Token *tout);
int compute(Token *tin);

int main(){
	using namespace std;
	
	scanf("%255[^\n]", strin);
	strin[255] = '\0';
	
	//printf("%s\n", strin);
	
	tokenize(strin, infix);
	toRPolish(infix, rpolish);
	
	outputTokens(rpolish);
	
	int result = compute(rpolish);
	printf(" = %d\n", result);

}

int compute(Token *tin){
	int ns[128];
	int *x = ns;
	
	for(Token *t = tin; t->t; ++t){
		char op = t->t;
		if(op == '0'){
			*(x++) = t->i;
		} else {
			if(x - 2 < ns){
				printf("\nERROR, bad rpolish\n");
				throw 1;
			}
			int a = *(x-2);
			int b = *(x-1);
			x -= 2;
			
			switch(op){
				case '+':
					*x = a + b;
					break;
				case '-':
					*x = a - b;
					break;
				case '*':
					*x = a * b;
					break;
				case '/':
					*x = a / b;
					break;
				case '^':
					int r = 1;
					for(; b > 0; --b)
						r *= a;
					*x = r;
					break;
			}
			++x;
		}
	}
	
	if(x != ns + 1){
		printf("\nERROR, bad rpolish\n");
		throw 1;
	}
	
	return ns[0];
}

// a > b --> +123
int compPrec(char a, char b);

void toRPolish(Token *tin, Token *tout){
	char opstack[128];
	char *s = opstack;
	
	for(Token *i = tin; i->t; ++i){
		switch(char tt = i->t){
			case '0':
				*(tout++) = *i;
				break;
				
			case '(':
				*(s++) = tt;
				break;
				
			case ')':
				while(s > opstack && *(s-1) != '('){
					(tout++)->t = *(--s);
				}
				if(s <= opstack){
					printf("\nERROR, no open bracket\n");
					throw 1;
				}
				--s; // discard '('
				break;
				
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				while(s > opstack &&
				      *(s-1) != '(' &&
					  compPrec(*(s-1), tt) >= 0)
				{
					(tout++)->t = *(--s);
				}
				*(s++) = tt;
				break;
				
			default:
				break;
		}
	}
	
	while(s > opstack){
		(tout++)->t = *(--s);
		if(*s == '('){
			printf("\nERROR, no close bracket\n");
			throw 1;
		}
	}
}

int precedence(char t){
	switch(t){
		case '+':
		case '-': return 2;
		case '*':
		case '/': return 3;
		case '^': return 4;
		default: return -1;
	}
}

// a > b --> +123
int compPrec(char a, char b){
	return precedence(a) - precedence(b);
}

void tokenize(char *strbuf, Token *tbuf){
	Token *p = tbuf;
	
	for(char *c = strbuf; *c; ++c){
		if(*c >= '0' && *c <= '9'){
			int x = 0;
			for(; *c &&
				  *c >= '0' &&
				  *c <= '9'
				; ++c)
			{
				x *= 10;
				x += *c - '0';
			}
			setTokeni(p++, x);
			--c;
			continue;
		}
		
		switch(*c){
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
			case '(':
			case ')':
				setToken(p++, *c);
				break;
				
			case ' ':
			default:
				continue;
		}
	}
	
	setToken(p, '\0');	
}

void outputTokens(Token *ts){
	for(Token *p = ts; p->t; ++p){
		if(p->t == '0')
			printf("%d ", p->i);
		else
			printf("%c ", p->t);
	}
	printf("\n");
}