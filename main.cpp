#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// all inputs combinations
bool truthTable[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
    };
void substituteVariables(string &expression, bool A, bool B, bool C) {
    for (char &ch : expression) {
        if (ch == 'A') {
            ch = A ? '1' : '0';
        } else if (ch == 'B') {
            ch = B ? '1' : '0';
        } else if (ch == 'C') {
            ch = C ? '1' : '0';
        }
    }
}
char evaluateOperation(char operand1, char operand2, char operation) {
   if (operation == '&') {
        return (operand1 == '1' && operand2 == '1') ? '1' : '0';
    }
    else if (operation == '|') {
        return (operand1 == '1' || operand2 == '1') ? '1' : '0';
    }
}
char NOT(char operand)
{
    return operand=='1'?'0':'1';

}
bool evaluateBooleanExpression(const string &expression) {
    stack<char> operators;
    char first_operand,second_operand,operation;
    bool first_operand_turn=false;
    bool operation_turn=false;
    bool second_operand_turn=false;
    bool first_operand_found=false;
    bool operation_found=false;
    bool second_operand_found=false;
    for (size_t i = 0; i < expression.size(); i++) {
        char ch = expression[i];
        if (isspace(ch)) continue;// Ignore whitespace
        if (ch == ')') {
            bool first_operand_turn=true;
            while (operators.top() != '(')
            {
                if(first_operand_turn)
                {
                first_operand = operators.top();
                operators.pop();
                if(first_operand=='1' ||first_operand=='0' )
                {
                    first_operand_turn=false;
                    first_operand_found=true;
                    operation_turn=true;
                    continue;
                }
                }
                 if(operation_turn)
                {
                operation = operators.top();
                operators.pop();
                if(operation=='&' ||operation=='|' )
                {
                    operation_turn=false;
                    operation_found=true;
                    second_operand_turn=true;
                    continue;
                }
                }
                 if(second_operand_turn)
                {
                second_operand = operators.top();
                operators.pop();
                if(second_operand=='1' ||second_operand=='0' )
                {
                    second_operand_turn=false;
                    second_operand_found=true;
                    continue;
                }
                }
            }
            operators.pop();
            if(first_operand_found && !operation_found && !second_operand_found)
            {
                char operation = operators.top();
                operators.pop();
                if(operation=='!')
                {
                    operators.push(NOT(first_operand));
                }
            }
            else if(first_operand_found && operation_found && second_operand_found)
            {
                    operators.push(evaluateOperation(first_operand,second_operand,operation));
            }
            first_operand_found=false;
            operation_found=false;
            second_operand_found=false;
            first_operand_turn=false;
            operation_turn=false;
            second_operand_turn=false;
        } else{
             operators.push(ch);
        }
    }
    return operators.top()=='1'? true : false;
}
void printTruthTable(bool circuitoutput[8], string circuitName)
{
    cout << "Truth Table for " << circuitName << ":" << "\n";
    for (int i = 0; i < 8; ++i)
    {
        cout << truthTable[i][0] << " " << truthTable[i][1] << " " << truthTable[i][2] << " : " << circuitoutput[i] << "\n";
    }
}

bool check_equivalance(string OriginalcircuitExpression,string SimplifiedcircuitExpression)
{
    cout << "checking equivalance:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool not_equivalent = false; // outputs of Simplified Circuit
    string temp1,temp2;
    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        temp1=OriginalcircuitExpression;
        temp2=SimplifiedcircuitExpression;
        substituteVariables(temp1, A, B, C);
        substituteVariables(temp2, A, B, C);
        Original_Circuit_output[i]=evaluateBooleanExpression(temp1);
        Simplified_Circuit_output[i]=evaluateBooleanExpression(temp2);
        if (Original_Circuit_output[i] != Simplified_Circuit_output[i])
        {
            not_equivalent = true;
        }
    }
    printTruthTable( Original_Circuit_output, "Original Circuit");
    printTruthTable( Simplified_Circuit_output, "Simplified Circuit");

    if (not_equivalent)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool check_Satisfiability(string OriginalcircuitExpression,string SimplifiedcircuitExpression)
{
    cout << "checking Satisfiability:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool first_time = true;
    string temp1,temp2;
    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        temp1=OriginalcircuitExpression;
        temp2=SimplifiedcircuitExpression;
        substituteVariables(temp1, A, B, C);
        substituteVariables(temp2, A, B, C);
        Original_Circuit_output[i]=evaluateBooleanExpression(temp1);
        Simplified_Circuit_output[i]=evaluateBooleanExpression(temp2);

        if (Original_Circuit_output[i] ==true && Simplified_Circuit_output[i]==true)
        {
             if (first_time)
            {
                cout << "Satisfiable.\nSatisfiable inputs:-\nA B C\n";
                first_time = false;
            }
            cout << A << " " << B << " " << C << "\n";
        }
    }
    if (first_time)
    {
        cout << "not Satisfiable\n";
        return false;
    }
    else
    {
        return true;
    }
}
int main() {
    string OriginalcircuitExpression;
    string SimplifiedcircuitExpression;
    bool A, B, C;
    cout << "Enter the Original circuit expression(e.g., ((!((A|!(B)))&(A&B))&C)  ):";
    getline(cin, OriginalcircuitExpression);
    cout << "Enter the Simplified circuit expression(e.g., (((!(A)&A)&B)&C)  ): ";
    getline(cin, SimplifiedcircuitExpression);
    if (check_equivalance(OriginalcircuitExpression,SimplifiedcircuitExpression))
    {
        cout << "Expressions are equivalent.\n";
    }
    else
    {
        cout << "Expressions are not equivalent.\n";
    }
    cout << "\n";
     // ask user to change gate in circuit until reach satisfiable one
    while (!check_Satisfiability(OriginalcircuitExpression,SimplifiedcircuitExpression))
    {
        cout << "\nmodify a gate in the circuit please :-\n\n";
        cout << "Enter the Original modified circuit expression(e.g., ((!((A|!(B)))|(A&B))&C)  ):";
        getline(cin, OriginalcircuitExpression);
        cout << "Enter the Simplified modified circuit expression(e.g., (B&C) ): ";
        getline(cin, SimplifiedcircuitExpression);
    }

     if (check_equivalance(OriginalcircuitExpression,SimplifiedcircuitExpression))
    {
        cout << "Expressions are equivalent.\n";
    }
    else
    {
         cout << "Expressions are not equivalent.\n";
    }

    return 0;
}
