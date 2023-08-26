#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"

//#include "nmsp_os/native_ui/base/nmspHiResTimer_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp 
{

#if 0
#pragma mark --- nmspHiResTimer_Win32-Decl ---
#endif // 0
#if 1

class HiResTimer_Win32
{
private:
	struct Cache	// only useful in c++11
	{
		Cache();
		static void initFreq(u64& o);
	public:
		u64 freq;
	};

public:
	static const size_t s_kMicroInv = 1000000;
	static const size_t s_kMilliInv = 1000;

public:
	//static void init();
	//template<ns> struct<ns>
	//template<us> struct<us>
	//template<ms> struct<ms>
	// double get(), u64 getCount()

public:
	HiResTimer_Win32();

	void	reset();

	double	get()		const;
	u64		getCount()	const;

	double	startTime()		 const;
	u64		startTimeCount() const;

	static u64 freqCount();

private:
	u64 getTick() const;

private:
	static Cache s_cache;
	//u64 _freq;
	u64 _start;
};

inline double	HiResTimer_Win32::startTime()		const { return sCast<double>(_start) / freqCount(); }
inline u64		HiResTimer_Win32::startTimeCount()	const { return _start; }
inline u64		HiResTimer_Win32::getCount()		const { u64 c = getTick(); return (c - _start); }


#endif

}


#endif
