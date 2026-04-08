#include <iostream>
using namespace std;

//khai bao cau truc file
struct File {
    string ten;
    float size;
    int time;
};
//khoi tao list
struct Node {
    File data;
    Node* next;
};

Node* head = NULL;

Node* tao(File x) {
    Node* p = new Node;
    p->data = x;
    p->next = NULL;
    return p;
}

// chen file theo thoi gian tang dan
void chen(File x) {
    Node* p = tao(x);

    if (!head || x.time < head->data.time) {
        p->next = head;
        head = p;
        return;
    }

    Node* t = head;
    while (t->next && t->next->data.time < x.time)
        t = t->next;

    p->next = t->next;
    t->next = p;
}

// tong size cac file
float tong() {
    float s = 0;
    for (Node* p = head; p; p = p->next)
        s += p->data.size;
    return s;
}

// tim size cua file nho nhat
Node* minNode() {
    Node* m = head;
    for (Node* p = head; p; p = p->next)
        if (p->data.size < m->data.size)
            m = p;
    return m;
}

// xoa node
void xoa(Node* x) {
    if (!head || !x) return;

    if (head == x) {
        head = head->next;
        delete x;
        return;
    }

    Node* p = head;
    while (p->next != x) p = p->next;

    p->next = x->next;
    delete x;
}

// giam <=32
void giam() {
    while (tong() > 32)
        xoa(minNode());
}

// in file ra man hinh
void in() {
    for (Node* p = head; p; p = p->next)
        cout << p->data.ten << " "
             << p->data.size << "GB "
             << p->data.time << endl;
}


int main() {
    chen({"file1", 10, 3});
    chen({"file2", 5, 1});
    chen({"file3", 8, 2});
    chen({"file4", 12, 4});

    cout <<"Danh sach:\n";
    in();
    cout << "Tong: " << tong() << "GB\n";

    giam();

    cout << "\nSau khi giam <=32GB:\n";
    in();

    cout <<"Tong moi: " << tong() <<"GB\n";
    return 0;
}