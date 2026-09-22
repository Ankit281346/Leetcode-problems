class Solution {
    struct Node {
        int prod = 1;
        int cnt[5] = {};
    };

    int n, k;
    vector<Node> tree;

    Node merge(const Node& a, const Node& b) {
        Node res;

        // Product of the whole combined segment
        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside left
        for (int r = 0; r < k; r++) {
            res.cnt[r] = a.cnt[r];
        }

        // Prefixes that start in left and continue into right
        for (int r = 0; r < k; r++) {
            int newRem = (a.prod * r) % k;
            res.cnt[newRem] += b.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int v = nums[l] % k;

            tree[node].prod = v;
            tree[node].cnt[v] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            val %= k;

            tree[node] = Node();
            tree[node].prod = val;
            tree[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(node * 2, l, mid, pos, val);
        } else {
            update(node * 2 + 1, mid + 1, r, pos, val);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {

        this->n = nums.size();
        this->k = k;

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // We only care about nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};