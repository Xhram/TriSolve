#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ti/getcsc.h>
#include <string.h>
#include <debug.h>
#include "globals.h" 
#include "tinyexpr.h"


//exsample input: "5.4+5"+piChar+"/2+52^("+sqrtChar+"4-3)+6-33"+degreeChar+"45'14.5\"" = -14.5
bool EvalMath(char* input,double* resultOut){
    int inputLength = strlen(input);
    int parenthesisOpenAndCloseCount = 0;
    int piCount = 0;
    int sqrtCount = 0;


    for (int i = 0; i < inputLength; i++)
    {
        if (input[i] == piChar) { // piChar
            piCount++;
        } else if (input[i] == sqrtChar) { // sqrtChar
            sqrtCount++;
        } else if (input[i] == '(') {
            parenthesisOpenAndCloseCount++;
        } else if (input[i] == ')') {
            parenthesisOpenAndCloseCount--;
        }
    }
    if(parenthesisOpenAndCloseCount != 0){return false;}
    char exspresionWithFunctionNames[inputLength + piCount + sqrtCount * 3];
    int j = 0;
    for(int i = 0; i < inputLength; i++){
        if(input[i] == piChar){
            exspresionWithFunctionNames[j] = 'p';
            exspresionWithFunctionNames[j + 1] = 'i';
            j += 2;
        } else if(input[i] == sqrtChar){
            exspresionWithFunctionNames[j] = 's';
            exspresionWithFunctionNames[j + 1] = 'q';
            exspresionWithFunctionNames[j + 2] = 'r';
            exspresionWithFunctionNames[j + 3] = 't';
            j += 4;
        } else {
            exspresionWithFunctionNames[j] = input[i];
            j++;
        }
    }
    

    *resultOut = te_interp(exspresionWithFunctionNames, 0);
    return true;
}