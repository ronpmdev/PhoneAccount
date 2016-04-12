//Programmer : Ronald P Mathews
//Email      : ronpmdev@gmail.com
//Date       : 12/04/2016 (DD/MM/YYYY)
//Timestamp  : 1460455650
//License    : The MIT License (MIT)

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

struct detail{
	int id;
	char name[30];
	long int pnum;
};
struct bill{
	int billid;
	int units;
	float per_u;
	float bill_amt;
	struct{
		short dd;
		short mm;
		short yy;
	}bd;
};

class phone{
	private:
		detail userd;
		bill ubill;
		char pssd[30], buffer[33];
		string line;
		int i;
		short ext;
	public:
		void spacing(short spc){		//Spacing for text in screen
			for(short i=0;i<spc;i++)
				cout<<" ";
		}
		
		void hr(int len){
			for(short i=0;i<len;i++)
				cout<<"_";			
		}
		
		void gohome(){
			cout<<"\n\nInput '1' to go home : ";
			cin>>ext;
			if(ext==1)
				home();
			else
				exit(0);
		}
			
		void login(){					//Login to the system
			cout<<"Enter the password : ";
			fflush(stdin);
			gets(pssd);
			if(!strcmp(pssd,"admin")){
				home();
			}
			else{
				cout<<"\aLogin failed!";
			}
		}
		
		void home(){					//Main screen
			system("CLS");
			spacing(28);
			cout<<"Phone account manager\n\n\n\n";
			cout<<"1. Add new user\n";
			cout<<"2. Create bill\n";
			cout<<"3. Search using number\n";
			cout<<"4. Delete user\n";
			cout<<"5. Exit";
			cout<<"\n\nEnter an input : ";
			short opt;
			cin>>opt;
			if(opt==1){
				addUser();
			}
			else if(opt==2){
				createBill();
			}
			else if(opt==3){
				searchNum();
			}
			else if(opt==4){
				deleteUser();
			}
			else if(opt==5){
				exit(0);
			}
		}
		
		void addUser(){		//Add details of new customer
			cout<<"Enter the name of customer : ";
			fflush(stdin);
			gets(userd.name);
			cout<<"Enter the phone number : ";
			cin>>userd.pnum;
			itoa (userd.pnum,buffer,10);
			
			ifstream userfile (buffer);
			if (userfile.is_open())
			{
				cout<<"Cannot create. Number already exists in another file\n";
			    userfile.close();
			    Sleep(1000);
			    home();
			}
			else{
				ofstream userfile;
				char name[10];
				strcpy(name,userd.name);
	  			userfile.open (buffer);
	 			userfile <<userd.name<<"\n"<<userd.pnum;
	 			userfile.close();
	 			cout<<"\n\n\n";
	 			spacing(35);
	 			cout<<"Saving...";
	 			Sleep(500);
	 			home();
 			}
		}
		
		void createBill(){
			system("CLS");
			cout<<"Enter phone number of customer : ";
			cin>>userd.pnum;
			itoa (userd.pnum,buffer,10);

  			ifstream userfile(buffer);
  			if (userfile.is_open()){
   				 userfile.close();
  			}
			else{
			  cout << "\a\n\nUser missing"; 
			  Sleep(1000);
			  home();
		    }
		    cout<<"Enter the call units : ";
		    cin>>ubill.units;
		    cout<<"Enter rate per unit : ";
		    cin>>ubill.per_u;
		    cout<<"Enter bill date data :";
			    cout<<"\n\tEnter the date : ";
			    cin>>ubill.bd.dd;
			    cout<<"\tEnter the month : ";
			    cin>>ubill.bd.mm;
			    cout<<"\tEnter the year : ";
			    cin>>ubill.bd.yy;
			ubill.bill_amt=ubill.units*ubill.per_u;
			ubill.billid=rand();
			cout<<"\n\n";
			spacing(32);
			cout<<"Generating Bill...";
			Sleep(1000);
			system("CLS");
			cout<<"\n\n";
			spacing(35);
			cout<<"Phone Bill\n";	
			hr(80);
			cout<<"\n\nBill id : "<<ubill.billid;
			ifstream ubilldata(buffer);
  			if (ubilldata.is_open()){
  				i=0;
   				 while ( getline (ubilldata,line) ){ 
   				 	if(i==0){
   				 		cout<<"\nName             : "<<line;
   				 		i++;
   				 	}
   				 	else if(i==1){
   				 		cout<<"\nPhone number     : "<<line;
   				 		i++;
   				 	}
   				 	else{
   				 		break;
   				 	}
    			 }
   				 ubilldata.close();
  			}
  			                  
			cout<<"\nBill date        : "<<ubill.bd.dd<<"/"<<ubill.bd.mm<<"/"<<ubill.bd.yy;
			cout<<"\nTotal call units : "<<ubill.units;
			cout<<"\nCharge per unit  : "<<ubill.per_u;
			cout<<"\nTotal charges    : "<<ubill.bill_amt;
			cout<<"\n\n";
			hr(80);
			gohome();
		}
		
		
		void searchNum(){
			system("CLS");
			cout<<"Enter the phone number to search for : ";
			cin>>userd.pnum;
			itoa (userd.pnum,buffer,10);
			ifstream userfile(buffer);
  			if (userfile.is_open()){
  				cout<<"\nUser found. Details shown below\n";
  				hr(31);
  				cout<<"\n\n";
  				while ( getline (userfile,line) ){ 
  					cout<<line<<endl;
  				}
   				userfile.close();
   				gohome();
  			}
			else{
				cout << "\a\n\nUser not found!"; 
				gohome();
		    }
		}
		
		void deleteUser(){
			system("CLS");
			cout<<"Enter the phone number of account you want to delete : ";
			cin>>userd.pnum;
			cout<<"\a\nInput '9' to delete or '5' to abort "<<userd.pnum<<" : ";
			cin>>ext;
			if(ext==9){
				itoa (userd.pnum,buffer,10);
				if( remove(buffer) != 0 ){
  					cout<<"\n\aError removing user!\n";
  					gohome();
  				}
 				 else{
  					  cout<<"\nSuccesfully deleted";
  					  gohome();
  				}
			}
			else{
				cout<<"\n\nDeletion aborted.\n\n";
				gohome();
			}
		}
		
};

int main() {
	phone ph;
	ph.login();
	return 0;
}
