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

// not used, fmt like design, but cannot use as typedef
template<class T>
struct JsonIo
{
	template<class SE>
	static void onJson(SE& se, T& v);
};

template<class SE, class T, class ENABLE = void>
struct JsonSE_Helper
{
	static void io(SE& se, T& v) 
	{
		se.io_beginObject();
		v.onJsonIo(se);
		se.io_endObject();
	}
};

class JsonSerializer_T
{
public:
	using Json = Json_T;

	using SizeType = FileIoTraits::SizeType;

	template<class SE, class T, class ENABLE> friend struct JsonSE_Helper;

public:
	static constexpr SizeType s_kLocalStackSize = 64;

public:
	JsonSerializer_T(Json& j);

	template<class T> void named_fixed_io(T& v, const char* name);
	template<class T> void fixed_io(T& v);

protected:
	void fixed_io(u8 & v);
	void fixed_io(u16& v);
	void fixed_io(u32& v);
	void fixed_io(u64& v);

	void fixed_io(i8 & v);
	void fixed_io(i16& v);
	void fixed_io(i32& v);
	void fixed_io(i64& v);

	//void fixed_io(f16& v);
	void fixed_io(f32& v);
	void fixed_io(f64& v);

	void fixed_io(bool& v);

	void io_beginObject();
	void io_endObject  ();

	void io_beginArray	();
	void io_endArray	();
	void io_resizeArray	(SizeType n);

	template<class T> void toValue			(const T& v);
	template<class T> void toObjectMember	(T& v, const char* name);
	template<class T> void toStr			(StrView_T<T> v);
	template<class T> void toEnum			(const T& v);
	template<class T> void toArrayElement	(T& v, SizeType i);

private:
	Vector_T<Json*, s_kLocalStackSize> _stack;
};

#endif


#if 0
#pragma mark --- JsonSerializer_T-Impl ---
#endif // 0
#if 1

inline
JsonSerializer_T::JsonSerializer_T(Json& j)
{
	_stack.reserve(s_kLocalStackSize);
	_stack.emplace_back(&j);
}

template<class T> inline 
void JsonSerializer_T::named_fixed_io(T& v, const char* name)
{
	toObjectMember(v, name);
}

template<class T> inline
void JsonSerializer_T::fixed_io(T& v)
{
	JsonSE_Helper<JsonSerializer_T, T>::io(*this, v);
}

inline void JsonSerializer_T::fixed_io(u8 & v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(u16& v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(u32& v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(u64& v)	{ toValue(v); }

inline void JsonSerializer_T::fixed_io(i8 & v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(i16& v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(i32& v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(i64& v)	{ toValue(v); }

//inline void JsonSerializer_T::fixed_io(f16& v) { toValue(v); }
inline void JsonSerializer_T::fixed_io(f32& v)	{ toValue(v); }
inline void JsonSerializer_T::fixed_io(f64& v)	{ toValue(v); }

inline void JsonSerializer_T::fixed_io(bool& v) { toValue(v); }

inline
void JsonSerializer_T::io_beginObject()
{
	auto& cur	= *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_null(), "");
	cur = Json_T::object();
}

inline
void JsonSerializer_T::io_endObject()
{
	auto& cur = *_stack.back(); NMSP_UNUSED(cur);
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_object(), "");
}

inline
void JsonSerializer_T::io_beginArray()
{
	auto& cur	= *_stack.back();
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_null(), "");
	cur = Json_T::array();
}

inline
void JsonSerializer_T::io_endArray()
{
	auto& cur	= *_stack.back(); NMSP_UNUSED(cur);
	NMSP_ASSERT(!_stack.is_empty(), "");
	NMSP_ASSERT(cur.is_array(), "");
}

inline
void JsonSerializer_T::io_resizeArray(SizeType n)
{
	auto& cur = *_stack.back(); NMSP_UNUSED(cur);
	NMSP_ASSERT(cur.is_array(), "");
	auto& arr = *cur.get_ptr<Json_T::array_t*>();
	arr.resize(n);
}

template<class T> inline
void JsonSerializer_T::toValue(const T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_null(), "");
	cur = v;
}
template<class T> inline 
void JsonSerializer_T::toObjectMember(T& v, const char* name)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_object(), "");

	auto& value = cur[name];
	_stack.emplace_back(&value);
	fixed_io(v);
	_stack.pop_back();
}

template<class T> inline
void JsonSerializer_T::toStr(StrView_T<T> v)
{
	NMSP_S_ASSERT(!IsSame<NMSP_ARGS(T, wchar_t)>, "");
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_null(), "");

	cur = "";
	auto& dst = *cur.get_ptr<Json_T::string_t*>();
	dst.assign(v.begin(), v.end());
}

template<class T> inline
void JsonSerializer_T::toEnum(const T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_null(), "");

	toValue(enumStr(v));
}

template<class T> inline
void JsonSerializer_T::toArrayElement(T& v, SizeType i)
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

#endif

#if 0
#pragma mark --- JsonSE_Helper-Impl ---
#endif // 0
#if 1

template<class T>
struct JsonSE_Helper<JsonSerializer_T, T, EnableIf<IsEnum<T> > >
{
	static void io(JsonSerializer_T& se, T& v) 
	{
		se.toEnum(v);
	}
};

template<class CHAR, size_t N, class ALLOC>
struct JsonSE_Helper<JsonSerializer_T, String_T<CHAR, N, ALLOC> >
{
	static void io(JsonSerializer_T& se, String_T<CHAR, N, ALLOC>& v) 
	{
		se.toStr(v.view());
	}
};

template<class T, size_t N, class ALLOC>
struct JsonSE_Helper<JsonSerializer_T, Vector_T<T, N, ALLOC> >
{
	static void io(JsonSerializer_T& se, Vector_T<T, N, ALLOC>& v) 
	{
		se.io_beginArray();
		auto n = v.size();
		se.io_resizeArray(n);
		for (size_t i = 0; i < n; i++)
		{
			se.toArrayElement(v[i], i);
		}
		se.io_endArray();
	}
};

#endif


}
