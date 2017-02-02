#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class LinkedList{

    public:

struct Node{

   Node* next;
   int data;

   Node(){

        next = NULL;
        data = -999;

   }

};

LinkedList(){

    int list_length;

    cout << "How many items do you want in  your list? " ;

    cin >> list_length;

    cout << "Do you want to fill them manually? (y/n) ";

    char decision;

    cin >> decision;

    head = create_list(list_length);



}

LinkedList(int list_size){



    cout << "Do you want to fill items manually? (y/n) ";

    char decision;

    cin >> decision;

    head = ( decision == 'y' ? create_manually(list_size) : create_list(list_size) );

}


// === PUBLIC FUNCTION DECLARATIONS === //


Node* addElement(Node* curr, int data){

    if(curr == NULL){
        curr = new Node;
        curr->data = data;
        length++;
        return curr;
    }else{

        Node* tmp = new Node;
        tmp->data = data;
        tmp->next = NULL;
        curr->next = tmp;
        length++;

        return tmp;

    }



}


Node* create_list(int len){

    Node* curr = head;

    Node* result = head;

    cout << "Node values will be random" << endl;

    for(int i = 0; i<len; i++){

        int tmp = rand();
        current =  curr = addElement(curr, tmp);

        if(head == NULL && i ==0 ){

            result = curr;

        }

    }

    cout << len << " nodes created" << endl;

    return result;

}

Node* create_manually( int len){

    Node* curr = head;

    Node* result = head;

    int input;

    for(int i = 0; i<len; i++){

        cout << "Enter new node value:" ;

        cin >> input;

        curr = current = addElement(curr, input);

        if(head == NULL && i ==0 ){

            result = curr;

        }

    }

    cout << len << " nodes created" << endl;

    return result;


}

void traverse_list(){

    Node* curr = head;

    Node* prevNode = head;

    int cnt = 1;

    while(curr != NULL){

        cout << "Node #" << cnt << " :: Data = " << curr->data << endl;

        cnt++;

        prevNode = curr;
        curr = curr->next;


    }

}

// === OVERLOADING OPERATORS === //

operator +(int data){

    current = addElement(current, data);

}

operator =(int n){


}

operator --(int){

    removeLast();

}

int& operator [](int index){        // For L-value

    // this is useless, I'm just experimenting

    if(index > length) {

        cout << "Index "  << index <<  " does not exist in this LinkedList " << endl;

        exit(1);
    }

    Node* tmp = getNode(index);

    return tmp->data;


}

const int& operator [](int index) const{            // For R-value

    // this is useless, but I'm experimenting with overloading again

    if(index > length || index < 1 ) {

        cout << "Index "  << index <<  " does not exist in this LinkedList " << endl;

        exit(1);
    }

    Node* tmp = getNode(index);

    return tmp->data;


}

friend ostream& operator << (ostream& current, const LinkedList& l);


// === PRIVATE === //
    private:

        Node* head = NULL;

        Node* current = NULL;

        int length = 0;

void removeLast(){

    Node* it = head;

    if(head == NULL || head == current) {

            current = NULL;
    }

    while(it->next!=current){

        it = it->next;

    }

    current = it;

    free(current->next);

    current->next = NULL;

    length--;

}

Node* getNode(int index) const{

    Node* curr = head;

    Node* prevNode = head;

    int cnt = 1;

    while(curr != NULL && cnt != index){

      //  cout << "Node #" << cnt << " :: Data = " << curr->data << endl;

        cnt++;

        prevNode = curr;
        curr = curr->next;


    }

    return curr;
}


};


 ostream& operator << (ostream& current, const LinkedList& l){

        LinkedList::Node* it = l.head;

        current << "-----------" << endl;
        while (it != NULL){

            current << it->data << endl;
            it = it->next;
        }

         current << "-----------" << endl;

         return current;


}

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

