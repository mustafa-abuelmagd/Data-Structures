#include <iostream>
#include <cassert>
#include <climits>

#include <vector>        // for debug
#include <algorithm>
#include <sstream>
#include <chrono>


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
        if (length <= 1) return;

        Node *prv = nullptr;
        for (Node *crr = head; crr;) {
            Node *nxt = crr->next;
            crr->next = prv;
            prv = crr;
            crr = nxt;
        }
        tail = head;
        head = prv;
        debug_verify_data_integrity();
    }


    static LinkedList *reverse(LinkedList *list) {
        if (list->length == 0) {
            cout << "Empty list\n";
            return nullptr;
        }
        if (list->length == 1) {
            cout << "Head is tail and tail is head\n";
            return list;
        }
        auto *newList = new LinkedList();
        list->reverse();

        for (Node *curr = list->head; curr; curr = curr->next) {
            insert_end(newList, curr);
        }
        list->reverse();
        return newList;
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
        if (length == 0 || length == 1) {
            cout << "ERROR:: Unable to reverse." << endl;
        }
        for (Node *curr = head; curr; curr = curr->next) {
            for (Node *curr2 = curr->next, *prv = curr; curr2;) {
                if (prv->value == curr2->value) {
                    delete_next_node(prv);
                    curr2 = prv->next;
                }
                prv = curr2;
                curr2 = curr2->next;
            }
        }
        debug_verify_data_integrity();
    }

    void remove_last_occurrence(int key) {
        if (length == 0 || length == 1) {
            cout << "ERROR:: Unable to reverse." << endl;
        }
        reverse();
        for (Node *prv = head, *curr = head->next;
             curr, prv;) {
            if (curr->value == key) {
                delete_next_node(prv);
                reverse();
                return;
            }
            curr = curr->next, prv = prv->next;
        }
        reverse();
        debug_verify_data_integrity();
    }

    void remove_last_occurrence_alt(int key) {
        Node *prv_node_to_delete = nullptr;
        bool is_found = false;
        for (Node *temp = head, *prv = nullptr; temp; prv = temp, temp = temp->next) {
            if (temp->value == key) {
                is_found = true;
                prv_node_to_delete = prv;
            }
        }
        if (is_found) {
            if (prv_node_to_delete) {
                delete_next_node(prv_node_to_delete);
            } else {
                delete_first();
            }
        }
        debug_verify_data_integrity();
    }

    Node *move_to_end(Node *prv, Node *curr) {
        Node *next = curr->next;
        tail->next = curr;

        if (prv) {
            prv->next = curr->next;
        } else {//curr was head
            head = next;
        }
        tail = curr;
        tail->next = nullptr;
        return next;
    }

    void move_to_back(int key) {
        int len = length;
        for (Node *curr = head, *prv = nullptr; len--;) {
            if (curr->value == key) {
                curr = move_to_end(prv, curr);
            } else {
                prv = curr;
                curr = curr->next;
            }

        }
        debug_verify_data_integrity();
    }

    int getMax(Node *head, int max) {
        if (!head->next) {
            int currMax = std::max(head->value, max);
            return currMax;
        } else return std::max(head->value, getMax(head->next, max));

    }

    // Homework 4
    // Arrange Odd positions to the first
    void arrange_odd_positions() {
        if (length <= 2)return;
        Node *tempTail = head; // use to insert node between or insert after
        for (Node *prv = head; prv; prv = prv->next) {
            if (prv != head && prv->next) {
                Node *detached = detach_next_node(prv);
                insert_node_between(tempTail, tempTail->next, detached);
                tempTail = tempTail->next;
            }

        }
        debug_verify_data_integrity();
    }

    void arrange_odd_even() {
        if (length <= 2)return;
        Node *curr_odd = head;
        Node *curr_even = head->next;
        while (curr_odd->next && curr_odd->next->next) {
            Node *next_even = curr_odd->next;
            curr_odd->next = curr_odd->next->next;
            next_even->next = next_even->next->next;
            curr_odd = curr_odd->next;
            if (length % 2 == 1) {
                tail = next_even;
            }
        }
        curr_odd->next = curr_even;
        debug_verify_data_integrity();

    }

    Node *detach_next_node(Node *node) {
        Node *node_to_detach = node->next;
        node->next = node_to_detach->next;
        if (is_same_node(node_to_detach, tail)) {
            node->next = nullptr;
            detach_node(node_to_detach);
            return node_to_detach;
        }
        detach_node(node_to_detach);
        return node_to_detach;
    }

    // problem 2  insert alternating
    void insert_alternating(LinkedList &list) {
        int itr = 1;
        Node *curr_new_list = list.head;
        for (Node *curr = head; curr; itr++) {
            if (curr_new_list->next && curr->next) {
                Node *tempNode = curr->next;
                Node *tempNode2 = curr_new_list->next;
                curr->next = curr_new_list;
                curr_new_list->next = tempNode;
                debug_data.insert(debug_data.begin() + itr, curr_new_list);

                curr = tempNode;
                curr_new_list = tempNode2;
            } else {
                if (!curr_new_list->next && curr->next) {
                    Node *tempNode = curr->next;
                    curr->next = curr_new_list;
                    curr_new_list->next = tempNode;
                    debug_data.insert(debug_data.begin() + ++itr, curr_new_list);
                    break;
                } else if (!curr->next && curr_new_list->next) {
                    curr->next = curr_new_list;
                    tail = list.tail;
                    debug_data.insert(debug_data.begin() + ++itr, list.debug_data.size() - itr, curr_new_list);
                    break;
                } else {
                    curr->next = curr_new_list;
                    debug_data.insert(debug_data.begin() + ++itr, list.debug_data.size() - itr + 1, curr_new_list);
                    tail = list.tail;
                    break;
                }

            }
        }
        list.tail = nullptr;
        list.head = nullptr;

        length += list.length;
        debug_verify_data_integrity();

    }

    // problem 3 adding two huge numbers

    void add_huge_numbers(LinkedList &another) {
        // { 1, 2, 3}
        // another =  {4, 5, 6}
        int length_diff = length - another.length;
        if (length_diff > 0) {
            for (int i = 0; i < length_diff; i++) {
                another.insert_end(new Node(0));
            }
        }
        if (length_diff < 0) {
            for (int i = 0; i < std::abs(length_diff); i++) {
                insert_end(new Node(0));
            }
        }

        int carry = 0;
        Node *curr2 = another.head;
        for (Node *curr = head; curr; curr2) {
            if (!(curr && curr2)) {
                break;
            }
            int value = (curr->value + curr2->value);
            curr->value = carry + (value % 10);
            carry = value / 10;

            curr = curr->next;
            curr2 = curr2->next;

        }
        insert_end(new Node(carry));
        reverse();

        for (Node *temp = head; temp; temp = temp->next) {
            if (temp->value == 0) {
                Node *nextNode = temp->next;
                delete_first();
                temp = nextNode;
            }
        }
    }

    // problem 4 delete all repeated
    void delete_all_repeated_sorted() {
        if (length < 2)return;
        bool is_prv_repeated = false;
        for (Node *crr = head->next, *prv = head, *prv_prv = nullptr; crr;) {
            if (prv->value == crr->value) {
                // 1- delete next node & set is_prv_repeated -> true
                delete_next_node(prv);
                is_prv_repeated = true;
                crr = prv;
            } else {
                if (is_prv_repeated) {
                    // if the first: meaning the prv_prv is nullptr -> delete head
                    if (!prv_prv) { // delete head, keep this null, prv = head
                        delete_first();
                        prv = head;
                    } else { // this means that it's repeated, but not the first node,,,, delete next, update prv
                        delete_next_node(prv_prv);
                        prv = prv_prv->next;
                    }
                    // reset is_prv_repeated -> false again
                    is_prv_repeated = false;
                } else {
                    prv_prv = prv;
                    prv = crr;
                }
            }
            crr = crr->next;
        }
        if (length == 1 && is_prv_repeated)delete_first();
    }

    Node *move_and_delete(Node *node) {
        Node *temp = node->next;
        delete_node(node);
        return temp;
    }

    void remove_all_repeated_from_sorted() {    // O(n) time - O(1) memory
        if (length <= 1)
            return;

        // Add dummy head for easier prv linking
        insert_front(new Node(-1234));

        tail = head;
        Node *previous = head;
        Node *cur = head->next;    // Our actual head

        while (cur) {
            // 2 cases: Either blocks of repeated so remove it. Or single node, keep it

            // keep removing blocks of SAME value
            bool any_removed = false;
            while (cur && cur->next && cur->value == cur->next->value) {
                int block_value = cur->value;
                any_removed = true;
                while (cur && cur->value == block_value)
                    cur = move_and_delete(cur);
            }
            if (any_removed) {
                if (!cur)
                    tail = previous;
                previous->next = cur;    // link after the removed nodes
                previous = cur;
            } else {
                // No duplicates. Connect and use as tail for now
                tail = cur;
                previous = cur;
                cur = cur->next;
            }
        }
        previous = head->next;    // actual head
        delete_first();        // remove dummy head
        head = previous;
        if (!head)
            tail = head;
        debug_verify_data_integrity();
    }


    void remove_all_repeated_alt() {
        if (length < 2)return;

        insert_front(new Node(-1234));
        tail = head;
        Node *prv = head;
        Node *curr = head->next;

        while (curr) {
            bool any_removed = false;
            while (curr && curr->next && curr->value == curr->next->value) {
                any_removed = true;
                int block_value = curr->value;
                while (curr->value == block_value) {
                    curr = move_and_delete(curr);
                }
            }

            if (any_removed) {


            } else {}
        }


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

    static void print(LinkedList *list) {
        for (Node *cur = list->head; cur; cur = cur->next)
            cout << cur->value << " ";
        cout << "\n";
    }

    void delete_node(Node *node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void detach_node(Node *node) {
        debug_remove_node(node);
        --length;
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

    static LinkedList *insert_end(LinkedList *list, Node *item) {
        auto itemVal = new Node(item->value);
        list->add_node(itemVal);

        if (!list->head)
            list->head = list->tail = itemVal;
        else
            list->tail->next = itemVal, list->tail = itemVal;
    }

    int get_nth_from_back(int idx) {
        return get_nth(length - idx + 1)->value;
    }

    bool is_same_node(Node *node1, Node *node2) {
        if (node1 && node2) return (node1->value == node2->value) && (node1 == node2);
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

void test1() {
    cout << "\n\ntest1\n";
    LinkedList list;

    list.insert_end(new Node(1));
    list.insert_end(new Node(2));
    list.insert_end(new Node(3));
    list.insert_end(new Node(4));
    list.insert_end(new Node(5));
    list.insert_end(new Node(6));


    list.reverse_alt();
    string expected = "6 5 4 3 2 1";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
    list.debug_verify_data_integrity();
}

void test2() {
    cout << "\n\ntest2\n";
    LinkedList list;

    list.insert_end(new Node(1));
    list.insert_end(new Node(2));


    list.reverse_alt();


    string expected = "2 1";
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

    list.insert_end(new Node(1));


    list.reverse_alt();


    string expected = "1";
    string result = list.debug_to_string();
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

    list.insert_end(new Node(1));
    list.insert_end(new Node(1));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(2));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(6));
    list.insert_end(new Node(0));
    list.insert_end(new Node(0));
    list.insert_end(new Node(0));
    list.insert_end(new Node(10));

    list.delete_all_repeated_sorted();


    string expected = "10";
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
    auto startTime1 = std::chrono::high_resolution_clock::now();

    test1();
    test2();
    test3();
//    test4();

    // Stop the timer
    auto endTime1 = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1);

    std::cout << "Execution time 1111111: =" << "startTime1  " << startTime1.time_since_epoch().count()
              << "   and endtime  " << endTime1.time_since_epoch().count()
              << "   and duration is  " << duration1.count() << " us" << std::endl;


    cout << "\n\nNO RTE\n";
    return 0;
}
