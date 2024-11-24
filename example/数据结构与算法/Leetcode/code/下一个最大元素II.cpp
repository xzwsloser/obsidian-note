class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
       vector<int> res(nums.size() , -1);
       stack<int> st;
       for(int i = 0 ; i < 2*nums.size() ; i ++) {
            if(st.empty()) {
                st.push(i % nums.size());
            } else {
                while(!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                    res[st.top()] = nums[i % nums.size()];
                    st.pop();
                }
                st.push(i % nums.size());
            }
       }
       return res;
    }
};