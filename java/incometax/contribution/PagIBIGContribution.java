/** 
 * Pinoy-Sweldo a module for computing Income Tax in the Philippines.
 * :copyright: 2020-Present by Daniel De Castro.
 * :license: MIT, see LICENSE for more details.
*/

package incometax.contribution;

public class PagIBIGContribution extends Contribution{

    // Calculates the Pag IBIG monthly contribution depending
    // on the user monthly income.

    public PagIBIGContribution(double monthlySalary) throws Exception{
        super(monthlySalary);
        setModel("PAG-IBIG");
        setMonthlyContribution(
            compute(monthlySalary)
        );
    }

    public double compute(double monthlySalary){
        if ( monthlySalary <= 1500 )
            return monthlySalary * 0.01;
        else if ( monthlySalary > 1500 && monthlySalary < 5000 )
            return monthlySalary * 0.02;
        else if ( monthlySalary >= 5000 )
            return 100;
        return 0.0;
    }
}

