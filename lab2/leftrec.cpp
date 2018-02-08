#include <bits/stdc++.h>
using namespace std;

///     cout<<vector;
template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v )
{
    os << "{";
    typename vector< T > :: const_iterator it;
    for( it = v.begin(); it != v.end(); it++ )
    {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "}";
}


///     cout<<map;
template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v )
{
    os << "[";
    typename map< F , S >::const_iterator it;
    for( it = v.begin(); it != v.end(); it++ )
    {
        if( it != v.begin() ) os << ", ";
        os << it -> first << " = " << it -> second ;
    }
    return os << "]";
}

void factorize(map< string,vector<string> > &prods)
{
    string z="Z";
    for(auto it=prods.begin();it!=prods.end();it++)
    {
        vector<string> s,r;
        for(auto iv=it->second.begin();iv!=it->second.end();iv++)
        {
            if((it->first)[0]==(*iv)[0])
            {
                //left recur
                s.push_back((*iv).substr(1));
            }
            else
            {
                r.push_back(*iv);
                r.push_back(*iv+z);
            }
        }
        if(s.size()>0)
        {
            prods[z]=s;
            prods[it->first]=r;
            z[0]--;
        }
    }
}

int main(int argv,char *args[])
{
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
    factorize(prods);
    cout<<prods<<endl;
    return 0;
}
    
