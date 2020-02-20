#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Library {
    int signUpDays;
    int booksPerDay;
    unordered_set<int> books;

    vector<int> toScan;
};

vector<Library> libs;
vector<int> answerLibs;
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
    for (Library& lib : libs) {
        int bookCount;
        is >> bookCount >> lib.signUpDays >> lib.booksPerDay;

        for (int i = 0; i < bookCount; ++i) {
            int b;
            is >> b;
            lib.books.insert(b);
        }
    }
}

void printOutput(ostream& os) {
    os << answerLibs.size() << '\n';

    for (int i = 0; i < answerLibs.size(); ++i) {
        Library& lib = libs[answerLibs[i]];

        os << answerLibs[i] << ' ' << lib.toScan.size() << '\n';

        for (int b : lib.toScan) {
            os << b << ' ';
        }

        os << '\n';
    }
}

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