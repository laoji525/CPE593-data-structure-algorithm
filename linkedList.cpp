/*
 * Student: Xujia Ji
 * Data 03/12/2018
 */
#include <iostream>
#include <fstream>
using namespace std;

class LinkedList1 {
private:
    class Node {
    public:
        int data;
        Node* next;
        Node(int v, Node* node) : data(v), next(node) {}
    };
    Node* head;
    Node* tail;
    int size_;
public:
    LinkedList1() : head(nullptr),tail(nullptr), size_(0) {}
    ~LinkedList1() { // O(n)
        for (Node* p = head; p != nullptr; ) {
            Node* q = p;
            p = p->next;
            delete q;
        }
    }
    LinkedList1(const LinkedList1& orig) {
        if (orig.head == nullptr) { // zero elements
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node(orig.head->data, nullptr);
        if (orig.head->next == nullptr) { // 1 element
            tail = head;
            return;
        }
        // guaranteed orig has at least 2 elements
        // head is a copy of the 1st element of orig
        Node* q = head;
        for (Node* p = head->next; p != nullptr; p = p->next) {
            Node* temp = new Node(p->data, nullptr);
            q->next = temp;
            q = temp;
            tail = q;
        }

    }
    LinkedList1& operator =(const LinkedList1& orig) = delete;


    void addFirst(int v) { //O(1)
        size_++;
        Node* p = new Node(v, nullptr);
        if(head == nullptr){
            head = new Node(v, nullptr);
            tail = head;
            return;
        }
        p->next = head;
        head = p;
    }
    void addEnd(int v) { //O(n)
        size_++;
        Node* p = new Node(v, nullptr);
        if (head == nullptr) {
            head = new Node(v, nullptr);
            tail = head;
            return;
        }
        if (head == tail){
            head->next = p;
            tail = p;
            return;
        }
        tail->next = p;
        tail = p;
    }
    void removeFirst() { // O(1)
        if (head == nullptr)return;
        size_--;
        Node* p = head;
        if(head == tail){
            head = tail = nullptr;
            delete p;
            return;
        }
        head = head->next;
        delete p;
    }
    void removeEnd() {
        if (head == nullptr) {
            return;
        }
        size_--;
        Node* p = head;
        if (p->next == nullptr) {
            delete p;
            head = nullptr;
            return;
        }
        Node* q = p->next;
        for (p = head; q->next != nullptr; p = q, q = q->next) //O(n)
            ;
        delete q;
        p->next = nullptr;
        tail = p;
    }
    int size() const { //O(n)
        int count = 0;
        for (Node* p = head; p != nullptr; p = p->next)
            count++;
        return count;
    }
    void print(){
        Node* p = head;
        while(p!= nullptr){
            cout<<p->data<<' ';
            p = p->next;
        }
        cout<<endl;
    }
    friend ostream& operator <<(ostream& s, const LinkedList1& list){
        for (Node* p = list.head; p != nullptr; p = p->next)
            s << p->data << ' ';
        return s;
    }

};

int main() {

    LinkedList1 a;
    ifstream f("HW4b.txt");
    string temp;
    while(f>>temp){
        if(temp == "ADD_FRONT"){
            int min, step, max;
            char colon;
            f>>min;
            f>>colon;
            f>>step;
            f>>colon;
            f>>max;
            for(int i = min; i<= max;i+= step){
                a.addFirst(i);
            }
        }else if(temp == "ADD_BACK"){
            int min, step, max;
            char colon;
            f>>min;
            f>>colon;
            f>>step;
            f>>colon;
            f>>max;
            for(int i = min; i<= max; i += step){
                a.addEnd(i);
            }
        }else if(temp == "REMOVE_FRONT"){
            int times;
            f>>times;
            do{
                a.removeFirst();
            }while (--times !=0);
        }else if(temp == "REMOVE_BACK") {
            int times;
            f >> times;
            do {
                a.removeEnd();
            } while (--times != 0);
        }else if(temp == "OUTPUT"){
            a.print();
        }
    }
    f.close();
}