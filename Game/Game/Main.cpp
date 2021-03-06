


#include <Windows.h>
#include "direct.h"
#include "Clock.h"
#include "MainGame.h"
#include "Text.h"
#include "SoundResource.h"

#include "CDirectInput.h"




LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//api 정의
HWND g_hWnd;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR pCmdLine, int nCmdShow)
{
	int clientWidth = 1200;
	int clientHeight = 900;
	bool isWindow = true;


	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;	// 창의 스타일 지정
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;	// 응용프로그램 인스턴스 핸들 연결
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);	// 아이콘
	wc.hCursor = LoadCursor(0, IDC_ARROW);	// 커서
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경 색깔
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"GameAppStyle";	// 응용프로그램의 스타일 대표이름
	if (!RegisterClass(&wc))
	{
		return 0;
	}


	DWORD style;
	if (isWindow)
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}

	HWND hWnd = CreateWindow(
		L"GameAppStyle",	// 응용프로그램의 스타일
		L"GAME",	// 창의 제목
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,	//x, y
		clientWidth, clientHeight,	//너비, 높이
		0,	// 부모 창이 있을 시, 부모창의 핸들
		0,	// 메뉴 핸들.
		hInstance,	// 만들어지는윈도우 창을 사용할 응용 프로그램 핸들 세팅
		0);
	if (NULL == hWnd)
	{
		return 0;
	}

	g_hWnd = hWnd;

	CDirectInput input;

	if (FAILED(input.Init(hInstance,hWnd,clientWidth,clientHeight)))
	{
		return FALSE;
	}


	if (FAILED(CDirect::GetInstance()->InitD3D(hWnd)))
	{
		return FALSE;
	}


	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 창모드 이면 클라이언트 크기를 조정
	if (true == isWindow)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd,
			0, 0,
			clientWidth + (clientWidth - clientRect.right),
			clientHeight + (clientHeight - clientRect.bottom),
			TRUE
		);
		
	}
	MSG msg = { 0 };
	
	CClock Clock(60);

	CMainGame::GetInstance()->Init();


	

	


	
	while (WM_QUIT != msg.message )
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	// 키코드를 문자 메시지 변화.
			DispatchMessage(&msg);	// 메시지를 창으로 배분.
		}
		else
		{
			if (float deltaTime = Clock.UpdateGame())
			{
				//게임 업데이트
				CMainGame::GetInstance()->Update(deltaTime);
				input.GetKeyInput();

				//렌더링
				CDirect::GetInstance()->Render_Begin();
				
				
				CMainGame::GetInstance()->Render();
				
				
				CDirect::GetInstance()->Render_End();
				
				for (int i = 0;i < 256;i++)
				{
					if (input.m_keyboardState[i] != 0)
					{
						char c = i - 128;
						int j = 0;
					}
				}
			}
		}
	}
	delete CMainGame::GetInstance();

	return (int)msg.wParam;
}


// 윈도우 프로시저함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	//int x = LOWORD(lParam);
	//int y = HIWORD(lParam);

	// 메시지 처리
	switch (msg)
	{

	case WM_DESTROY:
		
		PostQuitMessage(0);
		return 0;
	case VK_DOWN:
		break;
		
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
