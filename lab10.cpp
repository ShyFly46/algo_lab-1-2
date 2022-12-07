#include <iostream>

struct Tree{
	struct Node{
		int data;
		Node *left;
		Node *right;
		
		Node(int data){
			this->data = data;
			left = nullptr;
			right = nullptr;
		}
	};
	
	Node *root;
	
	void add(int data){
		Node *cur = root;
		Node **prev = &root;
		
		while(cur){
			if(data <= cur->data){
				*prev = &(cur->left);
				cur = cur->left;
			} else {
				*prev = &(cur->right);
				cur = cur->right;
			}
		}
		
		*prev = new Node(data);
	}
	
	static Tree* createBalanced(int nodes){
		if(nodes <= 0)
			return nullptr;
		
		if(nodes == 1)
			return new Node(0);
		
		Tree *tree = new Node(0);
		int right = (int)(nodes - 1) / 2;
		int left  = nodes - 1 - left;
		
		tree->left  = createBalanced(left);
		tree->right = createBalanced(right);
		
		return tree;
	}
	
	void removeNode(Node *del, Node **prev){
		if(!del->left){
			*prev = del->right;
			delete del;
			return;
		}
		
		List *leftmost = del->left;
		List **lptr = &(del->left);
		
		while(leftmost->right){
			lptr = &(leftmost->right);
			leftmost = leftmost0->right;
		}
		
		del->data = leftmost->data;
		*lptr = leftmost->left;
		delete leftmost;
	}
	
	List *peek(int data){
		Node *cur = root;
		
		while(cur){
			if(data == cur->data)
				return cur;
		
			if(data < cur->data)
				cur = cur->left;
			else
				cur = cur->right;
		}
			
		return nullptr;
	}
	
	void remove(int data){
		Node *cur = root;
		Node **prev = &root;
		
		while(cur){
			if(data == cur->data){
				removeNode(cur, prev);
				return;
			}
			
			if(data < cur->data){
				prev = &(cur->left);
				cur = cur->left;
			} else {
				prev = &(cur->right);
				cur = cur->right;
			}
		}
	}
	
	void displayLCR(Node *t){
		if(!t) return;
		displayLCR(t->left);
		std::cout << t->data << " ";
		displayLCR(t->right);
	}
	void displayCLR(Node *t){
		if(!t) return;
		std::cout << t->data << " ";
		displayCLR(t->left);
		displayCLR(t->right);
	}
	void displayLRC(Node *t){
		if(!t) return;
		displayLRC(t->left);
		displayLRC(t->right);
		std::cout << t->data << " ";
	}
	
	void display(int type = 0){
		type %= 3;
		
		switch(type){
			case 0:
				displayLCR(root);
				return;
			case 1:
				displayCLR(root);
				return;
			case 2:
				displayLRC(root);
				return;
		}
	}
};

int main(){
	
}