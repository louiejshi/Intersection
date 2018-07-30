//
//  main.cpp
//  Intersection
//
//  Created by Louie Shi on 7/30/18.
//  Copyright © 2018 Louie Shi. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"

using namespace std;

class Result
{
public:
    ListNode* tail;
    int size;

    Result()
    {
        tail = NULL;
        size = 0;
    }
    
    Result(ListNode* t, int s)
    {
        tail = t;
        size = s;
    }
    
    ListNode* getTail()
    {
        return tail;
    }
    
    int getSize()
    {
        return size;
    }
};

Result* sizeAndTail(ListNode* ln)
{
    Result* result = new Result();
    ListNode* ptr;
    
    // Default initialization if given empty LinkedList
    if(!ln)
    {
        return result;
    }
    
    for(ptr = ln; ptr; ptr=ptr->getNext())
    {
        (result->size)++;
        if(ptr->getNext() == NULL)
        {
            result->tail = ptr;
        }
    }
    return result;
}

ListNode* makeLengthtoShort(ListNode* ln, int length)
{
    ListNode* ptr = ln;
    
    for(int i = 0; i < length; i++)
    {
        ptr = ptr->getNext();
    }
    
    return ptr;
}

ListNode* intersection(ListNode* ln1, ListNode* ln2)
{
    Result* tail1 = new Result();   //Stores tail pointer + size
    Result* tail2 = new Result();   //Stores tail pointer + size
    
    int cutLength = 0;      //How much to move the head pointer in longer LinkedList
    
    ListNode* shorter;      //Points to the shorter LinkedList
    ListNode* longer;       //Points to the longer LinkedList
    ListNode* longListStart;    //Points to the same starting point as the shorter LinkedList
    
    if((ln1 == NULL) || (ln2 == NULL))
    {
        return NULL;
    }
    else
    {
        tail1 = sizeAndTail(ln1);
        tail2 = sizeAndTail(ln2);
        
        if(tail1->tail == tail2->tail)  // The 2 LinkedLists intersect
        {
            shorter = tail1->size < tail2->size ? ln1: ln2;
            longer = tail1->size < tail2->size ? ln2: ln1;
        }
        else    //The 2 LinkedLists DONT INTERSECT
        {
            return NULL;
        }
        
        cutLength = tail1->size < tail2->size ? (tail2->size - tail1->size):(tail1->size - tail2->size);
        
        longListStart = makeLengthtoShort(longer, cutLength);
        
        //Loop to find the intersecting LinkedList
        while(longListStart && shorter)
        {
            if(longListStart->getData() == shorter->getData())
            {
                return shorter;
            }
            longListStart = longListStart->getNext();
            shorter = shorter->getNext();
        }
    }
    return NULL;
}

int main(int argc, const char * argv[])
{
    LinkedList* ls1 = new LinkedList();
    LinkedList* ls2 = new LinkedList();
    
    ListNode* result;
    
    ListNode* ln1 = new ListNode(1);
    ListNode* ln1A = new ListNode(1);
    ListNode* ln2 = new ListNode(2);
    ListNode* ln3 = new ListNode(3);
    ListNode* ln4 = new ListNode(4);
    ListNode* ln5 = new ListNode(5);
    ListNode* ln6 = new ListNode(6);
    ListNode* ln7 = new ListNode(7);
    ListNode* ln9 = new ListNode(9);
    
    ls1->insertEnd(ln3);
    ls1->insertEnd(ln1);
    ls1->insertEnd(ln5);
    ls1->insertEnd(ln9);
    ls1->insertEnd(ln7);
    ls1->insertEnd(ln2);
    ls1->insertEnd(ln1A);

    cout << "LinkedList 1 Values: " << endl;
    ls1->print();
    cout << endl;
    
    ls2->insertEnd(ln4);
    ls2->insertEnd(ln6);
    ls2->insertEnd(ln7);
    
    cout << "LinkedList 2 Values: " << endl;
    ls2->print();
    cout << endl;
    
    //Begin of Intersection Code
    result = intersection(ls1->head, ls2->head);
    
    cout << "Intersection Node: " << result->getData() << endl;
    cout << endl;
    
    return 0;
}
