#include <stdio.h>
#include<iostream>
#include<fstream>
//#include<cctype> //tocheck if int is int, char is char
//#include<iomanip>
#include <cstdlib> //exit etc functions
//#include <ctime>
#include <string>
#include <conio.h> //system functions color
//#include <string.h>
//#include <time.h>
#include<cstring>//strcpy

using namespace std;

class Person
{   protected:
    char Name[50],Gender[10];
    int Age,Date,Month,Year;
    long int PhoneNum;
    int ZipCode,PersonID;
    char City[50],Country[50],State[50],blood_g[5];
public:
    virtual void getInfo() = 0;
    void PersonInfo()
    {
        cout<<"Enter Name :";
        cin.clear();
        cin.ignore();
        cin.getline(Name,50);
        cout<<"Enter Gender :";
        cin>>Gender;
        cout<<"Enter Age :";
        cin>>Age;
        cout<<"Enter Address :";
        cin>>Country;
        cout<<"Enter Blood group:";
        cin>>blood_g;
    }
    void PersonInfo(char n[], char g[],int a,char c[],char bg[])
    {
        strcpy(Name,n);
        strcpy(Gender,g);
        Age = a;
        strcpy(Country,c);
        strcpy(blood_g,bg);

    }

    void Display_info()
    {
        cout<<"Name: "<<Name<<endl;
        cout<<"Gender: "<<Gender<<endl;
        cout<<"Age: "<<Age<<endl;
        cout<<"Address: "<<this->Country<<endl;
        cout<<"Blood Group:"<<blood_g<<endl;
    }
};

class Staff:public Person
           {
           int salary;
           char time_from[30],time_to[30];

    public:
            void getInfo(){
                cout << "Staff name: "<< Name <<endl<<"Gender: "<<Gender<<endl<<"Salary: "<< salary <<endl<< "Working hours"<<time_from<<":"<<time_to;
            }
          void staff_info()
          {
              PersonInfo();
              cout<<"Enter salary:";cin>>salary;
              cout<<"Enter Duty time:"; cout<<"From:";cin>>time_from;cout<<"To:";cin>>time_to;
          }

           void show_staff()
           {
                cout<<"\nSalary: "<<salary;
                cout<<"\nDuty Time: "<<time_from<<"--"<<time_to<<endl;
                Display_info();
           }
};


class patient: public Person
{
int reg_no;
char occupation[30];
char date_admit[30];
char date_discharge[30];
int bill,total;

public:
    void getInfo(){
        cout << "Staff name: "<< Name <<endl<<"Gender: "<<Gender<<endl<<"Date of Admission "<< date_admit <<endl<< "Date of Discharge"<<date_discharge<<endl<<"Bill: "<<bill;
    }
    char medicine[100];
void patient_bill();
void getdata(); //function to accept data from user
void showdata(); //function to show data on screen
int retidno();
void modify_medicine(int n);
    void write_patient(); //write the record in file
    void display_all(); //read all records from file
    void display_p(int n); //accept reg_no and read record from file
    void modify_patient(int n); //accept reg_no and update record of file
    void delete_patient(int n); //accept reg_no and delete selected records from file
};


void patient::patient_bill()  //using scope resolution operator to define function outside class
{
    system("CLS");
cout << "********************************************************************************";
cout << "\n\n\t\t\t\tPatient Fee Charge\n\n ";
cout << "*******************************************************************************";
//cout << "\nHospital Room Charges                      :\t  1000";
cout << "\nHospital Care Charges                      :\t  50";
cout << "\nHospital Maintaince Charges                :\t  50";
cout << "\nPatient Individual  Charges                :\t " << bill;
total = 50 + 50 + bill;
cout << "\nTotal Fee Charge                           :\t"  << total<<"\n";
cout << "********************************************************************************";
}

void patient::getdata()
{
PersonInfo();
cout<<"\nEnter The registration number of the patient: ";
cin>>reg_no;
cout<<"\nEnter The occupation of the patient: ";
cin>>occupation;
cout<<"\nEnter The bill of the patient:";
cin>>bill;
cout<<"\nEnter The date admitted(dd/mm/yyyy):";
cin>>date_admit;
cout<<"\nEnter The date discharged(dd/mm/yyyy):";
cin>>date_discharge;
patient_bill();
strncpy(medicine, "null", sizeof(medicine) - 1);
    medicine[sizeof(medicine) - 1] = 0;
}

void patient::showdata()
{
cout<<"\nRegistration number of patient: "<<reg_no<<"\n";
Display_info();
cout<<"\nOccupation : "<<occupation;
cout<<"\nAdmit date : "<<date_admit;
cout<<"\nDischarhge date :"<<date_discharge;
cout<<"\nBill :"<<total;
cout<<"\nPrescribed Medicine: "<<medicine;

}

int  patient::retidno()
{
return reg_no;
}

void patient::modify_medicine(int n)
{
bool found=false;
patient p;
fstream File;
File.open("patient.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&p), sizeof(patient));
if(p.retidno()==n)
{
p.showdata();
cout<<"\n\nPlease Enter The Medicine of patient"<<endl;
                cin>>p.medicine;
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void patient::write_patient()  // writing into file
{
patient p;
ofstream outFile;
outFile.open("patient.dat",ios::binary|ios::app);
p.getdata();
outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
outFile.close();
    cout<<"\n\nPatient record Has Been Created ";
cin.ignore();
cin.get();
}

void patient::display_all()  //reading from file
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
p.showdata();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void patient::display_p(int n) //reading specific file
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
if(p.retidno()==n)
{
  p.showdata();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}


void patient:: modify_patient(int n)   //modifying patient details
{
bool found=false;
patient p;
fstream File;
File.open("patient.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&p), sizeof(patient));
if(p.retidno()==n)
{
p.showdata();
cout<<"\n\nPlease Enter The New Details of patient"<<endl;
                p.getdata();
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void patient:: delete_patient(int n)  //deleting a particular file
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
ofstream outFile;
outFile.open("Temp.dat",ios::out);
inFile.seekg(0,ios::beg);
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
if(p.retidno()!=n)
{
outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
}
}
outFile.close();
inFile.close();
remove("patient.dat");
rename("Temp.dat","patient.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}


class Doctor: public Staff
{
    int DocID;
    patient p;
    char Spz[500];

public:
     bool CheckRegNo(int n)
      {

      bool found=false;
 Doctor d;
 fstream File;
 File.open("Doctor.dat",ios::binary|ios::in);
 if(!File)
 {
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
 }
    while(!File.eof() && found==false)
        {

File.read(reinterpret_cast<char *> (&d), sizeof(Doctor));
if(d.DocID==n)
{
    found=true;
}
        }
        File.close();
        return found;
        cin.ignore();
        cin.get();


      }


    void DoctorInfo()
    {
        staff_info();
        id:
        cout<<"Enter Doctor ID(1200-1299):";
        int m;
        cin>>m;
        if(CheckRegNo(m)==false)
        {
            DocID=m;
        }
        else
        {
            cout<<"ID already taken\n";
            goto id;
        }


        cout<<"Enter Doctor Specialize :";
        cin>>Spz;
        system("pause");
    }

    void show_doctor()
    {
        cout<<"Doctor ID: "<<DocID;
        show_staff();

        cout<<"\nDoctor Specialize: "<<Spz;
    }

    int  retDid()
   {
return DocID;
   }

    void Prescribe_Medicine()
    {
        int n;
        cout<<"\n\n\tEnter Reg Number Of patient : "; cin>>n;
        p.modify_medicine(n);
    }


    void write_doctor()
   {
Doctor d;
ofstream outFile;
outFile.open("Doctor.dat",ios::binary|ios::app);
d.DoctorInfo();
outFile.write(reinterpret_cast<char *> (&d), sizeof(Doctor));

    cout<<"\n\nDoctor record Has Been Created ";
outFile.close();
cin.ignore();
   }


   void display_all_Doctor()
{
Doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(Doctor)))
{
d.show_doctor();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}


void display_d(int n)
{
Doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(Doctor)))
{
if(d.DocID==n)
{
  d.show_doctor();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void modify_doctor(int n)
{
bool found=false;
Doctor d;
fstream File;
File.open("Doctor.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&d), sizeof(Doctor));
if(d.DocID==n)
{
   d.show_doctor();
   cout<<"\n\nPlease Enter The New Details:"<<endl;
                d.DoctorInfo();
    int pos=(-1)*static_cast<int>(sizeof(d));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&d), sizeof(Doctor));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void Doctor_choice()
{
    char ch;

    do
{
int n;
system("cls");

        cout<<"\n\n\t01. Prescribe Medicine for patient ";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. To exit.....";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;

switch(ch)
{
case '1': Prescribe_Medicine();
     break;
case '2':
         cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;
            case '3':break;
default :cout<<"\b";
}
    }while(ch!='3');

}



   void Doctor_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT DOCTOR DATA";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. ALL DOCTOR ";
cout<<"\n\n\t04. MODIFY DOCTOR DATA";
cout<<"\n\n\t05. TO EXIT............";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;
        system("cls");
switch(ch)
{
case '1': write_doctor();
     break;
case '2':
         cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;

case '3':

        display_all_Doctor();
    break;
case '4':
        cout<<"Enter Doctor ID :";cin>>n;
        modify_doctor(n);
        break;
/*case '5':break;
default :cout<<"\b";*/
}
    }while(ch!='5');

}

};

class Nurse: public Staff
{

    int NurseID;
    char ChargeRoom [50];
    patient p;
public:
       void GetNurseInfo()
    {

       cout<<"--------------------------------"<<endl;
       staff_info();
       cout<<"Enter Nurse ID:";
       cin>>NurseID;
       cout<<"Enter Nurse Duty Room :";
       cin>>ChargeRoom;
    }


    void Display_NurseInfo()
    {
        cout<<"--------------------------------"<<endl;
        cout<<"Nurse ID :"<<NurseID;
        show_staff();

        cout<<"\n"<<"Nurse in charge Room :"<<ChargeRoom;
        cout<<endl;


    }

    void Write_NurseInfo()
{
    Nurse n;
ofstream outFile;
outFile.open("NurseInfo.dat",ios::binary|ios::app);
n.GetNurseInfo();

outFile.write(reinterpret_cast<char *> (&n), sizeof(Nurse));
outFile.close();
    cout<<"\n\nrecord Has Been Created ";
cin.ignore();
cin.get();
}
    void display_n(int m)
{
Nurse n;
ifstream inFile;
inFile.open("NurseInfo.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&n), sizeof(Nurse)))
{
if(n.NurseID==m)
{
  n.Display_NurseInfo();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord does not exist";
cin.ignore();
cin.get();
}

  void modify_Nurse(int m)
{
bool found=false;
Nurse n;
fstream File;
File.open("NurseInfo.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&n), sizeof(Nurse));
if(n.NurseID==m)
{
n.Display_NurseInfo();
cout<<"\n\nPlease Enter The New Details of nurse"<<endl;
                n.GetNurseInfo();
    int pos=(-1)*static_cast<int>(sizeof(n));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&n), sizeof(Nurse));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record does Not Found ";
cin.ignore();
cin.get();
}

void display_all_Nurse()
{
Nurse n;
ifstream inFile;
inFile.open("NurseInfo.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&n), sizeof(Nurse)))
{
n.Display_NurseInfo();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void Nurse_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT NURSE DATA";
cout<<"\n\n\t02. Search NURSE ";
cout<<"\n\n\t03. ALL NURSE ";
cout<<"\n\n\t04. MODIFY NURSE DATA";
cout<<"\n\n\t05. To EXIT..........";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;

switch(ch)
{
case '1': Write_NurseInfo();
     break;
case '2':
         cout<<"Enter NURSE ID :";cin>>n;
                      display_n(n);
                      break;

case '3':

        display_all_Nurse();
    break;
case '4':
        cout<<"Enter Nurse ID :";cin>>n;
        modify_Nurse(n);
        break;

}
    }while(ch!='5');

}

};


class Receptionist:public Staff
{
    patient p;
    int RecID;

public:


  void RecInfo()
    {
        staff_info();
        cout<<"Enter Receptionist ID :";
        cin>>RecID;

    }

    void show_receptionist()
    {

        show_staff();



        cout<<"Receptionist ID: "<<RecID;


    }




void entry_Patient()
{
char ch;
int num;
do{
system("cls");
cout<<"\n\n\n\tENTRY MENU";
cout<<"\n\n\t1.CREATE PATIENT RECORD";
cout<<"\n\n\t2.DISPLAY ALL PATIENTS RECORDS";
cout<<"\n\n\t3.SEARCH PATIENT RECORD ";
cout<<"\n\n\t4.MODIFY PATIENT RECORD";
cout<<"\n\n\t5.DELETE PATIENT RECORD";
cout<<"\n\n\t6.TO EXIT";
cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
cin>>ch;
system("cls");

switch(ch)
{
case '1': p.write_patient();break;
case '2': p.display_all(); break;
case '3': cout<<"\n\n\tPlease Enter The reg  number "; cin>>num;
   p.display_p(num);break;
case '4': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.modify_patient(num);break;
case '5': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.delete_patient(num);break;

}
}while(ch!='6');
}

 void write_receptionist()
   {
Receptionist r;
ofstream outFile;
outFile.open("Receptionist.dat",ios::binary|ios::app);
r.RecInfo();
outFile.write(reinterpret_cast<char *> (&r), sizeof(Receptionist));
outFile.close();
    cout<<"\n\nReceptionist record Has Been Created ";
cin.ignore();
cin.get();
   }


   void display_all_Receptionist()
{
Receptionist r;
ifstream inFile;
inFile.open("Receptionist.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&r), sizeof(Receptionist)))
{
r.show_receptionist();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}


void display_r(int n)
{
Receptionist r;
ifstream inFile;
inFile.open("Receptionist.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&r), sizeof(Receptionist)))
{
if(r.RecID==n)
{
  r.show_receptionist();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void modify_receptionist(int n)
{
bool found=false;
Receptionist r;
fstream File;
File.open("Receptionist.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&r), sizeof(Receptionist));
if(r.RecID==n)
{
   r.show_receptionist();
   cout<<"\n\nPlease Enter The New Details "<<endl;
                r.RecInfo();
    int pos=(-1)*static_cast<int>(sizeof(r));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&r), sizeof(Receptionist));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void Receptionist_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT Receptionist DATA";
cout<<"\n\n\t02. Search Receptionist ";
cout<<"\n\n\t03. ALL Receptionist ";
cout<<"\n\n\t04. MODIFY Receptionist DATA";

cout<<"\n\n\t05. To EXIT..........";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;

switch(ch)
{
case '1': write_receptionist();
     break;
case '2':
         cout<<"Enter Receptionist ID :";cin>>n;
                      display_r(n);
                      break;

case '3':

        display_all_Receptionist();
    break;
case '4':
        cout<<"Enter Receptionist ID :";cin>>n;
        modify_receptionist(n);
        break;

}
    }while(ch!='5');

}
};


class store_manager:public Staff
{

    private:
        string productName;
        string supplierName;
        int unit;
        int bill;
        int SID;

    public:

       void SInfo()
    {
        staff_info();
        cout<<"Enter Receptionist ID :";
        cin>>SID;
    }

    void show_StoreManager()
    {
        show_staff();
        cout<<"Store Manager ID: "<<SID;

    }

       void orderproducts()
       {
         cout<<"\n\n|----------- ORDER Products & SUPPLIES ----------|"<<endl<<endl;

         cout<<"Enter Product Name: ";
         cin>>productName;
         cout<<"\nEnter Supplier's Name: ";
         cin>>supplierName;
         cout<<"\nEnter Number of Unit: ";
         cin>>unit;
         cout<<"\nEnter Total bill: ";
         cin>>bill;
         ofstream fout;
         fout.open("Products&Supplies.txt",ios::app);
        fout<<"Product Name: "<< productName<<endl;
        fout<<"Supplier's Name: "<< supplierName<<endl;
        fout<<"Number of Unit: "<< unit<<endl;
        fout<<"Total Bill: "<< bill<<endl<<endl;
         fout.close();
        cout<<"\n\nPRODUCT ORDERED SUCCESSFULLY!!"<<endl<<endl;
        int choice;
        cout<<"Do you want to order more?"<<endl;
        cout<<"(1) Yes"<<endl;
        cout<<"(2) No"<<endl<<endl<<endl;
        cin>>choice;

    if(choice==1)
    {
        system("cls");
        orderproducts();
    }
    else
    {
        return;
    }

}

  void readFromFile()
{
    ifstream fin;
    fin.open("Products&Supplies.txt");

    string str;
    if(!fin)
    {
        cout<<"\nERROR LOADING FILE!!"<<endl;
        return;
    }
    else
    {
        while(!fin.eof())
        {
            getline(fin,str);
            cout<<str;
            cout<<endl;
        }
    }
    cout<<endl<<endl<<endl;
    fin.close();
    cin.get();
    system("pause");
}


void write_store_manager()
   {
store_manager s;
ofstream outFile;
outFile.open("StoreManager.dat",ios::binary|ios::app);
s.SInfo();
outFile.write(reinterpret_cast<char *> (&s), sizeof(store_manager));
outFile.close();
    cout<<"\n\nrecord Has Been Created ";
cin.ignore();
cin.get();
   }

   void display_all_storeManager()
{
store_manager s;
ifstream inFile;
inFile.open("StoreManager.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&s), sizeof(store_manager)))
{
s.show_StoreManager();
cout<<"\n\n=======================================================================================\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void display_s(int n)
{
store_manager s;
ifstream inFile;
inFile.open("StoreManager.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&s), sizeof(store_manager)))
{
if(s.SID==n)
{
  s.show_StoreManager();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}


void store_manager_choice()
{

    char ch;

    do
{
int n;
system("cls");

        cout<<"\n\n\t01. Order Products ";
cout<<"\n\n\t02. Show Order Products & Bills ";
cout<<"\n\n\t03. To exit.....";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;

switch(ch)
{
case '1':
         orderproducts();
     break;
case '2':
         readFromFile();
                      break;
            case '3':break;
default :cout<<"\b";
}
    }while(ch!='3');


}

void store_manager_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT STORE MANAGER DATA";
cout<<"\n\n\t02. Search STORE MANAGER ";
cout<<"\n\n\t03. ALL STORE MANAGER ";
cout<<"\n\n\t04. To exit this menu";
cout<<"\n\n\tPlease Select Your Option (1-4) ";
cin>>ch;

switch(ch)
{
case '1': write_store_manager();
     break;
case '2':
         cout<<"Enter STORE MANAGER ID :";cin>>n;
                      display_s(n);
                      break;

case '3':

        display_all_storeManager();
    break;

case '4':break;
default :cout<<"\b";
}
    }while(ch!='4');

}

};


class admin
{
  Doctor d;
  patient p;
  Receptionist r;
  store_manager s;
  Nurse n;

  public:
    void staff_menu()
    {
        char ch;
        do{
system("cls");
cout<<"\n\n\tStaff Menu";
cout<<"\n\n\t1.Doctor";
cout<<"\n\n\t2.Nurse";
cout<<"\n\n\t3.Receptionist";
cout<<"\n\n\t4.Store Manger";
cout<<"\n\n\t5.TO EXIT";
cout<<"\n\n\tPlease Enter Your Choice (1-4) ";
cin>>ch;
system("cls");

switch(ch)
 {
  case '1': d.Doctor_menu();break;
  case '2': n.Nurse_menu(); break;
  case '3':    r.Receptionist_menu();break;
  case '4':    s.store_manager_menu();break;

 }
}while(ch!='5');

    }

};
void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}

int main()
{
    system("color f5");
    admin a;
    Receptionist r;
    Doctor d;
    store_manager s;
    int ch;
    char pass[15];
    int n;
    cout << "\n\n\n\n\n\t\t\t\tWELCOME TO OUR HOSPITAL MANAGEMENT SYSTEM";
	for(int i=0;i<6;i++)
    {
        fordelay(10000000000);
        printf(".");
    }
    do{

            fomo:
                  system("cls");
    cout<<"\t\t\n\n\n";
    cout<<"\t\t\t\t\tSELECT AN OPTION\n\n";
    cout<<"\t\t\t\t1.Admin\n";
    cout<<"\t\t\t\t2.Receptionist\n";
    cout<<"\t\t\t\t3.Doctor\n";
    cout<<"\t\t\t\t4.Store Manager\n";
    cout<<"\t\t\t\t5.Exit From The SYSTEM\n";
    cin>>ch;
    switch(ch){
        case 1:
                 login1:
                 cout<<"Enter ADMIN password: ";

                 cin>>pass;

                 if(strcmp(pass,"admin")==0)
                 {
                   a.staff_menu();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    cout<<"PRESS 1 TO TRY AGAIN OR 5 TO GO BACK TO MENU\n";

                    cin>>n;
                    if(n==1)
                    goto login1;

                    else
                        goto fomo;
                 }
                 break;
        case 2:
                 login2:
                 cout<<"Enter Receptionist password: ";

                 cin>>pass;

                 if(strcmp(pass,"receptionist")==0)
                 {
                   r.entry_Patient();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    cout<<"PRESS 1 TO TRY AGAIN OR 5 TO GO BACK TO MENU\n";

                    cin>>n;
                    if(n==1)
                    goto login2;

                    else
                        goto fomo;
                 }
                break;
        case 3:

                 login3:
                 cout<<"Enter Doctor password: ";

                 cin>>pass;

                 if(strcmp(pass,"doctor")==0)
                 {
                   d.Doctor_choice();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    cout<<"PRESS 1 TO TRY AGAIN OR 5 TO GO BACK TO MENU\n";

                    cin>>n;
                    if(n==1)
                    goto login3;

                    else
                        goto fomo;
                 }
                 break;
        case 4:
                 login4:
                 cout<<"Enter STORE MANAGER password: ";

                 cin>>pass;
                 if(strcmp(pass,"store")==0)
                 {
                   s.store_manager_choice();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    cout<<"PRESS 1 TO TRY AGAIN OR 5 TO GO BACK TO MENU\n";

                    cin>>n;
                    if(n==1)
                    goto login4;

                    else
                        goto fomo;
                 }
                 break;
            }
    }while(ch!=5);
}
