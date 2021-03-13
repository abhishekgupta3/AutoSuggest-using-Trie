# Auto Suggest using Trie

Implemented the auto suggest feature used in browsers to suggest the words from incomplete written words by the user.
Used a Trie data structure to store 20,000 most used words in English.
The autosuggest function returns all the strings having the given prefix, if the given prefix does not exist it return the input string.

Calculated the ratio of average time required by normal prefix search and the trie search for the first 100 strings which came out to be 26.7:1. So the trie prefix search is about 26.749 times faster than prefix search. Also the memory required to store the words is very less as compared to storing as a list of strings.


