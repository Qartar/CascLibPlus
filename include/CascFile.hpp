// CascFile.hpp
//

#pragma once

#include "CascLib.hpp"

class CascStorage;
class CascIterator;

////////////////////////////////////////////////////////////////////////////////
/**
 *
 */
class CascFile
{
public:
    using MD5_HASH = BYTE[MD5_HASH_SIZE];

public:
    CascFile(CascFile&&);
    CascFile& operator=(CascFile&&);
    ~CascFile();

    //! Seek the specified position in the file.
    DWORD Seek(LONGLONG FilePos, DWORD dwMoveMethod);

    //! Read the file into the buffer.
    bool Read(void* lpBuffer, DWORD dwToRead, PDWORD pdwRead);

    //! Return the name of the file.
    char const* Name() const;

    //! Return the base name of the file without relative path.
    char const* BaseName() const;

    //! Return the file contents hash (using MD5).
    MD5_HASH const& Hash() const;

    //! Return the locale flags (WoW only).
    DWORD Locale() const;

    //! Return the file data Id (Wow only).
    DWORD DataId() const;

    //! Return the size of the file according to the file index.
    DWORD Size() const;

    //! Return the uncompressed size of the file.
    ULONGLONG ActualSize() const;

protected:
    HANDLE _file;

    CASC_FIND_DATA _data;

protected:
    friend CascStorage;
    friend CascIterator;

    CascFile(HANDLE hFile);
    CascFile(HANDLE hStorage, CASC_FIND_DATA const& Data);

    CascFile(CascFile const&) = delete;
    CascFile& operator=(CascFile const&) = delete;
};
