/** 
 * Pinoy-Sweldo a module for computing Income Tax in the Philippines.
 * :copyright: 2020-Present by Daniel De Castro.
 * :license: MIT, see LICENSE for more details.
*/

package incometax;

import incometax.contribution.*;

public class IncomeTax{

    // calculates the incme tax, netpay, and other contributions

    private SSSContribution sssContribution;
    private PhilHealthContribution philhealthContribution;
    private PagIBIGContribution pagibigContribution;
    private double monthlySalary, totalContributions, taxableIncome, incomeTax, 
        salaryAfterTax, totalDeductions, netPay;

    public IncomeTax(double monthlySalary) throws Exception{
        setSSSContribution(new SSSContribution(monthlySalary));
        setPhilHealthContribution(new PhilHealthContribution(monthlySalary, "employed"));
        setPagibigContribution(new PagIBIGContribution(monthlySalary));
        setMonthlySalary(monthlySalary);
    }

    public SSSContribution getSSSContribution() {
        return sssContribution;
    }

    public void setSSSContribution(SSSContribution sssContribution) {
        this.sssContribution = sssContribution;
    }

    public PhilHealthContribution getPhilHealthContribution() {
        return philhealthContribution;
    }

    public void setPhilHealthContribution(PhilHealthContribution philhealthContribution) {
        this.philhealthContribution = philhealthContribution;
    }

    public PagIBIGContribution getPagibigContribution() {
        return pagibigContribution;
    }

    public void setPagibigContribution(PagIBIGContribution pagibigContribution) {
        this.pagibigContribution = pagibigContribution;
    }

    public double getMonthlySalary() {
        return monthlySalary;
    }

    public void setMonthlySalary(double monthlySalary) {
        this.monthlySalary = monthlySalary;
    }

    public double getTotalContributions() {
        Contribution[] contrib = {getPagibigContribution(), getSSSContribution(), getPhilHealthContribution()};
        double sum = 0;
        for (int i = 0; i < contrib.length; i++){
            sum += contrib[i].getMonthlyContribution();
        }
        totalContributions = sum;
        return totalContributions;
    }

    public void setTotalContributions(double totalContributions) {
        this.totalContributions = totalContributions;
    }

    public double getTaxableIncome() {
        taxableIncome = getMonthlySalary() - getTotalContributions();
        return taxableIncome;
    }

    public void setTaxableIncome(double taxableIncome) {
        this.taxableIncome = taxableIncome;
    }

    public double getIncomeTax() {
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

    public void setIncomeTax(double incomeTax) {
        this.incomeTax = incomeTax;
    }

    public double getSalaryAfterTax() {
        salaryAfterTax = getMonthlySalary() - getIncomeTax();
        return salaryAfterTax;
    }

    public void setSalaryAfterTax(double salaryAfterTax) {
        this.salaryAfterTax = salaryAfterTax;
    }

    public double getTotalDeductions() {
        totalDeductions = getIncomeTax() + getTotalContributions();
        return totalDeductions;
    }

    public void setTotalDeductions(double totalDeductions) {
        this.totalDeductions = totalDeductions;
    }

    public double getNetPay() {
        netPay = getMonthlySalary() - getTotalDeductions();
        return netPay;
    }

    public void setNetPay(double netPay) {
        this.netPay = netPay;
    }

    public String toRepresentation(){
        return "Monthly salary = "+getMonthlySalary()+"\n"
            + getSSSContribution().getModel()+" = "+getSSSContribution().getMonthlyContribution()+"\n"
            + getPhilHealthContribution().getModel()+" = "+getPhilHealthContribution().getMonthlyContribution()+"\n"
            + getPagibigContribution().getModel()+" = "+getPagibigContribution().getMonthlyContribution()+"\n"
            + "Total contributions = "+getTotalContributions()+"\n"
            + "Income tax = "+getIncomeTax()+"\n"
            + "Salary after tax = "+getSalaryAfterTax()+"\n"
            + "Total deductions = "+getTotalDeductions()+"\n"
            + "Net pay = "+getNetPay()+"\n";
    }
    
}
