#include <bits/stdc++.h>
using namespace std;

class TrieNode{
	public:
		bool valid;
		int child[26];
		TrieNode(){
			valid = false;
			for(int i=0; i<26; i++) child[i] = -1;
		}
};

class Trie{
	private:
		vector<TrieNode> trie;
		int _newNode(){
			TrieNode tmp;
			trie.push_back(tmp);
			return trie.size() - 1;
		}
		void _add(string &str, int node, int idx){
			if(idx == str.size()){
				trie[node].valid = true; return;
			}
			int c = str[idx] - 'A';
			if(trie[node].child[c] == -1){
				int next = _newNode();
				trie[node].child[c] = next;
			}
			_add(str, trie[node].child[c], idx+1);
		}
		bool _exist(string &str){
			int now = 0;
			for(int i=0; i<str.size(); i++){
				int c = str[i] - 'A';
				if(trie[now].child[c] == -1) return false;
				now = trie[now].child[c];
			}
			return trie[now].valid;
		}
	public:
		Trie(){
			_newNode();
		}
		void add(string &str){
			_add(str, 0, 0);
		}
		void add(char str[]){
			string tmp(str);
			_add(tmp, 0, 0);
		}
		bool exist(string &str){
			return _exist(str);
		}
		bool exist(char str[]){
			string tmp(str);
			return _exist(tmp);
		}
};

int main(){
	Trie a;
	a.add("ASDF");
	a.add("FDSA");
	a.add("NJH");
	a.add("NJHAF");
	printf("%d\n", a.exist("ASDF"));
	printf("%d\n", a.exist("ASD"));
	printf("%d\n", a.exist(""));
	printf("%d\n", a.exist("NJ"));
	printf("%d\n", a.exist("NJH"));
	printf("%d\n", a.exist("NJHA"));
	printf("%d\n", a.exist("NJHAF"));
	printf("%d\n", a.exist("NJHAD"));
}
