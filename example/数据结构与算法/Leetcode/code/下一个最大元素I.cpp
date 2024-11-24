class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
       // 1. 利用nums2中的元素建立哈希
       unordered_map<int,int> um;
       for(int i = 0 ; i < nums1.size() ; i ++) {
            um[nums1[i]] = i;
       }
       // 2. 建立单调栈
       vector<int> ans(nums1.size(),-1);
       stack<int> st;
       for(int i = 0 ; i < nums2.size() ; i ++) {
            if(st.empty()) {
                st.push(i);
            } else {
                while(!st.empty() && nums2[i] > nums2[st.top()]) {
                    if(um.count(nums2[st.top()]) > 0) {
                        ans[um[nums2[st.top()]]] = nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
       }
       return ans;
    }
};