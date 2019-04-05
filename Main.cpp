#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>
#include <utility>
#include "box.h"
#include "ray.h"
#include "vector3.h"
using namespace std;

#define M_PI 3.141592653589793 

int width = 210;
int height = 70;

double fov = 90 * (M_PI / 180);

int main() {

	//position of camera
	Vector3 camera(0.0, 0.0, 0.0);
	double camera_yaw = 0.0;
	double camera_pitch = 0.0;
	double camera_roll = 0.0;

	double box_x_1 = -1.0;
	double box_y_1 = -1.0;
	double box_z_1 = -5.0;
	double box_x_2 = 1.0;
	double box_y_2 = 1.0;
	double box_z_2 = -3.0;

	//bounding box
	Vector3 box_1(box_x_1, box_y_1, box_z_1);
	Vector3 box_2(box_x_2, box_y_2, box_z_2);
	Box box(box_1, box_2);

	//screen buffer
	wchar_t *screen = new wchar_t[width*height];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SMALL_RECT windowSize = { 0, 0, 210, 70 };
	bool foo = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while (true) {

		if (GetAsyncKeyState((unsigned short)'W')) {

			Vector3 newCamera(sin(camera_yaw)*-0.1, 0.0, cos(camera_yaw)*-0.1);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState((unsigned short)'S')) {

			Vector3 newCamera(sin(camera_yaw)*0.1, 0.0, cos(camera_yaw)*0.1);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState((unsigned short)'A')) {

			Vector3 newCamera(cos(-camera_yaw)*-0.1, 0.0, sin(-camera_yaw)*-0.1);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState((unsigned short)'D')) {

			Vector3 newCamera(cos(-camera_yaw)*0.1, 0.0, sin(-camera_yaw)*0.1);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState((unsigned short)'R')) {

			Vector3 newCamera(0.0, 0.1, 0.0);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState((unsigned short)'F')) {

			Vector3 newCamera(0.0, -0.1, 0.0);
			camera = camera + newCamera;
		}
		if (GetAsyncKeyState(VK_LEFT)) {

			camera_yaw += 0.02;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {

			camera_yaw -= 0.02;
		}
		if (GetAsyncKeyState(VK_UP)) {

			camera_pitch += 0.02;
		}
		if (GetAsyncKeyState(VK_DOWN)) {

			camera_pitch -= 0.02;
		}


		for (double i = 0; i < width; i++) {
			for (double j = 0; j < height; j++) {

				//angles of camera->pixel
				double yaw = (fov / 2) - ((fov / width)*i);
				double pitch = -(fov / 2) + ((fov / height)*j);
				//pixel vector
				Vector3 dest(tan(yaw) * -1, tan(pitch) * -1, -1);
				dest.rotate_x(camera_pitch);
				dest.rotate_y(camera_yaw);
				dest.rotate_z(camera_roll);
				//ray from camera->pixel
				Ray ray(camera, dest);

				//check if box intersects ray
				if (box.intersect(ray, 0, 1000)) {
					screen[int(j*width + i)] = 9608;
				}
				else {
					screen[int(j*width + i)] = '\0';
				}
			}
		}

		// screen[width * height - 1] = '/0';
		WriteConsoleOutputCharacterW(hConsole, screen, width * height, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}