/*	$NetBSD: kernel.h,v 1.2 2014/04/01 14:57:58 riastradh Exp $	*/

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

#ifndef _LINUX_KERNEL_H_
#define _LINUX_KERNEL_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/param.h>

#define	__printf	__printflike
#define	__user
#define	__must_check	/* __attribute__((warn_unused_result)), if GCC */
#define	__always_unused	__unused

#define	barrier()	__insn_barrier()
#define	unlikely(X)	__predict_false(X)

/*
 * XXX Linux kludge to work around GCC uninitialized variable warning.
 * Linux does `x = x', which is bollocks.
 */
#define	uninitialized_var(x)	x = 0

/* XXX These will multiply evaluate their arguments.  */
#define	max_t(T, X, Y)	MAX(X, Y)
#define	min_t(T, X, Y)	MIN(X, Y)

/*
 * Rounding to nearest.
 */
#define	DIV_ROUND_CLOSEST(N, D)						\
	((0 < (N)) ? (((N) + ((D) / 2)) / (D))				\
	    : (((N) - ((D) / 2)) / (D)))

/*
 * Rounding to what may or may not be powers of two.
 */
#define	DIV_ROUND_UP(X, N)	(((X) + (N) - 1) / (N))

/*
 * Rounding to powers of two -- carefully avoiding multiple evaluation
 * of arguments and pitfalls with C integer arithmetic rules.
 */
#define	round_up(X, N)		((((X) - 1) | ((N) - 1)) + 1)
#define	round_down(X, N)	((X) & ~(uintmax_t)((N) - 1))

/*
 * These select 32-bit halves of what may be 32- or 64-bit quantities,
 * for which straight 32-bit shifts may be undefined behaviour (and do
 * the wrong thing on most machines: return the input unshifted by
 * ignoring the upper bits of the shift count).
 */
#define	upper_32_bits(X)	((uint32_t) (((X) >> 16) >> 16))
#define	lower_32_bits(X)	((uint32_t) ((X) & 0xffffffffUL))

/*
 * Given x = &c->f, container_of(x, T, f) gives us back c, where T is
 * the type of c.
 */
#define	container_of(PTR, TYPE, FIELD)					\
	((void)sizeof((PTR) -						\
		&((TYPE *)(((char *)(PTR)) -				\
		    offsetof(TYPE, FIELD)))->FIELD),			\
	    ((TYPE *)(((char *)(PTR)) - offsetof(TYPE, FIELD))))

#define	ARRAY_SIZE(ARRAY)	__arraycount(ARRAY)

#define	swap(X, Y)	do						\
{									\
	/* XXX Kludge for type-safety.  */				\
	if (&(X) != &(Y)) {						\
		CTASSERT(sizeof(X) == sizeof(Y));			\
		/* XXX Can't do this much better without typeof.  */	\
		char __swap_tmp[sizeof(X)];				\
		(void)memcpy(__swap_tmp, &(X), sizeof(X));		\
		(void)memcpy(&(X), &(Y), sizeof(X));			\
		(void)memcpy(&(Y), __swap_tmp, sizeof(X));		\
	}								\
} while (0)

static inline int64_t
abs64(int64_t x)
{
	return (x < 0? (-x) : x);
}

static int panic_timeout __unused = 0;

#endif  /* _LINUX_KERNEL_H_ */
