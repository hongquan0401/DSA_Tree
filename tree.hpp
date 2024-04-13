#include <iostream>
#include <queue>
#include <string>
#include <functional>

using namespace std;

template<typename T>
class BinaryTree
{
private:
    struct Node
    {
        T data;
        Node *pLeft, *pRight;
        Node(const T& val): data(val), pLeft(nullptr), pRight(nullptr) {}
        Node(const T& val, void *pL, void *pR): data(val), pLeft((Node*)pL), pRight((Node*)pR) {}
    };
    Node *pRoot;

    void traverse_NLR(Node* pR, std::function<void (T&)> op) {}
    void traverse_NRL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LNR(Node* pR, std::function<void (T&)> op) {}
    void traverse_RNL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LRN(Node* pR, std::function<void (T&)> op) {}
    void traverse_RLN(Node* pR, std::function<void (T&)> op) {}

    void clear(Node* pR) { 
        if (pR->pLeft) clear(pR->pLeft);
        if (pR->pRight) clear(pR->pRight);
        delete pR;
    }
public:
    BinaryTree(): pRoot(nullptr) {};
    // BinaryTree(Node* )
    ~BinaryTree( clear(); );
    void clear() { if (pRoot) clear(this->pRoot); };
    void traverse_BFS() = 0;
};

template<typename T>
class BST {
    private:
    struct Node
    {
        T data;
        Node *pLeft, *pRight;
        Node(const T& val): data(val), pLeft(nullptr), pRight(nullptr) {}
        Node(const T& val, void *pL, void *pR): data(val), pLeft((Node*)pL), pRight((Node*)pR) {}
    };
    Node *pRoot;
    int nE;
    std::function<bool (const T&, const T&)> fnLessThan, fnEqual;

    void traverse_NLR(Node* pR, std::function<void (T&)> op) {}
    void traverse_NRL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LNR(Node* pR, std::function<void (T&)> op) {}
    void traverse_RNL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LRN(Node* pR, std::function<void (T&)> op) {}
    void traverse_RLN(Node* pR, std::function<void (T&)> op) {}
    
    void clear(Node* pR) { 
        if (pR->pLeft) clear(pR->pLeft);
        if (pR->pRight) clear(pR->pRight);
        delete pR;
    }
    void remove(Node* &pR, const T& key){
        if (!pR) return;
        if (fnEqual(key,pR->data)){
            if (pR->pLeft && pR->pRight){
                Node* p = pR->pRight;
                while (p->pLeft) p->pLeft;
                pR->data = p->data;
                remove(pR->pRight,p->data);
            }
            else if (pR->pLeft) {
                Node* p = pR;
                pR = p->pLeft;
                delete p;
            }
            else if (pR->pRight) {
                Node* p = pR;
                pR = p->pRight;
                delete p;
            }
            else {
                delete pR;
                pR = nullptr;
            }
            nE--;
        }
        else if(fnLessThan(key,pR->data)) remove(pR->pLeft,key);
        else remove(pR->pRight,key);
    }
public:
    BST(std::function<bool (const T&, const T&)> lessthan = [](const T& a, const T& b)->bool {return a < b;},
        std::function<bool (const T&, const T&)> equal = [](const T& a, const T& b)->bool {return a == b;}): 
        pRoot(nullptr), fnLessThan(lessthan), fnEqual(equal),nE(0) {};
    ~BST( clear(); );
    void clear() { if (pRoot) clear(this->pRoot); nE = 0; };
    void traverse_BFS() = 0;


    void insert(const T& val) {
        Node**pR = &pRoot;
        while (*pR)
        {
            pR = fnLessThan(val,(*pR)->data) ? &((*pR)->pLeft) : &((*pR)->pRight);
        }
        pR = new Node(val);
        nE++;
    }
    void insert(T&& val) {
        Node**pR = &pRoot;
        while (*pR)
        {
            pR = fnLessThan(val,(*pR)->data) ? &((*pR)->pLeft) : &((*pR)->pRight);
        }
        pR = new Node(std::move(val));
        nE++;
    }
    void remove(const T& key) { remove(pRoot,key); }
    void removeAll(const T& key) {
        for (int oldN = nE; oldN = nE){
            if (nE) remove(pRoot,key);
        }
    }
};



template<typename T>
class AVL {
    private:
    enum BalanceFactor {LH,EH,RH}
    struct Node
    {
        T data;
        BalanceFactor bf;
        Node *pLeft, *pRight;
        Node(const T& val): data(val), pLeft(nullptr), pRight(nullptr), bf(EH) {}
        Node(const T& val, void *pL, void *pR): data(val), pLeft((Node*)pL), pRight((Node*)pR), bf(EH) {}
        Node(T&& val, void* pL = nullptr, void* pR = nullptr): data(std::move(val)),pLeft((Node*)pL),pRight((Node*)pR), bf(EH) {}
    };
    Node *pRoot;
    int nE;
    std::function<bool (const T&, const T&)> fnLessThan, fnEqual;

    void traverse_NLR(Node* pR, std::function<void (T&)> op) {}
    void traverse_NRL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LNR(Node* pR, std::function<void (T&)> op) {}
    void traverse_RNL(Node* pR, std::function<void (T&)> op) {}

    void traverse_LRN(Node* pR, std::function<void (T&)> op) {}
    void traverse_RLN(Node* pR, std::function<void (T&)> op) {}
    
    void clear(Node* pR) { 
        if (pR->pLeft) clear(pR->pLeft);
        if (pR->pRight) clear(pR->pRight);
        delete pR;
    }
    bool remove(Node* &pR, const T& key){
        if (!pR) return false;
        bool removeLeft = true, shorter = false;
        if (fnEqual(key,pR->data)){
            if (pR->pLeft && pR->pRight){
                Node* p = pR->pRight;
                while (p->pLeft) p = p->pLeft;
                pR->data = p->data;
                if (remove(pR->pRight,p->data)){
                    nE--;
                    return !balanceLeft(pR);
                }
            }
            else if (pR->pLeft) {
                Node* p = pR;
                pR = p->pLeft;
                delete p;
            }
            else if (pR->pRight) {
                Node* p = pR;
                pR = p->pRight;
                delete p;
            }
            else {
                delete pR;
                pR = nullptr;
            }
            nE--;
            return true;
        }
        else if(fnLessThan(key,pR->data)) {
            shorter = remove(pR->pLeft,key);
        }
        else {
            shorter = remove(pR->pRight,key);
            removeLeft = false;
        }
        if (shorter) {
            return removeLeft ? !balanceRIght(pR) : !balanceLeft(pR);
        }
        return false;
    }

    void rotateRight(Node* &pR) {
        Node* p = pR->pLeft;
        pR->pLeft = p->pRight;
        p->pRight = pR;
        pR = p;
    }
    void rotateLeft(Node* &pR) {
        Node* p = pR->pRight;
        pR->pRight = p->pLeft;
        p->pLeft = pR;
        pR = p;
    }
    bool balanceLeft(Node* &pR) {
        if      (pR->bf == EH) { pR->bf = LH; return true;  }
        else if (pR->bf == RH) { pR->bf == EH; return false; }
        if (pR->pLeft->bf == EH) {
            rotateRight(pR);
            pR->pRight->bf = LH;
            pR->bf = RH;
            return true;
        } else if (pR->pLeft->bf == LH) {
                rotateRight(pR);
                pR->bf = pR->pRight->bf = EH;
                return false;
        }
        rotateLeft(pR->pLeft);
        rotateRight(pR);
        if (pR->bf == EH) { pR->pLeft->bf = pR->pRight->bf = EH; }
        else if (pR->bf == LH) { pR->pLeft->bf = pR->bf = EH; pR->pRight->bf = RH; }
        else { pR->pRight->bf = pR->bf = EH; pR->pLeft->bf = LH; }
        return false;
    }
    bool balanceRIght(Node8 &pR) {
        if      (pR->bf == EH) { pR->bf = RH; return true;  }
                else if (pR->bf == LH) { pR->bf == EH; return false; }
                if (pR->pRight->bf == EH) {
                    rotateLeft(pR);
                    pR->pLeft->bf = RH;
                    pR->bf = RH;
                    return true;
                } else if (pR->pRight->bf == RH) {
                    rotateLeft(pR);
                    pR->bf = pR->pLeft->bf = EH;
                    return false;
                }
                rotateRight(pR->pRight);
                rotateLeft(pR);
                if (pR->bf == EH) { pR->pLeft->bf = pR->pRight->bf = EH; }
                else if (pR->bf == RH) { pR->pLeft->bf = pR->bf = EH; pR->pRight->bf = LH; }
                else { pR->pLeft->bf = pR->bf = EH; pR->pRight->bf = LH; }
                return false;
    }
    bool insert(Node* &pR, const T &val) {
        if (!pR){
            pR = new Node(val);
            return true;
        }
        if (fnLessThan(val,pR->data)) {
            // insert left
            if (insert(pR->pLeft,val)){
                return balanceLeft(pR)
            }
        }
        else {
            // insert right
            if (insert(pR->pRight,val)){
                return balanceRIght(pR);
            }
        }
        return false;
    }

public:
    AVL(std::function<bool (const T&, const T&)> lessthan = [](const T& a, const T& b)->bool {return a < b;},
        std::function<bool (const T&, const T&)> equal = [](const T& a, const T& b)->bool {return a == b;}): 
        pRoot(nullptr), fnLessThan(lessthan), fnEqual(equal),nE(0) {};
    ~AVL( clear(); );
    void clear() { if (pRoot) clear(this->pRoot); nE = 0; };
    void traverse_BFS() = 0;


    void insert(const T& val) {
        insert(root,val);
        nE++;
    }
    void insert(T&& val) {
        insert(root,val);
        nE++;
    }
    void remove(const T& key) { remove(pRoot,key); }
    void removeAll(const T& key) {
        for (int oldN = nE; oldN = nE){
            if (nE) remove(pRoot,key);
        }
    }
};