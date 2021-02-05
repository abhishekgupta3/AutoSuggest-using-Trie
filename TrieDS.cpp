#include <bits/stdc++.h>
using namespace std;

// TrieNode class
class TrieNode {
public:
	char data;
	TrieNode** children; //children 1D array of 26 alphabets
	bool isEnd;

	TrieNode(char data) {
		this->data = data;
		children = new TrieNode*[26];
		for (int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isEnd = false;
	}
};

// Trie Class
class Trie {
	TrieNode* root;

	// insert util function
	void insertUtil(string input, TrieNode* root) {
		// Base case
		if (input.length() == 0) {
			root->isEnd = true;
			return;
		}
		TrieNode * child;
		int index = input[0] - 'a';

		if (root->children[index] == NULL) {
			child = new TrieNode(input[0]);
			root->children[index] = child;
		}
		else {
			child = root->children[index];
		}

		insertUtil(input.substr(1), child);
	}

	// search util function
	bool searchUtil(string input, TrieNode* root) {
		// Base case
		if (input.length() == 0) return root->isEnd;

		TrieNode * child;
		int index = input[0] - 'a';

		if (root->children[index] == NULL) return false;
		else child = root->children[index];

		return searchUtil(input.substr(1), child);
	}

	// remove util function
	void removeUtil(string input, TrieNode* root) {
		// Base case
		if (input.length() == 0) {
			root->isEnd = false;
			return;
		}

		TrieNode * child;
		int index = input[0] - 'a';

		if (root->children[index] == NULL) return; // nothing to remove
		else child = root->children[index];

		removeUtil(input.substr(1), child); //this part only marks isEnd as false doesn't delete the node

		// delete the children node if it is last node & its all children are null
		if (child->isEnd) {

			for (int i = 0; i < 26; i++) {
				// if there is any child present don't need to delete
				if (child->children[i] != NULL) return;
			}
			delete child; // all children are NULL
			root->children[index] = NULL; // the parent's array should be marked null
		}
	}

	void display(string s, TrieNode* root) {
		for (int i = 0; i < 26; i++) {
			if (root->children[i] != NULL) {
				if (root->children[i]->isEnd) {
					cout << s << root->children[i]->data;
					cout << endl;
				}
				display(s + root->children[i]->data, root->children[i]);
			}
		}
		return;
	}

	// auto suggest util function
	void autoSuggestUtil(string input, string s , TrieNode* root) {
		// Base case
		if (input.length() == 0) {
			display(s, root);
		}

		TrieNode * child;
		int index = input[0] - 'a';

		if (root->children[index] == NULL) return;
		else child = root->children[index];

		return autoSuggestUtil(input.substr(1), s, child);
	}

public:

	Trie() {
		root = new TrieNode('\0'); // root stores null character
	}

	// Insert
	void insert(string input) {
		insertUtil(input, root);
	}

	// search
	bool search(string input) {
		return searchUtil(input, root);
	}

	// remove
	void remove(string input) {
		removeUtil(input, root);
	}

	// auto suggest
	void autoSuggest(string input) {
		string s = input;
		autoSuggestUtil(input, s, root);
	}

};

int main() {

#ifndef ONLINE_JUDGE
	freopen("20000words.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	Trie t;
	for (int i = 0; i < 20000; i++) {
		string words;
		cin >> words;
		t.insert(words);
	}

	// cout << "pass " << t.search("pass") << endl;
	// cout << "abcd " << t.search("abcd") << endl;

	t.autoSuggest("an");



	return 0;

}