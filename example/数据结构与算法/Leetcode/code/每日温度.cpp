class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
       // 单调栈: 每一次加入元素的时候和栈顶元素进行比较知道遇到大于自己的元素,并且被弹出的元素都需要在 ans 数组中初始化
       vector<int> ans(temperatures.size(),0);
       stack<int> st;
       for(int i = 0 ; i < temperatures.size() ; i ++) {
            if(st.empty()) {
                st.push(i);
            } else {
                while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                    ans[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
       }
       return ans;
    }
}