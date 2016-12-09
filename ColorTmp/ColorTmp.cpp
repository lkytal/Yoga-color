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
		for (int i = 0; i < 256; i++)
		{
			GammaArray[0][i] = i * r;
			GammaArray[1][i] = i * g;
			GammaArray[2][i] = i * b;
		}

		SetDeviceGammaRamp(hGammaDC, GammaArray);

		ReleaseDC(NULL, hGammaDC);
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

		ReleaseDC(NULL, hGammaDC);
	}

	return 0;
}

#ifdef _WINDOWAPP

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	int R = 245, G = 243, B = 255;

	if (lpCmdLine[0] != NULL)
	{
		lpCmdLine[3] = lpCmdLine[7] = '\0';

		R = _ttoi(lpCmdLine);
		G = _ttoi(&lpCmdLine[4]);
		B = _ttoi(&lpCmdLine[8]);
	}

	SetColorTemper(R, G, B);

	return 0;
}

#else

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 4)
	{
		SetColorTemper(_ttoi(argv[1]), _ttoi(argv[2]), _ttoi(argv[3]));
	}

	GetBrightLever();

	return 0;
}

#endif
