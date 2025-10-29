#include "LinkedList.h"

template<typename T>
Node<T>::Node(T val) : val(val), next(nullptr) {}

template<typename T>
Node<T>::Node(T val, Node* next) : val(val), next(next) {}

template<typename T>
LinkedList<T>::LinkedList() {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
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
    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head_ = new Node<T>(T());
    tail_ = new Node<T>(T());
    head_->next = tail_;
    Node<T>* thisCurr = head_;
    Node<T>* otherCurr = other.head_->next;
    while (otherCurr != other.tail_) {\
        thisCurr->next = new Node<T>(otherCurr->val);
        thisCurr = thisCurr->next;
        otherCurr = otherCurr->next;
    }
    thisCurr->next = tail_;
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
    Node<T>* newNode = new Node<T>(val, head_->next);
    // We want to grab the old head_
    head_->next = newNode;
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
}

template<typename T>
void LinkedList<T>::push_back(const value_type& val) {
    Node<T>* newNode = new Node<T>(val, tail_);

    Node<T>* curr = head_;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    curr->next = newNode;
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
        Node<T>* newNode = new Node<T>(val, curr->next);
        curr->next = newNode;
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
    prev->next = curr->next;
    delete curr;
}

template<typename T>
bool LinkedList<T>::remove(const value_type& target) {
    if (empty()) {
        return false;
    }
    int items_removed = 0;
    Node<T>* curr = head_->next;
    while (curr != tail_ && curr->val == target) {
        Node<T>* temp = curr->next;
        delete curr;
        curr = temp;
        items_removed++;
    }
    if (items_removed != 0) {
        head_->next = curr;
    }

    while (curr != tail_ && curr->next != tail_) {
        if (curr->next->val == target) {
            Node<T>* temp = curr->next->next;
            delete curr->next;
            curr->next = temp;
            items_removed++;
        } else {
            curr = curr->next;
        }
    }

    if (items_removed == 0) {
        return false;
    } else {
        return true;
    }
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
LinkedList<T>::Iterator::Iterator(Node<T>* node) : current_node(node) {}

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
void LinkedList<T>::reverse() {
    Node<T>* curr = head_->next;
    Node<T>* prev = head_;
    while (curr != tail_) {
        Node<T>* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
}

