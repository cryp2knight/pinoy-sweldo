
import incometax.*;
import incometax.contribution.*;

public class Project{

    public static void main(String[] args) {
        try {
            IncomeTax tax = new IncomeTax(20000);
            tax.setPhilHealthContribution(new PhilHealthContribution(tax.getMonthlySalary(), "self-employed"));
            System.out.print(tax.toRepresentation());
        }catch(Exception e){
            System.out.print(e.getMessage());
        }
    }
}
