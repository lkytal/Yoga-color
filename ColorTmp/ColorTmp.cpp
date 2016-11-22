// ColorTmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "Wingdi.h"
#include "stdio.h"

#pragma comment(lib,"gdi32.lib")

int SetColorTemper(int r, int g, int b)
{
	WORD GammaArray[3][256];

	HDC hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{
		GetDeviceGammaRamp(hGammaDC, (LPVOID)GammaArray);

		WORD lever = GammaArray[0][1];

		for (int i = 0; i < 256; i++)
		{
			GammaArray[0][i] = i * r;
			GammaArray[1][i] = i * g;
			GammaArray[2][i] = i * b;
		}

		return SetDeviceGammaRamp(hGammaDC, GammaArray);
	}

	return 0;
}

int GetBrightLever()
{
	WORD GammaArray[3][256];

	HDC hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{
		GetDeviceGammaRamp(hGammaDC, (LPVOID)GammaArray);

		for (int i = 1; i < 10; i++)
		{
			printf("\nLevel %d    ", i);

			printf("R: %d,  ", GammaArray[0][i] / i);
			printf("G: %d,  ", GammaArray[1][i] / i);
			printf("B: %d   ", GammaArray[2][i] / i);
		}
	}

	return 0;
}

#ifdef NDEBUG

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	SetColorTemper(240, 241, 255);

	return 0;
}

#else

int _tmain(int argc, _TCHAR* argv[])
{
	//SetColorTemper(245, 243, 255);

	GetBrightLever();

	return 0;
}

#endif
