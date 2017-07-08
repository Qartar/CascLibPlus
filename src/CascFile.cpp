// CascFile.cpp
//

#include "CascFile.hpp"

namespace {

unsigned char IntToHexChar[] = "0123456789abcdef";

char * StringFromBinary(BYTE const* pbBinary, size_t cbBinary, char * szBuffer)
{
    char * szSaveBuffer = szBuffer;

    // Convert the string to the array of MD5
    // Copy the blob data as text
    for(size_t i = 0; i < cbBinary; i++)
    {
        *szBuffer++ = IntToHexChar[pbBinary[0] >> 0x04];
        *szBuffer++ = IntToHexChar[pbBinary[0] & 0x0F];
        pbBinary++;
    }

    // Terminate the string
    *szBuffer = 0;
    return szSaveBuffer;
}

}

//------------------------------------------------------------------------------
CascFile::CascFile(HANDLE hFile)
    : _file(hFile)
{
}

//------------------------------------------------------------------------------
CascFile::CascFile(CascFile&& other)
    : _file(other._file)
    , _data(other._data)
{
    if (other._data.szPlainName) {
        auto offset = other._data.szPlainName - other._data.szFileName;
        _data.szPlainName = _data.szFileName + offset;
    }
    other._file = NULL;
}

//------------------------------------------------------------------------------
CascFile& CascFile::operator=(CascFile&& other)
{
    if (_file) {
        CascCloseFile(_file);
    }
    _file = other._file;
    _data = other._data;
    if (other._data.szPlainName) {
        auto offset = other._data.szPlainName - other._data.szFileName;
        _data.szPlainName = _data.szFileName + offset;
    }
    other._file = NULL;
    return *this;
}

//------------------------------------------------------------------------------
CascFile::CascFile(HANDLE hStorage, CASC_FIND_DATA const& Data)
    : _file(NULL)
    , _data(Data)
{
    BYTE EncodingKey[MD5_HASH_SIZE];

    memcpy(EncodingKey, Data.EncodingKey, MD5_HASH_SIZE);

    QUERY_KEY QueryKey{EncodingKey, MD5_HASH_SIZE};

    CascOpenFileByEncodingKey(hStorage, &QueryKey, 0, &_file);
}

//------------------------------------------------------------------------------
CascFile::~CascFile()
{
    if (_file) {
        CascCloseFile(_file);
    }
}

//------------------------------------------------------------------------------
DWORD CascFile::Seek(LONGLONG FilePos, DWORD dwMoveMethod)
{
    LARGE_INTEGER li;
    li.QuadPart = FilePos;
    return CascSetFilePointer(_file, li.LowPart, &li.HighPart, dwMoveMethod);
}

//------------------------------------------------------------------------------
bool CascFile::Read(void* lpBuffer, DWORD dwToRead, PDWORD pdwRead)
{
    return CascReadFile(_file, lpBuffer, dwToRead, pdwRead);
}

//------------------------------------------------------------------------------
char const* CascFile::Name() const
{
    return _file ? _data.szFileName : "";
}

//------------------------------------------------------------------------------
char const* CascFile::BaseName() const
{
    return _file ? _data.szPlainName : "";
}

//------------------------------------------------------------------------------
DWORD CascFile::Locale() const
{
    return _file ? _data.dwLocaleFlags : 0;
}

//------------------------------------------------------------------------------
DWORD CascFile::Size() const
{
    return _file ? _data.dwFileSize : 0;
}

//------------------------------------------------------------------------------
ULONGLONG CascFile::ActualSize() const
{
    LARGE_INTEGER li{0,0};
    li.LowPart = CascGetFileSize(_file, (PDWORD)&li.HighPart);
    return li.QuadPart;
}
