#include "RegCtrl.h"

RegCtrl::RegCtrl(void)
{
}

RegCtrl::~RegCtrl(void)
{
}

bool RegCtrl::Find(HKEY hKey, LPCTSTR lpSubKey)
{
	m_nLastError = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &m_hKey);
	if(ERROR_SUCCESS == m_nLastError)
	{
		RegCloseKey(m_hKey);
	}
	else
	{
		return false;
	}
	return true;
}

bool RegCtrl::Create(HKEY hKey, LPCTSTR lpSubKey)
{
	CString sSubKey(lpSubKey);
	CString sChildKey;
	int curPos = 0;

	m_nLastError = ERROR_SUCCESS;
	sChildKey= sSubKey.Tokenize(_T("\\"),curPos);
	while (sChildKey != _T(""))
	{
		TCHAR szKey[260];
		_tcscpy(szKey, sSubKey.Mid(0, curPos - 1));
		if(!Find(hKey, szKey))
		{
			m_nLastError = RegCreateKey(hKey, szKey, &m_hKey);
			RegCloseKey(m_hKey);
		}
		if(ERROR_SUCCESS != m_nLastError)
			break;
		sChildKey = sSubKey.Tokenize(_T("\\"), curPos);
	}   

	if(ERROR_SUCCESS != m_nLastError)
	{
		return false;
	}
	return true;
}

bool RegCtrl::Read(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD& dwType, LPBYTE lpData, DWORD& cbData)
{
	m_nLastError = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKey);
	if(ERROR_SUCCESS == m_nLastError)
	{
		m_nLastError = RegQueryValueEx(hKey, lpValueName, NULL, &dwType, lpData, &cbData);
		RegCloseKey(m_hKey);
	}
	else
	{
		return false;
	}
	if(ERROR_SUCCESS == m_nLastError)
		return true;
	else 
		return false;
}

bool RegCtrl::Read(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, BYTE lpByte[], DWORD& cbData)
{
	DWORD dwType = REG_BINARY;		
	m_nLastError = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &m_hKey);
	if(ERROR_SUCCESS == m_nLastError)
	{
		m_nLastError = RegQueryValueEx(m_hKey, lpValueName, NULL, &dwType, lpByte, &cbData);
		RegCloseKey(m_hKey);
	}
	else
	{
		return false;
	}
	if(ERROR_SUCCESS == m_nLastError)
		return true;
	else 
		return false;
}

bool RegCtrl::Write(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwType, const BYTE *lpData, DWORD cbData)
{
	m_nLastError = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_WRITE, &m_hKey);
	if(ERROR_SUCCESS == m_nLastError)
	{
		m_nLastError = RegSetValueEx(m_hKey, lpValueName, NULL, dwType, lpData, cbData);
		RegCloseKey(m_hKey);
	}
	else
	{
		return false;
	}
	if(ERROR_SUCCESS == m_nLastError)
		return true;
	else 
		return false;
}

bool RegCtrl::Write(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const BYTE lpByte[], DWORD cbData)
{
	m_nLastError = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_WRITE, &m_hKey);
	if(ERROR_SUCCESS == m_nLastError)
	{
		m_nLastError = RegSetValueEx(m_hKey, lpValueName, NULL, REG_BINARY, lpByte, cbData);
		RegCloseKey(m_hKey);
	}
	else
	{
		return false;
	}
	if(ERROR_SUCCESS == m_nLastError)
		return true;
	else 
		return false;
}

long RegCtrl::GetRegLastError()
{
	return m_nLastError;
}

