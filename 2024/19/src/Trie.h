#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>


struct TrieNode 
{
    std::vector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode();
};

class Trie 
{
    private:
        TrieNode* root;

    public:
        Trie();

        void insert(const std::string& word);
        bool search(const std::string& word);
        bool startsWith(const std::string& prefix);
        void deleteWord(const std::string& word);
        void print(TrieNode* node, const std::string& prefix) const;

        void print() const;
};

#endif //TRIE_H