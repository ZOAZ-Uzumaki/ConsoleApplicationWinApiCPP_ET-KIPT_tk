#include <windows.h>
#include <iostream>
#include <string>

const int MAX_SIZE = 10; // Максимальний розмір масиву

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"SymmetricArrayAppClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0, CLASS_NAME, L"Symmetric Array App",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL);

    if (hWnd == NULL)
    {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int symmetricArray[MAX_SIZE][MAX_SIZE];

void generateSymmetricArray(int size)
{
    std::cout << "Generated Symmetric... Array:\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < size; ++j)
        {
            int value = rand() % 100 + 1; // Генерація від 1 до 100
            symmetricArray[i][j] = value;
            symmetricArray[j][i] = value;
        }
    }
}

void replaceDiagonalWithZero(int size)
{
    for (int i = 0; i < size; ++i)
    {
        symmetricArray[i][i] = 0;
    }
}

void displayArray(HWND hWnd, int size)
{
    std::wstring resultText = L"Array:\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            resultText += std::to_wstring(symmetricArray[i][j]) + L"\t";
        }
        resultText += L"\n";
    }
    resultText += L"\n";

    MessageBox(hWnd, resultText.c_str(), L"Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        int size = 15; // Розмір масиву
        generateSymmetricArray(size);
        replaceDiagonalWithZero(size);
        displayArray(hWnd, size);
        PostQuitMessage(0);
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
