#pragma once

void noCursorType();          //xoa dau nhay console
void setTextColor(int color); //tao mau text
void FixConsoleWindow();      //lam mo nut resize console
void gotoXY(int x, int y);    //di chuyen dau nhay den toa do x,y
int whereX();                 // hoanh do cua dau nhay
int whereY();                 //tung do cua dau nhay

void txtLine(int x0, int y0, int x1, int y1, int color);
void txtPlot(unsigned char x, unsigned char y, unsigned char Color);