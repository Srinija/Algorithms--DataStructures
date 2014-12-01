#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

#define RETRY_TIME 200
#define MAX_NODE_SIZE 40

struct EdgeNode {
    int name;
    struct EdgeNode *next;
};

struct VertexNode {
    int name;
    struct EdgeNode *first;
    struct VertexNode *next;
};

class Graph {
public:
    Graph(): edgeNum(0), vertexNum(0) {
        VertexNode *VnodeList = new VertexNode;     //A pointer to the linked list of vertices
        VnodeList = NULL;
    }
    Graph(const Graph& graph) {
        this->edgeNum = 0;
        this->vertexNum = 0;
        this->VnodeList = NULL;
        EdgeNode *enode = new EdgeNode;
        VertexNode *vnode = new VertexNode;
        for (vnode = graph.VnodeList; vnode != NULL; vnode = vnode->next) {
            this->insert_vertex(vnode->name);
            for (enode = vnode->first; enode != NULL; enode = enode->next) {
                this->insert_edge(vnode->name, enode->name);
            }
        }
    }
    ~Graph() {edgeNum = 0; vertexNum = 0; delete []VnodeList;}
    void insert_edge(int v, int e);
    void delete_edge(int v, int ei);
    void append_edge(int src, int dest);
    void insert_vertex(int v);
    void delete_vertex(int v);
    VertexNode *SearchVnode(int v);
    int num_edges(int v);
    void SubstituteEnodes(int from, int to);
    void delete_self(int v);
    void ReadGraphFromText();
    int GraphContraction();
    void DisplayGraph();
    void GetRandomEdge(int &v, int &e);
    
private:
    struct VertexNode *VnodeList;
    int edgeNum;
    int vertexNum;
};

int main() {
    Graph g;
    g.ReadGraphFromText();
    
    int mincut = 10000;
    for (int i = 0; i < RETRY_TIME; i++) {
        Graph gTemp = Graph(g);
        int temp = gTemp.GraphContraction();
        if (mincut > temp) mincut = temp;
    }
    mincut = mincut / 2; // because the number of edges is doubled
    cout << "minimum cut is " << mincut << endl; // mincut is double times the real number of edges
    
    return (0);
}

//This function reads from file and adds them to the datastructure

void Graph::ReadGraphFromText() {
    ifstream ifs;
    ifs.open("KargerMinCut.txt");
    string line;
    stringstream strstream;
    int v, e;
    
    while (getline(ifs, line)) {
        strstream << line;
        strstream >> v;
        this->insert_vertex(v);
        while (strstream >> e) {
            this->insert_edge(v, e);
        }
        strstream.clear();
    }
    ifs.close();
}

int Graph::GraphContraction() {
    while (this->vertexNum > 2) { // contract edges until vertexNum is 2
        int e1, e2;
        srand( (unsigned)time(NULL) );
        this->GetRandomEdge(e1, e2);
        this->append_edge(e1, e2); // append all the nodes from v1 to v2
        this->delete_vertex(e1); // delete v1
        this->SubstituteEnodes(e1, e2); // substitute all (x, e1) with (x, e2)
        this->delete_self(e2); // delete selp-loop in v2
    }
    return this->edgeNum;
}

void Graph::DisplayGraph() {
    for (VertexNode *vnode = this->VnodeList; vnode != NULL; vnode = vnode->next) {
        cout << vnode->name << " ";
        EdgeNode *enode = vnode->first;
        while (enode != NULL) {
            cout << enode->name << " ";
            enode = enode->next;
        }
        cout << endl;
    }
}

void Graph::insert_edge(int v, int e) {
    EdgeNode *enode = new EdgeNode;
    enode->name = e;
    enode->next = NULL;
    VertexNode *vnode = new VertexNode;
    vnode = SearchVnode(v);
    
    if (vnode->first == NULL) { // insert enode for the first time
        vnode->first = enode;
    }
    else { // not the first time
        EdgeNode *curr = vnode->first;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = enode;
    }
    this->edgeNum++;
}

void Graph::delete_edge(int v, int ei) {
    EdgeNode *curr = new EdgeNode;
    EdgeNode *prev = new EdgeNode;
    VertexNode *vnode = new VertexNode;
    vnode = this->SearchVnode(v);
    curr = vnode->first;
    prev = NULL;
    
    if (ei == 0) vnode->first = curr->next; // if the first enode
    else { // if not the first enode
        for (int i = 0; i < ei; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = prev->next->next;
        curr->next = NULL;
        curr = NULL;
    }
    this->edgeNum--;
    delete curr, prev, vnode;
}

void Graph::append_edge(int src, int dest) {
    VertexNode *vsrc = new VertexNode;
    vsrc = this->SearchVnode(src);
    for (EdgeNode *esrc = vsrc->first; esrc != NULL; esrc = esrc->next) {
        this->insert_edge(dest, esrc->name);
    }
}

void Graph::insert_vertex(int v) {
    VertexNode *vnode = new VertexNode;
    vnode->name = v;
    vnode->next = NULL;
    vnode->first = NULL;
    VertexNode *curr = new VertexNode;
    curr = this->VnodeList;
    if (curr == NULL) { // insert vnode for the first time
        this->VnodeList = vnode;
    }
    else { // not the first time
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = vnode;
    }
    this->vertexNum++;
}

void Graph::delete_vertex(int v) {
    VertexNode *curr = new VertexNode;
    VertexNode *prev = new VertexNode;
    curr = this->VnodeList;
    prev = NULL;
    int num = 0;
    while (curr->next != NULL && curr->name != v) {
        prev = curr;
        curr = curr->next;
    }
    if (curr->name != v) cerr << "No Vnode named " << v << " been found" << endl;
    else { // found the vnode named v
        if (prev == NULL) { // if the first vnode
            num = this->num_edges(v);
            this->VnodeList = curr->next;
        }
        else { // if not the first vnode
            num = this->num_edges(v);
            prev->next = curr->next;
            curr->next = NULL;
        }
        this->vertexNum--;
        this->edgeNum -= num;
    }
    delete curr, prev;
}

VertexNode* Graph::SearchVnode(int v) {
    VertexNode *ret = new VertexNode;
    ret = this->VnodeList;
    while (ret->name != v && ret->next != NULL) {
        ret = ret->next;
    }
    if (ret->name == v) return ret;
    else return NULL;
}

int Graph::num_edges(int v) {
    VertexNode *vnode = new VertexNode;
    vnode = this->SearchVnode(v);
    EdgeNode *enode = new EdgeNode;
    enode = vnode->first;
    int ret = 0;
    if (enode == NULL) return ret;
    else {
        ret++;
        while (enode->next != NULL) {
            enode = enode->next;
            ret++;
        }
        return ret;
    }
}

void Graph::SubstituteEnodes(int from, int to) {
    VertexNode *vnode = new VertexNode;
    EdgeNode *enode = new EdgeNode;
    for (vnode = this->VnodeList; vnode != NULL; vnode = vnode->next) {
        for (enode = vnode->first; enode != NULL; enode = enode->next) {
            if (enode->name == from) enode->name = to;
        }
    }
}

void Graph::delete_self(int v) {
    VertexNode *vnode = new VertexNode;
    vnode = this->SearchVnode(v);
    EdgeNode *enode = new EdgeNode;
    enode = vnode->first;
    int ei = 0;
    do {
        if (enode->name == v) {
            enode = enode->next;
            this->delete_edge(v, ei);
        }
        else {
            enode = enode->next;
            ei++;
        }
    } while (enode != NULL);
}

void Graph::GetRandomEdge(int &v, int &e) {
    int vi = rand() % (this->vertexNum);
    VertexNode *vnode = new VertexNode;
    vnode = this->VnodeList;
    for (int i = 0; i < vi; i++) {
        vnode = vnode->next;
    }
    int ei = rand() % (this->num_edges(vnode->name));
    EdgeNode *enode = new EdgeNode;
    enode = vnode->first;
    for (int j = 0; j < ei; j++) {
        enode = enode->next;
    }
    v = vnode->name;
    e = enode->name;
}