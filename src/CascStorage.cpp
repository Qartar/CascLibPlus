// CascStorage.cpp
//

#include "CascStorage.hpp"

//------------------------------------------------------------------------------
CascStorage::CascStorage()
    : _storage(NULL)
{
}

//------------------------------------------------------------------------------
CascStorage::~CascStorage()
{
    Close();
}

//------------------------------------------------------------------------------
bool CascStorage::Open(TCHAR const* szDataPath, DWORD dwLocaleMask)
{
    Close();

    return CascOpenStorage(szDataPath, dwLocaleMask, &_storage);
}

//------------------------------------------------------------------------------
void CascStorage::Close()
{
    if (_storage != NULL) {
        CascCloseStorage(_storage);
        _storage = NULL;
    }
}

//------------------------------------------------------------------------------
CascFindFiles CascStorage::FindFiles(char const* szMask, TCHAR const* szListFile)
{
    return CascFindFiles(_storage, szMask, szListFile);
}

//------------------------------------------------------------------------------
DWORD CascStorage::GetFileId(char const* szFileName)
{
    return CascGetFileId(_storage, szFileName);
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFileByIndexKey(PQUERY_KEY pIndexKey, DWORD dwFlags)
{
    HANDLE hFile;
    if (CascOpenFileByIndexKey(_storage, pIndexKey, dwFlags, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFileByEncodingKey(PQUERY_KEY pEncodingKey, DWORD dwFlags)
{
    HANDLE hFile;
    if (CascOpenFileByEncodingKey(_storage, pEncodingKey, dwFlags, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFile(char const* szFileName, DWORD dwLocale, DWORD dwFlags)
{
    HANDLE hFile;
    if (CascOpenFile(_storage, szFileName, dwLocale, dwFlags, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}
