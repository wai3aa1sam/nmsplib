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

void NativeThread_Win32::create(const CreateDesc_Base& cd)
{
	auto cDesc = sCast<const CreateDesc&>(cd);

	Base::create(cd);

	if (cd.name.is_empty())
	{
		_name = "Nmsp_Thread_";
		_name += StrUtil::toTempStr(cd.localId);
	}

	_hnd = ::CreateThread(nullptr, 0, &_routine, (LPVOID)this, 0, (LPDWORD)&_threadId);
	throwIf(!_hnd, "");

	setName(_name);
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
		//_NMSP_LOG("thread-{}-{} {}: begin join",	localId(), threadId(), name());
		::WaitForSingleObject(_hnd, INFINITE);
		//_NMSP_LOG("thread-{}-{} {}: end join",		localId(), threadId(), name());
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

void		NativeThread_Win32::setName(StrViewA_T name)
{
	NMSP_ASSERT(_hnd, "");

	TempStringW_T<> nameW;
	UtfUtil::convert(nameW, _name);

	OSRet ret;
	ret = ::SetThreadDescription(_hnd, nameW.c_str());
	_NMSP_PROFILE_SET_THREAD_NAME(_name.c_str());
}

DWORD NativeThread_Win32::_routine(void* args)
{
	auto* nt = sCast<NativeThread_Win32*>(args);
	//OsTraits::setThreadLocalId(nt->localId());
	auto ret = nt->onRoutine(); NMSP_UNUSED(ret);
	return 0;
}

DWORD WINAPI NativeThread_Win32::_basicRoutine(void* cDescBase)
{
	auto* bcd = reinCast<CreateDesc_Base*>(cDescBase);
	OsTraits::setThreadLocalId(bcd->affinityIdx);

	NMSP_ASSERT(bcd->routine, "CreateDesc_Base::routine is nullptr");
	auto ret = bcd->routine(bcd->args); NMSP_UNUSED(ret);
	return 0;
}

}
#endif


#endif