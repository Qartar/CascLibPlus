// CascStorage.hpp
//

#pragma once

#include "CascLib.hpp"
#include "CascFile.hpp"
#include "CascIterator.hpp"

class CascStorage
{
public:
    CascStorage();
    ~CascStorage();

    bool Open(TCHAR const* szDataPath, DWORD dwLocaleMask);
    void Close();

    CascFindFiles FindFiles(char const* szMask, TCHAR const* szListFile);

    DWORD GetFileId(char const* szFileName);

    CascFile OpenFileByIndexKey(PQUERY_KEY pIndexKey, DWORD dwFlags);
    CascFile OpenFileByEncodingKey(PQUERY_KEY pEncodingKey, DWORD dwFlags);
    CascFile OpenFile(char const* szFileName, DWORD dwLocale, DWORD dwFlags);

protected:
    HANDLE _storage;
};
