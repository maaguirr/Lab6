#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string> 
#include <sstream>
using namespace std;
int counter = 0;
class List{
    
private:
    
    typedef struct student{
    int ID;
    string firstName;
    string lastName;
    float GPA;
    struct student *next;
    }*Student;
    
    Student head;
    Student curr;
    Student temp;
    
    
public:

    List(){
        head = NULL;
        curr = NULL;
        temp = NULL;
    }
    void addStudent(int ID, string firstName, string lastName, float GPA){
        Student s = new student;
        
        s->next = NULL;
        s->ID = ID;
        s->firstName = firstName;
        s->lastName = lastName;
        s->GPA = GPA;
        
        if(head != NULL){
            curr = head;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = s;
        }
        else{
            head = s;
        }
        counter++;
    }
    void deleteNode(int delID){
        Student delStudent = NULL;
        temp = head;
        curr = head;
        while(curr != NULL && curr->ID != delID){
            temp = curr;
            curr = curr->next;
        }
        if(curr == NULL){
            cout <<"Student ID: " << delID << " not found" << endl;
            delete delStudent;
        }
        else{
            delStudent = curr;
            curr = curr->next;
            temp->next = curr;
            if (delStudent == head){
                head = head->next;
                temp = NULL;
            }
            delete delStudent;
            cout << "The ID " << delID << " was deleted." << endl;
        }
        counter--;
        
        
    }
    
    void updateNode(int upID){
        
    Student curr = head;

       //if list is empty
       if(head == NULL) {
          return;
       }

       //navigate through list
       while(curr->ID != upID) {
        
          //if it is last student
          if(curr->next == NULL) {
             return;
          } else {
             //go to next link
             curr = curr->next;
          }
       }      
        cout << "enter new ID: " << endl;
        cin >> curr->ID;
        cout << "enter new first name: " << endl;
        cin >> curr->firstName;
        cout << "enter new last name: " << endl;
        cin >> curr->lastName;
        cout << "enter new GPA: " << endl;
        cin >> curr->GPA;
        
       return;
}

    void sort(){
        int i, j, k, tempID;
        float tempGPA;
        string tempFname, tempLname;
        Student curr;
        Student next;
	
        int size = counter;
        k = size ;
	
        for ( i = 0 ; i < size - 1 ; i++, k-- ) {
            curr = head;
            next = head->next;
		
        for ( j = 1 ; j < k ; j++ ) {   

            if ( curr->GPA > next->GPA ) {
                tempGPA = curr->GPA;
                curr->GPA = next->GPA;
                next->GPA = tempGPA;

                tempID = curr->ID;
                curr->ID = next->ID;
                next->ID = tempID;
            
                tempFname = curr->firstName;
                curr->firstName = next->firstName;
                next->firstName = tempFname;
                
                tempLname = curr->lastName;
                curr->lastName = next->lastName;
                next->lastName = tempLname;
            
         }
			
         curr = curr->next;
         next = next->next;
        }
    }   
    }
    
    void writeToFile(){
        ofstream out("student_info3.txt");
        curr = head;
        while(curr != NULL){
            out << curr->ID << " " << curr->firstName << " " << curr->lastName << " " << curr->GPA << endl;
            curr = curr->next;
        }
        out.close();
    }
    
    void printList(){
        curr = head;
        while(curr != NULL){
            cout << curr->ID << " " << curr->firstName << " " << curr->lastName << " " << curr->GPA << endl;
            curr = curr->next;
        }
    }
    
     ~List(){
        printf("\n");
        cout << "Destroyed List" << endl;
    }
};

void menu(void) {
	printf("Menu:\n");
	printf("1) List All Students\n");
	printf("2) Add a Student\n");
	printf("3) Remove a Student\n");
	printf("4) Update a Student\n");
    printf("5) Write students to file\n");
	printf("6) quit\n");
    printf("\n");
}


int main(){
    
    List Students;
    
    //reading students in from file and adding to list class
    int number;
    float number2;
    string line, nothing, nothing2, fname, lname;
    ifstream in("student_info.txt");
    if(!in.is_open()){
        cout << "Error opening file" << ends;
    }
    getline(in, nothing);// skip first line
    int numLines = 0;
    string unused;
    while (getline(in, unused)){
        ++numLines;
    }
    in.close();
    ifstream ifi("student_info.txt");
    getline(ifi, nothing2);// skip first line
    for (int i = 0; i < numLines; i++){
        getline(ifi, line);
        istringstream iss1(line);
        iss1 >> number;
        iss1 >> fname; 
        iss1 >> lname;
        iss1 >> number2; 
        Students.addStudent(number,fname,lname,number2);
    }
    ifi.close();
    int choice;
    bool run = 1;
    while(run){
        int dID;
        int uSt;
        menu();
        cout << "please enter menu choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                //sort();
                //reverse(&head);
                Students.sort();
                Students.printList();
                break;
            case 2:;
                cout << "enter student ID: " << endl;
                cin >> number;
                cout << "enter first name: " << endl;
                cin >> fname;
                cout << "enter last name: " << endl;
                cin >> lname;
                cout << "enter student gpa: "<< endl;
                cin >> number2;
        
                Students.addStudent(number,fname,lname,number2);
                break;
            case 3:
                cout << "enter student ID to delete: " << endl;
                cin >> dID;
                Students.deleteNode(dID);
                break;
            case 4:
                cout << "enter student ID to update: " << endl;
                cin >> uSt;
                Students.updateNode(uSt);
                break;
            case 5:
                Students.writeToFile();
                cout << "students written to file\n" << endl;
                break;
            case 6:
                List();
                run = 0;
                exit(0);
            default:
                cout << "please enter valid choice" << endl;
                break;
        }
    }
    
    return 0;
}