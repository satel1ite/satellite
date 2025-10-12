#include <iostream>
#include <string>

struct Node {
    int value;
    Node* next;
};

Node* AddNodeAtHead(Node* head, Node* node) {
    node->next = head;
    return node;
}

Node* DelNodeAtHead(Node* head) {
    if (head == nullptr) return nullptr;
    Node* newHead = head->next;
    delete head;
    return newHead;
}

Node* ReverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main() {
    Node* head = nullptr;
    std::string command;
    while (std::cin >> command) {
        if (command == "add") {
            int value;
            std::cin >> value;
            Node* newNode = new Node{value, nullptr};
            head = AddNodeAtHead(head, newNode);
        } else if (command == "del") {
            head = DelNodeAtHead(head);
        } else if (command == "reverse") {
            head = ReverseList(head);
        } else if (command == "print") {
            for (Node* curr = head; curr != nullptr; curr = curr->next) {
                std::cout << curr->value << "\n";
            }
        }
    }
    return 0;
}
