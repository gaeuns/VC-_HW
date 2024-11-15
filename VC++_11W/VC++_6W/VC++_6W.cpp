// VC++_6W.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "VC++_6W.h"
#include <time.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VC6W, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VC6W));

    MSG msg;

    // 기본 메시지 루프입니다:
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



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VC6W));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VC6W);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#define CLEAR_BT    1001

int drawStyle = 0, color = 0;
int px, py;
int mx, my;
int ux, uy;
bool stop = false;
HWND cWnd;
HDC hdc;
HPEN myPen, osPen;
HBRUSH myBrush, osBrush;
RECT clientRect;
int r, g, b;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        cWnd = FindWindow(NULL, L"ChildWindow");

        srand(time(NULL));

        GetClientRect(hWnd, &clientRect);

        CreateWindow(L"button", L"CLEAR", WS_VISIBLE | WS_CHILD, 0, 0, 100, 35, hWnd, (HMENU)CLEAR_BT, hInst, NULL);
    }
        break;
    case WM_SIZE:
    {
        GetClientRect(hWnd, &clientRect);
        
        HWND hButton = GetDlgItem(hWnd, CLEAR_BT);
        SetWindowPos(hButton, NULL, clientRect.right - 120, clientRect.top + 15, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
        break;
    case WM_USER:
    {
        cWnd = FindWindow(NULL, L"ChildWindow");
    }
        break;
    case WM_LBUTTONDOWN:
    {
        stop = true;
        px = LOWORD(lParam);
        py = HIWORD(lParam);
        LPARAM lParamP = MAKELPARAM(px, py);
        ux = px;
        uy = py;
        PostMessage(cWnd, message, NULL, lParamP);
    }
        break;
    case WM_MOUSEMOVE:
    {
        if (!stop) break;

        mx = LOWORD(lParam);
        my = HIWORD(lParam);

        LPARAM lParamM = MAKELPARAM(mx, my);
        PostMessage(cWnd, message, NULL, lParamM);

        hdc = GetDC(hWnd);

        myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
        osPen = (HPEN)SelectObject(hdc, myPen);

        if (drawStyle == 1)
        {
            ux = mx;
            uy = my;
        }
        if (drawStyle == 2)
        {
            ux = mx;
            uy = my;
        }
        if (drawStyle == 3)
        {
            ux = mx;
            uy = my;
        }
        if (drawStyle == 4)
        {
            MoveToEx(hdc, px, py, NULL);
            LineTo(hdc, mx, my);

            px = mx;
            py = my;
        }

        SelectObject(hdc, osPen);
        SelectObject(hdc, osBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);

        ReleaseDC(hWnd, hdc);
    }
        break;
    case WM_LBUTTONUP:
    {
        ux = LOWORD(lParam);
        uy = HIWORD(lParam);

        LPARAM lParamU = MAKELPARAM(ux, uy);
        PostMessage(cWnd, message, NULL, lParamU);

        hdc = GetDC(hWnd);

        myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
        osPen = (HPEN)SelectObject(hdc, myPen);

        if (color == 0)
        {
            myBrush = CreateSolidBrush(RGB(255, 255, 255));
            osBrush = (HBRUSH)SelectObject(hdc, myBrush);
        }
        else if (color == 1)
        {
            myBrush = CreateSolidBrush(RGB(255, 192, 203));
            osBrush = (HBRUSH)SelectObject(hdc, myBrush);
        }
        else if (color == 2)
        {
            myBrush = CreateSolidBrush(RGB(0, 0, 255));
            osBrush = (HBRUSH)SelectObject(hdc, myBrush);
        }
        else if (color == 3)
        {
            myBrush = CreateSolidBrush(RGB(191, 148, 228));
            osBrush = (HBRUSH)SelectObject(hdc, myBrush);
        }

        if (drawStyle == 1)
        {
            MoveToEx(hdc, px, py, NULL);
            LineTo(hdc, ux, uy);
        }
        if (drawStyle == 2)
        {
            Rectangle(hdc, px, py, ux, uy);
        }
        if (drawStyle == 3)
        {
            Ellipse(hdc, px, py, ux, uy);
        }
        if (drawStyle == 4) {}

        stop = false;

        SelectObject(hdc, osPen);
        SelectObject(hdc, osBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);

        ReleaseDC(hWnd, hdc);
    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case CLEAR_BT:
                InvalidateRect(hWnd, NULL, true);
                PostMessage(cWnd, WM_USER, NULL, NULL);
                break;
            case ID_32771:
                drawStyle = 1;
                PostMessage(cWnd, WM_USER + 1, NULL, NULL);
                break;
            case ID_32772:
                drawStyle = 2;
                PostMessage(cWnd, WM_USER + 2, NULL, NULL);
                break;
            case ID_32773:
                drawStyle = 3;
                PostMessage(cWnd, WM_USER + 3, NULL, NULL);
                break;
            case ID_32774:
                drawStyle = 4;
                PostMessage(cWnd, WM_USER + 4, NULL, NULL);
                break;
            case ID_32775:
                color = 0;
                PostMessage(cWnd, WM_USER + 5, NULL, NULL);
                break;
            case ID_32780:
                color = 1;
                PostMessage(cWnd, WM_USER + 6, NULL, NULL);
                break;
            case ID_32777:
                color = 2;
                PostMessage(cWnd, WM_USER + 7, NULL, NULL);
                break;
            case ID_32778:
                color = 3;
                PostMessage(cWnd, WM_USER + 8, NULL, NULL);
                break;
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
