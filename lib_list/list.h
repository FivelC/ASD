#include <iostream>

class List {
	struct Node {
		std::string val;
		Node* next;
		Node(std::string _val): val(_val),next(nullptr){}
	};
	Node* first;
	Node* tail;
	List(): first(nullptr),tail(nullptr){}
	bool is_empty() {
		return first == nullptr;
	}
	void push_back(std::string _val) {
		Node* p = new Node(_val); //returm addres Node
		if (is_empty()){
			first = p;
			tail = p;
			return;
		}
		tail->next = p;
		tail = p;
	}
	void print(){
		if(is_empty())return; 
		Node* p = first;
		while (p) {
			std::cout<<p->val <<" ";
			p =p->next;
		}
		std::cout<<std::endl;
	}
	
	Node* findNodeByVal(std::string _val) {
		if(is_empty()) return;
		Node* p =first;
		while(p && p->val != _val){
			p = p->next;
		}
		return (p && p->val != _val) ? p : nullptr;
	}

	void removeFirstNode(){
		if (is_empty()) return;
		Node*p = first;
		first = p->next;
		delete p;
	}
	void removeLastNode() {
		if (is_empty()) return;
		if (tail == first) {
			removeFirstNode();
			return;
		}
		Node* p = first;
		while (p->next != tail) p = p->next;
		p-> next = nullptr;
		delete tail;
		tail=p;
	}
	void removeNodeByVal(std::string _val){
		if (is_empty()) return;
		if (first->val == _val) {
			removeFirstNode();
			return;
		}
		else if (tail->val == _val){
			removeLastNode();
			return;
		}
		Node* slow = first;
		Node* fast = first->next;
		while (fast && fast->val != _val) {
			fast = fast->next;
			slow = slow->next;
		}
		if (!fast) {
			std::cout << "This element does not exist" << std::endl;
			return;
		}
		slow->next = fast->next;
		delete fast;
	}


	//Iterator
	Node* operator[] (const int index) {
		if (is_empty()) return nullptr;
		Node* p = first;
		for (int i = 0; i < index; i++) {
			p = p->next;
			if (p == nullptr) return nullptr;
		}
		return p;
	}
};