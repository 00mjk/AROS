/*
    Copyright � 1995-2010, The AROS Development Team. All rights reserved.
    $Id$

    Desc: PrepareContext() - Prepare a task context for dispatch.
    Lang: english
*/

#include <exec/execbase.h>
#include <exec/memory.h>
#include <utility/tagitem.h>
#include <proto/kernel.h>
#include <aros/ppc/cpucontext.h>

#include "etask.h"
#include "exec_intern.h"
#include "exec_util.h"

#define _PUSH(sp, val) *--sp = (IPTR)val

AROS_LH4(BOOL, PrepareContext,
	 AROS_LHA(VOLATILE struct Task *, task,       A0),
	 AROS_LHA(APTR,                   entryPoint, A1),
	 AROS_LHA(APTR,                   fallBack,   A2),
	 AROS_LHA(struct TagItem *,       tagList,    A3),
	 struct ExecBase *, SysBase, 6, Exec)
{
    AROS_LIBFUNC_INIT

    struct ExceptionContext *ctx;

    if (!(task->tc_Flags & TF_ETASK) )
	return FALSE;
  
    ctx = KrnCreateContext();
    GetIntETask (task)->iet_Context = ctx;
    if (!ctx)
	return FALSE;

    /* Set up arguments first */
    while(tagList)
    {
    	switch(tagList->ti_Tag)
	{
	    case TAG_MORE:
	    	tagList = (struct TagItem *)tagList->ti_Data;
		continue;
		
	    case TAG_SKIP:
	    	tagList += tagList->ti_Data;
		break;
		
	    case TAG_DONE:
	    	tagList = NULL;
    	    	break;
		
#define HANDLEARG(x) \
	    case TASKTAG_ARG ## x:			       \
	    	ctx->gpr[3 + x - 1] = (ULONG)tagList->ti_Data; \
		break;

	    HANDLEARG(1)
	    HANDLEARG(2)
	    HANDLEARG(3)
	    HANDLEARG(4)
	    HANDLEARG(5)
	    HANDLEARG(6)
	    HANDLEARG(7)
	    HANDLEARG(8)
	}
	
	if (tagList) tagList++;
    }

    /* Next we set up return address */    
    ctx->lr = (ULONG)fallBack;

    /* Then set up the frame to be used by Dispatch() */
    ctx->gpr[1] = (ULONG)task->tc_SPReg;
    ctx->ip = (ULONG)entryPoint;

    return TRUE;

    AROS_LIBFUNC_EXIT
} /* PrepareContext() */
