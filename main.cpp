#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

class joeBloggsPayroll{
    private:
        string name = "Joe Bloggs";
        float hoursWorked;
        float hourlyRate;
        char maritalStatus = '0';
        char parser;
        int grossPay;
        float netPay;
        float taxCredit;

        float PAYE;
        float USC;
        float PRSI;
        float taxCombined;
        int counterVariable = 0;

    public:
        void userInput();
        void determineTaxCredit();
        float weeklyGross();
        float calcPAYE();
        float calcUSC();
        float calcPRSI();
        float calcNet();
        void generateUi();
};

///This method assigns values to the core variables based, on user input,
///that are requiredfor this program to function
void joeBloggsPayroll:: userInput(){
    cout << "Please enter hours worked: " << endl;
    cin >> hoursWorked;

    cout << "Please enter your hourly rate: " << endl;
    cin >> hourlyRate;

    ///This will loop until a valid marital status is chosen
     while(counterVariable == 0){
        cout << "Please choose your marital status: " << endl;
        cout << "1. Single.       2. Married." << endl;
        cin >> parser;

        if(parser == '1'){
            maritalStatus = 'S';
            //cout << "S" << endl;
            counterVariable++;
        }
        else if(parser == '2'){
            maritalStatus = 'M';
            //cout << "M" << endl;
            counterVariable++;
        }
        else{
            cout << "Invalid." << endl;
        }
     }
}

///This method takes the previously defined maritalStatus char value
///and uses it to determine the value of taxCrtedit
void joeBloggsPayroll::determineTaxCredit(){

    if(maritalStatus == 'S'){
        taxCredit = 63.47;
    }
    else if(maritalStatus == 'M'){
        taxCredit = 95.19;
    }
    else{

    }
}

float joeBloggsPayroll::weeklyGross(){
    grossPay = hoursWorked * hourlyRate;
    //cout << grossPay << endl;
}

float joeBloggsPayroll::calcPAYE(){

    if(grossPay > 0 && grossPay >= 678.85){
        PAYE = 678.85 * 0.2;

        if(grossPay > 678.85){
            PAYE = PAYE + ((grossPay - 678.85) * 0.4) - taxCredit;

            }
        else{

        }
    }

    else{
        PAYE = grossPay * 0.2;
        //cout << "No 40% cut off" << endl;
    }


    //cout << "PAYE: " << PAYE << endl;
}

float joeBloggsPayroll::calcUSC(){

    float tempPay;
    float firstRate = 231;
    float secondRate = 397.82 - 231;
    float thirdRate = 1347 - 397.82;


    tempPay = grossPay;

    ///Nested if statements are used to cycle thorugh valid break-points in
    ///the emplyees income in order to determine the correct USC value
    if (grossPay > 231){
        USC = firstRate * 0.005;
        tempPay = tempPay - firstRate;
        //cout << "temp pay .5%: " << tempPay << " USC: " << USC << endl;

        if(grossPay > 397.82){

            tempPay = tempPay - secondRate;
            USC = USC + (secondRate * 0.02);
            //cout << "temp pay 2%: " << tempPay << " USC: " << USC << endl;

            if(grossPay > 397.82 && grossPay <= 1347){


                USC = USC + (tempPay * 0.045);
                //cout << "temp pay 4.5%: " << tempPay << " USC: " << USC << endl;

                if(grossPay > 1347){
                    tempPay = tempPay - thirdRate;
                    USC = USC + (tempPay * 0.08);
                    //cout << "temp pay 8%: " << tempPay << "USC: " << USC << endl;
                }
            }
            else{
                USC = USC + (tempPay * 0.045);
            }
        }
        else{
            USC = USC +(tempPay  * 0.02);
        }
    }
    else{
        USC = tempPay * 0.005;
    }
    //cout << USC << endl;
}

float joeBloggsPayroll::calcPRSI(){
    PRSI = grossPay * 0.04;
    //cout<< PRSI << endl;
}

float joeBloggsPayroll::calcNet(){
    taxCombined = PAYE + USC + PRSI;
    netPay = grossPay - taxCombined;
    //cout << netPay << endl;
}

void joeBloggsPayroll::generateUi(){
    userInput();
    determineTaxCredit();
    weeklyGross();
    calcPAYE();
    calcUSC();
    calcPRSI();
    calcNet();


   cout << "_________________________________________" << endl;
   cout << "|                 Weekly Payslip         |" << endl;
   cout << "|                                        |" << endl;
   cout<< "|" << fixed << setprecision(2) << setw(12) << "Name: "<< setw(12)  << name << setw(17) << "|" << endl;
cout << "|                                        |" << endl;

cout<< "|" << fixed << setprecision(2) << setw(12) << "Gross"<< setw(12)  << grossPay << setw(17) << "|" << endl;
cout << "|                                        |" << endl;

cout<< "|" << fixed << setprecision(2) << setw(12) << "PRSI"<< setw(12)  << PRSI << setw(17) << "|" << endl;
cout << "|                                        |" << endl;

cout<< "|" << fixed << setprecision(2) << setw(12) << "PAYE" << setw(12)  << PAYE << setw(17) << "|" << endl;
cout << "|                                        |" << endl;

cout<< "|" << fixed << setprecision(2) << setw(12) << "USC" << setw(12)  << USC << setw(17) << "|" << endl;
cout << "|                                        |" << endl;

cout<< "|" << fixed << setprecision(2) << setw(12) << "Net pay" << setw(12)  << netPay << setw(17) << "|" << endl;
cout << "|________________________________________|" << endl;


}

int main()
{
    system ("COLOR F0");

    joeBloggsPayroll myObj;

    myObj.generateUi();
    return 0;
}
