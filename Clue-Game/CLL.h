//
//  CLL.hpp
//  Clue-Game
//
//  Created by Julia on 7/30/16.
//  Copyright © 2016 Julia. All rights reserved.
//

#ifndef CLL_h
#define CLL_h

#include <stdio.h>

template <class T>
struct CLLNode {
    T item;
    CLLNode* next;
    CLLNode(T data) : item(data), next(NULL) {}
};

template <class T>
class CLL {
public:
    CLLNode<T> *head;
    CLLNode<T> *tail;
    CLL() {
        head = NULL;
        tail = NULL;
    }
    ~CLL() {
        if (head == NULL) return;
        
        CLLNode<T>* current = head;
        
        while(current->next != head) {
            CLLNode<T>* tmp = current;
            current = tmp->next;
            delete(tmp);
        }
        delete(current);
        head = NULL;
        tail = NULL;
        
    }
    
    void insertNode(CLLNode<T>* node){
        if (tail == NULL) {
            node->next = node;
            tail = node;
            head = node;
        }
        tail->next = node;
        tail = node;
        node->next = head;
    }
    int size(){
        if (head == NULL) return 0;
        int count = 1;
        CLLNode<T>* tmp = head;
        while(tmp->next != head) {
            count++;
            tmp = tmp->next;
        }
        return count;
    }

};

#endif /* CLL_h */
