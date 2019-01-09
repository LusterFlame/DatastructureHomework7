#include <iostream>
#include <list>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
int gp[110];
int to_gp(int x)
{
    if (!(gp[x] - x))
        return gp[x];
    gp[x] = to_gp(gp[x]);
    return to_gp(gp[x]);
}
class cla {
public:
    int VertexA;
    int VertexB;
    int weight;
};
vector<cla> ans;
list<int> gpli;
list<cla> Graph[110];

int main()
{
    int n, i, theMaxIndex = 0, mf = 0, mto, mwei;
    vector<cla> ans;
    cin >> n;
    for (i = 0; i < n; ++i) {
        cla tmp;
        cin >> tmp.VertexA >> tmp.VertexB >> tmp.weight;
        theMaxIndex = max(max(tmp.VertexB, tmp.VertexA), theMaxIndex);
        Graph[tmp.VertexA].push_back(tmp);
        swap(tmp.VertexA, tmp.VertexB);
        Graph[tmp.VertexA].push_back(tmp);
    }
    // cout << theMaxIndex << endl;
    for (i = 0; i <= theMaxIndex + 5; ++i) {
        gp[i] = i;
        gpli.push_back(i);
    }
    theMaxIndex++;
    while (theMaxIndex != 1) {
        for (list<int>::iterator it = gpli.begin(); it != gpli.end();) {
            mwei = 2e9;
            for (auto j = Graph[*it].begin(); j != Graph[*it].end(); ++j) {
                cla tmp = *j;
                if (mwei > tmp.weight && to_gp(tmp.VertexB) != to_gp(tmp.VertexA)) {
                    mf = tmp.VertexA;
                    mto = tmp.VertexB;
                    mwei = tmp.weight;
                }
            }
            // cout << endl << endl;
            if (mwei != 2e9) {
                theMaxIndex--;
                for (auto iter : Graph[*it]) {
                    Graph[mto].push_back(iter);
                }
                gp[*it] = mto;
                cla tmp;
                tmp.VertexB = mto;
                tmp.weight = mf;
                tmp.VertexA = mwei;
                cout << tmp.VertexB << " " << tmp.weight << " " << tmp.VertexA << endl;
                if (theMaxIndex == 1) {
                    break;
                };
                while (Graph[*it].size()) {
                    Graph[*it].pop_back();
                }
                // cout<<theMaxIndex<<endl;

                it = gpli.erase(it);
            }
        }
    }
    return 0;
}