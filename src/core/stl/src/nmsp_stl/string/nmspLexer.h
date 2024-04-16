#pragma once

#include "../common/nmsp_stl_common.h"
#include "nmspStrUtil.h"

/*
references:
- src/core/string/Lexer.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- Lexer_Token_T-Decl ---
#endif // 0
#if 1

class Lexer_T;

#define Lexer_TokenType_T_ENUM_LIST(E) \
	E(None, = 0) \
	E(Identifier,) \
	E(Number,) \
	E(String,) \
	E(Operator,) \
	E(Newline,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(Lexer_TokenType_T, u8);

class Lexer_Token_T
{
public:
	friend class Lexer_T;
public:
	using Type = Lexer_TokenType_T;

	bool isNone			() const;

	bool isIdentifier	() const;
	bool isNumber		() const;
	bool isString		() const;
	bool isOperator		() const;
	bool isNewline		() const;

	bool isIdentifier	(StrViewA_T v) const;
	bool isNumber		(StrViewA_T v) const;
	bool isString		(StrViewA_T v) const;
	bool isOperator		(StrViewA_T v) const;

			Type	type()	const;
	const StringT&	value() const;

protected:
	void setValue(StrViewA_T v);
	void reset(Type type = Type::None);

private:
	Type _type;
	StringT _value;
};

#endif

#if 0
#pragma mark --- Lexer_T-Decl ---
#endif // 0
#if 1

// template<ALLOC = DefaultAllocator>
class Lexer_T : public NonCopyable
{
public:
	using Token		= Lexer_Token_T;
	using TokenType = Lexer_TokenType_T;
	using SizeType	= size_t;

public:
	static constexpr SizeType s_kTabToSpaceCount = 4;

public:
	~Lexer_T() = default;

	void reset(ByteSpan_T srcData, StrViewA_T filename);
	void reset(StrViewA_T srcData, StrViewA_T filename);
	void clear();

	bool nextToken();
	bool skipNewline();

	template<class STR> void readIdentifier	(STR& o);
	template<class STR> void readNumber		(STR& o);
	template<class STR> void readString		(STR& o);
	template<class STR> void readOperator	(STR& o);
	template<class T>	void readEnum		(T& o);
						void readBool		(bool& o);

	void expected(TokenType type, const char* cstr);

	const Token&	token	() const;

	SizeType		pos		() const;
	SizeType		line	() const;
	SizeType		col		() const;
	const char*		cur		() const;
	StrViewA_T		remain	() const;
	StrViewA_T		filename() const;
	StrViewA_T		getLastNLines(SizeType n) const;

	char			curChar()  const;

protected:
	template<class... ARGS> void errorIf(bool cond, const char* fmt = "", ARGS&&... args);
	template<class... ARGS> void error (const char* fmt = "", ARGS&&... args);
							void errorUnexpectedToken();
							void _error(StrViewA_T msg);

protected:
	void nextChar();

private:
	void _nextLine();
	void _nextChar();

	void _expected(TokenType type);

	void ignoreSpace();

	bool parse();
	bool _parseIdentifier();
	bool _parseNumber();
	bool _parseString();
	bool _parseOperator();
	bool _parseNewline();
	bool _parseComment();

	void resetToken(TokenType type = TokenType::None);

	void addCharToToken(char ch);
	void addToToken(StrViewA_T v);
	template<class FUNC> void keepAddCharToTokenIf(FUNC&& func);
	template<class FUNC> void keepSkipCharIf(FUNC&& func);

	static bool isIdentifier(char ch);
	static bool isDigit(char ch);
	static bool isString(char ch);
	static bool isOperator(char ch);
	static bool isNewline(char ch);
	static bool isComment(char ch);
	static bool isAlpha(char ch);
	static bool isLowerCase(char ch);
	static bool isUpperCase(char ch);
	static bool isSign(char ch);

	template<size_t N, class ALLOC = DefaultAllocator>
	void getSpacesTo(StringA_T<N, ALLOC>& o, SizeType n = s_kTabToSpaceCount) const;

private:
	Token _token;

	StringT		_filename;
	StrViewA_T	_srcData;
	StrViewA_T	_srcDataCurLine;

	SizeType _line = 0;
	SizeType _col = 0;
	char	 _ch = 0;
};

#endif // 0

#if 0
#pragma mark --- Lexer_T-Impl ---
#endif // 0
#if 1

template<class... ARGS> inline 
void 
Lexer_T::errorIf(bool cond, const char* fmt, ARGS&&... args)
{
	if (cond)
	{
		error(fmt, nmsp::forward<ARGS>(args)...);
	}
}

template<class... ARGS> inline 
void 
Lexer_T::error (const char* fmt, ARGS&&... args)
{
	TempStringA_T<> tmp;
	fmtTo(tmp, fmt, nmsp::forward<ARGS>(args)...);
	_error(tmp);
}

inline void 
Lexer_T::resetToken(TokenType type)
{
	_token.reset(type);
}

template<class FUNC> 
inline void 
Lexer_T::keepAddCharToTokenIf(FUNC&& func)
{
	while (invoke(func, _ch))
	{
		addCharToToken(_ch);
	}
}

template<class FUNC> 
inline void 
Lexer_T::keepSkipCharIf(FUNC&& func)
{
	while (func(_ch))
	{
		nextChar();
	}
}

inline void 
Lexer_T::_expected(TokenType type)
{
	errorIf(token().type() != type, "expected Type: {}, current: {}", type, token().type());
}

inline 
void 
Lexer_T::expected(TokenType type, const char* cstr)
{
	errorIf(token().type() != type && StrUtil::isSame(token().value().c_str(), cstr), "expected Type: {}, current: {}", type, token().type());
	nextToken();
}

inline const Lexer_T::Token& 
Lexer_T::token() const
{
	return _token;
}

inline Lexer_T::SizeType 
Lexer_T::pos() const
{
	if (_srcData.is_empty())
		return _srcData.size();
	auto n = _srcDataCurLine.begin() - _srcData.begin();
	NMSP_ASSERT(n + _col <= _srcData.size());
	return n + _col;
}

inline Lexer_T::SizeType 
Lexer_T::line() const
{
	return _line;
}

inline Lexer_T::SizeType 
Lexer_T::col() const
{
	return _col;
}

inline const char* Lexer_T::cur() const
{
	NMSP_ASSERT(remain().begin() - 1 >= _srcData.begin());
	return remain().begin() - 1;
}

inline StrViewA_T Lexer_T::remain() const
{
	auto n = _col;
	NMSP_ASSERT(_srcDataCurLine.begin() + n <= _srcData.end());
	return StrViewA_T(_srcDataCurLine.begin() + n, _srcDataCurLine.size() - n);
}

inline StrViewA_T Lexer_T::filename() const
{
	return _filename;
}

inline char Lexer_T::curChar()  const { return _ch; }

template<class STR> inline 
void 
Lexer_T::readIdentifier	(STR& o)
{
	_expected(TokenType::Identifier);
	o = token().value();
	nextToken();
}

template<class STR> inline 
void 
Lexer_T::readNumber		(STR& o)
{
	_expected(TokenType::Number);
	o = token().value();
	nextToken();
}

template<class STR> inline 
void 
Lexer_T::readString		(STR& o)
{
	_expected(TokenType::String);
	o = token().value();
	nextToken();
}

template<class STR> inline 
void 
Lexer_T::readOperator	(STR& o)
{
	_expected(TokenType::Operator);
	o = token().value();
	nextToken();
}

template<class T> inline 
void 
Lexer_T::readEnum		(T& o)
{
	_expected(TokenType::Identifier);
	errorIf(!enumTryParse(o, token().value()), "Error: readEnum()");
	nextToken();
}

inline void 
Lexer_T::readBool		(bool& o)
{
	_expected(TokenType::Identifier);
	if (token().value() == "true")
	{
		o = true;
	}
	else if (token().value() == "false")
	{
		o = false;
	}
	else
		error();

	nextToken();
}

template<size_t N, class ALLOC> inline
void Lexer_T::getSpacesTo(StringA_T<N, ALLOC>& o, SizeType n) const
{
	o.clear();
	for (size_t i = 0; i < n; i++)
	{
		o += " ";
	}
}

inline bool 
Lexer_T::isIdentifier(char ch)
{
	return isAlpha(ch) || ch == '_';
}

inline bool 
Lexer_T::isDigit(char ch)
{
	if (ch >= '0' && ch <= '9') return true;
	return false;
}

inline bool 
Lexer_T::isString(char ch)
{
	if (ch == '\"' /*|| ch == '\''*/) return true;
	return false;
}

inline bool 
Lexer_T::isOperator(char ch)
{
	if (StrUtil::hasChar("=~!@#$%^&*()[]{}|;:<>,.?/+-", ch)) return true;
	return false;
}

inline bool 
Lexer_T::isSign(char ch)
{
	if (ch == '+' || ch == '-') return true;
	return false;
}

inline bool 
Lexer_T::isNewline(char ch)
{
	return StrUtil::hasChar("\n", ch);
}

inline bool 
Lexer_T::isComment(char ch)
{
	return StrUtil::hasChar("/", ch);
}

inline bool Lexer_T::isAlpha(char ch)		{ return isLowerCase(ch) || isUpperCase(ch); }
inline bool Lexer_T::isLowerCase(char ch)	{ return ch >= 'a' && ch <= 'z'; }
inline bool Lexer_T::isUpperCase(char ch)	{ return ch >= 'A' && ch <= 'Z'; }

#endif


#if 0
#pragma mark --- Lexer_Token_T-Impl ---
#endif // 0
#if 1


inline void 
Lexer_Token_T::setValue(StrViewA_T v)
{
	_value = v;
}

inline void 
Lexer_Token_T::reset(Type type)
{
	_type = type;
	_value.clear();
}

inline Lexer_Token_T::Type	Lexer_Token_T::type()	const { return _type; }
inline const StringT&		Lexer_Token_T::value()	const { return _value; }

inline bool Lexer_Token_T::isNone		() const { return _type == Type::None; }
inline bool Lexer_Token_T::isIdentifier	() const { return _type == Type::Identifier; }
inline bool Lexer_Token_T::isNumber		() const { return _type == Type::Number; }
inline bool Lexer_Token_T::isString		() const { return _type == Type::String; }
inline bool Lexer_Token_T::isOperator	() const { return _type == Type::Operator; }
inline bool Lexer_Token_T::isNewline	() const { return _type == Type::Newline; }

inline bool Lexer_Token_T::isIdentifier	(StrViewA_T v) const { return _type == Type::Identifier	&& _value == v; }
inline bool Lexer_Token_T::isNumber		(StrViewA_T v) const { return _type == Type::Number		&& _value == v; }
inline bool Lexer_Token_T::isString		(StrViewA_T v) const { return _type == Type::String		&& _value == v; }
inline bool Lexer_Token_T::isOperator	(StrViewA_T v) const { return _type == Type::Operator	&& _value == v; }


#endif

}

namespace nmsp {

inline void 
onFormat(fmt::format_context& ctx, const Lexer_Token_T& v)
{
	nmsp::formatTo(ctx, "--- {}: {}", v.type(), v.value());
}

}
NMSP_FORMATTER(Lexer_Token_T);