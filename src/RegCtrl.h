#pragma once

class RegCtrl
{
public:
	RegCtrl(void);
	~RegCtrl(void);

	bool Find(HKEY hKey, LPCTSTR lpSubKey);
	bool Create(HKEY hKey, LPCTSTR lpSubKey);

	bool Read(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD& dwType, LPBYTE lpData, DWORD& cbData);
	bool Read(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, BYTE lpByte[], DWORD& cbData);

	bool Write(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwType, const BYTE *lpData, DWORD cbData);
	bool Write(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const BYTE lpByte[], DWORD cbData);

	long GetRegLastError();

private:
	HKEY m_hKey;
	long m_nLastError;
};
