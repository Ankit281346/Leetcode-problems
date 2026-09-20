class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            int reversedPosition = 'z' - s[i] + 1;
            int stringPosition = i + 1;

            ans += reversedPosition * stringPosition;
        }

        return ans;
    }
};