#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

#if 0
#pragma mark --- Function_T-Decl ---
#endif // 0
#if 1

template <class T1, class T2> using EnableIfNotFunction_T = std::enable_if_t< !IsSame< Decay<T1>, Decay<T2> > >;

template<class T, size_t LOCAL_SIZE = 32, size_t ALIGN = StlTraits::s_kDefaultAlign, class FALLBACK_ALLOCATOR = DefaultAllocator>
class Function_T;

template<class RET, class... PARAMS, size_t LOCAL_SIZE, size_t ALIGN, class FALLBACK_ALLOCATOR>
class Function_T<RET(PARAMS...), LOCAL_SIZE, ALIGN, FALLBACK_ALLOCATOR> /*: public NonCopyable*/
{
public:
	using FallbackAllocator = FALLBACK_ALLOCATOR;
	using This				= Function_T<RET(PARAMS...), LOCAL_SIZE, ALIGN, FallbackAllocator>;
	using Allocator			= LocalAllocator_T<LOCAL_SIZE, ALIGN, FallbackAllocator>;

	using SizeType			= StlTraits::SizeType;

	static constexpr SizeType s_kLocalSize			= LOCAL_SIZE;
	static constexpr SizeType s_kAlign				= ALIGN;
	static constexpr bool	  s_enableFallbackAlloc = Allocator::s_enableFallbackAlloc;

	using FuncType									= RET(PARAMS...);
	template<class FUNC> using EnableIfNotFunction	= EnableIfNotFunction_T<FUNC, Function_T>;
	//template <class T> using UPtr					= eastl::unique_ptr<T, UPtr_Deleter<LocalBuffer> >
	class IFunctor;

public:
	Function_T() noexcept
		: _ftr(nullptr)
	{}

	Function_T(NullPtr) noexcept
		: _ftr(nullptr)
	{}

	Function_T(const Function_T& rhs)
	{
		_clone(rhs);
	}

	Function_T(Function_T&& rhs) noexcept
	{
		_move(std::move(rhs));
	}

	template<class FUNC, class = EnableIfNotFunction<FUNC>>
	Function_T(FUNC&& func)
	{
		_ctor(std::forward<FUNC>(func));
	}

	void operator=(const Function_T& rhs) 
	{
		_free();
		_clone(rhs);
	}

	void operator=(Function_T&& rhs) noexcept
	{
		_free();
		_move(std::move(rhs));
	}

	template<class FUNC, class = EnableIfNotFunction<FUNC> >
	void operator=(FUNC&& func) noexcept
	{
		_free();
		_ctor(std::forward<FUNC>(func));
	}

	~Function_T()
	{
		_free();
	}

	RET operator()(PARAMS&&... params)
	{
		return _ftr->operator()(std::forward<PARAMS>(params)...);
	}

	RET operator()(PARAMS&&... params) const
	{
		return _ftr->operator()(std::forward<PARAMS>(params)...);
	}

	explicit operator bool() const 
	{
		return _ftr != nullptr;
	}

	void operator=(NullPtr) 
	{
		_reset();
	}

	bool operator==(NullPtr) const
	{
		return _ftr == nullptr;
	}

private:
	template<class FUNC = void>
	static constexpr void staticCheck()
	{
		//static_assert(IsSame<FUNC, void>|| FUNC is callable, "FUNC in Function is not a callable");
		//static_assert(std::is_convertible_v<FUNC, decltype(std::function<FuncType>)>,	"Function_T: Wrong Signature!");
		//static_assert(IsFunction<FUNC>,													"Function_T: Type is not a function!");
		NMSP_S_ASSERT(sizeof(FUNC) <= s_kLocalSize || s_enableFallbackAlloc,			"Function_T: localBuf overflow");
	}

	template<class FUNC>
	void _ctor(FUNC&& func)
	{
		using Func		= Decay<FUNC>;
		using Functor	= Functor<Func>;
		staticCheck<Functor>();

		auto* buf	= _allocator.alloc(sizeof(Functor));
		auto* pfunc = new(buf) Functor(std::forward<Func>(func));
		_reset(pfunc);
	}

	void _clone(const Function_T& rhs)
	{
		if (this == &rhs) 
			return;
		IFunctor* pfunc = nullptr;
		if (rhs)
		{
			auto* buf	= _allocator.alloc(rhs._ftr->size());
			pfunc		= rhs._ftr->clone(buf);
		}
		_reset(pfunc);
	}

	void _move(Function_T&& rhs)
	{
		if (this == &rhs) 
			return;
		IFunctor* pfunc = nullptr;
		if (rhs)
		{
			auto* buf	= _allocator.alloc(rhs._ftr->size());
			pfunc		= rhs._ftr->clone(buf);
		}
		_reset(pfunc);

		rhs._free();
	}

	void _free()
	{
		if (_ftr && !_allocator.isUsingLocalBuf(_ftr))
		{
			_allocator.free(_ftr);
		}
		_reset();
	}

	void _reset(IFunctor* p = nullptr)
	{
		_ftr = p;
	}

private:

	//template<class RET, class... PARAMS, class FALLBACK_ALLOCATOR>
	class IFunctor
	{
	public:
		virtual ~IFunctor()							= default;
		virtual RET operator()(PARAMS&&...) const	= 0;
		virtual IFunctor* clone(void* buf) const	= 0;

		virtual SizeType size() const = 0;
	};

	template<class FUNC>
	class Functor final : public IFunctor
	{
	public:
		using Func		= Decay<FUNC>;

	public:
		template<typename FUNCTOR>
		Functor(FUNCTOR&& func)
			: _func(nmsp::forward<FUNCTOR>(func))
		{}

		~Functor()
		{
		}

		//virtual RET operator()(PARAMS&&... params) const override { return _func(std::forward<PARAMS>(params)...); }
		virtual RET operator()(PARAMS&&... params) const override	{ return std::invoke(_func, nmsp::forward<PARAMS>(params)...); }

		virtual IFunctor* clone(void* buf) const override 
		{
			staticCheck<Functor>();
			return new(buf) Functor(_func); 
		};

		virtual SizeType size() const 
		{ 
			return sizeof(Functor);
		}

	private:
		FUNC _func;
	};

private:
	Allocator	_allocator;
	IFunctor*	_ftr = nullptr;
};


#endif

#if 0
#pragma mark --- Function-Impl ---
#endif // 0
#if 1





#endif

}