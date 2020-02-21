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
    unordered_set<int> libBooks;

    vector<int> toScan;

    bool canScanMore() const {
        return (days - signUpDays) * booksPerDay - toScan.size() > 0;
    }

    int potentialScore() const {
        int s = 0;
        for (int b : toScan) {
            s += books[b];
        }
        return s;
    }

    // int result() const {
    //     int score = 0;
    //     for (int b : toScan) {

    //     }
    // }
};

vector<Library> libs;

int maxSearch = 1000;

void removeDuplicateBooks() {
    unordered_set<int> seenBooks;
    for (Library& lib : libs) {
        vector<int> toRm;
        for (int b : lib.libBooks) {
            if (seenBooks.count(b)) {
                toRm.push_back(b);
            } else {
                seenBooks.insert(b);
            }
        }

        for (int b : toRm) {
            lib.libBooks.erase(b);
        }
    }
}

void addRem(unordered_set<int>& addedBooks) {
    vector<pair<int, int>> bookScoreToId(books.size());
    for (int i = 0; i < books.size(); ++i) {
        bookScoreToId[i].first = books[i];
        bookScoreToId[i].second = i;
    }
    sort(bookScoreToId.begin(), bookScoreToId.end());

    for (int i = bookScoreToId.size() - 1; i >= 0; --i) {
        int id = bookScoreToId[i].second;

        if (addedBooks.count(id)) {
            continue;
        }

        // for (int j = 0; j < maxSearch; ++j) {
        //     int index = rand() % libs.size();
        // }

        for (Library& lib : libs) {
            if (lib.canScanMore() && lib.libBooks.count(id)) {
                lib.toScan.push_back(id);
                addedBooks.insert(id);
                break;
            }
        }
    }
}

void solveB() {
    // removeDuplicateBooks();

    vector<pair<double, int>> libSToId(libs.size());
    for (int i = 0; i < libs.size(); ++i) {
        libSToId[i].first = libs[i].signUpDays * libs[i].signUpDays;
        // libSToId[i].first = libs[i].signUpDays * libs[i].signUpDays /
        //                     (double)libs[i].booksPerDay;
        libSToId[i].second = i;
    }
    sort(libSToId.begin(), libSToId.end());

    unordered_set<int> addedBooks;

    for (int i = 0; i < libSToId.size(); ++i) {
        Library& lib = libs[libSToId[i].second];

        vector<pair<int, int>> scoreToBooks;
        scoreToBooks.reserve(lib.libBooks.size());
        for (int b : lib.libBooks) {
            scoreToBooks.emplace_back(books[b], b);
        }
        sort(scoreToBooks.begin(), scoreToBooks.end());
        // reverse(scoreToBooks.begin(), scoreToBooks.end());

        // for (int j = scoreToBooks.size() - 1; j >= 0; --j) {
        //     int skipProb = rand() % 100000;
        //     if (skipProb <= 10000) {
        //         continue;
        //     }

        //     if (!addedBooks.count(scoreToBooks[j].second) &&
        //         lib.canScanMore()) {
        //         lib.toScan.push_back(scoreToBooks[j].second);
        //         addedBooks.insert(scoreToBooks[j].second);
        //     }
        // }

        for (auto sb : scoreToBooks) {
            if (!addedBooks.count(sb.second) && lib.canScanMore()) {
                lib.toScan.push_back(sb.second);
                addedBooks.insert(sb.second);
            }
        }

        if (lib.toScan.size() > 0) {
            answerLibs.push_back(libSToId[i].second);
        }
    }

    vector<pair<double, int>> scoreToId;
    scoreToId.reserve(answerLibs.size());
    for (int id : answerLibs) {
        scoreToId.emplace_back(libs[id].potentialScore(), id);
        // scoreToId.emplace_back(
        //     libs[id].potentialScore() / (double)libs[id].signUpDays, id);
    }

    sort(scoreToId.begin(), scoreToId.end());
    reverse(scoreToId.begin(), scoreToId.end());

    answerLibs.clear();
    for (int i = 0; i < scoreToId.size(); ++i) {
        answerLibs.push_back(scoreToId[i].second);
    }

    // addRem(addedBooks);
}

void solveF() {}

void solveD2() {
    // removeDuplicateBooks();

    vector<pair<int, int>> libSToId(libs.size());
    for (int i = 0; i < libs.size(); ++i) {
        libSToId[i].first = libs[i].libBooks.size();
        libSToId[i].second = i;
    }
    sort(libSToId.begin(), libSToId.end());
    reverse(libSToId.begin(), libSToId.end());

    // random_shuffle(libSToId.begin(), libSToId.end());
    unordered_set<int> addedBooks;

    for (int i = 0; i < libSToId.size(); ++i) {
        Library& lib = libs[libSToId[i].second];

        // reverse(scoreToBooks.begin(), scoreToBooks.end());

        // for (int j = scoreToBooks.size() - 1; j >= 0; --j) {
        //     int skipProb = rand() % 100000;
        //     if (skipProb <= 10000) {
        //         continue;
        //     }

        //     if (!addedBooks.count(scoreToBooks[j].second) &&
        //         lib.canScanMore()) {
        //         lib.toScan.push_back(scoreToBooks[j].second);
        //         addedBooks.insert(scoreToBooks[j].second);
        //     }
        // }

        for (auto sb : lib.libBooks) {
            if (!addedBooks.count(sb) && lib.canScanMore()) {
                lib.toScan.push_back(sb);
                addedBooks.insert(sb);
            }
        }

        if (lib.toScan.size() > 0) {
            answerLibs.push_back(libSToId[i].second);
        }
    }

    vector<pair<double, int>> scoreToId;
    scoreToId.reserve(answerLibs.size());
    for (int id : answerLibs) {
        scoreToId.emplace_back(libs[id].toScan.size(), id);
        // scoreToId.emplace_back(libs[id].booksPerDay * libs[id].booksPerDay /
        //                            (double)libs[id].signUpDays,
        //                        id);
    }

    sort(scoreToId.begin(), scoreToId.end());
    reverse(scoreToId.begin(), scoreToId.end());

    answerLibs.clear();
    for (int i = 0; i < scoreToId.size(); ++i) {
        answerLibs.push_back(scoreToId[i].second);
    }

    // vector<int> best = answerLibs;
    // int bestScore = calculateScore(answerLibs);

    // vector<int> current = best;
    // int currentScore = bestScore;
    // for (int i = 0; i < 100; ++i) {
    //     vector<int> newA = best;

    //     for (int j = 0; j < 10; ++j) {
    //         int pos1 = rand() % newA.size();
    //         int pos2 = rand() % newA.size();

    //         swap(newA[pos1], newA[pos2]);
    //     }

    //     int newScore = calculateScore(newA);

    //     if (newScore > bestScore) {
    //         best = newA;
    //         bestScore = newScore;
    //     }
    // }

    // answerLibs = best;

    // addRem(addedBooks);
}

void solveD() {
    vector<pair<int, int>> bookScoreToId(books.size());
    for (int i = 0; i < books.size(); ++i) {
        bookScoreToId[i].first = books[i];
        bookScoreToId[i].second = i;
    }
    sort(bookScoreToId.begin(), bookScoreToId.end());

    vector<pair<int, int>> libSToId(libs.size());
    for (int i = 0; i < libs.size(); ++i) {
        libSToId[i].first = libs[i].libBooks.size();
        libSToId[i].second = i;
    }
    sort(libSToId.begin(), libSToId.end());

    unordered_set<int> libsSet;

    for (int i = bookScoreToId.size() - 1; i >= 0; --i) {
        for (int j = libSToId.size() - 1; j >= 0; --j) {
            Library& lib = libs[libSToId[j].second];

            if (lib.canScanMore() && lib.libBooks.count(i)) {
                lib.toScan.push_back(i);
                libsSet.insert(libSToId[j].second);
                break;
            }
        }

        printf("Books remaining: %d\n", i);
    }

    vector<pair<int, int>> scoreToId;
    scoreToId.reserve(libsSet.size());
    for (int id : libsSet) {
        scoreToId.emplace_back(libs[id].potentialScore(), id);
    }

    sort(scoreToId.begin(), scoreToId.end());
    reverse(scoreToId.begin(), scoreToId.end());

    for (int i = 0; i < scoreToId.size(); ++i) {
        answerLibs.push_back(scoreToId[i].second);
    }
}

// void solveGreedy() {
//     vector<pair<int, int>> libSToId(libs.size());
//     for (int i = 0; i < libs.size(); ++i) {
//         libSToId[i].first = libs[i].signUpDays;
//         libSToId[i].second = i;
//     }
//     sort(libSToId.begin(), libSToId.end());

//     unordered_set<int> libsSet;
//     unordered_set<int> addedBooks;

//     for (int i = 0; i < libSToId.size(); ++i) {
//         Library& lib = libs[libSToId[]]
//     }

//     for (int i = bookScoreToId.size() - 1; i >= 0; --i) {
//         for (int j = libSToId.size() - 1; j >= 0; --j) {
//             Library& lib = libs[libSToId[j].second];

//             if (lib.canScanMore() && lib.libBooks.count(i)) {
//                 lib.toScan.push_back(i);
//                 libsSet.insert(libSToId[j].second);
//                 break;
//             }
//         }

//         printf("Books remaining: %d\n", i);
//     }

//     vector<pair<int, int>> scoreToId;
//     scoreToId.reserve(libsSet.size());
//     for (int id : libsSet) {
//         scoreToId.emplace_back(libs[id].potentialScore(), id);
//     }

//     sort(scoreToId.begin(), scoreToId.end());
//     reverse(scoreToId.begin(), scoreToId.end());

//     for (int i = 0; i < scoreToId.size(); ++i) {
//         answerLibs.push_back(scoreToId[i].second);
//     }
// }

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

            if (lib.canScanMore() && lib.libBooks.count(i)) {
                lib.toScan.push_back(i);
                libsSet.insert(libSToId[j].second);
                break;
            }
        }

        printf("Books remaining: %d\n", i);
    }

    vector<pair<int, int>> scoreToId;
    scoreToId.reserve(libsSet.size());
    for (int id : libsSet) {
        scoreToId.emplace_back(
            libs[id].potentialScore() / (double)libs[id].signUpDays, id);
    }

    sort(scoreToId.begin(), scoreToId.end());
    reverse(scoreToId.begin(), scoreToId.end());

    for (int i = 0; i < scoreToId.size(); ++i) {
        answerLibs.push_back(scoreToId[i].second);
    }
}

int calculateScore() {
    int score = 0;
    int remDays = days;

    unordered_set<int> seenLibs;
    for (int i = 0; i < answerLibs.size(); ++i) {
        if (seenLibs.count(answerLibs[i])) {
            puts("Invalid answer");
            return -1;
        }

        Library& lib = libs[answerLibs[i]];

        remDays -= lib.signUpDays;
        reverse(lib.toScan.begin(), lib.toScan.end());

        for (int i = 0; i < remDays && !lib.toScan.empty();
             i += lib.booksPerDay) {
            for (int j = 0; j < lib.booksPerDay && !lib.toScan.empty(); ++j) {
                score += books[lib.toScan.back()];
                lib.toScan.pop_back();
            }
        }

        seenLibs.insert(answerLibs[i]);
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
    for (int i = 0; i < libs.size(); ++i) {
        Library& lib = libs[i];

        int bookCount;
        is >> bookCount >> lib.signUpDays >> lib.booksPerDay;

        for (int j = 0; j < bookCount; ++j) {
            int b;
            is >> b;

            if (j == 0 && i % 2) {
                if (libs[i - 1].libBooks.size() > bookCount) {
                    continue;
                } else {
                    libs[i - 1].libBooks.erase(b);
                }
            }

            lib.libBooks.insert(b);
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

void printDebugOutput(const string& file) {
    puts("----------------------");

    printf("Score: %d\n", calculateScore());
    printf("Result for: %c\n", file[0]);
}

vector<string> inputFiles = {"a", "b", "c", "d", "e", "f"};

int main() {
    int inputToSolve;
    scanf("%d", &inputToSolve);

    const string& file = inputFiles[inputToSolve];
    ifstream is("input/" + file + ".in");
    ofstream os("output/" + file + ".out");

    readInput(is);
    if (file == "d") {
        solveD2();
    } else {
        solveB();
    }
    // if (file == "b") {

    // } else if (file == "d") {
    //     solveD();
    // } else {
    //     solve();
    // }
    printOutput(os);
    printDebugOutput(file);

    return 0;
}