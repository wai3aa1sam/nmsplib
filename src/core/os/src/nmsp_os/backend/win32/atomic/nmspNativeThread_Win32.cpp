#include "nmsp_os-pch.h"

#include "nmspNativeThread_Win32.h"

#if NMSP_OS_WINDOWS

#if 0
#pragma mark --- NativeThread_Win32-Impl ---
#endif // 0
#if 1
namespace nmsp {

NativeThread_Win32::~NativeThread_Win32()
{
	#if NMSP_DEBUG
	NMSP_ASSERT(_isJoined,	"must call join() on derived class, also should be awaked");
	#endif // NMSP_DEBUG
	NMSP_ASSERT(!_hnd,		"must call join() on derived class, also should be awaked");
}

void NativeThread_Win32::create(const CreateDesc& cd)
{
	Base::create(cd);

	if (cd.name.is_empty())
	{
		_name = "My_Thread_";
		_name += StrUtil::toTempStr(cd.affinityIdx);
	}

	TempStringW_T<> nameW;
	UtfUtil::convert(nameW, _name);

	_hnd = ::CreateThread(nullptr, 0, &_routine, (LPVOID)this, 0, (LPDWORD)&_threadId);
	throwIf(!_hnd, "");

	OSRet ret;
	ret = ::SetThreadDescription(_hnd, nameW.c_str());
	_NMSP_PROFILE_SET_THREAD_NAME(_name.c_str());

	setAffinity(cd.affinityIdx);

	#if NMSP_DEBUG
	_isJoined = false;
	#endif // NMSP_DEBUG
}

void		NativeThread_Win32::join				()
{
	if (_hnd)
	{
		#if NMSP_DEBUG
		_isJoined = true;
		#endif // NMSP_DEBUG
		::WaitForSingleObject(_hnd, INFINITE);
		_hnd = 0;
	}
}

void		NativeThread_Win32::setAffinity		(int k_th_bit)
{
	if (k_th_bit == -1 || k_th_bit == 0)
		return;

	NMSP_ASSERT(_hnd);
	::SetThreadAffinityMask(_hnd, 1LL << k_th_bit);
}

size_t		NativeThread_Win32::threadId			()
{
	return _threadId;
}

ThreadHnd	NativeThread_Win32::nativeHnd			()
{
	return _hnd;
}

DWORD NativeThread_Win32::_routine(void* args)
{
	auto* nt = static_cast<NativeThread_Win32*>(args);
	OsTraits::setThreadLocalId(nt->localId());
	auto ret = nt->onRoutine(); NMSP_UNUSED(ret);
	return 0;
}

DWORD WINAPI NativeThread_Win32::_basicRoutine(void* basicCreateDesc)
{
	auto* bcd = reinterpret_cast<BasicCreateDesc*>(basicCreateDesc);
	OsTraits::setThreadLocalId(bcd->affinityIdx);

	NMSP_ASSERT(bcd->routine, "BasicCreateDesc::routine is nullptr");
	auto ret = bcd->routine(bcd->args); NMSP_UNUSED(ret);
	return 0;
}

}
#endif


#endif