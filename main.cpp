#include<iostream>
#include"Dam.h"
using namespace std;

void advancedsettings(Dam &D)         //change dam depth,addinlets or outlets,etc
{
    int ch,n=0;
    bool loop = true;
    while(loop)
    {
    try{
        cout << "1-Increase or Decrease depth of dam\n2-Add outlet\n3-Add inlet\n4-Exit advanced settings\n";
        cin >> ch;
        if (cin.fail()) 
        {
            throw invalid_argument("Invalid input! Please enter a valid integer.");
        }
        switch(ch)
        {
            case 1:
            {
                cout << "Depth increased(+ve) or decreased(-ve) by? ";
                cin >> n;
                if (cin.fail()) 
                    throw invalid_argument("Invalid input! Please enter a valid integer.");
                D.adddepth(n);
                break;
            }
            case 2:
            {
                D.Addoutlet();
                break;
            }
            case 3:
            {
                D.Addinlet();
                break;
            }
            case 4:
            {
                loop = false;
                break;
            }
            default:
            {
                cout << "Invalid input Enter again";
            }
        }
    }
    catch (const invalid_argument& e) 
    {
        cout << e.what() << endl;
        cin.clear();  // Clears the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discards invalid input
    } 
    }
    
}

int main()
{
    string nam, loc;
    cout << "Enter Dam Name: " << endl;
    getline(cin, nam);
    cout << "Enter Dam Location city: " << endl;
    getline(cin, loc);
    int in,o,l,b;
    cout << "Enter number of inlets and outlets of dam: ";
    cin >> in >> o;
    cout << "Enter Length, breadth: ";
    cin >> l >> b;
    Dam D (nam, loc, in, o, l, b);
    cin >> D;
    bool loop =true;
    while(loop)
    {
        int ch,n;
        cout << "\n\n                OPERATE                \n1-Dispaly dam status\n2-Update inlets data\n3-operate outlets\n4-Simulate for n seconds\n5-Auto pilot\n6-Exit\n7-Advanced Settings\n :";
        cin >> ch;
        switch(ch)
        {
            case 1:
            {
                cout << D;
                break;
            }
            case 2:
            {
                try {
                cout << "choose inlets(0-" << D.I.size()-1 << "): ";
                cin >> n;
                if (n < 0 || n >= D.I.size()) 
                {
                    throw out_of_range("Invalid inlet index!");
                }
                int i;
                float p;
                cout << "Enter inlet rate and pH: ";
                cin >> i >> p;
                D.I[n].operate(i,p);
                } 
                catch (const out_of_range& e) 
                {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3:
            {
                try {
                cout << "choose outlets(0-" << D.O.size()-1 << "): ";
                cin >> n;
                if (n < 0 || n >= D.O.size()) 
                {
                throw out_of_range("Invalid outlet index!");
                }
                    cout << "Open(0-100)? : ";
                    int val;
                    cin >> val;
                    D.O[n].operate(val);
                }
                catch (const out_of_range& e) 
                {
                    cout << e.what() << endl;
                }
                break;
            }
            case 4:
            {
                cout << "no of Seconds: ";
                cin >> n;
                D.simulate(n);
                cout << D;
                break;
            }
            case 5:
            {
                D.autopilot();
                break;
            }
            case 6:
            {
                cout << "\nExited\n-X-X-X-X-X-";
                loop = false;
                exit(1);
                break;
            }
            case 7:
            {
                advancedsettings(D);
                break;
            }
            default:
            {
                cout << "Invalid input" << endl;
            }
        }
    }
return 0;
}
