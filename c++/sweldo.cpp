/** 
 * Pinoy-Sweldo a module for computing Income Tax in the Philippines.
 * :copyright: 2020-Present by Daniel De Castro.
 * :license: MIT, see LICENSE for more details.
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Contribution
{
private:
    double monthlyContribution;
    double salaryAfterContribution;
    double monthlySalary;
    string model;

public:
    void setMonthlySalary(double ms);
    double getMonthlyContribution();
    void setMonthlyContribution(double mc);
    double getSalaryAfterContribution();
    void setSalaryAfterContribution(double sac);
    double getMonthlySalary();
    string getModel();
    void setModel(string model);
    Contribution(double ms);
};

Contribution::Contribution(double ms): monthlySalary(ms){
    setMonthlySalary(ms);
}

void Contribution::setMonthlySalary(double ms)  {
        if (monthlySalary < 0)
            throw invalid_argument("Invalid input, must be greater than equal to 0.");
        monthlySalary = ms;
}

double Contribution::getMonthlySalary(){
    return monthlySalary;
}

void Contribution::setMonthlyContribution(double mc){
    monthlyContribution = mc;
}

double Contribution::getMonthlyContribution(){
    return monthlyContribution;
}

void Contribution::setSalaryAfterContribution(double sac){
    salaryAfterContribution = sac;
}

double Contribution::getSalaryAfterContribution(){
    salaryAfterContribution = monthlySalary - monthlyContribution;
    return salaryAfterContribution;
}

void Contribution::setModel(string m){
    model = m;
}

string Contribution::getModel(){
    return model;
}


////////////////////////////////
////////////////////////////////
// SSS Contribution
////////////////////////////////
////////////////////////////////


class SSSContribution: public Contribution{

    // Calculates the SSS monthly contribution depending
    // on the user monthly income.
    // Only applicable for employed users.
    // Uses the SSS Contribution Table 2019 for the computation

private:
    double contributionTable[37][3] = {
        {2250,80, 0},
        {2250,2749.99,100},
        {2750,3249.99,120},
        {3250,3719.99,140},
        {3750,4249.99,160},
        {4250,4749.99,180},
        {4750,5249.99,200},
        {5250,5749.99,220},
        {5750,6249.99,240},
        {6250,6749.99,260},
        {6750,7249.99,280},
        {7250,7749.99,300},
        {7750,8249.99,320},
        {8250,8749.99,340},
        {8750,9249.99,360},
        {9250,9749.99,380},
        {9750,10249.99,400},
        {10250,10749.99,420},
        {10750,11249.99,440},
        {11250,11749.99,460},
        {11750,12249.99,480},
        {12250,12749.99,500},
        {12750,13249.99,520},
        {13250,13749.99,540},
        {13750,14249.99,560},
        {14250,14749.99,580},
        {14750,15249.99,600},
        {15250,15749.99,620},
        {15750,16249.99,640},
        {16250,16749.99,660},
        {16750,17249.99,680},
        {17250,17749.99,700},
        {17750,18249.99,720},
        {18250,18749.99,740},
        {18750,19249.99,760},
        {19250,19749.99,780},
        {19750,800, 0}
    };

public:
    SSSContribution(double ms);
    double compute(double monthlySalary);
};

SSSContribution::SSSContribution(double ms): Contribution(ms){
    setModel("SSS");
    setMonthlyContribution(compute(ms));
};

double SSSContribution::compute(double ms){
    int l = 37;
    for (int i = 0; i < l; i++){
        if ( i == 0 && ms <= contributionTable[i][0] )
            return contributionTable[i][1];
        if (
            i == l - 1
            && ms >= contributionTable[i][0]
        )
            return contributionTable[i][1];
        if (
            ms >= contributionTable[i][0]
            && ms <= contributionTable[i][1]
        )
            return contributionTable[i][2];
    }
    return 0.0;   
}


////////////////////////////////
////////////////////////////////
// PhilHealth Contribution
////////////////////////////////
////////////////////////////////


class PhilHealthContribution: public Contribution{

    // Calculates the PhilHealth monthly contribution depending
    // on the user monthly income.
    // Uses the PhilHealth Contribution Table 2019 for the computation


private:
    string membership;
public:
    void setMembership(string m);
    string getMembership();
    double compute(double ms, string m);
    PhilHealthContribution(double ms, string m);
    
};

PhilHealthContribution::PhilHealthContribution(double ms, string m): Contribution(ms), membership(m){
    setModel("PhilHealth");
    setMembership(m);
    setMonthlyContribution(compute(ms, m));
}

void PhilHealthContribution::setMembership(string m){
    if ( m == "employed" || m == "self-employed" )
        membership = m;

    else throw invalid_argument("Invalid membership.");
}

string PhilHealthContribution::getMembership(){
    return membership;
}

double PhilHealthContribution::compute(double ms, string m){
    if ( m == "employed" ) {
        if ( ms <= 10000 )
            return 137.50;
        else if ( ms >= 10000.01 && ms <= 39999.99 )
            return ( ms * 0.0275 ) / 2;
        else if ( ms >= 40000 )
            return 1100.0;
    }
    else if ( m == "self-employed" ){
        if ( ms <= 25000 )
            return 200.0;
        else if ( ms > 25000 )
            return 300.0;
    }
    return 0.0;
}


// ////////////////////////////////
// ////////////////////////////////
// // PAGIBIG Contribution
// ////////////////////////////////
// ////////////////////////////////

class PagIBIGContribution: public Contribution{

    // Calculates the Pag IBIG monthly contribution depending
    // on the user monthly income.

public:
    double compute(double ms);
    PagIBIGContribution(double ms);
};

PagIBIGContribution::PagIBIGContribution(double ms): Contribution(ms){
    setModel("PAG-IBIG");
    setMonthlyContribution(compute(ms));
}

double PagIBIGContribution::compute(double ms){
    if ( ms <= 1500 )
        return ms * 0.01;
    else if ( ms > 1500 && ms < 5000 )
        return ms * 0.02;
    else if ( ms >= 5000 )
        return 100;
    return 0.0;
}

// ////////////////////////////////
// ////////////////////////////////
// // Income Tax
// ////////////////////////////////
// ////////////////////////////////

class IncomeTax{

    // calculates the incme tax, netpay, and other contributions

private:
    SSSContribution sssContribution;
    PhilHealthContribution philhealthContribution;
    PagIBIGContribution pagibigContribution;
    double monthlySalary;
    double totalContributions, taxableIncome, incomeTax, 
        salaryAfterTax, totalDeductions, netPay;
public:
    IncomeTax(double ms);
    void setSSSContribution(SSSContribution sss);
    SSSContribution getSSSContribution();
    PhilHealthContribution getPhilHealthContribution();
    void setPhilHealthContribution(PhilHealthContribution ph);
    PagIBIGContribution getPagibigContribution();
    void setPagibigContribution(PagIBIGContribution pg);
    double getMonthlySalary();
    void setMonthlySalary(double ms);
    double getTotalContributions();
    void setTotalContributions(double tc);
    double getTaxableIncome();
    void setTaxableIncome(double ti);
    double getIncomeTax();
    void setIncomeTax(double it);
    double getSalaryAfterTax();
    void setSalaryAfterTax(double sat);
    double getTotalDeductions();
    void setTotalDeductions(double td);
    double getNetPay();
    void setNetPay(double np);
    string toRepresentation();
};

IncomeTax::IncomeTax(double ms):
    sssContribution(SSSContribution(ms)),
    philhealthContribution(PhilHealthContribution(ms, "employed")), 
    pagibigContribution(PagIBIGContribution(ms)), 
    monthlySalary(ms) {
}

void IncomeTax::setSSSContribution(SSSContribution sss){
    sssContribution = sss;
}

SSSContribution IncomeTax::getSSSContribution(){
    return sssContribution;
}

void IncomeTax::setPhilHealthContribution(PhilHealthContribution ph){
    philhealthContribution = ph;
}

PhilHealthContribution IncomeTax::getPhilHealthContribution(){
    return philhealthContribution;
}

void IncomeTax::setPagibigContribution(PagIBIGContribution pg){
    pagibigContribution = pg;
}

PagIBIGContribution IncomeTax::getPagibigContribution(){
    return pagibigContribution;
}

void IncomeTax::setMonthlySalary(double ms){
    monthlySalary = ms;
}

double IncomeTax::getMonthlySalary(){
    return monthlySalary;
}

void IncomeTax::setTotalContributions(double tc){
    totalContributions = tc;
}

double IncomeTax::getTotalContributions(){
    Contribution contrib[] = {getPagibigContribution(), getSSSContribution(), getPhilHealthContribution()};
    double sum = 0;
    for (int i = 0; i < 3; i++){
        sum += contrib[i].getMonthlyContribution();
    }
    totalContributions = sum;
    return totalContributions;
}

void IncomeTax::setTaxableIncome(double ti){
    taxableIncome = ti;
}

double IncomeTax::getTaxableIncome(){
    taxableIncome = getMonthlySalary() - getTotalContributions();
    return taxableIncome;
}

void IncomeTax::setIncomeTax(double it){
    incomeTax = it;
}

double IncomeTax::getIncomeTax(){
    if (getTaxableIncome() <= 20833 )
        incomeTax = 0.0;
    else if (getTaxableIncome() > 20833 && getTaxableIncome() <= 33332 )
        incomeTax = ( getTaxableIncome() - 20833 ) * 0.20;
    else if (getTaxableIncome() == 33333 )
        incomeTax = 2500;
    else if (getTaxableIncome() > 33333 && getTaxableIncome() <= 66666 )
        incomeTax = ( getTaxableIncome() - 33333 ) * 0.25 + 2500;
    else if (getTaxableIncome() == 66667 )
        incomeTax = 10833.33;
    else if (getTaxableIncome() > 66667 && getTaxableIncome() <= 166666 )
        incomeTax = ( getTaxableIncome() - 66667 ) * 0.30 + 10833.33;
    else if (getTaxableIncome() == 166667 )
        incomeTax = 40833.33;
    else if (getTaxableIncome() > 166667 && getTaxableIncome() <= 666666 )
        incomeTax = ( getTaxableIncome() - 166667 ) * 0.32 + 40833.33;
    else if (getTaxableIncome() == 666667 )
        incomeTax = 200833.33;
    else if (getTaxableIncome() > 666667 )
        incomeTax = ( getTaxableIncome() - 666667 ) * 0.35 + 200833.33;
    return incomeTax;
}

void IncomeTax::setSalaryAfterTax(double sat){
    salaryAfterTax = sat;
}

double IncomeTax::getSalaryAfterTax(){
    salaryAfterTax = getMonthlySalary() - getIncomeTax();
    return salaryAfterTax;
}

void IncomeTax::setTotalDeductions(double td){
    totalDeductions = td;
}

double IncomeTax::getTotalDeductions(){
    totalDeductions = getIncomeTax() + getTotalContributions();
    return totalDeductions;
}

void IncomeTax::setNetPay(double np){
    netPay = np;
}

double IncomeTax::getNetPay(){
    netPay = getMonthlySalary() - getTotalDeductions();
    return netPay;
}

string IncomeTax::toRepresentation(){
    return "Monthly salary = "+ to_string(getMonthlySalary()) +"\n"
        + getSSSContribution().getModel()+" = "+ to_string(getSSSContribution().getMonthlyContribution())+"\n"
        + getPhilHealthContribution().getModel()+" = "+to_string(getPhilHealthContribution().getMonthlyContribution())+"\n"
        + getPagibigContribution().getModel()+" = "+to_string(getPagibigContribution().getMonthlyContribution())+"\n"
        + "Total contributions = "+to_string(getTotalContributions())+"\n"
        + "Income tax = "+to_string(getIncomeTax())+"\n"
        + "Salary after tax = "+to_string(getSalaryAfterTax())+"\n"
        + "Total deductions = "+to_string(getTotalDeductions())+"\n"
        + "Net pay = "+to_string(getNetPay())+"\n";
}


////////////////////////////////
////////////////////////////////
// MAIN
////////////////////////////////
////////////////////////////////

int main(){
    IncomeTax tax = IncomeTax(20000);
    cout << tax.toRepresentation();
}
