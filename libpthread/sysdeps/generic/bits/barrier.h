/* Thread barrier attribute type.  Generic version.
   Copyright (C) 2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef _BITS_BARRIER_H
#define _BITS_BARRIER_H	1

#include <bits/spin-lock.h>

/* This structure describes the attributes of a POSIX barrier.  */
struct __pthread_barrier
{
  __pthread_spinlock_t lock;
  struct __pthread *queue; /* List of waiters.  */
  unsigned pending;	/* Number of that still need to wait on
			   barrier.  */
  unsigned count;	/* Number of threads that must wait before
			   barrier is passed.  */
  struct __pthread_barrierattr *attr;
  void *data;
};


#endif /* bits/barrier.h */
