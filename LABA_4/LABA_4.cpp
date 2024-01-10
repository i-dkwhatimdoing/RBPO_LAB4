#include <iostream>
#include <new>

template <typename T>
class StackBasedOnBidirectionalLinkedList {
private:
    template <typename T>
    class Node {
    public:
        T info;
        Node* plus;
        Node* form;
        Node(T info = T(), Node* plus = nullptr, Node* form = nullptr) {
            this->info = info;
            this->plus = plus;
            this->form = form;
        }
    };
    Node<T>* max;
    int size;
public:
    int GetSize() const {
        return size;
    };
    void clear();
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element) const;
    StackBasedOnBidirectionalLinkedList();
    StackBasedOnBidirectionalLinkedList(const StackBasedOnBidirectionalLinkedList<T>& other);
    StackBasedOnBidirectionalLinkedList(StackBasedOnBidirectionalLinkedList<T>&& other);
    StackBasedOnBidirectionalLinkedList(std::initializer_list<T> ilist);
    ~StackBasedOnBidirectionalLinkedList();
    StackBasedOnBidirectionalLinkedList<T>& operator=(const StackBasedOnBidirectionalLinkedList<T>& other);
    StackBasedOnBidirectionalLinkedList<T>& operator=(StackBasedOnBidirectionalLinkedList<T>&& other);
    StackBasedOnBidirectionalLinkedList<T>& operator=(std::initializer_list<T> ilist);
};

template<typename T>
StackBasedOnBidirectionalLinkedList<T>::StackBasedOnBidirectionalLinkedList() {
    size = 0;
    max = nullptr;
}

template<typename T>
StackBasedOnBidirectionalLinkedList<T>::~StackBasedOnBidirectionalLinkedList() {
    clear();
}


template <typename T>
StackBasedOnBidirectionalLinkedList<T>::StackBasedOnBidirectionalLinkedList(const StackBasedOnBidirectionalLinkedList<T>& other) : max(nullptr), size(0) {
    *this = other;
}

template <typename T>
StackBasedOnBidirectionalLinkedList<T>::StackBasedOnBidirectionalLinkedList(std::initializer_list<T> ilist) : max(nullptr), size(0) {
    *this = ilist;
}

template <typename T>
StackBasedOnBidirectionalLinkedList<T>::StackBasedOnBidirectionalLinkedList(StackBasedOnBidirectionalLinkedList<T>&& other) : max(nullptr), size(0) {
    *this = std::move(other);
}

template <typename T>
StackBasedOnBidirectionalLinkedList<T>& StackBasedOnBidirectionalLinkedList<T>::operator=(StackBasedOnBidirectionalLinkedList<T>&& other) {
    if (this != &other) {
        clear();
        max = other.max;
        size = other.size;
        other.max = nullptr;
        other.size = 0;
    }
    return *this;
}

template<typename T>
bool StackBasedOnBidirectionalLinkedList<T>::Push(const T& element) {
    Node<T>* newNode = new(std::nothrow) Node<T>(element);
    if (newNode == nullptr) {
        return false;
    }
    if (size > 0) {
        newNode->plus = newNode;
    }
    max = newNode;
    size++;
    return true;
}

template <typename T>
StackBasedOnBidirectionalLinkedList<T>& StackBasedOnBidirectionalLinkedList<T>::operator=(std::initializer_list<T> ilist) {
    clear();
    for (const T& item : ilist) {
        Push(item);
    }
    return *this;
}

template<typename T>
bool StackBasedOnBidirectionalLinkedList<T>::Pop(T& element) {
    if (max == nullptr) {
        return false;
    }
    element = max->info;
    Node<T>* toDelete = max;
    if (size == 1) {
        max->form = nullptr;
    }
    else {
        max = toDelete->plus;
    }
    delete toDelete;
    --size;
    return true;
}

template <typename T>
StackBasedOnBidirectionalLinkedList<T>& StackBasedOnBidirectionalLinkedList<T>::operator=(const StackBasedOnBidirectionalLinkedList<T>& other) {
    if (this != &other) {
        clear();
        if (other.max != nullptr) {
            Node<T>* currentOther = other.max->plus;
            do {
                if (!Push(currentOther->info)) {
                    clear();
                    throw std::bad_alloc();
                }
                currentOther = currentOther->plus;
            } while (currentOther != other.max->plus);
        }
    }
    return *this;
}


template<typename T>
void StackBasedOnBidirectionalLinkedList<T>::clear() {
    Node<T>* plusNode;
    while (size > 0) {
        plusNode = max->plus;
        delete max;
        max = plusNode;
        --size;
    }
    max = nullptr;
    max = nullptr;
}

template<typename T>
bool StackBasedOnBidirectionalLinkedList<T>::Peek(T& element) const {
    if (max == nullptr) {
        return false;
    }
    element = max->info;
    return true;
}


int main() {
    return 0;
}