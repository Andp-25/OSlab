#include <bits/stdc++.h>
#include <string.h>
using namespace std;


string mru="";
int curr = 0;

void getfunc(string s1,map<string,string> &ct)
{
    // cout<<"getfunc\n";
    if(ct.find(s1)!=ct.end())
    {
            cout<<ct[s1]<<"\n";
            mru = s1;
    }
    else
    cout<<"-1"<<"\n";
}
void setfunc(string s1,string s2, int cap,map<string,string> &ct)
{
    // cout<<"setfunc\n";
    if(ct.find(s1)!=ct.end())
    {
        ct[s1] = s2;
        mru = s1;
    }
    else
    {
        if (curr==cap)
        {
            ct.erase(mru);
            ct[s1] = s2;

        }
        else
        {
            ct[s1]=s2;
            curr++;

        }
    }

}
int main()
{
    int cap,q;
    cin>>cap;
    cin>>q;
    cout<<"check"<<"\n";
    map<string,string> ct;
    // int curr =0 ;
    // string inp;
    // cin>>inp;
    int i =0;
    // int l = inp.length();
    // cout<<"before loop\n";
    // cout<<i<<" "<<l<<"\n";
    for(int i=0;i<q;i++)
    {
        cout<<"Enter S or G\n";
        char c;
        cin>>c;
        if(c=='S')

        {

            string s1;string s2;
            cin>>s1>>s2;
            setfunc(s1,s2,cap,ct);
        }
        else
        {
            string s1;
            cin>>s1;
            getfunc(s1,ct);

        }
    }
    // for(i=0;i<l;)
    // {
    //     char cur = inp[i];
    //     cout<<cur;
    //     int subct=0;
    //     i+=2;
    //     if (cur == 'G')
    //     {
    //         int tempg = i;
    //         while(true)
    //         {
    //             if(inp[i]!=' ')
    //             {
    //                 i++;
    //                 subct++;
    //             }
    //             else
    //             break;
    //         }
    //         string s1 = inp.substr(tempg,subct);
    //         getfunc(s1,ct);

    //         //i is at space after get command
    //     }
    //     else 
    //     {
    //         int temp = i;
    //         int subct = 0;
    //         while(true)
    //         {
    //             if(inp[i]!=' ')
    //             {
    //                 i++;
    //                 subct++;
    //             }
    //             else
    //             break;
    //         }
    //         string s1 = inp.substr(temp,subct);
    //         i++;
    //         subct=0;
    //         int temp2 = i;
    //         while(true)
    //         {
    //             if(inp[i]!=' ')
    //             {
    //                 i++;
    //                 subct++;
    //             }
    //             else
    //             break;
    //         }
    //         string s2 = inp.substr(temp2,subct);
    //         setfunc(s1,s2,cap,ct);
    //     }
    //     i++;
    // }
    return 0;

}