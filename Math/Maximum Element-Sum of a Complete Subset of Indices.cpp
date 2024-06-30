struct sieve
{
  vector<int> primes, composite, sd;
  sieve(int n) : composite(n + 1), sd(n + 1)
  {
    sd[1] = 1;
    for (int i = 2; i <= n; i++)
    {
      if (!composite[i])
      {
        primes.push_back(i);
        sd[i] = i;
      }
      for (int j = 0; j < primes.size() && i * primes[j] <= n; j++)
      {
        composite[i * primes[j]] = true;
        sd[i * primes[j]] = primes[j];
        if (i % primes[j] == 0)
          break;
      }
    }
  }
};

class Solution
{
public:
  long long maximumSum(vector<int> &nums)
  {
    const int K = 1300;
    int n = nums.size();
    sieve sv(n);
    unordered_map<bitset<K>, long long> sum;
    vector<int> prime_idx(n + 1);
    for (int i = 0; i < sv.primes.size(); i++)
      prime_idx[sv.primes[i]] = i;
    for (int i = 0; i < n; i++)
    {
      bitset<K> cur_mask;
      int x = i + 1;
      while (sv.sd[x] != 1)
      {
        int k = sv.sd[x], cnt = 0;
        while (sv.sd[x] == k)
        {
          x /= k;
          cnt++;
        }
        cur_mask[prime_idx[k]] = cnt & 1;
      }
      sum[cur_mask] += nums[i];
    }
    long long ans = 0;
    for (auto &[mask, mask_sum] : sum)
      ans = max(ans, mask_sum);
    return ans;
  }
};
