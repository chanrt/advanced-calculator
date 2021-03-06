# advanced-calculator
A freely typed calculator with advanced functions:

Current features:
1) Works with Integers, decimals, scientific constants and variables (unstable with variables as of now)
2) Both degrees and radians supported: the commands to change mode are "$ degree mode" and "$ radian mode"
3) Unary functions: factorial, reciprocal, sqrt, cbrt, log (base 10), ln (base e), trig, inverse trig
4) Binary functions: addition, subtraction, multiplication, division, modulo, power, permutation, combination, log_(base) (number)
5) Mutiple argument functions: Mean and standard deviation
6) Constants:
  a) Mathematical constants: pi, Euler's number, golden ratio 
  b) Universal constants: speed of light, Planck's constant, reduced Planck constant
  c) Atomic and nuclear constants: masses of proton, neutron and electron, Bohr radius, fine structure constant, Hartree energy, Rydberg's constant, 1st and 2nd radiation constant
  d) Physio-chemical constants: atomic mass unit, Avogadro number, Boltzmann constant, Faraday constant, universal gas constant, Stefan - Boltzmann constant, Wien's constant
  e) Electromagnetic constants: vacuum permittivity, vacuum permeability, vacuum impedance, Coulomb's constant, elementary charge, Bohr magneton, nuclear magneton, Von Klitzing constant
  
Notes:
1) Evaluates unary functions first: The unary function closest to operand is applied first. Eg: in "$ sqrt ~2", reciprocal is taken first and then sqrt is applied. All unary functions except ! (factorial) are pre-operand, hence ! has first priority and the rest of unary functions have second priority
2) Order of evaluation of binary functions: log_, modulo, permutation, combination, power, division, multiplication, addition, subtraction
3) All constants need to be preceeded by a '#". For example, "$ #c" gives you the speed of light
4) Use brackets '(' and ')' to specify the required order of evaluation

  
