#include <iostream>
#include <climits>  // INT_MAX for
#include <vector>   // std::vector for
using namespace std;

// Kullanicinin girmedigi vertex için minimum key degerini bulan yardimci fonksiyon
int minKey(const vector<int>& key, const vector<bool>& mstSet)
{
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < key.size(); v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Olusturulan MST'yi yazdiran yardimci fonksiyon
void printMST(const vector<int>& parent, const vector<vector<int>>& graph)
{
    int total_cost = 0;
    cout << "Kenar \tAgirlik\n";
    for (int i = 1; i < parent.size(); i++) {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
        total_cost += graph[i][parent[i]];
    }
    cout << "MST'nin toplam maliyeti: " << total_cost << endl;
}

// Adjacency matrix kullanarak MST'yi olusturan ve yazdiran fonksiyon
void primMST(vector<vector<int>>& graph)
{
    int V = graph.size(); // Grafin vertex sayisi
    vector<int> parent(V); // Olusturulan MST'yi saklayan array
    vector<int> key(V, INT_MAX); // Kesimdeki minimum agirlikli kenari secmek icin kullanilan key degerleri
    vector<bool> mstSet(V, false); // MST'de yer almayan vertex'leri temsil eden array

    // MST'de her zaman ilk vertex'i dahil et
    key[0] = 0;
    parent[0] = -1; // Ilk dugum her zaman MST'nin kokudur

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph);
}

// Ana fonksiyon
int main()
{
    int V;
    cout << "Grafin boyutunu girin (nxn matris icin n degeri): ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Graf icin adjacency matrisini girin (" << V << "x" << V << " matris):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    // Cözümü yazdir
    primMST(graph);

    return 0;
}

