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

    void debug_add_node_pos(Node *node, int idx) {
        debug_data.insert(debug_data.begin() + idx, node);
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

    LinkedList(const LinkedList &) = delete;

    LinkedList &operator=(const LinkedList &another) = delete;

    ~LinkedList() {
        while (head) {
            Node *temp = head->next;
            delete head;
            head = temp;
        }

    }


    Node *getHead() {
        return head;
    }

    Node *getTail() {
        if (head == nullptr) return nullptr;
        return debug_data[debug_data.size() - 1];
    }

    void insert_end_no_tail(int val) {
        Node *newNode = new Node(val);
//        cout << "came here" << getTail()->value << endl;
        if (head == nullptr) {
            head = newNode;
        }

        if (!debug_data.empty()) getTail()->next = newNode;
        debug_data.push_back(newNode);
    }

    void insert_front(Node *newNode) {
        newNode->next = head;
        head = newNode;
        length++;
        if (length == 1) {
            tail = head;
        }
        debug_data.insert(debug_data.begin(), newNode);
    }

    void delete_first() {
        Node *deletedHead = head;
        head = head->next;
        delete_node(deletedHead);
        if (!head) tail = nullptr;
        debug_verify_data_integrity();
    }

    void delete_last() {
        if (length <= 1) {
            delete_first();
            return;
        }
        Node *newTail = get_nth(length - 1);
        delete_node(tail);
        tail = newTail;
        tail->next = nullptr;
        debug_verify_data_integrity();
    }

    void detach_head() {
        Node *deletedHead = head;
        head = head->next;
        deletedHead->next = nullptr;
        if (!head) tail = nullptr;
        debug_remove_node(deletedHead);
        --length;
    }

    void detach_tail() {
        Node *newTail = get_nth(length - 1);
        tail = newTail;
        tail->next = nullptr;
        debug_remove_node(tail);
        --length;
    }

    void delete_nth(int idx) {
        if (idx < 1 || idx > length) {
            cout << "\nError:: Invalid index to delete \n";
            return;
        }
        if (idx == 1) {
            delete_first();
            return;
        }
        if (idx == length) {
            delete_last();
            return;
        }
        Node *nth_previous = get_nth(idx - 1);
        Node *nth = nth_previous->next;
        nth_previous->next = nth_previous->next->next;
        delete_node(nth);
        debug_verify_data_integrity();
    }

    void delete_next_node(Node *node) {
        Node *node_to_delete = node->next;
        node->next = node_to_delete->next;
        if (is_same_node(node_to_delete, tail)) {
            delete_last();
            return;
        }
        delete_node(node_to_delete);
    }

    void delete_by_key(int val) { //O(n) time, o(1) space
        if (!head) {
            cout << "Error:: LinkedList is empty\n";
            return;
        }
        int itr = 1;

        for (Node *curr = head; curr; curr = curr->next, itr++) {
            if (curr->value == val) {
                delete_nth(itr);
                return;
            }
        }
        cout << "Error: No key found" << endl;
        debug_verify_data_integrity();
    }

    int get_by_key(int val) { //O(n) time, o(1) space
        int itr = 0;
        for (Node *curr = head; curr; curr = curr->next, itr++) {
            if (curr->value == val) return itr;
        }
    }

    void delete_by_key_alt(int val) {
        if (!head) {
            cout << "Error:: LinkedList is empty\n";
            return;
        }

        for (Node *curr = head; curr; curr = curr->next) {
            if (curr->next->value == val) {
                delete_next_node(curr->next);
                return;
            }
        }
        cout << "Error: No key found" << endl;
        debug_verify_data_integrity();
    }

    void swap_pairs() {
        if (!head) {
            cout << "Error:: LinkedList is empty\n";
            return;
        }
        for (Node *curr = head; curr; curr = curr->next->next) {
            if (curr->next != nullptr) {
                int temp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = temp;
            }
            if (!curr->next)return;
        }
        cout << "STATE:: came here\n";

        debug_verify_data_integrity();
    }

    void swap_pairs_alt() {
        if (!head) {
            cout << "Error:: LinkedList is empty\n";
            return;
        }
        for (Node *curr = head; curr; curr = curr->next) {
            if (curr->next) {
                swap(curr->next->value, curr->value);
                curr = curr->next;
            }
        }
        cout << "STATE:: came here\n";

        debug_verify_data_integrity();
    }

    void reverse() {
        if (length == 0) {
            cout << "ERROR:: No Nodes Dummy!" << endl;
            return;
        }
        if (length == 1) {
            cout << "ERROR:: length of one Linked lists are the same when reversed" << endl;
            return;
        }
        head->next = nullptr;
        for (int i = 1; i < length; i++) { // We used one since we're linking backwards. 1->0, 0->-1 is wrong
            debug_data[i]->next = debug_data[i - 1];
        }
        std::reverse(debug_data.begin(), debug_data.end());
        Node *tempNode = head;
        head = tail;
        tail = tempNode;
        print();
        debug_verify_data_integrity();
    }

    void reverse_alt() {
        if (length == 0) { cout << "Empty list\n"; }
        if (length == 1) { cout << "Head is tail and tail is head\n"; }
        tail = head;
        Node *prev = head;
        while (head) {
            Node *next = head->next;
            head->next = prev;

            prev = head;
            head = next;
        }
        head = prev;
        tail->next = nullptr;
        debug_verify_data_integrity();

    }

    void delete_even_positions() {
        if (length <= 1) {
            cout << "Invalid Operation\n";
            return;
        }
        for (Node *temp = head; temp; temp = temp->next) {
            if (temp->next) {
                delete_next_node(temp);
            }
        }
        debug_verify_data_integrity();
    }

    void delete_even_positions_alt() {
        if (length <= 1) {
            cout << "Invalid Operation\n";
            return;
        }
        for (Node *curr = head->next, *prev = head; curr;) {
            delete_next_node(prev);
            if (!prev->next) {
                break;
            }
            curr = prev->next->next;
            prev = prev->next;
        }
        debug_verify_data_integrity();
    }

    void insert_node_between(Node *node1, Node *node2, Node *newNode) {
        if (!node1) insert_front(newNode);

        else if (!node2) insert_end(newNode);

        else {
            newNode->next = node2;
            node1->next = newNode;
            add_node_pos(newNode, get_by_key(newNode->value));
        }
        return;
    }

    void insert_sorted(Node *newNode) {
        if (length == 0) insert_end(newNode);

        else if (length == 1) {
            if (head->value > newNode->value) insert_front(newNode);
            else insert_end(newNode);
        } else {
            for (Node *curr = head->next, *prv = head; curr;) {
                if (prv->value > newNode->value) {
                    insert_node_between(nullptr, curr, newNode);
                    break;
                } else if (is_same_node(curr, tail) && curr->value < newNode->value) {
                    insert_node_between(prv, nullptr, newNode);
                    break;
                } else if (prv->value < newNode->value && newNode->value < curr->value) {
                    insert_node_between(prv, curr, newNode);
                    break;
                }

                curr = prv->next->next;
                prv = prv->next;

            }
        }
        debug_verify_data_integrity();
    }

    void swap_head_and_tail() {
        if (!length)return;
        else if (length == 1) {
            cout << "Already done\n";
            return;
        } else {
            Node *prv_head = head;
            Node *prv_tail = tail;
            detach_tail();
            detach_head();
            cout << "prv head is " << prv_head->value << "and next is" << prv_head->next << endl;
            cout << "prv tail is " << prv_tail->value << "and next is" << prv_tail->next << endl;
            insert_front(prv_tail);
            insert_end(prv_head);
        }
        debug_verify_data_integrity();
    }

    void rotate_k_times(int k) {
        int actual_k = k % length;
        for (int i = 0; i < actual_k; i++) {
            rotate_once();
        }
    }

    void rotate_once() {
        Node *newTail = get_previous(tail);
        tail->next = head;
        head = newTail->next;
        tail = newTail;
        tail->next = nullptr;
        debug_data.insert(debug_data.begin(), head);
        debug_data.erase(debug_data.end() - 1);
    }

    void remove_duplicates() {
        for (Node *curr = head; curr; curr = curr->next) {
            for (Node *curr2 = head; curr2; curr2 = curr2->next) {
                if (curr2->next && curr2->next->value == curr->value) {
                    delete_next_node(curr2);
                }
            }
        }
        debug_verify_data_integrity();
    }


    Node *get_previous(Node *target) {        // O(n) time - O(1) memory
        for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
            if (cur == target)    // memory wise
                return prv;
        }
        return nullptr;    // still more steps needed - NOT found
    }

    void swap_head_and_tail_alt() {
        if (!length)return;
        else if (length == 1) {
            cout << "Already done\n";
            return;
        } else {
            Node *prv_head = head;
            tail->next = head->next;
            Node *pTail = get_previous(tail);
            pTail->next = head;
            head->next = nullptr;
            head = tail;
            tail = prv_head;
        }
        debug_verify_data_integrity();
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

    void add_node_pos(Node *node, int idx) {
        debug_add_node_pos(node, idx);
        ++length;
    }

    void insert_end(Node *item) {
        add_node(item);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }

    int get_nth_from_back(int idx) {
        return get_nth(length - idx + 1)->value;
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

//void test1() {
//    cout << "\n\ntest1\n";
//    LinkedList list;
//
//    list.insert_end(1);
//    list.insert_end(2);
//    list.insert_end(3);
//    list.insert_end(4);
//    list.insert_end(5);
//
//    list.delete_first();
//    list.delete_last();
//    list.delete_nth(2);
//
//
//    cout << "came here" << endl;
//
//    // some actions
//    list.print();
//    // must see it, otherwise RTE    // must see it, otherwise RTE
//
//
//    string expected = "2 4";
//    string result = list.debug_to_string();
//    if (expected != result) {
//        cout << "no match:\nExpected: " <<
//             expected << "\nResult  : " << result << "\n";
//        assert(false);
//    }
//    list.debug_print_list("********");
//}

void test3() {
    cout << "\n\ntest3\n";
    LinkedList list;

    list.insert_end(new Node(0));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(4));
    list.insert_end(new Node(4));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(7));

    list.remove_duplicates();
    string expected = "0 2 4 6 7";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
    list.debug_verify_data_integrity();
}


int main() {
//    test1();
    test3();
//    test4();
    cout << "\n\nNO RTE\n";
    return 0;
}
