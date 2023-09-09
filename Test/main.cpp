#include <argon2.h>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <vector>

std::ostream& operator<<(std::ostream& os, std::vector<unsigned char> ucVec) {
    std::ios::fmtflags f = os.flags();

    os << std::hex << std::uppercase;

    for (unsigned char uc : ucVec) os << std::setw(2) << std::setfill('0') << static_cast<int>(uc);

    os.flags(f);

    return os;
}

int main() {
    constexpr int workFactor = 3, memoryUsage = 12288;
    int threadsAndLanes = std::thread::hardware_concurrency();

    std::string content, salt;
    std::vector<unsigned char> ucCon, ucSalt, out;

    std::cout << "Enter the password to be derivated: ";

    std::getline(std::cin, content);

    ucCon.assign(
        std::make_move_iterator(content.begin()),
        std::make_move_iterator(content.end())
    );

    std::cout << "\nEnter the salt: ";

    std::getline(std::cin, salt);

    ucSalt.assign(
        std::make_move_iterator(salt.begin()),
        std::make_move_iterator(salt.end())
    );

    int size = 0;

    std::cout << "\nSet the size of the hash: ";

    std::cin >> size;

    try {
        out.resize(size);
    }
    catch (...) {
        std::cout << "\nInvalid size\n";
        return 1;
    }

    std::cout << "\nWork factor: " << workFactor << " Memory cost: " << memoryUsage << " Threads & Lanes: " << threadsAndLanes << "\n\n";

    if (argon2id_hash_raw(
        workFactor,
        memoryUsage,
        threadsAndLanes,
        ucCon.data(),
        ucCon.size(),
        ucSalt.data(),
        ucSalt.size(),
        &out[0],
        size
    ) != ARGON2_OK) {
        std::cout << "Failed hashing password\n";
        return 1;
    }

    ucCon.clear();
    ucSalt.clear();

    std::cout << out << "\n";
}