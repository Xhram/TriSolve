

Menu("TRIANGLE DATA","SSS (SIDE SIDE SIDE)",0,"ASS (ANGLE SIDE SIDE)",1,"SAS (SIDE ANGLE SIDE)",2,"ASA (ANGLE SIDE ANGLE)",3,"AAS (ANGLE ANGLE SIDE)",4)

Lbl 0
Input "SIDE A: ",A
Input "SIDE B: ",B
Input "SIDE C: ",C
If A+B>C and B+C>A and C+A>B
Then
cos((B²+C²-A²)/(2BC))→D
cos((C²+A²-B²)/(2CA))→E
cos((A²+B²-C²)/(2AB))→F
(A+B+C)/2→S
√(S(S-A)(S-B)(S-C))→G
(A+B+C)→P
Disp " "
Disp "ANGLE A: "+toString(D)
Disp "ANGLE B: "+toString(E)
Disp "ANGLE C: "+toString(F)
Disp "AREA: "+toString(G)
Disp "PERIMETER: "+toString(P)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI





Else
Disp "TRIANGLE NOT EXIST"

End
Return
Lbl 1

Input "ANGLE A: ",D
Input "SIDE A(OPP. ANGLE A): ",A
Input "SIDE B: ",B
If (B²cos(D)²-B²+A²)<0
Then
­1→L
­1→M
Else
B*cos(D)-√(B²cos(D)²-B²+A²)→L
B*cos(D)+√(B²cos(D)²-B²+A²)→M
End

If L>0 and M>0
Then
cos((L²+A²-B²)/(2LA))→E
cos((M²+A²-B²)/(2MA))→J
cos((A²+B²-L²)/(2AB))→F
cos((A²+B²-M²)/(2AB))→K
(A+B+L)/2→S
(A+B+M)/2→T
√(S(S-A)(S-B)(S-L))→G
√(T(T-A)(T-B)(T-M))→H
(A+B+L)→P
(A+B+M)→Q
Disp " "
L→C
Disp "SIDE(C1): "+toString(L)
Disp "ANGLE(B1): "+toString(E)
Disp "ANGLE(C1): "+toString(F)
Disp "PERI.(1): "+toString(P)
Disp "AREA(1): "+toString(G)
Q→O
H→P
Input "DISPLAY TRIANGLE",Z
(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI

Input "SHOW NEXT TRIANGLE",Z
Disp " "
Disp "SIDE(C2): "+toString(M)
Disp "ANGLE(B2): "+toString(J)
Disp "ANGLE(C2): "+toString(K)
Disp "PERI.(2): "+toString(P)
Disp "AREA(2): "+toString(O)
Input "DISPLAY TRIANGLE",Z
M→C
J→E
K→F

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI



Return
End
If L>0
Then
cos((L²+A²-B²)/(2LA))→E
cos((A²+B²-L²)/(2AB))→F
(A+B+L)/2→S
√(S(S-A)(S-B)(S-L))→G
(A+B+L)→P
Disp " "
L→C
Disp "SIDE(C): "+toString(L)
Disp "ANGLE(B): "+toString(E)
Disp "ANGLE(C): "+toString(F)
Disp "PERI.: "+toString(P)
Disp "AREA: "+toString(G)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI


Return
End
If M>0
Then
cos((M²+A²-B²)/(2MA))→J
cos((A²+B²-M²)/(2AB))→K
(A+B+M)/2→T
√(T(T-A)(T-B)(T-M))→H
(A+B+M)→Q
Disp " "
M→C
J→E
K→F
Disp "SIDE(C): "+toString(M)
Disp "ANGLE(B): "+toString(J)
Disp "ANGLE(C): "+toString(K)
Disp "PERI.: "+toString(Q)
Disp "AREA: "+toString(H)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI



Return
End
If L≤0 and M≤0
Then
Disp " "
Disp "TRIANGLE DOES NOT EXIST"
Return
End
Lbl 2
Input "SIDE A: ",A
Input "ANGLE B: ",E
Input "SIDE C: ",C

√(A²+C²-2(A)(C)cos(E)→B

cos((A²+B²-C²)/(2AB))→F
180-F-E→D

cos((B²+C²-A²)/(2BC))→D
(A+B+C)/2→S
√(S(S-A)(S-B)(S-C))→G
(A+B+C)→P
Disp " "
Disp "SIDE B: "+toString(B)
Disp "ANGLE A: "+toString(D)
Disp "ANGLE C: "+toString(F)
Disp "PERI.: "+toString(P)
Disp "AREA: "+toString(G)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI

Return
Lbl 3
Disp "NO ANGLE IS OPPS. OF SIDE"
Input "ANGLE A: ",D
Input "SIDE B: ",B
Input "ANGLE C: ",F

180-D-F→E
(B/sin(E))*sin(D)→A
(B/sin(E))*sin(F)→C


Disp " "
Disp "SIDE A: "+toString(A)
Disp "ANGLE B: "+toString(E)
Disp "SIDE C: "+toString(C)
Disp "PERI.: "+toString(P)
Disp "AREA: "+toString(G)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI



Return
Lbl 4
Input "ANGLE A: ",D
Input "ANGLE B: ",E
Input "SIDE A: ",A
180-D-E→F
(A/sin(D)*sin(E)→B
(A/sin(D)*sin(F)→C
(A+B+C)/2→S
√(S(S-A)(S-B)(S-C))→G
(A+B+C)→P
Disp " "
Disp "SIDE B: "+toString(B)
Disp "SIDE C: "+toString(C)
Disp "ANGLE C: "+toString(F)




Disp "PERI.: "+toString(P)
Disp "AREA: "+toString(G)
Input "DISPLAY TRIANGLE",Z

(cos(F)*B)→U
(sin(F)*B)→V
prgmDISPTRI


Return



