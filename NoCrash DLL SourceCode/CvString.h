#pragma once

#ifndef CvString_h
#define CvString_h

#include <string>
#pragma warning( disable: 4251 )		// needs to have dll-interface to be used by clients of class

// CV4_NOINLINE: variadic functions MUST NOT be inlined; inlining destroys
// va_start's anchor to the real parameter list and produces wild va_lists.
//
// Order matters: prefer __declspec(noinline) when _MSC_VER is defined
// (true for cl.exe AND for clang --target *-pc-windows-msvc).
// Why not __attribute__((noinline)) first under __clang__?  MinGW's _mingw.h
// does `#define __attribute__(x)` when __GNUC__ is undefined (our case),
// silently erasing the attribute.  __declspec is not touched by MinGW
// headers, so it survives unconditionally.
#if defined(_MSC_VER)
#  define CV4_NOINLINE __declspec(noinline)
#elif defined(__clang__) || defined(__GNUC__)
#  define CV4_NOINLINE __attribute__((noinline))
#else
#  define CV4_NOINLINE
#endif

//
// simple string classes, based on stl, but with a few helpers
//
// DON'T add any data members or virtual functions to these classes, so they stay the same size as their stl counterparts
//
// Mustafa Thamer
// Firaxis Games, copyright 2005
//

// wide string
class CvWString : public std::wstring
{
public:
	CvWString() {}
	CvWString(const std::string& s) { Copy(s.c_str()); 	}
	CvWString(const CvWString& s) { *this = s; 	}
	CvWString(const char* s) { Copy(s); 	}
	CvWString(const wchar* s) { if (s) *this = s; }
//	CvWString(const __wchar_t* s) { if (s) *this = s; }
	CvWString(const std::wstring& s) { assign(s.c_str()); }
#ifndef _USRDLL
	// FString conversion, if not in the DLL
	CvWString(const FStringA& s) { Copy(s.GetCString()); }
	CvWString(const FStringW& s) { assign(s.GetCString()); }
#endif
	~CvWString() {}

	void Copy(const char* s)
	{
		if (s)
		{
			int iLen = strlen(s);
			if (iLen)
			{
				wchar *w = new wchar[iLen+1];
				swprintf(w, L"%S", s);	// convert
				assign(w);
				delete [] w;
			}
		}
	}

	// FString compatibility
	const wchar* GetCString() const 	{ return c_str(); }

	// implicit conversion
	operator const wchar*() const 	{ return c_str(); }

	// operators
	wchar& operator[](int i) { return std::wstring::operator[](i);	}
	wchar& operator[](std::wstring::size_type i) { return std::wstring::operator[](i);	}
	const wchar operator[](int i) const { return std::wstring::operator[](i);	}
	const CvWString& operator=( const wchar* s) { if (s) assign(s); else clear();	return *this; }
	const CvWString& operator=( const std::wstring& s) { assign(s.c_str());	return *this; }
	const CvWString& operator=( const std::string& w) { Copy(w.c_str());	return *this; }
	const CvWString& operator=( const CvWString& w) { assign(w.c_str());	return *this; }
#ifndef _USRDLL
	// FString conversion, if not in the DLL
	const CvWString& operator=( const FStringW& s) { assign(s.GetCString());	return *this; }
	const CvWString& operator=( const FStringA& w) { Copy(w.GetCString());	return *this; }
#endif
	const CvWString& operator=( const char* w) { Copy(w);	return *this; }

	void Format( LPCWSTR lpszFormat, ... );

	// static helpers
	static bool formatv(std::wstring& out, const wchar * fmt, va_list args);
	static bool format(std::wstring & out, const wchar * fmt, ...);
	static CvWString format(const wchar * fmt, ...);
	static std::wstring formatv(const wchar * fmt, va_list args);
};


//#define WIDEPTR(s) (s ? CvWString(s).c_str() : NULL)

inline CvWString operator+( const CvWString& s, const CvWString& t) { return (std::wstring&)s + (std::wstring&)t; }
inline CvWString operator+( const CvWString& s, const wchar* t) { return (std::wstring&)s + std::wstring(t); }
inline CvWString operator+( const wchar* s, const CvWString& t) { return std::wstring(s) + std::wstring(t); }
//CvString operator+( const CvString& s, const CvString& t) { return (std::string&)s + (std::string&)t; }

class CvWStringBuffer
{
public:
	CvWStringBuffer()
	{
		m_pBuffer = NULL;
		m_iLength = 0;
		m_iCapacity = 0;
	}

	~CvWStringBuffer()
	{
		SAFE_DELETE_ARRAY(m_pBuffer);
	}

	void append(wchar character)
	{
		int newLength = m_iLength + 1;
		ensureCapacity(newLength + 1);
		m_pBuffer[m_iLength] = character;
		m_pBuffer[m_iLength + 1] = 0; //null character
		m_iLength = newLength;
	}

	void append(const wchar *szCharacters)
	{
		if(szCharacters == NULL)
			return;

		int inputLength = wcslen(szCharacters);
		int newLength = m_iLength + inputLength;
		ensureCapacity(newLength + 1);

		//append data
		memcpy(m_pBuffer + m_iLength, szCharacters, sizeof(wchar) * (inputLength + 1)); //null character
		m_iLength = newLength;
	}

	void append(const CvWString &szString)
	{
		append(szString.GetCString());
	}

	void append(const CvWStringBuffer &szStringBuffer)
	{
		append(szStringBuffer.m_pBuffer);
	}

	void assign(const CvWString &szString)
	{
		assign(szString.GetCString());
	}

	void assign(const wchar *szCharacters)
	{
		clear();
		append(szCharacters);
	}

	void clear()
	{
		if(m_pBuffer != NULL)
		{
			m_iLength = 0;
			m_pBuffer[0] = 0; //null character
		}
	}

	bool isEmpty() const
	{
		if(m_iLength == 0)
			return true;
		else
			return false;
	}

	const wchar *getCString()
	{
		ensureCapacity(1);
		return m_pBuffer;
	}

private:
	void ensureCapacity(int newCapacity)
	{
		if(newCapacity > m_iCapacity)
		{
			m_iCapacity = 2 * newCapacity; //grow by %100
			wchar *newBuffer = new wchar [m_iCapacity];

			//copy data
			if(m_pBuffer != NULL)
			{
				memcpy(newBuffer, m_pBuffer, sizeof(wchar) * (m_iLength + 1)); //null character
				//erase old memory
				SAFE_DELETE_ARRAY(m_pBuffer);
			}
			else
			{
				newBuffer[0] = 0; //null character
			}

			m_pBuffer = newBuffer;
		}
	}

	wchar *m_pBuffer;
	int m_iLength;
	int m_iCapacity;
};

//
class CvString : public std::string
{
public:
	CvString() {}
	CvString(int iLen) { reserve(iLen); }
	CvString(const char* s) { operator=(s); }
	CvString(const std::string& s) { assign(s.c_str()); }
	explicit CvString(const std::wstring& s) { Copy(s.c_str()); }		// don't want accidental conversions down to narrow strings
	~CvString() {}

	void Convert(const std::wstring& w) { Copy(w.c_str());	}
	void Copy(const wchar* w)
	{
		if (w)
		{
			int iLen = wcslen(w);
			if (iLen)
			{
				char *s = new char[iLen+1];
				sprintf(s, "%S", w);	// convert
				assign(s);
				delete [] s;
			}
		}
	}

	// implicit conversion
	operator const char*() const 	{ return c_str(); }
	//	operator const CvWString() const 	{ return CvWString(c_str()); }

	// operators
	char& operator[](int i) { return std::string::operator[](i);	}
	char& operator[](std::string::size_type i) { return std::string::operator[](i);	}
	const char operator[](int i) const { return std::string::operator[](i);	}
	const CvString& operator=( const char* s) { if (s) assign(s); else clear();	return *this; }
	const CvString& operator=( const std::string& s) { assign(s.c_str());	return *this; }
//	const CvString& operator=( const std::wstring& w) { Copy(w.c_str());	return *this; }		// don't want accidental conversions down to narrow strings
//	const CvString& operator=( const wchar* w) { Copy(w);	return *this; }

	// FString compatibility
	bool IsEmpty() const { return empty();	}
	const char* GetCString() const 	{ return c_str(); }							// convert
	int CompareNoCase( const char* lpsz ) const { return stricmp(lpsz, c_str()); }
	int CompareNoCase( const char* lpsz, int iLength ) const { return strnicmp(lpsz, c_str(), iLength);  }
	void Format( LPCSTR lpszFormat, ... );
	int GetLength() const { return size(); }
	int Replace( char chOld, char chNew );
/*************************************************************************************************/
/**	TrueModular								05/26/09	Written: Mr. Genie	Imported: Xienwolf	**/
/**				Replace a full string instead of a single character								**/
/**	Properly links Modular modifications to previous elements, and allows partial overwriting	**/
/*************************************************************************************************/
	int Replace( const CvString& searchString, const CvString& replaceString);
/*************************************************************************************************/
/**	TrueModular								END													**/
/*************************************************************************************************/

	void getTokens(const CvString& delimiters, std::vector<CvString>& tokensOut) const;

	// static helpers
	static bool formatv(std::string& out, const char * fmt, va_list args);
	static bool format(std::string & out, const char * fmt, ...);
	static CvString format(const char * fmt, ...);
	static std::string formatv(const char * fmt, va_list args);
};

//////////////////////////////////////////////////////////////////////////
// INLINES
// Don't move these into a cpp file, since I don't want CvString to be part of the DLL, MT
//////////////////////////////////////////////////////////////////////////

inline int CvString::Replace( char chOld, char chNew )
{
	int i, iCnt = 0;
	for(i=0;i<(int)size();i++)
	{
		if ((*this)[i] == chOld)
		{
			replace(i, 1, std::string(1, chNew) );
			iCnt++;
		}
	}
	return iCnt;
}

/*************************************************************************************************/
/**	TrueModular								05/26/09	Written: Mr. Genie	Imported: Xienwolf	**/
/**		Doing a function as an INLINE keeps us from slowing down everything as much I guess		**/
/**	Properly links Modular modifications to previous elements, and allows partial overwriting	**/
/*************************************************************************************************/
inline int CvString::Replace(const CvString& searchString, const CvString& replaceString)
{
	int iCnt = 0;
	std::string::size_type pos = this->find(searchString, 0);
	int intLengthSearch = searchString.length();

	while(std::string::npos != pos)
	{
		this->replace(pos, intLengthSearch, replaceString);
		pos = this->find(searchString, pos + intLengthSearch);
		iCnt++;
	}

	return iCnt;
}
/*************************************************************************************************/
/**	TrueModular								END													**/
/*************************************************************************************************/
inline void CvString::getTokens(const CvString& delimiters, std::vector<CvString>& tokensOut) const
{
	//tokenizer code taken from http://www.digitalpeer.com/id/simple

	// skip delimiters at beginning.
	size_type lastPos = find_first_not_of(delimiters, 0);

	// find first "non-delimiter".
	size_type pos = find_first_of(delimiters, lastPos);

	while (CvString::npos != pos || CvString::npos != lastPos)
	{
		// found a token, parse it.
		CvString token = substr(lastPos, pos - lastPos);
		tokensOut.push_back(token);

		// skip delimiters.  Note the "not_of"
		lastPos = find_first_not_of(delimiters, pos);

		// find next "non-delimiter"
		pos = find_first_of(delimiters, lastPos);
	}
}

// CvString / CvWString variadic format / Format / formatv helpers are
// defined in CvString.cpp (out-of-line). Inlining the variadic dispatcher
// corrupts va_start under some clang inlining-cost configurations.

#endif	// CvString_h

