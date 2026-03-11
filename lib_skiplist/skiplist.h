#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include "../lib_TVector/TVector.h"
#define LEVEL 5
template <class TKey,class TVal>
class SkipList {
	struct Node {
		std::pair<TKey, TVal> data;
		TVector<Node*> next;
		Node(const TKey& key, const TVal& value, int level)
			: data(key, value), next(level + 1, nullptr) {}
	};

	Node* _head;
	int _level;

public:
	skipList(){
		_head = new Node(0, LEVEL);
		_level = 0;
	}
    void insert(int data)
    {
        int newLevel = 0;

        while (newLevel < maxNumberOfLevel && (rand() % 2) == 1)
        {
            newLevel++;
        }

        if (_level < newLevel)
        {
            _head->next.resize(newLevel + 1);

            _level = newLevel;
        }


        Node* current = _head;


        TVector<Node*> Update(Level + 1, nullptr);

        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] and current->next[i]->data < data)
            {
                current = current->next[i];
            }
            Update[i] = current;

        }

        current = current->next[0];

        if (current == nullptr or current->data != data)
        {
            Node* newNode = new Node(data, Level);

            for (int i = 0; i <= newLevel; i++)
            {
                newNode->next[i] = Update[i]->next[i];

                Update[i]->next[i] = newNode;

            }

            cout << "Element " << data << " inserted successfully.\n";
        }
        else
        {
            cout << "Element " << data << " already exists.\n";
        }
    }
	void remove(int data);
	bool find(int data);
	void print();
};
#endif