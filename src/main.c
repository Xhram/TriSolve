#include <ti/getcsc.h>
#include <sys/util.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <debug.h>
#include "globals.h"

#include "mathprint.h"
#include "mathParseing.h"
#include "trianglesolver.h"





//All things will be stored in Degrees

//Side A - Red
double SideA = 2;
double AngleA = 60;
//Side B - Green
double SideB = 2;
double AngleB = 60;
//Side C - Blue
double SideC = 2;
double AngleC = 60;
//tri 1 storage
//Side A - Red
double Tri1SideA = 2;
double Tri1AngleA = 60;
//Side B - Green
double Tri1SideB = 2;
double Tri1AngleB = 60;
//Side C - Blue
double Tri1SideC = 2;
double Tri1AngleC = 60;
//tri 2 storage
//Side A - Red
double Tri2SideA = 2;
double Tri2AngleA = 60;
//Side B - Green
double Tri2SideB = 2;
double Tri2AngleB = 60;
//Side C - Blue
double Tri2SideC = 2;
double Tri2AngleC = 60;

double ScaleX = 100;
double ScaleY = 100;
double ShiftX = 0;
double ShiftY = 0;

uint16_t SafeBoxWidth = 250;
uint8_t SafeBoxHeight = 190;
uint16_t SafeBoxX = 35;
uint8_t SafeBoxY = 15;

double PointCX, PointCY, PointAX, PointAY, PointBX, PointBY = 0;

bool isInDegMode = true;
bool inEditMode = false;
bool showingTri1 = true;
bool doesTri2exist = false;
//func declerations---
void initFonts();
void updateKeys();
void initKeys();
void loadTri();
void drawTipBar();
int clamp(int num, int min, int max);
int max_int(int num1, int num2);
double max(double num1, double num2);
double max3(double num1, double num2, double num3);
double max4(double num1, double num2, double num3, double num4);
double min(double num1, double num2);
double min3(double num1, double num2, double num3);
double min4(double num1, double num2, double num3, double num4);
double avg(double num1, double num2);
double dist(double x1, double y1, double x2, double y2);
void calcTrianglePoints();
void calcScaleMod();
void drawTriangle();
void double_to_compact(char *buffer, size_t size, double value, int significant_figures);
void setValueOfRenderingTir();
void lableTriangle();
void drawEditScreen();
char keyPressToChar(uint8_t *key);
void deleteChar(char userInput[6][20], uint8_t *curserPos, uint8_t *curserLimit);
void addChar(char userInput[6][20], char pressedChar, uint8_t *curserPos, uint8_t *curserLimit);
void propertyEditingMenu();
void editTriMenu();
void infoScreen();




//fonts



void initFonts(){
    gfx_SetFontData(TextData);
    gfx_SetFontSpacing(TextSpacingData);
}


//---------key borad system-------------------
uint8_t old_kb_Data[8];
uint8_t press_kb_Data[8];

void updateKeys(){
    for(int i = 0;i<8;i++){
        old_kb_Data[i] = kb_Data[i];
    }
    kb_Scan();
    for(int i = 0;i<8;i++){
        press_kb_Data[i] = (old_kb_Data[i] ^ kb_Data[i]) & kb_Data[i];

    }
}
void initKeys(){
    for(int i = 0;i<8;i++){
        old_kb_Data[i] = 0b11111111;
        press_kb_Data[i] = 0b00000000;
    }
    kb_Scan();
}
//---------key borad system-------------------


void loadTri(){
    Tri1SideA = 12.000000;
    Tri1SideB = 7.250364;
    Tri1SideC = 7.000000;
    Tri1AngleA = 114.710304;
    Tri1AngleB = 33.289691;
    Tri1AngleC = 32.000000;

    Tri2SideA = 12.000000;
    Tri2SideB = 13.102790;
    Tri2SideC = 7.000000;
    Tri2AngleA = 65.289695;
    Tri2AngleB = 82.710304;
    Tri2AngleC = 32.000000;


    doesTri2exist = true;

}

void drawTipBar(){
    gfx_SetTextScale(2,2);
    gfx_SetColor(gfx_RGBTo1555(0,0,0));
    gfx_HorizLine_NoClip(0,220,320);
    for (int i = 1; i <= 4; i++) {
        gfx_VertLine_NoClip(i*(320/5),220,20);
    }
    gfx_SetTextBGColor(nullTextColor);
    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("Exit",5,224);
    if(showingTri1){
        if(!doesTri2exist){
            gfx_SetColor(disabledColor);
            gfx_FillRectangle_NoClip(257,221,63,19);
        }
        gfx_PrintStringXY("Tri1",262,224);
    } else {
        gfx_PrintStringXY("Tri2",262,224);
    }
    if(inEditMode){
        gfx_PrintStringXY("Solv",133,224);
        if(showingTri1){
            gfx_SetColor(selectColor);
        } else {
            gfx_SetColor(disabledColor);
        }
        gfx_FillRectangle_NoClip(65,221,63,19);
        gfx_PrintStringXY("Set",74,224);
        gfx_SetColor(disabledColor);
        gfx_FillRectangle_NoClip(193,221,63,19);

    } else {
        gfx_PrintStringXY("Edit",134,224);
        gfx_PrintStringXY("Info",65,224);

    }
    if(isInDegMode){
        gfx_PrintStringXY("Deg",200,224);
    } else {
        gfx_PrintStringXY("Rad",200,224);
    }
    if(press_kb_Data[1] == kb_Trace && !inEditMode){
        isInDegMode = !isInDegMode;
    }
}
int clamp(int num,int min,int max){
    if(num < min){
        return min;
    }
    if(num > max){
        return max;
    }
    return num;
}
int max_int(int num1,int num2){
    if(num1 < num2){
        return num2;
    }
    return num1;
}
double max(double num1,double num2){
    if(num1 < num2){
        return num2;
    }
    return num1;
}
double max3(double num1,double num2,double num3){
    return max(max(num1,num2),num3);
}
double max4(double num1, double num2, double num3, double num4) {
    return max(max(num1, num2), max(num3, num4));
}
double min(double num1,double num2){
    if(num1 > num2){
        return num2;
    }
    return num1;
}
double min3(double num1,double num2,double num3){
    return min(min(num1,num2),num3);
}
double min4(double num1, double num2, double num3, double num4) {
    return min(min(num1, num2), min(num3, num4));
}
double avg(double num1,double num2){
    return (num1 + num2)/2;
}
double dist(double x1,double y1,double x2,double y2){
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
}
void calcTrianglePoints(){
    PointAX = PointAY = PointBX = PointBY = PointCX = PointCY = 0;
    PointBX = (SafeBoxX + (SafeBoxWidth / 2)) - ((SideC*ScaleX)/2);
    PointBY = SafeBoxY + SafeBoxHeight;
    PointCX = SideA * cos(-AngleB*M_PI/180.0) * ScaleX;
    PointCY = SideA * sin(-AngleB*M_PI/180.0) * ScaleY;
    PointCX += PointBX;
    PointCY += PointBY;
    double angle = -AngleB+180-AngleC;
    PointAX = SideB * cos(angle*M_PI/180.0) * ScaleX;
    PointAY = SideB * sin(angle*M_PI/180.0) * ScaleY;
    PointAX += PointCX;
    PointAY += PointCY;

    //ajusting for bad tri
    double adjust = avg(PointBX,PointAX) - (SafeBoxX + (SafeBoxWidth / 2));
    PointAX -= adjust;
    PointBX -= adjust;
    PointCX -= adjust;
}
void calcScaleMod(){
    setValueOfRenderingTir();
    ScaleX = 1;
    ScaleY = 1;
    calcTrianglePoints();
    double maxX,maxY,minX,minY;
    maxX = max3(PointAX,PointBX,PointCX);
    maxY = max3(PointAY,PointBY,PointCY);
    minX = min3(PointAX,PointBX,PointCX);
    minY = min3(PointAY,PointBY,PointCY);
    if(doesTri2exist){
        showingTri1 = !showingTri1;
        setValueOfRenderingTir();
        calcTrianglePoints();
        maxX = max4(PointAX,PointBX,PointCX,maxX);
        maxY = max4(PointAY,PointBY,PointCY,maxY);
        minX = min4(PointAX,PointBX,PointCX,minX);
        minY = min4(PointAY,PointBY,PointCY,minY);
        showingTri1 = !showingTri1;
        setValueOfRenderingTir();
        calcTrianglePoints();
    }
    ScaleX = SafeBoxWidth/(maxX-minX + 1);
    ScaleY = SafeBoxHeight/(maxY-minY);
    ShiftX = (SafeBoxX + (SafeBoxWidth / 2)) - avg(maxX,minX);

}
void drawTriangle(){
    gfx_SetColor(gfx_RGBTo1555(0,0,200));

    gfx_Line(PointAX + ShiftX,PointAY,PointBX + ShiftX,PointBY);
    gfx_SetColor(224);
    gfx_Line(PointCX + ShiftX,PointCY,PointBX + ShiftX,PointBY);
    gfx_SetColor(7);
    gfx_Line(PointAX + ShiftX,PointAY,PointCX + ShiftX,PointCY);
    
}
void double_to_compact(char *buffer, size_t size, double value, int significant_figures) {
    if (size == 0 || significant_figures <= 0) return; // No space to write

    // Handle special cases
    if (isnan(value)) {
        if (size > 3) {
            buffer[0] = 'n'; buffer[1] = 'a'; buffer[2] = 'n';
            buffer[3] = '\0';
        }
        return;
    } else if (isinf(value)) {
        if (size > 3) {
            buffer[0] = value < 0 ? '-' : '+';
            buffer[1] = 'i'; buffer[2] = 'n'; buffer[3] = 'f';
            buffer[4] = '\0';
        }
        return;
    }

    // Initialize index for the output buffer
    int idx = 0;
    double abs_value = fabs(value);

    // Check whether to use normal or scientific notation
    if (abs_value < 1e-3 || abs_value >= 1e6) {
        // Using scientific notation
        int exponent = 0;

        // Handle negative values
        if (value < 0) {
            if (idx < (int)size) {
                buffer[idx++] = '-';
            }
            value = -value;
        }

        // Normalize the value to scientific notation
        while (value >= 10.0) {
            value /= 10.0;
            exponent++;
        }
        while (value < 1.0) {
            value *= 10.0;
            exponent--;
        }

        // Convert the significant figures
        int first_digit = (int)value;
        if (idx < (int)size) {
            buffer[idx++] = '0' + first_digit;  // First digit before the decimal point
        }

        // Convert fractional part up to the desired significant figures
        if (idx < (int)size) {
            buffer[idx++] = '.';
        }
        value -= first_digit;

        // Add digits up to the desired significant figures
        for (int i = 0; i < significant_figures - 1 && idx < (int)size; ++i) {
            value *= 10;
            int digit = (int)value;
            if (idx < (int)size) {
                buffer[idx++] = '0' + digit;
            }
            value -= digit;
        }

        // Add exponent notation
        if (idx < (int)size) {
            buffer[idx++] = 'e';
        }

        // Add exponent sign and value
        if (exponent < 0) {
            if (idx < (int)size) buffer[idx++] = '-';
            exponent = -exponent;
        } else {
            if (idx < (int)size) buffer[idx++] = '+';
        }

        // Add exponent value
        if (exponent >= 10 && idx < (int)size) {
            buffer[idx++] = '0' + (exponent / 10);
            if (idx < (int)size) buffer[idx++] = '0' + (exponent % 10);
        } else if (idx < (int)size) {
            buffer[idx++] = '0' + exponent;
        }
    } else {
        // Using normal representation
        // Process the integer part
        int integer_part = (int)value;
        if (integer_part == 0) {
            buffer[idx++] = '0'; // Handle zero
        } else {
            // Convert integer part
            int temp = integer_part;
            int digits[10];
            int digit_count = 0;

            // Extract digits in reverse
            while (temp > 0 && digit_count < 10) {
                digits[digit_count++] = temp % 10;
                temp /= 10;
            }

            // Write digits to buffer in the correct order
            for (int i = digit_count - 1; i >= 0 && idx < (int)size; --i) {
                buffer[idx++] = '0' + digits[i];
            }
        }

        // Process the fractional part
        if (idx < (int)size) {
            buffer[idx++] = '.';
        }
        value -= integer_part;

        // Add fractional part up to the desired significant figures
        for (int i = 0; i < significant_figures - 1 && idx < (int)size; ++i) {
            value *= 10;
            int digit = (int)value;
            if (idx < (int)size) {
                buffer[idx++] = '0' + digit;
            }
            value -= digit;
        }

        // Remove trailing zeros if they exist after significant figures
        while (idx > 0 && buffer[idx - 1] == '0') --idx;
        if (idx > 0 && buffer[idx - 1] == '.') --idx;  // Remove trailing decimal point
    }

    // Null-terminate the string
    if (idx < (int)size) buffer[idx] = '\0';
    else buffer[size - 1] = '\0';  // Ensure null-termination within target size
}
void setValueOfRenderingTir(){
    if(showingTri1){
        SideA = Tri1SideA;
        SideB = Tri1SideB;
        SideC = Tri1SideC;
        AngleA = Tri1AngleA;
        AngleB = Tri1AngleB;
        AngleC = Tri1AngleC;
    } else {
        SideA = Tri2SideA;
        SideB = Tri2SideB;
        SideC = Tri2SideC;
        AngleA = Tri2AngleA;
        AngleB = Tri2AngleB;
        AngleC = Tri2AngleC;
    }
}

void lableTriangle(){
    double angle;
    gfx_SetTextScale(1,1);
    gfx_SetTextBGColor(223);
    //Side A
    gfx_SetTextFGColor(224);
    char Number[10];
    char SideALable[12];
    
    double_to_compact(Number, sizeof(Number), SideA,3);
    snprintf(SideALable, sizeof(SideALable),"a=%s",Number);
    gfx_PrintStringXY(SideALable,clamp(avg(PointCX,PointBX) + ShiftX - 6 * strlen(SideALable),2,320 - (strlen(SideALable) * 8 + 2)),avg(PointBY,PointCY));

    //Angle A
    angle = AngleA;
    if(!isInDegMode){
        angle*=M_PI/180;
    }
    snprintf(SideALable, sizeof(SideALable),"A=%3.2f",angle);
    gfx_PrintStringXY(SideALable,clamp(PointAX + ShiftX - 6 * strlen(SideALable) - 16,2,320 - (strlen(SideALable) * 8 + 2)),PointAY - 10);
    
    //Side B
    gfx_SetTextFGColor(7);
    char SideBLable[12];
    
    double_to_compact(Number, sizeof(Number), SideB,3);
    snprintf(SideBLable, sizeof(SideBLable),"b=%s",Number);
    gfx_PrintStringXY(SideBLable,clamp(avg(PointCX,PointAX) + ShiftX + 5,2,320 - (strlen(SideBLable) * 8 + 2)),avg(PointAY,PointCY));

    //Angle B
    angle = AngleB;
    if(!isInDegMode){
        angle*=M_PI/180;
    }
    snprintf(SideBLable, sizeof(SideBLable),"B=%3.2f",angle);
    gfx_PrintStringXY(SideBLable,clamp(PointBX + ShiftX + 6,2,320 - (strlen(SideBLable) * 8 + 2)),PointBY - 10);

    //Side C
    gfx_SetTextFGColor(28);
    char SideCLable[12];

    double_to_compact(Number, sizeof(Number), SideC,3);
    snprintf(SideCLable, sizeof(SideCLable),"c=%s",Number);
    gfx_PrintStringXY(SideCLable,clamp(avg(PointBX,PointAX) + ShiftX - 6 * strlen(SideCLable)/2,2,320 - (strlen(SideCLable) * 8 + 2)),avg(PointAY,PointBY) - 10);

    //Angle C
    angle = AngleC;
    if(!isInDegMode){
        angle*=M_PI/180;
    }
    snprintf(SideCLable, sizeof(SideCLable),"C=%3.2f",angle);
    gfx_PrintStringXY(SideCLable,clamp(PointCX + ShiftX - 6 * strlen(SideCLable)/2,2,320 - (strlen(SideCLable) * 8 + 2)),PointCY + 10);
}
void drawEditScreen(){
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(0,0,320,25);
    gfx_SetTextFGColor(222);
    gfx_SetTextScale(2,2);
    gfx_PrintStringXY("Edit Triangle:",5,6);
    gfx_SetTextFGColor(0);
    for(int i = 1;i<6;i++){
        gfx_HorizLine_NoClip(0,33 * (i+1) - 8,320);
    }


}

bool in2ndMode = false;

char keyPressToChar(uint8_t *key){
    if(key[3] == kb_0){
        return '0';
    }
    if(key[3] == kb_1){
        return '1';
    }
    if(key[3] == kb_7){
        return '7';
    }
    if(key[3] == kb_4){
        return '4';
    }
    if(key[3] == kb_5){
        return '5';
    }
    if(key[3] == kb_8){
        return '8';
    }
    if(key[4] == kb_2){
        return '2';
    }
    if(key[4] == kb_5){
        return '5';
    }
    if(key[4] == kb_8){
        return '8';
    }
    if(key[5] == kb_3){
        return '3';
    }
    if(key[5] == kb_6){
        return '6';
    }
    if(key[5] == kb_9){
        return '9';
    }
    if(key[6] == kb_Add){
        return '+';
    }
    if(key[6] == kb_Sub){
        return '-';
    }
    if(key[6] == kb_Mul){
        return '*';
    }
    if(key[6] == kb_Div){
        return '/';
    }
    if(key[6] == kb_Power && !in2ndMode){
        return '^';
    }
    if(key[6] == kb_Power && in2ndMode){
        return piChar;
    }
    if (key[4] == kb_LParen) {
        return '(';
    }
    if (key[5] == kb_RParen) {
        return ')';
    }
    if(key[2] == kb_Square && in2ndMode){
        return sqrtChar;
    }
    if (key[4] == kb_DecPnt) {
        return '.';
    }
    if(key[2] == kb_Square && !in2ndMode){
        return squareChar;
    }

    return '\0';
}


char PropertyLabels[6][9] = {"Angle A=","Angle B=","Angle C=","Side a=","Side b=","Side c="};
char PropertyValues[2][6][40];
double PropertyNumaricValues[6];//x==0? -> not set
uint8_t selected;
bool hasChangedValues;

void deleteChar(char userInput[6][20],uint8_t* curserPos,uint8_t* curserLimit){
    if(*curserPos != *curserLimit){
        for(int i = *curserPos;i<*curserLimit;i++){
            if((i+1)/19 < 6){
                userInput[i/19][i%19] = userInput[(i+1)/19][(i+1)%19];
            } else {
                userInput[i/19][i%19] = '\0';
            }
        }
        (*curserLimit)--;
    }
}

void addChar(char userInput[6][20], char pressedChar, uint8_t* curserPos, uint8_t* curserLimit){
    if(*curserPos == *curserLimit){
        (*curserLimit)++;
        userInput[(int)(*curserPos)/19][(int)(*curserPos)%19] = pressedChar;
        userInput[(int)(*curserPos)/19][(int)(*curserPos)%19 + 1] = '\0';
        (*curserPos)++;
    } else {
        userInput[(int)(*curserPos)/19][(int)(*curserPos)%19] = pressedChar;
        (*curserPos)++;
    }
}



void propertyEditingMenu(){
    char title[22];
    char userInput[6][20] = {"","","","","",""};
    uint8_t curserPos = 0;
    uint8_t tick = 0;
    uint8_t curserLimit = 0;
    char uparrow[2] = {upArrowChar,'\0'};
    snprintf(title, sizeof(title), "Editing %s",PropertyLabels[selected]);


    do {
        updateKeys();
        tick += 15;
        gfx_FillScreen(255);
        //draw title
        gfx_SetColor(0);
        gfx_FillRectangle_NoClip(0,0,320,25);
        gfx_SetTextFGColor(53);
        gfx_SetTextScale(2,2);
        gfx_PrintStringXY(title,5,6);

        gfx_SetTextFGColor(255);
        gfx_SetTextScale(1,1);
        gfx_PrintStringXY((isInDegMode)?"deg":"rad",320 - 8*3,2);
        if(in2ndMode){
            gfx_PrintStringXY("2nd",320 - 8*3,2 + 10);
        }
        gfx_SetTextFGColor(0);


        //handle input
        gfx_SetTextScale(2,2);
        gfx_SetColor(0);
        gfx_SetMonospaceFont(8);
        for(int i = 0;i<6;i++){
            gfx_PrintStringXY(userInput[i],5,30 + 24 * i);
        }
        if(tick < 130){
            gfx_FillRectangle_NoClip(5 + (curserPos%19) * 16,27 + 24 * (curserPos/19),16,20);
            if(in2ndMode){
                gfx_SetTextFGColor(255);
                gfx_PrintStringXY(uparrow,5 + (curserPos%19) * 16,30 + 24 * (curserPos/19));
                gfx_SetTextFGColor(0);
            } 
        }
        


        if (press_kb_Data[7] == kb_Up && curserPos >= 19) {
            curserPos -= 19;
        }
        if (press_kb_Data[7] == kb_Down && curserPos < 5 * 19) {
            curserPos += 19;
        }
        if (press_kb_Data[7] == kb_Left && curserPos > 0) {
            curserPos--;
        }
        if (press_kb_Data[7] == kb_Right && curserPos < 6 * 19 - 1) {
            curserPos++;
        }

        if(curserPos > curserLimit){
            curserPos = curserLimit;
        }

        

        //trigger on input of char
        char pressedChar = keyPressToChar(press_kb_Data);
        if(pressedChar != '\0' && curserPos < 6 * 19){
            
            
            if(pressedChar != sqrtChar && pressedChar != squareChar){
                if(userInput[curserPos/19][curserPos%19] == sqrtChar){
                    curserPos++;
                    deleteChar(userInput,&curserPos,&curserLimit);
                    curserPos--;
                    addChar(userInput, pressedChar, &curserPos, &curserLimit);
                } else if(userInput[curserPos/19][curserPos%19] == '(' && userInput[max_int(curserPos - 1,0)/19][max_int(curserPos-1,0)%19] == sqrtChar) {
                    deleteChar(userInput,&curserPos,&curserLimit);
                    curserPos--;
                    addChar(userInput, pressedChar, &curserPos, &curserLimit);
                } else {
                    addChar(userInput, pressedChar, &curserPos, &curserLimit);

                }
                
            } else if(curserPos < 6 * 19 - 1){
                
                if(curserPos != curserLimit){
                    for(int i = curserLimit;i>curserPos;i--){
                        userInput[(i+1)/19][(i+1)%19] = userInput[i/19][i%19];
                    }
                    

                }
                if(pressedChar == sqrtChar){
                    addChar(userInput, pressedChar, &curserPos, &curserLimit);
                    addChar(userInput, '(', &curserPos, &curserLimit);
                } else if(pressedChar == squareChar){
                    addChar(userInput, '^', &curserPos, &curserLimit);
                    addChar(userInput, '2', &curserPos, &curserLimit);
                }
                if(curserPos != curserLimit){curserLimit++;}
            }
            in2ndMode = false;
        }
        if(press_kb_Data[1] == kb_Del){
            if(userInput[curserPos/19][curserPos%19] == sqrtChar){
                deleteChar(userInput,&curserPos,&curserLimit);
            } else if(userInput[curserPos/19][curserPos%19] == '(' && userInput[max_int(curserPos - 1,0)/19][max_int(curserPos-1,0)%19] == sqrtChar){
                deleteChar(userInput,&curserPos,&curserLimit);
                curserPos--;
                deleteChar(userInput,&curserPos,&curserLimit);
            }
            deleteChar(userInput,&curserPos,&curserLimit);

            in2ndMode = false;
            
        }
        if(press_kb_Data[6] == kb_Clear){
            for (int i = 0; i < 6; i++) {
                userInput[i][0] = '\0';
            }
            curserLimit = 0;
            curserPos = 0;
            in2ndMode = false;
        }
        if(press_kb_Data[1] == kb_2nd){
            in2ndMode = !in2ndMode;
        }

        //Angle Menu`
        if(press_kb_Data[3] == kb_Apps && in2ndMode && canUseDegreeSymbolMenu){
            in2ndMode = false;
            uint8_t selectedAngle = 0;
            char angleLabebs[3][4] = {{'1',':',degreeChar},"2:'","3:\""};
            do {
                updateKeys();
                if(press_kb_Data[1] == kb_2nd){
                    in2ndMode = !in2ndMode;
                }

                gfx_FillScreen(255);
                gfx_SetTextScale(2,2);
                //draw title
                gfx_SetMonospaceFont(0);
                gfx_SetColor(0);
                gfx_FillRectangle_NoClip(0,0,320,25);
                gfx_SetTextFGColor(53);
                gfx_SetTextScale(2,2);
                gfx_PrintStringXY(title,5,6);
                gfx_SetTextFGColor(0);

                gfx_SetMonospaceFont(8);
                gfx_SetTextFGColor(255);
                gfx_SetColor(0);
                gfx_FillRectangle_NoClip(3,28,16*5 + 3,19);
                gfx_PrintStringXY("ANGLE",5,30);
                gfx_SetTextFGColor(0);
                gfx_SetMonospaceFont(0);
                for(int i = 0;i<3;i++){
                    if(selectedAngle == i){
                        gfx_SetTextBGColor(selectColor);
                    } else {
                        gfx_SetTextBGColor(nullTextColor);
                    }
                    gfx_PrintStringXY(angleLabebs[i],5,30 + 24 * (i+1));
                }


                gfx_SetTextBGColor(nullTextColor);

                if(press_kb_Data[7] == kb_Up && selectedAngle > 0){
                    selectedAngle--;
                }
                if(press_kb_Data[7] == kb_Down && selectedAngle < 2){
                    selectedAngle++;
                }

                if(press_kb_Data[6] == kb_Enter || press_kb_Data[3] == kb_1 || press_kb_Data[4] == kb_2 || press_kb_Data[5] == kb_3){
                    bool quickSelect = press_kb_Data[6] != kb_Enter;
                    if(quickSelect){
                        if(press_kb_Data[3] == kb_1){
                            pressedChar = degreeChar;
                        } else if (press_kb_Data[4] == kb_2){
                            pressedChar = '\'';
                        } else {
                            pressedChar = '\"';
                        }
                    } else {
                        if(selectedAngle == 0){
                            pressedChar = degreeChar;
                        } else if (selectedAngle == 1){
                            pressedChar = '\'';
                        } else {
                            pressedChar = '\"';
                        }

                    }
                    
                    
                    if(curserPos < 6 * 19){
                        if(curserPos == curserLimit){
                            curserLimit++;
                            userInput[curserPos/19][curserPos%19] = pressedChar;
                            userInput[curserPos/19][curserPos%19 + 1] = '\0';
                            curserPos++;
                        } else {
                            userInput[curserPos/19][curserPos%19] = pressedChar;
                            curserPos++;
                        }
                    }
                    in2ndMode = false;
                    break;
                }




                gfx_BlitBuffer();




            } while (!(in2ndMode && press_kb_Data[1] == kb_Mode) && press_kb_Data[6] != kb_Clear && press_kb_Data[1] != kb_Yequ);
            updateKeys();
        }




        gfx_SetMonospaceFont(0);

        //draw tip bar
        gfx_SetTextScale(2,2);
        gfx_SetColor(0);
        gfx_HorizLine_NoClip(0,220,320);
        gfx_VertLine_NoClip(320/2,220,20);
        gfx_SetTextFGColor(0);
        gfx_PrintStringXY("Discard[f1]",3,223);
        gfx_PrintStringXY("Save[f5]",185,223);


        
        if(press_kb_Data[1] == kb_Graph || press_kb_Data[6] == kb_Enter){
            double result = 0;
            char totalInput[6*19 + 1];
            for (int i = 0; i < 6*19; i++)
            {
                totalInput[i] = userInput[i/19][i%19];
            }
            totalInput[6*19] = '\0';
            
            if(EvalMath(totalInput,&result) && !isnan(result)){
                if(!hasChangedValues){
                    hasChangedValues = true;
                    for(int i = 0;i<6;i++){
                        PropertyNumaricValues[i] = 0;
                        snprintf(PropertyValues[0][i], sizeof(PropertyValues[0][i]), "? unset ?");
                        snprintf(PropertyValues[1][i], sizeof(PropertyValues[1][i]), "! can not be set !");

                    }
                }

                snprintf(PropertyValues[0][selected], sizeof(PropertyValues[0][selected]), "%f",result);
                PropertyNumaricValues[selected] = result;
                break;
            } else {
                dbg_printf("error\n");
                gfx_SetColor(255);
                gfx_FillRectangle_NoClip(10,10,300,220);
                gfx_SetColor(0);
                gfx_Rectangle_NoClip(10,10,300,220);
                gfx_SetTextScale(3,3);
                gfx_SetMonospaceFont(0);
                gfx_PrintStringXY("Error:",100,20);
                gfx_HorizLine_NoClip(10,42,300);
                gfx_HorizLine_NoClip(10,188,300);
                gfx_HorizLine_NoClip(10,110,300);
                gfx_SetTextScale(2,2);
                
                gfx_PrintStringXY("An error occured",15,50);
                gfx_PrintStringXY("when parsing your",15,70);
                gfx_PrintStringXY("math expression.",15,90);
                gfx_PrintStringXY("Remeber:",15,120);
                gfx_SetTextScale(1,1);
                gfx_PrintStringXY("-All \"(\" must have a \")\"",15,140);
                gfx_PrintStringXY("-No implicit multiplication",15,150);
                gfx_SetTextScale(2,2);
                gfx_PrintStringXY("Press [y=]",15,190);
                gfx_PrintStringXY("to continue...",15,210);

                gfx_BlitBuffer();

                do
                {
                    updateKeys();
                } while (press_kb_Data[1] != kb_Yequ && press_kb_Data[6] != kb_Enter);
                updateKeys();
            }
        } else {
            gfx_BlitBuffer();

        }



    } while (press_kb_Data[1] != kb_Yequ);
    updateKeys();
}


void editTriMenu(){
    selected = 0;
    inEditMode = true;
    hasChangedValues = false;
    
    if(!doesTri2exist){
        for(int i = 0;i<6;i++){
            snprintf(PropertyValues[1][i], sizeof(PropertyValues[1][i]), "! no other triangle exists !");
        }
    }
    //tri 1
    PropertyNumaricValues[0] = Tri1AngleA;
    PropertyNumaricValues[1] = Tri1AngleB;
    PropertyNumaricValues[2] = Tri1AngleC;
    PropertyNumaricValues[3] = Tri1SideA;
    PropertyNumaricValues[4] = Tri1SideB;
    PropertyNumaricValues[5] = Tri1SideC;


    //tri 1
    snprintf(PropertyValues[0][3], sizeof(PropertyValues[0][3]), "%f", Tri1SideA);
    snprintf(PropertyValues[0][4], sizeof(PropertyValues[0][4]), "%f", Tri1SideB);
    snprintf(PropertyValues[0][5], sizeof(PropertyValues[0][5]), "%f", Tri1SideC);
    if(isInDegMode){
        snprintf(PropertyValues[0][0], sizeof(PropertyValues[0][0]), "%f", Tri1AngleA);
        snprintf(PropertyValues[0][1], sizeof(PropertyValues[0][1]), "%f", Tri1AngleB);
        snprintf(PropertyValues[0][2], sizeof(PropertyValues[0][2]), "%f", Tri1AngleC);
    } else {
        snprintf(PropertyValues[0][0], sizeof(PropertyValues[0][0]), "%f", Tri1AngleA * M_PI/180);
        snprintf(PropertyValues[0][1], sizeof(PropertyValues[0][1]), "%f", Tri1AngleB * M_PI/180);
        snprintf(PropertyValues[0][2], sizeof(PropertyValues[0][2]), "%f", Tri1AngleC * M_PI/180);
    }
    //tri 2
    snprintf(PropertyValues[1][3], sizeof(PropertyValues[1][3]), "%f", Tri2SideA);
    snprintf(PropertyValues[1][4], sizeof(PropertyValues[1][4]), "%f", Tri2SideB);
    snprintf(PropertyValues[1][5], sizeof(PropertyValues[1][5]), "%f", Tri2SideC);
    if(isInDegMode){
        snprintf(PropertyValues[1][0], sizeof(PropertyValues[1][0]), "%f", Tri2AngleA);
        snprintf(PropertyValues[1][1], sizeof(PropertyValues[1][1]), "%f", Tri2AngleB);
        snprintf(PropertyValues[1][2], sizeof(PropertyValues[1][2]), "%f", Tri2AngleC);
    } else {
        snprintf(PropertyValues[1][0], sizeof(PropertyValues[1][0]), "%f", Tri2AngleA * M_PI/180);
        snprintf(PropertyValues[1][1], sizeof(PropertyValues[1][1]), "%f", Tri2AngleB * M_PI/180);
        snprintf(PropertyValues[1][2], sizeof(PropertyValues[1][2]), "%f", Tri2AngleC * M_PI/180);
    }

    do {
        updateKeys();
    

        gfx_FillScreen(255);
        drawEditScreen();

        gfx_SetTextFGColor(255);
        gfx_SetTextScale(1,1);
        gfx_PrintStringXY((isInDegMode)?"deg":"rad",320 - 8*3,2);
        if(in2ndMode){
            gfx_PrintStringXY("2nd",320 - 8*3,2 + 10);
        }
        gfx_SetTextFGColor(0);

        


        //part of drawing code
        
        
        gfx_SetTextScale(1,1);
        for(int i = 0;i<6;i++){
            if(showingTri1 && selected == i){
                gfx_SetTextBGColor(selectColor);
            } else {
                gfx_SetTextBGColor(nullTextColor);
            }
            gfx_PrintStringXY(PropertyLabels[i],5,33 * (i+1) - 4);
            gfx_PrintStringXY(PropertyValues[(showingTri1)?0:1][i],5,33 * (i+1) + 7);

        }
        
        gfx_SetTextBGColor(nullTextColor);




        if(showingTri1 && press_kb_Data[7] == kb_Up && selected > 0){
            selected--;
            in2ndMode = false;
        }
        if(showingTri1 && press_kb_Data[7] == kb_Down && selected < 5){
            selected++;
            in2ndMode = false;
        }
        if(press_kb_Data[1] == kb_2nd){
            in2ndMode = !in2ndMode;
        }
        

        if((press_kb_Data[1] == kb_Window || press_kb_Data[6] == kb_Enter) && showingTri1){
            in2ndMode = false;
            propertyEditingMenu();
            
        }
        if(press_kb_Data[6] == kb_Clear && !in2ndMode && showingTri1){
            PropertyNumaricValues[selected] = 0;
            snprintf(PropertyValues[0][selected], sizeof(PropertyValues[0][selected]), "? unset ?");
            hasChangedValues = true;
        }
        if(press_kb_Data[6] == kb_Clear && in2ndMode){
            for(int i = 0;i<6;i++){
                PropertyNumaricValues[i] = 0;
                snprintf(PropertyValues[0][i], sizeof(PropertyValues[0][i]), "? unset ?");
                snprintf(PropertyValues[1][i], sizeof(PropertyValues[1][i]), "! can not be set !");
            }
            hasChangedValues = true;
            in2ndMode = false;
        }
        if(press_kb_Data[1] == kb_Graph && doesTri2exist){
            showingTri1 = !showingTri1;
            in2ndMode = false;
        }


        drawTipBar();

        if(press_kb_Data[1] == kb_Zoom){
            in2ndMode = false;
            bool validTri = attemptToSolveTri(PropertyNumaricValues[3],PropertyNumaricValues[4],PropertyNumaricValues[5],(isInDegMode)?PropertyNumaricValues[0]:(PropertyNumaricValues[0] * 180 / M_PI),(isInDegMode)?PropertyNumaricValues[1]:(PropertyNumaricValues[1] * 180 / M_PI),(isInDegMode)?PropertyNumaricValues[2]:(PropertyNumaricValues[2] * 180 / M_PI),&doesTri2exist,&Tri1SideA,&Tri1SideB,&Tri1SideC,&Tri1AngleA,&Tri1AngleB,&Tri1AngleC,&Tri2SideA,&Tri2SideB,&Tri2SideC,&Tri2AngleA,&Tri2AngleB,&Tri2AngleC);
            dbg_printf("\n\n\n\n\nTRI SOLVE:\n");
            
            dbg_printf("validTri: %d\n",validTri);
            dbg_printf("Input values:\n");
            dbg_printf("AngleA: %f\n", PropertyNumaricValues[0]);
            dbg_printf("AngleB: %f\n", PropertyNumaricValues[1]);
            dbg_printf("AngleC: %f\n", PropertyNumaricValues[2]);
            dbg_printf("SideA: %f\n", PropertyNumaricValues[3]);
            dbg_printf("SideB: %f\n", PropertyNumaricValues[4]);
            dbg_printf("SideC: %f\n", PropertyNumaricValues[5]);
            dbg_printf("\n-----Output values:-----\n");
            dbg_printf("Is Tri2 Valid: %d\n", doesTri2exist);
            dbg_printf("Tri1AngleA: %f\n", Tri1AngleA);
            dbg_printf("Tri1AngleB: %f\n", Tri1AngleB);
            dbg_printf("Tri1AngleC: %f\n", Tri1AngleC);
            dbg_printf("Tri1SideA: %f\n", Tri1SideA);
            dbg_printf("Tri1SideB: %f\n", Tri1SideB);
            dbg_printf("Tri1SideC: %f\n", Tri1SideC);
            dbg_printf("\n\n-----TRI 2-----\n");
            dbg_printf("Tri2AngleA: %f\n", Tri2AngleA);
            dbg_printf("Tri2AngleB: %f\n", Tri2AngleB);
            dbg_printf("Tri2AngleC: %f\n", Tri2AngleC);
            dbg_printf("Tri2SideA: %f\n", Tri2SideA);
            dbg_printf("Tri2SideB: %f\n", Tri2SideB);
            dbg_printf("Tri2SideC: %f\n", Tri2SideC);

            if(validTri){
                if(!doesTri2exist){
                    Tri2AngleA = 0;
                    Tri2AngleB = 0;
                    Tri2AngleC = 0;
                    Tri2SideA = 0;
                    Tri2SideB = 0;
                    Tri2SideC = 0;
                    showingTri1 = true;
                }
                setValueOfRenderingTir();
                break;
                
            } else {
                dbg_printf("error\n");
                gfx_SetColor(255);
                gfx_FillRectangle_NoClip(10,10,300,220);
                gfx_SetColor(0);
                gfx_Rectangle_NoClip(10,10,300,220);
                gfx_SetTextScale(3,3);
                gfx_SetMonospaceFont(0);
                gfx_PrintStringXY("Error:",100,20);
                gfx_HorizLine_NoClip(10,42,300);
                gfx_HorizLine_NoClip(10,188,300);
                gfx_HorizLine_NoClip(10,130,300);
                gfx_SetTextScale(2,2);
                
                gfx_PrintStringXY("An error occured",15,50);
                gfx_PrintStringXY("when solving for",15,70);
                gfx_PrintStringXY("your triangle.",15,90);
                gfx_PrintStringXY("No Trinagle Found",15,110);
                gfx_PrintStringXY("Remeber:",15,135);
                gfx_SetTextScale(1,1);
                gfx_PrintStringXY("-You need at least 3 variables to solve",15,155);
                gfx_PrintStringXY("-If a value is negative it will",15,165);
                gfx_PrintStringXY("be considered as unset",15+7+7,175);
                gfx_SetTextScale(2,2);
                gfx_PrintStringXY("Press [y=]",15,190);
                gfx_PrintStringXY("to continue...",15,210);

                gfx_BlitBuffer();

                do
                {
                    updateKeys();
                } while (press_kb_Data[1] != kb_Yequ && press_kb_Data[6] != kb_Enter);
                updateKeys();
            }


        } else {
            gfx_BlitBuffer();

        }



    } while (press_kb_Data[1] != kb_Yequ);
    updateKeys();
    inEditMode = false;
}
void infoScreen(){
    gfx_BlitBuffer();
    gfx_FillScreen(255);
    gfx_SetColor(0);
    gfx_FillRectangle_NoClip(0,0,320,25);
    gfx_SetTextFGColor(222);
    gfx_PrintStringXY("Info:",5,6);
    gfx_SetTextFGColor(0);
    gfx_SetTextScale(2,2);
    gfx_PrintStringXY("Codded By:",5,30);
    gfx_PrintStringXY("Isaac Ruiz Kahle",5,50);
    gfx_SetTextScale(1,1);
    gfx_PrintStringXY("In Spite of:Mis.Le",3,70);
    gfx_PrintStringXY("Thanks to:Norbert Zych(did a bit),ce tool chain",3,80);
    gfx_PrintStringXY("devs(didnt help to much),and Tinyexpr(Parses)",3,90);
    gfx_HorizLine_NoClip(0,105,320);
    gfx_PrintStringXY("Triangle 1 Area:",5,110);
    double semiPermiter = (Tri1SideA + Tri1SideB + Tri1SideC) / 2;
    double area = sqrt(semiPermiter * (semiPermiter - Tri1SideA) * (semiPermiter - Tri1SideB) * (semiPermiter - Tri1SideC));
    char Number[30];
    snprintf(Number,sizeof(Number),"%f",area);
    gfx_PrintStringXY(Number,5,120);
    double perimiter = (Tri1SideA + Tri1SideB + Tri1SideC);
    snprintf(Number,sizeof(Number),"%f",perimiter);
    gfx_PrintStringXY("Triangle 1 Perimiter:",5,130);
    gfx_PrintStringXY(Number,5,140);
    gfx_HorizLine_NoClip(0,155,320);


    gfx_PrintStringXY("Triangle 2 Area:",5,160);
    if(doesTri2exist){
        semiPermiter = (Tri2SideA + Tri2SideB + Tri2SideC) / 2;
        area = sqrt(semiPermiter * (semiPermiter - Tri2SideA) * (semiPermiter - Tri2SideB) * (semiPermiter - Tri2SideC));
        perimiter = (Tri2SideA + Tri2SideB + Tri2SideC);

    } else {
        semiPermiter = 0;
        area = 0;
        perimiter = 0;
    }
    snprintf(Number,sizeof(Number),"%f",area);
    gfx_PrintStringXY(Number,5,170);
    snprintf(Number,sizeof(Number),"%f",perimiter);
    gfx_PrintStringXY("Triangle 2 Perimiter:",5,180);
    gfx_PrintStringXY(Number,5,190);
    gfx_HorizLine_NoClip(0,205,320);
    gfx_SetTextScale(2,2);
    gfx_PrintStringXY("Exit[y=]",110,215);
    gfx_SetTextScale(1,1);
    gfx_PrintStringXY(version,2,240 - 9);


    gfx_BlitBuffer();
    do
    {
        updateKeys();

    } while (press_kb_Data[1] != kb_Yequ && press_kb_Data[6] != kb_Clear);
    updateKeys();
}

int main(void)
{
    dbg_printf("Loading TriSolve in debug mode\n");
    initKeys();
    loadTri();
    setValueOfRenderingTir();

    //font loading
    initFonts();
    


    /* Initialize graphics drawing */
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetTextTransparentColor(nullTextColor);
    

    calcScaleMod();
    calcTrianglePoints();
    //editTriMenu();
    uint8_t tick = 0;
    do {
        updateKeys();
        tick++;
        if(tick == 0){
            calcScaleMod();
            calcTrianglePoints();
        }

        gfx_FillScreen(255);


        drawTriangle();
        lableTriangle();
        drawTipBar();



        if(press_kb_Data[1] == kb_Window){
            infoScreen();
            calcScaleMod();
            calcTrianglePoints();
        }


        gfx_BlitBuffer();
        
        if(press_kb_Data[1] == kb_Zoom){
            editTriMenu();
            
            calcScaleMod();
            calcTrianglePoints();
        }
        if(press_kb_Data[1] == kb_Graph && doesTri2exist){
            showingTri1 = !showingTri1;
            setValueOfRenderingTir();
            calcScaleMod();
            calcTrianglePoints();
        }


    } while (press_kb_Data[1] != kb_Yequ && press_kb_Data[6] != kb_Clear);

    gfx_End();
    return 0;
}