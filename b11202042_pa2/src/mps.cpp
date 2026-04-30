#include<iostream>
#include<vector>
#include<algorithm>
#include <utility>
using namespace std;


// functions
int MPS(int n, int* C, int** m);
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

    int** m = new int*[n];
    for (int i = 0; i < n; i++){
        m[i] = new int[n - i]; // new table but upper triangle M(i, j) = M[i, j - i]
    }
    for (int i = 0; i < n; i++){
        m[i][0] = 0; // init to 0
    }

    int mps = MPS(n, C, m);

    cout << mps << endl;

    // cout << n << endl;
    // for (int i = 0; i < n; i++){
    //     cout << C[i] << " ";
    // }
    return 0;
}


// Function Implementation

int MPS(int n, int* C, int** m){
    for (int l = 1; l < n; l++){
        for (int i = 0; i < n - l; i++){
            int j = i + l;
            int k = C[j];

            if (k == i){ // case 3
                m[i][l] = 1 + ((l == 1) ? 0 : m[i + 1][l - 2]);
            }
            else if (k < i || k > j){ // case 1
                m[i][l] = m[i][l - 1];
            }
            else{ // case 2
                int right = ((j == k + 1) ? 0 : m[k + 1][j - k - 2]);
                m[i][l] = max(m[i][k - i - 1] + 1 + right, m[i][l - 1]);
            }
        }
    }

    return m[0][n - 1];
}