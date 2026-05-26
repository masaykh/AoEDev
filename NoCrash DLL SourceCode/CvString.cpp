// Out-of-line definitions for CvString / CvWString variadic format helpers.
//
// These functions used to live inline in CvString.h. Under some clang
// inlining-cost configurations, the trivial 'format(fmt, ...)' wrapper was
// being inlined despite __attribute__((noinline)) on the declaration. When
// a variadic function is inlined, its 'fmt' parameter no longer exists as a
// real stack parameter, so the va_start() macro resolves to a pointer into
// random caller-frame memory and the first read of any '%s' argument crashes
// inside _vsnprintf. Moving the bodies into this TU guarantees a single
// out-of-line definition that clang cannot inline against.
//
// CV4_NOINLINE kept on the definitions for documentation / belt-and-braces.

#include "CvGameCoreDLL.h"
#include "CvString.h"

//
// static
//
CV4_NOINLINE bool CvString::formatv(std::string & out, const char * fmt, va_list args)
{
	char buf[2048];
	char * pbuf = buf;
	int len = 0;
	int attempts = 0;
	bool success = false;
	const int kMaxAttempts = 40;

	do
	{
		int maxlen = 2047+2048*attempts;
		len = _vsnprintf(pbuf,maxlen,fmt,args);
		attempts++;
		success = (len>=0 && len<=maxlen);
		if (!success)
		{
			if (pbuf!=buf)
				delete [] pbuf;
			pbuf = new char[2048+2048*attempts];
		}
	}
	while (!success && attempts<kMaxAttempts);

	if (success)
		out = pbuf;
	else
		out = "";

	if (pbuf!=buf)
		delete [] pbuf;

	return success;
}

//
// static
//
CV4_NOINLINE bool CvWString::formatv(std::wstring & out, const wchar * fmt, va_list args)
{
	wchar buf[2048];
	wchar * pbuf = buf;
	int len = 0;
	int attempts = 0;
	bool success = false;
	const int kMaxAttempts = 40;

	do
	{
		int maxlen = 2047+2048*attempts;
		len = _vsnwprintf(pbuf,maxlen,fmt,args);
		attempts++;
		success = (len>=0 && len<=maxlen);
		if (!success)
		{
			if (pbuf!=buf)
				delete [] pbuf;
			pbuf = new wchar[2048+2048*attempts];
		}
	}
	while (!success && attempts<kMaxAttempts);

	if (success)
		out = pbuf;
	else
		out = L"";

	if (pbuf!=buf)
		delete [] pbuf;

	return success;
}

//
// static
//
CV4_NOINLINE std::wstring CvWString::formatv(const wchar * fmt, va_list args)
{
	std::wstring result;
	formatv( result, fmt, args );
	return result;
}

//
// static
//
CV4_NOINLINE CvWString CvWString::format(const wchar * fmt, ...)
{
	std::wstring result;
	va_list args;
	va_start(args,fmt);
	formatv(result,fmt,args);
	va_end(args);
	return CvWString(result);
}

//
// static
//
CV4_NOINLINE bool CvWString::format(std::wstring & out, const wchar * fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	bool r = formatv(out,fmt,args);
	va_end(args);
	return r;
}

CV4_NOINLINE void CvWString::Format( LPCWSTR lpszFormat, ... )
{
	std::wstring result;
	va_list args;
	va_start(args,lpszFormat);
	formatv(result,lpszFormat,args);
	va_end(args);
	*this = result;
}

//
// static
//
CV4_NOINLINE std::string CvString::formatv(const char * fmt, va_list args)
{
	std::string result;
	formatv( result, fmt, args );
	return result;
}

//
// static
//
CV4_NOINLINE CvString CvString::format(const char * fmt, ...)
{
	std::string result;
	va_list args;
	va_start(args,fmt);
	formatv(result,fmt,args);
	va_end(args);
	return CvString(result);
}

//
// static
//
CV4_NOINLINE bool CvString::format(std::string & out, const char * fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	bool r = formatv(out,fmt,args);
	va_end(args);
	return r;
}

CV4_NOINLINE void CvString::Format( LPCSTR lpszFormat, ... )
{
	std::string result;
	va_list args;
	va_start(args,lpszFormat);
	formatv(result,lpszFormat,args);
	va_end(args);
	*this = result;
}
