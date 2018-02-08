#include <bits/stdc++.h>
using namespace std;
#include "utilities.h"
//globals
map< string,set<string> > first;
map< string,set<string> > &getFirst(map< string,vector<string> > prods) 
{
    static map< string,set<string> > f;
    f.clear();
    while(prods.size()!=0)
    {
        for(auto it=prods.begin();it!=prods.end();it++)
        {
            uint l=0;
            auto j=it->second;
            for(uint i=0;i<j.size();i++,l++)
            {
                string firstChar=j[i].substr(0,1);
                if(islower(firstChar[0])||j[i]=="@")//rule 1&4
                {
                    f[it->first].insert(firstChar);
                    j.erase(j.begin()+i--);
                }
                else if(firstChar!="")
                {
                    if(f.find(firstChar)!=f.end())
                    {
                        f[it->first].insert(f[firstChar].begin(),f[firstChar].end());
                        if(j[i].length()>0&&f[firstChar].find("@")!=f[firstChar].end())
                            j[i]=j[i].substr(1);
                        else
                            j.erase(j.begin()+i--);
                    }
                }
                else
                {
                    j.erase(j.begin()+i--);
                }
            }
            prods[it->first]=j;
            if(j.size()==0)
            {
                prods.erase(it);
            }
        }
    }
    return f;
}
map< string,set<string> > &getFollow(map< string,vector<string> > &prods)
{
    static map< string,set<string> > g;
    g.clear();
    g["S"].insert("$");
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        for(uint i=0;i<it->second.size();i++)
        {
            string s=it->second[i];
            for(uint j=0;j<s.length()-1;j++)
            {
                if(isupper(s[j]))
                {
                    if(islower(s[j+1]))
                    {
                        g[string()+s[j]].insert(string()+s[j+1]);
                    }
                    else
                    {
                        string curr=string()+s[j],next=string()+s[j+1];
                        int _count=0;
                        g[curr].insert(first[next].begin(),
                                first[next].end());
                        
                        //debug(curr);
                        while(first[next].find("@")!=first[next].end())
                        {
                            //debug(*first[next].find("@"));
                            //debug(next);
                            if(j+_count+1<s.size())
                                next=string()+s[j+_count+1];
                            else
                            {    
                                g[curr].insert("$");
                                break;
                            }
                            g[curr].insert(first[next].begin(),
                                first[next].end());
                            _count++;
                        }
                        g[curr].erase("@");
                    }
                }
            }
        }
    }
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        for(uint i=0;i<it->second.size();i++)
        {
            string s=it->second[i];
            if(isupper(s[s.length()-1]))
            {
                g[string()+s[s.length()-1]].insert(
                    g[it->first].begin(),g[it->first].end());
            }
        }
    }
    return g;
}
int main()
{
    //@ is epsilon
    freopen("input1.txt","r",stdin);
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
    first=getFirst(prods);
    cout<<"first = "<<first<<endl;
    cout<<"follow = "<<getFollow(prods)<<endl;
    return 0;
}
