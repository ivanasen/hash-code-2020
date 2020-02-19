#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> inputFiles = {};

void solve() {}

void readInput(istream& is) {}

void printOutput(ostream& os) {}

void printDebugOutput() {}

int main() {
    int inputToSolve;
    scanf("%d", &inputToSolve);

    const string& file = inputFiles[inputToSolve];
    ifstream is("input/" + file + ".in");
    ofstream os("output/" + file + ".out");

    readInput(is);
    solve();
    printOutput(os);
    printDebugOutput();

    return 0;
}