#include <iostream>

using namespace std;

#define ORIGINAL_EXPRESSION(A, B, C) (((A && B) || ((B || C) && (B && C)) || ((B && C) && (!(B && C)))))
#define SIMPLIFIED_EXPRESSION(A, B, C) ((A && B) || (B && C))

void printTruthTable(bool truthTable[8][3], bool circuitoutput[8],string circuitName) {
    cout << "Truth Table for " << circuitName << ":" << "\n";
    for (int i = 0; i < 8; ++i) {
        cout << truthTable[i][0] << " " << truthTable[i][1] << " " << truthTable[i][2] << " : " << circuitoutput[i] << "\n";
    }
}

void checkOutputsEqual(bool originalTruthTable[8], bool simplifiedTruthTable[8]) {
    for (int i = 0; i < 8; ++i) {
        if (originalTruthTable[i] != simplifiedTruthTable[i]) {
            cout << "Expressions are not equivalent\n";
            return ;
        }
    }
    cout << "Expressions are equivalent\n" ;
}


int main()
{
    bool A, B, C; // circuit inputs
    bool Original_Circuit_output[8];//outputs of Original Circuit
    bool Simplified_Circuit_output[8];//outputs of Simplified Circuit
    //all inputs combinations
    bool truthTable[8][3] = {
        {1, 1, 1}, 
        {1, 1, 0}, 
        {1, 0, 1}, 
        {1, 0, 0}, 
        {0, 1, 1}, 
        {0, 1, 0}, 
        {0, 0, 1}, 
        {0, 0, 0}
    };
    //satsifiable inputs for both original and simplified
     bool Satisfiable_inputs[8][3];
     bool satisfiable=0;
     int j=0;//counter for number of inputs statsify both experssion
     int x=0;//to choose which modified simplified expression to choose
     bool y;
     bool z;
    //evaluating output of original and simplified circuit
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        Original_Circuit_output[i] = ORIGINAL_EXPRESSION(A,B,C);
        Simplified_Circuit_output[i] = SIMPLIFIED_EXPRESSION(A,B,C);
    }

    printTruthTable(truthTable, Original_Circuit_output, "Original Circuit");
    printTruthTable(truthTable, Simplified_Circuit_output, "Simplified Circuit");

    checkOutputsEqual(Original_Circuit_output, Simplified_Circuit_output);

    //satisfiabillity check part
    while(!satisfiable)
    {
    for (int i = 0; i < 8; ++i)
    {
        A = truthTable[i][0];
        B = truthTable[i][1];
        C = truthTable[i][2];
        y=ORIGINAL_EXPRESSION(A,B,C);
        switch (x)
        {
            case 0:
            z=(A && B) || (B && C);
            break;
            case 1:
            z=(A || B) || (B && C); //fist modification
            break;
            case 2:
            z=(A && B) || (B || C);//second modification
            break;
            case 3:
            z=(A && B) && (B && C);//third modification
            break;  
        }
        if(y==1 && z ==1 )
        {
          satisfiable=1;
          Satisfiable_inputs[j][0]=A;
          Satisfiable_inputs[j][1]=B;
          Satisfiable_inputs[j][2]=C;
          j++;
        }
    }
    if(satisfiable)
    {
      cout<<"Satisfiable_inputs\n";
      for(int i=0;i<j;i++)
      {
        cout << Satisfiable_inputs[i][0] << " " << Satisfiable_inputs[i][1] << " " << Satisfiable_inputs[i][2] << "\n";
      }
    }
    else
    {
      x++;//modify the simplified expression
      cout<<"modify the simplified expression";
    }
    }
    return 0;
}
