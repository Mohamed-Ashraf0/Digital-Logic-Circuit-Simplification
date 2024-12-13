#include <iostream>
using namespace std;

#define ORIGINAL_EXPRESSION(A, B, C) (((!( A || !(B))) &&  (A && B)) && C )
#define SIMPLIFIED_EXPRESSION(A, B, C) !A && A && B && C
//by changeing 1 gate of unmodified circuit
#define MODIFIED_ORIGINAL_EXPRESSION(A, B, C) (((!( A || !(B))) ||  (A && B)) && C )
#define MODIFIED_SIMPLIFIED_EXPRESSION(A, B, C) B && C
#define ORIGINAL_CIRCUIT 1
#define MODIFIED_CIRCUIT 0

// all inputs combinations
bool truthTable[8][3] = {
    {1, 1, 1},
    {1, 1, 0},
    {1, 0, 1},
    {1, 0, 0},
    {0, 1, 1},
    {0, 1, 0},
    {0, 0, 1},
    {0, 0, 0}};

void printTruthTable(bool truthTable[8][3], bool circuitoutput[8], string circuitName)
{
    cout << "Truth Table for " << circuitName << ":" << "\n";
    for (int i = 0; i < 8; ++i)
    {
        cout << truthTable[i][0] << " " << truthTable[i][1] << " " << truthTable[i][2] << " : " << circuitoutput[i] << "\n";
    }
}

bool check_equivalance(bool status)
{
    cout << "checking equivalance:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool not_equivalent = false; // outputs of Simplified Circuit

    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];

        if (status) // modified or unmodified
        {
            Original_Circuit_output[i] = ORIGINAL_EXPRESSION(A, B, C);
            Simplified_Circuit_output[i] = SIMPLIFIED_EXPRESSION(A, B, C);
        }
        else
        {
            Original_Circuit_output[i] = MODIFIED_ORIGINAL_EXPRESSION(A, B, C);
            Simplified_Circuit_output[i] = MODIFIED_SIMPLIFIED_EXPRESSION(A, B, C);
        }

        if (Original_Circuit_output[i] != Simplified_Circuit_output[i])
        {
            not_equivalent = true;
        }
    }

    printTruthTable(truthTable, Original_Circuit_output, "Original Circuit");
    printTruthTable(truthTable, Simplified_Circuit_output, "Simplified Circuit");

    if (not_equivalent)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool check_Satisfiability(bool status)
{
    cout << "checking Satisfiability:-\n";
    bool A, B, C;                      // circuit inputs
    bool Original_Circuit_output[8];   // outputs of Original Circuit
    bool Simplified_Circuit_output[8]; // outputs of Simplified Circuit
    bool first_time = true;

    // evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];

        if (status)
        {
            Original_Circuit_output[i] = ORIGINAL_EXPRESSION(A, B, C);
            Simplified_Circuit_output[i] = SIMPLIFIED_EXPRESSION(A, B, C);
        }
        else
        {
            Original_Circuit_output[i] = MODIFIED_ORIGINAL_EXPRESSION(A, B, C);
            Simplified_Circuit_output[i] = MODIFIED_SIMPLIFIED_EXPRESSION(A, B, C);
        }

        if (Original_Circuit_output[i] == true && Simplified_Circuit_output[i] == true)
        {
            if (first_time)
            {
                cout << "Satisfiable\nSatisfiable inputs:-\n";
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

int main()
{
    // equivalance check part
    if (check_equivalance(ORIGINAL_CIRCUIT))
    {
        cout << "Expressions are equivalent.\n";
    }
    else
    {
        cout << "Expressions are not equivalent.\n";
    }
    cout << "\n";

    // satisfiabillity check part
    if (check_Satisfiability(ORIGINAL_CIRCUIT))
    {
        return 0; // finish program
    }
    else
    {
        cout << "\nTrying modified circuit...\n\n";

        if (check_Satisfiability(MODIFIED_CIRCUIT))
        {
            cout << "\n";

            if (check_equivalance(MODIFIED_CIRCUIT))
            {
                cout << "Expressions are equivalent.\n";
            }
            else
            {
                cout << "Expressions are not equivalent.\n";
            }
        }
        else
        {
            cout << "Changed gate but still not Satisfiable\n";
        }
    }

    return 0;
}
