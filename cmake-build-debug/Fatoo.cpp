#include <iostream>
using namespace std;

class list {  //class to create object for further declaration of new nodes(imolementation of a singly linked list)
public:  //all parameters are kept public so that they can be accessed easily

    int d;  //for data part of a new node
    list *next;  //for next field of node
};

class singlylinkedlist {
//implementation of a singly linked list is done by this class
public:
    list *start;  // for head node  of a linked list
    list *last;   // for last node of a linked list

    list *ploc;   //for a logiacal predecessor of current node or loc
    list *loc;    //for current node

    //CONSTRUCTOR
    singlylinkedlist() {
        start = NULL;
        ploc = NULL;
        loc = NULL;

    }


    //Function to check if list is Empty:
    bool isEmpty() {
        if (start == NULL) {
            return true;
            cout<<isEmpty()<< endl;
        }
        else
            return false;
    }

    //function for insertion at the front end of list
    void insertAtFront(int value) {

        list *h_node = new list();
        h_node->d= value;


        if (isEmpty()){  // pre condition for insertion
            start = h_node;
            last = h_node;
        }
        else
            h_node->next = start;  //upgradation
        start = h_node;


    }


    //function for insertion at tail end of list

    void insertAtTailEnd (int value)
    {
        list *n_node = new list();
        n_node->d=value;

        if (isEmpty()) {  //a precondition
            start = n_node;
            last = n_node;
        }
        else
            last->next = n_node;  //upgradation
        last = n_node;

    }

    //function for printing an entire list
    void PrintList()
    {
        list *temp= new list();  //a temporary pointer variable to store location of anode temporarily
        temp = start;

        if (!isEmpty()) {
            while (temp != NULL){
                cout << temp->d << " ";
                temp= temp->next;
            }
        }
        else  //if list is empty
            cout << "NO PARAMETER FOUND!!!" << endl;

    }

    //a function to search a particular element from a list
    void Search(int value)
    {
        loc = start;
        ploc = NULL;

        //these two checkes will determine the basic demand for searching in a linked list
        while (loc != NULL && loc->d < value) {
            ploc = loc;
            loc = loc->next;

        }
        if (loc != NULL && loc->d != value) {
            loc = NULL;
        }
    }

    //function to insert all elemnts in a sorted format
    void InsertSorted(int value)
    {
        list *node=new list();  //newnode
        node->d=value;

        Search(value);  // entered value is searched, so that it can be put at its appropriate loctaion in alist
        if (loc != NULL) {  //check using loc
            cout << "DUPLICATION NOT ALLOWED" << endl;
        }

        else
        if (ploc == NULL) {  //check for front end insertion
            insertAtFront(value);
        }
        else {
            node->next=ploc->next;
            ploc->next=node;
        }
        if(ploc==last) {
            last=node;
        }
    }

    //function to delete a value from list
    void Delete(int value){
        if (!isEmpty()){ //check if the list is empty
            Search(value);

            if (loc != NULL){//if value is found
                if (ploc == NULL){//if value is in head node
                    if (last == start){ //if there is only one value
                        start = NULL;
                        last = NULL;
                        delete[] loc;
                    }
                    else{
                        start = loc->next;
                        delete[] loc;
                    }
                }
                else if (last == loc){// if value is at tail end
                    ploc->next = last->next;
                    last = ploc; //update last

                    delete[] loc;
                }
                else{//if ploc is non-Null
                    ploc->next = loc->next;
                    delete[] loc;
                }
            }
            else{ //if the value is not found in the list
                cout<<"Value "<<value<<" not Found!"<<endl;
                return;
            }
        }
    }

    //function for the destruction of a list
    void destroyList() {
        list *temp= new list();  //a temporary variable
        temp=start;

        if (isEmpty()) {  //precondition
            cout <<"THERE IS NOTHING TO DESTROY"<< endl;
        }

        else
            while(temp!=NULL) {
                temp=temp->next;
                delete temp;
            }

    }
    void ReversePrint( list* node) {
        if(node== NULL) return;

        ReversePrint(node->next);
        cout<<node->d<<" "<<endl;
    }

    void DeleteoddNode() {
        list *temp = new list();

        if (!isEmpty()) {

            loc = start;
            ploc = NULL;

            while (loc != NULL) {

                if (loc->d % 2 != 0) {
                    if (ploc == NULL) {
                        if (last == start) {
                            start = NULL;
                            last = NULL;
                            delete loc;
                            loc = ploc;
                        } else {
                            start = loc->next;
                            delete loc;
                            loc = start;
                            ploc = NULL;
                        }
                    } else if (loc == last) {
                        ploc->next = loc->next;
                        last = ploc;
                        delete loc;
                        loc = last;
                        loc->next = NULL;

                    } else {
                        ploc->next = loc->next;
                        delete loc;
                        loc = ploc->next;
                    }
                } else {
                    ploc = loc;
                    loc = loc->next;
                }
            }
        }
    }
        void ReverseList()
        {
            list *temp = new list();   //for current node
            list *nn = new list();   //for next node
            list *p = new list();  //for previous node

            temp = start;
            nn = NULL;
            p = NULL;

            while (temp != NULL) {

                nn = temp->next;
                temp->next = p;

                p = temp;
                temp = nn;
            }
            start = p;
            return;
        }


};


//Main Function
    int main()
    {

        singlylinkedlist *ll=new singlylinkedlist();

        //object of singlylinked list
        cout<<"list  is as:"<<endl;

        //INSERTIONS INTO A LIST
        ll->InsertSorted(1);
        ll->InsertSorted(2);
        ll->InsertSorted(7);
        ll->InsertSorted(6);
        ll->PrintList();
        ll->ReverseList();
        //	ll->SwapValues(1,2);
        ll->PrintList();

        return 0;
    }