#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmspJsonSerializer.h"

/*
references:
- src/core/serializer/json/JsonDeserializer.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- JsonDeserializer_T-Decl ---
#endif // 0
#if 1

class JsonDeserializer_T
{
public:
	using Json = Json_T;

	using SizeType = FileIoTraits::SizeType;

	template<class SE, class T, class ENABLE> friend struct JsonSE_Helper;

public:
	static constexpr SizeType s_kLocalStackSize = 64;

public:
	JsonDeserializer_T(Json& j);

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

	void fixed_io(bool v);

	void io_beginObject();
	void io_endObject  ();

	SizeType	io_beginArray	();
	void		io_endArray	();
	template<class T> void io_resizeArray	(T& v, SizeType n);

	template<class T> void toValue			(T& v);
	template<class T> void toObjectMember	(T& v, const char* name);
	template<class T> void toStr			(T& v);
	template<class T> void toEnum			(T& v);
	template<class T> void toArrayElement	(T& v, SizeType i);

private:
	Vector_T<Json*, s_kLocalStackSize> _stack;
};

#endif


#if 0
#pragma mark --- JsonDeserializer_T-Impl ---
#endif // 0
#if 1

inline
JsonDeserializer_T::JsonDeserializer_T(Json& j)
{
	_stack.emplace_back(&j);
}

template<class T> inline 
void JsonDeserializer_T::named_fixed_io(T& v, const char* name)
{
	toObjectMember(v, name);
}

template<class T> inline 
void JsonDeserializer_T::fixed_io(T& v)
{
	JsonSE_Helper<JsonDeserializer_T, T>::io(*this, v);
}

inline void JsonDeserializer_T::fixed_io(u8 & v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(u16& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(u32& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(u64& v) { toValue(v); }

inline void JsonDeserializer_T::fixed_io(i8 & v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(i16& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(i32& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(i64& v) { toValue(v); }

//inline void JsonDeserializer_T::fixed_io(f16& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(f32& v) { toValue(v); }
inline void JsonDeserializer_T::fixed_io(f64& v) { toValue(v); }

inline void JsonDeserializer_T::fixed_io(bool v) { toValue(v); }

template<class T> inline 
void JsonDeserializer_T::toValue		(T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(!cur.is_null(), "");
	v = cur;
}

template<class T> inline 
void JsonDeserializer_T::toObjectMember	(T& v, const char* name)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_object(), "");
	auto it = cur.find(name);
	NMSP_ASSERT(it != cur.end(), "not found");

	_stack.emplace_back(&(*it));
	fixed_io(v);
	_stack.pop_back();
}

template<class T> inline 
void JsonDeserializer_T::toStr			(T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_string(), "");
	auto& value = *cur.get_ptr<Json::string_t*>();
	
	v.reserve(value.size());
	v = value.c_str();
}

template<class T> inline 
void JsonDeserializer_T::toEnum			(T& v)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_string(), "");
	auto& value = *cur.get_ptr<Json::string_t*>();

	auto ret = enumTryParse(v, value.c_str()); NMSP_UNUSED(ret);
	NMSP_ASSERT(ret, "");
}

template<class T> inline 
void JsonDeserializer_T::toArrayElement	(T& v, SizeType i)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_array(), "");
	auto& value = *cur.get_ptr<Json::array_t*>();
	auto& element = value.at(i);
	
	_stack.emplace_back(&element);
	fixed_io(v);
	_stack.pop_back();
}

inline 
void JsonDeserializer_T::io_beginObject()
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_object(), "");
}

inline 
void JsonDeserializer_T::io_endObject ()
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_object(), "");
}

inline 
JsonDeserializer_T::SizeType JsonDeserializer_T::io_beginArray()
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_array(), "");
	auto& value = *cur.get_ptr<Json::array_t*>();
	return value.size();
}

inline 
void JsonDeserializer_T::io_endArray()
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_array(), "");
}

template<class T> inline 
void JsonDeserializer_T::io_resizeArray(T& v, SizeType n)
{
	auto& cur = *_stack.back();
	NMSP_ASSERT(cur.is_array(), "");
	v.clear();
	v.resize(n);
}

#endif

#if 0
#pragma mark --- JsonSE_Helper-Impl ---
#endif // 0
#if 1

template<class T>
struct JsonSE_Helper<JsonDeserializer_T, T, EnableIf<IsEnum<T> > >
{
	static void io(JsonDeserializer_T& se, T& v) 
	{
		se.toEnum(v);
	}
};

template<class CHAR, size_t N, class ALLOC>
struct JsonSE_Helper<JsonDeserializer_T, String_T<CHAR, N, ALLOC> >
{
	static void io(JsonDeserializer_T& se, String_T<CHAR, N, ALLOC>& v) 
	{
		se.toStr(v);
	}
};

template<class T, size_t N, class ALLOC>
struct JsonSE_Helper<JsonDeserializer_T, Vector_T<T, N, ALLOC> >
{
	static void io(JsonDeserializer_T& se, Vector_T<T, N, ALLOC>& v) 
	{
		auto n = se.io_beginArray();
		se.io_resizeArray(v, n);
		for (size_t i = 0; i < n; i++)
		{
			se.toArrayElement(v[i], i);
		}
		se.io_endArray();
	}
};

#endif

}