#pragma once

namespace nmsp {

#if 0
#pragma mark --- TestMovableType-Impl ---
#endif // 0
#if 1

template<size_t MAX_BYTE = 128>
struct TestMovableType
{
	using SizeType					= size_t;
	using String					= std::string;
	using Map						= std::unordered_map<SizeType, std::string>;
	template<class T> using SPtr	= std::shared_ptr<T>;

	constexpr static SizeType s_kMaxByteSize = MAX_BYTE;

	#define _INTERNAL_NEW_BYTES(ptr)				NMSP_ALLOC(ptr, s_kMaxByteSize)
	#define _INTERNAL_SIZE_TYPE_NEW_BYTES(ptr, i)	NMSP_ALLOC_T(ptr, SizeType); new(ptr) SizeType(i)

	//#define _INTERNAL_NEW_BYTES nullptr

	TestMovableType(SizeType i)
	{
		String tmp_str(std::to_string(i));
		Map tmp_map;
		tmp_map[0] = std::to_string(i);
		SizeType* sp; _INTERNAL_SIZE_TYPE_NEW_BYTES(sp, i);
		SPtr<SizeType> tmp_sptr(sp);

		index	= i;
		pBytes	= _INTERNAL_NEW_BYTES;
		str		= tmp_str;
		map		= tmp_map;
		sptr	= tmp_sptr;
	}

	TestMovableType()
	{
		String tmp_str("0");
		Map tmp_map;
		tmp_map[0] = "";
		SizeType* sp; _INTERNAL_SIZE_TYPE_NEW_BYTES(sp, 0);
		SPtr<SizeType> tmp_sptr(sp);
		*tmp_sptr = 1000;

		index	= 0;
		_INTERNAL_NEW_BYTES(pBytes);
		str		= tmp_str;
		map		= tmp_map;
		sptr	= tmp_sptr;
	}

	TestMovableType(const TestMovableType& rhs)
		: index(rhs.index), str(rhs.str), map(rhs.map), sptr(rhs.sptr) 
	{
		_INTERNAL_NEW_BYTES(pBytes);
		if (pBytes)
			memcpy(pBytes, rhs.pBytes, s_kMaxByteSize);
	}

	TestMovableType(TestMovableType&& rhs)
		: index(rhs.index), pBytes(rhs.pBytes), str(std::move(rhs.str)), map(std::move(rhs.map)), sptr(std::move(rhs.sptr))
	{
		rhs.pBytes = nullptr;
	};

	~TestMovableType()
	{
		if (pBytes)
			NMSP_FREE(pBytes);
	}

	void operator=(const TestMovableType& rhs)
	{
		if (pBytes)
			NMSP_FREE(pBytes);
		_INTERNAL_NEW_BYTES(pBytes);
		index	= rhs.index;
		str		= rhs.str;
		map		= rhs.map;
		sptr	= rhs.sptr;

		if (pBytes)
			memcpy(pBytes, rhs.pBytes, s_kMaxByteSize);
	}

	void operator=(TestMovableType&& rhs)
	{
		if (pBytes)
		{
			NMSP_FREE(pBytes);
		}
		index	= rhs.index;
		pBytes	= rhs.pBytes;
		str		= std::move(rhs.str);
		map		= std::move(rhs.map);
		sptr	= std::move(rhs.sptr);

		rhs.index	= 0;
		rhs.pBytes	= nullptr;
	}

	void operator+=(size_t n) { *(this->sptr) = n; }
	void operator-=(size_t n) { *(this->sptr) -= n; }

	bool operator==(const TestMovableType& rhs) const
	{
		return index == rhs.index && str == rhs.str && map == rhs.map && *sptr == *rhs.sptr;
	}

	bool operator!=(const TestMovableType& rhs) const
	{
		return !(this->operator==(rhs));
	}

	bool operator>(const TestMovableType& rhs)
	{
		return index > rhs.index;
	}

	bool operator>=(const TestMovableType& rhs)
	{
		return index >= rhs.index;
	}

	bool operator<(const TestMovableType& rhs)
	{
		return !operator>(rhs);
	}

	bool operator<=(const TestMovableType& rhs)
	{
		return !operator>=(rhs);
	}

	SizeType index = 0;
	u8* pBytes;
	String str;
	Map map;
	SPtr<SizeType> sptr;

	#undef _INTERNAL_NEW_BYTES
	#undef _INTERNAL_SIZE_TYPE_NEW_BYTES
};

#endif

#if 0
#pragma mark --- TestType-Impl ---
#endif // 0
#if 1

class TestType
{
public:
	TestType()  { std::cout << "default ctr" << "\n"; }
	~TestType() { std::cout << "default dtr" << "\n"; }

	TestType(const TestType& v)
	{
		std::cout << "copy ctr" << "\n";
	}
	TestType(TestType&& v) noexcept
	{
		std::cout << "move ctr" << "\n";
	}
	void operator=(const TestType& v)
	{
		std::cout << "copy op=" << "\n";
	}
	void operator=(TestType&& v) noexcept
	{
		std::cout << "move op=" << "\n";
	}
};

#endif // 0

}