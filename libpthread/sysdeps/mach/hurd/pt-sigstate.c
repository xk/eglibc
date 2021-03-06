/* Set a thread's signal state.  Hurd on Mach version.
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

#include <pthread.h>
#include <assert.h>
#include <signal.h>
#include <hurd/signal.h>
#include <hurd/msg.h>

#include <pt-internal.h>

error_t
__pthread_sigstate (struct __pthread *thread, int how,
		    const sigset_t *set, sigset_t *oset,
		    int clear_pending)
{
  error_t err = 0;
  struct hurd_sigstate *ss;
  sigset_t pending;

  ss = _hurd_thread_sigstate (thread->kernel_thread);
  assert (ss);

  _hurd_sigstate_lock (ss);

  if (oset)
    *oset = ss->blocked;

  if (set)
    switch (how)
      {
      case SIG_BLOCK:
	ss->blocked |= *set;
	break;

      case SIG_SETMASK:
	ss->blocked = *set;
	break;

      case SIG_UNBLOCK:
	ss->blocked &= ~*set;
	break;

      default:
	err = EINVAL;
	break;
      }

  if (! err && clear_pending)
    __sigemptyset (&ss->pending);

  pending = _hurd_sigstate_pending (ss) & ~ss->blocked;
  _hurd_sigstate_unlock (ss);

  if (! err && pending)
    /* Send a message to the signal thread so it
       will wake up and check for pending signals.  */
    __msg_sig_post (_hurd_msgport, 0, 0, __mach_task_self ());

  return err;
}
