#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>
#include "box.h"
#include "ray.h"
#include "vector3.h"
using namespace std;

#define M_PI 3.141592653589793 

int width = 120;
int height = 30;

double fov = 90*(M_PI/180);

int main() {

    //position of camera
    Vector3 camera(0.0, 0.0, 0.0);

    //bounding box
    Vector3 box_1(-1.0, -1.0, -5.0);
    Vector3 box_2(1.0, 1.0, -3.0);
    Box box(box_1, box_2);

    //screen buffer
    wchar_t *screen = new wchar_t[width*height];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    while(true) {

        for(double i = 0; i < width; i++) {
            for(double j = 0; j < height; j++) {

                //angles of camera->pixel
                double yaw = (fov / 2) - ((fov / width)*i);
				double pitch = (fov / 2) - ((fov / height)*j);
                //pixel vector
				Vector3 dest(tan(yaw)/-1, tan(pitch)/-1, -1);
                //ray from camera->pixel
                Ray ray(camera, dest);

                //check if box intersects ray
                if(box.intersect(ray, 0, 1000)) {
                    screen[int(j*width+i)] = 'O';
                } else {
                    screen[int(j*width+i)] = '.';
                }
            }
        }

        // screen[width * height - 1] = '/0';
        WriteConsoleOutputCharacterW(hConsole, screen, width * height, { 0,0 }, &dwBytesWritten);
    }

    return 0;
}