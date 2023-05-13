#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmspBasicJson.h"

/*
references:
- src/core/serializer/json/JsonSerializer.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- JsonSerializer_T-Decl ---
#endif // 0
#if 1

class JsonSerializer_T;

template<class T>
struct JsonIO
{
	template<class SE>
	static void onJson(const T& v, SE& se);
};

template<class T, class ENABLE = void>
struct JsonSerializer_Helper
{
	static void io(const T& v, JsonSerializer_T& se) 
	{
		JsonIO<T>::onJson(v, se);
	}
};


class JsonSerializer_T
{
public:
	using Json = Json_T;

	template<class T, class ENABLE> friend struct JsonSerializer_Helper;

	using SizeType = FileIoTraits::SizeType;

public:
	static constexpr SizeType s_kLocalStackSize = 64;

public:
	JsonSerializer_T(Json& j);

	template<class T> void named_fixed_io(const T& v, const char* name);
	template<class T> void fixed_io(const T& v);

	void fixed_io(const u8 & v);
	void fixed_io(const u16& v);
	void fixed_io(const u32& v);
	void fixed_io(const u64& v);

	void fixed_io(const i8 & v);
	void fixed_io(const i16& v);
	void fixed_io(const i32& v);
	void fixed_io(const i64& v);

	//void fixed_io(const f16& v);
	void fixed_io(const f32& v);
	void fixed_io(const f64& v);

	void fixed_io(bool v);

	void io_begin_object(const char* name = nullptr);
	void io_end_object  (const char* name = nullptr);

	void io_begin_array(SizeType size);
	void io_end_array  (SizeType size);
	template<class T> void fixed_io_array_element(const T& v, SizeType i);

	template<class T> void toValue(const T& v);
	template<class T> void toStr  (StrView_T<T> v);

private:
	Vector_T<Json*, s_kLocalStackSize> _stack;
};



#endif


#if 0
#pragma mark --- JsonSerializer_T-Impl ---
#endif // 0
#if 1

JsonSerializer_T::JsonSerializer_T(Json& j)
{
	_stack.reserve(s_kLocalStackSize);
	_stack.emplace_back(&j);
}

template<class T> inline 
void JsonSerializer_T::named_fixed_io(const T& v, const char* name)
{
	io_begin_object(name);
	fixed_io(v);
	io_end_object(name);
}

template<class T> inline
void JsonSerializer_T::fixed_io(const T& v)
{
	io_begin_object();
	JsonSerializer_Helper<T>::io(v, *this);
	io_end_object();
}

inline void JsonSerializer_T::fixed_io(const u8 & v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const u16& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const u32& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const u64& v) { toValue(v); }

inline void JsonSerializer_T::fixed_io(const i8 & v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const i16& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const i32& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const i64& v) { toValue(v); }

//inline void JsonSerializer_T::fixed_io(const f16& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const f32& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(const f64& v) { toValue(v); }

inline void JsonSerializer_T::fixed_io(bool v) { toValue(v); }

inline
void JsonSerializer_T::io_begin_object(const char* name)
{
	auto& cur	= *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");
	auto& next = name ? cur[name] : cur.emplace_back(cur.object());
	_stack.emplace_back(&next);
}

inline
void JsonSerializer_T::io_end_object(const char* name)
{
	//auto& cur = *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");
	//NMSP_ASSERT(name || (!name && cur.is_object()), "");
	_stack.pop_back();
}

inline
void JsonSerializer_T::io_begin_array(SizeType size)
{
	auto& cur	= *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");

	cur = cur.array();
	cur.get_ptr<Json_T::array_t*>()->resize(size);
	auto& next = cur;
	_stack.emplace_back(&next);
}

inline
void JsonSerializer_T::io_end_array(SizeType size)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_array() && cur.get<Json_T::array_t>().size() == size, "");
	_stack.pop_back();
}

template<class T> inline
void JsonSerializer_T::fixed_io_array_element(const T& v, SizeType i)
{
	auto& cur = *_stack.back();
	auto& arr = *cur.get_ptr<Json_T::array_t*>();
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_array(), "");

	auto& element = arr.at(i);
	_stack.emplace_back(&element);
	fixed_io(v);
	_stack.pop_back();
}

template<class T> inline
void JsonSerializer_T::toValue(const T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_null(), "");
	cur = v;
}

template<class T> inline
void JsonSerializer_T::toStr(StrView_T<T> v)
{
	NMSP_S_ASSERT(!IsSame<NMSP_ARGS(T, wchar_t)>, "");

	auto& cur = *_stack.back();
	//NMSP_ASSERT(cur.is_null(), "");
	cur = "";
	auto& dst = *cur.get_ptr<Json_T::string_t*>();
	dst.assign(v.begin(), v.end());
}

#endif

#if 0
#pragma mark --- JsonSerializer_Helper-Impl ---
#endif // 0
#if 1

template<class CHAR, size_t N, class ALLOC>
struct JsonSerializer_Helper<String_T<CHAR, N, ALLOC>>
{
	static void io(const String_T<CHAR, N, ALLOC>& v, JsonSerializer_T& se) 
	{
		se.toStr(v.view());
	}
};

template<class T, size_t N, class ALLOC>
struct JsonSerializer_Helper<Vector_T<T, N, ALLOC>>
{
	static void io(const Vector_T<T, N, ALLOC>& v, JsonSerializer_T& se) 
	{
		se.io_begin_array(v.size());
		for (size_t i = 0; i < v.size(); i++)
		{
			se.fixed_io_array_element(v[i], i);
		}
		se.io_end_array(v.size());
	}
};

#endif


}
