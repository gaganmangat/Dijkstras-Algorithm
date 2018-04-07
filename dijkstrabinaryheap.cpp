#include <iostream>

using namespace std;

static int n = 0; //no of unprocessed vertices
int svertex;

struct node
{
    int vno;
    int distance;
    int predecessor;
    //int processed = 0;
};

struct node1
{
    int vno;
    int distance;
    int predecessor;
};
struct node1 answer[10];

int vertices;
int edges;
int k = 0;
int selectedv;

int initializeSingleSource(int svertex, struct node heap[10], int n);
int insertHeap(struct node heap[10], int vno, int distance, int predecessor, int n);
int display(struct node heap[10], int n);
int extractMin(struct node heap[10], int n);
int decreaseKey(struct node heap[10], int edjelength, int adjvertex, int n);
//int heapify(struct node heap[10], int n);

int main()
{
    cout<<"Enter number of vertices\n";
    cin>>vertices;
    cout<<"Enter number of edges\n";
    cin>>edges;

    int g[vertices][vertices]; //assuming vertices are numbered as 1,2,3,....
    int i, j;

    for(i=1; i<=vertices; i++) //initializing the graph
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

    struct node heap[10];

    n = initializeSingleSource(svertex, heap, n);

    while(n != 0)
    {
        //cout<<"not empty yet\n";
        n = extractMin(heap, n);

        for(j=1; j<=vertices; j++)
        {
            //cout<<"in MAIN FOR LOOP RELAX\n";
            cout<<"selectedvertex: "<<selectedv<<"  j: "<<j<<endl;
            if(g[selectedv][j] != 0)
            {
                //j is the adjacent vertex
                cout<<"weight of adjacent vertex "<<j<<" of "<<selectedv<<"is: "<<g[selectedv][j]<<endl;
                int length = g[selectedv][j];
                n = decreaseKey(heap, length, j, n);
                n= display(heap, n);
            }
            cout<<"out of if\n";
        }
        cout<<"out of for\n";
    }
    n = display(heap, n);

    cout<<"ANSWER IS: \n\n";
    for(int v=0; v<k; v++)
    {
        cout<<answer[v].vno<<"\t"<<answer[v].distance<<"\t"<<answer[v].predecessor<<endl;
    }

    return 0;
}

int initializeSingleSource(int svertex, struct node heap[10],int n)
{
    int i;
    //cout<<"value of n at the start of initialize: "<<n<<endl;
    for(i=1; i<=vertices; i++)
    {
        n++;
        if(i != svertex) n = insertHeap(heap, i, INT_MAX, INT_MIN, n);
        else n = insertHeap(heap, i, 0, -1, n); //distance: 0 , predecessor:-1 for source
    }
    cout<<"Nodes after initialization are: \n\n";
    n = display(heap, n);
    return n;
}

int insertHeap(struct node heap[10], int vno, int distance, int predecessor, int n)
{
    int pos = n;
    cout<<"value of n is: "<<n<<endl;
    heap[n].vno = vno;
    heap[n].distance = distance;
    heap[n].predecessor = predecessor;

    while(pos > 1)
    {
        //cout<<"while\n";
        int par = pos/2;
        cout<<"par: "<<par<<"pos: "<<pos<<endl;
        cout<<"a[par]: "<<heap[par].distance<<"  a[pos]: "<<heap[pos].distance<<endl;
        if(heap[pos].distance >= heap[par].distance && par >= 1)
        {
            cout<<"in if\n";
            return n;
        }
        else
        {
            cout<<"in else\n";
            swap(heap[par], heap[pos]);
            /*int temp = heap[pos];
            heap[pos] = heap[par];
            heap[par] = temp;*/
            pos = par;
        }
    }
    return n;
}
int display(struct node heap[10], int n)
{
    cout<<"value of n in display is: "<<n<<endl;
    for(int i=1; i<=n; i++)
    {
        cout<<"heap["<<i<<"]:  "<<heap[i].vno<<"\t"<<heap[i].distance<<"\t"<<heap[i].predecessor<<endl;
    }
    return n;
}

int extractMin(struct node heap[10], int n)
{
    answer[k].vno = heap[1].vno;
    answer[k].distance = heap[1].distance;
    answer[k].predecessor = heap[1].predecessor;
    selectedv = answer[k].vno;

    //cout<<"heap[1]: "<<heap[1].vno<<"\t"<<heap[1].distance<<"\nheap[n]: "<<heap[n].vno<<"\t"<<heap[n].distance<<endl;
    //cout<<"n is: "<<n<<endl;
    heap[1] = heap[n];
    n--;
    //cout<<"new value of n is: "<<n<<endl;


    int ptr = 1;
    int left = 2;
    int right = 3;

    //cout<<"a[ptr]: "<<heap[ptr].vno<<"  a[left]: "<<heap[left].vno<<"  a[right]: "<<heap[right].vno<<endl;

    while(left <= n)
    {
        if(heap[ptr].distance < heap[left].distance && heap[ptr].distance < heap[right].distance) return n;

        if(heap[right].distance > heap[left].distance)
        {
            swap(heap[ptr], heap[left]);
            ptr = left;
        }
        else
        {
            swap(heap[ptr], heap[right]);
            ptr = right;
        }
        left = 2*ptr;
        right = left + 1;
    }


    //n = heapify(heap, n);
    cout<<"extracted vno,distance is: "<<answer[k].vno<<"\t"<<answer[k].distance<<endl;
    k++;
    return n;
}

int decreaseKey(struct node heap[10], int edgelength, int adjvertex, int n)
{
    if(n == 0)
    {
        n = display(heap, n);
        return n;
    }
    cout<<"IN DECREASEKEY\n";
    //start = display(start);
    int replacekey, newkey;
    //Node* ptr;
    //Node* preptr;
    //ptr = start;
    int i = 1;
    int j = 1;
    while(heap[i].vno != adjvertex)
    {
        i++;
    }

    int t = k-1;
    while(t--)
    {
        if(answer[t].vno == heap[i].vno)
        {
            cout<<"vertex already processed\n";
            return n;
        }
    }

    //Node* ptr1 = start;
    //while(heap[j].vno != selectedv) j++;

    replacekey = heap[i].distance;
    cout<<"replacekey: "<<replacekey<<endl;
    newkey = answer[k-1].distance + edgelength;
    cout<<"newkey: "<<newkey<<endl;

    /*cout<<"Enter the value to be replaced\n";
    cin>>replacekey;
    cout<<"Enter the new value\n";
    cin>>newkey;*/
    int flag = 0;
    //Node* newnode = (Node*)malloc(sizeof(Node));
//    Node* preptr;

    if(newkey >= replacekey)
    {
        cout<<"the newkey should be less than the previous key\n";
        //return start;
    }
    //else if(ptr->processed == 1) cout<<"Already processed\n";
    else
    {
        cout<<"in else decreasekey\n";
        heap[i].distance = newkey;
        heap[i].predecessor = selectedv;
    }

    swap(heap[1], heap[i]);
    int ptr = 1;
    int left = 2;
    int right = 3;

    //cout<<"a[ptr]: "<<heap[ptr].vno<<"  a[left]: "<<heap[left].vno<<"  a[right]: "<<heap[right].vno<<endl;

    while(left <= n)
    {
        if(heap[ptr].distance < heap[left].distance && heap[ptr].distance < heap[right].distance) return n;

        if(heap[right].distance > heap[left].distance)
        {
            swap(heap[ptr], heap[left]);
            ptr = left;
        }
        else
        {
            swap(heap[ptr], heap[right]);
            ptr = right;
        }
        left = 2*ptr;
        right = left + 1;
    }
    //n = heapify(heap, n);
    //start = display(start);
    //if(flag == 0) cout<<"Value not present\n";
    return n;
}
/*
int heapify(struct node heap[10], int n)
{
    int ptr = 1;
    int left = 2;
    int right = 3;

    //cout<<"a[ptr]: "<<heap[ptr].vno<<"  a[left]: "<<heap[left].vno<<"  a[right]: "<<heap[right].vno<<endl;

    while(left <= n)
    {
        if(heap[ptr].distance < heap[left].distance && heap[ptr].distance < heap[right].distance) return n;

        if(heap[right].distance > heap[left].distance)
        {
            swap(heap[ptr], heap[left]);
            ptr = left;
        }
        else
        {
            swap(heap[ptr], heap[right]);
            ptr = right;
        }
        left = 2*ptr;
        right = left + 1;
    }
    return n;
}
*/
