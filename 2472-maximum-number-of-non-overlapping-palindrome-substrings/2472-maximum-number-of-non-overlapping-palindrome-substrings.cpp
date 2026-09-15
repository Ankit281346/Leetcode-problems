class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        vector<vector<bool>> pal(n, vector<bool>(n, false));

        // Find all palindromic substrings
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (s[i] == s[j] &&
                    (len <= 2 || pal[i + 1][j - 1])) {
                    pal[i][j] = true;
                }
            }
        }

        // dp[i] = maximum number using first i characters
        vector<int> dp(n + 1, 0);

        for (int j = 0; j < n; j++) {
            // Don't choose anything ending at j
            dp[j + 1] = dp[j];

            // Try every palindrome ending at j
            for (int i = 0; i <= j - k + 1; i++) {
                if (pal[i][j]) {
                    dp[j + 1] = max(dp[j + 1], dp[i] + 1);
                }
            }
        }

        return dp[n];
    }
};