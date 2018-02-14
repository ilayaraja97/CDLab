#include <bits/stdc++.h>
using namespace std;
#include "utilities.h"
//globals
map< string,set<string> > first,follow;
//map< string, map<string,string> > lltable;
map< string,set<string> > &getFirst(map< string,vector<string> > prods);
map< string,set<string> > &getFollow(map< string,vector<string> > &prods);
map< string, map<string,string> > &getLLTable(map< string,vector<string> > &prods);
bool parseLL(map< string, map<string,string> > &llt,string input);

inline bool isTerminal(char a)
{
    return !isupper(a);
}

int main()
{
    //@ is epsilon
    string input;
    cin>>input;
    freopen("input3.txt","r",stdin);
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
    if(parseLL(getLLTable(prods),input))
    {
        cout<<"The input is correct"<<endl;
    }
    else
    {
        cout<<"not"<<endl;
    }
    return 0;
}

bool parseLL(map< string, map<string,string> > &llt,string input)
{
    stack<string> ss;
    ss.push("$");
    ss.push("S");//push start symbol
    int i=0;
    string fc=string()+input[i];
    while(fc!="$")
    {
        cerr<<"stack ="<<ss<<endl;
        cerr<<input<<" "<<i<<endl;
        if(ss.top()==fc||ss.top()=="@")
        {
            try
            {
                if(ss.top()!="@")
                    fc=string()+input[++i];
                ss.pop();
            }
            catch(exception &e)
            {
                //cerr<<"out of bounds"<<endl;
                return false;
            }
        }
        else
        {
            try
            {
                string buff=llt.at(ss.top()).at(fc);
                ss.pop();
                for(int k=buff.length()-1;k>=0;k--)
                {
                    ss.push(string()+buff[k]);
                }
            }
            catch(exception &e)
            {
                //cerr<<"not in map"<<endl;
                return false;
            }
        }
    }
    //cerr<<ss<<endl;
    //cerr<<input<<" "<<i<<endl;
    return ss.top()=="$"&&fc=="$";
}

map< string, map<string,string> > &getLLTable(map< string,vector<string> > &prods)
{
    static map< string, map<string,string> > l;
    follow=getFollow(prods);
    //cerr<<first<<endl;
    //cerr<<follow<<endl;
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        auto j=it->second;
        for(uint i=0;i<j.size();i++)
        {
            //find first of a part prod
            string firstChar=j[i].substr(0,1);
            bool nullString=true;
            if(j[i]=="@")
            {
                for(auto is=follow[it->first].begin();is!=follow[it->first].end();is++)
                {
                    try
                    {
                        if(l[it->first].at(*is)=="@")
                            continue;
                        l[it->first].at(*is)="@";
                        cerr<<*is<<endl;
                        cerr<<"not LL(1) grammar"<<l<<endl;
                        exit(1);
                    }
                    catch (exception &e)
                    {
                        l[it->first][*is]="@";
                    }
                }
                continue;
            }
            for(uint k=0;k<j[i].length()&&nullString;k++)
            {
                firstChar=j[i].substr(k,k+1);
                if(isTerminal(firstChar[0]))
                {
                    try
                    {
                        if(l[it->first].at(firstChar)==j[i])
                            continue;
                        l[it->first].at(firstChar)=j[i];
                        cerr<<"not LL(1) grammar"<<l<<endl;
                        exit(1);
                    }
                    catch (exception &e)
                    {
                        l[it->first][firstChar]=j[i];
                    }
                    break;
                }
                else
                {
                    nullString=false;
                    for(auto is=first[firstChar].begin();is!=first[firstChar].end();is++)
                    {
                        if(*is=="@")
                        {
                            nullString=true;
                        }
                        else
                        {
                            try
                            {
                                if(l[it->first].at(*is)==j[i])
                                    continue;
                                l[it->first].at(*is)=j[i];
                                cerr<<"not LL(1) grammar"<<l<<endl;
                                exit(1);
                            }
                            catch (exception &e)
                            {
                                l[it->first][*is]=j[i];
                            }
                        }
                    }
                }
            }
            if(nullString)
            {
                for(auto is=follow[it->first].begin();is!=follow[it->first].end();is++)
                {
                    try
                    {
                        if(l[it->first].at(*is)=="@")
                            continue;
                        l[it->first].at(*is)="@";
                        cerr<<"not LL(1) grammar"<<l<<endl;
                        exit(1);
                    }
                    catch (exception &e)
                    {
                        l[it->first][*is]="@";
                    }
                }
            }
        }
    }
    return l;
}

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
                if(isTerminal(firstChar[0])||j[i]=="@")//rule 1&4
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
    first=getFirst(prods);
    g.clear();
    g["S"].insert("$");
    bool followAdd=false;
    vector<string> pending;
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        for(uint i=0;i<it->second.size();i++)
        {
            string s=it->second[i];
            for(uint j=0;j<s.length()-1;j++)
            {
                if(!isTerminal(s[j]))
                {
                    if(isTerminal(s[j+1]))
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
                            //debug(first[next]);
                            //debug(next);
                            //debug(s);
                            if(j+_count+1<s.length())
                                next=string()+s[j+_count+1];
                            else
                            {
                                followAdd=true;
                                break;
                            }
                            g[curr].insert(first[next].begin(),
                                first[next].end());
                            _count++;
                        }
                        g[curr].erase("@");
                        //debug(g[curr]);
                    }
                }
                if(!isTerminal(s[j])||followAdd)
                {
                    if(g.find(it->first)!=g.end())
                    {
                        g[string()+s[j]].insert(g[it->first].begin(),
                                g[it->first].end());
                    }
                    else
                    {
                        pending.push_back(string()+s[j]);
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
            if(!isTerminal(s[s.length()-1]))
            {
                g[string()+s[s.length()-1]].insert(
                    g[it->first].begin(),g[it->first].end());
            }
        }
    }
    return g;
}
