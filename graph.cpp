#include "graph.h"

Graph::Graph(int n, int m) {
    this->n = n;
    this->m = m;
    this->curr_arc = 0;
    N_minus = delta_plus = delta_minus = vector<vector<int>>(n + 1);
    adj_matrix = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));

    score = vector<int>(n + 1);
    x = y = vector<float>(n + 1);
    arc_cost = vector<vector<int>>(n + 1, vector<int>(n + 1));
    key_arc = vector<pair<int, int>>(m);
}

float Graph::dist(int i, int j) {
    float dx = (x[i] - x[j]), dy = (y[i] - y[j]);
    float dist = sqrt(dx*dx + dy*dy);
    return dist;
}

void Graph::insert_edge(int i, int j) {
    this->arc_cost[i][j] = dist(i, j);

    this->arc_key[i][j] = curr_arc;
    this->key_arc[curr_arc] = {i, j};
    this->delta_plus[i].push_back(curr_arc);
    this->delta_minus[j].push_back(curr_arc);

    this->N_plus[i].push_back(j);
    this->N_minus[j].push_back(i);

    adj_matrix[i][j] = 1;

    this->curr_arc += 1;
}

void Graph::read_cordinates(fstream& entrada) {
    vector<float> x(n + 1), y(n + 1);
    for(int i = 0; i < n; i++) {
        int u;
        entrada >> u;
        entrada >> x[u] >> y[u];
    }
    int curr_arc = 0;
    //calc as distancias euclidianas
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;
            insert_edge(i, j);
        }
    }
}

vector<int> Graph::get_delta_plus(vector<int> S) {
    //pega de acordo com a notacao
    vector<int> ans;
    for(int u : S) {
        for(int v : N_plus[u]) {
            if(!adj_matrix[u][v]) {
                //se nao ta no grafo adiciona na lista
                ans.push_back(arc_key[u][v]);
            }
        }
    }

    return ans;
}

vector<int> Graph::get_delta_minus(vector<int> S) {
    //pega de acordo com a notacao
    vector<int> ans;
    for(int u : S) {
        for(int v : N_minus[u]) {
            if(!adj_matrix[u][v]) {
                //se nao ta no grafo adiciona na lista
                ans.push_back(arc_key[u][v]);
            }
        }
    }

    return ans;
}