#include "Trie.h"

const int ALPHABET_SIZE = 26;

TrieNode::TrieNode() : children(ALPHABET_SIZE, nullptr), isEndOfWord(false) {}

Trie::Trie() : root(new TrieNode()) {}

// Add words to the Trie.
void Trie::insert(const std::string& word) 
{
    TrieNode* current = root;

    for (char ch : word) 
    {
        int index = ch - 'a';
        if (!current->children[index]) 
        {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }

    current->isEndOfWord = true;
}

// Returns true if the word exists in the Trie.
bool Trie::search(const std::string& word) 
{
    TrieNode* current = root;

    for (char ch : word) 
    {
        int index = ch - 'a';
        if (!current->children[index]) 
        {
            return false;
        }
        current = current->children[index];
    }

    return current->isEndOfWord;
}

// Returns true if a prefix exists in the Trie.
bool Trie::startsWith(const std::string& prefix) 
{
    TrieNode* current = root;

    for (char ch : prefix) 
    {
        int index = ch - 'a';
        if (!current->children[index]) 
        {
            return false;
        }
        current = current->children[index];
    }

    return true;
}

// Delete word from the Trie.
void Trie::deleteWord(const std::string& word)
{
    TrieNode* node = root;
    for (char ch : word) 
    {
        int index = ch - 'a';
        if (!node->children[index])
        {
            return;
        }
        node = node->children[index];
    }
    if (node->isEndOfWord == true)
    {
        node->isEndOfWord = false;
    }
}

// Function to print the trie
void Trie::print(TrieNode* node, const std::string& prefix) const
{
    if (node->isEndOfWord) 
    {
        std::cout << prefix << std::endl;
    }
    for (int i = 0; i < 26; i++) 
    {
        if (node->children[i]) 
        {
            print(node->children[i], prefix + char('a' + i));
        }
    }
}

// Function to start printing from the root
void Trie::print() const { print(root, ""); }