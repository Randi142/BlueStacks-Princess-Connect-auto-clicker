#include <iostream>
#include <windows.h>
#include <thread>
#define KEY 0x8000
#define x_ratio 0.25
#define y_ratio 0.825

void keyCheck(int &key);
void autoClick(int &key);
RECT rect;
HWND hwnd = FindWindowA(NULL,"BlueStacks");
int first_xPos, first_yPos;
int console_xPos, console_yPos;
int width, length;

int main(){
    int key;
    if(hwnd == NULL)
        std::cout<<"Cannot find BlueStacks"<<std::endl;
    else
    {
        std::thread key_check_thread(keyCheck, std::ref(key));
        std::thread clicking_thread(autoClick, std::ref(key));
        key_check_thread.join();
        clicking_thread.join();
        return 0;
    }
}

//check keyboard state from Ctrl+1 to Ctrl+5 and Ctrl+`
void keyCheck(int &key){
    int num = 0x30;
    int add = 0;
    while(true)
        if((GetAsyncKeyState(VK_CONTROL) & KEY)){    //check ctrl
            if(GetAsyncKeyState(num+add) & KEY)      //check 1-5
                key = add;
            if(GetAsyncKeyState(VK_OEM_3) & KEY)     //check `
                key = 0;
            add++;
            if(add == 6)
                add = 0;
        }
}

//auto click according to the order
void autoClick(int &key){
    while(true)
        if(key){
            switch(key){
                case 1:
                    SetCursorPos(first_xPos+console_xPos, first_yPos+console_yPos);
                    break;
                case 2:
                    SetCursorPos(first_xPos*1.5+console_xPos, first_yPos+console_yPos);
                    break;
                case 3:
                    SetCursorPos(first_xPos*2+console_xPos, first_yPos+console_yPos);
                    break;
                case 4:
                    SetCursorPos(first_xPos*2.5+console_xPos, first_yPos+console_yPos);
                    break;
                case 5:
                    SetCursorPos(first_xPos*3+console_xPos, first_yPos+console_yPos);
                    break;
            }
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(10);
        }
        else{
            //update console position & size
            GetWindowRect(hwnd,&rect);
            console_xPos = rect.left;
            console_yPos = rect.top;
            width = rect.bottom - rect.top;
            length = rect.right - rect.left;
            first_xPos = length*x_ratio;
            first_yPos = width*y_ratio; 
        }
}
