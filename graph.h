#include <bits/stdc++.h>

using namespace std;

class Graph {
    public:
    int n, m, curr_arc;
    vector<vector<int>> N_plus, N_minus, delta_plus, delta_minus, adj_matrix;

    //custo e premio
    vector<float> x, y; //cordenadas
    vector<int> score; //premio s_i
    vector<float> arc_cost; //custo do arco (i, j)

    //id de arco
    vector<pair<int, int>> key_arc;
    vector<vector<int>> arc_key;
    
    Graph(int);
    float dist(int, int);
    void insert_edge(int, int);
    void read_cordinates();
    vector<int> get_delta_plus(vector<int>);
    vector<int> get_delta_minus(vector<int>);
};
