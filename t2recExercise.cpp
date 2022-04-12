// سیدمصطفی سجادی نسب
// 4001231060
// https://github.com/mim-s/forUniv

#include <iostream>
#include <conio.h>
using namespace std;
int func(int, int, int[]);
int main()
{
    int coins[5] = {1, 2, 5, 10, 50},
        n,
        t = 5;
    cin >> n;
    cout << func(n, t, coins) << '\n';

    getch();
    return 0;
}
int func(int n, int t, int coins[])
{
    if (n == 0)
    {
        return 1;
    }
    if (n < 0 || t == 0)
    {
        return 0;
    }
    int ans = func(n - coins[t - 1], t, coins) + func(n, t - 1, coins);
    return ans;
}