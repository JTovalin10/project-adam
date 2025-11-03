#include "LinkedList.h"

template<typename T>
Node<T>::Node(T val) : val(val), next(nullptr) {}

template<typename T>
Node<T>::Node(T val, Node* next) : val(val), next(next) {}

template<typename T>
LinkedList<T>::LinkedList() : size_(0) {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : size_(other.size_) {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
    Node<T>* thisCurr = head_;
    Node<T>* otherCurr = other.head_->next;
    while (otherCurr != other.tail_) {
        thisCurr->next = new Node<T>(otherCurr->val);
        thisCurr = thisCurr->next;
        otherCurr = otherCurr->next;
    }
    thisCurr->next = tail_;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other) : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = new Node<T>(T());
    other.tail_ = new Node<T>(T());
    other.size_ = 0;
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
    Node<T>* thisCurr = head_;
    Node<T>* otherCurr = other.head_->next;
    while (otherCurr != other.tail_) {
        thisCurr->next = new Node<T>(otherCurr->val);
        thisCurr = thisCurr->next;
        otherCurr = otherCurr->next;
    }
    thisCurr->next = tail_;
    size_ = other.size_;
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) {
    if (this == &other) {
        return *this;
    }
    size_ = other.size_;
    head_ = other.head_;
    tail_ = other.tail_;

    other.head_ = new Node<T>(T());
    other.tail_ = new Node<T>(T());
    other.size_ = 0;
    return *this;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) {
    if (index >= size_) {
        throw std::out_of_range("LinkedList::get_index, index is out of range");
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
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) const {
    if (index >= size_) {
        throw std::out_of_range("LinkedList::get_index, index is out of range");
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
}

template<typename T>
void LinkedList<T>::push_front(const value_type& val) {
    Node<T>* newNode = new Node<T>(val, head_->next);
    head_->next = newNode;
    size_++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_front, the linked list is empty");
    }
    Node<T>* oldHead = head_->next;
    Node<T>* newHead = oldHead->next;
    head_->next = newHead;
    delete oldHead;
    size_--;
}

template<typename T>
void LinkedList<T>::push_back(const value_type& val) {
    Node<T>* newNode = new Node<T>(val, tail_);

    Node<T>* curr = head_;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    curr->next = newNode;
    size_++;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_back, The LinkedList is empty");
    }
    Node<T>* curr = head_;
    Node<T>* prev = nullptr;
    while (curr->next != tail_) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = tail_;
    delete curr;
    size_--;
}

template<typename T>
void LinkedList<T>::insert(const value_type& val, size_type index) {
    if (index > size_) {
        throw std::out_of_range("LinkedList::insert, index is out of range");
    }
    if (index == 0) {
        push_front(val);
    } else {
        Node<T>* curr = head_;
        size_type i = 0;
        while (curr->next != tail_ && i < index) {
            curr = curr->next;
            i++;
        }
        Node<T>* newNode = new Node<T>(val, curr->next);
        curr->next = newNode;
        size_++;
    }
}

template<typename T>
void LinkedList<T>::erase(size_type index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("LinkedList::erase, the LinkedList is empty or index is out of range");
    }
    Node<T>* curr = head_->next;
    Node<T>* prev = head_;
    size_type i = 0;
    while (curr != tail_ && i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    prev->next = curr->next;
    delete curr;
    size_--;
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
typename LinkedList<T>::size_type LinkedList<T>::size() const {
    return size_;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
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
    Node<T>* curr = head_->next;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    return curr->val;
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("LinkedList, the LinkedList is empty");
    }
    Node<T>* curr = head_->next;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    return curr->val;
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
    Node<T>* prev = nullptr;
    while (curr != nullptr) {
        Node<T>* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    Node<T>* old_head = head_;
    head_ = prev;
    tail_ = old_head;
}

