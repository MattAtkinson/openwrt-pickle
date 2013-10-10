v 20110115 2
C 40000 40000 0 0 0 title-B.sym
C 47100 43600 1 0 0 pic16F628-1.sym
{
T 47400 46700 5 8 1 1 0 0 1
refdes=U1 PIC16F628A-I/P
T 48100 43700 5 8 0 1 0 0 1
footprint=DIP18
T 48100 46400 5 8 0 1 0 0 1
device=PIC16F628
}
C 43200 43500 1 0 0 max232-2.sym
{
T 43500 47150 5 10 0 0 0 0 1
device=MAX232
T 44600 47200 5 10 1 1 0 6 1
refdes=U2 ST232CN
T 43500 47350 5 10 0 0 0 0 1
footprint=DIP16
}
N 47100 44200 46100 44200 4
N 46100 44200 46100 45000 4
N 46100 45000 45200 45000 4
N 45200 43800 45600 43800 4
N 45600 43800 45600 44800 4
N 45600 44800 47100 44800 4
T 42100 44900 9 10 1 0 0 0 1
TXD
T 42100 43700 9 10 1 0 0 0 1
CTS
N 43200 45000 42600 45000 4
N 43200 43800 42600 43800 4
N 49800 46000 53700 46000 4
N 49800 46300 53700 46300 4
C 53700 46200 1 0 0 resistor-2.sym
{
T 54100 46550 5 10 0 0 0 0 1
device=RESISTOR
T 54000 46500 5 10 1 1 0 0 1
refdes=4K7
}
C 53700 45900 1 0 0 resistor-2.sym
{
T 54100 46250 5 10 0 0 0 0 1
device=RESISTOR
T 54000 45600 5 10 1 1 0 0 1
refdes=4K7
}
N 53200 46000 53200 47200 4
N 52700 46300 52700 47200 4
T 53000 47500 9 10 1 0 0 0 1
CLK
T 52500 47500 9 10 1 0 0 0 1
DAT
T 52300 47900 9 10 1 0 0 0 1
PS/2 MOUSE
N 45800 43900 47100 43900 4
N 45200 44200 45800 44200 4
N 45800 44200 45800 43900 4
N 45200 44600 46000 44600 4
N 46000 44500 47100 44500 4
N 46000 44600 46000 44500 4
C 42300 46400 1 0 0 capacitor-1.sym
{
T 42500 47100 5 10 0 0 0 0 1
device=CAPACITOR
T 42500 46900 5 10 1 1 0 0 1
refdes=C1 100n
T 42500 47300 5 10 0 0 0 0 1
symversion=0.1
}
C 45200 46400 1 0 0 capacitor-1.sym
{
T 45400 47100 5 10 0 0 0 0 1
device=CAPACITOR
T 45400 46900 5 10 1 1 0 0 1
refdes=C3 100n
T 45400 47300 5 10 0 0 0 0 1
symversion=0.1
}
C 45200 45600 1 0 0 capacitor-1.sym
{
T 45400 46300 5 10 0 0 0 0 1
device=CAPACITOR
T 45400 46100 5 10 1 1 0 0 1
refdes=C4 100n
T 45400 46500 5 10 0 0 0 0 1
symversion=0.1
}
C 42300 45600 1 0 0 capacitor-1.sym
{
T 42500 46300 5 10 0 0 0 0 1
device=CAPACITOR
T 42500 46100 5 10 1 1 0 0 1
refdes=C2 100n
T 42500 46500 5 10 0 0 0 0 1
symversion=0.1
}
C 47100 47400 1 90 0 capacitor-1.sym
{
T 46400 47600 5 10 0 0 90 0 1
device=CAPACITOR
T 46600 47600 5 10 1 1 90 0 1
refdes=C5 100n
T 46200 47600 5 10 0 0 90 0 1
symversion=0.1
}
C 45900 45500 1 0 0 ground.sym
N 43200 46200 42300 46200 4
N 42300 46200 42300 46600 4
N 43200 45400 42300 45400 4
N 42300 45400 42300 45800 4
N 46200 46600 46200 48500 4
T 50000 40700 9 10 1 0 0 0 1
PS/2 TO SERIAL MOUSE PROTOCOL CONVERTER
T 53900 40400 9 10 1 0 0 0 1
1.00
T 53900 40100 9 10 1 0 0 0 1
D M BROAD
T 50000 40100 9 10 1 0 0 0 1
1
T 51500 40100 9 10 1 0 0 0 1
1
T 50000 40400 9 10 1 0 0 0 1
mouse/pic16f628a.sch
T 40700 44500 9 10 1 0 0 0 1
RXD
T 40700 44100 9 10 1 0 0 0 1
RTS
N 42000 45000 41200 44600 4
N 42000 43800 41200 44200 4
C 48000 48300 1 90 1 capacitor-2.sym
{
T 47300 48100 5 10 0 0 90 6 1
device=POLARIZED_CAPACITOR
T 47500 48100 5 10 1 1 90 6 1
refdes=4.7uF
T 47100 48100 5 10 0 0 90 6 1
symversion=0.1
}
N 43200 44600 42600 44600 4
N 43200 44200 42600 44200 4
T 42100 44100 9 10 1 0 0 0 1
RTS
T 42100 44500 9 10 1 0 0 0 1
RXD
T 40400 42700 9 15 1 0 0 0 1
IBM PC
C 50500 42700 1 0 0 jumper-1.sym
{
T 50800 43200 5 8 0 0 0 0 1
device=JUMPER
T 50800 43200 5 10 1 1 0 0 1
refdes=J1
}
C 51500 42700 1 0 0 jumper-1.sym
{
T 51800 43200 5 8 0 0 0 0 1
device=JUMPER
T 51800 43200 5 10 1 1 0 0 1
refdes=J2
}
C 52500 42700 1 0 0 jumper-1.sym
{
T 52800 43200 5 8 0 0 0 0 1
device=JUMPER
T 52800 43200 5 10 1 1 0 0 1
refdes=J3
}
C 53500 42700 1 0 0 jumper-1.sym
{
T 53800 43200 5 8 0 0 0 0 1
device=JUMPER
T 53800 43200 5 10 1 1 0 0 1
refdes=J4
}
N 49800 43900 50600 43900 4
N 50600 43900 50600 43700 4
N 51600 43700 51600 44200 4
N 51600 44200 49800 44200 4
N 52600 43700 52600 44500 4
N 52600 44500 49800 44500 4
N 53600 43700 53600 44800 4
N 53600 44800 49800 44800 4
N 42000 42700 53600 42700 4
T 40600 41300 9 10 1 0 0 0 1
12V
T 40600 41000 9 10 1 0 0 0 1
GND
T 40600 40700 9 10 1 0 0 0 1
GND
T 40600 40400 9 10 1 0 0 0 1
5V
N 41100 40800 42000 40800 4
T 40200 41700 9 10 1 0 0 0 1
FLOPPY POWER
T 40300 43700 9 10 1 0 0 0 1
RS-232 SERIAL
N 41100 40500 42500 40500 4
N 42500 40500 42500 42300 4
T 49900 45700 9 10 1 0 0 0 1
NC
T 49900 45400 9 10 1 0 0 0 1
NC
T 46700 45400 9 10 1 0 0 0 1
NC
T 46700 45700 9 10 1 0 0 0 1
NC
T 46700 46000 9 10 1 0 0 0 1
NC
T 46700 46300 9 10 1 0 0 0 1
NC
N 46500 45100 47100 45100 4
N 46500 42700 46500 47200 4
N 54600 46000 54700 46000 4
N 54700 42300 54700 48500 4
N 54700 46300 54600 46300 4
N 54700 48500 46200 48500 4
N 46500 47200 52200 47200 4
T 52000 47500 9 10 1 0 0 0 1
GND
N 53700 47200 54700 47200 4
T 53600 47500 9 10 1 0 0 0 1
5V
N 42000 40800 42000 42700 4
T 55000 43500 9 10 1 0 0 0 1
J1 ALGORITHM
T 55000 43100 9 10 1 0 0 0 1
J2 SCALING
T 55000 42700 9 10 1 0 0 0 1
J3/J4 RESOLUTION
N 49800 45100 54700 45100 4
N 42500 42300 54700 42300 4
N 44000 42700 44000 43500 4
N 44400 42300 44400 43500 4
N 41100 41100 42000 41100 4
T 41200 41300 9 10 1 0 0 0 1
NC
N 46900 48300 46900 48500 4
N 46900 47400 46900 47200 4
N 47800 47400 47800 47200 4
N 47800 48300 47800 48500 4
N 46200 46600 46100 46600 4