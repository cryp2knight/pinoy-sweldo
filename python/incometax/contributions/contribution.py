"""
    Pinoy-Sweldo a module for computing Income Tax in the Philippines.
    :copyright: 2020-Present by Daniel De Castro.
    :license: MIT, see LICENSE for more details.
"""

class Contribution:
    """
    Base class for different contributions
    """
    def __init__(self, monthly_salary = 0):
        self.validate_income(monthly_salary)
        self.monthly_contribution = None
        self.model = '--'
    
    def validate_income(self, monthly_salary):
        if not isinstance(monthly_salary, (int, float)):
            raise ValueError({'monthly_salary':
                            'Invalid input, must be a number.'})
        if monthly_salary < 0:
            raise ValueError({'monthly_salary': 
                            'Invalid input, must be greater than equal to 0'})
        self.monthly_salary = monthly_salary
    
    @property
    def salary_after_contribution(self):
        return  self.monthly_salary - self.monthly_contribution

    def __repr__(self):
        return f'[{self.model}] <{self.monthly_salary}>'