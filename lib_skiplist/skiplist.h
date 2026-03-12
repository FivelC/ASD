#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include "../lib_TVector/TVector.h"
const int maxNumberOfLevel = 5;
class Node
{
public:

    int data;
    std::vector<Node*> next;  
    Node(int data, int Level) : data(data), next(Level + 1, nullptr) {} 
};

class skipList {
private:
    Node* head;
    int Level;

public:
    skipList::skipList()
    {
        head = new Node(0, maxNumberOfLevel);    

        Level = 0;                             

    }

    void skipList::insert(int data)
    {
        int newLevel = 0;

        while (newLevel < maxNumberOfLevel && (rand() % 2) == 1) 
        {
            newLevel++;
        }

        if (Level < newLevel)
        {
            head->next.resize(newLevel + 1);

            Level = newLevel;
        }


        Node* current = head;


        std::vector<Node*> Update(Level + 1);

        for (int i = Level; i >= 0; i--)
        {

            while (current->next[i] && current->next[i]->data < data)
            {
                current = current->next[i];
            }

            Update[i] = current;

        }

        current = current->next[0];

        if (current == nullptr || current->data != data) 
        {
            Node* newNode = new Node(data, Level);

            for (int i = 0; i <= newLevel; i++)
            {
                newNode->next[i] = Update[i]->next[i];

                Update[i]->next[i] = newNode; 

            }

            std::cout << "Element " << data << " inserted successfully.\n";
        }
        else
        {
           std:: cout << "Element " << data << " already exists.\n";  
        }
    }

    bool skipList::search(int data)
    {
        Node* current = head;           


        for (int i = Level; i >= 0; i--) 
        {
            while (current->next[i] && current->next[i]->data < data) 
            {
                current = current->next[i]; 

            }
        }

        current = current->next[0];
    }

    void skipList::display()
    {

        std::cout << "skip List:" << std::endl;

        for (int i = Level; i >= 0; i--) // 
        {
            Node* current = head->next[i];

            std::cout << "Level " << i << ": ";

            while (current != nullptr)
            {
                std::cout << current->data << " ";
                current = current->next[i];
            }
            std::cout << std::endl;
        }
    }

};
#endif