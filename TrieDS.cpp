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

	// whether the given node has child
	bool hasChild(TrieNode* root) {

		for (int i = 0; i < 26; ++i) {
			if (root->children[i] != NULL) {
				return true;
			}
		}
		return false;
	}

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

		int index = input[0] - 'a';

		if (root->children[index] == NULL) return false;
		return searchUtil(input.substr(1), root->children[index]);
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

	void displayUtil(string s, TrieNode* root) {
		// if the given char is end of word print it
		if (root->isEnd == true) {
			cout << s << endl;
		}

		// for all children in root if not NULL recursively call its children
		for (int i = 0; i < 26; i++) {
			if (root->children[i] != NULL) {
				displayUtil(s + root->children[i]->data, root->children[i]);
			}
		}
	}

	// auto suggest util function
	void autoSuggestUtil(string input, TrieNode* root) {

		TrieNode * temp = root;
		int len = input.length();

		// traversing the given input string
		for (int i = 0; i < len; i++) {
			int index = input[i] - 'a';
			// no such prefix exist then return
			if (temp->children[index] == NULL) {
				return;
			}
			temp = temp->children[index];
		}

		// if it is end node and has no children print the input string
		if (temp->isEnd and hasChild(temp) == false) {
			cout << input << endl;
			return;
		}

		// print the subtree
		if (hasChild(root)) {
			displayUtil(input, temp);
		}
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

	// display
	void display() {
		displayUtil("", root);
	}

	// auto suggest
	void autoSuggest(string input) {
		autoSuggestUtil(input, root);
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

// Testing
	// t.insert("abc");
	// t.insert("abcd");
	// t.insert("ghi");
	// t.insert("abcd");
	// t.insert("ghifg");
	// t.insert("abbcd");
	// t.insert("ghhii");
	// t.insert("abccd");
	// t.insert("uvai");

	// cout << "abc " << t.search("abc") << endl;
	// cout << "pass " << t.search("pass") << endl;
	// cout << "abcd " << t.search("abcd") << endl;
	// cout << "abc " << t.search("abc") << endl;
	// cout << endl;
	// t.remove("abc");
	// t.display();
	// cout << endl;

	t.autoSuggest("alchem");
	cout << endl;



	return 0;

}