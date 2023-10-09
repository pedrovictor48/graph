#include "graph.h"

Graph::Graph(int n) {
    this->n = n;
    this->curr_arc = 0;
    this->delta_plus = vector<vector<int>>(n + 1, vector<int>(0));
    this->N_plus = vector<vector<int>>(n + 1, vector<int>(0));
    this->N_minus = vector<vector<int>>(n + 1, vector<int>(0));
    this->delta_minus = vector<vector<int>>(n + 1, vector<int>(0));

    this->adj_matrix = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    this->arc_key = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));

    this->score = vector<int>(n + 1);
    this->x = vector<float>(n + 1);
    this->y = vector<float>(n + 1);
    this->key_arc = vector<pair<int, int>>();
}

float Graph::dist(int i, int j) {
    float dx = (x[i] - x[j]), dy = (y[i] - y[j]);
    float dist = sqrt(dx*dx + dy*dy);
    return dist;
}

void Graph::insert_edge(int i, int j) {
    this->arc_cost.push_back(dist(i, j));

    this->arc_key[i][j] = curr_arc;
    key_arc.push_back({i, j});
    this->delta_plus[i].push_back(curr_arc);
    this->delta_minus[j].push_back(curr_arc);

    this->N_plus[i].push_back(j);
    this->N_minus[j].push_back(i);

    adj_matrix[i][j] = 1;
    
    this->curr_arc += 1;
    this->m = curr_arc;
}

void Graph::read_cordinates() {
    vector<float> x(n + 1), y(n + 1);
    for(int i = 0; i < n; i++) {
        int u;
        cin >> u;
        cin >> x[u] >> y[u];
    }
    //calc as distancias euclidianas
    for(int i = 1; i <= this->n; i++) {
        for(int j = 1; j <= this->n; j++) {
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
