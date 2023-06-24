#include <iostream>
#include <cassert>

using namespace std;

class Node {
public:
    int value;
    Node *next = nullptr;
    Node *previous = nullptr;
    static int length;

    Node(int val) {
        value = val;
    }

    Node() {}

    int getValue() const {
        return value;
    }

    void setValue(int valuee) {
        value = valuee;
    }

    void setNext(Node *nextt) {
        next = nextt;
    }

    void setPrevious(Node *prev) {
        previous = prev;
    }

    static Node *find(Node *head, int val) {
        Node *curr = head;
        while (curr->next != nullptr) {
            cout << "executing  \n";
            if (curr->value == val) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    static void printNodes(Node *head) {
        Node *curr = head;
        while (curr->next != nullptr) {
            cout << "Current node's value is " << curr->value << endl;
            curr = curr->next;
        }
    }

    static void recursively(Node *head) {
        if (head != nullptr) {
            recursively(head->next);
            cout << "Current node's value is " << head->value << endl;
        }
    }

    static void printFor(Node *head) {
        int temp = 0;
        Node *curr = head;
        while (curr->next != nullptr) {
            temp++;
            curr = curr->next;
        }
        curr = head;
        for (int i = 0; i <= temp; i++) {
            cout << "curr node is " << curr->value << endl;
            curr = curr->next;
        }

    }


};



int main() {

    Node *head = new Node(1);
    Node *second = new Node(2);
    Node *third = new Node(3);
    Node *fourth = new Node(4);
    Node *tails = new Node(5);

    head->setNext(second);
    second->setNext(third);
    third->setNext(fourth);
    fourth->setNext(tails);
    tails->setNext(nullptr);

    tails->setPrevious(fourth);
    fourth->setPrevious(third);
    third->setPrevious(second);
    second->setPrevious(head);

    Node::printFor(head);


    return 0;
}
