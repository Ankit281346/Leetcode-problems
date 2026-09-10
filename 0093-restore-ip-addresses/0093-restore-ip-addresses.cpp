class Solution {
public:
    vector<string> ans;

    void backtrack(string& s, int index, int parts, string current) {

        // If we have 4 parts
        if (parts == 4) {
            if (index == s.size()) {
                current.pop_back();   // remove last '.'
                ans.push_back(current);
            }
            return;
        }

        // Try taking 1, 2, or 3 digits
        for (int len = 1; len <= 3; len++) {

            if (index + len > s.size())
                break;

            string part = s.substr(index, len);

            // Leading zero
            if (part.size() > 1 && part[0] == '0')
                continue;

            // Value > 255
            if (stoi(part) > 255)
                continue;

            backtrack(s, index + len, parts + 1,
                      current + part + ".");
        }
    }

    vector<string> restoreIpAddresses(string s) {
        backtrack(s, 0, 0, "");
        return ans;
    }
};