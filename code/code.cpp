#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector <string> readMessages() {
    vector <string> messages;
    string str;
    while (getline(cin, str)) {
        messages.push_back(str + "\n");
    }
    return messages;
}

bool isAlpha(char c) {
    return isalpha(c) || ('à' <= c && c <= 'ÿ') || ('À' <= c && c <= 'ß');
}

bool isLower(char c) {
    return islower(c) || ('à' <= c && c <= 'ÿ');
}

void codeMessages() {
    vector <string> messages = readMessages();
    map <string, vector <vector <string> > > patterns;
    for (auto message: messages) {
        string pattern;
        vector <string> params;
        string word;
        bool isUpper = true;
        for (char c: message) {
            if (isAlpha(c)) {
                word += c;
                if (isLower(c)) {
                    isUpper = false;
                }
            } else {
                if (word.size() >= 3 && isUpper) {
                    string numOfParam = to_string(params.size());
                    pattern += "{" + numOfParam + "}";
                    params.push_back(word);
                } else if (word.size() > 0) {
                    pattern += word;
                }
                word = "";
                isUpper = true;
                if (c != '\n') {
                	pattern += c;
                }
            }
        }
        patterns[pattern].push_back(params);
    }
    int num = 0;
    for (auto pattern: patterns) {
        cout << "#" << num << ":" << pattern.first << endl;
        cout << "[";
        bool firstParams = true;
        for (auto params: pattern.second) {
            if (firstParams) {
                firstParams = false;
            } else {
                cout << ",";
            }
            cout << "(";
            bool isFirstParam = true;
            for (auto param: params) {
                if (isFirstParam) {
                    isFirstParam = false;
                } else {
                    cout << ",";
                }
                cout << param;
            }
            cout << ")";
        }
        cout << "]" << endl;
        num++;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    codeMessages();
}
