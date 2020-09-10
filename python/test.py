import unittest

from incometax.contributions import SSSContribution, PagIBIGContribution, PhilHealthContribution

class TestSSSContribution(unittest.TestCase):

    def test_lowest_contribution(self):
        c = SSSContribution(2000)
        self.assertEqual(c.monthly_contribution, 80)

    def test_other_contribution(self):
        c = SSSContribution(8251)
        self.assertEqual(c.monthly_contribution, 340)

    def test_largest_contribution(self):
        c = SSSContribution(20000)
        self.assertEqual(c.monthly_contribution, 800)

class TestPhilHealthContribution(unittest.TestCase):

    def test_value_error_for_invalid_membership(self):
        self.assertRaises(ValueError, PhilHealthContribution, 200, 'test')
    
    def test_contribution_value_employed(self):
        self.assertEqual(
            PhilHealthContribution(9000).monthly_contribution,
            137.50
            )
        
        self.assertEqual(
            PhilHealthContribution(11000).monthly_contribution,
            (11000*0.0275)/2
            )
        self.assertEqual(
            PhilHealthContribution(43000).monthly_contribution,
            1100
            )

    def test_contribution_value_self_employed(self):
        self.assertEqual(
            PhilHealthContribution(20000, 'self-employed').monthly_contribution,
            200
            )
        
        self.assertEqual(
            PhilHealthContribution(26000, 'self-employed').monthly_contribution,
            300
            )


if __name__ == '__main__':
    unittest.main()