#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Library {};

vector<Library> libs;
vector<int> books;
int days;

void solve() {}

void readInput(istream& is) {
    int bookCount, libCount;
    is >> bookCount >> libCount >> days;

    books.resize(bookCount);
    for (int& b : books) {
        is >> b;
    }

    libs.resize(libCount);
}

void printOutput(ostream& os) {}

void printDebugOutput() {}

vector<string> inputFiles = {"a", "b", "c", "d", "e", "f"};

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