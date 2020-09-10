from .contribution import Contribution

class PhilHealthContribution(Contribution):
    """
    Calculates the PhilHealth monthly contribution depending
    on the user monthly income.
    Uses the PhilHealth Contribution Table 2019 for the computation

    """

    def __init__(self, monthly_salary = 0, membership = 'employed'):
        """
        membership is either "employed" or "self-employed"
        """
        super().__init__(monthly_salary)
        self.model = 'PhilHealth'
        self.validate_membership(membership)
        self.monthly_contribution = self.compute(monthly_salary, membership)

    def validate_membership(self, membership):
        if membership not in ('employed', 'self-employed'):
            raise ValueError({'membership': 'invalid membership'})
        self.membership = membership
    
    def compute(self, monthly_salary, membership = 'employed'):
        """
        accepts the monthly_salary and membership type
        and returns the monthly contribution

        """
        if membership == 'employed':
            if monthly_salary <= 10000:
                return 137.50
            elif monthly_salary >= 10000.01 and monthly_salary <= 39999.99:
                return ( monthly_salary * 0.0275 ) / 2
            elif monthly_salary >= 40000:
                return 1100.0
        elif membership == 'self-employed':
            if monthly_salary <= 25000:
                return 200.0
            elif monthly_salary > 25000:
                return 300.0
