#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

void encode(Node* root, const string& str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

string decode(Node* root, const string& encodedStr) {
    string decodedStr;
    Node* curr = root;

    for (char bit : encodedStr) {
        curr = (bit == '0') ? curr->left : curr->right;

        if (!curr->left && !curr->right) {
            decodedStr += curr->ch;
            curr = root;
        }
    }

    return decodedStr;
}

int main() {
    string text = "huffman coding algorithm";

    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    Node* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    string encodedStr;
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }

    cout << "\nEncoded String:\n" << encodedStr << "\n";

    string decodedStr = decode(root, encodedStr);

    cout << "\nDecoded String:\n" << decodedStr << "\n";

    return 0;
}
