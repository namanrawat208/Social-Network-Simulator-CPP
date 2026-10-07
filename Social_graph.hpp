#include "AVL_post.hpp"

#include <iostream>

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <cctype>
#include <memory>

// taking account of case insenstivity 
string tolowercase(const string& s){
    string t = s;
    for(auto &c : t){
        c = tolower(c);
    }
    return t;
}
struct User {
    int id;
    string usernameLower;     
    string displayName;       
    unordered_set<int> friends; 
    PostNode* postsRoot;
    User(){
        id = - 1;
        postsRoot = nullptr;
    }
};

class SocialNet {
private:
    vector<User> users; 
    unordered_map<string,int> nameToId; 
    long long timestampCounter = 1; 

public:
    SocialNet(){}
    ~SocialNet(){
        for(auto &u: users){
            deletepost(u.postsRoot);
        } 
    }

    bool addUser(const string &username){
        string str = tolowercase(username);
        if(nameToId.find(str) != nameToId.end()){
            cout<< "user already exist"<<endl;
            return false;
        } 
        int i = users.size();
        User u;
        u.id = i;
        u.usernameLower = str;
        u.displayName = username;
        u.postsRoot = nullptr;
        users.push_back(u);
        nameToId[str] = i;
        cout<<"User added"<<endl;
        return true;
    }


    int getId(const string &username) const {
        string key = tolowercase(username);
        auto it = nameToId.find(key);
        if(it==nameToId.end()) return -1;
        return it->second;
    }

    bool addFriend(const string &a, const string &b){
        int ia = getId(a), ib = getId(b);
        if(ia<0 || ib<0){
            cout << "One of the users does not exist"<< endl;
            return false;
        } 
        if(ia==ib){
            cout<< " Can't make friends "<<endl;
            return false;
        } 
       
        users[ia].friends.insert(ib);
        users[ib].friends.insert(ia);
        cout<<"friends added"<<endl;
        return true;
    }

    void listFriends(const string &username){
        int id = getId(username);
        if(id<0){
            cout << "Not in users list"; 
            return;
        }
        vector<string> fr;
        for(int fid: users[id].friends) fr.push_back(users[fid].displayName);
        sort(fr.begin(), fr.end(), [&](const string &a, const string &b){
            string A = tolowercase(a), B = tolowercase(b);
            if(A==B) return a < b;
            return A < B;
        });
        if(fr.empty()){
            cout << "No freind exist";
            return;
        }
        for(int i=0;i<fr.size();++i){
            if(i) cout << " ";
            cout << fr[i];
        }
        cout << endl;
    }

    void suggestFriends(const string &username, int N){
        int id = getId(username);
        if(id<0 || N<=0) {
            cout << endl; 
            return; 
        }
        unordered_map<int,int> count;
        
        for(int f: users[id].friends){
            for(int fof: users[f].friends){
                if(fof==id) continue;
                if(users[id].friends.find(fof) != users[id].friends.end()) continue;
                count[fof]++;
            }
        }
        if(count.empty()){
            cout <<"No mutual friends"<<endl; 
            return; 
        }
        vector<pair<int,int>> cand;
        for(auto &kv: count) cand.push_back(kv); 
        sort(cand.begin(), cand.end(), [&](const pair<int,int>&A, const pair<int,int>&B){
            if(A.second != B.second) return A.second > B.second; 
            string na = tolowercase(users[A.first].displayName);
            string nb = tolowercase(users[B.first].displayName);
            if(na != nb) return na < nb;
            return users[A.first].displayName < users[B.first].displayName;
        });
        int printed = 0;
        for(auto &p: cand){
            if(printed >= N) break;
            if(printed!=0) cout << " ";
            cout << users[p.first].displayName;
            printed++;
        }
        cout << endl;
    }

    void degreesOfSeparation(const string &a, const string &b){

        int ia = getId(a), ib = getId(b);
        if(ia<0 || ib<0){ cout << "Users are not connected"<<endl; return; }
        if(ia==ib){ cout << "0\n"; return; }
        int n = users.size();
        vector<int> dist(n, -1);
        queue<int>q; q.push(ia); dist[ia]=0;
        // bfs
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v: users[u].friends){
                if(dist[v]==-1){
                    dist[v]=dist[u]+1;
                    if(v==ib){ cout << dist[v] << "\n"; return; }
                    q.push(v);
                }
            }
        }
        cout << "Users are not connected"<<endl;
    }

    void addPost(const string &username, const string &content){
        int id = getId(username);
        if(id<0){
            cout<<"user doesnot exist"<<endl;
            return;

        } 
        long long ts = timestampCounter++;
        users[id].postsRoot = insertHelper(users[id].postsRoot, ts, content);
        cout<<"post added"<<endl;
    }

    void outputPosts(const string &username, int N){
        int id = getId(username);
        if(id<0){ cout << "User doesnot exist"<<endl; return; }
        vector<string> out;
        int rem;
        if(N==-1){
            rem = INT_MAX;
        }
        else{
            rem = N;
        }
        collect_N_latestpost(users[id].postsRoot, out, rem);
        if(out.empty()){ cout << "No post"; return; }
        for(int i=0;i<out.size();++i){
            if(i) cout << "\n";
            cout << out[i];
        }
        cout << "\n";
    }
};