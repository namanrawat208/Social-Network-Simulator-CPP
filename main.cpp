#include "Social_graph.hpp"

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

vector<string> splitBySpaceKeepQuotes(const string &line){
    vector<string> tokens;
    int n = line.size();
    for(int i=0;i<n;){
        while(i<n && isspace((unsigned char)line[i])) i++;
        if(i>=n) break;

        if(line[i]=='"'){ // Quoted string
            int j=i+1;
            string t;
            while(j<n && line[j]!='"'){ t.push_back(line[j]); j++; }
            tokens.push_back(t);
            if (j < n) {
                i = j + 1; 
            } else {
                i = j;     
            }
        } else { // Normal token
            int j=i;
            string t;
            while(j<n && !isspace((unsigned char)line[j])){ t.push_back(line[j]); j++; }
            tokens.push_back(t);
            i=j;
        }
    }
    return tokens;
}

int main() {
    SocialNet sn;
    string line;

    while(getline(cin, line)){
        if(line.empty()) continue;
        vector<string> tokens = splitBySpaceKeepQuotes(line);
        if(tokens.empty()) continue;

        string command = tokens[0];

        if (command=="ADD_USER" && tokens.size() ==2){
            sn.addUser(tokens[1]);
            
        }
        else if (command=="ADD_FRIEND" && tokens.size()==3){
            sn.addFriend(tokens[1],tokens[2]);
            
        }
        else if (command == "LIST_FRIENDS" && tokens.size()==2){
            sn.listFriends(tokens[1]);
        }
        else if (command == "SUGGEST_FRIENDS" && tokens.size() == 3) {
            int N = stoi(tokens[2]);
            sn.suggestFriends(tokens[1], N);
        }
        else if (command == "DEGREE_OF_SEPARATION" && tokens.size()==3){
            sn.degreesOfSeparation(tokens[1],tokens[2]);
        }
        else if (command == "ADD_POST" && tokens.size()==3){
            sn.addPost(tokens[1],tokens[2]);
        }
        else if (command == "OUTPUT_POST" && tokens.size()==3){
            int N = stoi(tokens[2]);
            sn.outputPosts(tokens[1],N);
        }
        else if (command == "exit") {
            break; // exit program
        }
        else {
            cout << "Unknown command: " << tokens[0] << endl;
        }

    }
    return 0;
}