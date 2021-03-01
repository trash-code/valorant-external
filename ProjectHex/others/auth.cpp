#pragma warning (disable : 4996);
#pragma comment (lib, "advapi32.lib")
#include "auth.h"
#include <iostream>
#include <string>
#include "../others/hwid.h"
#include <iostream>
#include <stdio.h>
#include "../curl/curl.h"
#include "../crypto/crypto.h"
#include "../others/xor.h"
#include "../program.h"
#include "../hashlib/md5wrapper.h"

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")

std::string arep;
std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer);
}
size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
    s->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
void strGetRandomAlphaNum(std::string sStr, unsigned int iLen)
{
    char Syms[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int Ind = 0;
    srand(time(NULL) + rand());
    while (Ind < iLen)
    {
        sStr[Ind++] = Syms[rand() % 62];
    }
    sStr[iLen] = '\0';
}
std::string gen_random(const int len) {

    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand((unsigned)time(NULL) * getpid());

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;

}
void program::login(std::string key, std::string userid, std::string pid)
{
    std::string akey = gen_random(32);
    std::string aiv = gen_random(16);
    std::string eakey;
    std::string eaiv;
    auto md5 = new md5wrapper();
    std::string hash = md5->getHashFromFile(GetCurrentDirectory());
    std::string ekey;
    std::string euid = security::encrypt(userid, akey, aiv);
    std::string epid = security::encrypt(pid, akey, aiv);
    std::string ehwid;
    CryptoPP::StringSource ss(hwid::get_hardware_id("123"), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(ehwid)));
    CryptoPP::StringSource ss1(key, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(ekey)));
    CryptoPP::StringSource ss2(akey, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(eakey)));
    CryptoPP::StringSource ss3(aiv, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(eaiv)));
    while (epid.find("+") != std::string::npos)
    {
        akey = gen_random(32);
        aiv = gen_random(16);
        euid = security::encrypt(userid, akey, aiv);
        epid = security::encrypt(pid, akey, aiv);
    }

    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURL* curl = curl_easy_init();
        if (curl)
        {
            std::string ssl = _xor_("sha256//auV7j2KCAfgiTpHH3hcm8ULVeAZSNeuGB9+SlYkR3/o=");
            std::string s;
            std::string api = _xor_("https://panel.proxine.ninja/api/login.php?id=").c_str() + ekey + _xor_("&uuid=").c_str() + euid + _xor_("&hwid=").c_str();
            std::string login = api + ehwid + _xor_("&name=").c_str() + eakey + _xor_("&current=").c_str() + eaiv + _xor_("&a=\"").c_str() + epid + _xor_("\"&h=").c_str() + hash;
            curl_easy_setopt(curl, CURLOPT_URL, login.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, ssl.c_str());
            CURLcode res = curl_easy_perform(curl);
            arep = security::decrypt(s.c_str(), akey, aiv);
            curl_easy_cleanup(curl);
        }
    }
    if (arep == _xor_("334").c_str())
    {
        std::cout << _xor_("Please Ask Owner For New App");
        Sleep(5000);
        exit(0);
    }
    if (arep == _xor_("333").c_str())
    {
        std::cout << _xor_("License Invalid");
        Sleep(5000);
        exit(0);
    }
    if (arep == _xor_("999").c_str())
    {
        std::cout << _xor_("License Expired");
        Sleep(5000);
        exit(0);
    }
    if (arep == _xor_("450").c_str())
    {
        IsValid = true;
        std::cout << _xor_("Authenticating...");
        //Sleep(1000);
        system("cls");
        main::program();
    }
    if (arep == _xor_("666").c_str())
    {
        std::cout << _xor_("HWID Mismatch");
        Sleep(5000);
        exit(0);
    }

}