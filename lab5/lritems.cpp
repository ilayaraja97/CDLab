#include <bits/stdc++.h>
using namespace std;
#include "utilities.h"

set <map <string ,vector<string> > > getLRItems(map< string,vector<string> > &prods);
void closure(map< string,vector<string> > &prods,map< string,vector<string> > &item,string lval);
void completeLR(set <map <string ,vector<string> > > &lr,map< string,vector<string> > &prods,map< string,vector<string> > &item);

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
    //map< string,vector<string> > item;
    //item["X"].push_back(".S");
    //closure(prods,item,"X");
    //cout<<item<<endl<<endl;;
    cout<<getLRItems(prods)<<endl;
    return 0;
}

set <map <string ,vector<string> > > getLRItems(map< string,vector<string> > &prods)
{
    static set <map <string ,vector<string> > > lr;
    map< string, vector<string> > item;
    //make augumented grammar
    item["X"].push_back(".S");
    completeLR(lr,prods,item);
    return lr;
}

void completeLR(set <map <string ,vector<string> > > &lr,map< string,vector<string> > &prods,map< string,vector<string> > &item)
{
    //debug(item);
    for(auto it=item.begin();it!=item.end();it++)
    {
        closure(prods,item,it->first);
    }
    lr.insert(item);
    map< string, map< string, vector<string> > > newItems;
    for(auto it=item.begin();it!=item.end();it++)
    {
        for(auto is=it->second.begin();is!=it->second.end();is++)
        {
            string s=*is;
            uint i=s.find('.');
            if(i==s.size()-1)
            continue;
            s[i]=s[i+1];
            s[i+1]='.';
            newItems[string()+s[i]][it->first].push_back(s);
        }
    }
    for(auto it=newItems.begin();it!=newItems.end();it++)
    {
        completeLR(lr,prods,it->second);
    }
}

void closure(map< string,vector<string> > &prods,map< string,vector<string> > &item,string lval)
{
    //debug(item);
    
    if(isupper(lval[0]))
    //try{
    for(auto is=item[lval].begin();is!=item[lval].end();is++)
    {
        bool recursion=true;
        string s=*is;
        for(uint i=1;i<s.length();i++)
        {
            debug(s[i-1]);
            debug(s[i]);
            cout<<s<<endl;
            debug(item);
            if(s[i-1]=='.'&&isupper(s[i]))
            {
                debug(item);
                if(string()+s[i]!=lval)
                {
                    recursion=false;
                }
                //debug(s[i]);
                //debug(lval);
                if(item[string()+s[i]].size()==prods[string()+s[i]].size())
                {
                    recursion=false;
                }
                item[string()+s[i]]=prods[string()+s[i]];
                //debug(prods[string()+s[i]]);
                for(auto ir=item[string()+s[i]].begin();ir!=item[string()+s[i]].end();ir++)
                {
                    *ir="."+*ir;
                }
                
                if(recursion)
                closure(prods,item,string()+s[i]);
            }
            debug(2);
        }
    }
    //}
    //catch(exception &e)
    //{
        //debug(item);
        //debug(lval);
    //}
}
