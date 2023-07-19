#include<iostream>
using namespace std;
int ctanodos = 0;
class nodeTrie {
public:
bool getEnd() {
return end;
};
void setEnd(bool valuereceived) {
end = valuereceived;
};
char getLetter() {
return letter;
};
nodeTrie(char c, nodeTrie* p) : parent(p), letter(c), end(false) {
for(int i=0; i<26; i++) {
child[i] = nullptr;
}
}
nodeTrie* getNode(int i) {
return child[i];
};
nodeTrie* getChild(char c) {
return child[c - 'a'];
}
void addChild(nodeTrie* node) {
child[node->letter - 'a'] = node;
}
private:
char letter;
bool end;
nodeTrie* parent;
nodeTrie* child[26];
};

class trie {
public:
trie() {
root = new nodeTrie('\0', nullptr);
}
void insert(string word);
bool search(string word);
nodeTrie* getRoot() {
return root;
};
private:
nodeTrie* root;
};
void trie::insert(string word) {
nodeTrie* current = root;
for (int i = 0; i < word.length(); i++) {
char c = word[i];
nodeTrie* sub = current->getChild(c);
if (sub != nullptr) {
current = sub;
}
else {
current->addChild(new nodeTrie(c, current));
current = current->getChild(c);
}
if (i == word.length() - 1) {
current->setEnd(true);
}
}
}

bool trie::search(string word) {
nodeTrie* current = root;
for (int i = 0; i < word.length(); i++) {
char c = word[i];
nodeTrie* sub = current->getChild(c);
if (sub == nullptr) {
return false;
}
current = sub;
}
return current->getEnd();
}

void printTriePh(int padre, nodeTrie* node) {
if (node == nullptr) {
return;
}
ctanodos++;
int actual;
actual = ctanodos;
cout << "nodo padre: " << padre << ", nodo actual:" << actual << ", letra actual: " << node->getLetter()<< endl;
for (int i = 0; i < 26; i++) {
if (node->getNode(i) != nullptr) {
printTriePh(actual, node->getNode(i));
}
}
}

int main(){
trie myTrie;
myTrie.insert("cosa");
myTrie.insert("cocina");
myTrie.insert("cocinero");
myTrie.insert("cartera");
myTrie.insert("carta");
myTrie.insert("base");

printTriePh(0, myTrie.getRoot());
return 0;
}