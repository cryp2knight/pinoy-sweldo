package incometax.contribution;

public class PagIBIGContribution extends Contribution{

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

