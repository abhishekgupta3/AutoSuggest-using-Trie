// Normal Prefix Search

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {

#ifndef ONLINE_JUDGE
	freopen("20000words.txt", "r", stdin);
	freopen("timeTaken_NormalPrefixSearch.txt", "w", stdout);
#endif

	vector <string> v;

	for (int i = 0; i < 20000; i++) {
		string words;
		cin >> words;
		v.push_back(words);
	}
	int count = 0;

	auto start = high_resolution_clock::now();

	// prefix search for first 100 words
	for (int i = 0; i < 100; ++i) {
		count = 0;
		for (int j = 0; j < 20000; j++) {
			if (v[j].substr(0, v[i].length()) == v[i]) {
				count++;
			}
		}
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by prefix search for first 100 words: "
	     << duration.count() << " microseconds" << endl;


	return 0;

}