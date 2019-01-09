#include <iostream>
#include <cstdlib>
#include <vector>
#include <windows.h>

using namespace std;

class cla 
{
public:
    int next, w, Index;
};

cla Out[1000]; 
vector<cla> Graph[1000], Graph2[1000];
int l[1000] = {0}, e[1000] = {0};

void DFS(int type, int pos) 
{
    if (!type) 
    {
        for (auto &i : Graph2[pos]) 
        {
            int late = l[pos] - i.w;
            l[i.next] = late;
            Out[i.Index].Index = late;
            DFS(0, i.next);
        }
    } 
    else if (type == 1) 
    {
        for (auto &i : Graph[pos]) 
        {
            if (l[i.next] < l[pos] + i.w) 
                l[i.next] = l[pos] + i.w;
            int early = max(Out[i.Index].w, l[pos]);
            Out[i.Index].w = early;
            DFS(1, i.next);
        }
    }
}

int main() 
{
    //init
    int n, theMaxIndex = 0, x;
    cin >> n;

    for (int i = 0; i < n; i++) 
    {
        cla temp;
        cin >> temp.Index >> x >> temp.next >> temp.w;
        theMaxIndex = max(theMaxIndex, temp.next);
        Graph[x].push_back(temp);
        swap(x, temp.next);
        Graph2[x].push_back(temp);
    }

    //Main Calculating
    DFS(1, 0);
    DFS(0, theMaxIndex);

    //Answer output
    cout << "act.\te\tl\tslack\tcritical" << endl;
    for (int i = 1; i <= n; i++) 
    {
        int slack = Out[i].Index - Out[i].w;
        printf("%d\t%d\t%d\t%d\t", i, Out[i].w, Out[i].Index, slack);
        switch(slack)
        {
            case 0:
                cout << "No" << endl;
                break;
            default:
                cout << "Yes" << endl;
        }
    }
    Sleep(10000);
    return 0;
}