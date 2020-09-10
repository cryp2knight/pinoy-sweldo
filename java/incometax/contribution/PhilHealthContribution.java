package incometax.contribution;

public class PhilHealthContribution extends Contribution{

    private String membership;

    public PhilHealthContribution(double monthlySalary, String membership) throws Exception {
        super(monthlySalary);
        setModel("PhilHealth");
        setMembership(membership);
        setMonthlyContribution(
            compute(monthlySalary, membership)
        );
    }

    public void setMembership(String membership) throws Exception{
        if (
            membership.equalsIgnoreCase("employed") ||
            membership.equalsIgnoreCase("self-employed")
        )
            this.membership = membership;

        else throw new Exception("Invalid membership.");
    }

    public String getMembership(){
        return membership;
    }

    public double compute(double monthlySalary, String membership){
        if ( membership.equalsIgnoreCase("employed") ) {
            if ( monthlySalary <= 10000 )
                return 137.50;
            else if ( monthlySalary >= 10000.01 && monthlySalary <= 39999.99 )
                return ( monthlySalary * 0.0275 ) / 2;
            else if ( monthlySalary >= 40000 )
                return 1100.0;
        }
        else if ( membership.equalsIgnoreCase("self-employed") ){
            if ( monthlySalary <= 25000 )
                return 200.0;
            else if ( monthlySalary > 25000 )
                return 300.0;
        }
        return 0.0;
    }
}
