#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cassert>

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
    return isalpha(c) || ('а' <= c && c <= 'я') || ('А' <= c && c <= 'Я');
}

void codeMessages(string &inputPath, string &outputPath) {
    freopen(inputPath.c_str(), "r", stdin);
    freopen(outputPath.c_str(), "w", stdout);
	vector <string> messages = readMessages();
    map <string, int> cnt;
    for (auto message: messages) {
        vector <string> params;
        string word;
        for (char c: message) {
            if (isAlpha(c)) {
                word += c;
            } else {
                if (word.size() >= 3) {
                	cnt[word]++;
                }
                word = "";
            }
        }
    }
    vector <pair <int, string> > tmp;
    for (auto x: cnt) {
    	if (x.second > 1) {
	    	tmp.push_back({x.second, x.first});
	    }
    }
    sort(tmp.rbegin(), tmp.rend());
    map <string, int> dict;
    for (int i = 0; i < tmp.size(); ++i) {
    	cout << tmp[i].second << endl;
    	dict[tmp[i].second] = i;
    }
    cout << endl;

    for (auto message: messages) {
        string result;
        string word;
        for (char c: message) {
            if (isAlpha(c)) {
                word += c;
            } else {
                if (dict.count(word)) {
                	result += "#" + to_string(dict[word]);
                } else {
                	result += word;
                }
                word = "";
                if (c != '\n') {
                	result += c;
                }
            }
        }
        cout << result << endl;
    }
}

void decodeMessages(string &inputPath, string &outputPath) {
    freopen(inputPath.c_str(), "r", stdin);
    freopen(outputPath.c_str(), "w", stdout);
	vector <string> dict;		
	string s;
	while (true) {
		getline(cin, s);
		if (s == "") {
			break;
		}
		dict.push_back(s);
	}
	while (getline(cin, s)) {
		string result;
		int pos = 0;
		while (pos < s.size()) {
			if (s[pos] == '#') {
				pos++;
				bool isEmpty = true;
				int num = 0;
				while (pos < s.size() && isdigit(s[pos])) {
					num = 10 * num + (s[pos] - '0');
					pos++;
					isEmpty = false;
				}
				if (isEmpty) {
					result += '#';
				} else {
					result += dict[num];
				}
			} else {
				result += s[pos];
				pos++;
			}
		}
		cout << result << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc == 4) {
		string type = string(argv[1]);
		string input = string(argv[2]);
		string output = string(argv[3]);
		if (type == "code") {
			codeMessages(input, output);
		} else if (type == "decode") {
			decodeMessages(input, output);
		} else {
			throw "Режим может быть только code/decode";
		}
	} else {
		throw "Неправильно указаны аргументы";
	}
}
