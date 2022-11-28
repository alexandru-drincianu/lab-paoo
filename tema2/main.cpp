#include <iostream>
#include <string>
using namespace std;

class User {
    protected:
        string username;
        string password;

    public:
    
    User();
    User(const string& username, const string& password);
    ~User();
    User(const User& u);
    User& operator=(const User& u);
    
    string getUsername(){
        return username;
    }
};

// User constructor definition
User::User()
    :username(),
    password()
    {
        cout<<"Account created"<< endl;
    }

// User constructor definition
User::User(const string& username, const string& password)
    :username(username),
     password(password)
    {
        cout<<"Account created"<<endl;
    }

// User destructor definition
User::~User(){
    cout<<"User destructor called"<<endl;
}


// User copy constructor definition
User::User(const User&u)
    :username(u.username),
    password(u.password)
    {
        cout<<"Copy constructor called"<<endl;
    }

// User assignment operator definition    
User& User::operator=(const User& u)
{
    cout<<"Copy assignment operator called"<<endl;
    if(this == &u) return *this; // ITEM 11
    username = u.username;
    password = u.password;
    return *this; // ITEM 10
}

class Regular : public User {
    public:
        Regular();
        Regular(const string& username, const string& password);
        Regular(const Regular& r);
        Regular& operator=(const Regular& r);
        void doSomething(){
            cout<<"User "<< username << " did something" << endl;;
        }
};

Regular::Regular()
    :User(){}
    
Regular::Regular(const string& username, const string& password)
    :User(username,password){}


Regular::Regular(const Regular& r)
    :User(r){} // ITEM 12

Regular& Regular::operator=(const Regular& r)
{
    if(this==&r) return *this;
    User::operator=(r); // ITEM 12
    return *this;
}

class Admin : public User{
    public:
        Admin();
        Admin(const string& username, const string& password);
        
        Admin(const Admin&) = delete;
        Admin& operator= (const Admin&) = delete;

        Regular createRegular(const string& username, const string& password){
            cout<<"User " << username <<  " created" << endl;
            Regular r(username, password);
            return r;
        }
};

Admin::Admin()
    :User(){}
    
Admin::Admin(const string& username, const string& password)
    :User(username,password){}

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

    // self assignment operator
    regular3 = regular3;

    // chain assignment
    regular1 = regular2 = regular3;

    // will not compile
    // Admin admin1(admin2);

    return 0;
}