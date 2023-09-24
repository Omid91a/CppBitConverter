#include "CppBitConverter.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>

double BitConverter::Round(double value, int dec)
{
	double factor = pow(10, dec);
	int temp = value * factor;
	return (double)temp / factor;
}

void BitConverter::InvertBytes(QByteArray& data)
{
	for (auto first = data.begin(), last = data.end() - 1; first < last; first++, last--)
		std::swap(*first, *last);
}

template <typename T>
QByteArray BitConverter::GetBytes(T value, bool msb)
{
	auto casted_value = reinterpret_cast<char*>(&value);
	QByteArray ret(casted_value, casted_value + sizeof(T));

	if (msb)
		InvertBytes(ret);

	return ret;
}

//
// Summary:
//     Returns the specified 16-bit signed integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 2.
QByteArray BitConverter::GetBytes(uint16_t value, bool msb)
{
	return GetBytes<uint16_t>(value, msb);
}

//
// Summary:
//     Returns the specified 32-bit signed integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 4.
QByteArray BitConverter::GetBytes(int value, bool msb)
{
	return GetBytes<int>(value, msb);
}

//
// Summary:
//     Returns the specified 64-bit signed integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 8.
QByteArray BitConverter::GetBytes(long value, bool msb)
{
	return GetBytes<long>(value, msb);
}

//
// Summary:
//     Returns the specified 32-bit unsigned integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 4.
QByteArray BitConverter::GetBytes(unsigned int value, bool msb)
{
	return GetBytes<unsigned int>(value, msb);
}

//
// Summary:
//     Returns the specified 32-bit unsigned integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 4.
QByteArray BitConverter::GetBytes(uint64_t value, bool msb)
{
	return GetBytes<uint64_t>(value, msb);
}

//
// Summary:
//     Returns the specified 64-bit unsigned integer value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 8.
QByteArray BitConverter::GetBytes(unsigned long value, bool msb)
{
	return GetBytes<unsigned long>(value, msb);
}

//
// Summary:
//     Returns the specified single-precision floating point value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 4.
QByteArray BitConverter::GetBytes(float value, bool msb)
{
	return GetBytes<float>(value, msb);
}

//
// Summary:
//     Returns the specified double-precision floating point value as an array of bytes.
//
// Parameters:
//   value:
//     The number to convert.
//
// Returns:
//     An array of bytes with length 8.
QByteArray BitConverter::GetBytes(double value, bool msb)
{
	return GetBytes<double>(value, msb);
}

template <class T>
T BitConverter::ToNumber(QByteArray bytes, int start_index, bool msb)
{
	if (bytes.size() >= start_index + sizeof(T))
	{
		if (msb)
		{
			QByteArray temp(&bytes[start_index], &bytes[start_index + sizeof(T)]);
			InvertBytes(temp);

			return *reinterpret_cast<const T*>(&temp[0]);
		}
		else
			return *reinterpret_cast<const T*>(&bytes[start_index]);
	}
	else
	{
		auto end_index = bytes.size() - 1;

		QByteArray temp(&bytes[start_index], &bytes[end_index] + 1);
		temp.resize(sizeof(T));

		if (msb)
			InvertBytes(temp);

		return *reinterpret_cast<const T*>(&temp[0]);
	}
}
//
// Summary:
//     Returns a double-precision floating point number converted from eight bytes at
//     a specified position in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A double precision floating point number formed by eight bytes beginning at startIndex.
double BitConverter::ToDouble(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<double>(value, startIndex, msb);
}

//
// Summary:
//     Returns a 16-bit signed integer converted from two bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 16-bit signed integer formed by two bytes beginning at startIndex.
short BitConverter::ToInt16(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<int16_t>(value, startIndex, msb);
}

//
// Summary:
//     Returns a 32-bit signed integer converted from four bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 32-bit signed integer formed by four bytes beginning at startIndex.
int BitConverter::ToInt32(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<int32_t>(value, startIndex, msb);
}

//
// Summary:
//     Returns a 64-bit signed integer converted from eight bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 64-bit signed integer formed by eight bytes beginning at startIndex.
long BitConverter::ToInt64(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<int64_t>(value, startIndex, msb);
}

//
// Summary:
//     Converts the numeric value of each element of a specified array of bytes to its
//     equivalent hexadecimal string representation.
//
// Parameters:
//   value:
//     a number
//
// Returns:
//     A string of hexadecimal.
std::string BitConverter::ToHex(uint64_t value, bool msb)
{
	std::stringstream stream;
	stream << std::hex << value;
	std::string result = stream.str();

	std::transform(result.begin(), result.end(), result.begin(), ::toupper);

	return "0x" + result;
}

//
// Summary:
//     Returns a 16-bit unsigned integer converted from two bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     The array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 16-bit unsigned integer formed by two bytes beginning at startIndex.
unsigned short BitConverter::ToUInt16(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<uint16_t>(value, startIndex, msb);
}

//
// Summary:
//     Returns a 32-bit unsigned integer converted from four bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 32-bit unsigned integer formed by four bytes beginning at startIndex.
unsigned int BitConverter::ToUInt32(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<uint32_t>(value, startIndex, msb);
}

//
// Summary:
//     Returns a 64-bit unsigned integer converted from eight bytes at a specified position
//     in a byte array.
//
// Parameters:
//   value:
//     An array of bytes.
//
//   startIndex:
//     The starting position within value.
//
// Returns:
//     A 64-bit unsigned integer formed by the eight bytes beginning at startIndex.
uint64_t BitConverter::ToUInt64(QByteArray value, int startIndex, bool msb)
{
	return ToNumber<uint64_t>(value, startIndex, msb);
}

//
// Summary:
//     This method will use in show a counter when that could be big
//     and have variation. this method split the counter and append a sufix lik K(kilo), M(milion) and B(bilion).
//
// Parameters:
//   value:
//     A double or int value;
//
// Returns:
//     A string with a sufix.
std::string BitConverter::GetNumberStrWithUnit(double value)
{
	double factor = 1;
	std::string sufix;

	if (std::abs(value) <= 1000)
	{
		sufix = "";
		factor = 1.0;
	}
	else if (std::abs(value) <= 1000000)
	{
		sufix = " K";
		factor = 1000.0;
	}
	else if (std::abs(value) <= 1000000000)
	{
		sufix = " M";
		factor = 1000000.0;
	}
	else if (std::abs(value) > 1000000000)
	{
		sufix = " B";
		factor = 1000000000.0;
	}
	//
	double temp = value / factor;
	if (temp > 1)
		temp = (double)((int)(temp / 1000.0)) * 1000.0; // 3 digit precise

	return std::to_string(temp) + sufix;
}
