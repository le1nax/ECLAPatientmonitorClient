#pragma once

#include <cmath>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <cstring>
#include <codecvt>
#include <locale>
#include <iomanip>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "imgui.h"

/// @brief Bool value that determines if debug meassages are put out. Strongly effects the efficiency of the measurement
static constexpr bool configModeDebug = false;
/// @brief Sets the maximum value of the sent buffer
static constexpr size_t maxbuffersize = 2001;
/// @brief buffersize of the payload message
static constexpr size_t valuebuffersize = sizeof(int32_t);
/// @brief buffersize of the beacon value of the message
static constexpr size_t beaconbuffersize = sizeof(uint8_t);
/// @brief buffersize of the timestamp
static constexpr size_t timestampbuffersize = sizeof(uint16_t);
/// @brief buffersize of the messagecounter
static constexpr size_t counterbuffersize = beaconbuffersize;
/// @brief conversion factor of the payload value, used for HW Press
static constexpr double canPressConversionFactor = 1e-2;
/// @brief conversion factor of the payload value, used for HW Temperature
static constexpr double canTempConversionFactor = 1e-2;
/// @brief maximum number of displayable Pressure values, before the display resets (cyclic plot)
static constexpr size_t maxNumberOfPressValues = 10000;
/// @brief maximum number of displayable Temperature values, before the display resets (cyclic plot)
static constexpr size_t maxNumberOfTemperatureValues = 10000;
/// @brief lowest displayable plot value for Honeywell Pressure Value
static constexpr int64_t lowestCanPressValue = -1500;
/// @brief highest displayable plot value for Honeywell Pressure Value
static constexpr int64_t highestCanPressValue = 1500;
/// @brief lowest displayable plot value for Honeywell Temperature Value
static constexpr int64_t lowestCanTemperatureValue = -10;
/// @brief highest displayable plot value for Honeywell Temperature Value
static constexpr int64_t highestCanTemperatureValue = 50;

/// @brief Enum class defining the type of a DataPoint
enum class DataPointType 
{
    BP = 0, 
    ECG = 1, 
    CONFIG = 2,
    DEBUG = 3
};

/// @brief Enum class defining the CanIDs. It is used to process incoming messages.
enum class EnumCanID
{
    PRESS =     0x102A0010, 
    TEMP =      0x102A0020,
    SFM3300 =   0x102A0060, 
    CONFIG = 2,
    DEBUG = 3
};

/// @brief Template function that formates an input type of integers into a byte vector
/// @return vector of std::byte
template<typename... Ts>
std::vector<std::byte> make_bytes(Ts&&... args) noexcept {
return{std::byte(std::forward<Ts>(args))...};
}
/// @brief This function swaps the endianness of a char buffer
/// @param buffer Points to the first char of the buffer
/// @param size integer size of the buffer
static void swapEndianness(char* buffer, size_t size) {
    for (size_t i = 0; i < size / 2; ++i) {
        // Swap bytes using XOR
        buffer[i] ^= buffer[size - i - 1];
        buffer[size - i - 1] ^= buffer[i];
        buffer[i] ^= buffer[size - i - 1];
    }
}

/// @brief Debug function that outputsa certain amount of Bytes from a buffer
/// @param array Points to the first char of the buffer
/// @param numBytes The number of bytes to read
static void readBytesFromArray(const char* array, size_t numBytes) {
    for (size_t i = 0; i < numBytes; ++i) {
        if(configModeDebug) {
            std::cout << std::hex << static_cast<int>(static_cast<uint8_t>(array[i])) << " ";
            std::cout << std::endl;
        }
    }
}

/// @brief Replaces null characters from a given input string
/// @param inputString The given input string
/// @return outputs the inputString without null characters
static std::string ReplaceNullCharacters(const std::string& inputString) {
    std::string outputString = inputString;
    size_t pos = outputString.find('\0');
    while (pos != std::string::npos) {
        outputString.replace(pos, 1, "");
        pos = outputString.find('\0', pos);
    }
    return outputString;
}

/// @brief Extracts a 16 bit unsigned integer 
/// @param sourcevalue unsigned 32 bit source integer
/// @return extracted unsigned 16 bit return value
static uint16_t Get16bitLSBfromUInt(uint32_t sourcevalue)
        {
            uint32_t lsb = (sourcevalue & 0xFFFF);
            return (uint16_t)lsb;
        }

/// @brief String manipulation function, trims an input string to its first elements that are non whitespace
static std::string TrimString(const std::string& inputString) {
    std::string trimmedString = inputString;
    size_t firstNonWhitespace = trimmedString.find_first_not_of(" \t\r\n");
    size_t lastNonWhitespace = trimmedString.find_last_not_of(" \t\r\n");
    if (firstNonWhitespace != std::string::npos && lastNonWhitespace != std::string::npos) {
        trimmedString = trimmedString.substr(firstNonWhitespace, lastNonWhitespace - firstNonWhitespace + 1);
    }
    else {
        trimmedString.clear();
    }
    return trimmedString;
}

/// @brief Converts utf8 to string 
static std::string Utf8ToString(const std::string& utf8String)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(utf8String);
    std::string outputString(wideString.begin(), wideString.end());
    return outputString;
}

/// @brief size of unsigned short integer (16 bit)
static inline constexpr size_t uInt16Size = sizeof(unsigned short);

/// @brief Reads Byte Values from a given buffer, assuming little endian 
static unsigned long ReadByteValuesFromBufferLittleEndian(const char* buffer, unsigned long  startIndex, unsigned long  numBytesToRead)
{
    unsigned long  value;
    std::memcpy(&value, buffer + startIndex, numBytesToRead);
    return value;
}

/// @brief reads value from given buffer with a given length (16 Bytes)
static unsigned long Read16ByteValuesFromBufferLittleEndian(const char* buffer, unsigned long  startIndex)
{
    unsigned long  value;
    std::memcpy(&value, buffer + startIndex, uInt16Size);
    return value;
}

static std::string formatTm(const struct tm& timeInfo) {
    std::ostringstream oss;

    oss << std::setfill('0');  // Set fill character to '0'

    // Format date components: dd-MM-yyyy
    oss << std::setw(2) << timeInfo.tm_mday << "-"
        << std::setw(2) << (timeInfo.tm_mon + 1) << "-"
        << std::setw(4) << (timeInfo.tm_year + 1900) << " ";

    // Format time components: HH:mm:ss.fff
    oss << std::setw(2) << timeInfo.tm_hour << ":"
        << std::setw(2) << timeInfo.tm_min << ":"
        << std::setw(2) << timeInfo.tm_sec << "."
        << std::setw(3) << 0 << std::setfill('0');  // Fill milliseconds with '0'

    return oss.str();
}


static int BinaryCodedDecimalToInteger(int value)
        {
            if (value != 0xFF)
            {
                int lowerNibble = value & 0x0F;
                int upperNibble = value >> 4;

                int multipleOfOne = lowerNibble;
                int multipleOfTen = upperNibble * 10;

                return (multipleOfOne + multipleOfTen);
            }
            else return 0;
        }

static std::unique_ptr<char[]> ReadBytesFromBuffer(const char* array, size_t startIndex, size_t numBytes) {
    std::unique_ptr<char[]> output(new char[numBytes]);

    for (size_t i = 0; i < numBytes; ++i) {
        output[i] = array[startIndex + i];
    }

    return output;
}

static uint16_t Read16ByteValuesFromBuffer(const char* buffer, size_t startIndex) {
    char* buf = ReadBytesFromBuffer(buffer, startIndex, uInt16Size).release();
    unsigned long  value = 0;
    std::memcpy(&value, buf, uInt16Size);
    delete[] buf;
    return value;
}


/// @todo exeption handling 
static int32_t ReadByteSignedValuesFromBuffer(const char* buffer, unsigned long  startIndex, unsigned long  numBytesToRead)
{
    auto buf = ReadBytesFromBuffer(buffer, startIndex, numBytesToRead).release();
    // unsigned long  value = 0;
    // std::memcpy(&value, buf, numBytesToRead);

    int32_t interpretedValue = *(int*)buf;
    delete[] buf;
    return interpretedValue;
}   