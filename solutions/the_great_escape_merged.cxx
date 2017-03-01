#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
struct Connection
{
    int n1;
    int n2;
};

struct Node
{
    int no;
    bool visited;
};

int length;
bool DFS(const vector<Node*>& nodes, const vector<Connection*>& connections, const vector<int>& gateways, Node* v)
{
    length++;
    v->visited = true;
    for(int g : gateways)
    {
        if(g == v->no) return true;    
    }
    
    
    vector<int> outConnections;
    
    for(Connection* c:connections)
    {
        if(c->n1 == v->no)
        {
            outConnections.push_back(c->n2);  
        }
        else if(c->n2 == v->no)
        {
            outConnections.push_back(c->n1); 
        }
  
    }
    
    for(int c:outConnections)
    {
        for(Node* n: nodes)
        {
            if(n->no != v->no && n->no == c && !n->visited)
            {
                if(DFS(nodes, connections, gateways, n))
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    
    vector<Node*> nodes;
    for(int i = 0; i<N; ++i)
    {
        Node* n = new Node();
        n->no = i;
        n->visited = false;
        nodes.push_back(n);
    }
    
    vector<Connection*> connections;
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        
        Connection* c = new Connection();
        c->n1 = N1;
        c->n2 = N2;
        connections.push_back(c);
    }
    
    vector<int> gateways;
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        
        gateways.push_back(EI);
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        cerr << "gateway: " << SI <<  endl;
        
        vector<int> outConnections;
        
        for(Connection* c:connections)
        {
            if(c->n1 == SI)
            {
                outConnections.push_back(c->n2);  
            }
            else if(c->n2 == SI)
            {
                outConnections.push_back(c->n1); 
            }
      
        }
        
        int result = outConnections[0];
        for(int c: outConnections)
        {
            for(int g: gateways)
            {
                if(c == g)
                {
                    result = c;    
                }
            }
        }
        
 
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << SI << " " << result << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
    }
}