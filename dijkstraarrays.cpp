#include <iostream>
#include <climits>

using namespace std;
const int MAX = 10;
static int n = 0; //no of unprocessed vertices
int svertex;

struct node
{
    int vno;
    int distance;
    int predecessor;
    int processed = 0;
};

int vertices;
int edges;
int k = 1;
int selectedv;

int emptyOrNot(struct node arr[MAX], int n);
int initializeSingleSource(int svertex, struct node arr[MAX], int n);
int insertNode(struct node arr[MAX], int vno, int distance, int predecessor, int n);
int display(struct node arr[MAX], int n);
int extractMin(struct node arr[MAX], int n);
int decreaseKey(struct node arr[MAX], int edjelength, int adjvertex, int n);
int sortArray(struct node arr[MAX], int n);

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

    int s[vertices] = {0};

    cout<<"Enter the source vertex\n";
    cin>>svertex;

    struct node arr[MAX];

    n = initializeSingleSource(svertex, arr, n);

    while( emptyOrNot(arr, n) )
    {
        cout<<"not empty yet\n";
        //cout<<"emptyornot: "<<emptyOrNot(arr, n)<<endl;
        n = extractMin(arr, n);
        cout<<"The selectedv is: "<<selectedv<<endl;
        s[k] = selectedv;
        k++;

        cout<<"ARRAY S CONTAINS THE VERTICES: \n\n";

        for(j=1; j<=vertices; j++)
        {
            cout<<s[j]<<"\t";
        }
        cout<<"\n\n";

        for(j=1; j<=vertices; j++)
        {
            //cout<<"in MAIN FOR LOOP RELAX\n";
            cout<<"selectedvertex: "<<selectedv<<"  j: "<<j<<endl;
            if(g[selectedv][j] != 0)
            {
                //j is the adjacent vertex
                cout<<"weight of adjacent vertex "<<j<<" of "<<selectedv<<"is: "<<g[selectedv][j]<<endl;
                int length = g[selectedv][j];
                n = decreaseKey(arr, length, j, n);
                n = display(arr, n);
            }
            //cout<<"out of if\n";
        }
        //cout<<"out of for\n";
        //cout<<"BEFORE NEXT ITERATION\n";
        n = display(arr, n);
    }
    n = display(arr, n);
    cout<<"ARRAY S CONTAINS THE VERTICES: \n\n";

    for(j=1; j<k; j++)
    {
        cout<<s[j]<<"\t";
    }

    return 0;
}

int emptyOrNot(struct node arr[MAX], int n)
{
    int i = 1;
    while(i <= n)
    {
        cout<<"emptyornot while  ";
        if(arr[i].processed == 0) return 1;
        i++;
    }
    return 0;
}

int initializeSingleSource(int svertex, struct node arr[MAX], int n)
{
    int i;
    cout<<"value of n at the start of arr: "<<n<<endl;
    for(i=1; i<=vertices; i++)
    {
        n++;
        if(i != svertex) n = insertNode(arr, i, INT_MAX, INT_MIN, n);
        else n = insertNode(arr, i, 0, -1, n); //distance: 0 , predecessor:-1 for source
    }
    cout<<"Nodes after initialization are: \n\n";
    n = display(arr, n);
    return n;
}

int insertNode(struct node arr[MAX], int vno, int distance, int predecessor, int n)
{
    cout<<"value of n is: "<<n<<endl;
    arr[n].vno = vno;
    arr[n].distance = distance;
    arr[n].predecessor = predecessor;

    n = sortArray(arr, n);
    return n;
}
int display(struct node arr[MAX], int n)
{
    cout<<"value of n in display is: "<<n<<endl;
    for(int i=1; i<=n; i++)
    {
        cout<<arr[i].vno<<"\t"<<arr[i].distance<<"\t"<<arr[i].predecessor<<"\t"<<arr[i].processed<<endl;
    }
    cout<<"\n";
    return n;
}

int sortArray(struct node arr[MAX], int n)
{
    int i, j;
    for(i=1; i<n; i++)
    {
        for(j=i+1; j<=n; j++)
        {
            if(arr[i].distance > arr[j].distance) swap(arr[i], arr[j]);
        }
    }
    return n;
}

int extractMin(struct node arr[MAX], int n)
{
    int i = 1;
    while(arr[i].processed != 0)
    {
        cout<<"while ";
        i++;
    }

    arr[i].processed = 1;
    selectedv = arr[i].vno;

    cout<<"extracted vno,distance is: "<<arr[i].vno<<"\t"<<arr[i].distance<<endl;
    n = display(arr, n);
    return n;
}

int decreaseKey(struct node arr[MAX], int edgelength, int adjvertex, int n)
{
    if(n == 0)
    {
        n = display(arr, n);
        return n;
    }
    cout<<"IN DECREASEKEY\n";

    int i = 1;
    int j = 1;
    while(arr[i].vno != adjvertex) i++;
    while(arr[j].vno != selectedv) j++;

    int replacekey = arr[i].distance;
    cout<<"replacekey: "<<replacekey<<endl;
    int newkey = arr[j].distance + edgelength;
    cout<<"newkey: "<<newkey<<endl;

    if(newkey >= replacekey)
    {
        cout<<"the newkey should be less than the previous key\n";
    }
    else if( arr[i].processed == 1) cout<<"Already processed\n";
    else
    {
        cout<<"in else decreasekey\n";
        arr[i].distance = newkey;
        arr[i].predecessor = j;
        n = sortArray(arr, n);
    }
    return n;
}


