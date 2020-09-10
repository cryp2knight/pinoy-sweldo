from incometax.income_tax import IncomeTax

def main():
    while True:
        try:
            salary = float(input("Monthly Salary:"))
            incometax = IncomeTax(salary)
            print(incometax)
            break
        except ValueError as e:
            print(e)

if __name__ == "__main__":
    main()