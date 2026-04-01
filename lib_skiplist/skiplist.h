#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <ctime>
#include "../lib_TVector/TVector.h" 

const int maxNumberOfLevel = 5;

template <typename TKey, typename TValue>
class Node {
public:
    std::pair<TKey, TValue> data;
    TVector<Node*> next;

    Node(TKey key, TValue val, int level)
        : data(std::make_pair(key, val)) {
        next.resize(level + 1);
        for (int i = 0; i <= level; i++) {
            next[i] = nullptr;
        }
    }
};

template <typename TKey, typename TValue>
class skipList {
private:
    Node<TKey, TValue>* head;
    int currentLevel;
    Node<TKey, TValue>* find(const TKey& key, TVector<Node<TKey, TValue>*>& update) {
        Node<TKey, TValue>* current = head;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->data.first < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        return current->next[0];
    }
public:
    skipList() {
        head = new Node<TKey, TValue>(TKey(), TValue(), maxNumberOfLevel);
        currentLevel = 0;
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    void insert(TKey key, TValue value) {

        TVector<Node<TKey, TValue>*> update;
        update.resize(maxNumberOfLevel + 1);

        for (int i = 0; i <= maxNumberOfLevel; i++) {
            update[i] = nullptr;
        }

        Node<TKey, TValue>* current = find(key, update);

        if (current != nullptr && current->data.first == key) {
            current->data.second = value;
            return;
        }

        int newLevel = 0;
        while (newLevel < maxNumberOfLevel && (std::rand() % 2) == 1) {
            newLevel++;
        }

        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = head;
            }
            currentLevel = newLevel;
        }

        Node<TKey, TValue>* newNode = new Node<TKey, TValue>(key, value, newLevel);

        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    bool search(TKey key) {
        TVector<Node<TKey, TValue>*> update;
        update.resize(maxNumberOfLevel + 1);

        Node<TKey, TValue>* node = find(key, update);

        return node != nullptr && node->data.first == key;
    }

    void display() {
        std::cout << "\n---SKIP LIST---\n";
        for (int i = currentLevel; i >= 0; i--) {
            Node<TKey, TValue>* current = head->next[i];
            std::cout << "L" << i << ": [HEAD]";
            while (current != nullptr) {
                std::cout << " -> (" << current->data.first << ";" << current->data.second << ")";
                current = current->next[i];
            }
            std::cout << " -> nullptr\n";
        }
        std::cout << "-------------------------------\n";
    }
};

#endif