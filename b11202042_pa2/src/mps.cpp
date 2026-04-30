#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<fstream>
using namespace std;


// functions
int MPS(int n, int* C, int** m);
void FindChord(int i, int j, int* C, int** m, vector<pair<int, int>>& r);

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr << "Usage: mps <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()){
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int n;
    if (!(inputFile >> n)) return 0;

    // cin >> n;
    // if ((n == 0) || (n % 2 == 1)) return 0;

    // int* C = new int[n];
    // for (int i = 0; i < n / 2; i++){
    //     int u, v;
    //     cin >> u >> v;
    //     C[u] = v;
    //     C[v] = u;
    // }

    int* C = new int[n];
    for (int i = 0; i < n / 2; ++i){
        int u, v;
        inputFile >> u >> v;
        C[u] = v;
        C[v] = u;
    }

    // cout << n << endl;
    // for (int i = 0; i < n; i++){
    //     cout << C[i] << " ";
    // }

    int** m = new int*[n];
    for (int i = 0; i < n; i++){
        m[i] = new int[n - i]; // new table but upper triangle M(i, j) = M[i, j - i]
    }
    for (int i = 0; i < n; i++){
        m[i][0] = 0; // init to 0
    }

    int mps = MPS(n, C, m);
    vector<pair<int, int>> chord;
    FindChord(0, n - 1, C, m, chord);
    sort(chord.begin(), chord.end());

    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()){
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    outputFile << mps << "\n";
    for (const auto& p : chord){
        outputFile << p.first << " " << p.second << "\n";
    }
    outputFile.close();

    // cout << mps << endl;
    // for (const auto& p : chord){
    //     cout << p.first << " " << p.second << endl;
    // }

    for (int i = 0; i < n; i++) delete[] m[i];
    delete[] m;
    delete[] C;
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

void FindChord(int i, int j, int* C, int** m, vector<pair<int, int>>& r){
    if (i >= j) return;

    int l = j - i;
    int k = C[j];

    if (k == i){ // case 3
        r.push_back({i, j});
        FindChord(i + 1, j - 1, C, m, r);
    }
    else if (k < i || k > j){ // case 1
        FindChord(i, j - 1, C, m, r);
    }
    else{ // case 2
        if (m[i][l] == m[i][l - 1]){
            FindChord(i, j - 1, C, m, r);
        }
        else{
            FindChord(i, k - 1, C, m, r);
            r.push_back({k, j});
            FindChord(k + 1, j - 1, C, m, r);
        }
    }
}