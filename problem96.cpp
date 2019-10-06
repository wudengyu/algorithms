/*暗号
 *动态规划
*/
#include <iostream>
#include <cstring>
#define line 60001
#define MOD 100000000
using namespace std;
int main()
{
    string x, y;
    int *dp[2], *s[2];
    while (!getline(cin, x).eof() && !getline(cin, y).eof())
    {
        int xl = x.length() - 1;
        int yl = y.length() - 1;
        x = ' ' + x;
        y = ' ' + y;
        for (int i = 0; i < 2; i++)
        {
            *(dp + i) = new int[yl + 1];
            *(s + i) = new int[yl + 1];
        }
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j <= yl; j++)
            {
                dp[i][j] = 0;
                s[i][j] = 1;
            }
        }
        for (int i = 1; i <= xl; i++)
        {
            int cu = i & 1, pr = cu ^ 1;
            for (int j = 1; j <= yl; j++)
            {
                if (x[i] == y[j])
                    dp[cu][j] = dp[pr][j - 1] + 1;
                else
                    dp[cu][j] = max(dp[pr][j], dp[cu][j - 1]);
                s[cu][j] = 0;
                if (dp[cu][j] == dp[pr][j])
                    s[cu][j] += s[pr][j];
                if (dp[cu][j] == dp[cu][j - 1])
                    s[cu][j] += s[cu][j - 1];
                if (dp[cu][j] == dp[pr][j] && dp[cu][j] == dp[cu][j - 1] && dp[pr][j - 1] == dp[cu][j])
                    s[cu][j] -= s[pr][j - 1];
                if (x[i] == y[j] && dp[cu][j] == dp[pr][j - 1] + 1)
                    s[cu][j] += s[pr][j - 1];
                if (s[cu][j] > MOD)
                    s[cu][j] %= MOD;
                if (s[cu][j] < 0)
                    s[cu][j] = (s[cu][j] % MOD) + MOD;
            }
        }
        cout << dp[xl & 1][yl] << endl;
        if (dp[xl & 1][yl] == 0)
            cout << 0 << endl;
        else
            cout << s[xl & 1][yl] << endl;
        for (int i = 0; i < 2; i++)
        {
            delete[] * (dp + i);
            delete[] * (s + i);
        }
    }
}