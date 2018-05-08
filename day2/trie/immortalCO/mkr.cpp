#include <bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("-O2")
using namespace std;

#define str string
struct Init{
	union Hack{void* p; size_t v; };
	Init() {
		srand(((Hack) {new char}).v);
		srand(rand() + clock());
		srand(rand() + time(0));
	}
}	__init;

template<class T> T par(string s) {
	stringstream in; in << s;
	T v; in >> v; 
	return v;
}

map<int, int> nxt[1111];
string rep[1111];
int n, fa[1111];
map<string, string> args;
template<class T> T A(string s) {return par<T>(args[s]);}
int lim;

int randint(int l, int r) {return rand() % (r - l + 1) + l;}

vector<int> make_spl(int n, int sma = 0, double rat = 1.5) {
	set<int> s;
	int m = pow(randint(1, 1e8) / 1e8, rat) * (n / (1 + sma));
	if(m < 1) m = 1; if(m > (n / (1 + sma))) m = n / (1 + sma);
	n -= m * sma;
	s.insert(n);
	while((int) s.size() < m) s.insert(randint(1, n));
	int l = 0;
	n += m * sma;
	vector<int> ret;
	for(auto r : s) {ret.push_back(r - l + sma); l = r; }
	sort(ret.begin(), ret.end());	
	int sum = 0; for(auto x : ret) sum += x; assert(sum == n);
	return ret;
}

string rand_num(int n) {
	string s;
	for(int i = 0; i < n; ++i) s.push_back(randint('0' + !i, '9'));
	return s;
}

string make_list(int n) {
	vector<int> spl;
	do spl = make_spl(n + 1, 1, 0.7);
	while(count(spl.begin(), spl.end(), 2) > 9);
	string ret;
	for(int i = 1; i <= n; ++i) {
		int c = count(spl.begin(), spl.end(), i + 1);
		set<string> st;
		while((int) st.size() < c) st.insert(rand_num(i));
		for(auto x : st) ret += x + ",";
	}
	ret.pop_back();
	assert((int) ret.size() == n);
	return ret;
}

int step(int p, int w) {
	if(!nxt[p][w]) {rep[nxt[p][w] = ++n] = rep[p] + char(w); fa[n] = p;}
	return nxt[p][w];
}

void trie_insert(string s) {
	int p = 0;
	for(auto c : s) p = step(p, c);
	// cout << s << endl;
}

vector<string> split(string s) {
	vector<string> ret; string cur;
	for(auto c : s) {
		if(c == ',') {ret.push_back(cur); cur = "";}
		else cur.push_back(c);
	}
	ret.push_back(cur);
	return ret;
}
bool cmp(const str& a, const str& b) {
	return a.length() != b.length() ? a.length() < b.length() : a < b;
}
bool pig(string s) {
	string l = "";
	for(auto x : split(s)) {if(!cmp(l, x)) return 0; l = x;}
	return 1;
}

int main() {
	for(string s; cin >> s; ) {
		string a[2]; bool mark = 0;
		for(int i = 0; i != (int) s.size(); ++i) {
			if(s[i] == '=') mark = 1;
			else a[mark].push_back(s[i]);
		}
		args[a[0]] = a[1];
	}
	lim = A<int>("n");
	if(args.count("chain")) 
		trie_insert(make_list(lim));
	else {
		for(auto x : make_spl(randint(lim/4,lim*3/4), 0, 2)) trie_insert(make_list(x));
		for( ; ; ) {
			vector<int> per;
			for(int i = 1; i <= n; ++i) per.push_back(i);
			random_shuffle(per.begin(), per.end());
			for(auto x : per) {
				string str = rep[x];
				// cout << x << " " << str << endl;
				do str.push_back(randint('0' + (str.back() == ','), '9')); while(!pig(str));
				while((int) str.size() + (int) split(str).back().size() + 2 + n <= lim && rand() % 2) {
					str.push_back(','); 
					str.push_back(randint('1', '9'));
					while(!pig(str)) str.push_back(randint('0', '9'));
				}
				if(n + (int) str.size() > lim) continue;
				int on = n;
				trie_insert(str);
				if(on != n) goto success;
				// cout << "inserted n = " << n << endl;
			}
			break;
			success: continue;
		}
		if(n < lim) trie_insert(make_list(lim - n));
	}
	assert(n <= lim);
	string out;
	for(int i = 1; i <= n; ++i) out.push_back(rep[i].back());
	for(int t = ((A<int>("m") == -1) ? randint(1, n) : A<int>("m")); t--; ) {
		int p = rand() % out.size();
		if(!(args.count("keep") && out[p] == '?')) out[p] = '?';
	}
	cout << out << endl;
	for(int i = 1; i <= n; ++i) cout << fa[i] << " \n"[i == n];
}
