#include <iostream>
#include <string.h>
#include <vector>

int total = 0;
 
using namespace std;
 

bool is_available(int process_id, int allocated[][3],
                  int max[][3], int need[][3], int available[])
{
 
    bool flag = true;
 
    for (int i = 0; i < 3; i++) {
 
        if (need[process_id][i] > available[i])
            flag = false;
    }
 
    return flag;
}
 

void safe_sequence(bool marked[], int allocated[][3], int max[][3],
                   int need[][3], int available[], vector<int> safe, int p)
{
 
    for (int i = 0; i < p; i++) {
 
        if (!marked[i] && is_available(i, allocated, max, need, available)) {
 
            marked[i] = true;
 
            for (int j = 0; j < 3; j++)
                available[j] += allocated[i][j];
 
            safe.push_back(i);
    
            safe_sequence(marked, allocated, max, need, available, safe, p);
            safe.pop_back();
 
            marked[i] = false;
 
         
            for (int j = 0; j < 3; j++)
                available[j] -= allocated[i][j];
        }
    }
 

    if (safe.size() == p) {
 
        total++;
        for (int i = 0; i < p; i++) {
 
            cout <<safe[i] <<" ";
            if (i != (p - 1))
                cout << " ";
        }
 
        cout << ", ";
    }
}
 
// Driver Code
int main()
{
    
 
    int resources[3];
    int p;
    // cout<<"No of processes\n";
    cin>>p;
    // cout<<"Available resources\n";
    for(int i=0;i<3;i++)
    {
    cin>>resources[i];
    }
    int allocated[p][3], max[p][3];
    // cout<<"Enter total input\n";
    for(int i = 0;i<p;i++)
    {
        cin>>allocated[i][0]>>allocated[i][1]>>allocated[i][2]>>max[i][0]>>max[i][1]>>max[i][2];

    }
   
   

    int available[3];
 
    for (int i = 0; i < 3; i++) {
 
        int sum = 0;
        for (int j = 0; j < p; j++)
            sum += allocated[j][i];
 
        available[i] = resources[i] - sum;
    }
 
   
    vector<int> safe;
 

    bool marked[p];
    memset(marked, false, sizeof(marked));
 
   
    int need[p][3];
    for (int i = 0; i < p; i++)
        for (int j = 0; j < 3; j++)
            need[i][j] = max[i][j] - allocated[i][j];
 

    safe_sequence(marked, allocated, max, need, available, safe, p);
 
    return 0;
}