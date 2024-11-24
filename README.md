# Truth Table and Circuit Equivalence Checker

This program evaluates two Boolean circuit expressions (an **original** and a **simplified** version), generates their truth tables, verifies if the outputs of both expressions are equivalent, and determines the satisfiable inputs under certain conditions.

## Features

1. **Generate Truth Tables**:
   - Computes the truth table for the original Boolean expression.
   - Computes the truth table for the simplified Boolean expression.
   
2. **Expression Equivalence Check**:
   - Compares the outputs of the original and simplified expressions for all possible inputs to determine if they are equivalent.

3. **Satisfiability Check**:
   - Finds input combinations that satisfy both the original and modified expressions.
   - Iteratively modifies the simplified expression to check satisfiability.

4. **Input Modifications**:
   - Supports multiple modifications of the simplified expression to explore satisfiability.

## How It Works

### Boolean Expressions
The following expressions are evaluated:
- **Original Expression**:  
  `((A && B) || ((B || C) && (B && C)) || ((B && C) && (!(B && C))))`
  
- **Simplified Expression**:  
  `(A && B) || (B && C)`

Additionally, alternative simplified expressions are tested to find satisfiable input conditions.

### Truth Table
The program iterates through all possible combinations of inputs (`A`, `B`, `C`) and evaluates the outputs for each expression.

### Satisfiability Check
The program determines the combinations of inputs where:
1. The original expression evaluates to `true`.
2. A selected modified version of the simplified expression also evaluates to `true`.

If no such inputs exist for the current modification, the program increments the modification index and retries with a different expression.

### Output
1. Truth tables for both original and simplified expressions.
2. Whether the original and simplified expressions are equivalent.
3. Satisfiable input combinations for the selected modification of the simplified expression.
