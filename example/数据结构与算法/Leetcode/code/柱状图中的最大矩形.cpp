class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
       heights.insert(heights.begin(),0);
       heights.push_back(0);
       stack<int> st;
       int result = 0;
       for(int i = 0 ; i < heights.size() ; i ++) {
            while(!st.empty() && heights[i] < heights[st.top()]) {
                int mid = st.top();
                st.pop();
                if(!st.empty()) {
                    int h = heights[mid];
                    int w = i - st.top() - 1;
                    result = max(result , h * w);       
                }
            }
            st.push(i);
       } 
       return result;
    }
};