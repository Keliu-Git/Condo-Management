/*
Kenny Liu
ICS4U1-02
January 26, 2018
A program that similates a situation in which the user is the manager of a condominium.
The program records the informations regarding the units within the condo. The user is able
to modify to these records, append, or to reset them.

Input: Integer, string
Output: String
*/
#include <iostream>
#include <string>

using namespace std;

class Condo{
protected:
    int roomNum[10][10];
    int floor, room;
    string outString;
    string condoData [10][10];

public:
    //Initialize the array for room number.
    Condo(){
        int room = 100;
        int *ptr = roomNum[0];
        for (int index =0; index < 100; index++){
            *ptr = room;
            ptr++;
            room++;
            //After incrementing 'room', if its value is a multiple of 10, e.g. 210, minus 10 and increment by 100 to get to the next floor.
            if (room%10==0)
                room +=90;
        }
    }

    //Method for displaying the information
    void display(){
        cout<<"Enter the floor you would like to output: \n";
        cin>>floor;
        if (floor < 1 or floor > 10)
            throw string ("Invalid input \n");


        string* ptrData = condoData[floor-1];
        int *ptrRoom = roomNum[floor-1];
        for (ptrData; ptrData < condoData[floor]; ptrData++){
            cout<<*ptrRoom<<": ";
            cout<<*ptrData<<" ";
            ptrRoom++;
            cout<<endl;
        }
    }

    void displayUI(){
        cout<<"-------------------------------------------- \n";
        cout<<"1. Display records \n";
        cout<<"2. Append to 'Resident' records \n";
        cout<<"3. Modify 'Unit' records \n";
        cout<<"4. Modify 'Resident' records \n";
        cout<<"5. Delete 'Resident' records \n";
        cout<<"6. Quit \n";
    }

    //Function to get locate the unit that the user would like to manipulate
    void unitLocator(){
        cout<<"Enter the floor of the unit (1-10): \n";
        cin>>floor;
        if (floor < 1 or floor > 10)
                throw string("Invalid input \n");

        cout<<"Enter the number of the unit (0-9): \n";
        cin>>room;
        if (room < 0 or room > 9)
                throw string("Invalid input \n");
    }

};

class Unit:public Condo{
public:

    //Initialize the array, fill it with "No data"
    Unit(){
        string* ptr = condoData[0];
        string initial = "No data";
        for (int index = 0; index < 100; index++){
            *ptr = initial;
            ptr++;
            }
        }

    //Method to modify the information of individual units
    void modify(){
        string area,value;
        unitLocator();

        cout<<"Enter the area of this unit (in square meters): \n";
        cin.ignore();
        getline(cin,area);

        cout<<"Enter the value this unit currently has: \n";
        getline(cin,value);

        while (value.find("$") != string::npos){
            value.erase(value.find("$"),1);
        }


        outString = "Area (m^2): "+area+", Value($): "+value;
        condoData[floor-1][room] = outString;

    }


};

class Resident:public Condo{

public:
    Resident(){
        string* ptr = condoData[0];
        string initial = "Vacant";
        for (int index = 0; index < 100; index++){
            *ptr = initial;
            ptr++;
        }
    }

    //Function to append to the residential info
    void append(){
        string name, number, age;

        unitLocator();

        cin.ignore();

        if(condoData[floor-1][room] != "Vacant")
            throw string("The unit is occupied. You can only modify the information or delete it. \n");

        cout<<"Enter the name of the owner you would like to add in: \n";
        getline(cin,name);

        cout<<"Enter the age of the owner: \n";
        getline(cin,age);

        cout<<"Enter the contact information of the owner: \n";
        getline(cin,number);

        outString = "Name: "+name+", Age: "+age+", Contact Information: "+number;

        condoData[floor-1][room] = outString;
    }


    //Function to wipe a unit's residential info
    void del(){

            unitLocator();

            condoData[floor-1][room] = "Vacant";
    }

    //Function to modify the residents' info
    void modify(){
            unitLocator();

            string inString = condoData[floor-1][room];

            if (inString == "Vacant")
                throw string("Cannot modify a vacant unit \n");


        int endPtr, counter = 0;

        //Separate the string data by their comma, store in an array.
        string Info[3];
        while (counter<3){
            endPtr = inString.find(",");
            Info[counter] = inString.substr(0,endPtr);
            inString.erase(0,endPtr+1);
            counter++;
        }

        int usrInput = 0;
        while (usrInput != 4){
                try{
                    cout<<"1. Owner's name \n";
                    cout<<"2. Owner's age \n";
                    cout<<"3. Owner's contact information \n";
                    cout<<"4. Cancel \n";
                    cout<<"Enter a number to choose an action: \n";
                    cin>>usrInput;
                    if (usrInput<1 or usrInput>4)
                        throw string("Invalid input \n");

                    switch(usrInput){
                        //Replacing the name of the owner with a new one
                case 1:
                    cout<<"Enter the replacing name: \n";
                    cin.ignore();
                    getline(cin,Info[0]);
                    usrInput = 4;
                    break;

                        //Replacing the age of the owner
                case 2:
                    cout<<"Enter the replacing age: \n";
                    cin.ignore();
                    getline(cin,Info[1]);
                    usrInput = 4;
                    break;

                        //Replacing the contact info
                case 3:
                    cout<<"Enter the replacing contact information \n";
                    cin.ignore();
                    getline(cin,Info[2]);
                    usrInput = 4;
                    break;
                    }
                }catch(string &error){
                    cout<<error;
                }

        }
        //Concatenate all of the strings in the array, store back to the record array.
        outString = Info[0]+", "+Info[1]+", "+Info[2];
        condoData[floor-1][room] = outString;
    }


};


//Program main body
int main(){
    Condo condo;
    Unit unit;
    Resident res;
    int userInput = 0;

    while (userInput != 6){
            int subMenuInput = 0;

            try{
                condo.displayUI();
                cout<<"Enter a number to choose an action: \n";
                cin>>userInput;

            if (userInput < 1 or userInput > 6)
                throw string("Invalid input \n");

            switch(userInput){

            case 1:
                while (subMenuInput != 3){
                    try{
                        cout<<"1. Display owners' information \n";
                        cout<<"2. Display units' information \n";
                        cout<<"3. Cancel \n";
                        cout<<"Enter a number to choose an action: \n";
                        cin>>subMenuInput;
                        if (subMenuInput< 1 or subMenuInput > 3)
                            throw string("Invalid input \n");

                        switch(subMenuInput){
                            case 1: res.display(); subMenuInput = 3; break;
                            case 2: unit.display(); subMenuInput = 3;break;
                        }
                    }catch(string &error){
                        cout<<error;
                    }
                }
                break;
            case 2:res.append();break;
            case 3:unit.modify();break;
            case 4:res.modify();break;
            case 5:res.del();break;

            }

            }catch (string &error){
                cout<<error;
            }
            cout<<endl;
    }

return 0;
}
