class Solution {
public:
    struct State {
        long long score;
        vector<int> indices;
    };

    vector<vector<State>> dp;
    vector<vector<int>> a;

    bool better(const State& x, const State& y) {
        if (x.score != y.score)
            return x.score > y.score;

        return x.indices < y.indices;
    }

    State solve(int i, int k) {
        if (i == a.size() || k == 0)
            return {0, {}};

        if (dp[i][k].score != -1)
            return dp[i][k];

        // Option 1: skip current interval
        State skip = solve(i + 1, k);

        // Option 2: take current interval
        int r = a[i][1];

        // First interval with left > r
        int next = upper_bound(
            a.begin() + i + 1,
            a.end(),
            r,
            [](int value, const vector<int>& interval) {
                return value < interval[0];
            }
        ) - a.begin();

        State take = solve(next, k - 1);
        take.score += a[i][2];
        take.indices.push_back(a[i][3]);

        // indices must be sorted for lexicographical comparison
        sort(take.indices.begin(), take.indices.end());

        return dp[i][k] = better(take, skip) ? take : skip;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // [left, right, weight, original_index]
        a.resize(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        sort(a.begin(), a.end());

        dp.assign(n, vector<State>(5, {-1, {}}));

        return solve(0, 4).indices;
    }
};