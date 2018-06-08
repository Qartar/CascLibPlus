// CascStorage.hpp
//

#pragma once

#include "CascLib.hpp"
#include "CascFile.hpp"
#include "CascIterator.hpp"

////////////////////////////////////////////////////////////////////////////////
/**
 * Encapsulates the state of a storage handle.
 */
class CascStorage
{
public:
    CascStorage(TCHAR const* szDataPath, DWORD dwLocaleMask);
    ~CascStorage();

    bool GetStorageInfo(CASC_STORAGE_INFO_CLASS InfoClass, void* pvStorageInfo, size_t cbStorageInfo, size_t* pcbLengthNeeded);

    CascFile OpenFileByEKey(PQUERY_KEY pCKey, PQUERY_KEY pEKey, DWORD dwEncodedSize);
    CascFile OpenFileByCKey(PQUERY_KEY pCKey);
    CascFile OpenFile(char const* szFileName, DWORD dwLocale, DWORD dwFlags);

    DWORD GetFileId(char const* szFileName);

    CascFindFiles FindFiles(char const* szMask, TCHAR const* szListFile);

protected:
    HANDLE _storage;
};
