#include "tree.hpp"

using namespace std;

int main(){
    BST<int>* tree = new BST<int>([](const int& a, const int& b) -> bool {return a < b; },
                                [] (const int& a, const int& b) -> bool { return a==b; });
    for (int i = 0; i < 10; i++) {
        tree->insert(rand() %100);
    }
}