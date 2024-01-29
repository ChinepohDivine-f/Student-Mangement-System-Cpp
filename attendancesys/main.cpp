#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>


using namespace std;

class connection{
public:
	const char* hostname    = "localhost";
	const char* username    = "root";
	const char* password    = "";
	const char* database    = "attendancesys";
	unsigned int port       = 3306;
	const char* unixsocket  = NULL;
	unsigned long clientflag = 0;
	//int qstate = -1;
	stringstream ss;

	MYSQL* connectdatabase(){
		MYSQL* conn;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
		if(conn){
			cout<<"connected to database . . ."<<endl;
			return conn;
		}
		else{
			cout<<"Failed to connect to database . . .!"<<endl;
			return conn;
		}
	}
};

class student:public connection{
public:
	string matricule;
	string s_fname;
	string s_lname;
	string fullname;
	string att;


        MYSQL_ROW row;
        MYSQL_RES* res;
//methods
    boolean studentLogin(MYSQL * conn){
		cout << "\tAUTHENTIFICATION"<<endl;
		cout << "\t Student first Name: " ;
			cin >> s_fname;
		cout << "\t Student last Name: " ;
			cin >> s_lname;
			fullname = s_fname + " " + s_lname;
			cout << "\tStudent name = "<< fullname << endl;
		cout << "\t Student Matricule: ";
			cin >> matricule;
        int qstate = 0;
	

        if (conn) {
        string query = "SELECT * FROM student WHERE studentName = '"+fullname+"' and studentMatricule = '"+matricule+"' ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
            if (!qstate) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                if (row != NULL) {
                    cout << "User found!" << endl;
                    return 0;
                }
                else {
                    cout << "User not found!" << endl;
                    return 1;
                }
            }
        }

		//return 0;
    }
    void viewAttendance(MYSQL * conn){
    	system("cls");
		cout << "Your attendance"<<endl;

        MYSQL_ROW row;
        MYSQL_RES* res;
        cout << "\tMatricule\tName\t\tattendance"<<endl;
        if(conn){
            ss << "SELECT * FROM student WHERE studentName = '"+fullname+"'";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);
            cout << qstate;
            //int qstate = mysql_query(conn, "SELECT * FROM student WHERE studentName = '"+fullname+"'");
            if(qstate >= 0){
                res = mysql_store_result(conn);
                int count = mysql_num_fields(res);
                while(row = mysql_fetch_row(res)){
                    for(int i=0;i<count;i++){
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;

                }
            }
        }
    }
};

class admin:public student,public connection{
private:
	int a_id;
	string a_name;
	string password;
public:
	int adminLogin(MYSQL * conn){
		cout << "\tAUTHENTIFICATION"<<endl;
		cout << "\t Admin Name:\t";
			cin >> a_name;
		cout << "\t Admin Password:";
			cin >> password;

        MYSQL_ROW row;
        MYSQL_RES* res;

        int qstate = 0;
        stringstream  ss;
        string a,b;
        a = a_name;
        b = password;
        cout << qstate;

        if (conn) {
        string query = "SELECT * FROM admin WHERE adminName = '"+a+"' and adminPass = '"+b+"' ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
            if (!qstate) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                if (row != NULL) {
                    cout << "User found!" << endl;
                    return 0;
                }
                else {
                    cout << "User not found!" << endl;
                    return 1;
                }
            }
        }
    }

	void addStudent(MYSQL* conn){
		system("cls");
		cout << "Add Student" << endl;
		//if(getStudent()){
		cout << "\t Student first Name: " ;
			cin >> s_fname;
		cout << "\t Student last Name: " ;
			cin >> s_lname;
			fullname = s_fname + " " + s_lname;
			cout << "\tStudent name = "<< fullname << endl;
		cout << "\t Student Matricule: ";
			cin >> matricule;
        int qstate = 0;
        stringstream  ss;
        fullname;
        matricule;
        att = "None";
        ss << "INSERT INTO student (studentMatricule, studentName, StudentAttendance) VALUES ('"+matricule+"', '"+fullname+"', '"+att+"')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        cout << qstate;
        if(qstate == 0){
            cout<<"Student added successfully.....! \n";
        }
        else{
            cout<<"Failed to add Student.......  \n";
        }


		//}
	}
	void markStudentPresent(MYSQL * conn){
		system("cls");
		cout << "Mark Student Present" << endl;
		cout << "\t Student Matricule: "; //get student matrucule
			cin >> matricule;
         int qstate = 0, temp;
        stringstream  ss;
        cout << "Was student present(1) or absent(0)? ";
        cin >> temp;

        if (temp == 1){att = "present";} //conditional statement to mark present or absent
        else if (temp == 0){att = "absent";}
        else {return;}

        ss << "UPDATE student SET StudentAttendance = '"+att+"' WHERE  studentMatricule = '"+matricule+"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        cout << qstate;
        if(qstate == 0){
            cout<<"Student " << matricule <<  " marked "<< att <<" successfully.....! \n";
        }
        else{
            cout<<"Failed to mark Student.......  \n";
        }
	}
	void deleteStudent(MYSQL* conn){
		system("cls");
		cout << "Delete Student" << endl;
        stringstream ss;
        cout<<"Enter Student matricule No: ";
        cin>>matricule;

        ss  << "DELETE FROM student WHERE studentMatricule = '"+matricule+"'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        cout << qstate;
        if(qstate == 0){
            cout<<"~~~~~Student record deleted...~~~ \n";
        }
        else{
            cout<<"~~~~~failed to delete...~~~ \n";
        }
        cout << endl; //creating space
	}
	void viewStudentList(MYSQL* conn){ //display working perfectly
		system("cls");
		cout << "Display Student List" << endl;
		//code to display student table
		MYSQL_ROW row;
        MYSQL_RES* res;
        cout << "\tMatricule\tName\t\tattendance"<<endl;
        if(conn){
            int qstate = mysql_query(conn, "SELECT * FROM student");
            cout << qstate;
            if(qstate >= 0){
                res = mysql_store_result(conn);
                int count = mysql_num_fields(res);
                while(row = mysql_fetch_row(res)){
                    for(int i=0;i<count;i++){
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;
                }
            }
        }
        else{
            cout<<"Failed to fetch ";
        }
	}
};

class studentSignIn:public admin{
public:
    signIn(){
        cout << "STUDENT SIGNIN PAGE" <<endl;
        //function overloading of the addstudent fucntion in admin class
    }
};

class screen{
public:
	 void clearScreen(){
		try{
			system("cls");
			//throw(505);
		}catch(...){
			system("clear");
		}
	}
	 void homeScreen(){
		cout << "Student Management System"<<endl;
		cout << "Login option" <<endl;
		cout << "\t1. admin" <<endl;
		cout << "\t2. student" <<endl;
		cout << "\t3. student SignIn" <<endl;
		cout << "\t10. exit" <<endl;
	}
	void green(){
        system("color a");
	}
	void color(){
        system("color ");
	}
};



int main(int argc, char *argv[]){
    op: // reference point
	MYSQL* conn;
	connection c;
	studentSignIn sign;
	conn = c.connectdatabase();
	cout << endl;
	admin adm; // admin object
	student stu; // student object
	screen scr; // screen object
	scr.green();

	while (conn){
		scr.clearScreen();
		scr.homeScreen();

		int UserInput, am;
		cout << "\n\t-> ";
		cin >> UserInput;
		switch (UserInput){
		case 1:
			scr.clearScreen();
			cout << "-------ADMIN LOGIN--------" <<endl;
			am = adm.adminLogin(conn);
			if (am == 0){
				while (true){
					int choice;
					cout << "What do you wish to do?"<<endl;
					cout << "\t1. Add a student" << endl;
					cout << "\t2. Mark a student Present" << endl;
					cout << "\t3. Delete student" << endl;
					cout << "\t4. view Student list" << endl;
					cout << "\t < - back to Home [press 10]" << endl;
					cout << "\t-> ";
					cin >> choice;
					if (choice == 10){
						goto op;
					}
					switch (choice){
					case 1:
						adm.addStudent(conn);
						break;
					case 2:
					    cout << "mark student present"<<endl;
						adm.markStudentPresent(conn);
						break;
					case 3:
						adm.deleteStudent(conn);
						break;
					case 4:
						adm.viewStudentList(conn);
						break;
					default:
						system("cls");
						cout << "Try choosing from the given options" <<endl;
					}
				}

			}
			else{
				cout << "\nUser Not Found" << endl;
			}
			system("pause");

			break;
		case 2:
			int sm;
			scr.clearScreen();
			cout << "STUDENT LOGIN" << endl;
			sm = stu.studentLogin(conn);
			if (sm == 0){
				while (true){
					int choice;
					cout << "What do you wish to do?"<<endl;
					cout << "\t1. Attendance" << endl;
					cout << "\t < - back to Home [press 10]" << endl;
					cout << "\t-> ";
					cin >> choice;
					if (choice == 10){
						goto op;
					}
					switch (choice){
					case 1:
						stu.viewAttendance(conn);
						break;
					default:
						system("cls");
						cout << "Try choosing from the given options" <<endl;
					}
				}

			}
			else{
				cout << "User Not Found" << endl;
			}

			break;
        case 3:
            sign.signIn();
            //sign.addStudent();
            adm.addStudent(conn);
            system("pause");
            break;
		case 10:
			scr.clearScreen();
			scr.color();
			cout << "BYE ....."<<endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "-----------INVALID OPTION-----------" << endl;

		}
	}
	return 0;
}















/*
using namespace std;

const char* hostname    = "localhost";
const char* username    = "root";
const char* password    = "";
const char* database    = "cppdb";
unsigned int port       = 3306;
const char* unixsocket  = NULL;
unsigned long clientflag = 0;

MYSQL* connectdatabase(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if(conn){
        cout<<"connected to database "<<endl;
        return conn;
    }
    else{
        cout<<"Failed to connect to database"<<endl;
        return conn;
    }
}

insertion(MYSQL* conn){
    int qstate = 0;
    stringstream  ss;
    string usernamedb,emaildb,passworddb;
    cout<<"enter username "<<endl;
    cin>>usernamedb;
    cout<<"Enter email id "<<endl;
    cin>>emaildb;
    cout<<"Enter password "<<endl;
    cin>>passworddb;
    ss << "INSERT INTO users (username, email, password) VALUES ('"+usernamedb+"', '"+emaildb+"', '"+passworddb+"')";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout<<"Record inserted...~~~ \n";
    }
    else{
        cout<<"failed to insert...~~~ \n";
    }

}

display(MYSQL* conn){
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM users");
        if(!qstate){
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row = mysql_fetch_row(res)){
                    for(int i=0;i<count;i++){
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;

            }
        }

    }
    else{
        cout<<"Failed to fetch ";


    }




}
deletedb(MYSQL* conn)
{
    string username;
    stringstream ss;
    cout<<"Enter username of record ";
    cin>>username;

    //ss  << "DELETE FROM users WHERE username = '"+username+"' ";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout<<"~~~~~Record deleted...~~~ \n";
    }
    else{
        cout<<"~~~~~failed to delete...~~~ \n";
    }


}

//"SELECT * FROM student WHERE name = '"+name+'" and password = '"+password+"'";
    "select * from Users where name=? and password=? "


    UPDATE Customers
SET ContactName = 'Alfred Schmidt', City = 'Frankfurt'
WHERE CustomerID = 1;

        "UPDATE student SET StudentAttedance = '"+att+"' WHERE  studentMatricule = '"+matricule+"'

*/
