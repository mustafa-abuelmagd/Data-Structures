#include <iostream>
#include <cassert>
#include <climits>

#include <vector>        // for debug
#include <algorithm>
#include <sstream>

using namespace std;

struct Node {
    int value{};
    Node *next{};

    Node(int value) : value(value) {}

    ~Node() {
        cout << "Destroy value: " << value << " at address " << this << "\n";
    }
};
//class Node {
//public:
//    int value;
//    Node *next = nullptr;
//    Node *previous = nullptr;
//    static int length;
//
//    Node(int val) {
//        value = val;
//    }
//
//    Node() {}
//
//    int getValue() const {
//        return value;
//    }
//
//    void setValue(int valuee) {
//        value = valuee;
//    }
//
//    void setNext(Node *nextt) {
//        next = nextt;
//    }
//
//    void setPrevious(Node *prev) {
//        previous = prev;
//    }
//
//    static Node *find(Node *head, int val) {
//        Node *curr = head;
//        while (curr->next != nullptr) {
//            cout << "executing  \n";
//            if (curr->value == val) return curr;
//            curr = curr->next;
//        }
//        return nullptr;
//    }
//
//    static void printNodes(Node *head) {
//        Node *curr = head;
//        while (curr->next != nullptr) {
//            cout << "Current node's value is " << curr->value << endl;
//            curr = curr->next;
//        }
//    }
//
//    static void recursively(Node *head) {
//        if (head != nullptr) {
//            recursively(head->next);
//            cout << "Current node's value is " << head->value << endl;
//        }
//    }
//
//    static void printFor(Node *head) {
//        int temp = 0;
//        Node *curr = head;
//        while (curr->next != nullptr) {
//            temp++;
//            curr = curr->next;
//        }
//        curr = head;
//        for (int i = 0; i <= temp; i++) {
//            cout << "curr node is " << curr->value << endl;
//            curr = curr->next;
//        }
//
//    }
//
//
//};

class LinkedList {
private:
    Node *head{};
    Node *tail{};
    int length = 0;    // let's maintain how many nodes

    vector<Node *> debug_data;    // add/remove nodes you use

    void debug_add_node(Node *node) {
        debug_data.push_back(node);
    }

    void debug_remove_node(Node *node) {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:
    LinkedList() {}

    LinkedList(int headVal) {
        Node *temp_head = new Node(headVal);
        head = temp_head;
        tail = temp_head;
        length++;
    }

    ~LinkedList() {
        for (int i = 0; i < debug_data.size(); i++) {
            delete_node(debug_data[i]);
        }

    }


    Node *getHead() {
        return head;
    }

    void insert_front(int val) {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        length++;
        debug_data.insert(debug_data.begin(), newNode);
    }

    void delete_front() {
        Node *deletedHead = head;
        cout << "Deleting node with value: " << deletedHead->value << endl;
        head = head->next;
        debug_remove_node(deletedHead);
        length--;
    }

    void print() {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->value << " ";
        cout << "\n";
    }

    void delete_node(Node *node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node *node) {
        debug_add_node(node);
        ++length;
    }

    void insert_end(int value) {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }

    int get_nth_from_back(int idx) {
        int real_idx = length - idx;
        if (real_idx < 0)return -1;
        return debug_data[real_idx]->value;
    }

    bool is_same_node(Node *node1, Node *node2) {
        if (node1 && node2) return node1->value == node2->value;
        if (!node1) return !node2;
    }

    bool is_same(LinkedList &list2) {
        if (length == 0 || list2.length == 0) {
            cout << "exited here 1" << endl;
            return (length == list2.length
                     && is_same_node(head, list2.head));
        }
        Node *temp2 = list2.head;
        for (Node *temp = head; temp; temp = temp->next) {
            if (!is_same_node(temp, temp2)) {
                cout << "value1 " << temp->value << " value2 " << temp2->value << endl;
                return false;
            }
            temp2 = temp2->next;

        }
        return true;
    }

    bool is_same_no_len_or_tail(LinkedList &list2) {
        if (!is_same_node(head, list2.head)) {
            cout << "exited here 1" << endl;
            return false;
        }
        Node *temp2 = list2.head;
        for (Node *temp = head; temp; temp = temp->next) {
            if (!is_same_node(temp, temp2)) {
                cout << "value1 " << temp->value << " value2 " << temp2->value << endl;
                return false;
            }
            temp2 = temp2->next;

        }
        return true;
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
                return itr - 1;
            }
            prev = temp;
        }
        return -1;
    }

    LinkedList(const LinkedList &) = delete;

    LinkedList &operator=(const LinkedList &another) = delete;

    void debug_print_address() {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->value << "\t";
        cout << "\n";
    }

    void debug_print_node(Node *node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }
        cout << node->value << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->value << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }

    void debug_print_list(string msg = "") {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int) debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n" << flush;
    }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node *cur = head; cur; cur = cur->next) {
            oss << cur->value;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        } else {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);    // Consider infinite cycle?
        assert(length == len);
        assert(length == (int) debug_data.size());
    }
};

void test1() {
    cout << "\n\ntest1\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);

    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);

    cout << "Gotten from back 1st " << list.get_nth_from_back(1) << endl;
    cout << "Gotten from back 2nd " << list.get_nth_from_back(2) << endl;
    cout << "Gotten from back 3rd " << list.get_nth_from_back(3) << endl;

    // some actions
    list.print();
    // must see it, otherwise RTE    // must see it, otherwise RTE


    string expected = "3 2 1 1 2 3";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
    list.debug_verify_data_integrity();
}

void test3() {
    cout << "\n\ntest3\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);

    LinkedList list2;
    list2.insert_end(1);
    list2.insert_end(2);
    list2.insert_end(3);
    // some actions
    list.is_same_no_len_or_tail(list2);
    // must see it, otherwise RTE    // must see it, otherwise RTE


    string expected = list.debug_to_string();
    string result = list2.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
    list.debug_verify_data_integrity();
}

void test4() {
    cout << "\n\ntest4\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);

    LinkedList list2;
    list2.insert_end(1);
    list2.insert_end(2);
    list2.insert_end(3);
    list2.insert_end(4);

    // some actions
    cout << "result 1 is " << list.is_same(list2) << endl;
    bool result1 = list.is_same_no_len_or_tail(list2);
    assert (result1);


    string expected = list.debug_to_string();
    string result = list2.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
    list2.debug_print_list("********");
    list.debug_verify_data_integrity();
}

void test5() {
    cout << "\n\ntest5\n";
    LinkedList list;


    LinkedList list2;
    cout << "Not here " << "\n";
    bool result1 = list.is_same_no_len_or_tail(list2);
    cout << "might come here with result " << result1 << "\n";
    if (!result1) {
        cout << "can it be here? " << result1 << "\n";

        assert (false);
    }


//    string expected = list.debug_to_string();
//    string result = list2.debug_to_string();
//    if (expected != result) {
//        cout << "no match:\nExpected: " <<
//             expected << "\nResult  : " << result << "\n";
//        assert(false);
//    }
//    list.debug_print_list("********1");
//    list2.debug_print_list("********2");
    list.debug_verify_data_integrity();
    list2.debug_verify_data_integrity();
}


int main() {

//    LinkedList *firstLinkedList = new LinkedList();
//    firstLinkedList->insert_node(1);
//    firstLinkedList->insert_node(2);
//    firstLinkedList->insert_node(3);
//    firstLinkedList->insert_node(4);
//    firstLinkedList->insert_node(5);
//    firstLinkedList->insert_node(6);
//    firstLinkedList->insert_node(7);
//    firstLinkedList->insert_node(8);



//    test1();
    test3();
    test4();
    test5();
    cout << "\n\nNO RTE\n";
    return 0;
}
