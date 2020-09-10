from pandas import DataFrame
from .contributions import PhilHealthContribution, SSSContribution, PagIBIGContribution

class IncomeTax:
    
    def __init__(self, monthly_salary):
        self.sss_contribution = SSSContribution(monthly_salary)
        self.philhealth_contribution = PhilHealthContribution(monthly_salary)
        self.pagibig_contribution = PagIBIGContribution(monthly_salary)
        self.monthly_salary = monthly_salary
    
    @property
    def total_contributions(self):
        return sum([c.monthly_contribution for c in (
            self.philhealth_contribution,
            self.sss_contribution,
            self.pagibig_contribution
        )])

    @property
    def taxable_income(self):
        return self.monthly_salary - self.total_contributions

    def set_philhealth_membership(self, membership = 'employed'):
        self.philhealth_contribution = PhilHealthContribution(self.monthly_salary, membership)

    @property
    def income_tax(self):
        taxable_income = self.taxable_income
        if taxable_income <= 20833:
            return 0.0
        elif taxable_income > 20833 and taxable_income <= 33332:
            return ( taxable_income - 20833 ) * 0.20
        elif taxable_income == 33333:
            return 2500
        elif taxable_income > 33333 and taxable_income <= 66666:
            return ( taxable_income - 33333 ) * 0.25 + 2500
        elif taxable_income == 66667:
            return 10833.33
        elif taxable_income > 66667 and taxable_income <= 166666:
            return ( taxable_income - 66667 ) * 0.30 + 10833.33
        elif taxable_income == 166667:
            return 40833.33
        elif taxable_income > 166667 and taxable_income <= 666666:
            return ( taxable_income - 166667 ) * 0.32 + 40833.33
        elif taxable_income == 666667:
            return 200833.33
        elif taxable_income > 666667:
            return ( taxable_income - 666667 ) * 0.35 + 200833.33
    
    @property
    def salary_after_tax(self):
        return self.monthly_salary - self.income_tax
    
    @property
    def total_deductions(self):
        return self.income_tax + self.total_contributions
    
    @property
    def net_pay(self):
        return self.monthly_salary - self.total_deductions

    def __repr__(self):
        data = [
            ['Monthly salary', self.monthly_salary],
            ['SSS', self.sss_contribution.monthly_contribution ],
            ['PhilHealth', self.philhealth_contribution.monthly_contribution],
            ['PAGIBIG', self.pagibig_contribution.monthly_contribution],
            ['Total Contributions', self.total_contributions],
            ['Income Tax', self.income_tax],
            ['Salary after tax', self.salary_after_tax],
            ['Total deductions', self.total_deductions],
            ['Net pay', self.net_pay]
        ]
        return str(DataFrame(data, columns=['---','Php']))
