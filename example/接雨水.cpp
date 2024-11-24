// 单调栈
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int result = 0;
        st.push(0);
        for(int i = 1 ; i < height.size() ; i ++) {
            if(height[i] <= height[st.top()]) {
                st.push(i);
            } else {
                while(!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if(!st.empty()) {
                        int h = min(height[st.top()] , height[i]) - height[mid];
                        int w = i - st.top() - 1;
                        result += h * w;
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};

// 双指针
class Solution {
public:
    int trap(vector<int>& height) {
        int result = 0;
        vector<int> maxLeft(height.size() , 0);
        vector<int> maxRight(height.size() , 0);
        maxLeft[0] = height[0];
        maxRight[height.size() - 1] = height[height.size() - 1];
        for(int i = 1 ; i < height.size() ; i ++) {
            maxLeft[i] = max(height[i],maxLeft[i - 1]);
        }
        for(int j = height.size() - 2 ; j >= 0 ; j --) {
            maxRight[j] = max(height[j] , maxRight[j + 1]);
        }
        for(int i = 0 ; i < height.size() ; i ++) {
            int count = min(maxLeft[i] , maxRight[i]) - height[i];
            if(count > 0) result += count;
        }
        return result;
    }
};