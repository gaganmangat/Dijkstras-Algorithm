#include <iostream>
#include<malloc.h>
#include<climits>

using namespace std;

struct node
{
    int vno; //vertexnumber
    int distance; //minimum distance of the vertex from the source
    int processed = 0; //for nodes which are still under processing
    int predecessor;
    struct node* next;
};
typedef struct node Node;

int vertices; //number of vertices
int edges; //number of edges
int svertex; //source
int selectedv;
int k = 1;

Node* start = NULL;
void InitializeSingleSource(int svertex);
Node* insertNodeSorted(Node* start, int value, int distance, int predecessor);
Node* display(Node* start);
Node* extractMin(Node* start);
Node* decreaseKey(Node* start, int edgelength, int adjvertex);
int emptyOrNot(Node* start);

int main()
{
    cout<<"value of start is: "<<start<<endl;
    cout<<"Enter number of vertices\n";
    cin>>vertices;
    cout<<"Enter number of edges\n";
    cin>>edges;
    //int u, v, weight;
    int g[vertices][vertices];
    //assuming vertices are numbered as 1,2,3,....
    int i, j;

    for(i=1; i<=vertices; i++) //initialising the graph
    {
        for(j=1; j<=vertices; j++)
        {
            g[i][j] = 0;
        }
    }

    int u, v, w; //intial vertex,final vertex and weight

    for(i=1; i<=edges; i++)
    {
        cout<<"Enter the initial and final vertices of the edge "<<i<<"\n";
        cin>>u>>v;
        cout<<"Enter weight of the edge\n";
        cin>>w;
        g[u][v] = w;
    }

    cout<<"THE ADJACENCY MATRIX OF THE WEIGHTED GRAPH IS: \n\n";
    for(i=1; i<=vertices; i++)
    {
        for(j=1; j<=vertices; j++)
        {
            cout<<g[i][j]<<"\t";
        }
        cout<<endl;
    }


    cout<<"Enter the source vertex\n";
    cin>>svertex;
    InitializeSingleSource(svertex);

    int s[vertices] = {0};
    //int k = 0;

    while(emptyOrNot(start))
    {
        cout<<"emptyornot: "<<!emptyOrNot(start)<<endl;
        start = extractMin(start);
        cout<<"The selectedv is: "<<selectedv<<endl;
        s[k] = selectedv;
        k++;

        cout<<"ARRAY S CONTAINS THE VERTICES: \n\n";

        for(j=1; j<=vertices; j++)
        {
            cout<<s[j]<<"\t";
        }
        cout<<"\n\n";
        //start = display(start);
        for(j=1; j<=vertices; j++)
        {
            cout<<"in MAIN FOR LOOP RELAX\n";
            cout<<"selectedvertex: "<<selectedv<<"  j: "<<j<<endl;
            if(g[selectedv][j] != 0)
            {
                cout<<"weight of adjacent vertex "<<j<<" of "<<selectedv<<"is: "<<g[selectedv][j]<<endl;
                int length = g[selectedv][j];
                start = decreaseKey(start, length, j);
            }
            cout<<"out of if\n";
        }
        cout<<"out of for\n";
    }
    cout<<"out of while\n";
    start = display(start);

    return 0;
}

void InitializeSingleSource(int svertex)
{
    int i;
    for(i=1; i<=vertices; i++)
    {
        if(i != svertex) start = insertNodeSorted(start, i, INT_MAX, INT_MIN);
        else start = insertNodeSorted(start, i, 0, -1); //distance: 0 , predecessor:-1 for source
    }
    cout<<"Nodes after initialization are: \n\n";
    start = display(start);
}

int emptyOrNot(Node* start)
{
    Node* ptr;
    ptr = start;
    cout<<"in empty or not\n";
    while(ptr != NULL)
    {
        //cout<<"while ";
        if(ptr->processed == 0)
        {
          cout<<"ptr->vno: "<<ptr->vno<<endl;
          cout<<"ptr->processed: "<<ptr->processed<<endl;
          cout<<"returning 1\n";
          return 1;
        }
        //cout<<"ptr->next: "<<ptr->next<<endl;
        ptr = ptr->next;
    }
    cout<<"returning 0\n";
    return 0;
}

Node* insertNodeSorted(Node* start, int vno, int distance, int predecessor)
{
    cout<<"in insertnode\n";
    Node* newnode;
    Node* ptr;
    Node* preptr;
    ptr = start;

    newnode = (Node*)malloc(sizeof(Node));
    newnode->vno = vno;
    newnode->distance = distance;
    newnode->predecessor = predecessor;
    newnode->processed = 0;
    //newnode->data = value;

    if(start == NULL)
    {
        cout<<"empty linked list\n";
        start = newnode;
        newnode->next = NULL;
    }
    else
    {
        cout<<"in else\n";
        if(newnode->distance <= start->distance) //insert in the beginning
        {
            cout<<"first position insertion because "<<newnode->distance<<"<="<<start->distance<<"\n";
            newnode->next = start;
            start = newnode;
            return start;
        }
        while(newnode->distance > ptr->distance && ptr->next != NULL)
        {
            cout<<"while ";
            preptr = ptr;
            ptr = ptr->next;
        }
        if(ptr->next == NULL && newnode->distance > ptr->distance) //insert at the end
        {
            cout<<"insert at end\n";
            ptr->next = newnode;
            newnode->next = NULL;
        }
        else //insert at the appropriate position
        {
            cout<<"insert in between\n";
            newnode->next = ptr;
            preptr->next = newnode;
        }
    }

    return start;
}

Node* display(Node* start)
{
    Node* ptr;
    ptr = start;
    //cout<<"\nQUEUE:   ";
    if(start == NULL) cout<<"Empty\n";
    cout<<"Vertexno\t"<<"Distance\t"<<"Predecessor\t"<<"Processed\n\n";
    while(ptr != NULL)
    {
        cout<<"not yet NULL\n";
        cout<<ptr->vno<<"\t"<<ptr->distance<<"\t"<<ptr->predecessor<<"\t"<<ptr->processed<<endl;
        ptr = ptr->next;
    }
    cout<<"\n";
    return start;
}

Node* extractMin(Node* start)
{
    cout<<"\nIN EXTRACTMIN\n";
    Node* ptr;
    ptr = start;
        while(ptr->processed == 1 && ptr->next != NULL) ptr = ptr->next;
        if(ptr->processed == 0)
        {
            selectedv = ptr->vno;
            cout<<"selectedvertex: "<<selectedv<<endl;
            ptr->processed = 1;
        }
    return start;

}

Node* decreaseKey(Node* start, int edgelength, int adjvertex)
{
    if(start == NULL)
    {
        start = display(start);
        return start;
    }
    cout<<"IN DECREASEKEY\n";
    //start = display(start);
    int replacekey, newkey;
    Node* ptr;
    Node* preptr;
    ptr = start;
    while(ptr->vno != adjvertex)
    {
        preptr = ptr;
        ptr = ptr->next; //distance to be updated of the adjacent vertex
        //preptr = ptr;
    }

    Node* ptr1 = start;
    while(ptr1->vno != selectedv) ptr1 = ptr1->next;

    replacekey = ptr->distance;
    cout<<"replacekey: "<<replacekey<<endl;
    newkey = ptr1->distance + edgelength;

    if(newkey >= replacekey)
    {
        cout<<"the newkey should be less than the previous key\n";
        //return start;
    }
    else if(ptr->processed == 1) cout<<"Already processed\n";
    else
    {
                if(ptr->next == NULL)
                {
                    cout<<"in if(last element)\n";
                    cout<<"preptr->vno: "<<preptr->vno<<endl;
                    cout<<"preptr->distance: "<<preptr->distance<<endl;
                    preptr->next = NULL;

                    free(ptr);
                }
                else if(ptr == start)
                {
                    cout<<"in elseif(first element)\n";
                    start = start->next;
                    free(ptr);
                }
                else
                {
                    cout<<"in else\n";
                    preptr->next = ptr->next;
                    free(ptr);
                }
                //start = display(start);
                cout<<"adjacentvertex is: "<<adjvertex<<endl;
                cout<<"newkey is: "<<newkey<<endl;
                cout<<"predecessor is: "<<ptr1->vno<<endl;
                cout<<"distancepreviousvertex: "<<ptr1->distance<<endl;
                start = display(start);
                start = insertNodeSorted(start, adjvertex, newkey, ptr1->vno);
    }
    return start;
}

