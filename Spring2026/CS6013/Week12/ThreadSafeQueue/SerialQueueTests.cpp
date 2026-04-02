///////////////////////////////////////////
// Created by Jonathan Pulsipher on 4/1/26.
///////////////////////////////////////////

#include "SerialQueue.hpp"
#include <assert.h>

#include "SerialQueue.hpp"
#include "ConcurrentQueue.hpp"

bool testDynamic(SerialQueue<int> *q, int n) {
    for (int i = 0; i < n; i++) {
        q->enqueue(i);
    }
    for (int i = 0; i < n; i++) {
        int test;
        assert(q->dequeue(&test));
        assert(test == i);
    }
    return true;
}

int main(int argc, char **argv) {
    //Basic queue tests - init, dequeue past full
    SerialQueue<int> *q = new SerialQueue<int>();
    assert( q->size() == 0 );

    //Enqueue
    q->enqueue(10);
    q->enqueue(20);
    q->enqueue(30);
    assert(q->size() == 3);

    //Dequeue checking values
    int ret;
    assert(q->dequeue(&ret));
    assert(ret == 10);
    assert(q->dequeue(&ret));
    assert(ret == 20);
    assert(q->dequeue(&ret));
    assert(ret == 30);

    //Dequeue past full
    assert(q->dequeue(&ret) == false);

    assert(testDynamic(q, 1000));
}

