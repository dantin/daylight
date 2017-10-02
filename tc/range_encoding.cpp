#include <iostream>
#include <vector>
using namespace std;

class RangeEncoding
{
public:
    int minRanges(vector<int> arr);
};

int RangeEncoding::minRanges(vector<int> arr)
{
    int prev = arr[0], n = 1;

    for(int i = 1; i < arr.size(); ++i)
    {
        if(prev + 1 == arr[i])
        {
            prev = arr[i];
            continue;
        }
        else
        {
            prev = arr[i];
            ++n;
        }

    }
    return n;
}

int main()
{
    RangeEncoding re;
    int n;
    vector<int> v;

    while(true)
    {
        cin >> n;
        if(n == -1) break;
        v.push_back(n);
    }
    cout << endl;


    cout << re.minRanges(v) << endl;
    return 0;

}
