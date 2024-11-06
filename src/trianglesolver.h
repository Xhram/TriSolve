// trianglesolver.h
#ifndef TRIANGLESOLVER_H
#define TRIANGLESOLVER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ti/getcsc.h>
#include <string.h>
#include <debug.h>

// Function declarations
bool attemptToSolveTri(double SideA, double SideB, double SideC, double AngleA, double AngleB, double AngleC,bool* isTri2, double* Tri1SideAOut, double* Tri1SideBOut, double* Tri1SideCOut, double* Tri1AngleAOut, double* Tri1AngleBOut, double* Tri1AngleCOut, double* Tri2SideAOut, double* Tri2SideBOut, double* Tri2SideCOut, double* Tri2AngleAOut, double* Tri2AngleBOut, double* Tri2AngleCOut);

#endif // TRIANGLESOLVER_H