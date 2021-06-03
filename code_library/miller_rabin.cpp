#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace prm{
    const vector<int> BASES_32 = {2, 3, 5, 7};
    const vector<int> BASES_64 = {2, 450775, 1795265022, 9780504, 28178, 9375, 325};

    const vector<int> SMALL_PRIMES = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 193, 407521, 299210837};

    inline long long fast_modmul(long long a, long long b, long long m){
        if (a >= m) a %= m;
        if (b >= m) b %= m;
        if (m < (long long)UINT_MAX) return (uint64_t)a * b % m;

        #ifdef __SIZEOF_INT128__
            return __int128(a) * b % m;
        #endif

        long double x = (long double)a * b;
        long long c = x / m;

        a = (uint64_t)a * b - (uint64_t)c * m;
        if (a >= m) a -= m;
        if (a < 0) a += m;

        return a;
    }

    long long expo(long long x, long long n, long long m){
        long long res = 1;

        while (n){
            if (n & 1) res = fast_modmul(res, x, m);
            x = fast_modmul(x, x, m);
            n >>= 1;
        }

        return res % m;
    }

    bool is_probable_composite(long long a, long long n, int s){
        long long x = expo(a, (n - 1) >> s, n);
        if (x == 1) return false;

        for (int i = 0; i < s; i++){
            if (x == (n - 1)) return false;
            x = fast_modmul(x, x, n);
        }
        return true;
    }

    bool miller_rabin(long long n, const vector<int>& bases){
        if (n < 2 || (n & 1) == 0) return n == 2;

        for (auto &&p: SMALL_PRIMES){
            if (n == p) return true;
            if (n % p == 0) return false;
        }

        int s = __builtin_ctzll(n - 1);
        for (auto a: bases){
            if (is_probable_composite(a, n, s)) return false;
        }

        return true;
    }

    bool is_prime(long long n){
        if (n < INT_MAX) return miller_rabin(n, BASES_32);
        return miller_rabin(n, BASES_64);
    }
}

int main(){
    using namespace prm;

    assert(is_prime(2));
    assert(is_prime(3));
    assert(is_prime(97));
    assert(is_prime(1000003));
    assert(is_prime(2783117));
    assert(is_prime(1000000007));
    assert(is_prime(2147483647));
    assert(is_prime(143305320273842137LL));
    assert(is_prime(701874195430938151LL));

    assert(!is_prime(1));
    assert(!is_prime(4));
    assert(!is_prime(245)); // 5 * 7 * 7
    assert(!is_prime(7745740235689LL)); // 2783117 * 2783117
    assert(!is_prime(2783117019481819LL)); // 2783117 * 1000000007
    assert(!is_prime(666666673000000003L)); // 1000000009 * 666666667
    assert(!is_prime(33144425233627921LL)); // 100003 * 474119 * 699053
    assert(!is_prime(3533656326712328192LL)); // 822743477 * 4294967296

    return 0;
}
