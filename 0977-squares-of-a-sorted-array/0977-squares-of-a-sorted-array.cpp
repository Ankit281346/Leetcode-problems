class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
           int n = nums.size();
            vector<int> result(n);
        int left=0;
        int right=nums.size()-1;
        int k=n-1;

        while(left<=right){
            if(abs(nums[left])>abs(nums[right])){
                result[k]=nums[left]*nums[left];
                left++;
            }else{
                result[k]=nums[right]*nums[right];
                right--;
            }
            k--;
        }
        return result;

    }    
};
    
    