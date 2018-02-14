#include <bits/stdc++.h>
using namespace std;
#include "utilities.h"

namespace opGrammar{
    const int LT = 0, EQ = 1, GT = 2, INVALID=3;
    const int PRECEDENCE_TABLE[7][7]={
      //{i, +, -, *, /, ^, $},
        {3, 2, 2, 2, 2, 2, 2},//i
        {0, 2, 2, 0, 0, 0, 2},//+
        {0, 0, 2, 0, 0, 0, 2},//-
        {0, 0, 0, 2, 0, 0, 2},//*
        {0, 0, 0, 0, 2, 0, 2},///
        {0, 0, 0, 0, 0, 2, 2},//^
        {0, 0, 0, 0, 0, 0, 1},//$
    };
    int op2int(string s)
    {
        if(s=="+")
            return 1;
        if(s=="-")
            return 2;
        if(s=="*")
            return 3;
        if(s=="/")
            return 4;
        if(s=="^")
            return 5;
        if(s=="$")
            return 6;
        return 0;
    }
    
    bool bottomUpParser(vector<string> input)
    {
        stack<string> ss;
        ss.push("$");
        input.push_back("$");
        uint i=0;
        while(!ss.empty())
        {
            if(ss.top()=="$"&&input[i]=="$")
                return true;
            switch(PRECEDENCE_TABLE[op2int(ss.top())][op2int(input[i])])
            {
                case LT:
                case EQ:
                ss.push(input[i]);
                i++;
                break;
                case GT:
                ss.pop();
                break;
                case INVALID:
                break;
            }
            cerr<<ss<<endl;
        }
        return false;
    }
}

vector<string> tokenize(string input);

int main()
{
    freopen("input1.txt","r",stdin);
    string input;
    cin>>input;
    try{
        vector<string> vs=tokenize(input);
        cout<<vs<<endl;
        cout<<opGrammar::bottomUpParser(vs)<<endl;
    }
    catch(const char* emsg)
    {
        cerr<<emsg<<endl;
    }
    return 0;
}

vector<string> tokenize(string input)
{
    static vector<string> r;
    bool isIden=false,isConst=false,isOper=false;
    string operators="+-*/^";
    for(uint i=0,j=-1;i<input.length();i++)
    {
        if(isalpha(input[i]))
        {
            if(!isConst)
            {
                if(!isIden)
                {
                    j++;
                    r.push_back("");
                    isIden=true;
                    isOper=false;
                }
            }
            else
            {
                throw "invalid expression";
            }
        }
        else if(isdigit(input[i]))
        {
            if(!isIden)
            {
                if(!isConst)
                {
                    j++;
                    r.push_back("");
                    isConst=true;
                    isOper=false;
                }
            }
            else
            {
                isIden=true;
            }
        }
        else if(operators.find(input[i])!=string::npos)
        {
            if(!isOper)
            {
                j++;
                r.push_back("");
                isConst=isIden=false;
                isOper=true;
            }
            else
            {
                throw "invalid expression";
            }
        }
        else
        {
            throw "invalid expression";
        }
        r[j].push_back(input[i]);
    }
    return r;
}
