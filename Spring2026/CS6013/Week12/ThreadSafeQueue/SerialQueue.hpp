#pragma once

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
class SerialQueue {

public:
   /**
    * Initializes SerialQueue with an empty, "dummy" node.
    * After init, this looks like...
    * head -> "dummy" node
    * tail ---^
    */
   SerialQueue() :
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
      Node *tmp = new Node{ x, nullptr };

      //tail_m.lock();
      tail_->next = tmp;
      tail_ = tmp;
      //tail_m.unlock();
      size_++;
   }

   /**
    * removes node from head of list and puts data into 'ret'
    *
    * @param ret
    * @return true if item dequeued, false if no item to dequeue
    */
   bool dequeue( T * ret ) {
      if ( empty() ) {
         return false;
      } else {
         // head_m.lock();
         Node * tmp = head_;
         Node * new_head = tmp->next;
         // if(new_head == NULL){
         //    head_m.unlock();
         //    return false; // nothing in queue
         // }
         *ret = new_head->data;
         head_ = new_head;
         delete tmp;
         // head_m.unlock();
         return true;
      }
   }

   ~SerialQueue() {

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

   bool empty() const { return head_ == tail_; }
};
