#include <iostream>
#include <cmath>

bool is_palindrome(unsigned int number) {
    std::string str = std::to_string(number);
    unsigned int n = str.length();
    for(int i = 0; i < n / 2; i++) {
        if(str[i] != str[n - i - 1])
            return false;
    }
    return true;
}

bool is_primal(unsigned int number) {
    if (number < 2) {
        return false;
    } 
    if (number == 2) {
        return true;
    }
    if (number % 2 == 0) {
        return false;
    }
    for(int i = 3; i <= sqrt(number); i+=2) {
        if(number % i == 0)
            return false;
    }
    return true;
}

struct node {
    unsigned int value;
    node* next = nullptr;
};

struct linkedList {
    node* first = nullptr;

    bool is_empty();
    void add(unsigned int value);
    void print();
    void sort();
    bool has_palindromes();
    void delete_primal();
    void double_elements();
    ~linkedList();
};


int main() {
    linkedList list;
    /*list.add(17);
    list.add(1);
    list.add(13);
    list.add(12);
    list.add(11);
    list.add(15);*/

    unsigned int n;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        unsigned int value;
        std::cin >> value;
        list.add(value);
    }
    if(not list.has_palindromes()) {
        list.sort();
    }
    else {
        list.delete_primal();
        list.double_elements();
    }
    list.print();
    return 0;

}

bool linkedList::is_empty() {
    return  (first == nullptr);
}

void linkedList::add(unsigned int value)  {
    node* newNode = new node {value};
    if (is_empty()) {
        first = newNode;
    }
    else {
        node* current = first;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        }
}

void linkedList::print() {
    node* current = first;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void linkedList::sort() {
    if (is_empty())
        return;
    bool swapped;
    do {
        swapped = false;
        node* current = first;
        while (current->next != nullptr) {
            if (current->value < current->next->value) {
                std::swap(current->value, current->next->value);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    
}

bool linkedList::has_palindromes() {
    node* current = first;
    if(is_palindrome(first->value))
        return true;
    while (current != nullptr) {
        if(is_palindrome(current->value))
            return true;
        current = current->next;
    }
    return false;
}

void linkedList::delete_primal() {
    if(is_empty())
        return;
    node* current = first;
    node* previous = nullptr;

    while (current != nullptr) {
        if(is_primal(current->value)) {
            if(previous == nullptr) {
                first = current->next;
                delete current;
                current = first;
            }
            else {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}

void linkedList::double_elements() {
    if(is_empty())
        return;
    node* current = first;
    while (current != nullptr) {
        node* newNode = new node{current->value, current->next};
        current->next = newNode;
        current = newNode->next;
    }
}

linkedList::~linkedList() {
    node* current = first;
    node* nextNode = current->next;
    while (current != nullptr) {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}