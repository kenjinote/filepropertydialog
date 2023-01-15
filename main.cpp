#pragma comment(linker, "/opt:nowin98")
#include <windows.h>

#define IDU_BUTTON1 100

CHAR szClassName[]="window";

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	SHELLEXECUTEINFO sei;
	static HWND hEdit1;
	CHAR *str;
	int len;
	switch(msg){
	case WM_CREATE:
		CreateWindow("STATIC","ファイル名:",WS_CHILD|WS_VISIBLE,10,10,120,28,hWnd,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hEdit1=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","filepropertydialog.exe",WS_CHILD|WS_VISIBLE,140,10,400,28,hWnd,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		CreateWindow("BUTTON","プロパティ",WS_CHILD|WS_VISIBLE,10,50,150,28,hWnd,(HMENU)IDU_BUTTON1,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		break;
	case WM_GETMINMAXINFO:
		{// 窓の最小サイズを設定
			MINMAXINFO* lpMMI=(MINMAXINFO*)lParam;
			lpMMI->ptMinTrackSize.x=560;
			lpMMI->ptMinTrackSize.y=140;
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case IDU_BUTTON1:
			len=GetWindowTextLength(hEdit1)+1;
			str=(char *)malloc(len);
			GetWindowText(hEdit1,str,len);
			ZeroMemory ( &sei, sizeof(sei) );
			sei.cbSize = sizeof(sei);
			sei.lpFile = str;
			sei.lpVerb = TEXT("properties");
			sei.fMask = SEE_MASK_INVOKEIDLIST | SEE_MASK_NOCLOSEPROCESS;
			ShellExecuteEx (&sei);
			free(str);
			break;
		default:
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return(0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"ファイルのプロパティを表示する",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(msg.wParam);
}

