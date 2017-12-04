// CascIterator.hpp
//

#pragma once

#include "CascLib.hpp"
#include "CascFile.hpp"

#include <string>

#ifdef _UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif

class CascStorage;
class CascFindFiles;

////////////////////////////////////////////////////////////////////////////////
/**
 * Enables iteration over files in the `CascStorage` object using C++11's
 * ranged-based for loop syntax. You should not need to manipulate this class
 * directly.
 */
class CascIterator
{
public:
    ~CascIterator();
    CascIterator(CascIterator&&);
    CascIterator& operator=(CascIterator&&);

    bool operator!=(CascIterator const&);

    CascFile operator*();
    CascIterator& operator++();

protected:
    CascFindFiles* _find;
    HANDLE _handle;
    CASC_FIND_DATA _data;
    bool _valid;

protected:
    friend CascFindFiles;

    CascIterator(CascFindFiles* pFind, HANDLE hFind, CASC_FIND_DATA* pData);
    CascIterator(CascIterator const&) = delete;
    CascIterator& operator=(CascIterator const&) = delete;
};

////////////////////////////////////////////////////////////////////////////////
/**
 * Enables iteration over files in the `CascStorage` object using C++11's
 * ranged-based for loop syntax. You should not need to manipulate this class
 * directly.
 */
class CascFindFiles
{
public:
    ~CascFindFiles();

    CascIterator begin();
    CascIterator end();

protected:
    HANDLE _storage;
    std::string _mask;
    tstring _listfile;

protected:
    friend CascStorage;
    friend CascIterator;

    CascFindFiles(HANDLE hStorage, char const* szMask, TCHAR const* szListFile);
};
