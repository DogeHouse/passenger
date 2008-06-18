/*
 * OXT - OS eXtensions for boosT
 * Provides important functionality necessary for writing robust server software.
 *
 * Copyright (c) 2008 Phusion
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#if !(defined(NDEBUG) || defined(OXT_DISABLE_BACKTRACES))

#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include "backtrace.hpp"
#include "macros.hpp"

namespace oxt {

static thread_specific_ptr<boost::mutex> backtrace_mutex;
static thread_specific_ptr< list<trace_point *> > current_backtrace;
boost::mutex _thread_registration_mutex;
list<thread_registration *> _registered_threads;

boost::mutex &
_get_backtrace_mutex() {
	boost::mutex *result;
	
	result = backtrace_mutex.get();
	if (OXT_UNLIKELY(result == NULL)) {
		result = new boost::mutex();
		backtrace_mutex.reset(result);
	}
	return *result;
}

list<trace_point *> *
_get_current_backtrace() {
	list<trace_point *> *result;
	
	result = current_backtrace.get();
	if (OXT_UNLIKELY(result == NULL)) {
		result = new list<trace_point *>();
		current_backtrace.reset(result);
	}
	return result;
}

} // namespace oxt

#endif

