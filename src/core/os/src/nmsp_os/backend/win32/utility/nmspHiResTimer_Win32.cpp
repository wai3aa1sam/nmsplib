#include "nmsp_os-pch.h"

#include "nmspHiResTimer_Win32.h"

#if NMSP_OS_WINDOWS

namespace nmsp 
{

#if 0
#pragma mark --- nmspHiResTimer_Win32-Impl ---
#endif // 0
#if 1

HiResTimer_Win32::Cache::Cache()
{
	initFreq(freq);
}

void HiResTimer_Win32::Cache::initFreq(u64& o)
{
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	o = Util_Win32::toU64(f);
}

HiResTimer_Win32::Cache HiResTimer_Win32::s_cache;

HiResTimer_Win32::HiResTimer_Win32()
{
	reset();
}

void HiResTimer_Win32::reset() 
{
	_start = getTick();
}

double HiResTimer_Win32::get() const
{
	u64 c = getTick();
	return (double)(c - _start) / freqCount();
}

u64 HiResTimer_Win32::getTick() const
{
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);
	return Util_Win32::toU64(v);
}

u64 HiResTimer_Win32::freqCount()
{
	return s_cache.freq;
}

#endif

}

#endif