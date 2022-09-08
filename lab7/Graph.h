#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <math.h> 

#define INFINITY 2147483647 //defining term, infinity to be the max size of an int number. 2^31 - 1


using namespace std;
class Graph{
  private:
    int v; //number of vertices
    //adjacency list, associates: adjacent vertex and weight
    list<pair<int, int>> *adj;
  public:
    Graph(int _v){
      v = _v;
      adj = new list<pair<int, int>>[v];
    }
    void addEdge(int a, int b, int weight){
       pair<int,int> p = make_pair(b, weight);
       adj[a].push_back(make_pair(b, weight));
       adj[b].push_back(make_pair(a, weight));
    }
    
    int shortestPath(int source, int dest, ofstream& of){
      set<pair<int,int>> g_set;      
      vector<int> distances(v, INFINITY);
      //inserting our source into the priority queue and setting it's distance to 0.
      distances[source] = 0;
      g_set.insert(make_pair(0, source));
      
      while(!g_set.empty()){
        pair<int, int> temp = *(g_set.begin());
        g_set.erase(g_set.begin());
        int v1 = temp.second;

        for(auto it = adj[v1].begin(); it != adj[v1].end(); it++){
          int v2 = (*it).first;
          int w = (*it).second;

          if(distances[v2] > distances[v1] + w){
            if(distances[v2] != INFINITY)
              g_set.erase(g_set.find(make_pair(distances[v2], v2)));

            distances[v2] = distances[v1] + w;
            g_set.insert(make_pair(distances[v2], v2));
          }
        }
      }
    of << distances[dest];
  }
};