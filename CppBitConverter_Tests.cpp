
#include "CppBitConverter.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

void Round_TEST()
{
	std::cout << std::endl << "Test Case1: Function->Round [Running]" << std::endl;

	double number = 20.2523665582255;
	double rounded_value_0dig = BitConverter::Round(number, 0);
	double rounded_value_1dig = BitConverter::Round(number, 1);
	double rounded_value_2dig = BitConverter::Round(number, 2);
	double rounded_value_3dig = BitConverter::Round(number, 3);
	double rounded_value_4dig = BitConverter::Round(number, 4);

	assert(rounded_value_0dig == 20);
	assert(rounded_value_1dig == 20.2);
	assert(rounded_value_2dig == 20.25);
	assert(rounded_value_3dig == 20.252);
	assert(rounded_value_4dig == 20.2523);

	std::cout << "Test Case1: Function->Round [Pass]" << std::endl;
}

void InvertBytes_TEST()
{
	std::cout << std::endl << "Test Case2: Function->InvertBytes [Running]" << std::endl;

	QByteArray arr = { 0x10,0x11,0x12,0x13 };
	QByteArray expect_result = { 0x13,0x12,0x11,0x10 };

	BitConverter::InvertBytes(arr);
	assert(arr == expect_result);

	std::cout << "Test Case2: Function->InvertBytes [Pass]" << std::endl;
}

void GetBytes_TEST()
{
	std::cout << std::endl << "Test Case3: Function->GetBytes [Running]" << std::endl;

	// double testing
	double number = 852456.852456;
	QByteArray expect_result_msb = { 0x41, 0x2A, 0x03, 0xD1, 0xB4, 0x75, 0x1C, 0xE3 };
	QByteArray expect_result_lsb = { 0xE3, 0x1C, 0x75, 0xB4, 0xD1, 0x03, 0x2A, 0x41 };

	QByteArray result = BitConverter::GetBytes(number, true); // msb calc
	assert(result == expect_result_msb);

	result = BitConverter::GetBytes(number); // lsb calc
	assert(result == expect_result_lsb);

	// int32
	int32_t number_int = -852456;
	expect_result_msb = { 0xFF, 0xF2, 0xFE, 0x18 };
	expect_result_lsb = { 0x18, 0xFE, 0xF2, 0xFF }; // 0xFFF2FE18

	result = BitConverter::GetBytes(number_int, true); // msb calc
	assert(result == expect_result_msb);

	result = BitConverter::GetBytes(number_int); // lsb calc
	assert(result == expect_result_lsb);

	// uint32
	uint32_t number_uint = 852456;
	expect_result_msb = { 0x00, 0x0D, 0x01, 0xE8 };
	expect_result_lsb = { 0xE8, 0x01, 0x0D, 0x00 }; // 000D01E8

	result = BitConverter::GetBytes(number_uint, true); // msb calc
	assert(result == expect_result_msb);

	result = BitConverter::GetBytes(number_uint); // lsb calc
	assert(result == expect_result_lsb);

	std::cout << "Test Case1: Function->GetBytes [Pass]" << std::endl;
}

void ToNumber_TEST()
{
	std::cout << std::endl << "Test Case4: Function->ToNumber [Running]" << std::endl;
	QByteArray input = { 0x00, 0x0D, 0x01, 0xE8     // uint32 msb
						, 0xE8, 0x01, 0x0D, 0x00	// uint32 lsb
						, 0xFF, 0xF2, 0xFE, 0x18	// int32 msb
						, 0x18, 0xFE, 0xF2, 0xFF	// int32 lsb
						, 0x41, 0x2A, 0x03, 0xD1, 0xB4, 0x75, 0x1C, 0xE3  // double msb
						, 0xE3, 0x1C, 0x75, 0xB4, 0xD1, 0x03, 0x2A, 0x41  // double lsb
						, 0x10, 0x11, 0x00
						};

	uint32_t result_uint32_msb = BitConverter::ToUInt32(input,0,true);
	uint32_t result_uint32_lsb = BitConverter::ToUInt32(input, 4, false);
	int32_t result_int32_msb = BitConverter::ToInt32(input,8,true);
	int32_t result_int32_lsb = BitConverter::ToInt32(input, 12, false);
	double result_double_msb = BitConverter::ToDouble(input, 16, true);
	double result_double_lsb = BitConverter::ToDouble(input, 24, false);

	uint32_t result_uint32_not_enough_byte = BitConverter::ToUInt32(input, 32, false);

	assert(result_uint32_msb == 852456);
	assert(result_uint32_lsb == 852456);
	assert(result_int32_msb == -852456);
	assert(result_int32_lsb == -852456);
	assert(result_double_msb == 852456.852456);
	assert(result_double_lsb == 852456.852456);
	assert(result_uint32_not_enough_byte == 4368);

	std::cout << "Test Case4: Function->ToNumber [Pass]" << std::endl;
}

void ToHex_TEST()
{
	std::string result = BitConverter::ToHex(852456, false);
	std::string expect_result = "0xD01E8";

	assert(result == expect_result);
}

int main()
{
	Round_TEST();
	InvertBytes_TEST();
	GetBytes_TEST();
	ToNumber_TEST();
	ToHex_TEST();
}