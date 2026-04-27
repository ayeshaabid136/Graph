#include <iostream>
#include<queue>
#include <climits>
using namespace std;

struct Vertex;     //forward declaration

struct Edge{
    Vertex* v;
    Edge* next;
    int weight;
};

struct Vertex{
    int data;
    Vertex* next;
    Edge* edgeList;
    bool visited;
    Vertex* parent;   //will use for path
};

struct EdgeList{  //this struct is for "Kruskal" for storing all edges in a list
    int u , v;
    int w;
};

 Vertex* v = NULL;


//Add Vertex
Vertex* AddVertex(Vertex* v, int value){
    Vertex* temp = v;
    while(temp != NULL){
        if(temp->data == value){
            cout<<"Vertex already Exist\n";
            return v;
        }
        temp = temp->next;
    }
    Vertex* newVertex = new Vertex;
    newVertex->data = value;
    newVertex->edgeList = NULL;
    newVertex->visited = false;
    newVertex->next = v;
    cout<<"Vertex Added\n";
    return newVertex;   
}

//Add Edge
void AddEdge(Vertex* v, int src, int dest, int weight, bool IsDirected){
    //1. finding source vertex
    Vertex* srcVertex = v;    
    while(srcVertex != NULL){
        if(srcVertex->data == src)  break;
        srcVertex = srcVertex->next;
    }
    //2. finding destination vertex
    Vertex* destVertex = v;
    while(destVertex != NULL){
        if(destVertex->data == dest)  break;
        destVertex = destVertex->next;
    }
    //3. check that src and dest Vertiex exist or not
    if(srcVertex == NULL || destVertex == NULL){
        cout<<"Source or Destination vertex Not exist\n";
        return;
    }
    //4.  Now Add Edge
    Edge* newEdge = new Edge;
    newEdge->v = destVertex;   //address of destVertex put in newedge
    newEdge->weight = weight;   //store weight
    newEdge->next = srcVertex->edgeList;   //ye is liye ky old edge delete na hon new edge agy hi add hojayegi
    srcVertex->edgeList = newEdge;    //new node at start of vertex ki edgeList
    
    //5. if UnDirected Graph then, reversly add edge.(dest -> src)
    if(!IsDirected){
        Edge* reverseEdge = new Edge;
        reverseEdge->v = srcVertex;
        reverseEdge->weight = weight;
        reverseEdge->next = destVertex->edgeList;
        destVertex->edgeList = reverseEdge;
    }
    cout<<"Edge Added with weight: " << weight << "\n";
}


//Remove Edge
void RemoveEdge(Vertex* v, int src, int dest){
    Vertex* srcVertex = v;
    //find source vertex 
    while(srcVertex != NULL && srcVertex->data != src){
        srcVertex = srcVertex->next;
    }
    if(srcVertex == NULL){
        cout<<"Source Vertes Not Exist\n";
        return;
    }
    Edge* pre = NULL;
    Edge* cur = srcVertex->edgeList;
    while(cur != NULL){
        if(cur->v->data == dest){
            if(pre == NULL){
                srcVertex->edgeList = cur->next;
            }
            else{
                pre->next = cur->next;
            }
            delete cur;
            cout<<"Edge Removed\n";
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    cout<<"edge Not found\n";
}

//Remove Vertex 
void RemoveVertex(Vertex* v, int value){
    //1. remove all its edges
    Vertex* temp = v;
    while(temp != NULL){
        RemoveEdge(v, temp->data, value);
        temp = temp->next;
    }
    //2. find vertex to delete
    Vertex* pre = NULL;
    Vertex* cur = v;
    while(cur != NULL && cur->data != value){
        pre = cur;
        cur = cur->next;
    }
    if(cur == NULL){
        cout<< "Vertex Not Found\n";
        return;
    }
    //3. Delete its edge list
    Edge* e = cur->edgeList;
    while(e != NULL){
        Edge* t = e;
        e =  e->next;
        delete t;
    }
    //4. remove vertex from list
    if(pre == NULL){
        v = cur->next;
    }
    else{
        pre->next = cur->next;
    }
    delete cur;
    cout<< "Vertex Removed!\n";
}


//Display
void Display(Vertex* v){
    Vertex* temp = v;
    while(temp != NULL){
        cout<<"Vertex "<< temp->data <<"->";

        //us vertex ki sab edges print 
        Edge* e = temp->edgeList;
        while(e != NULL){
            cout<< "(" << e->v->data <<" , " << e->weight << ") ";
            e = e->next;
        }
        cout<<"NULL\n";
        temp = temp->next;
    }
}
  

//BFS
void BFS(Vertex* v) {    

    if (v == NULL) {
        cout << "Graph is empty\n";
        return;
    }

    queue<Vertex*> q;

    //visit start vertex  and push them
    v->visited = true;
    q.push(v);          // Enqueue__putting vertex in queue
    cout << "BFS: ";

    while (!q.empty()){

        // Front nikalo or print
        Vertex* V = q.front();  // Dequeue
        q.pop();
        cout << V->data << " ";

        // Us vertex ki saari edges dekho
        Edge* e = V->edgeList;
        while (e != NULL) {
            if (e->v->visited == false) {
                e->v->visited = true;
                q.push(e->v);   // add in the Queue 
            }
            e = e->next;
        }
    }
    cout << endl;

    // Visited reset karo
    Vertex* temp = v;
    while (temp != NULL) {
        temp->visited = false;
        temp = temp->next;
    }
}

//Out-Degree
int OutDegree(Vertex* v, int value) {

    // find Vertex 
    Vertex* temp = v;
    while (temp != NULL) {
        if (temp->data == value) break;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Vertex not found\n";
        return 0;
    }

    // OutDegree 
    int count = 0;
    Edge* e = temp->edgeList;
    while (e != NULL) {
        count++;
        e = e->next;
    }
    cout<<"Out-Degree of " << value << " = " << count <<endl ;
    return count;
}

//In-Degree
int InDegree(Vertex* v, int value){
    Vertex* temp = v;
    while(temp != NULL && temp->data != value){
        temp = temp->next;
    }
    if(temp == NULL){
        cout<<"Vertex Not Found\n";
        return 0;
    }
    int count = 0;
    Vertex* cur = v;
    while(cur != NULL){
        Edge* e = cur->edgeList;
        while(e != NULL){
            if(e->v == temp){
                count++;
            }
            e = e->next;
        }
        cur = cur->next;
    }
    cout<<"In-Degree of " << value << " = " << count <<endl ;
    return count;
    
}

//SumOfDegrees
void SumOfDegrees(Vertex* v){
    Vertex* temp = v;
    int total = 0;
    while(temp != NULL){

        int in = InDegree(v, temp->data);
        int out = OutDegree(v, temp->data);

        total += (in + out);
        temp = temp->next;
    }
    cout<<" Sum Of Degrees = " << total <<endl;
}

//path
void FindPathBFS(Vertex* v, int src, int dest) {

    Vertex* start = v;
    // find source
    while (start != NULL && start->data != src) {
        start = start->next;
    }

    if (start == NULL) {
        cout << "Source not found\n";
        return;
    }
     //BFS
    queue<Vertex*> q;

    start->visited = true;
    start->parent = NULL;
    q.push(start);

    Vertex* destination = NULL;
    while (!q.empty()) {
        Vertex* v = q.front();
        q.pop();

        if (v->data == dest) {
            destination = v;
            break;
        }

        Edge* e = v->edgeList;
        while (e != NULL) {

            if (!e->v->visited) {
                e->v->visited = true;
               e->v->parent = v;   // store parent
                q.push(e->v);
            }

            e = e->next;
        }
    }
    //if no path
    if (destination == NULL) {
        cout << "No Path\n";
    }
    else {
        cout << "Path: ";   //print path(reverse)

        Vertex* cur = destination;
        while (cur != NULL) {
            cout << cur->data << " ";
            cur = cur->parent;
        }
    }
    // reset visited
    Vertex* temp = v;
    while (temp != NULL) {
        temp->visited = false;
        temp = temp->next;
    }
    cout << endl;
}

//Is Graph Connected
bool IsConnected(Vertex* v) {
    if (v == NULL) return true;

    queue<Vertex*> q;

    // start from first vertex
    v->visited = true;
    q.push(v);    //push visited vertex in the queue

    // BFS
    while (!q.empty()) {
        Vertex* V = q.front();
        q.pop();

        Edge* e = V->edgeList;
        while (e != NULL) {
            if (!e->v->visited) {
                e->v->visited = true;
                q.push(e->v);
            }
            e = e->next;
        }
    }

    // check all vertices visited or not
    Vertex* temp = v;
    while (temp != NULL) {
        if (!temp->visited) {
            // reset
            Vertex* t = v;
            while (t != NULL) {
                t->visited = false;
                t = t->next;
            }
            return false;
        }
        temp = temp->next;
    }

    // reset
    temp = v;
    while (temp != NULL) {
        temp->visited = false;
        temp = temp->next;
    }
    return true;
}

//Is graph cyclic
bool IsCyclic(Vertex* v) {

    if (v == NULL) return false;

    queue<Vertex*> q;

    v->visited = true;
    q.push(v);

    while (!q.empty()) {
        Vertex* V = q.front();
        q.pop();

        Edge* e = V->edgeList;
        while (e != NULL) {
            // agar neighbor visit nahi hua
            if (!e->v->visited) {
                e->v->visited = true;
                q.push(e->v);
            }
            // agar visited hai then, cycle ho sakti hai
            else if (e->v->visited) {

                // reset
                Vertex* temp = v;
                while (temp != NULL) {
                    temp->visited = false;
                    temp = temp->next;
                }
                return true;
            }
            e = e->next;
        }
    }
    // reset
    Vertex* temp = v;
    while (temp != NULL) {
        temp->visited = false;
        temp = temp->next;
    }
    return false;
}

//Is Adjacent
bool IsAdjacent(Vertex* v, int src, int dest) {

    // 1. source vertex dhoondo
    Vertex* temp = v;
    while (temp != NULL && temp->data != src) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Source not found\n";
        return false;
    }

    // 2. uski edge list check karo
    Edge* e = temp->edgeList;
    while (e != NULL) {
        if (e->v->data == dest) {
            return true;   // edge mil gayi
        }
        e = e->next;
    }
    return false;  // edge nahi mili
}

//Find Neighbours
void FindNeighbours(Vertex* v, int value){
    // 1. vertex dhoondo
    Vertex* temp = v;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Vertex not found\n";
        return;
    }

    // 2. print its edge list
    cout << "Neighbours of " << value << ": ";
    Edge* e = temp->edgeList;
    while (e != NULL) {
        cout << e->v->data << " ";
        e = e->next;
    }
    cout << endl;
}

//Search Vertex
void SearchVertex(Vertex* v, int value){
    Vertex* temp = v;
    while(temp != NULL){
        if(temp->data == value){
            cout<<"Vertex Found: " << value <<endl;
            return;
        }
        temp = temp->next;
    }
    cout<<"Vertex Not Found\n";
}


//Kruskal Only for UnDirected Graph
void kruskal(Vertex* v){
    //1. store all edges in a list
    EdgeList arr[20];
    int n = 0;
    //store edges
    Vertex* temp = v;
    while(temp){
        Edge* e = temp->edgeList;
        while(e){
            arr[n++] = {temp->data, e->v->data, e->weight};
            e = e->next;
        }
        temp = temp->next;
    }

    //2. sort edges using bubble sort
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j].w > arr[j+1].w){
                swap(arr[j], arr[j+1]);
            }
        }
    }

    //3. from sorted data add smallest edge values in the spanning tree, and avoid cycle
    int parent[20];   //array
    for(int i=0; i<20; i++){
        parent[i] = i;
        cout<<"Kruskal MST: \n";

        //MST logic
        for(int i=0; i<n; i++){
            //convert char to int for array indexing
            int u = arr[i].u;
            int v = arr[i].v;
            if(parent[u] != parent[v]){
                cout<< arr[i].u  <<  " - " <<  arr[i].v << " ( " << arr[i].w << " ) \n";

                int old = parent[v];
                for(int j=0; j<20; j++){
                    if(parent[j] == old){
                        parent[j] = parent[u];
                    }
                }
            }
        }
    }
}

//prim
void Prim(Vertex* v) {
    if (!v) return;

    bool visited[20] = {false};

    // start from given vertex
    visited[v->data] = true;
    cout << "Prim MST:\n";

    for (int i = 0; i < 10; i++) {
        int minWeight = 9999;
        Vertex* from = NULL;
        Vertex* to = NULL;

        Vertex* temp = v;
        // scan all visited vertices
        while (temp) {
            if (visited[temp->data]) {
                Edge* e = temp->edgeList;
                while (e) {
                    if (!visited[e->v->data] && e->weight < minWeight) {
                        minWeight = e->weight;
                        from = temp;
                        to = e->v;
                    }
                    e = e->next;
                }
            }
            temp = temp->next;
        }
        // agar koi edge na mile
        if (!to) break;

        cout << from->data << " - " << to->data << " (" << minWeight << ")\n";
        visited[to->data] = true;
    }
}

//Dijkstra Shortest path
void Dijkstra(Vertex* v, int src){

    int INF = 9999;
    int dist[20];
    bool visited[20];

    //Initialization
    for(int i=0; i<20; i++){
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;  //distance of src vertex is "0"

    for(int i=0; i<20; i++){
        int minVertex = -1;
        int minDist = INF;
        
        // find min Distance
        for(int j=0; j<20; j++){
            if(!visited[j] && dist[j] < minDist){
                minDist = dist[j];
                minVertex = j;
            }
        }
        if(minVertex == -1)  break;

        visited[minVertex] = true;

        //find this vertex in the list
        Vertex* temp = v;
        while(temp != NULL && temp->data != minVertex){
            temp = temp->next;
        }

        if(temp == NULL)   continue;

        Edge* e = temp->edgeList;
        while(e != NULL){
            int neighbor = e->v->data;
            if(!visited[neighbor] && dist[minVertex] + e->weight < dist[neighbor]){
                dist[neighbor] = dist[minVertex] + e->weight;
            }
            e = e->next;
        }
    }
    //print
    cout<< "Shortest Distance: \n";
    for(int i=0; i<20; i++){
        if(dist[i] != INF){
            cout<< "From " << src << " To " << i << " = " << dist[i] <<endl;
        }
    }
}




int main(){

    int choice;
    int src, dest, value;
    int weight;
    bool directed;

    do{
        cout << "\n-----ADJACENCY LIST-----\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Remove Edge\n";
        cout << "4. Remove Vertex\n";
        cout << "5. Display Graph\n";
        cout << "6. BFS\n";
        cout << "7. Out Degree\n";
        cout << "8. In Degree\n";
        cout << "9. Sum Of Degree\n";
        cout << "10. Path\n";
        cout << "11. Is connected\n";
        cout << "12. Is Cyclic\n"; 
        cout << "13. Is Adjacent\n";
        cout << "14. Find Neighbours\n";
        cout << "15. Search Vertex\n";
        cout << "16. Kruskal\n";
        cout << "17. Prim\n";
        cout << "18. Dijkstra Shortest Path\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){

            case 1:
                cout << "Enter vertex: ";
                cin >> value;
                v = AddVertex(v, value);
                break;

            case 2:
                cout << "Enter src dest: ";
                cin >> src >> dest;
                cout<<"Enter weight: ";
                cin>> weight;
                cout<< "Enter (1 for directed) and (0 for undirected)";
                cin>> directed;
                AddEdge(v, src, dest, weight, directed);
                break;

            case 3:
                cout<<"enter src and dest to remove edge:";
                cin>> src >> dest;
                RemoveEdge(v, src, dest);
                break;

            case 4: 
                cout<<"Enter vertex to remove:";
                cin>> value;
                RemoveVertex(v, value);
                break;

            case 5:
                Display(v);
                break;

            case 6:
                BFS(v);
                break;

            case 7:
                cout << "Enter vertex: ";
                cin >> value;
                OutDegree(v, value);
                break;
            
            case 8:
                cout << "Enter vertex: ";
                cin >> value;
                InDegree(v, value);
                break;


            case 9:
                 SumOfDegrees(v);
                 break;

            case 10:
                cout<<"Enter src and dest to find Path: ";
                cin>> src >> dest;
                FindPathBFS(v, src, dest);
                break;

            case 11:
                IsConnected(v);
                break;

            case 12:
                 IsCyclic(v);
                 break;

            case 13:
                cout << "Enter src dest : ";
                cin >> src >> dest;
                cout << IsAdjacent(v, src, dest) << endl;
                break;

            case 14:
                cout << "Enter vertex to find Neighbours: ";
                cin >> value;
                FindNeighbours(v, value);
                break;

            case 15:
                cout << "Enter vertex to Search: ";
                cin >> value;
                SearchVertex(v, value);
                break;

            case 16:
                kruskal(v);
                break;

            case 17:
                Prim(v);
                break;

            case 18:
                cout<< "Enter Source: ";
                cin>> src;
                Dijkstra(v, src);
                break;
        }

    }while(choice != 0);

    return 0;
}
