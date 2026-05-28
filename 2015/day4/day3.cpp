// md5_win.cpp
#include <windows.h>
#include <wincrypt.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

#pragma comment(lib, "advapi32.lib") // con MSVC

std::string md5_hex_win(const std::string& input) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    std::string result;

    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("CryptAcquireContextA failed");
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        throw std::runtime_error("CryptCreateHash failed");
    }

    if (!CryptHashData(hHash, reinterpret_cast<const BYTE*>(input.data()), (DWORD)input.size(), 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        throw std::runtime_error("CryptHashData failed");
    }

    DWORD cbHash = 0;
    DWORD cbSize = sizeof(DWORD);
    CryptGetHashParam(hHash, HP_HASHVAL, NULL, &cbHash, 0);

    std::vector<BYTE> pbHash(cbHash);
    if (!CryptGetHashParam(hHash, HP_HASHVAL, pbHash.data(), &cbHash, 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        throw std::runtime_error("CryptGetHashParam failed");
    }

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (DWORD i = 0; i < cbHash; ++i) {
        oss << std::setw(2) << static_cast<int>(pbHash[i]);
    }
    result = oss.str();

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    return result;
}

bool check_for_leading_0(string hash){
    for (int i=0; i<6; i++){
        if (hash.at(i)!='0'){
            return false;
        }
    }
    return true;
}

int main() {
    const std::string input = "yzbqklnj";
    int solution{0};
    std::string hash_text{};
    
    do{
        ++solution;
        std::string attempt = input + std::to_string(solution); 
        cout<< "provo con " << solution << endl;
        try {
            hash_text = md5_hex_win(attempt);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    } while ( !check_for_leading_0(hash_text) );

    cout << "La soluzione e': " << solution << endl;
    cout << "hash e' " << md5_hex_win(input + std::to_string(solution)) << endl;

    return 0;
}
