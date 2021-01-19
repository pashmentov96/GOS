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
    return isalpha(c) || ('À' <= c && c <= 'ÿ') || ('À' <= c && c <= 'ß');
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

vector <string> split(const string &str, char delimiter) {
	string tmp;
	vector <string> result;
	for (char c: str) {
		if (c == delimiter) {
			result.push_back(tmp);
			tmp = "";	
		} else {
			tmp += c;
		}
	}
	if (tmp != "") {
		result.push_back(tmp);
	}
	return result;
}

vector <vector <string> > getParamsFromStr(const string &str) {
	string tmp = str.substr(1, str.size() - 2);
	vector <string> elements = split(tmp, ')');
	vector <vector <string> > result;
	for (auto s: elements) {
		string params = s.substr(s.find('(') + 1);
		result.push_back(split(params, ','));
	}
	return result;	
}

void decodeMessages() {
	string pattern;
	while (getline(cin, pattern)) {
		string str;
		getline(cin, str);
		auto messages = getParamsFromStr(str);

		for (auto params: messages) {
			string result = "";
			int lastPos = 3;
			for (int i = 0; i < params.size(); ++i) {
				string tmp = "{" + to_string(i) + "}";
				int newPos = pattern.find(tmp, lastPos);
				result += pattern.substr(lastPos, newPos - lastPos) + params[i];
				lastPos = newPos + tmp.size();
			}
			result += pattern.substr(lastPos);
			cout << result << endl;
		}	
    }
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    codeMessages();
    // decodeMessages();
}