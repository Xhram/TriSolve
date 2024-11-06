#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ti/getcsc.h>
#include <string.h>
#include <debug.h>

double rad(double deg) {
    return deg * (M_PI / 180);
}

double deg(double rad) {
    return rad * (180 / M_PI);
}


bool attemptToSolveTri(double SideA, double SideB, double SideC, double AngleA, double AngleB, double AngleC,bool* isTri2, double* Tri1SideAOut, double* Tri1SideBOut, double* Tri1SideCOut, double* Tri1AngleAOut, double* Tri1AngleBOut, double* Tri1AngleCOut, double* Tri2SideAOut, double* Tri2SideBOut, double* Tri2SideCOut, double* Tri2AngleAOut, double* Tri2AngleBOut, double* Tri2AngleCOut){
    bool givenSideA = SideA > 0;
    bool givenSideB = SideB > 0;
    bool givenSideC = SideC > 0;
    bool givenAngleA = AngleA > 0;
    bool givenAngleB = AngleB > 0;
    bool givenAngleC = AngleC > 0;
    
    //SSSAAA - side side side angle angle angle
    if(givenSideA && givenSideB && givenSideC && givenAngleA && givenAngleB && givenAngleC){
        if(SideA + SideB <= SideC + 1 || SideA + SideC <= SideB + 1 || SideB + SideC <= SideA + 1){
            return false;
        }
        double sumOfAngles = AngleA + AngleB + AngleC;
        if(sumOfAngles > 181 || sumOfAngles < 179){
            return false;
        }
        *isTri2 = false;
        *Tri1SideAOut = SideA;
        *Tri1SideBOut = SideB;
        *Tri1SideCOut = SideC;
        *Tri1AngleAOut = AngleA;
        *Tri1AngleBOut = AngleB;
        *Tri1AngleCOut = AngleC;
        return true;
    }
    
    //SSS - side side side
    if(givenSideA && givenSideB && givenSideC && !givenAngleA && !givenAngleB && !givenAngleC){
        *isTri2 = false;

        *Tri1SideAOut = SideA;
        *Tri1SideBOut = SideB;
        *Tri1SideCOut = SideC;
        *Tri1AngleAOut = acos((pow(SideB,2) + pow(SideC,2) - pow(SideA,2))/(2*SideB*SideC)) * 180/M_PI;
        *Tri1AngleBOut = acos((pow(SideA,2) + pow(SideC,2) - pow(SideB,2))/(2*SideA*SideC)) * 180/M_PI;
        *Tri1AngleCOut = 180 - *Tri1AngleAOut - *Tri1AngleBOut;
        return true;
    }
    //SAS - side angle side
    if((givenSideA && givenAngleC && givenSideB) || (givenSideA && givenAngleB && givenSideC) || (givenSideB && givenAngleA && givenSideC)){
        double tempSideA = 0;
        double tempSideB = 0;
        double tempSideC = 0;
        double tempAngleA = 0;
        double tempAngleB = 0;
        double tempAngleC = 0;
        if(givenSideA && givenAngleC && givenSideB){
            tempSideA = SideA;
            tempAngleB = AngleC;
            tempSideC = SideB;
        } else if(givenSideA && givenAngleB && givenSideC){
            tempSideA = SideA;
            tempAngleB = AngleB;
            tempSideC = SideC;
        } else if(givenSideB && givenAngleA && givenSideC){
            tempSideA = SideB;
            tempAngleB = AngleA;
            tempSideC = SideC;
        }
        *isTri2 = false;
        tempSideB = sqrt(pow(tempSideA,2) + pow(tempSideC,2) - 2*tempSideA*tempSideC*cos(tempAngleB*M_PI/180));
        tempAngleC = acos((pow(tempSideA,2) + pow(tempSideB,2) - pow(tempSideC,2))/(2*tempSideA*tempSideB)) * 180/M_PI;
        tempAngleA = acos((pow(tempSideB,2) + pow(tempSideC,2) - pow(tempSideA,2))/(2*tempSideB*tempSideC)) * 180/M_PI;
        if(givenSideA && givenAngleC && givenSideB){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleB;
        } else if(givenSideA && givenAngleB && givenSideC){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleC;
        } else if(givenSideB && givenAngleA && givenSideC){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleC;
        }
        return true;
    }
    //ASA - angle side angle
    if((givenAngleA && givenSideB && givenAngleC) || (givenAngleA && givenSideC && givenAngleB) || (givenAngleB && givenSideA && givenAngleC)){
        double tempSideA = 0;
        double tempSideB = 0;
        double tempSideC = 0;
        double tempAngleA = 0;
        double tempAngleB = 0;
        double tempAngleC = 0;
        if (givenAngleA && givenSideB && givenAngleC){
            tempAngleA = AngleA;
            tempSideB = SideB;
            tempAngleC = AngleC;
        }else if (givenAngleA && givenSideC && givenAngleB){
            tempAngleA = AngleA;
            tempSideB = SideC;
            tempAngleC = AngleB;
        } else if (givenAngleB && givenSideA && givenAngleC){
            tempAngleA = AngleB;
            tempSideB = SideA;
            tempAngleC = AngleC;
        }
        tempAngleB = 180 - tempAngleA - tempAngleC;
        tempSideA = (tempSideB/sin(tempAngleB*M_PI/180)) * sin(tempAngleA*M_PI/180);
        tempSideC = (tempSideB/sin(tempAngleB*M_PI/180)) * sin(tempAngleC*M_PI/180);
        *isTri2 = false;
        if(givenAngleA && givenSideB && givenAngleC){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleC;
        } else if(givenAngleA && givenSideC && givenAngleB){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleB;
        } else if(givenAngleB && givenSideA && givenAngleC){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleC;
        }
        return true;
        
    }
    //AAS - angle angle side
    if((givenAngleA && givenAngleB && givenSideA) || (givenAngleA && givenAngleC && givenSideA) || (givenAngleB && givenAngleC && givenSideB) || (givenAngleB && givenAngleA && givenSideB) || (givenAngleC && givenAngleB && givenSideC) || (givenAngleC && givenAngleA && givenSideC)){
        double tempSideA = 0;
        double tempSideB = 0;
        double tempSideC = 0;
        double tempAngleA = 0;
        double tempAngleB = 0;
        double tempAngleC = 0;
        if(givenAngleA && givenAngleB && givenSideA){
            tempAngleA = AngleA;
            tempAngleB = AngleB;
            tempSideA = SideA;
        } else if(givenAngleA && givenAngleC && givenSideA){
            tempAngleA = AngleA;
            tempAngleB = AngleC;
            tempSideA = SideA;
        } else if(givenAngleB && givenAngleC && givenSideB){
            tempAngleA = AngleB;
            tempAngleB = AngleC;
            tempSideA = SideB;
        } else if(givenAngleB && givenAngleA && givenSideB){
            tempAngleA = AngleB;
            tempAngleB = AngleA;
            tempSideA = SideB;
        } else if(givenAngleC && givenAngleB && givenSideC){
            tempAngleA = AngleC;
            tempAngleB = AngleB;
            tempSideA = SideC;
        } else if(givenAngleC && givenAngleA && givenSideC){
            tempAngleA = AngleC;
            tempAngleB = AngleA;
            tempSideA = SideC;
        }
        tempAngleC = 180 - tempAngleA - tempAngleB;
        tempSideB = (tempSideA/sin(tempAngleA*M_PI/180)) * sin(tempAngleB*M_PI/180);
        tempSideC = (tempSideA/sin(tempAngleA*M_PI/180)) * sin(tempAngleC*M_PI/180);

        *isTri2 = false;
        if(givenAngleA && givenAngleB && givenSideA){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleC;
        } else if(givenAngleA && givenAngleC && givenSideA){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleB;
        } else if(givenAngleB && givenAngleC && givenSideB){
            *Tri1SideAOut = tempSideC;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleC;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleB;
        } else if(givenAngleB && givenAngleA && givenSideB){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleC;
        } else if(givenAngleC && givenAngleB && givenSideC){
            *Tri1SideAOut = tempSideC;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideA;
            *Tri1AngleAOut = tempAngleC;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleA;
        } else if(givenAngleC && givenAngleA && givenSideC){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideA;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleA;
        }
        return true;
    }
    //ASS - Anagle Side Side 
    if((givenAngleA && givenSideC && givenSideA) || (givenAngleA && givenSideB && givenSideA) || (givenAngleB && givenSideA && givenSideB) || (givenAngleB && givenSideC && givenSideB) || (givenAngleC && givenSideB && givenSideC) || (givenAngleC && givenSideA && givenSideC)){
        double tempSideA = 0;
        double tempSideB = 0;
        double tempSideC = 0;
        double tempAngleA = 0;
        double tempAngleB = 0;
        double tempAngleC = 0;
        double tempTri2SideA = 0;
        double tempTri2SideB = 0;
        double tempTri2SideC = 0;
        double tempTri2AngleA = 0;
        double tempTri2AngleB = 0;
        double tempTri2AngleC = 0;
        bool tempIsTri2exsit = false;
        if(givenAngleA && givenSideC && givenSideA){
            tempAngleA = AngleA;
            tempSideB = SideC;
            tempSideA = SideA;
        } else if (givenAngleA && givenSideB && givenSideA){
            tempAngleA = AngleA;
            tempSideB = SideB;
            tempSideA = SideA;
        } else if (givenAngleB && givenSideA && givenSideB){
            tempAngleA = AngleB;
            tempSideB = SideA;
            tempSideA = SideB;
        } else if (givenAngleB && givenSideC && givenSideB){
            tempAngleA = AngleB;
            tempSideB = SideC;
            tempSideA = SideB;
        } else if (givenAngleC && givenSideB && givenSideC){
            tempAngleA = AngleC;
            tempSideB = SideB;
            tempSideA = SideC;
        } else if (givenAngleC && givenSideA && givenSideC){
            tempAngleA = AngleC;
            tempSideB = SideA;
            tempSideA = SideC;
        }

        double tempAngleAInDegrees = tempAngleA;
        double tempSideOppositeAngleA = tempSideA;
        double cosAngleA = cos(rad(tempAngleAInDegrees));
        double sideBCosAngleA = tempSideB * cosAngleA;
        double discriminant = sideBCosAngleA * sideBCosAngleA - tempSideB * tempSideB + tempSideOppositeAngleA * tempSideOppositeAngleA;

        double sideC1, sideC2;
        if (discriminant < 0) {
            sideC1 = -1;
            sideC2 = -1;
        } else {
            sideC1 = sideBCosAngleA - sqrt(discriminant);
            sideC2 = sideBCosAngleA + sqrt(discriminant);
        }

        if (sideC1 > 0 && sideC2 > 0) {
            double angleB1 = deg(acos((sideC1 * sideC1 + tempSideOppositeAngleA * tempSideOppositeAngleA - tempSideB * tempSideB) / (2 * sideC1 * tempSideOppositeAngleA)));
            double angleB2 = deg(acos((sideC2 * sideC2 + tempSideOppositeAngleA * tempSideOppositeAngleA - tempSideB * tempSideB) / (2 * sideC2 * tempSideOppositeAngleA)));
            double angleC1 = deg(acos((tempSideOppositeAngleA * tempSideOppositeAngleA + tempSideB * tempSideB - sideC1 * sideC1) / (2 * tempSideOppositeAngleA * tempSideB)));
            double angleC2 = deg(acos((tempSideOppositeAngleA * tempSideOppositeAngleA + tempSideB * tempSideB - sideC2 * sideC2) / (2 * tempSideOppositeAngleA * tempSideB)));

            tempSideA = tempSideOppositeAngleA;
            tempSideC = sideC1;
            tempAngleB = angleB1;
            tempAngleC = angleC1;

            tempTri2SideA = tempSideOppositeAngleA;
            tempTri2SideB = tempSideB;
            tempTri2SideC = sideC2;
            tempTri2AngleA = tempAngleA;
            tempTri2AngleB = angleB2;
            tempTri2AngleC = angleC2;

            tempIsTri2exsit = true;
        } else if (sideC1 > 0) {
            double angleB1 = deg(acos((sideC1 * sideC1 + tempSideOppositeAngleA * tempSideOppositeAngleA - tempSideB * tempSideB) / (2 * sideC1 * tempSideOppositeAngleA)));
            double angleC1 = deg(acos((tempSideOppositeAngleA * tempSideOppositeAngleA + tempSideB * tempSideB - sideC1 * sideC1) / (2 * tempSideOppositeAngleA * tempSideB)));

            tempSideA = tempSideOppositeAngleA;
            tempSideC = sideC1;
            tempAngleB = angleB1;
            tempAngleC = angleC1;

            tempIsTri2exsit = false;
        } else if (sideC2 > 0) {
            double angleB2 = deg(acos((sideC2 * sideC2 + tempSideOppositeAngleA * tempSideOppositeAngleA - tempSideB * tempSideB) / (2 * sideC2 * tempSideOppositeAngleA)));
            double angleC2 = deg(acos((tempSideOppositeAngleA * tempSideOppositeAngleA + tempSideB * tempSideB - sideC2 * sideC2) / (2 * tempSideOppositeAngleA * tempSideB)));

            tempSideA = tempSideOppositeAngleA;
            tempSideC = sideC2;
            tempAngleB = angleB2;
            tempAngleC = angleC2;

            tempIsTri2exsit = false;
        } else {
            dbg_printf("TRIANGLE DOES NOT EXIST\n");
            return false;
        }
        *isTri2 = tempIsTri2exsit;
        
        if(givenAngleA && givenSideC && givenSideA){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleB;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideA;
                *Tri2SideBOut = tempTri2SideC;
                *Tri2SideCOut = tempTri2SideB;
                *Tri2AngleAOut = tempTri2AngleA;
                *Tri2AngleBOut = tempTri2AngleC;
                *Tri2AngleCOut = tempTri2AngleB;
            }
        } else if (givenAngleA && givenSideB && givenSideA){
            *Tri1SideAOut = tempSideA;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleA;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleC;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideA;
                *Tri2SideBOut = tempTri2SideB;
                *Tri2SideCOut = tempTri2SideC;
                *Tri2AngleAOut = tempTri2AngleA;
                *Tri2AngleBOut = tempTri2AngleB;
                *Tri2AngleCOut = tempTri2AngleC;
            }
        } else if (givenAngleB && givenSideA && givenSideB){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideC;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleC;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideB;
                *Tri2SideBOut = tempTri2SideA;
                *Tri2SideCOut = tempTri2SideC;
                *Tri2AngleAOut = tempTri2AngleB;
                *Tri2AngleBOut = tempTri2AngleA;
                *Tri2AngleCOut = tempTri2AngleC;
            }
        } else if (givenAngleB && givenSideC && givenSideB){
            *Tri1SideAOut = tempSideC;
            *Tri1SideBOut = tempSideA;
            *Tri1SideCOut = tempSideB;
            *Tri1AngleAOut = tempAngleC;
            *Tri1AngleBOut = tempAngleA;
            *Tri1AngleCOut = tempAngleB;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideC;
                *Tri2SideBOut = tempTri2SideA;
                *Tri2SideCOut = tempTri2SideB;
                *Tri2AngleAOut = tempTri2AngleC;
                *Tri2AngleBOut = tempTri2AngleA;
                *Tri2AngleCOut = tempTri2AngleB;
            }
        } else if (givenAngleC && givenSideB && givenSideC){
            *Tri1SideAOut = tempSideC;
            *Tri1SideBOut = tempSideB;
            *Tri1SideCOut = tempSideA;
            *Tri1AngleAOut = tempAngleC;
            *Tri1AngleBOut = tempAngleB;
            *Tri1AngleCOut = tempAngleA;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideC;
                *Tri2SideBOut = tempTri2SideB;
                *Tri2SideCOut = tempTri2SideA;
                *Tri2AngleAOut = tempTri2AngleC;
                *Tri2AngleBOut = tempTri2AngleB;
                *Tri2AngleCOut = tempTri2AngleA;
            }
        } else if (givenAngleC && givenSideA && givenSideC){
            *Tri1SideAOut = tempSideB;
            *Tri1SideBOut = tempSideC;
            *Tri1SideCOut = tempSideA;
            *Tri1AngleAOut = tempAngleB;
            *Tri1AngleBOut = tempAngleC;
            *Tri1AngleCOut = tempAngleA;
            if(tempIsTri2exsit){
                *Tri2SideAOut = tempTri2SideB;
                *Tri2SideBOut = tempTri2SideC;
                *Tri2SideCOut = tempTri2SideA;
                *Tri2AngleAOut = tempTri2AngleB;
                *Tri2AngleBOut = tempTri2AngleC;
                *Tri2AngleCOut = tempTri2AngleA;
            }
        }
        return true;
    }


    dbg_printf("Most likely it can't solve this type of triangle\n");
    return false;

}


