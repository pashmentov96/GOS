#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector <string> split(const string &str, char delimiter) {
	string tmp;
	vector <string> result;
	for (char c : str) {
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
	for (auto s : elements) {
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

		for (auto params : messages) {
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
	decodeMessages();
}
