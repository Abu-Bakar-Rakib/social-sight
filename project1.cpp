#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Post
{
public:
    string content;
    Post* next;

    Post(string c) : content(c), next(nullptr) {}
};

class User
{
public:
    string name;
    User* next;
    vector<User*> friends;
    Post* posts;

    User(string n) : name(n), next(nullptr), posts(nullptr) {}

    void addPost(string postContent) {
        Post* newPost = new Post(postContent);
        if (posts == nullptr) {
            posts = newPost;
        } else {
            Post* temp = posts;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newPost;
        }
    }

    void addFriend(User* user) {
        friends.push_back(user);
    }

    void removeFriend(string friendName) {
        for (auto it = friends.begin(); it != friends.end(); ++it) {
            if ((*it)->name == friendName) {
                friends.erase(it);
                break;
            }
        }
    }

    void showFriends() {
        for (User* friendUser : friends) {
            cout << friendUser->name << endl;
        }
    }

    void showPosts() {
        Post* temp = posts;
        while (temp != nullptr) {
            cout << name << " : " << temp->content << endl;
            temp = temp->next;
        }
    }

    void showMutuals(User* otherUser) {
        for (User* friendUser : friends) {
            for (User* otherFriend : otherUser->friends) {
                if (friendUser->name == otherFriend->name) {
                    cout << friendUser->name << endl;
                }
            }
        }
    }
};

class friends_group
{
private:
    User* head;

public:
    friends_group() : head(nullptr) {}

    void addUser(string name) {
        User* newUser = new User(name);
        if (head == nullptr) {
            head = newUser;
        } else {
            User* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
        cout << "Congratulations!" << name << " is signed up in friends_group." << endl;
    }

    User* findUser(string name) {
        User* temp = head;
        while (temp != nullptr && temp->name != name) {
            temp = temp->next;
        }
        return temp;
    }

    void addFriend(string name1, string name2) {
        User* user1 = findUser(name1);
        User* user2 = findUser(name2);

        if (user1 && user2) {
            user1->addFriend(user2);
            user2->addFriend(user1);
            cout << user1->name << " and " << user2->name << " are friends now." << endl;
        } else {
            cout << "One or both users not found." << endl;
        }
    }

    void removeFriend(string name1, string name2) {
        User* user1 = findUser(name1);
        User* user2 = findUser(name2);

        if (user1 && user2) {
            user1->removeFriend(name2);
            user2->removeFriend(name1);
            cout << user1->name << " and " << user2->name << " are no longer friends." << endl;
        } else {
            cout << "One or both users not found." << endl;
        }
    }

    void addPost(string name, string postContent) {
        User* user = findUser(name);
        if (user) {
            user->addPost(postContent);
            cout << user->name << " has successfully posted." << endl;
        } else {
            cout << "User not found." << endl;
        }
    }

    void showPosts(string name) {
        User* user = findUser(name);
        if (user) {
            user->showPosts();
        } else {
            cout << "User not found." << endl;
        }
    }

    void showFriends(string name) {
        User* user = findUser(name);
        if (user) {
            user->showFriends();
        } else {
            cout << "User not found." << endl;
        }
    }

    void showMutuals(string name1, string name2) {
        User* user1 = findUser(name1);
        User* user2 = findUser(name2);

        if (user1 && user2) {
            cout << "Mutual friends of " << user1->name << " and " << user2->name << " are:" << endl;
            user1->showMutuals(user2);
        } else {
            cout << "One or both users not found." << endl;
        }
    }
};

int main()
{
    friends_group app;
    int choice;
    string name1, name2, post;

    cout << "\t\tfriends_group Mates\n\t_______________________________\n__Enter The numbers according to your choice Mate__\n";
    cout << "1. Add user\t2. Add friend\t3. Add post\n4. Show posts\t5. Show friends\t6. Show mutual\n7. Remove friend\t8. Exit\n";

    while (true) {
        cout << "\nYou Chose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter The User Name to Log in: ";
                cin >> name1;
                app.addUser(name1);
                break;
            case 2:
                cout << "Enter the name of who wants to add friends: ";
                cin >> name1;
                cout << "Enter the name " << name1 << " wants to add: ";
                cin >> name2;
                app.addFriend(name1, name2);
                break;
            case 3:
                cout << "Enter the name of the user who wants to post: ";
                cin >> name1;
                cout << "Enter the post: ";
                cin.ignore();
                getline(cin, post);
                app.addPost(name1, post);
                break;
            case 4:
                cout << "Enter the name of the user whose post you want to see: ";
                cin >> name1;
                app.showPosts(name1);
                break;
            case 5:
                cout << "Enter the name of the user to see his/her friends: ";
                cin >> name1;
                cout << name1 << "'s friends are," << endl;
                app.showFriends(name1);
                break;
            case 6:
                cout << "Enter the names of the two users to find mutual friends: ";
                cin >> name1 >> name2;
                app.showMutuals(name1, name2);
                break;
            case 7:
                cout << "Enter the name who wants to remove a friend: ";
                cin >> name1;
                cout << "Enter the name " << name1 << " wants to remove: ";
                cin >> name2;
                app.removeFriend(name1, name2);
                break;
            case 8:
                return 0;
        }
    }
}
