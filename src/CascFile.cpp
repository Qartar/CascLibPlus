// CascFile.cpp
//

#include "CascFile.hpp"

//------------------------------------------------------------------------------
BYTE const DefaultEncodingKey[MD5_HASH_SIZE] = {};

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
    LONG HighPart = FilePos >> 32;
    return CascSetFilePointer(_file, FilePos & 0xffffffff, &HighPart, dwMoveMethod);
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
CascFile::MD5_HASH const& CascFile::Hash() const
{
    if (_file) {
        return _data.EncodingKey;
    } else {
        return DefaultEncodingKey;
    }
}

//------------------------------------------------------------------------------
DWORD CascFile::Locale() const
{
    return _file ? _data.dwLocaleFlags : 0;
}

//------------------------------------------------------------------------------
DWORD CascFile::DataId() const
{
    return _file ? _data.dwFileDataId : 0;
}

//------------------------------------------------------------------------------
DWORD CascFile::Size() const
{
    return _file ? _data.dwFileSize : 0;
}

//------------------------------------------------------------------------------
ULONGLONG CascFile::ActualSize() const
{
    DWORD HighPart = 0;
    DWORD LowPart = CascGetFileSize(_file, &HighPart);
    return (static_cast<ULONGLONG>(HighPart) << 32) | LowPart;
}
