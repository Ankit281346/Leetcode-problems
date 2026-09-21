class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        // dp[r] stores the number of subarrays ending at the current index with product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> next_dp(k, 0);
            int val = num % k;

            // Start a new subarray with just `num`
            next_dp[val]++;

            // Extend existing subarrays
            for (int r = 0; r < k; ++r) {
                if (dp[r] > 0) {
                    next_dp[(r * val) % k] += dp[r];
                }
            }

            // Add the counts of all subarrays ending at this index to the final answer
            for (int r = 0; r < k; ++r) {
                result[r] += next_dp[r];
            }

            dp = std::move(next_dp);
        }

        return result;
    }
};