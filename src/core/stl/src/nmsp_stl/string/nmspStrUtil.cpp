#include "nmsp_stl-pch.h"

#include "nmspStrUtil.h"

namespace nmsp {

void StrUtil::appendBinToHex(StringT& result, ByteSpan_T data)
{
	const char* hex = "0123456789ABCDEF";
	size_t lineCount = (data.size() + 15) / 16;

	for (size_t line = 0; line < lineCount; line++) 
	{
		size_t lineStart = line * 16;
		for (size_t i = 0; i < 16; i++) {
			size_t index = lineStart + i;

			if (index < data.size()) 
			{
				u8 v = data[index];
				result.push_back(hex[v >> 4]);
				result.push_back(hex[v & 0xF]);
			} else {
				result.append("  ");
			}
			result.push_back(' ');
		}

		result.append("    ");

		for (size_t i = 0; i < 16; i++) 
		{
			size_t index = lineStart + i;

			if (index < data.size()) {
				u8 v = data[index];
				if (v < 32) {
					result.push_back(' '); // non-printable character
				} else {
					result.push_back(v);
				}
			} else {
				result.push_back(' ');
			}
			//			result.push_back(' ');
		}

		result.push_back('\n');
	}
}

const char* StrUtil::findChar(StrViewA_T view, StrViewA_T charList, bool ignoreCase) 
{
	auto* start = view.data();
	auto* end = start + view.size();
	auto* p = start;

	if (ignoreCase) 
	{
		for ( ; p < end; p++ ) 
		{
			for (auto& ch : charList) 
			{
				if (ignoreCaseCompare(*p, ch) == 0) 
				{
					return p;
				}
			}
		}
	} 
	else 
	{
		for ( ; p < end; p++ ) 
		{
			for (auto& ch : charList) 
			{
				if (*p == ch) 
				{
					return p;
				}
			}
		}
	}
	return nullptr;
}

const char* StrUtil::findCharFromEnd(StrViewA_T view, StrViewA_T charList, bool ignoreCase) 
{
	if (view.size() <= 0) return nullptr;

	auto* start = view.data();
	auto* end = start + view.size();
	auto* p = end - 1;

	if (ignoreCase) 
	{
		for ( ; p >= start; p-- ) 
		{
			for(auto& ch : charList) 
			{
				if (ignoreCaseCompare(*p, ch) == 0) 
				{
					return p;
				}
			}
		}
	} 
	else 
	{
		for ( ; p >= start; p-- ) 
		{
			for(auto& ch : charList) 
			{
				if (*p == ch) 
				{
					return p;
				}
			}
		}
	}
	return nullptr;
}

int StrUtil::ignoreCaseCompare(StrViewA_T a, StrViewA_T b)
{
	size_t n = std::min(a.size(), b.size());
	for (size_t i = 0; i < n; i++) 
	{
		int c = ignoreCaseCompare(a[i], b[i]);
		if (c != 0) return c;
	}
	if (a.size() < b.size()) return -1;
	if (a.size() > b.size()) return 1;
	return 0;
}

bool StrUtil::isSame(StrViewA_T  a, StrViewA_T  b)
{
	return a.size() == b.size() && isSame(a.data(), b.data());
}

bool StrUtil::isSame(const char* a, const char* b)
{
	return ::strcmp(a, b) == 0;
}

bool StrUtil::isDigit		(char ch)	{ return ch >= '0' && ch <= '9'; }
bool StrUtil::isAlpha		(char ch)	{ return isLowerCase(ch) || isUpperCase(ch); }
bool StrUtil::isLowerCase	(char ch)	{ return ch >= 'a' && ch <= 'z'; }
bool StrUtil::isUpperCase	(char ch)	{ return ch >= 'A' && ch <= 'Z'; }



}