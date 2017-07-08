// CascIterator.cpp
//

#include "CascIterator.hpp"
#include "CascStorage.hpp"

//------------------------------------------------------------------------------
CascIterator::CascIterator(CascFindFiles* pFind, HANDLE hFind, CASC_FIND_DATA* pData)
    : _find(pFind)
    , _handle(hFind)
    , _data(pData ? *pData : CASC_FIND_DATA())
    , _valid(hFind ? true : false)
{
}

//------------------------------------------------------------------------------
CascIterator::CascIterator(CascIterator&& other)
    : _find(other._find)
    , _handle(other._handle)
    , _data(other._data)
    , _valid(other._valid)
{
    other._handle = NULL;
    other._valid = false;
}

//------------------------------------------------------------------------------
CascIterator::~CascIterator()
{
    if (_handle) {
        CascFindClose(_handle);
    }
}

//------------------------------------------------------------------------------
CascIterator& CascIterator::operator=(CascIterator&& other)
{
    if (_handle) {
        CascFindClose(_handle);
    }
    _find = other._find;
    _handle = other._handle;
    _data = other._data;
    _valid = other._valid;

    other._handle = NULL;
    other._valid = false;

    return *this;
}

//------------------------------------------------------------------------------
bool CascIterator::operator!=(CascIterator const& rhs)
{
    return (_find != rhs._find ||
            (_handle && rhs._handle && _handle != rhs._handle) ||
            _valid != rhs._valid);
}

//------------------------------------------------------------------------------
CascIterator& CascIterator::operator++()
{
    if (_valid) {
        _valid = CascFindNextFile(_handle, &_data);
    }
    return *this;
}

//------------------------------------------------------------------------------
CascFile CascIterator::operator*()
{
    return CascFile(_find->_storage, _data);
}

//------------------------------------------------------------------------------
CascFindFiles::CascFindFiles(HANDLE hStorage, char const* szMask, TCHAR const* szListFile)
    : _storage(hStorage)
    , _mask(szMask)
    , _listfile(szListFile)
{
}

//------------------------------------------------------------------------------
CascIterator CascFindFiles::begin()
{
    CASC_FIND_DATA Data;
    HANDLE hFind = CascFindFirstFile(_storage, _mask.c_str(), &Data, _listfile.c_str());

    return CascIterator(this, hFind, &Data);
}

//------------------------------------------------------------------------------
CascIterator CascFindFiles::end()
{
    return CascIterator(this, NULL, NULL);
}

//------------------------------------------------------------------------------
CascFindFiles::~CascFindFiles()
{
}
