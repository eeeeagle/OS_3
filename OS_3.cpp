#include <windows.h>

void DrawTableLeg(HDC dc, int startX, int startY, int endY)
{
	int index = 0;
	for (int y = startY; y >= endY; y--) 
	{
		for (int x = startX - index; x <= startX + index; x++) 
		{
			if (x == startX) 
				SetPixelV(dc, x, y, RGB(0, 0, 0));
			else 
				SetPixelV(dc, x, y, RGB(104, 90, 44));
		}
		if (index < 25) index++;
	}
}

void DrawAshtrays(HDC dc, int x, int y)
{
	SelectObject(dc, CreateSolidBrush(RGB(192, 192, 192)));
	SelectObject(dc, CreatePen(PS_SOLID, 1, BLACK_PEN));

	Rectangle(dc, x, y, x + 150, y + 20);
	Ellipse(dc, x, y, x + 150, y + 40);

	SelectObject(dc, CreatePen(PS_NULL, 1, BLACK_PEN));
	Rectangle(dc, x, y, x + 150, y + 20);

	SelectObject(dc, CreatePen(PS_SOLID, 1, BLACK_PEN));
	Ellipse(dc, x, y + 20, x + 150, y - 20);

	SelectObject(dc, CreateSolidBrush(RGB(128, 128, 128)));
	Ellipse(dc, x + 10, y + 20, x + 140, y);

	SelectObject(dc, CreateSolidBrush(RGB(192, 192, 192)));
	Ellipse(dc, x + 65, y + 25, x + 85, y + 15);

	SelectObject(dc, CreateSolidBrush(RGB(104, 90, 44)));
	Ellipse(dc, x + 65, y - 25, x + 85, y - 15);
	SelectObject(dc, CreatePen(PS_NULL, 1, BLACK_PEN));
	Ellipse(dc, x + 65, y - 30, x + 85, y - 15);

	SelectObject(dc, CreateSolidBrush(RGB(128, 128, 128)));
	Ellipse(dc, x + 65, y + 25, x + 85, y + 10);
}

void DrawCigarette(HDC dc, int x, int y)
{
	SelectObject(dc, CreateSolidBrush(RGB(255, 255, 255)));
	SelectObject(dc, CreatePen(PS_SOLID, 1, BLACK_PEN));
	Ellipse(dc, x, y, x + 20, y + 20);

	POINT pt[4];
	pt[0].x = (x + x + 20) / 2; pt[0].y = y;
	pt[1].x = (x + x + 20) / 2; pt[1].y = y + 20;
	pt[2].x = (x + x + 100) / 2; pt[2].y = y + 60;
	pt[3].x = (x + x + 100) / 2; pt[3].y = y + 40;
	SelectObject(dc, CreatePen(PS_NULL, 1, BLACK_PEN));
	Polygon(dc, pt, 4);

	SelectObject(dc, CreateSolidBrush(RGB(255, 207, 71)));
	SelectObject(dc, CreatePen(PS_SOLID, 1, BLACK_PEN));
	Ellipse(dc, x + 40, y + 40, x + 60, y + 60);

	pt[0].x = (x + x + 100) / 2; pt[0].y = y + 40;
	pt[1].x = (x + x + 100) / 2; pt[1].y = y + 60;
	pt[2].x = (x + x + 140) / 2; pt[2].y = y + 80;
	pt[3].x = (x + x + 140) / 2; pt[3].y = y + 60;
	SelectObject(dc, CreatePen(PS_NULL, 1, BLACK_PEN));
	Polygon(dc, pt, 4);

	SelectObject(dc, CreatePen(PS_SOLID, 1, BLACK_PEN));
	SelectObject(dc, CreateSolidBrush(RGB(128, 128, 128)));
	Ellipse(dc, x + 60, y + 60, x + 80, y + 80);
}

void MyDraw(HWND h) 
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(h, &ps);

	DrawTableLeg(dc, 170, 500, 200);
	DrawTableLeg(dc, 670, 500, 200);
	DrawTableLeg(dc, 370, 700, 400);
	DrawTableLeg(dc, 870, 700, 400);

	int index = 0;
	for (int y = 191; y < 420; y++) 
	{
		for (int x = 131 + index; x < 700 + index; x++) 
			SetPixelV(dc, x, y, RGB(104, 90, 44));
		index++;
	}

	MoveToEx(dc, 130, 191, NULL);
	LineTo(dc, 359, 420);
	LineTo(dc, 928, 420);
	LineTo(dc, 698, 191);
	LineTo(dc, 130, 191);

	SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(104, 90, 44)));
	for (int x = 0, y = 0; x < 10 && y < 10; x++, y++) 
	{
		MoveToEx(dc, 130, 192 + y, NULL);
		LineTo(dc, 359, 421 + y);
	}

	SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	MoveToEx(dc, 130, 202, NULL);
	LineTo(dc, 359, 431);

	SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(104, 90, 44)));
	for (int x = 0, y = 0; x < 10 && y < 10; x++, y++) 
	{
		MoveToEx(dc, 359, 421 + y, NULL);
		LineTo(dc, 928, 421 + y);
	}

	SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	MoveToEx(dc, 359, 431, NULL);
	LineTo(dc, 928, 431);

	MoveToEx(dc, 359, 431, NULL);
	LineTo(dc, 359, 420);

	MoveToEx(dc, 928, 431, NULL);
	LineTo(dc, 928, 420);

	MoveToEx(dc, 130, 191, NULL);
	LineTo(dc, 130, 202);

	DrawAshtrays(dc, 443, 275);
	DrawCigarette(dc, 500, 275);

	EndPaint(h, &ps);
	ReleaseDC(h, dc);
	DeleteDC(dc);
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) 
{
	switch (Message) 
	{
	case WM_PAINT:
		MyDraw(hwnd);
		break;
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE) PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		if ((LOWORD(lparam) < 20) && (LOWORD(lparam) < 20)) PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));

	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = (WNDPROC)WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "OS_3";

	RegisterClass(&w);

	HWND hwnd = CreateWindow("OS_3", "OS_3", WS_OVERLAPPEDWINDOW, 10, 60, 1000, 800, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}
