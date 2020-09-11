<div align="center">
  <h1>Pinoy Sweldo</h1>
  <img src="https://img.shields.io/badge/Java-8-red?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Python-3.6-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/C%2B%2B-14-yellow?style=for-the-badge">
  <a href="https://mit-license.org" target="_blank"><img src="https://img.shields.io/badge/license-MIT-blue.svg?longCache=true&style=for-the-badge" alt="License"></a> 
  <p>A module in Java, Python, and C++ for computing income tax and contributions.</p> <p>My homework for <b>IT 331</b></p>
</div>


## Usage
### Java
```java
try {
  IncomeTax tax = new IncomeTax(20000);
  System.out.print(tax.toRepresentation());
}catch(Exception e){
  System.out.print(e.getMessage());
}
```
#### Compile and run
```bash
javac Project.java && java Project
```
### C++
```cpp
IncomeTax tax = IncomeTax(20000);
cout << tax.toRepresentation();
```
#### Compile and run
```bash
g++ sweldo.cpp -o sweldo && ./sweldo
```
### Python 3
```py
incometax = IncomeTax(20000)
print(incometax)
```
#### Run
```bash
python3 main.py
```

## Tests
### Python
```bash
python3 test.py
```

## TODO
> Write unit tests

> Other classification for contributions