#pragma once
#include <string>
#include <iostream>

using namespace std;

template <typename data, typename key_value = string>
class unordered_table {
private:
	struct node {
		key_value key;
		data value;
		node* next;
		node(key_value k, data v, node* n = nullptr) {
			key = k;
			value = v;
			next = n;
		}
	};
	node* head;
	node* last;
public:
	unordered_table();
	unordered_table(key_value k, data v);
	void add(key_value key, data value);
	data find(key_value key);
	~unordered_table();

};

template <typename data, typename key_value> unordered_table<data, key_value>::unordered_table() {
	head = nullptr;
	last = nullptr;
}

template <typename data, typename key_value> unordered_table<data, key_value>::unordered_table(key_value k, data v) {
	head = new node(k, v);
	last = head;
}

template <typename data, typename key_value> void unordered_table<data, key_value>::add(key_value key, data value) {
	if (head == nullptr) {
		last = new node(key, value);
		head = last;
	}
	else {
		last->next = new node(key, value);
		last = last->next;
	}
}

template <typename data, typename key_value> data unordered_table<data, key_value>::find(key_value key) {
	node* iterator = head;
	data result;
	if (head != nullptr) {
		while (iterator != nullptr) {
			if (head->key == key) {
				result = head->value;
				head = head->next;
				delete iterator;
				return result;
			}
			else if((iterator->next == last) && (last->key == key)) {
				data result = last->value;
				delete last;
				last = iterator;
				last->next = nullptr;
				return result;
			}
			else if ((iterator->next != nullptr) && (iterator->next->key == key)) {
				result = iterator->next->value;
				node* remember_node = iterator->next->next;
				delete iterator->next;
				iterator->next = remember_node;
				
				return result;
			}
			iterator = iterator->next;
		}
	}
	else {
		cout << "table is empty" << endl;
	}
}

template <typename data, typename key_value> unordered_table<data, key_value>::~unordered_table() {
	node* iterator = head;
	node* victim;
	while (iterator != nullptr) {
		victim = iterator;
		iterator = iterator->next;
		delete victim;
	}
}
