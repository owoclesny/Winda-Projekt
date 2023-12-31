// WindowsProject3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject3.h"


#define MAX_LOADSTRING 100
int id = 0;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Winda winda;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void mapa(HDC hdc) {

    Graphics graphics(hdc);
    Pen black(Color(255, 0, 0, 0), 5);
    Pen red(Color(255, 255, 0, 0), 5);
    Bitmap PersonImg(L"steve2.png");
    for (int i = 4;i >= 0;--i) {
        if (i % 2 == 0) graphics.DrawLine(&black, 0,  floor_distance * (i+1), 250, floor_distance * (i + 1));       //rysowanie pieter
        else graphics.DrawLine(&black, 500, floor_distance * (i + 1), 750, floor_distance * (i + 1));
    }
    int poz = winda.pozycja;
    graphics.DrawLine(&red, 251, 0 + poz, 499, 0 + poz);                                    //rysowanie windy
    graphics.DrawLine(&red, 251, 0 + poz, 251, floor_distance + poz);
    graphics.DrawLine(&red, 499, 0 + poz, 499, floor_distance + poz);
    graphics.DrawLine(&red, 251, floor_distance + poz, 499, floor_distance + poz);


    for (int i = 0;i <= 4; ++i) {
        for (auto& man : kolejkon[i]) {
            Rect PersonSpace(man.z, man.y, PersonImg.GetWidth() / 2, PersonImg.GetHeight() / 2);
            graphics.DrawImage(&PersonImg, PersonSpace);
        }
    }
    for (auto& man : winda.srodek) {
        Rect PersonSpace(man.z, floor_distance + poz - 60, PersonImg.GetWidth() / 2, PersonImg.GetHeight() / 2);
        graphics.DrawImage(&PersonImg, PersonSpace);
    }

    TextOut(hdc, 900, 50, L"Ud�wig(maks 600kg/8 osob):", 27);
    if (winda.srodek.size() != 0) {
        wchar_t udzwig[4];
        swprintf(udzwig, 4, L"%d", winda.srodek.size() * 70);
        TextOut(hdc, 1100, 50, udzwig, 3);
        if (winda.srodek.size() > 8){
            TextOut(hdc, 900, 70, L"Nie ladzia :(", 14);
            }
    }
    else {
        TextOut(hdc, 1100, 50, L"0", 2);
    }
}

void guzik(int wmId) {              //generowanie ludzi oczekujacych na winde i dodawanie ich do kolejki dla kazdego pietra
    int pietro = wmId / 10;
    int cel = wmId % 10;
    if (pietro % 2 == 0) {
        Czlowiek ludz(50+10*kolejkon[pietro].size(),60+floor_distance*(4-pietro),cel ,pietro, ++id);
        kolejkon[pietro].push_back(ludz);
        winda.wezwanie(ludz);
    }
    else {
        Czlowiek ludz(700 - 10 * kolejkon[pietro].size(), 60 + floor_distance * (4 - pietro), cel, pietro, ++id);
        kolejkon[pietro].push_back(ludz);
        winda.wezwanie(ludz);
    }
    
    
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 1, 10, NULL); //100 FPS (1000ms/100=10)
    
   for (int i = 4; i >= 0; --i) {
       for (int j = 4; j >= 0; --j){
           if (i!=j){
               if (i % 2 == 0) {
                   wchar_t pietro[16];
                   swprintf(pietro, 16, L"%d", j);
                   HWND hwndButton = CreateWindow(
                       L"BUTTON",  // Predefined class; Unicode assumed 
                       L"T",      // Button text 
                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                       20,         // x position 
                       10+20*(abs(j-4))+floor_distance*(abs(i-4)),// y position 
                       20,        // Button width
                       20,        // Button height
                       hWnd,     // Parent window
                       (HMENU)(i*10+j), // Button id
                       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                       NULL);      // Pointer not needed.
                   SetWindowText(hwndButton, pietro);  //podmiana tekstuna na guziku na pietro
                }
               else {
                   wchar_t pietro[16];
                   swprintf(pietro, 16, L"%d", j);
                   HWND hwndButton = CreateWindow(
                       L"BUTTON",  // Predefined class; Unicode assumed 
                       L"T",      // Button text 
                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                       730,         // x position 
                       10 + 20 * (abs(j - 4)) + floor_distance * (abs(i - 4)),// y position 
                       20,        // Button width
                       20,        // Button height
                       hWnd,     // Parent window
                       (HMENU)(i*10+j), //Button id
                       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                       NULL);      // Pointer not needed.
                   SetWindowText(hwndButton, pietro);
               }
           }

       

       }

   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (wmId >= 0 and wmId < 45) {
                guzik(wmId);
            }
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // create memory DC and memory bitmap where we shall do our drawing

        HDC memDC = CreateCompatibleDC(hdc);

        // get window's client rectangle. We need this for bitmap creation.
        RECT rcClientRect;
        GetClientRect(hWnd, &rcClientRect);

        // now we can create bitmap where we shall do our drawing
        HBITMAP bmp = CreateCompatibleBitmap(hdc,
            rcClientRect.right - rcClientRect.left,
            rcClientRect.bottom - rcClientRect.top);

        // we need to save original bitmap, and select it back when we are done,
        // in order to avoid GDI leaks!
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
        FillRect(memDC, &rcClientRect, (HBRUSH)(COLOR_WINDOW + 1));
        mapa(memDC);

        BitBlt(hdc, 0, 0, rcClientRect.right - rcClientRect.left,
            rcClientRect.bottom - rcClientRect.top, memDC, 0, 0, SRCCOPY);

        // all done, now we need to cleanup
        SelectObject(memDC, oldBmp); // select back original bitmap
        DeleteObject(bmp); // delete bitmap since it is no longer required
        DeleteDC(memDC);   // delete memory DC since it is no longer required
        EndPaint(hWnd, &ps);
    }
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE); //nowe wygenerowanie ekranu
        winda.reset();
        winda.ruch();
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
