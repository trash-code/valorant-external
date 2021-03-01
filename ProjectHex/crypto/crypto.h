#pragma once
#include <winsvc.h>
#pragma warning (disable: 4191 4099)
#pragma comment (lib, "crypto/cryptlib.lib")
#include "aes.h"
#include "modes.h"
#include "base64.h"
#include "hex.h"
#include <iosfwd>
#include "stdcpp.h"
#include <algorithm>
#include <winioctl.h>
#include <winternl.h>
#include <iostream>
#include <string>
#include <random>

class security
{
public:
	static std::string encrypt(const std::string str_in, const std::string key, const std::string iv);
	static std::string decrypt(const std::string str_in, const std::string key, const std::string iv);
	static std::vector<unsigned char> encrypt_decrypt_data(std::vector<unsigned char> data, std::vector<unsigned char> key);
	static std::string random_string(int len);
	static std::string random_num(int len);
	static std::string random_string2(int len);
	std::string key_enc;
	std::string key;
	std::string iv;
private:
};
