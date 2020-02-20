#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> answerLibs;
vector<int> books;
int days;

struct Library {
    int signUpDays;
    int booksPerDay;
    unordered_set<int> books;

    vector<int> toScan;

    bool canScanMore() const {
        return (days - signUpDays) * booksPerDay - toScan.size() >= 0;
    }

    // int result() const {
    //     int score = 0;
    //     for (int b : toScan) {

    //     }
    // }
};

vector<Library> libs;

void solveA() {
    vector<pair<int, int>> libSToId(libs.size());
    for (int i = 0; i < libs.size(); ++i) {
        libSToId[i].first = libs[i].signUpDays;
        libSToId[i].second = i;
    }
    sort(libSToId.begin(), libSToId.end());

    for (int i = 0; i < libSToId.size(); ++i) {
        Library& lib = libs[libSToId[i].second];

        for (int book : lib.books) {
            if (lib.canScanMore()) {
                lib.toScan.push_back(book);
            }
        }

        answerLibs.push_back(libSToId[i].second);
    }
}

void solve() {
    vector<pair<int, int>> bookScoreToId(books.size());
    for (int i = 0; i < books.size(); ++i) {
        bookScoreToId[i].first = books[i];
        bookScoreToId[i].second = i;
    }
    sort(bookScoreToId.begin(), bookScoreToId.end());

    vector<pair<int, int>> libSToId(libs.size());
    for (int i = 0; i < libs.size(); ++i) {
        libSToId[i].first = libs[i].signUpDays;
        libSToId[i].second = i;
    }
    sort(libSToId.begin(), libSToId.end());

    unordered_set<int> libsSet;

    for (int i = bookScoreToId.size() - 1; i >= 0; --i) {
        for (int j = libSToId.size() - 1; j >= 0; --j) {
            Library& lib = libs[libSToId[j].second];

            if (lib.canScanMore() && lib.books.count(i)) {
                lib.toScan.push_back(i);
                libsSet.insert(libSToId[j].second);
                break;
            }
        }

        printf("Books remaining: %d\n", i);
    }

    libSToId.clear();
    for (int id : libsSet) {
        libSToId.emplace_back(libs[id].signUpDays, id);
    }
    sort(libSToId.begin(), libSToId.end());

    for (int i = 0; i < libSToId.size(); ++i) {
        answerLibs.push_back(libSToId[i].second);
    }
}

int calculateScore() {
    int score = 0;
    for (int i = 0; i < answerLibs.size(); ++i) {
        Library& lib = libs[answerLibs[i]];
        for (int b : lib.toScan) {
            score += books[b];
        }
    }
    return score;
}

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

    puts("Input parsed");
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

void printDebugOutput() {
    puts("----------------------");

    printf("Score: %d\n", calculateScore());
}

vector<string> inputFiles = {"a", "b", "c", "d", "e", "f"};

int main() {
    int inputToSolve;
    scanf("%d", &inputToSolve);

    const string& file = inputFiles[inputToSolve];
    ifstream is("input/" + file + ".in");
    ofstream os("output/" + file + ".out");

    readInput(is);
    if (file == "a") {
        solveA();
    } else {
        solve();
    }
    printOutput(os);
    printDebugOutput();

    return 0;
}