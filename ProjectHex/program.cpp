#include "others/program.h"
#include <iostream>
#include "main.h"
#include "others/auth.h"
#include "others/xor.h"
#include "Print/print.h"


void LoadCheat()
{

    printf("Protecting\n");
    LoadProtectedFunctions();
    Protect(LoadProtectedFunctions);

    printf("Connecting driver\n");
    Unprotect(Driver::initialize);
    Unprotect(CheckDriverStatus);
    printf("Connected!\n");

    if (!Driver::initialize() || !CheckDriverStatus()) {
        wchar_t VarName[] = { 'F','a','s','t','B','o','o','t','O','p','t','i','o','n','\0' };
        UNICODE_STRING FVariableName = UNICODE_STRING();
        FVariableName.Buffer = VarName;
        FVariableName.Length = 28;
        FVariableName.MaximumLength = 30;
        myNtSetSystemEnvironmentValueEx(
            &FVariableName,
            &DummyGuid,
            0,
            0,
            ATTRIBUTES);
        memset(VarName, 0, sizeof(VarName));
        Beep(600, 1000);
        char tx[] = { 'N','O',' ','E','F','I',' ',';','(','\n', 0 };
        printf(tx);
        ProtectedSleep(3000);
        ProtectedExit(1);

    }
    Protect(Driver::initialize);
    Protect(CheckDriverStatus);


    SetupWindow();
    DirectXInit(MyWnd);

    verify_game();

    HANDLE hdl = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cache), nullptr, NULL, nullptr);

    CloseHandle(hdl);

    while (TRUE) {

        MainLoop();
    }

}

void WaitingForGame()
{

    HWND lmao = NULL;

    system(_xor_("cls").c_str());
    Print::warning(_xor_("\n\n  Waiting for Game...\n").c_str());
    while (GameWnd == NULL)
    {
        GameWnd = FindWindowW(NULL, TEXT(_xor_(L"Valorant  ")).c_str());

        Sleep(1);
    }
    Beep(350, 100);
    system(_xor_("cls").c_str());
    Print::warning(_xor_("\n  Process found!\n").c_str());
    Print::warning(_xor_("  Once you are in the main menu, press F2 to load.").c_str());
    while (1)
    {
        if (GetAsyncKeyState(VK_F2) & 1)
        {
            system(_xor_("cls").c_str());
            Sleep(100);
            Beep(350, 100);
            LoadCheat();

        }
    }

}

void choices()
{

    Print::text(_xor_("[1] Load Cheat\n").c_str(), White);
    std::string choice;
    std::getline(std::cin, choice);


    if (choice == _xor_("1").c_str())
    {
        system(_xor_("cls").c_str());
        WaitingForGame();

    }


    else if (choice != _xor_("1").c_str())
    {
        system(_xor_("cls").c_str());
        choices();

    }

}

void main::program()
{
	if (IsValid == false)
	{
		std::cout << "Session Expired\n";
		Sleep(5000);
        ProtectedExit(0);
	}

    choices();
}