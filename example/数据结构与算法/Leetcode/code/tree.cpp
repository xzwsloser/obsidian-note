#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
// 定义数据结构
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int val , struct TreeNode* left , struct TreeNode* right) : val(val) , left(left) , right(right) {}
    TreeNode(int val): val(val) , left(nullptr) , right(nullptr) {}
    TreeNode() {}
} TreeNode;
/**
 *        1 
 *      /  \ 
 *     2    3
 *    / \  / \ 
 *   4   5 6  7
 */
/**
 *  定义测试函数
 */
static void create_tree(TreeNode* root);

static void pre_order_re(TreeNode* root);  // 递归前序遍历
static void in_order_re(TreeNode* root);   // 递归中序遍历
static void back_order_re(TreeNode* root); // 递归后序遍历

static void pre_order(TreeNode* root);  // 迭代前序遍历
static void in_order(TreeNode* root);  // 迭代中序遍历
static void back_order(TreeNode* root);  // 迭代后序遍历
static void level_order(TreeNode* root);  // 层次遍历

int main()
{
    // 构建树
    TreeNode* root = new TreeNode(1);
    create_tree(root);
    printf("pre_order_re \n");
    pre_order_re(root);
    printf("\n");
    printf("in_order_re \n");
    in_order_re(root);
    printf("\n");
    printf("back_order_re \n");
    back_order_re(root);
    printf("\n");
    printf("pre_order \n");
    pre_order(root);
    printf("\n");
    printf("in_order \n");
    in_order(root);
    printf("\n");
    printf("back_order \n");
    back_order(root);
    printf("\n");
    printf("level_order \n");
    level_order(root);
    printf("\n");
}

static void create_tree(TreeNode* root)
{
    root -> left = new TreeNode(2);
    root -> right = new TreeNode(3);
    root -> left -> left = new TreeNode(4);
    root -> left -> right = new TreeNode(5);
    root -> right -> left = new TreeNode(6);
    root -> right -> right = new TreeNode(7);
}

static void pre_order_re(TreeNode* root)
{
    if(root == nullptr) return ;
    printf("%d " , root -> val);
    pre_order_re(root -> left);
    pre_order_re(root -> right);
}

static void in_order_re(TreeNode* root)
{
    if(root == nullptr) return ;
    in_order_re(root -> left);
    printf("%d " , root -> val);
    in_order_re(root -> right);
}

static void back_order_re(TreeNode* root)
{
    if(root == nullptr) return ;
    back_order_re(root -> left);
    back_order_re(root -> right);
    printf("%d " , root -> val);
}

/**
 *  以下是统一迭代法
 */

static void pre_order(TreeNode* root) {
    TreeNode* node;  // 记录此时遍历到的节点
    stack<TreeNode*> st;
    if(root != nullptr) st.push(root);
    while(!st.empty()) {
        node = st.top();
        if(node != nullptr) {
            // 首先弹出节点,放置重复加入
            st.pop();
            // 右
            if(node -> right) st.push(node -> right);
            // 左
            if(node -> left) st.push(node -> left);
            // 中
            st.push(node);
            st.push(nullptr);
        } else {
            // 弹出空节点
            st.pop();
            node = st.top();
            st.pop();
            printf("%d " , node -> val);
        }
    }
}

static void in_order(TreeNode* root) 
{
    TreeNode* node;
    stack<TreeNode*> st;
    if(root != nullptr) st.push(root);
    while(!st.empty()) {
        node = st.top();
        if(node != nullptr) {
            st.pop();
            // 右
            if(node -> right) st.push(node -> right);
            st.push(node);
            st.push(nullptr);
            if(node -> left) st.push(node -> left);
        } else {
            st.pop();
            node = st.top();
            st.pop();
            printf("%d " , node -> val);
        }
    }
}

static void back_order(TreeNode* root)
{
    TreeNode* node;
    stack<TreeNode*> st;
    if(root != nullptr) st.push(root);
    while(!st.empty()) {
        node = st.top();
        if(node != nullptr) {
            st.pop();
            st.push(node);
            st.push(nullptr); // 放置重复入栈
            if(node -> right) st.push(node -> right);
            if(node -> left) st.push(node -> left);
        } else {
            st.pop();
            node = st.top();
            st.pop();
            printf("%d " , node -> val);
        }
    } 
}

static void level_order(TreeNode* root)
{
    TreeNode* node;
    queue<TreeNode*> que;
    if(root != nullptr) que.push(root);
    while(!que.empty()) {
        node = que.front();
        que.pop();
        printf("%d " , node -> val);
        if(node -> left) que.push(node -> left);
        if(node -> right) que.push(node -> right);
    } 
}



/*********************************
*  复习过程
*********************************/
static void pre_order_re(TreeNode* root) 
{
    if(root == nullptr) return ;
    statck<TreeNode*> st;
    st.push(root);
    TreeNode* node;
    while(!st.empty()) {
        node = st.front();
        if(node != nullptr) {
            st.pop();  // 防止重复入栈
            if(node -> right) st.push(node -> right);
            if(node -> left) st.push(node -> left);
            st.push(node);
            st.push(nullptr);
        } else {
            st.pop();
            node = st.front();
            st.pop();
            printf("%d " , node -> val);
        }
    }
}















































