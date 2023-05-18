#include <iostream>
#include <random>
#include <chrono>
#include <functional>

#include "BTree.h"

using namespace std;

int main()
{
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(1, 999);
    auto dice = bind(distribution, generator);

    BTree<int> myBTree;
    int value;

    for(int i(0); i < 100; i++){
        value = dice();

        cout << "insertando..." << value << endl;

        myBTree.insertData(value);
    }

    cout << "recorrido en preorder:" << endl;
    myBTree.parsePreOrder();
    cout << endl << endl;

    cout << "recorrido en inorder: " << endl;
    myBTree.parseInOrder();
    cout << endl << endl;

    cout << "recorrido en postorder:" << endl;
    myBTree.parsePostOrder();
    cout << endl << endl;

    cout << "altura del arbol: " << myBTree.getHeight();
    cout << endl;

    cout << "el valor menor es: " << myBTree.getLowest();
    cout << endl;

    cout << "el valor mayor es: " << myBTree.getHighest();
    cout << endl;
}
