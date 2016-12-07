// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Projekt3.h"

#define MAX_LOADSTRING 100
#define TMR_1 1


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

	struct blok{
		int scianax1;
		int scianax2;
		int scianay;
		int szerokosc;
		int wysokosc;
		int waga;
		int spod;
	};

	blok blok1 =
	{
		blok1.scianax1  = 500,
		blok1.scianax2  = 550,
		blok1.scianay   = 350,
		blok1.szerokosc = 50,
		blok1.wysokosc  = 55,
		blok1.waga      = 200,
		blok1.spod      = blok1.wysokosc + blok1.scianay,
	};

	blok blok2 =
	{
		blok2.scianax1  = 570,
		blok2.scianax2  = 620,
		blok2.scianay   = 350,
		blok2.szerokosc = 50,
		blok2.wysokosc  = 55,
		blok2.waga      = 200,
		blok2.spod      = blok2.wysokosc + blok2.scianay,
	};

	blok blok3 =
	{
		blok3.scianax1  = 340,
		blok3.scianax2  = 390,
		blok3.scianay   = 350,
		blok3.szerokosc = 50,
		blok3.wysokosc  = 55,
		blok3.waga      = 400,
		blok3.spod      = blok3.wysokosc + blok3.scianay,
	};

BOOL zapamietywanie;
BOOL przenoszenie1;
BOOL przenoszenie2;
BOOL przenoszenie3;
BOOL bloczek1;
BOOL bloczek2;
BOOL bloczek3;
DOUBLE value1;
DOUBLE value2;
DOUBLE valuey;
DOUBLE szybkosc;
INT i;
INT podloga = 405;
INT dopuszczalne_obciazenie = 300;
INT x;
INT y;
INT wspx;
INT wspy;
INT Dlugosc_ramienia = 300;
INT wspXczubka;
INT wspYczubka;
INT licznik;
vector <int> ruch;


void sprawdzanie_dotkniecia(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void przenoszenie_bloczka(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void odtwarzanie_ruchow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255,255,0,0));
	pen.SetWidth(8);
	Pen tlo(Color(255,0,50,100));
	tlo.SetWidth(10);
	Pen skrzynie(Color(250,150,0,0));
	skrzynie.SetWidth(7);
	
	graphics.DrawLine(&tlo,0,podloga,1000,podloga);

	graphics.DrawRectangle(&skrzynie, blok1.scianax1, blok1.scianay, blok1.szerokosc, blok1.wysokosc);
	graphics.DrawRectangle(&skrzynie, blok2.scianax1, blok2.scianay, blok2.szerokosc, blok2.wysokosc);
	graphics.DrawRectangle(&skrzynie, blok3.scianax1, blok3.scianay, blok3.szerokosc, blok3.wysokosc);

	graphics.DrawLine(&pen,100,400,100+wspx,400+wspy);	
	graphics.DrawLine(&pen,100+wspx,400+wspy,wspx+100+x,wspy+400+y);
	
	
}


int OnCreate(HWND window)
{
   SetTimer(window, TMR_1, 25, 0);
   return 0;
}



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	przenoszenie1 = false;
	przenoszenie2 = false;
	przenoszenie3 = false;
	zapamietywanie = false;
	bloczek1 = false;
	bloczek2 = false;
	bloczek3 = false;
	licznik = 0;
	szybkosc = 0.01;
	valuey = 100;
	value1 = 0;
	value2 = -3.1415/2;
	i = 0;
	

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   OnCreate(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;



case WM_KEYDOWN:
{
    switch(( int ) wParam )
    {
    case VK_RETURN:
        //MessageBox( hWnd, TEXT("Wciœniêto Entera"), TEXT("Yeah"), MB_ICONINFORMATION );
        break;
        
    case VK_ESCAPE:
        DestroyWindow( hWnd );
        break;


	case VK_RIGHT:
		
		if( wspy+400+y <=400 && 400+wspy <= 400 && blok1.spod <= 405 && blok2.spod <=405 && blok3.spod <=405 )
		{
			value2+=szybkosc;
			wspx = Dlugosc_ramienia* cos(value2);
			wspy = Dlugosc_ramienia* sin(value2);
			value1+=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);

			if (zapamietywanie == true)
				{
				ruch.push_back(6);
				licznik++;
				}
		}
		else
			MessageBox( hWnd, TEXT("Próbujesz przekroczyæ zakres ruchu"), TEXT("Ostrze¿enie"), MB_ICONINFORMATION );

		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
		break;
	case VK_LEFT:
		if(wspx+100+x > 120)
		{
			value2-=szybkosc;
			wspx = Dlugosc_ramienia* cos(value2);
			wspy = Dlugosc_ramienia* sin(value2);
			value1-=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);
			if(zapamietywanie == true)
				{
				ruch.push_back(4);
				licznik++;
				}
		}
		else
			MessageBox( hWnd, TEXT("Próbujesz przekroczyæ zakres ruchu"), TEXT("Ostrze¿enie"), MB_ICONINFORMATION );

		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
		break;

	case VK_UP:	
		if(wspx+100+x > 120)
		{
			value1-=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);

			if (zapamietywanie == true)
				{
				ruch.push_back(8);
				licznik++;
				}
		}
		else
			MessageBox( hWnd, TEXT("Próbujesz przekroczyæ zakres ruchu"), TEXT("Ostrze¿enie"), MB_ICONINFORMATION );

		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
		break;
	case VK_DOWN:
		
		if(wspy+400+y <=400 && 400+wspy <=400 && blok1.spod <= 405 && blok2.spod <=405 && blok3.spod <=405)
			{
			value1+=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);

			if (zapamietywanie == true)
				{
				ruch.push_back(2);
				licznik++;
				}
			}
		else
			MessageBox( hWnd, TEXT("Próbujesz przekroczyæ zakres ruchu"), TEXT("Ostrze¿enie"), MB_ICONINFORMATION );

			sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
			przenoszenie_bloczka( hWnd,  message, wParam, lParam);
		
		
		break;
	case VK_NUMPAD5:
		if(szybkosc <= 0.05)
		{
			szybkosc+=0.01;
			if(zapamietywanie == true)
			{
				ruch.push_back(1);
				licznik++;
			}
		}
		break;
	case VK_NUMPAD2:
		if(szybkosc > 0.01)
		{
			szybkosc-=0.01;
			if(zapamietywanie == true)
			{
				ruch.push_back(3);
				licznik++;
			}

		}
		break;
	case VK_NUMPAD4:
		if(bloczek1 == true)
		{
			if( dopuszczalne_obciazenie > blok1.waga)
			{
				przenoszenie1 = true;		
			}
			else MessageBox( hWnd, TEXT("Bloczek jest za ciezki"), TEXT("Komunikat"), MB_ICONINFORMATION );			
		}	
		if(bloczek2 == true)
		{
			if( dopuszczalne_obciazenie > blok2.waga)
			{
				przenoszenie2 = true;		
			}
			else MessageBox( hWnd, TEXT("Bloczek jest za ciezki"), TEXT("Komunikat"), MB_ICONINFORMATION );
		}
		if(bloczek3 == true)
		{
			if( dopuszczalne_obciazenie > blok3.waga)
			{
				przenoszenie3 = true;		
			}
			else MessageBox( hWnd, TEXT("Bloczek jest za ciezki"), TEXT("Komunikat"), MB_ICONINFORMATION );

			
		}

		if (zapamietywanie == true)
				{
				ruch.push_back(7);
				licznik++;
				}
		break;
	case VK_NUMPAD1:
		if(blok1.scianay + blok1.wysokosc <= podloga+3 && blok2.scianay + blok2.wysokosc <=podloga+3 && blok3.scianay + blok3.wysokosc <= podloga+3 &&
			blok1.scianay + blok1.wysokosc >= podloga-3 && blok2.scianay + blok2.wysokosc >=podloga-3 && blok3.scianay + blok3.wysokosc >= podloga-3)
		{
		blok1.spod = podloga;
		blok2.spod = podloga;
		blok3.spod = podloga;
		blok1.scianay = blok1.spod - blok1.wysokosc;
		blok2.scianay = blok2.spod - blok2.wysokosc;
		blok3.scianay = blok3.spod - blok3.wysokosc;
		przenoszenie1 = false;
		przenoszenie2 = false;
		przenoszenie3 = false;
		}
		else
		MessageBox( hWnd, TEXT("Nie mozna upuscic bloczka w powietrzu"), TEXT("Komunikat"), MB_ICONINFORMATION );

		if (zapamietywanie == true)
				{
				ruch.push_back(9);
				licznik++;
				}
		break;

	case VK_NUMPAD6:
		if(zapamietywanie == false)
		{
			zapamietywanie = true;
			ruch.clear();
			i=0;
			licznik=0;
			MessageBox( hWnd, TEXT("zapamietywanie wlaczone"), TEXT("Komunikat"), MB_ICONINFORMATION );
		}
		else if(zapamietywanie == true)
		{
			zapamietywanie = false;
			MessageBox( hWnd, TEXT("zapamietywanie wylaczone"), TEXT("Komunikat"), MB_ICONINFORMATION );			
		}
		break;

	case VK_NUMPAD3:
		if(zapamietywanie == false)
		{
				for(int j=0 ; j<licznik-2 ; j++)
				{
				odtwarzanie_ruchow( hWnd, message, wParam, lParam);
				Sleep(25);
				InvalidateRect(hWnd, NULL, TRUE);
				hdc = BeginPaint(hWnd, &ps);
				MyOnPaint(hdc);
				EndPaint(hWnd, &ps);
				}
				i=0;
			
		}
		else MessageBox( hWnd, TEXT("Musisz zakonczyc zapamietywanie"), TEXT("Komunikat"), MB_ICONINFORMATION );
		}

}
break;




	case WM_TIMER:
		switch (wParam)
		{
			case TMR_1:
				//force window to repaint
				InvalidateRect(hWnd, NULL, TRUE);
				hdc = BeginPaint(hWnd, &ps);
				MyOnPaint(hdc);
				EndPaint(hWnd, &ps);
			break;
		}

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

void sprawdzanie_dotkniecia(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wspXczubka = wspx+100+x;
	wspYczubka = wspy+400+y;

	if(wspXczubka > blok1.scianax1 && wspXczubka < blok1.scianax2 && wspYczubka > blok1.scianay)
	{
		//MessageBox( hWnd, TEXT("Dotknales drugi bloczek"), TEXT("Komunikat"), MB_ICONINFORMATION );
		bloczek1 = true;		
	}
	else bloczek1 = false;

	if(wspXczubka > blok2.scianax1 && wspXczubka < blok2.scianax2 && wspYczubka > blok2.scianay)
	{
		//MessageBox( hWnd, TEXT("Dotknales drugi bloczek"), TEXT("Komunikat"), MB_ICONINFORMATION );
		bloczek2 = true;
	}
	else bloczek2 = false;

	if(wspXczubka > blok3.scianax1 && wspXczubka < blok3.scianax2 && wspYczubka > blok3.scianay)
	{
		//MessageBox( hWnd, TEXT("Dotknales trzeci bloczek"), TEXT("Komunikat"), MB_ICONINFORMATION );
		bloczek3 = true;
	}
	else bloczek3 = false;
}

void przenoszenie_bloczka(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(przenoszenie1 == true)
	{
	blok1.scianax1 = wspXczubka - blok1.szerokosc/2;
	blok1.scianax2 = wspXczubka + blok1.szerokosc/2;
	blok1.scianay  = wspYczubka;
	blok1.spod     = blok1.wysokosc + blok1.scianay;

	}
	if(przenoszenie2 == true)
	{
	blok2.scianax1 = wspXczubka - blok2.szerokosc/2;
	blok2.scianax2 = wspXczubka + blok2.szerokosc/2;
	blok2.scianay  = wspYczubka;
	blok2.spod     = blok2.wysokosc + blok2.scianay;

	}
	if(przenoszenie3 == true)
	{
	blok3.scianax1 = wspXczubka - blok3.szerokosc/2;
	blok3.scianax2 = wspXczubka + blok3.szerokosc/2;
	blok3.scianay  = wspYczubka;
	blok3.spod     = blok3.wysokosc + blok3.scianay;

	}
}

void odtwarzanie_ruchow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	i++;
	if (ruch[i] == 8)
	{
		if(wspx+100+x > 120)
		{
			value1-=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);
		}

		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
	}

	if (ruch[i] == 6) 
	{
		if( wspy+400+y <=400 && 400+wspy <= 400 && blok1.spod <= 405 && blok2.spod <=405 && blok3.spod <=405 )
		{
			value2+=szybkosc;
			wspx = Dlugosc_ramienia* cos(value2);
			wspy = Dlugosc_ramienia* sin(value2);
			value1+=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);
		}
		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
	}

	if (ruch[i] == 4) 
	{
		if(wspx+100+x > 120)
		{
			value2-=szybkosc;
			wspx = Dlugosc_ramienia* cos(value2);
			wspy = Dlugosc_ramienia* sin(value2);
			value1-=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);
		}
		sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
		przenoszenie_bloczka( hWnd,  message, wParam, lParam);
	}

	if (ruch[i] == 2)
	{
		if(wspy+400+y <=400 && 400+wspy <=400 && blok1.spod <= 405 && blok2.spod <=405 && blok3.spod <=405)
			{
			value1+=szybkosc;
			x = Dlugosc_ramienia* cos(value1);
			y = Dlugosc_ramienia* sin(value1);
			}
			sprawdzanie_dotkniecia( hWnd, message, wParam, lParam);
			przenoszenie_bloczka( hWnd,  message, wParam, lParam);
	}
	if (ruch[i] == 7)
	{
		if(bloczek1 == true)
		{
			if( dopuszczalne_obciazenie > blok1.waga)
			{
				przenoszenie1 = true;		
			}			
		}	
		if(bloczek2 == true)
		{
			if( dopuszczalne_obciazenie > blok2.waga)
			{
				przenoszenie2 = true;		
			}
		}
		if(bloczek3 == true)
		{
			if( dopuszczalne_obciazenie > blok3.waga)
			{
				przenoszenie3 = true;		
			}
		}
		
	}

	if (ruch[i] == 9)
	{
		if(blok1.scianay + blok1.wysokosc <= podloga+3 && blok2.scianay + blok2.wysokosc <=podloga+3 && blok3.scianay + blok3.wysokosc <= podloga+3 &&
			blok1.scianay + blok1.wysokosc >= podloga-3 && blok2.scianay + blok2.wysokosc >=podloga-3 && blok3.scianay + blok3.wysokosc >= podloga-3)
		{
		blok1.spod = podloga;
		blok2.spod = podloga;
		blok3.spod = podloga;
		blok1.scianay = blok1.spod - blok1.wysokosc;
		blok2.scianay = blok2.spod - blok2.wysokosc;
		blok3.scianay = blok3.spod - blok3.wysokosc;
		przenoszenie1 = false;
		przenoszenie2 = false;
		przenoszenie3 = false;
		}
	}

	if (ruch[i] == 1)
	{
		if(szybkosc <= 0.05)
		{
			szybkosc+=0.01;
		}
	}
	if (ruch[i] == 3)
	{
		if(szybkosc > 0.01)
		{
			szybkosc-=0.01;
		}
	}
}