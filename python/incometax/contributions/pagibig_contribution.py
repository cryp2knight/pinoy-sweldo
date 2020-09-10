from .contribution import Contribution

class PagIBIGContribution(Contribution):
    """
    Calculates the Pag IBIG monthly contribution depending
    on the user monthly income.

    """

    def __init__(self, monthly_salary = 0):
        super().__init__(monthly_salary)
        self.model = 'PAG-IBIG'
        self.monthly_contribution = self.compute(monthly_salary)

    def compute(self, monthly_salary):
        """
        accepts the monthly_salary 
        and returns the monthly contribution

        """
        if monthly_salary <= 1500:
            return monthly_salary * 0.01
        elif monthly_salary > 1500 and monthly_salary < 5000:
            return monthly_salary * 0.02
        elif monthly_salary >= 5000:
            return 100
