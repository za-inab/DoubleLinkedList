#include <iostream>
#include <conio.h>

using namespace std;

class ListNode{
public:
    int data;
    ListNode	*next;
    ListNode	*prev;
    ListNode()
    {
        data=0;
        next=NULL;
        prev=NULL;
    }

};

class MyLinkedList{
public:
    ListNode *first; // special variable which stores address of head node.
    ListNode *last; // special variable which stores address of the last node.

    ListNode *PredLoc_; //to be used by Search(value) method to store address of logical predecessor of value in a list.
    ListNode *Loc_; //to be used by Search(value) method to store address of the node containing the searched value in a list. If it is not found it contains NULL.

    MyLinkedList(){

        first=NULL;
        last=NULL;
        Loc_=NULL;
        PredLoc_=NULL;

    }
    void PrintList()
    {
        ListNode *temp=new ListNode();
        temp=first;

        if (first==NULL)
        {
            cout<<"List is empty"<<endl;
            return;
        }
        else {
            cout << "The elements of list are " << endl;
            for (int i = 0; temp != NULL; i++) {
                cout << i + 1 << ") " << temp->data << endl;
                temp = temp->next;
            }
        }
    }
    bool isEmpty()
    {
        return (first==NULL && last==NULL);

    }
    void InsertAtFront(int value)
    {
        ListNode* temp=new ListNode();
        temp->data=value;

        cout<<"Error idhar hai"<<endl;
        if(first==NULL)
        {
            first=temp;
            last=temp;
        }
        else if(first != NULL)
        {
            temp->next=first;
            first->prev=temp;
            first=temp;
            temp->prev=NULL;

        }
        PrintList();

    }

    void InsertAtEnd(int value)
    {
        ListNode* temp=new ListNode();
        temp->data=value;

        PredLoc_=NULL;
        Loc_=first;

        if(Loc_==NULL)
        {
            first=temp;
            last=temp;
            temp->next=NULL;
            temp->prev=NULL;
        }
        else if(Loc_==last)
        {
            last=temp;
            first->next=temp;
            temp->prev=Loc_;
            Loc_->next=temp;
            temp->next=NULL;
            Loc_->prev=NULL;
        }
        else
        {
            while(Loc_ !=NULL)
            {
                PredLoc_=Loc_;
                Loc_=Loc_->next;
            }
            Loc_=temp;
            PredLoc_->next=Loc_;
            Loc_->prev=PredLoc_;
            Loc_->next=NULL;
            last=temp;
        }


    }

    void InsertSorted(int value)
    {
        ListNode* temp=new ListNode();
        temp->data=value;
        Search(value);


        if (Loc_!= NULL)
        {
            cout<<"The value already exists. Cannot rewrite"<<endl;
            return;
        }

        else
        {

            if(PredLoc_==NULL) {
                InsertAtFront(value);
                PrintList();
                return;
            }
            if (PredLoc_->next==NULL) {
                InsertAtEnd(value);
                PrintList();
                return;
            }
            else{
                    Loc_=temp;
                    temp->next=PredLoc_->next;
                    PredLoc_->next=temp;
                    Loc_->prev=PredLoc_;
                    Loc_->next->prev=Loc_;
            }


        }

        PrintList();

    }

    void Search(int value)
    {
        Loc_=first;
        PredLoc_=NULL;

        while(Loc_ != NULL && Loc_->data<value)
        {
            PredLoc_=Loc_;
            Loc_=Loc_->next;
        }

        if(Loc_!= NULL && Loc_->data == value)
        {
            cout<<"The required value "<<value<<" is present in list"<<endl;

            return;
        }
        else if(Loc_!= NULL && Loc_->data != value)
        {
            cout<<"The required value "<<value<<" is not in list"<<endl;
            Loc_=NULL;
        }

    }

    void DeleteNode(int value)
    {
        ListNode* temp=new ListNode();

        Search(value);

        if(Loc_==NULL)
        {
            cout<<"The value does not exists"<<endl;
            return;
        }
        else if(Loc_ !=NULL)
        {
            if(Loc_==first)
            {
                temp=Loc_;
                first=first->next;
                first->prev=NULL;
                Loc_=first;
                delete temp;

            }
            else if(Loc_==last)
            {
                temp=Loc_;
                last=last->prev;
                last->next=NULL;
                Loc_=last;
                delete temp;
            }
            else if(Loc_!=first && Loc_!=last)
            {
                temp=Loc_;
                PredLoc_->next=Loc_->next;
                Loc_->next->prev=PredLoc_;
                Loc_=Loc_->next;
                delete temp;

            }
            PrintList();

        }


    }

    void DeleteList()
    {
        Loc_=first;
        first=NULL;
        last=NULL;

        ListNode* temp=new ListNode();

        while (Loc_!=NULL)
        {
            temp=Loc_;
            Loc_=Loc_->next;
            delete temp;
        }
        PrintList();

    }
    void ReverseList(ListNode **head)
    {
        ListNode *temp = NULL;
        ListNode *current=*head;

        if(!isEmpty())
        {
            while(current!=NULL)
            {
                temp = current->prev;
                current->prev = current->next;
                current->next = temp;
                current = current->prev;
            }

            if(temp!=NULL){
                *head = temp->prev;
            }

            PrintList();
        }
        else
            cout<<"Cannot reverse as list is empty."<<endl;
    }

    void SwapNodes(ListNode **head_ref, int x, int y)
    {
        if(x==y)
            return;

        ListNode *prevX=NULL;
        ListNode *currentX=*head_ref;
        ListNode *prevY=NULL;
        ListNode *currentY=*head_ref;

        while(currentX && currentX->data != x){
            prevX=currentX;
            currentX=currentX->next;
        }

        while(currentY && currentY->data != y){
            prevY = currentY;
            currentY = currentY->next;
        }

        if(currentX==NULL || currentY==NULL)
        {
            cout<<"The value(s) donot exist."<<endl;
            return;
        }

        // If x is not head of linked list
        if (prevX != NULL)
        {
            prevX->next = currentY;
        }

        else // Else make y as new head
            *head_ref = currentY;

        // If y is not head of linked list
        if (prevY != NULL)
        {
            prevY->next = currentX;
        }
        else // Else make x as new head
            *head_ref = currentX;

        ListNode *temp=currentX->next;
        currentX->next = currentY->next;
        currentY->next = temp;

        PrintList();
    }

    void GroupingEvenOddNodes()
    {
        ListNode* end = first;
        ListNode* prev = NULL;
        ListNode* curr = first;

        /* Get pointer to the last node */
        while (end->next != NULL)
            end = end->next;

        ListNode* new_end = end;

        /* Consider all odd nodes before the first
         even node and move them after end */
        while (curr->data % 2 != 0 && curr != end)
        {
            new_end->next = curr;
            curr = curr->next;
            new_end->next->next = NULL;
            new_end = new_end->next;
        }

        /* Do following steps only if
        there is any even node */
        if (curr->data % 2 == 0)
        {
            /* Change the head pointer to
            point to first even node */
            first = curr;

            /* now current points to
            the first even node */
            while (curr != end)
            {
                if ((curr->data) % 2 == 0)
                {
                    prev = curr;
                    curr = curr->next;
                }
                else
                {
                    /* break the link between
                    prev and current */
                    prev->next = curr->next;

                    /* Make next of curr as NULL */
                    curr->next = NULL;

                    /* Move curr to end */
                    new_end->next = curr;

                    /* make curr as new end of list */
                    new_end = curr;

                    /* Update current pointer to
                    next of the moved node */
                    curr = prev->next;
                }
            }
        }

            /* We must have prev set before executing
            lines following this statement */
        else prev = curr;

        /* If there are more than 1 odd nodes
        and end of original list is odd then
        move this node to end to maintain
        same order of odd numbers in modified list */
        if (new_end != end && (end->data) % 2 != 0)
        {
            prev->next = end->next;
            end->next = NULL;
            new_end->next = end;
        }
        PrintList();
        return;
    }





    };


int main() {

    MyLinkedList dllist;

    dllist.InsertAtEnd(1);
    dllist.InsertAtEnd(2);
    dllist.InsertAtEnd(3);
    //dllist.InsertAtEnd(4);
    dllist.InsertAtEnd(5);
    dllist.InsertAtEnd(6);
    dllist.InsertAtEnd(7);



    cout<<"Creating a doubly linked list and implementing different functions"<<endl;
    cout<<"Printing values initially stored in list"<<endl;
    dllist.PrintList();
    cout<<endl;

    cout<<"Inserting 0 at the start of list by insert at front function"<<endl;
    dllist.InsertAtFront(0);
    cout<<endl;

    cout<<"Inserting 8 at the end of list by insert at end function"<<endl;
    dllist.InsertAtEnd(8);
    dllist.PrintList();
    cout<<endl;

    cout<<"Checking that list is empty or not by is empty function"<<endl;
    bool empty=dllist.isEmpty();
    if (empty==1)
        cout<<"The list is empty"<<endl;
    else
        cout<<"The list is not empty"<<endl;
    cout<<endl;

    cout<<"Searching the value of 5 by using search function"<<endl;
    dllist.Search(5);
    cout<<endl;

    cout<<"Inserting 4 in the list by insert sorted function"<<endl;
    dllist.InsertSorted(4);
    cout<<endl;

    cout<<"Deleting the value of 5 by delete node function"<<endl;
    dllist.DeleteNode(5);
    cout<<endl;


    cout<<"Using reverse function to reverse list"<<endl;
    dllist.ReverseList(&dllist.first);
    cout<<endl;

    cout<<"Using Grouping function to seperate even and odd lists"<<endl;
    dllist.GroupingEvenOddNodes();
    cout<<endl;

    cout<<"Using swap functions to swap the values of lists"<<endl;
    dllist.SwapNodes(& dllist.first,2,7);
    cout<<endl;

    cout<<"Destroying list by using delete list function"<<endl;
    dllist.DeleteList();
    cout<<endl;

    return 0;
}


