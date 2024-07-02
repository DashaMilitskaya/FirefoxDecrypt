#pragma once
#include "windows.h"
#include <iostream>


enum class SECItemType {
    siBuffer = 0,
    siClearDataBuffer = 1,
    siCipherDataBuffer,
    siDERCertBuffer,
    siEncodedCertBuffer,
    siDERNameBuffer,
    siEncodedNameBuffer,
    siAsciiNameString,
    siAsciiString,
    siDEROID,
    siUnsignedInteger,
    siUTCTime,
    siGeneralizedTime
};

struct SECItem {
    SECItemType type;
    unsigned char* data;
    size_t len;
};


typedef enum SECStatus
{
    SECWouldBlock = -2,
    SECFailure = -1,
    SECSuccess = 0
};


typedef SECStatus(*PNSSINIT) (const char* configdir);
typedef HRESULT(CALLBACK* PDECRYPT)(SECItem*, SECItem*, void*);
typedef HRESULT(CALLBACK* PNSSSHUTDOWN)();
//PK11_SetPasswordFunc

typedef void(*PK11_SETPSWDFUNC)(void*);
//SECU_GetModulePassword
//char * SECU_GetModulePassword(PK11SlotInfo* slot, PRBool retry, void* arg)

typedef CHAR* (*SECUGetModulePassword)(void* slot, bool retry, void* arg);

HRESULT DecryptFunction(char* dllPath, const char * userPath);