#include "nmsp_stl-pch.h"
#include "nmspLexer.h"

namespace nmsp {

#if 0
#pragma mark --- Lexer_T-Impl ---
#endif // 0
#if 1

void 
Lexer_T::reset(ByteSpan_T srcData, StrViewA_T filename)
{
	reset(makeStrView(srcData), filename);
}

void 
Lexer_T::reset(StrViewA_T srcData, StrViewA_T filename)
{
	clear();
	_filename		= filename;
	_srcData		= srcData;
	_srcDataCurLine	= _srcData;

	nextChar();
	nextToken();
}

void 
Lexer_T::clear()
{
	_srcData = StrViewA_T{};
	_srcDataCurLine = StrViewA_T{};
	
	_line	= 1;
	_col	= 0;
	_ch		= 0;
}

bool 
Lexer_T::nextToken()
{
	return parse();
}

void 
Lexer_T::errorUnexpectedToken()
{
	error("Unexpected Token: {}", token().value());
}

void
Lexer_T::_error(StrViewA_T msg)
{
	TempStringA_T<> tmp = msg;
	fmtTo(tmp, "\n{}\n", getLastNLines(3));

	{
		TempStringA_T<> lastLine = getLastNLines(1);
		size_t i = 0;
		for (auto& c : lastLine) 
		{
			if (i >= _col) break;
			if (c == ' ' ) { tmp += '-';	continue; }
			if (c == '\n') { tmp += c;		continue; }
			if (c == '\t') { tmp += "----";	continue; }
			tmp += '-';
			i++;
		}
		tmp += "^^^\n";
	}

	fmtTo(tmp, "  token={}\n  file={}:{}:{}\n", _token, _filename, _line, _col);
	throw NMSP_ERROR("{}", tmp);
}

void Lexer_T::nextChar()
{
	_nextChar();
	if (isNewline(_ch))
	{
		_nextLine();
	}
}

void 
Lexer_T::_nextLine()
{
	_srcDataCurLine = StrViewA_T{ _srcDataCurLine.begin() + _col, _srcDataCurLine.end() };
	_line++;
	_col = 0;
}

void 
Lexer_T::_nextChar()
{
	_ch = 0;
	if (_srcDataCurLine.data() + _col >= _srcDataCurLine.end())
		return;

	_ch = _srcDataCurLine[_col];
	_col++;
}

void 
Lexer_T::ignoreSpace()
{
	while(StrUtil::hasChar(" \t\f\r", _ch))
	{
		nextChar();
	}
}

bool 
Lexer_T::skipNewline()
{
	bool ret = true;
	while (ret && _token.isNewline())
	{
		ret = nextToken();
	}
	return ret;
}

bool
Lexer_T::parse()
{
	char ch		= 0;
	bool ret = false;

	for (;;)
	{
		ignoreSpace();
		ch		= _ch;

		if (ch == 0)
			break;

		if (isIdentifier(ch))
		{
			ret = _parseIdentifier();
			break;
		}
		else if (isDigit(ch))
		{
			ret = _parseNumber();
			break;
		}
		else if (isString(ch))
		{
			ret = _parseString();
			break;
		}

		if (isNewline(ch))
		{
			ret = _parseNewline();
			break;
		}

		if (isComment(ch))
		{
			ret = _parseComment();
			continue;
		}

		resetToken(TokenType::Operator);
		addCharToToken(ch);
		ret = true;
		break;
	}
	return ret;
}

bool 
Lexer_T::_parseIdentifier()
{
	resetToken(TokenType::Identifier);

	auto isIdentifierOrDigit = [](char ch) { return Lexer_T::isIdentifier(ch) || Lexer_T::isDigit(ch); };
	keepAddCharToTokenIf(isIdentifierOrDigit);

	return true;
}

bool 
Lexer_T::_parseNumber()
{
	resetToken(TokenType::Number);
	keepAddCharToTokenIf(Lexer_T::isDigit);

	if (_ch == '.')
	{
		addCharToToken(_ch);
		keepAddCharToTokenIf(Lexer_T::isDigit);
	}

	return true;
}

bool 
Lexer_T::_parseString()
{
	resetToken(TokenType::String);
	nextChar();

	char ch = 0;
	for (;;)
	{
		ch = _ch;
		if (isString(ch))
		{
			nextChar();
			break;
		}

		if (ch == 0)
			break;

		if (ch == '\\')
		{
			nextChar();
			switch (_ch)
			{
				case '\\':
				case '/':
				case '"':
				case '\'':
					{ addCharToToken(_ch); } break;

				case 'a': { addCharToToken('\a'); } break;
				case 'b': { addCharToToken('\b'); } break;
				case 'f': { addCharToToken('\f'); } break;
				case 'n': { addCharToToken('\n'); } break;
				case 'r': { addCharToToken('\r'); } break;
				case 't': { addCharToToken('\t'); } break;
				case 'v': { addCharToToken('\v'); } break;

				default:  { error("Invalid String escape sequences."); }break;
			}
		}
		else
		{
			addCharToToken(ch);
		}
	}

	return true;
}

bool 
Lexer_T::_parseOperator()
{
	resetToken(TokenType::Operator);
	addCharToToken(_ch);
	
	for (;;)
	{
		char ch = _ch;
		if (ch == '0')
			break;

		addCharToToken(_ch);
	}

	return true;
}

bool 
Lexer_T::_parseNewline()
{
	resetToken(TokenType::Newline);
	_token.setValue("<Newline>");
	nextChar();
	return true;
}

bool 
Lexer_T::_parseComment()
{
	auto isNotNewline	= [](char ch) { return !isNewline(ch); };
	auto isNotAsterisk	= [](char ch) { return ch != '*'; };

	nextChar();
	if (_ch == '/')
	{
		keepSkipCharIf(isNotNewline);
	}
	else if (_ch == '*')	// comment block
	{
		nextChar();
		keepSkipCharIf(isNotAsterisk);
		nextChar();
		if (_ch == '/')
		{
			nextChar();
			return true;
		}
		return false;
	}

	return true;
}

void 
Lexer_T::addCharToToken(char ch)
{
	_token._value += ch;
	nextChar();
}

void 
Lexer_T::addToToken(StrViewA_T v)
{
	_token._value += v;
	nextChar();
}

StrViewA_T		
Lexer_T::getLastNLines(SizeType n) const
{
	if (_ch == '\0' || _srcData.is_empty())
		return StrViewA_T{};

	auto beg	= _srcData.begin();
	auto p		= cur();

	for (;p > beg && n > 0; --p)
	{
		if (isNewline(*p))
		{
			--n;
		}
	}
	++p;
	return StrViewA_T{p, sCast<SizeType>(cur() - p + 1)};
}

#endif




#if 0
#pragma mark --- Lexer_Token_T-Impl ---
#endif // 0
#if 1

#endif

}