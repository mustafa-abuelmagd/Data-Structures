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

class LinkedList {
public:
    Node *head;
    Node *tail;
    int length;


    LinkedList() {}

    LinkedList(int headVal) {
        Node *temp_head = new Node(headVal);
        head = temp_head;
        tail = temp_head;
        length++;
    }

    Node *getHead() {
        return head;
    }

    void insert_node(int val) {
        Node *temp_head = new Node(val);
        if (head == nullptr) {
            head = temp_head;
            tail = temp_head;
        } else {
            tail->next = temp_head;
            tail = temp_head;
        }
        length++;
    }

    Node *get_nth(int idx) {
        int itr = 0;
        for (Node *curr = head; curr; curr = curr->next) {
            itr++;
            if (itr == idx) {
                return curr;
            }
        }
        return nullptr;
    }

    int indexOf(int val) {
        int itr = 0;
        for (Node *temp = head; temp; temp = temp->next, itr++) {
            if (temp->value == val)
                return itr;
        }
        return -1;
    }

    int improvedSearch(int val) {
        int itr = 0;
        Node *prev = nullptr;

        for (Node *temp = head; temp; temp = temp->next, itr++) {
            if (temp->value == val) {
                if (!prev)
                    return itr;
                swap(prev->value, temp->value);
                return itr-1;
            }
            prev = temp;
        }
        return -1;
    }

    void print() {
        for (Node *temp = head; temp; temp = temp->next) {
            cout << "node " << temp->value << endl;
        }
    }

};

int main() {

    LinkedList *firstLinkedList = new LinkedList();
    firstLinkedList->insert_node(1);
    firstLinkedList->insert_node(2);
    firstLinkedList->insert_node(3);
    firstLinkedList->insert_node(4);
    firstLinkedList->insert_node(5);
    firstLinkedList->insert_node(6);
    firstLinkedList->insert_node(7);
    firstLinkedList->insert_node(8);
    cout << " gotten value " << firstLinkedList->improvedSearch(1) << endl;
    cout << " gotten value " << firstLinkedList->improvedSearch(6) << endl;
    cout << " gotten value " << firstLinkedList->improvedSearch(7) << endl;
    cout << " gotten value " << firstLinkedList->improvedSearch(8) << endl;
    cout << " gotten value " << firstLinkedList->improvedSearch(6) << endl;

    return 0;
}
