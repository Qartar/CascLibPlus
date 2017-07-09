// CascStorage.hpp
//

#pragma once

#include "CascLib.hpp"
#include "CascFile.hpp"
#include "CascIterator.hpp"

////////////////////////////////////////////////////////////////////////////////
/**
 *
 */
class CascStorage
{
public:
    CascStorage(TCHAR const* szDataPath, DWORD dwLocaleMask);
    ~CascStorage();

    bool GetStorageInfo(CASC_STORAGE_INFO_CLASS InfoClass, void* pvStorageInfo, size_t cbStorageInfo, size_t* pcbLengthNeeded);

    CascFile OpenFileByIndexKey(PQUERY_KEY pIndexKey, DWORD dwFlags);
    CascFile OpenFileByEncodingKey(PQUERY_KEY pEncodingKey, DWORD dwFlags);
    CascFile OpenFile(char const* szFileName, DWORD dwLocale, DWORD dwFlags);

    DWORD GetFileId(char const* szFileName);

    CascFindFiles FindFiles(char const* szMask, TCHAR const* szListFile);

protected:
    HANDLE _storage;
};
