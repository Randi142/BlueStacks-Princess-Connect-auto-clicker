#include <iostream>
#include <windows.h>

void windowAdjust(HWND &hwnd, RECT &rect, int &x, int &y);
void keyCheck(int &flag);
void autoClick(int flag, int x, int y);

int main(){

    int xPos, yPos;
    int flag;
    HWND hwnd = FindWindowA(NULL,"BlueStacks");
    RECT rect;

    SetWindowPos(hwnd ,0,0,0 ,1600,900 ,SWP_SHOWWINDOW|SWP_NOMOVE);
    if(hwnd==NULL)
        std::cout<<"cannot find bluestacks"<<std::endl;
    else{
        std::cout<<"auto clicker is ready"<<std::endl;
        while (1)
        {   
            windowAdjust(hwnd, rect, xPos, yPos);
            keyCheck(flag);
            autoClick(flag,xPos,yPos);
        } 
    }
    return 0;
}
//adjust window position,size&scale
void windowAdjust(HWND &hwnd, RECT &rect, int &x, int &y){
    GetWindowRect(hwnd,&rect);
    x = rect.left;
    y = rect.top;
}
//check keyboard from Ctrl+` to Ctrl+5
void keyCheck(int &flag){
    if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x31) & 0x8000)){
        flag = 1;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x32) & 0x8000)){
        flag = 2;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x33) & 0x8000)){
        flag = 3;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x34) & 0x8000)){
        flag = 4;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x35) & 0x8000)){
        flag = 5;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_OEM_3) & 0x8000)){
        flag = 0;
    }
}
//auto click according to the order
void autoClick(int flag, int x, int y){
    if(flag){
        switch(flag){
            case 1:
                SetCursorPos(x+390, y+745);
                break;
            case 2:
                SetCursorPos(x+580, y+745);
                break;
            case 3:
                SetCursorPos(x+770, y+745);
                break;
            case 4:
                SetCursorPos(x+960, y+745);
                break;
            case 5:
                SetCursorPos(x+1150, y+745);
                break;
        }
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(10);
    }
}
