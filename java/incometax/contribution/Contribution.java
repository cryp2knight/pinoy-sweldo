package incometax.contribution;

public class Contribution{

    private double monthlyContribution;
    private double salaryAfterContribution;
    private double monthlySalary;
    public String model = "---";

    public Contribution(double monthlySalary) throws Exception {
        setMonthlySalary(monthlySalary);
    }

    public void setMonthlySalary(double monthlySalary) throws Exception {
        if (monthlySalary < 0)
            throw new Exception("Invalid input, must be greater than equal to 0.");
        this.monthlySalary = monthlySalary;
    }

    public double getMonthlyContribution() {
        return this.monthlyContribution;
    }

    public void setMonthlyContribution(double monthlyContribution) {
        this.monthlyContribution = monthlyContribution;
    }

    public double getSalaryAfterContribution() {
        this.salaryAfterContribution = this.monthlySalary - this.monthlyContribution;
        return this.salaryAfterContribution;
    }

    public double getMonthlySalary() {
        return this.monthlySalary;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

}
