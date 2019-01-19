#include "Probability.h"

#include <algorithm>

int Factorial(int n)
{
    int const MAX_N = 12;           // Maximum n whose factorial can be represented in 32 bits

    static int const f[MAX_N + 1] =
    {
        1,          //  0!
        1,          //  1!
        2,          //  2!
        6,          //  3!
        24,         //  4!
        120,        //  5!
        720,        //  6!
        5040,       //  7!
        40320,      //  8!
        362880,     //  9!
        3628800,    // 10!
        39916800,   // 11!
        479001600,  // 12!
    };

    if (n < 0 || n > MAX_N)
        return 0;
    else
        return f[n];
}

__int64 Factorial64(int n)
{
    int const MAX_N = 20;           // Maximum n whose factorial can be represented in 64 bits

    static __int64 const f[MAX_N + 1] =
    {
        1i64,                   //  0!
        1i64,                   //  1!
        2i64,                   //  2!
        6i64,                   //  3!
        24i64,                  //  4!
        120i64,                 //  5!
        720i64,                 //  6!
        5040i64,                //  7!
        40320i64,               //  8!
        362880i64,              //  9!
        3628800i64,             // 10!
        39916800i64,            // 11!
        479001600i64,           // 12!
        6227020800i64,          // 13!
        87178291200i64,         // 14!
        1307674368000i64,       // 15!
        20922789888000i64,      // 16!
        355687428096000i64,     // 17!
        6402373705728000i64,    // 18!
        121645100408832000i64,  // 19!
        2432902008176640000i64, // 20!
    };

    if (n < 0 || n > MAX_N)
        return 0;
    else
        return f[n];
}

int Combinations(int n, int r)
{
    // nCr = nPr / r! = n! / ( n - r )! / r!
    //
    // In order to expand the possible range of values without encountering overflow, we have to rewrite the
    // equation. Note that nCr = nC(r-1) * (n-r+1)/r and nCr is always an integer, i.e. nC(r-1) * (n-r+1) is
    // a multiple of r.
    //
    // nC1 = n/1
    // nC2 = nC1 * (n-1)/2 = n/1 * (n-1)/2
    // nC3 = nC2 * (n-2)/3 = n/1 * (n-1)/2 * (n-2)/3
    // nCr = n/1 * (n-1)/2 * (n-2)/3 * ... (n-r+1)/r
    //
    // Note also that nCr = nC(r+1) * (r+1)/(n-r) and the same logic applies.
    //
    // nCn = 1
    // nC(n-1) = nCn * n/1 = 1 * n/1 = n/1
    // nC(n-2) = nC(n-1) * (n-1)/2 = n/1 * (n-1)/2
    // nC(n-3) = nC(n-2) * (n-2)/3 = n/1 * (n-1)/2 * (n-2)/3
    // nCr = n/1 * (n-1)/2 * (n-2)/3 * ... (r+1)/(n-r)
    //
    // Since both arrive at the same result using a different number of iterations, we simply choose the smaller of
    // r and n-r.

    int c = 1;
    int k = std::min(r, n - r);

    int a = n;

    for (int i = 1; i <= k; ++i)
    {
        c *= a;
        c /= i;
        --a;
    }

    return c;
}

int Permutations(int n, int r)
{
    // nPr = n! / ( n - r )!
    //
    // In order to expand the possible range of values without encountering overflow, we have to rewrite the
    // equationn as nPr = (n-r+1) * (n-r+2) * (n-r+3) * ... n.

    if (n < 0 || r < 0 || n < r)
        return 0;

    int p = 1;

    for (int i = n - r + 1; i <= n; ++i)
    {
        p *= i;
    }

    return p;
}
