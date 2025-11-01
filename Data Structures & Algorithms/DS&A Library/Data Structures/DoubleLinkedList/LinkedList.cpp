#include <cstddef>        // for std::size_t
#include <stdexcept>      // for std::out_of_range (throws)

template<typename T>
Node<T>::Node(value_type val) : val(val) {}

template<typename T>
Node<T>::Node(value_type, Node<value_type>* prev, Node<value_type>* next) : val(val), prev(prev), next(next) {}

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = new Node(T());
    tail_ = new Node(T());
    head->next = tail_;
    tail_->prev = head_;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    LinkedList<T> curr = head_;
    while (curr != nullptr) {
        LinkedList<T> temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head_ = new Node(T());
    tail_ = new Node(T());
    head_->next = tail_;
    tail_->prev = head_;
    ListNode<T>* curr = other.head_->next;
    ListNode<T>* copy = head_;
    while (curr != other.tail_) {
        ListNode<T>* newNode = new ListNode(curr->val);
        newNode->prev = copy;
        copy->next = newNode;
        
    }
    tail_->prev = curr;
    curr->next = tail_;
    size_ = other.size_;
}