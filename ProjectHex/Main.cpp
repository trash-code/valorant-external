#include "others/hwid.h"
#include <iostream>
#include <stdio.h>
#include "crypto/crypto.h"
#include "others/auth.h"
#include "others/xor.h"
#include <wincrypt.h>
#include "crypto/hex.h"
#include <consoleapi2.h>

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "ntdll.lib")
bool IsValid = false;
std::string userid = ""; // ENTER USER ID
std::string ProgramID = ""; // ENTER PROGRAM ID

uint64_t add[16];

bool k_f5 = 0;
bool k_f6 = 0;
bool k_f7 = 0;
bool k_f8 = 0;

bool IsKeyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

int aim_key = VK_RBUTTON;

int main()
{

	std::cout << _xor_("Key: ");
	std::string i2;
	std::cin >> i2;

	program::login(i2, userid, ProgramID);

}