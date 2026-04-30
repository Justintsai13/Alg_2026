#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// functions
int MPS(int n, const int* C, int* M);

vector<pair<int, int>> Traceback(int n, const int* C, int* M);

void FindChord(int i, int j, int n, const int* C, int* M, vector<pair<int, int>>& r);

int main(){
    int n;
    cin >> n;
    if ((n == 0) || (n % 2 == 1)) return 0;

    int* C = new int[n];
    for (int i = 0; i < n / 2; i++){
        int u, v;
        cin >> u >> v;
        C[u] = v;
        C[v] = u;
    }

    cout << n << endl;
    for (int i = 0; i < n; i++){
        cout << C[i] << " ";
    }
}