#include "LinkedList.h"

template<typename T>
Node<T>::Node(T val) : val(val), next(nullptr) {}

template<typename T>
Node<T>::Node(T val, Node<T>* prev, Node<T>* next) : val(val), prev(prev), next(next) {}

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
    tail_->prev = head_;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* curr = head_;
    while (curr != nullptr) {
        Node<T>* nextCurr = curr->next;
        delete curr;
        curr = nextCurr;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this == &other) {
        return *this;
    }
    Node<T>* curr = head_->next;
    while (curr != tail_) {
        Node<T>* temp = curr->next;
        delete curr;
        curr = temp;
    }
    head_->next = tail_;
    tail_->prev = head_;
    Node<T>* this_curr = head_;
    Node<T>* other_curr = other.head_->next;
    while (other_curr != other.tail_) {
        this_curr->next = new Node<T>(otherCurr->val, this_curr, nullptr);
        this_curr = this_curr->next;
        other_curr = other_curr->next;
    }
    this_curr->next = tail_;
    tail_->prev = this_curr;
    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
    tail_->prev = head_;
    Node<T>* this_curr = head_;
    Node<T>* other_curr = other.head_->next;
    while (other_curr != other.tail_) {
        this_curr->next = new Node<T>(other_curr->val, this_curr, nullptr);
        this_curr = this_curr->next;
        other_curr = other_curr->next;
    }
    this_curr->next = tail_;
    tail_->prev = this_curr;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) {
    if (empty()) {
        throw std::out_of_range("LinkedList::get_index, the LinkedList is empty");
    }
    size_type i = 0;
    Node<T>* curr = head_->next;
    while (curr != tail_) {
        if (i == index) {
            return curr->val;
        }
        curr = curr->next;
        i++;
    }
    throw std::out_of_range("LinkedList::get_index, the LinkedList does not contain the target");
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) const {
    if (empty()) {
        throw std::out_of_range("TESTING::LinkedList::get_index, the LinkedList is empty");
    }
    size_type i = 0;
    Node<T>* curr = head_->next;
    while (curr != tail_) {
        if (i == index) {
            return curr->val;
        }
        curr = curr->next;
        i++;
    }
    throw std::out_of_range("LinkedList::get_index, the LinkedList does not contain the target");
}

template<typename T>
void LinkedList<T>::push_front(const value_type& val) {
    Node<T>* old_head = head_->next;
    Node<T>* new_node = new Node<T>(val);
    
    old_head->prev = new_node;
    new_node->next = old_head;

    new_node->prev = head_;
    head_->next = new_node;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_front, the linked list is empty");
    }
    Node<T>* old_head = head_->next;
    Node<T>* new_head = old_head->next;
    head_->next = new_head;
    new_head->prev = head_;
    delete old_head;
}

template<typename T>
void LinkedList<T>::push_back(const value_type& val) {
    Node<T>* old_last = tail_->prev;
    Node<T>* new_node = new Node<T>(val, old_last, tail_);

    old_last->next = new_node;
    tail_->prev = new_node;
    
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_back, The LinkedList is empty");
    }
    Node<T>* old_last = tail_->prev;
    Node<T>* new_last = old_last->prev;
    new_last->next = tail_;
    tail_->prev = new_last;
    delete old_last;
}

template<typename T>
void LinkedList<T>::insert(const value_type& val, size_type index) {
    if (index == 0) {
        push_front(val);
    } else {
        Node<T>* curr = head_;
        size_type i = 0;
        while (curr->next != tail_ && i < index) {
            curr = curr->next;
            i++;
        }
        if (i != index) {
            throw std::out_of_range("LinkedList::insert, the index was not in range");
        }
        Node<T>* next_node = curr->next;
        Node<T>* new_node = new Node<T>(val, curr, curr->next);

        curr->next = new_node;
        next_node->prev = new_node;
    }
}

template<typename T>
void LinkedList<T>::erase(size_type index) {
    if (empty()) {
        throw std::out_of_range("LinkedList::erase, the LinkedList is empty");
    }
    Node<T>* curr = head_->next;
    Node<T>* prev = head_;
    size_type i = 0;
    while (curr != tail_ && i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == tail_) {
        throw std::out_of_range("LinkedList::erase, the index is out of range");
    }
    Node<T>* new_next = curr->next;
    new_next->prev = prev;
    prev->next = curr->next;
    delete curr;
}

template<typename T>
Node<T>* LinkedList<T>::find(const value_type& target) {
    Node<T>* curr = head_->next;
    while (curr != tail_) {
        if (curr->val == target) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
const Node<T>* LinkedList<T>::find(const value_type& target) const {
    Node<T>* curr = head_->next;
    while (curr != tail_) {
        if (curr->val == target) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}


template<typename T>
size_type LinkedList<T>::size() const {
    size_type i = 0;
    Node<T>* curr = head_;
    while (curr->next != tail_) {
        curr = curr->next;
        i++;
    }
    return i;
}

template<typename T>
bool LinkedList<T>::empty() const {
    if (head_->next == tail_) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("LinkedList::front, the LinkedList is empty");
    }
    return head_->next->val;
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("LinkedList::front, the LinkedList is empty");
    }
    return head_->next->val;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::back() {
    if (empty()) {
        throw std::out_of_range("LinkedList, the LinkedList is empty");
    }
    return tail_->prev->val;
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("LinkedList, the LinkedList is empty");
    }
    return tail_->prev->val;
}

template<typename T>
LinkedList<T>::Iterator::Iterator(Node<T>* node, Node<T>* tail) : current_node(node), tail_(tail) {}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::Iterator::operator*() {
    return current_node->val;
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    current_node = current_node->next;
    return *this;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current_node != other.current_node;
}

template<typename T>
bool LinkedList<T>::Iterator::hasNext() {
    if (current_node->next == tail_) {
        return false;
    } else {
        return true;
    }
}

template<typename T>
typename LinkedList<T>::value_type LinkedList<T>::Iterator::next() {
    current_node = current_node->next;
    return current_node->val;
}


template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return Iterator(head_->next, tail_);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return Iterator(tail_, tail_);
}

template<typename T>
void LinkedList<T>::reverse() {
    Node<T>* curr = head_;
    while (curr != nullptr) {
        Node<T>* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = temp;
    }
    Node<T>* old_head = head_;
    head_ = tail_;
    tail_ = old_head;
}

