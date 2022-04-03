#include <iostream>
#include<bits/stdc++.h>
#include<fstream>
#include <string>
/* E:\Programming\AskMe */
using namespace std;

string getLine()
{
    string Q;
    cin.ignore();
    getline(cin,Q);
    return Q;
}


// Question class //


class question
{
private:
    char anonymous ;
    int Asker = 0;
    int Replier = 0;
    static int lastQ ;
    string Question ;
    string answer = " Not Answered yet! ";
    int id=0;
public :
    question( int Asker, int Replier, string Question, char anonymous ) : Asker(Asker), Replier(Replier),anonymous (anonymous), Question(Question)
    {
        id = ++lastQ;

    }
    question(   int Asker,int Replier, string Question, string answer, char anonymous, int id):  Asker(Asker), Replier(Replier), Question(Question), answer(answer), anonymous(anonymous), id(id)
    {
        ++lastQ;

    }

    int getID()
    {
        return id;
    }
    int getAsker()
    {
        return Asker;
    }
    int getReplier()
    {
        return Replier;
    }
    char isAnonymous()
    {
        return anonymous ;
    }
    string getQuestion()
    {
        return Question;
    }
    string getAns()
    {
        return answer;
    }

    void updateAnswer(string Answer)
    {
        answer = Answer;
    }


    static int getLastQ();
    static void deleteLastQ();
};





class user              /*  USER CLASS  */
{
private:
    int id=0;
    string name;
    string pass;
    static int users_num;

public:
    user( string name, string pass) : name(name), pass(pass)
    {
        id=users_num++;
        //users_num++;
        // addUser();
        //createFile();
    }
    user( int ID, string name, string pass) : id(ID),  name(name), pass(pass)
    {
        users_num++;
        //users_num++;
        // addUser();
        //createFile();
    }
    string getname()
    {
        return name;
    }
    //      void     setname():
    string getpass()
    {
        return pass;
    }
    //  void         setpass();
    int getID()
    {
        return id ;
    }
    static int getNum();

    void QuestionsToMe(vector<question> &q) //   Display all questions came to me (answered or not), and not showing id of anonymous users
    {
        for(int i=0; i<question::getLastQ(); i++)
        {
            if(q[i].getReplier() == getID() && q[i].isAnonymous() =='a')
            {
                cout<< "Question "<<q[i].getID()<<" to user "<<q[i].getReplier()<<"\tQuestion : "<<q[i].getQuestion()<<endl;
                cout<<"Answer : "<< q[i].getAns()<<endl;
            }
            else if(q[i].getReplier() == getID() && q[i].isAnonymous() =='n')
            {
                cout<< "Question "<<q[i].getID()<<" from user "<<q[i].getAsker()<<" to user "<<q[i].getReplier()<<"\tQuestion : "<<q[i].getQuestion()<<endl;
                cout<<"Answer : "<< q[i].getAns()<<endl;

            }
        }
    }

    void MyQuestions(vector<question> &q) // Display my answered questions

    {
        for(int i=0; i<question::getLastQ(); i++)
        {
            if(q[i].getAsker() == getID() && q[i].getAns() != " Not Answered yet! ")
            {
                cout<< "Question "<<q[i].getID()<<" from user "<<q[i].getAsker()<<" to user "<<q[i].getReplier()<<"\tQuestion : "<<q[i].getQuestion()<<endl;
                cout<<"Answer : "<< q[i].getAns()<<endl;
            }

        }
    }
    void Answer(int qID, vector<question> &q) // editing the files and writing the answer
    {
        string A;
        for(int i=0; i<question::getLastQ(); i++)
            if( q[i].getID() == qID)
            {
                if(getID() == q[i].getReplier())
                {
                    cout<< " Write the answer : ";
                    A=getLine();
                    q[i].updateAnswer(A);
                    update(q);
                    break;
                }
                else
                {
                    cout<< " ID is incorrect "<<endl;
                    break;
                }
            }
    }

    void addUser()
    {
        ofstream write;
        write.open( "users.txt", ios::app | ios::out);
        write <<getID() << "\t" << getname() << "\t" << getpass()<< endl << endl;

    }



    void update(int qID, int userID, string Question, char NA)  // Ask a question
    {
        ofstream write;
        write.open( "questions.txt", ios::app );
        if(write.fail())
            cout<< "failed to open file !"<<endl;
        write << endl;
        write << NA << "\t" << qID <<"\t" << getID() << "\t" << userID << "\t" << endl;
        write << Question << endl;
        write << " Not answered yet! " ;

    }

    void update(vector<question> &q) //  // Deleting YOUR  questions (that you were asked not others)  from "questions" file
    {
        ofstream write;
        write.open( "questions.txt", ios::out | ios::trunc );
        if(write.fail())
            cout<< "failed to open file !"<<endl;

        for(int i=0; i<question::getLastQ(); i++)
        {
            write << endl;
            write << q[i].isAnonymous() << "\t" << q[i].getID() <<"\t" << q[i].getAsker() << "\t" << q[i].getReplier() << "\t" << endl;
            write << q[i].getQuestion() << endl;
            write <<  q[i].getAns() << endl ;

        }
    }


    void Delete(int qID, vector<question> &q) // and add answer
    {
        vector<question>::iterator it = q.begin() ;
        for(int i=0; i<question::getLastQ(); i++)
        {
            if( q[i].getID() == qID)
            {
                if(getID() == q[i].getReplier())
                {
                    q.erase(it + i);
                    question::deleteLastQ();
                    cout <<" question deleted !" << endl;
                    update(q);
                    break;
                }
                else
                {
                    cout <<" ID is incorrect !" << endl;
                    break;
                }
            }
            else if(i == question::getLastQ() - 1)
                cout <<" ID is incorrect!" << endl;

        }
    }


    void Ask(int userID, vector<question> &q)  // Asking a question
    {
        char NA;
        cout << "a- Anonymous "<<endl;
        cout << "n- Not Anonymous "<<endl;
        cin>>NA;

        string Q ;


        switch(NA)
        {
        case 'a':
        {
            cout << "Write your Question :  ";
            Q = getLine();
            question newQuestion = question(id, userID, Q, NA);
            q.push_back(newQuestion);
            update( newQuestion.getID(), userID, Q, NA);
        }
        break;
        case 'n':
        {
            cout << "Write your Question :  ";
            Q = getLine();
            question newQuestion = question(id, userID, Q, NA);
            q.push_back(newQuestion);
            update( newQuestion.getID(), userID, Q, NA);
        }
        break;
        default:
        {
            cout <<" error !"<<endl;
        }
        break;
        }
    }


    void Users(vector<user> &users) // showing users of the system
    {
        cout<< "ID\tName"<<endl;
        for (int i = 0 ; i <=user::getNum() ; i++)
        {
            cout<< users[i].getID()<<"\t"<<users[i].getname()<<endl;
        }
    }
    void feed(vector<question> &q)
    {
        for(int i=0; i<question::getLastQ(); i++)
        {
            if(q[i].getAns() != " Not Answered yet! " && q[i].isAnonymous() =='a')
            {
                cout<< "Question "<<q[i].getID()<<" to user "<<q[i].getReplier()<<"\tQuestion : "<<q[i].getQuestion()<<endl;
                cout<<"Answer : "<< q[i].getAns()<<endl;
            }
            else if(q[i].getAns() != " Not Answered yet! " && q[i].isAnonymous() =='n')
            {
                cout<< "Question "<<q[i].getID()<<" from user "<<q[i].getAsker()<<" to user "<<q[i].getReplier()<<"\tQuestion : "<<q[i].getQuestion()<<endl;
                cout<<"Answer : "<< q[i].getAns()<<endl;

            }
        }
    }






};

int user::users_num = 0;
int question::lastQ=0;
int user::getNum()
{
    return users_num;
}
int question::getLastQ()
{
    return lastQ;
}
void question::deleteLastQ()
{
    --lastQ;
}



void loadQuestions(vector<question> &q)
{
    fstream read;
    int id=0;
    int Asker = 0;
    int Replier = 0;
    char anonymous ;
    string Q = " ";
    string A = " ";

    read.open( "questions.txt" );
    if(read.fail())
        cout<< "failed to open file !"<<endl;
    while( !read.eof() )
    {
        read >> anonymous;
        read >> id ;
        read >> Asker;
        read >> Replier;
        // read.ignore();
        getline(read,Q);
        getline(read,Q);
        getline(read,A);
        question newQuestion = question(  Asker, Replier, Q, anonymous);
        newQuestion.updateAnswer(A);
        q.push_back(newQuestion);

    }
}


void loadUsers(vector<user> &users)
{
    fstream read;
    string name;
    string pass;
    int id = 0;

    read.open( "users.txt" );
    if(read.fail())
        cout<< "failed to open file !"<<endl;
    while( !read.eof() )
    {
        read >> id >> name >> pass;
        user newUser = user(id,name, pass);
        users.push_back(newUser);

    }


}






int Search  (int id, string pass, vector<user> &users)
{

    for(int i=0; i<user::getNum(); i++ )
    {
        if(users[i].getID() == id && users[i].getpass() == pass)
            return i ;
    }

    return -1;
}


/*bool verify(int id, int pass, vector<user> users)
{

}*/
int main()
{
    int choice=0;
    int id=0;
    int idx=0;
    string name;
    string pass;
    vector<user> users;
    vector<question> questions;
    bool flag = true;


    fstream readUsers;
    readUsers.open( "users.txt" );
    if(readUsers.fail())
    {
        ofstream readUsers;
        readUsers.open( "users.txt" );
        readUsers.close();
    }

    fstream readQuestions;
    readQuestions.open( "questions.txt" );
    if(readQuestions.fail())
    {
        ofstream readQuestions;
        readQuestions.open( "questions.txt" );
        readQuestions.close();
    }


    loadUsers(users);
    loadQuestions(questions);
    while(true)
    {
        cout << "1- sign up" << endl;
        cout << "2- login" << endl;
        cout << "Enter a choice" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
        {

            cout << endl << "Enter your name: ";
            cin >> name;
            cout << endl << "Enter your password: ";
            cin >> pass;

            user newUser = user(name, pass);
            users.push_back(newUser);
            cout << endl << "Your ID: "<<newUser.getID()<<endl;
            newUser.addUser();
            //users.insert(it, newUser); // create iterator then pass it to create user and add it to users vector
            // users.insert (user::getNum()-1, newUser);
            //addUser();
        }
        break;
        case 2:
        {
            flag =true;
            cout << endl << "Enter your ID: ";
            cin >> id;
            cout << endl << "Enter your password: ";
            cin >> pass;
            idx=Search(id, pass, users);
            if(idx!=-1)
            {
                cout<<" Welcome "<<users[idx].getname()<<endl<<endl;
                user u=users[idx];

                while(flag) // first flag
                {
                    cout << "1- Show questions to me" << endl;
                    cout << "2- Show questions from me " << endl;
                    cout << "3- Answer a question " << endl;
                    cout << "4- Delete a question " << endl;
                    cout << "5- Ask a question " << endl;
                    cout << "6- Show all users " << endl;
                    cout << "7- Feed " << endl;
                    cout << "8- log out " << endl;
                    cout << "Enter a choice" << endl;
                    cin >> choice;
                    switch(choice)
                    {
                    case 1:
                    {
                        u.QuestionsToMe(questions);
                    }
                    break;
                    case 2:
                    {
                        u.MyQuestions(questions);
                    }
                    break;
                    case 3:
                    {
                        cout << "Enter the question ID you wanna answer: ";
                        cin>>id;
                        u.Answer(id,questions);
                    }
                    break;
                    case 4:
                    {
                        cout << "Enter the question ID you wanna delete: ";
                        cin >> id;
                        u.Delete(id, questions);
                    }
                    break;
                    case 5:
                    {
                        cout << "Enter the user ID you wanna ask: ";
                        cin >> id;
                        u.Ask(id, questions);

                    }
                    break;
                    case 6:
                    {
                        u.Users(users);
                    }
                    break;
                    case 7:
                    {
                        u.feed(questions);
                    }
                    break;
                    case 8:
                    {
                        flag = false;
                    }
                    break;
                    default:
                    {
                        cout<< "enter valid choice"<<endl;
                    }
                    break;
                    }

                }
            }
            else
                cout<<"WRONG pass OR id ! "<<endl;



        }
        break;
        default:
        {
            cout<<" Enter valid option"<<endl;
        }
        break;
        }
    }
    return 0;
}
