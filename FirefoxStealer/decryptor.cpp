#include "decryptor.h"
#include <fstream>
#include <string>
PNSSINIT nss_init;    // Function pointer
PDECRYPT PK11_decrypt;    // Function pointer
PNSSSHUTDOWN nss_shutdown;    // Function pointer
PK11_SETPSWDFUNC nss_setpswf;
SECUGetModulePassword secu_gmpwd;
HINSTANCE libnss;
HINSTANCE libplc;





HMODULE LoadLibrary2(char* libDir, const char* libName) {
    char loadPath[4096] = { 0 };
    HMODULE tmpLib = NULL;

    strcpy_s(loadPath, libDir);
    strcat_s(loadPath, "\\");
    strcat_s(loadPath, libName);

    std::cout << loadPath;

    if (!strcmp(libName, "nss3.dll")) {
        libnss = LoadLibraryA(loadPath);
        tmpLib = libnss;
    }
    else if (!strcmp(libName, "plc4.dll")) {
        libplc = LoadLibraryA(loadPath);
        tmpLib = libplc;
    }
    else {
        tmpLib = LoadLibraryA(loadPath);
    }

    if (NULL == tmpLib) {
        printf("Failed to load library %s\n", libName);
        return NULL;
    }

    printf("%s loaded successfuly\n", libName);

    return tmpLib;
}


static int LoadFirefoxLibraries(char* firefoxPath) {
    int i = 0;
    //const char* libName = NULL;

    // Load the libraries from firefox path.
    if (NULL == firefoxPath) {
        return 1;
    }

    char loadPath[4096] = { 0 };
    strcpy_s(loadPath, firefoxPath);
    strcat_s(loadPath, "\\");
    strcat_s(loadPath, "dependentlibs.list");

    std::cout << loadPath;

    std::ifstream inFile(loadPath);
    std::string LibName;

    while (getline(inFile, LibName)) {
      
        if (NULL == LoadLibrary2(firefoxPath, LibName.c_str())) {
            return 1;
        }

    }
    inFile.close();

    printf("Firefox libraries loaded successfully\n");

}
//

static int InitializeNSSLibrary(const char* userPath) {
    //PK11_SetPasswordFunc



    if ((*nss_init) (userPath) != SECSuccess) {
        printf("Initialization failed , Make sure key3.db and cert8.db "\
            "files are present in the specified directory\n");

        return 0;
    }
    printf("NSS library initiliazed successfully\n");

    return 1;
}


HRESULT DecryptFunction(char* dllPath, const char* userPath)
{
   
        HRESULT hrReturnVal;
        
        LoadFirefoxLibraries(dllPath);
   
        nss_init = (PNSSINIT)GetProcAddress(libnss, "NSS_Init");
        PK11_decrypt = (PDECRYPT)GetProcAddress(libnss, "PK11_Decrypt");
        nss_shutdown = (PNSSSHUTDOWN)GetProcAddress(libnss, "NSS_Shutdown");;    // Function pointer
        //PK11_SETPSWDFUNC nss_setpswf;
        //SECUGetModulePassword secu_gmpwd;
        nss_setpswf = (PK11_SETPSWDFUNC)GetProcAddress(libnss, "PK11_SetPasswordFunc");
        secu_gmpwd = (SECUGetModulePassword)GetProcAddress(libnss, "SEC_");
        std::cout << nss_init;
        if (NULL != nss_init)
        {
            // call the NssInit
            std::cout << userPath;
            if (!InitializeNSSLibrary(userPath)) {
                std::cout << "not init";
                return 1;
            }
        }
        else
        {
            // report the error
            std::cout << "load nss_int faled";
            hrReturnVal = ERROR_DELAY_LOAD_FAILED;
        }
     
    return hrReturnVal;
}


