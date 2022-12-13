#include <iostream>
#include <string>
#include <memory>
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

    static void lockUser(User *u){
        cout<<"User "<<u->getUsername()<<" locked"<<endl;
    }

    static void unlockUser(User *u){
        cout<<"User "<<u->getUsername()<<" unlocked"<<endl;
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

        //ITEM 13
        static Regular* createRegular(const string& username, const string& password){
			return new Regular(username, password);
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

        //ITEM 13
        static Admin* createAdmin(const string& username, const string& password){
			return new Admin(username, password);
		}
};

Admin::Admin()
    :User(){}
    
Admin::Admin(const string& username, const string& password)
    :User(username,password){}


// ITEM 14
class lockUser {
    private:
		shared_ptr<User> u;
	public:
        ~lockUser();
		explicit lockUser(User *us)
		: u(us, User::unlockUser)
		{ 
            User::lockUser(u.get());
		} 
};

lockUser::~lockUser(){
    cout<<"lockUser destructor called"<<endl;
}

int main() {

    cout<< "--------------------- ITEM 13 DEMO ---------------------"<< endl;
    // Declaring a variable regular1 of type unique_ptr (auto_ptr is deprecated)
    unique_ptr<Regular> regular1(Regular::createRegular("dani","12345"));

    cout << regular1 -> getUsername() << endl;


    // won't compile because unique_ptr will not allow it because it should be unique
    // unique_ptr<Regular> regular2(regular1)

    // Declaring a variable admin3 of type shared_ptr
    shared_ptr<Admin> admin1(Admin::createAdmin("alex", "12345"));

    // print admin1 username
    cout << admin1 -> getUsername() << endl;

    //shared_ptr allows us to copy 
    shared_ptr<Admin> admin2(admin1);
    cout << admin1 -> getUsername() << endl;
    cout << admin2 -> getUsername() << endl;


    cout<< "--------------------- ITEM 14 DEMO ---------------------" << endl;


    User *u = new User("Maria", "password");
	{
        // user is locked when it's created
		lockUser lu(u);
		cout << u->getUsername() << endl;
        // user is unlocked after lockUser destructor is called
	}
	cout<<"after user was unlocked"<<endl;
    return 0;
}