SocialNet Simulator

Overview

This is a SocialNet Stimulator which implements a "Social Netwrok Stimulation" system in c++ ;

It simulates the backend of a small social media platform where users can:

- Add users
    ADD_USER <username>
    adduser to the social net

- Make friends
    ADD FRIEND <username1> <username2>
    make friends username1 with username2
    
- List their friends
    LIST_FRIENDS <username>
    list all the friends of username 

- Post messages
    ADD POST <username> "<postcontent>"
    create a post by username and stores it as an avl tree

- View their recent posts
    OUTPUT POSTS <username> <N>
    output n latest posts

- Find degrees of separation between users
    DEGREES_OF_SEPARATION <username1> <username2>
    return the shortest path between username 1 and username 2

- Get friend suggestions
    SUGGEST_FRIENDS <username> <N> 
    suggest freinds for username which have more mutual friends and if they are same , priortize them alphabetically 


for compiling ;

To compile the project manually, use:

```bash
g++ -std=c++17 -O2 main.cpp -o SocialNetApp

    



