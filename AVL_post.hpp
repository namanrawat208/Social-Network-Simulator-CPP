#ifndef AVLPOST_HPP
#define AVLPOST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <cctype>
#include <memory>


using namespace std;
struct PostNode{
    long long timestamps;
    string content ;
    PostNode* left ;
    PostNode* right;
    int height ;
    PostNode(long long time_of_upload , string content_in_post){
        timestamps = time_of_upload;
        content = content_in_post;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

int height_of_post(PostNode* post){
    if (post!= nullptr){
        return post->height ;
    }
    else{
        return -1;
    }
    
}
void update_height_of_post(PostNode* post){
    post->height = 1+max(height_of_post(post->left),height_of_post(post->right));
}
PostNode* rightRotatePost(PostNode* y){
    PostNode* x = y->left;
    PostNode* T2 = x->right;
    x->right = y;
    y->left = T2;

    update_height_of_post(y);
    update_height_of_post(x);
    return x;
}

PostNode* leftRotatePost(PostNode* y){
    PostNode* x = y->right;
    PostNode* T2 = x->left;
    
    y->right = T2;
    x->left = y;
    
    update_height_of_post(y);
    update_height_of_post(x);
    return x;
}

int get_balance_factor(PostNode* post){
    if (post == nullptr){
        return 0;

    }
    else{
        int h = height_of_post(post->left)-height_of_post(post->right);
        return h;
    }
}

PostNode* insertHelper(PostNode* root , long long time , const string &s) {
        // 1. Standard BST insertion
        if (root == nullptr)
            return new PostNode(time,s);

        if (time < root->timestamps)
            root -> left = insertHelper(root->left, time,s);
        else if (time > root->timestamps)
            root->right = insertHelper(root->right, time,s);
        
        // 2. Update height of this ancestor node
        root->height = 1 + max(height_of_post(root->left), height_of_post(root->right));

        // 3. Get the balance factor to check for imbalance
        int balance = get_balance_factor(root);

        // 4. If unbalanced, perform rotations
        // Left Left Case
        // implement
        if (balance > 1 && time < root->left->timestamps) {
            return rightRotatePost(root);
        }
        // Right Right Case
        // implement
        if (balance < -1 && time > root->right->timestamps) {
            return leftRotatePost(root);
        }
        // Left Right Case
        if (balance > 1 && time > root->left->timestamps) {
            root->left = leftRotatePost(root->left);
            return rightRotatePost(root);
        }
        // Right Left Case
        // implement
        if (balance < -1 && time < root->right->timestamps) {
            root->right = rightRotatePost(root->right);
            return leftRotatePost(root);
        }
        return root;
    }

void collect_N_latestpost(PostNode* root , vector<string>&out , int& remaining){
    if(!root || remaining==0){
        return;
    }
    collect_N_latestpost(root->right , out , remaining);

    if (remaining == 0 ){
        return ;
    }

    out.push_back(root->content);
    remaining--;

    collect_N_latestpost(root->left , out , remaining);
}

void deletepost(PostNode* post){
    if(!post){
        return ;
    }
    else{
        deletepost (post->right);
        deletepost (post->left);
        delete post;
    }
}

#endif