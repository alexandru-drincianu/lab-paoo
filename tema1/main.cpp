// #include <iostream>
// #include <string>
// using namespace std;

// class User {
//     protected:
//         string username;
//         string password;

//     public:
//     // User constructor
//     User(const string& username, const string& password);
//     User (const User&) = delete;
//     User& operator= (const User&) = delete;

//     string getUsername(){
//         return username;
//     }
// };

// // User constructor definition
// User::User(const string& username, const string& password)
//     :username(username),
//      password(password)
//     {
//         cout<<"Account created"<<endl;
//     }

// class Regular : public User {
//     public:
//         Regular(const string& username, const string& password):User(username, password){}
//         ~Regular();

//         void doSomething(){
//             cout<<"User "<< username << " did something" << endl;;
//         }
// };

// class Admin : public User{
//     public:
//         Admin(const string& username, const string& password):User(username, password){}
//         ~Admin();
//         Admin(const Admin&) = delete;
//         Admin& operator= (const Admin&) = delete;

//         Regular* createRegular(const string& username, const string& password){
//             cout<<"User " << username <<  " created" << endl;
//             return new Regular(username, password);
//         }
// };


// int main() {
//     cout<<"-------------------------------"<<endl;
//     Admin admin("Alex", "Dani");
//     Admin* admin1 = new Admin("Alex", "12345");
//     Admin* admin2 = new Admin("Paul", "12345");

//     Regular* regular1 = admin1->createRegular("Dan", "12345");
//     regular1->doSomething();

//     cout<<"-------------------------------"<<endl;
//     // calling the copy constructor
//     Regular* regular2(regular1);
//     cout<<regular2->getUsername()<<endl;

//     // calling the copy assignment operator
//     Regular* regular3;
//     regular3=regular1;
//     cout<<regular3->getUsername()<<endl;

//     Admin* admin3(admin1);
//     return 0;
// }

#include <iostream>
#include <string>
using namespace std;

class User {
    protected:
        string username;
        string password;

    public:
    // User constructor
    User(){};
    User(const string& username, const string& password);
    ~User();

    string getUsername(){
        return username;
    }
};

// User constructor definition
User::User(const string& username, const string& password)
    :username(username),
     password(password)
    {
        cout<<"Account created"<<endl;
    }

User::~User(){
    cout<<"Account destroyed"<<endl;
}

class Regular : public User {
    public:
        Regular(){};
        Regular(const string& username, const string& password):User(username, password){}
        ~Regular(){};

        void doSomething(){
            cout<<"User "<< username << " did something" << endl;;
        }
};

class Admin : public User{
    public:
        Admin(const string& username, const string& password):User(username, password){}
        ~Admin(){};
        Admin(const Admin&) = delete;
        Admin& operator= (const Admin&) = delete;

        Regular createRegular(const string& username, const string& password){
            cout<<"User " << username <<  " created" << endl;
            Regular r(username, password);
            return r;
        }
};


int main() {
    cout<<"-------------------------------"<<endl;
    Admin admin1("Alex", "12345");
    Admin admin2("Dani", "12345");

    Regular regular1 = admin1.createRegular("Andrei", "12345");
    regular1.doSomething();

    cout<<"-------------------------------"<<endl;
    // calling the copy constructor
    Regular regular2(regular1);
    cout<<regular2.getUsername()<<endl;

    // calling the copy assignment operator
    Regular regular3;
    regular3=regular1;
    cout<<regular3.getUsername()<<endl;

    // will not compile
    // Admin admin1(admin2);

    return 0;
}
