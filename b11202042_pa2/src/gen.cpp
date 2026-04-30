#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;

void generatePairs(int n) {
    vector<int> numbers;
    for (int i = 0; i < 2 * n; ++i) numbers.push_back(i);
    
    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);
    
    int m = 2 * n;
    string filename = to_string(m) + ".in";
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Can't open output file. " << std::endl;
        return;
    }
    outfile << m << endl;
    for (int i = 0; i < 2 * n; i += 2) outfile << numbers[i] << " " << numbers[i + 1] << endl;
    outfile.close();
}

int main() {
    int n;
    cout << "Input an even number n: ";
    cin >> n;
    if (n % 2 != 0) {
        cerr << "Invalid: not an even number. " << endl;
        return EXIT_FAILURE;
    }
    generatePairs(n);
    return EXIT_SUCCESS;
}