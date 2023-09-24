#include <math.h>
#include <cstdint>
#include <vector>
#include <string>

typedef std::vector<unsigned char> QByteArray;

class BitConverter
{
public:
    static double Round(double value, int dec);
    static void InvertBytes(QByteArray &data);

    template <typename T>
    static QByteArray GetBytes(T value, bool msb);

    static QByteArray GetBytes(uint16_t value, bool msb = false);
    static QByteArray GetBytes(int value, bool msb = false);
    static QByteArray GetBytes(long value, bool msb = false);
    static QByteArray GetBytes(unsigned int value, bool msb = false);
    static QByteArray GetBytes(uint64_t value, bool msb = false);
    static QByteArray GetBytes(unsigned long value, bool msb = false);
    static QByteArray GetBytes(float value, bool msb = false);
    static QByteArray GetBytes(double value, bool msb = false);

    template <class T>
    static T ToNumber(QByteArray bytes, int start_index, bool msb);

    static double ToDouble(QByteArray value, int startIndex, bool msb = false);
    static short ToInt16(QByteArray value, int startIndex, bool msb = false);
    static int ToInt32(QByteArray value, int startIndex, bool msb = false);
    static long ToInt64(QByteArray value, int startIndex, bool msb = false);
    static std::string ToHex(uint64_t value, bool msb = false);
    static unsigned short ToUInt16(QByteArray value, int startIndex, bool msb = false);
    static unsigned int ToUInt32(QByteArray value, int startIndex, bool msb = false);
    static uint64_t ToUInt64(QByteArray value, int startIndex, bool msb = false);
    static std::string GetNumberStrWithUnit(double cnt);
};
