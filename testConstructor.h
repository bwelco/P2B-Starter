//
// Created by fengguang on 10/14/21.
//

#ifndef TEST_CONSTRUCTOR_H
#define TEST_CONSTRUCTOR_H


#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Eecs281PQ.h"
#include "BinaryPQ.h"
#include "UnorderedPQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"

#include <time.h>
#include <stdlib.h>
#include "testConstructor.h"

using namespace std;

void testConstructor() {
    // range
    vector<int> vec;

    int arr[10] = {1, 4, 2, 9, 7, 8, 3, 5, 6, 10};
    for (int i = 0; i < 10; ++i) {
        vec.push_back(arr[i]);
    }

    Eecs281PQ<int> *pq1 = new PairingPQ<int>(vec.begin(), vec.end());

    assert(!pq1->empty());

    for (int i = 10; i >= 1; --i) {
        assert(pq1->top() == i);
        pq1->pop();
    }

    Eecs281PQ<int> *pq2 = new PairingPQ<int>(vec.begin(), vec.end() - 1);
    assert(!pq2->empty());

    for (int i = 9; i >= 1; --i) {
        assert(pq2->top() == i);
        pq2->pop();
    }

    SortedPQ<int> *pq3 = new SortedPQ<int>(vec.begin(), vec.end());
    for (int i = 10; i >= 1; --i) {
        assert(pq3->top() == i);
        pq3->pop();
    }

    BinaryPQ<int> *pq4 = new BinaryPQ<int>(vec.begin(), vec.end());
    for (int i = 10; i >= 1; --i) {
        assert(pq4->top() == i);
        pq4->pop();
    }


    // empty
    Eecs281PQ<int> *pq5 = new PairingPQ<int>();

    for (int i = 10; i >= 1; --i) {
        pq5->push(arr[i - 1]);
    }

    for (int i = 10; i >= 1; --i) {
        assert(pq5->top() == i);
        pq5->pop();
    }

    SortedPQ<int> *pq6 = new SortedPQ<int>();

    for (int i = 10; i >= 1; --i) {
        pq6->push(arr[i - 1]);
    }

    for (int i = 10; i >= 1; --i) {
        assert(pq6->top() == i);
        pq6->pop();
    }

    BinaryPQ<int> *pq7 = new BinaryPQ<int>();
    for (int i = 10; i >= 1; --i) {
        pq7->push(arr[i - 1]);
    }

    for (int i = 10; i >= 1; --i) {
        assert(pq7->top() == i);
        pq7->pop();
    }
}

#endif // TEST_CONSTRUCTOR_H
