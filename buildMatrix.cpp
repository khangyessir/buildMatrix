class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        auto topologicalSort = [](int n, const vector<vector<int>>& conditions) {
            unordered_map<int, vector<int>> graph;
            vector<int> degree(n + 1, 0);
            for(const auto& cond : conditions) {
                int u = cond[0];
                int v = cond[1];
                graph[u].push_back(v);
                degree[v]++;
            }
            queue<int> q;
            for(int i=1; i<=n; i++) {
                if(degree[i] == 0) {
                    q.push(i);
                }
            }
            vector<int> topo_order;
            while(!q.empty()) {
                int node = q.front();
                q.pop();
                topo_order.push_back(node);
                for(int nei : graph[node]) {
                    if(--degree[nei] == 0) {
                        q.push(nei);
                    }
                }
            }
            if(topo_order.size() == n) {
                return topo_order;
            } else {
                return vector<int>();
            }
        };
        vector<int> rowOrder = topologicalSort(k, rowConditions);
        vector<int> colOrder = topologicalSort(k, colConditions);
        if(rowOrder.empty() || colOrder.empty()) {
            return {};
        }
        unordered_map<int, int> rowPos, colPos;
        for(int i=0; i<k; i++) {
            rowPos[rowOrder[i]] = i;
            colPos[colOrder[i]] = i;
        }
        vector<vector<int>> matrix(k, vector<int>(k, 0));
        for(int j=1; j<=k; j++) {
            int r = rowPos[j];
            int c = colPos[j];
            matrix[r][c] = j;
        }
        return matrix;
    }
};