class Solution:
    def makeStringSorted(self, s: str) -> int:
        counter, prod, res, mod = [0]*26, 1, 0, 1000000007
        for i, c in enumerate(s[::-1], 1):
            ind = ord(c)-97
            counter[ind] += 1
            res = (res+prod*sum(counter[:ind])//counter[ind])%mod
            prod = prod*i//counter[ind]
        return res
