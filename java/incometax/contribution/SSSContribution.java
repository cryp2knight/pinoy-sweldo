package incometax.contribution;

public class SSSContribution extends Contribution {

    static final double[][] contributionTable = {
        {2250,80},
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
        {19750,800}
    };

    public SSSContribution(double monthlySalary) throws Exception{
        super(monthlySalary);
        setModel("SSS");
        setMonthlyContribution(
            compute(monthlySalary)
        );
    }

    public double compute(double monthlySalary){

        for (int i = 0; i < contributionTable.length; i++){
            if ( i == 0 && monthlySalary <= contributionTable[i][0] )
                return contributionTable[i][1];
            if (
                i == contributionTable.length - 1
                && monthlySalary >= contributionTable[i][0]
            )
                return contributionTable[i][1];
            if (
                monthlySalary >= contributionTable[i][0]
                && monthlySalary <= contributionTable[i][1]
            )
                return contributionTable[i][2];
        }

        return 0.0;
    }

}
