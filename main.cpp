
//  d2aconverter.cpp
//  d2aconvertorvoltages
//  Digital to Analogue convertor for an inverted ideal 741 op-amp amplifier circuit. Will calculate the voltage outputs from nth input bits,
// The input and output values will be displayed in a truth table format.
//  Created by genny on 12/12/22.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;


//Voltage input class, defines a voltage input source with its accompanying resistor.
class Vin
{
    
private:
    double Rn;  //object resistor value
    double Vn;
    int status;    //on is 1, 0 is off,  vin, off is 0v

public:
    Vin();
    Vin(double R, double V);
    
    double getResistance();
    double getVoltage();;
    int getStatus();
    void setStatus(int);
};

Vin::Vin()
{
    this->Rn = 0;
    this->Vn= 0;
    this->status = 0;
}

Vin::Vin(double R, double V)
{
    Rn = R;
    Vn =V;
}

void Vin::setStatus(int s)
{
    status = s;
}

int Vin:: getStatus()
{
    return this->status;
}

double Vin::getResistance()
{
    return this-> Rn;
}

double Vin:: getVoltage()
{
    return this->Vn;
}


Vin makeV(double R, double V);
void vectorprint(vector<Vin> ins, double r);

int main()
{
    double Rf;      //Equivalent Feedback Resistance Value
    int n;           //n is number of voltage inputs (ie:if a 4 bit, enter 4)
    double binaryV; // WHat other voltage value will be used aside from 0? Is binary.
    double Rv; //2^n resistor value, only need MSB significant resistor value, user may input this
    
    cout<<"_______D/A Converter for an Inverted 741 OP-AMP________ \n\n\n\n";
    cout<<"How many digital inputs does the design have:"<<endl;
    cin>>n;
    cout<<"What is the equivalent feedback reisstance value: "<<endl;
    cin>>Rf;
    cout<<"What is the 'ON' status digital input voltage value, the voltage value when the source is turned on: "<<endl;
    cin>>binaryV;
    
    
    cout<<"From MSB to LSB, Enter Resistance at each input----\n"<<endl;
    
    vector <Vin> inputs;//holds input values
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter the resistor value at bit "<<i+1<<endl;
        cin>>Rv;
        inputs.push_back(makeV(Rv,binaryV));
    }
    vectorprint(inputs, Rf);
    return 0;
}

Vin makeV(double R, double V)
{
    if (R <= 0 || V == 0) {
        throw invalid_argument("Invalid resistor or voltage value.");
    }
    Vin in(R,V);
    return in;
}

void summingHelper(vector<Vin>& ins, double r, vector<double>& out, int n, double current)
{
    // Base case: if we have set the status of all inputs, we can calculate the output voltage
    if (n == ins.size()) {
        out.push_back(current);
        return;
    }

    // First, we set the current input status to 0 (off)
    ins[n].setStatus(0);

    // Recursively call summingHelper with the current input turned off
    summingHelper(ins, r, out, n+1, current);

    // Then, we set the current input status to 1 (on) and calculate the voltage drop across it
    ins[n].setStatus(1);
    double currentR = 0;
    double CurrentV= 0;
    for (int i = 0; i < ins.size(); i++)
    {
        if (ins[i].getStatus() == 1)
        { // get specifics
            currentR = ins[i].getResistance();
            CurrentV = ins[i].getVoltage();
        }
    }
    double voltage = -r*(CurrentV/currentR); //calculate voltage

    // Recursively call summingHelper with the current input turned on, and update the current output voltage accordingly
    summingHelper(ins, r, out, n+1, current + voltage);

    // Reset the current input status to 0 (off) before returning
    ins[n].setStatus(0);
}


void vectorprint(vector<Vin> ins, double r)
{
    vector<vector<bool>> truthTable;
    for (int i = 0; i < pow(2, ins.size()); i++)
    {
        bitset<8> binary(i);
        vector<bool> row;
        for (int j = ins.size()-1; j >= 0; j--)
        {
            row.push_back(binary[j]);
        }
        truthTable.push_back(row);
    }

    //call to summer, then prjt
    vector<double> out;
    summingHelper(ins, r, out, 0, 0);
    
    //print truth table
    cout<<"\n\nFrom MSB to LSB (left to right)"<<endl;
    cout << "\nTruth Table \n" << endl;
   
    //label bits and outputs
    cout<<"|Bits (1-"<<ins.size()<<")|"<<endl;
    int skip = 0;
    for(int i=0 ;i < ins.size();i++)
    {
        if(i!=ins.size() && (i+1) != 0)
        {
            cout<<i+1<<"   ";
            skip++;
        }
       else break;
    }
    cout<<"|Voltage Outputs"<<endl;
    for(int i=0; i<(4*skip);i++)
    {
        cout<<"_";
    }
    
    cout<<"|______________"<<endl;
    for (int i = 0; i < pow(2, ins.size()); i++)
    {
        for (int j = ins.size()-1; j >= 0; j--)
        {
            cout << truthTable[i][j] << "   ";
        }
        cout << "| " << out[i] << endl;
    }
}
