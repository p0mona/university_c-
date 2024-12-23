//Task 2

#include <iostream>
#include <memory>
#include <string>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;

        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}

    void addFirst(const T& e) {
        auto newNode = std::make_shared<Node>(e);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addLast(const T& e) {
        auto newNode = std::make_shared<Node>(e);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void removeFirst() {
        if (!head) {
            throw std::runtime_error("Deque is empty.");
        }
        head = head->next;
        if (head) {
            head->prev.reset();
        } else {
            tail.reset();
        }
    }

    void removeLast() {
        if (!tail) {
            throw std::runtime_error("Deque is empty.");
        }
        tail = tail->prev;
        if (tail) {
            tail->next.reset();
        } else {
            head.reset();
        }
    }

    T getFirst() const {
        if (!head) {
            throw std::runtime_error("Deque is empty.");
        }
        return head->data;
    }

    T getLast() const {
        if (!tail) {
            throw std::runtime_error("Deque is empty.");
        }
        return tail->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        auto current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

int main() {
 Deque<std::string> deque;
 deque.addFirst("My name");
 deque.addLast("is Polina");
 std::cout << "First: " << deque.getFirst() << std::endl;
 std::cout << "Last: " << deque.getLast() << std::endl;
 
 deque.removeFirst();
 std::cout << "First after removing: " << deque.getFirst() << std::endl;
 
 deque.removeLast();
 std::cout << "Is deque empty? " << (deque.isEmpty() ? "Yes" : "No") << std::endl;
 
 return 0;
 }
 
