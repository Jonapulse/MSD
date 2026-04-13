//
// Created by Jonathan Pulsipher on 4/1/26.
//

#ifndef THREADSAFEQUEUE_CONCURRENTQUEUE_H
#define THREADSAFEQUEUE_CONCURRENTQUEUE_H

#pragma once
#include <mutex>

////////////////////////////////////////////////////////////////////////
//
// Author: Jon Pulsipher
// Date: 4/1/26
//
// CS 6013
//
// Outline for SerialQueue class.  Fill in the missing data, comments, etc.
//
////////////////////////////////////////////////////////////////////////

template <typename T>
class ConcurrentQueue {

public:
    /**
     * Initializes SerialQueue with an empty, "dummy" node.
     * After init, this looks like...
     * head -> "dummy" node
     * tail ---^
     */
    ConcurrentQueue() :
       head_( new Node{ T{}, nullptr } ), size_( 0 )
    {
        tail_ = head_;
    }

    /**
     * Adds 'x' to the tail of the list
     * After first enqueue, this looks like...
     * head -> "dummy" -> new Node
     * tail --------------^
     * @param x
     */
    void enqueue( const T & x ) {
        std::unique_lock<std::mutex> my_lock(tail_m);

        Node *tmp = new Node{ x, nullptr };

        //std::unique_lock<std::mutex> my_lock(tail_m);
        tail_->next = tmp;
        tail_ = tmp;
        size_++;
    }

    /**
     * removes node from head of list and puts data into 'ret'
     *
     * @param ret
     * @return true if item dequeued, false if no item to dequeue
     */
    bool dequeue( T * ret ) {
        std::unique_lock<std::mutex> my_lock(head_m);
        if ( empty() ) {
            return false;
        } else {
            Node * tmp = head_;
            Node * new_head = head_->next;
            *ret = new_head->data;
            head_ = new_head;
            size_--;
            my_lock.unlock(); //Release before the end because delete is thread-safe)
            delete tmp;
            return true;
        }
    }

    ~ConcurrentQueue() {

        while( head_ != nullptr ) {
            Node* temp = head_->next;
            delete head_;
            head_ = temp;
        }
    }

    int size() const { return size_; }

private:

    struct Node {
        T      data;
        Node * next;
    };

    Node * head_; //My 'dummy' node
    Node * tail_;
    int    size_;
    std::mutex head_m; //lock for critical sections w/ head
    std::mutex tail_m; //lock for critical sections w/ tail

    bool empty() const { return head_ == tail_; }
};

#endif //THREADSAFEQUEUE_CONCURRENTQUEUE_H