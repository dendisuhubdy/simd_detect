/* cpu_x86_Windows.ipp
 * 
 * Author           : Alexander J. Yee
 * Modified         : Dendi Suhubdy
 * Date Created     : 04/12/2014
 * Last Modified    : 06/30/2018
 * 
 */

#include <Windows.h>
#include <intrin.h>

#include "cpu_x86.h"

namespace simd_detect{
    void cpu_x86::cpuid(int32_t out[4], int32_t x){
        __cpuidex(out, x, 0);
    }
    __int64 xgetbv(unsigned int x){
        return _xgetbv(x);
    }
    //  Detect 64-bit - Note that this snippet of code for detecting 64-bit has been copied from MSDN.
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    BOOL IsWow64()
    {
        BOOL bIsWow64 = FALSE;

        LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
            GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

        if (NULL != fnIsWow64Process)
        {
            if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
            {
                printf("Error Detecting Operating System.\n");
                printf("Defaulting to 32-bit OS.\n\n");
                bIsWow64 = FALSE;
            }
        }
        return bIsWow64;
    }
    bool cpu_x86::detect_OS_x64(){
#ifdef _M_X64
        return true;
#else
        return IsWow64() != 0;
#endif
    }

}
