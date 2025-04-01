#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T val;
    Node* next;
};

template<typename T>
class List {
private:
    Node<T>* head;

public:
    List() : head(nullptr) {}  // Inicializamos head

    T front() {
        if (empty()) throw out_of_range("Lista vacía");
        return head->val;
    }

    T back() {
        if (empty()) throw out_of_range("Lista vacía");
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->val;
    }

    void push_front(T value) {
        Node<T>* nuevo = new Node<T>;
        nuevo->val = value;
        nuevo->next = head;
        head = nuevo;
    }

    void push_back(T value) {
        Node<T>* nuevo = new Node<T>;
        nuevo->val = value;
        nuevo->next = nullptr;

        if (empty()) {
            head = nuevo;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = nuevo;
        }
    }

    T pop_front() {
        if (empty()) throw out_of_range("Lista vacía");
        Node<T>* temp = head;
        T valor = temp->val;
        head = head->next;
        delete temp;
        return valor;
    }

    T pop_back() {
        if (empty()) throw out_of_range("Lista vacía");
        
        T valor;
        if (head->next == nullptr) {
            valor = head->val;
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            valor = temp->next->val;
            delete temp->next;
            temp->next = nullptr;
        }
        return valor;
    }

    T operator[](int index) {
        if (index < 0 || empty()) throw out_of_range("Índice inválido");
        
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            if (temp->next == nullptr) throw out_of_range("Índice inválido");
            temp = temp->next;
        }
        return temp->val;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        int cont = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            cont++;
            temp = temp->next;
        }
        return cont;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Ordenamiento por inserción
    void sort() {
        if (empty() || head->next == nullptr) return;
        
        Node<T>* sorted = nullptr;
        Node<T>* curr = head;
        
        while (curr != nullptr) {
            Node<T>* next = curr->next;
            if (sorted == nullptr || sorted->val >= curr->val) {
                curr->next = sorted;
                sorted = curr;
            } else {
                Node<T>* temp = sorted;
                while (temp->next != nullptr && temp->next->val < curr->val) {
                    temp = temp->next;
                }
                curr->next = temp->next;
                temp->next = curr;
            }
            curr = next;
        }
        head = sorted;
    }

    // Reversión iterativa
    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
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