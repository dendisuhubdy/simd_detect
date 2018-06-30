/* cpu_x86_Linux.ipp
 * 
 * Author           : Alexander J. Yee
 * Modified         : Dendi Suhubdy
 * Date Created     : 04/12/2014
 * Last Modified    : 06/30/2018
 * 
 */

#include <cpuid.h>
#include "cpu_x86.h"

namespace simd_detect{

    void cpu_x86::cpuid(int32_t out[4], int32_t x){
        __cpuid_count(x, 0, out[0], out[1], out[2], out[3]);
    }
    uint64_t xgetbv(unsigned int index){
        uint32_t eax, edx;
        __asm__ __volatile__("xgetbv" : "=a"(eax), "=d"(edx) : "c"(index));
        return ((uint64_t)edx << 32) | eax;
    }
#define _XCR_XFEATURE_ENABLED_MASK  0
    //  Detect 64-bit
    bool cpu_x86::detect_OS_x64(){
        //  We only support x64 on Linux.
        return true;
    }
}
