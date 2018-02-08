#include <bits/stdc++.h>
using namespace std;

void insert(map<string , vector<string> > &trie,vector<string> &v,int level=0,string s="#")
{
    for(int i=0;i<v.size();i++)
    {   
        if(trie[s].find(v[i][level]) != trie[s].end())
        {
            trie[s].push_back(v[i][level]);
            insert(trie,v,level+1);
        }
    }
}

void traverse(map< string,vector<string> > &prods,map< string,vector<string> > &trie,int level=0,string s="#")
{
    static stack<string> current;
    if(trie[s].size()==0)
        return;
    for(int i=0;i<trie[s].size();i++)
    {   
        traverse(prods,trie,level+1,trie[s][i],current+s);
        
    }
    
}

void factorize(map< string,vector<string> > &prods,vector<string> &v)
{
    map<string , vector<string> > trie;
    insert(trie,v);
    
}

int main(int argv,char *args[])
{
    freopen("input.txt","r",stdin);
    map< string,vector<string> > prods;
    string buff;
    while(getline(cin,buff,'\n'))
    {
        string p,rx;
        istringstream iss(buff);
        vector<string> r;
        getline(iss,p,'>');
        while(getline(iss,rx,'|'))
            r.push_back(rx);
        prods[p]=r;
    }
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        factorize(prods,it.second);
    }
    return 0;
}
    
