

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Nov 14 21:05:09 2014
 */
/* Compiler settings for HMCEncoder.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_HMCEncoderLib,0x7D308C03,0xFB74,0x49ED,0x9C,0x3B,0xAA,0x4B,0x78,0x14,0xC4,0xB5);


MIDL_DEFINE_GUID(IID, IID_IHMCEncoder,0x2FDD6C62,0xCA3B,0x4D2A,0xA9,0x2C,0x10,0x7E,0xA5,0x51,0xF4,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCEncoder,0x2FDD6C62,0xCA3B,0x4D2A,0xA9,0x1C,0x10,0x7E,0xA5,0x51,0xF4,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCEncoderPage,0x2FDD6C62,0xCA3B,0x4D2A,0xA9,0x3C,0x10,0x7E,0xA5,0x51,0xF4,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCEncoderLogPage,0x2FDD6C62,0xCA3B,0x4D2A,0xA9,0x4C,0x10,0x7E,0xA5,0x51,0xF4,0x2D);


MIDL_DEFINE_GUID(IID, IID_IHMCFrameRate,0x89F5B7A4,0xF4DE,0x48A6,0xBB,0x2C,0xD8,0xAD,0x77,0x2D,0x17,0x7B);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCFrameRate,0x89F5B7A4,0xF4DE,0x48A6,0xBB,0x1C,0xD8,0xAD,0x77,0x2D,0x17,0x7B);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCFrameRatePage,0x89F5B7A4,0xF4DE,0x48A6,0xBB,0x3C,0xD8,0xAD,0x77,0x2D,0x17,0x7B);


MIDL_DEFINE_GUID(IID, IID_IHMCDesktopSource,0x3D7090C2,0xB04C,0x42F2,0x93,0x24,0x3E,0x7E,0xE2,0xBE,0xEF,0xE7);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCDesktopSource,0x3D7090C2,0xB04C,0x42F2,0x93,0x14,0x3E,0x7E,0xE2,0xBE,0xEF,0xE7);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCDesktopSourcePage,0x3D7090C2,0xB04C,0x42F2,0x93,0x34,0x3E,0x7E,0xE2,0xBE,0xEF,0xE7);


MIDL_DEFINE_GUID(IID, IID_IHMCFrameWriter,0xE6E91083,0x47A0,0x41CE,0xA7,0x21,0x61,0x1A,0x62,0x11,0x1F,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCFrameWriter,0xE6E91083,0x47A0,0x41CE,0xA7,0x11,0x61,0x1A,0x62,0x11,0x1F,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_HMCFrameWriterPage,0xE6E91083,0x47A0,0x41CE,0xA7,0x31,0x61,0x1A,0x62,0x11,0x1F,0x6A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



