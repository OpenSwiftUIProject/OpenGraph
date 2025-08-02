//
//  OGVersion.c
//  OpenGraph

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGVersion.h>

#if OPENGRAPH_RELEASE == OPENGRAPH_RELEASE_2024
const double OpenGraphVersionNumber __attribute__ ((used)) = (double)6.0;
const unsigned char OpenGraphVersionString[] __attribute__ ((used)) = "@(#)PROGRAM:OpenGraph  PROJECT:OpenGraph-6.0.87\n";
const uint64_t OGVersion = 0x2001e;
#elif OPENGRAPH_RELEASE == OPENGRAPH_RELEASE_2021
const double OpenGraphVersionNumber __attribute__ ((used)) = (double)3.2;
const unsigned char OpenGraphVersionString[] __attribute__ ((used)) = "@(#)PROGRAM:OpenGraph  PROJECT:OpenGraph-3.2.1\n";
const uint64_t OGVersion = 0x20014;
#endif
