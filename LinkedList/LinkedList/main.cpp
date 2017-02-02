#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"


// === MAIN === //

int main()
{


    srand (time(NULL));

    LinkedList list1;
    LinkedList list2(5);

    cout << "created 2 lists, traversing list 1" << endl;

    list1.traverse_list();

    list1 + 666;

    cout << "added 666 to list 1, traversing again " << endl;

    list1.traverse_list();

   // list1.removeLast();

    list1--;

    cout << "Removed last" << endl;
    list1.traverse_list();

    list1[3] = -999;

    cout << "Changed 3rd node" << endl;

    list1.traverse_list();


    cout << "DONE" << endl;

    system("PAUSE");

}

