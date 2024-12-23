//Task1
#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>

std::string toBCD(int decimal) {
    std::string bcd = "";
    while (decimal > 0) {
        int digit = decimal % 10;
        std::bitset<4> bcd_digit(digit);
        bcd = bcd_digit.to_string() + " " + bcd;
        decimal /= 10;
    }
    return bcd;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <decimal_number> <conversion_code: hex|oct|bin|bcd>\n";
        return 1;
    }

    int decimal = atoi(argv[1]);
    std::string conversionType = argv[2];

    if (conversionType == "hex") {
        std::cout << "0x" << std::hex << decimal << std::endl;
    }
    else if (conversionType == "oct") {
        std::cout << "0" << std::oct << decimal << std::endl;
    }
    else if (conversionType == "bin") {
        std::cout << std::bitset<32>(decimal) << std::endl;
    }
    else if (conversionType == "bcd") {
        std::cout << toBCD(decimal) << std::endl;
    }
    else {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    return 0;
}
