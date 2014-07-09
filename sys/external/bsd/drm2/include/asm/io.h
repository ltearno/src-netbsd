/*	$NetBSD: io.h,v 1.2 2014/03/18 18:20:42 riastradh Exp $	*/

/*-
 * Copyright (c) 2013 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Taylor R. Campbell.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ASM_IO_H_
#define _ASM_IO_H_

#include <sys/bus.h>

#include <uvm/uvm_page.h>

#include <linux/mm_types.h>

/*
 * XXX This is bollocks, and is wrong on various architectures (should
 * work for x86; who knows what else), but bus_space_barrier won't work
 * because we have no bus space tag or handle or offset or anything.
 */
#define	mmiowb()	__insn_barrier()

#define	memcpy_fromio	memcpy
#define	memcpy_toio	memcpy
#define	memset_io	memset

/*
 * XXX Not sure why this is here, but so it is in Linux...  Also, not
 * sure what the right type is: Linux uses dma_addr_t, but I don't
 * think bus_addr_t is right here -- paddr_t sounds more appropriate.
 */

static inline bus_addr_t
page_to_phys(struct page *page)
{
	return VM_PAGE_TO_PHYS(&page->p_vmp);
}

#endif  /* _ASM_IO_H_ */
