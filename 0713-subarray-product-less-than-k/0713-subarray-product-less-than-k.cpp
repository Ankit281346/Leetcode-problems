class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int low = 0;
        int high = 0;
        int n = nums.size();
        int product = 1;
        int count = 0;

        if (k <= 1)
            return 0;

        for (high = 0; high < n; high++) {

            product = product * nums[high];

            while (product >= k) {
                product = product / nums[low];
                low++;
            }

            count = count + (high - low + 1);
        }

        return count;
    }
};