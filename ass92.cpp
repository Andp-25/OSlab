#include<bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int ram_size;
        cin >> ram_size;
        int q;
        cin >> q;
       
        //pages set for ordering
        //pages value for later retrieval
        map<int,int> pages_value;
        set<pair<int,int>> pages_set;
       
        int usage=0;
        while(q--){
            usage++;
            char type;
            cin >> type;
            if(type=='S'){
                int key,value;
                cin >> key>> value;
                if(pages_value[key]){
                    for(auto it: pages_set){
                        pair<int,int> p1 = it;
                        if(p1.second==key){
                            pages_set.erase(it);
                            break;
                        }
                    }
                    pages_set.insert({usage,key});
                    pages_value[key]=value;
                }
                else{
                    if(pages_set.size()==ram_size)
                    {
                        pair<int,int> p1 = *(--pages_set.end());
                        pages_value[p1.second]=0;
                        pages_set.erase(--pages_set.end());
                    }
                    pages_set.insert({usage,key});
                    pages_value[key]=value;
                }
            }
            else{
                int key;
                cin >> key;
                if(pages_value[key]){
                    cout << pages_value[key] << endl;
                }
                else{
                    cout << -1 << endl;
                }
            }
        }
    }
    return 0;
}