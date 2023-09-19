#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmspJsonSerializer.h"
#include "nmspJsonDeserializer.h"

/*
references:
- src/core/serializer/json/JsonUtil.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

//#define NMSP_NAMED_FIXED_IO(SE, OBJ, MEMBER) SE.named_fixed_io(OBJ.MEMBER, #MEMBER)
#define NMSP_NAMED_FIXED_IO(SE, MEMBER) SE.named_fixed_io(this->MEMBER, #MEMBER)

namespace nmsp {

#if 0
#pragma mark --- JsonDeserializer_T-Decl ---
#endif // 0
#if 1

struct JsonUtil
{
public:
	using Json = Json_T;

public:
	JsonUtil() = delete;

public:
	template<class T> static void readFile (StrViewA_T filename, T& outData);
	template<class T> static char writeFile(StrViewA_T filename, T& data, bool createDir, bool logResult = true);
	template<class T> static char writeFileIfChanged(StrViewA_T filename, T& data, bool createDir, bool logResult = true, bool logNoChange = false);

	template<class T>			static StringT	serialize	(T& data);
	template<class T>			static void		deserialize	(StrViewA_T json, T& data);
	template<class T, size_t N> static void		serializeTo	(StringA_T<N>& o, T& data);
};

#endif

template<class T> inline 
void JsonUtil::readFile(StrViewA_T filename, T& outData)
{
	MemMapFile_T mmf;
	mmf.open(filename);
	deserialize(mmf.strview(), outData);
}

template<class T> inline 
char JsonUtil::writeFile(StrViewA_T filename, T& data, bool createDir, bool logResult)
{
	TempStringA_T<> tmp;
	serializeTo(tmp, data);
	return File::writeFile(filename, tmp.view(), createDir, logResult);
}

template<class T> inline 
char JsonUtil::writeFileIfChanged(StrViewA_T filename, T& data, bool createDir, bool logResult, bool logNoChange)
{
	TempStringA_T<> tmp;
	serializeTo(tmp, data);
	return File::writeFileIfChanged(filename, tmp.view(), createDir, logResult, logNoChange);
}

template<class T>
inline StringT JsonUtil::serialize(T& data)
{
	StringT o;
	serializeTo(o, data);
	return o;
}

template<class T>
inline void JsonUtil::deserialize(StrViewA_T json, T& data)
{
	Json j = Json::parse(json.begin(), json.end());
	JsonDeserializer_T se{j};
	se.fixed_io(data);
}

template<class T, size_t N> inline 
void JsonUtil::serializeTo(StringA_T<N>& o, T& data)
{
	Json js;
	JsonSerializer_T se{js};
	se.fixed_io(data);
	auto str = js.dump(1, '\t');
	o = str.c_str();
}


}