#include <iostream>
#include <cassert>

using namespace std;

//class Vector {
//private:
//    int *arr = nullptr;
//    int size = 0;
//    int capacity = 0;
//public:
//    Vector(int size) : size(size) {
//        if (size < 0) size = 1;
//        capacity = size * 2;
//        arr = new int[capacity]{};
//    }
//
//    ~Vector() {
//        delete[] arr;
//        arr = nullptr;
//    }
//
//    int get_size() {
//        return size;
//    }
//
//    int get(int idx) {
//        assert(0 <= idx && idx <= size);
//        return arr[idx];
//    }
//
//    void set(int idx, int val) {
//        assert(0 <= idx && idx <= size);
//        arr[idx] = val;
//    }
//
//    void print() {
//        for (int i = 0; i < capacity; i++) {
//            cout << arr[i] << "  ";
//            cout << "\n";
//        }
//    }
//
//    int find(int val) {
//        for (int i = 0; i < size; i++) {
//            if (arr[i] == val) return i;
//        }
//        return -1;
//    }
//
//    int get_front() {
//        return arr[0];
//    }
//
//    int get_last() {
//        return arr[size - 1];
//    }
//
//    void resize() {
//        capacity *= 2;
//        int *new_arr = new int[capacity]{};
//        for (int i = 0; i < size; i++) {
//            new_arr[i] = arr[i];
//        }
//        swap(arr, new_arr);
//        delete[] new_arr;
//    }
//
//    void insert(int pos, int val) {
//        if (size + 1 == capacity) resize();
//        arr[size++] = arr[size];
//        for (int i = size + 1; i > pos; i--) {
//            arr[i] = arr[i - 1];
//        }
//        arr[pos] = val;
//    }
//
//    void rotate_right(int times) {
//        int actual_times = times % size;
//        for (int i = 0; i < actual_times; i++) {
//            rotate_right_once();
//        }
//
//    }
//
//    void rotate_right_once() {
//        int latest = arr[size - 1];
//        for (int i = size - 1; i > 0; i--) {
//            arr[i] = arr[i - 1];
//        }
//        arr[0] = latest;
//    }
//
//    void rotate_left(int times) {
//        int actual_times = times % size;
//        for (int i = 0; i < actual_times; i++) {
//            rotate_left_once();
//        }
//
//    }
//
//    void rotate_left_once() {
//        int first = arr[0];
//        for (int i = 0; i < size; i++) {
//            arr[i] = arr[i + 1];
//        }
//        arr[size - 1] = first;
//    }
//
//    void push_back(int val) {
//        if (size == capacity) {
//            cout << "resizing... \n ";
//            resize();
//        }
//        arr[size++] = val;
//    }
//
//    void removeElement(int pos) {
//        for (int i = pos; i < size; i++) {
//            arr[i - 1] = arr[i];
//        }
//        arr[size] = 0;
//
//    }
//
//    int find_transposition(int value) {
//        for (int i = 0; i < size; i++) {
//            if (arr[i] == value && i - 1 >= 0) {
//                int temp = arr[i - 1];
//                arr[i - 1] = arr[i];
//                arr[i] = temp;
//                return i;
//
//            }
//        }
//        return -1;
//    }
//
//
//};

class Node {
public:
    int value;
    Node *next = nullptr;
    Node *previous = nullptr;
    static int length;

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

    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();
    Node *fourth = new Node();
    Node *tails = new Node();


    head->setValue(1);
    second->setValue(2);
    third->setValue(3);
    fourth->setValue(4);
    tails->setValue(5);

    head->setNext(second);
    second->setNext(third);
    third->setNext(fourth);
    fourth->setNext(tails);
    tails->setNext(nullptr);

    tails->setPrevious(fourth);
    fourth->setPrevious(third);
    third->setPrevious(second);
    second->setPrevious(head);


//    recursively(head);

//    cout << "value  " << Node::find(head, 3);
    Node::printFor(head);


    return 0;
}
