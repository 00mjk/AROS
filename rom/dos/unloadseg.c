/*
    (C) 1995-96 AROS - The Amiga Replacement OS
    $Id$
    $Log$
    Revision 1.8  1997/12/14 20:21:18  hkiel
    Changed to use cpak.

    Revision 1.7  1997/12/11 14:32:09  bergers
    UnLoadSeg() built on top of InternalUnLoadSeg().


    Revision 1.7  1997/12/09 00:17:00  bergers
    Calls InternalUnLoadSeg() now.

    Revision 1.6  1997/01/27 00:36:33  ldp
    Polish

    Revision 1.5  1996/12/09 13:53:48  aros
    Added empty templates for all missing functions

    Moved #include's into first column

    Revision 1.4  1996/10/24 15:50:38  aros
    Use the official AROS macros over the __AROS versions.

    Revision 1.3  1996/08/13 13:52:52  digulla
    Replaced <dos/dosextens.h> by "dos_intern.h" or added "dos_intern.h"
    Replaced AROS_LA by AROS_LHA

    Revision 1.2  1996/08/01 17:40:59  digulla
    Added standard header for all files

    Desc:
    Lang: english
*/
#include <proto/exec.h>
#include <dos/dos.h>
#include "dos_intern.h"

extern void Exec_FreeMem();

/*****************************************************************************

    NAME */
#include <proto/dos.h>

        AROS_LH1(BOOL, UnLoadSeg,

/*  SYNOPSIS */
        AROS_LHA(BPTR, seglist, D1),

/*  LOCATION */
        struct DosLibrary *, DOSBase, 26, Dos)

/*  FUNCTION
        Free a segment list allocated with LoadSeg().

    INPUTS
        seglist - The segment list.

    RESULT
        success = returns whether everything went ok. Returns FALSE if
                  seglist was NULL.
    NOTES

    EXAMPLE

    BUGS

    SEE ALSO
        LoadSeg()

    INTERNALS

    HISTORY
        29-10-95    digulla automatically created from
                            dos_lib.fd and clib/dos_protos.h

*****************************************************************************/
{
  AROS_LIBFUNC_INIT
  AROS_LIBBASE_EXT_DECL(struct DosLibrary *,DOSBase)


  if (seglist)
    return InternalUnLoadSeg(seglist, (void *)&Exec_FreeMem);

  return FALSE;

  AROS_LIBFUNC_EXIT
} /* UnLoadSeg */
