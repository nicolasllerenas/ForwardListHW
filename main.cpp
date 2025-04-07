#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T val;
    Node* next;
    Node(T value) : val(value), next(nullptr){}
    Node(T value, Node<T>* n) : val(value), next(n){}
};

template<typename T>
class List{
private:
    Node<T>* head;
public:
    List() : head(nullptr){}
    List(Node<T>* h) : head(h){}
    T front(){
        return head->val;
    }
    T back(){
        Node<T>* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        return temp->val;
    }
    void push_front(T value){
        Node<T>* nodo = new Node<T>(value, head);
        head = nodo;
    }
    void push_back(T value){
        Node<T>* nodo = new Node<T>(value);
        if(!head){
            head = nodo;
            return;
        }
        Node<T>* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nodo;
        nodo->next = NULL;
    }
    void pop_front(){
        if(!head || !head->next) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back(){
        if(!head) return;
        if(head->next == NULL){
            delete head;
            head = NULL;
        }
        else{
            Node<T>* temp = head;
            while(temp->next->next != NULL){
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
        }
    }
    T operator [](int num){
        Node<T>* temp = head;
        int cont = 0;
        while(temp != nullptr && cont < num){
            temp = temp->next;
            cont++;
        }
        if (!temp) throw std::out_of_range("Index out of bounds");
        return temp->val;
    }
    bool empty(){
        return head == NULL;
    }
    int size(){
        Node<T>* temp = head;
        int cont = 1;
        while(temp->next != NULL){
            cont++;
            temp = temp->next;
        }
        return cont;
    }
    void clear(){
        while(head != NULL){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    Node<T>* merge(Node<T>* left, Node<T>* right){
        if(!left) return right;
        if(!right) return left;

        if(left->val < right->val){
            left->next = merge(left->next, right);
            return left;
        }
        else{
            right->next = merge(left, right->next);
            return right;
        }
    }
    Node<T>* MergeSort(Node<T>* node){
        if(!node || !node->next) return node;

        Node<T>* slow = node;
        Node<T>* fast = node->next;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* mid = slow->next;
        slow->next = nullptr;

        Node<T>* left = MergeSort(node);
        Node<T>* right = MergeSort(mid);

        return merge(left, right);
    }
    void sort(){
        head = MergeSort(head);
    }
    void reverse(){
        Node<T>* prev = nullptr;
        Node<T>* temp = head;
        Node<T>* next = nullptr;

        while(temp){
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }

        head = prev;
    }
    void print(){
        Node<T>* temp = head;
        while(temp != NULL){
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    List<int> lista;
    
    // Pruebas básicas
    lista.push_back(3);
    lista.push_front(1);
    lista.push_back(5);
    lista.push_front(0);
    
    cout << "Tamano: " << lista.size() << endl;       // 4
    cout << "Front: " << lista.front() << endl;      // 0
    cout << "Back: " << lista.back() << endl;        // 5
    
    lista.pop_back();
    lista.pop_front();
    cout << "Tamano despues de pops: " << lista.size() << endl;  // 2
    cout << "Elemento 0: " << lista[0] << endl;      // 1
    
    lista.sort();
    cout << "Ordenado: " << lista[0] << " " << lista[1] << endl; // 1 3
    
    lista.reverse();
    cout << "Reverso: " << lista[0] << " " << lista[1] << endl;  // 3 1
    
    lista.clear();
    cout << "Lista Vacia? " << lista.empty() << endl;    // 1 (true)
    
    return 0;
}