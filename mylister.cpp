#include <iostream>
#include <string>
#include <fstream>
using namespace std;
enum retstat { failure, success };

struct Task {
  int priority;
  string name;
  string due_date;
  string time;
};

struct Node {
    Task item;
    Node* next;
};

int extractYear(string date) {
  int year=0;
  for(int i=0;i<4;i++) year=year*10+(date[i]-'0');
  return year;
}
int extractMonth(string date) {
  int month=0;
  for(int i=5;i<=6;i++) month=month*10+(date[i]-'0');
  return month;
}
int extractDay(string date) {
  int day=0;
  for(int i=8;i<10;i++) day=day*10+(date[i]-'0');
  return day;
}
int extractHour(string time) {
  int hour=0;
  for(int i=0;i<2;i++) hour=hour*10+(time[i]-'0');
  return hour;
}
int extractMinute(string time) {
  int minute=0;
  for(int i=3;i<5;i++) minute=minute*10+(time[i]-'0');
  return minute;
}
retstat addItem(Node** head) {
  int pr=1;
  string name, date, time;
  int year,month,day,hour,minute;
  Node *temp=*head;
  Node *prev=nullptr;
  cout << "Enter the name of task: ";
  getline(std::cin, name);

  cout<< "Enter the due date (format: YYYY-MM-DD): ";
  getline(std::cin, date);

  cout<<"Enter the due time (format: HH:MM): ";
  getline(cin,time);
  
  year=extractYear(date);
  month=extractMonth(date);
  day=extractDay(date);
  hour=extractHour(time);
  minute=extractMinute(time);

  Node *newNode=new Node();
  newNode->item.name=name;
  newNode->item.due_date=date;
  newNode->item.time=time;
  if(temp==nullptr) {
    *head=newNode;
    newNode->next=temp;
  }
  else {
    while(temp!=nullptr) {
      if(year<extractYear(temp->item.due_date)) break;
      else if(year==extractYear(temp->item.due_date)){
        if(month<extractMonth(temp->item.due_date)) break;
        else if(month==extractMonth(temp->item.due_date)){
          if(day<extractDay(temp->item.due_date)) break;
          else if(day==extractDay(temp->item.due_date)){
            if(hour<extractHour(temp->item.time)) break;
            else if(hour==extractHour(temp->item.time)){
              if(minute<extractMinute(temp->item.time)) break;
            }
          }
        }
      }
      prev=temp;
      temp=temp->next;
    }
    if(prev!=nullptr) prev->next=newNode;
    else *head=newNode;
    newNode->next=temp;
  }
  temp=*head;
  while(temp!=nullptr) {
    temp->item.priority=pr;
    pr++;
    temp=temp->next;
  }
  return success;
}

retstat removeItem(Node **head, int priority) {
  Node *temp=*head,*prev=nullptr;
  int pr=1;
  while(temp!=NULL) {
    if(temp->item.priority==priority) break;
    prev=temp;
    temp=temp->next;
  }
  if(temp==NULL) return failure;
  if(prev!=nullptr) prev->next=temp->next;
  else *head=temp->next;
  delete temp;
  temp=*head;
  while(temp!=nullptr) {
    temp->item.priority=pr;
    pr++;
    temp=temp->next;
  }
  return success;
}
retstat updateItem(Node **head, int priority) {
  string nname, ntime, ndate;
  Node *temp=*head;
  int pr=1;
  while(temp!=nullptr) {
    if(temp->item.priority==priority) break;
    temp=temp->next;
  }
  if(temp==nullptr) return failure;

  cout<<"What change do you want to make?\n";
  cout<<"1. Change the name of task\n";
  cout<<"2. Change the due date\n";
  cout<<"3. Change the due time\n";
  int opt; cin>>opt;
  Node *newNode=new Node();
  switch(opt) {
    case 1: 
      cout<<"Enter a new name: "; cin>>nname;
      newNode->item.name=nname;
      newNode->item.due_date=temp->item.due_date;
      newNode->item.time=temp->item.time;
      break;
    case 2:
      cout<<"Enter a new due date: "; cin>>ndate;
      newNode->item.name=temp->item.name;
      newNode->item.due_date=ndate;
      newNode->item.time=temp->item.time;
      break;
    case 3:
      cout<<"Enter a new due time: "; cin>>ntime;
      newNode->item.name=temp->item.name;
      newNode->item.due_date=temp->item.due_date;
      newNode->item.time=ntime;
      break;
    default:
    cout<<"No change applied!\n";
  }
  int year=extractYear(newNode->item.due_date);
  int month=extractMonth(newNode->item.due_date);
  int day=extractDay(newNode->item.due_date);
  int hour=extractHour(newNode->item.time);
  int minute=extractMinute(newNode->item.time);
  retstat code=removeItem(head,priority);
  if(code==failure) return failure;
  
  Node *temp2=*head;
  Node *prev2=nullptr;
    while(temp2!=nullptr) {
      if(year<extractYear(temp2->item.due_date)) break;
      else if(year==extractYear(temp2->item.due_date)){
        if(month<extractMonth(temp2->item.due_date)) break;
        else if(month==extractMonth(temp2->item.due_date)){
          if(day<extractDay(temp2->item.due_date)) break;
          else if(day==extractDay(temp2->item.due_date)){
            if(hour<extractHour(temp2->item.time)) break;
            else if(hour==extractHour(temp2->item.time)){
              if(minute<extractMinute(temp2->item.time)) break;
            }
          }
        }
      }
      prev2=temp2;
      temp2=temp2->next;
    }
    if(prev2!=nullptr) prev2->next=newNode;
    else *head=newNode;
    newNode->next=temp2;
    temp2=*head;
   while(temp2!=nullptr) {
    temp2->item.priority=pr;
    pr++;
    temp2=temp2->next;
  }

  return success;
}

void viewList(Node* head) {
    Node* temp = head;
    if (temp == nullptr) {
        std::cout << "Nothing in the list\n";
    } else {
        std::cout << "Priority Number Name of Task";
        for(int i=1;i<=100-12;i++) cout<<" ";
        std::cout<<"Due Date    "<<"Due Time"<<endl;
        while (temp != nullptr) {
            std::cout << temp->item.priority;
            std::cout<<"              ";
            std::cout<<temp->item.name;
            for(int i=1;i<=100-temp->item.name.size();i++) std::cout<<" ";
            std::cout<<temp->item.due_date<<"   ";
            cout<<temp->item.time<<endl;
            temp = temp->next;
        }
    }
}

void writeRemainingTasksToFile(Node* head) {
    std::ofstream outFile("remaining_tasks.txt"); // Open file in write mode
    if (!outFile) {
        std::cerr << "Error: Unable to open file 'remaining_tasks.txt' for writing.\n";
        return;
    }

    Node* temp = head;
    if (temp == nullptr) {
        outFile << "No remaining tasks.\n";
    } else {
        outFile << "Priority Number, Name of Task, Due Date, Due Time\n";
        while (temp != nullptr) {
            outFile << temp->item.priority << ", " 
                    << temp->item.name << ", " 
                    << temp->item.due_date << ", " 
                    << temp->item.time << "\n";
            temp = temp->next;
        }
    }
}

void freeList(Node* head) {
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        prev = temp;
        temp = temp->next;
        delete prev;  
    }
}

int main() {
    Node* head = nullptr;
    retstat code;
    int pr;

    std::cout << "========Welcome to My Lister========\n";
    std::cout << "Please use this to never miss a deadline!\n";

    int opt = 1;
    while (opt != 0) {
        std::cout << "Select any one of these:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. See list\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> opt;
        std::cin.ignore();  

        switch (opt) {
            case 1:
                code = addItem(&head);
                if (code == failure)
                    std::cout << "The priority order exists!!!\n";
                else
                    std::cout << "Successfully added the item!!\n";
                break;
            case 2:
                cout<<"Enter the priority number of the task you want to remove: ";
                cin>>pr;
                code=removeItem(&head,pr);
                if(code==failure) std::cout << "The given priority does not exist!!!!\n";   
                else cout<<"Successfully removed the item!!!!\n";
                break;
            case 3:
                cout<<"Enter the priority number of the task to be updated: ";
                cin>>pr;
                code=updateItem(&head,pr);
                if(code==failure) cout<<"Priority number not found!!\n";
                else cout<<"Successfully updated item!!\n";
                break;
            case 4:
                viewList(head);
                break;
            case 0:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter values between 0 and 4 inclusive.\n";
        }
    }
    if(head!=nullptr) writeRemainingTasksToFile(head);
    freeList(head);  
    return 0;
}
