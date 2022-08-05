#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <nan.h>
#include <errno.h>


#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <assert.h>
#include <signal.h>
#include <pthread.h>


#include <iostream>
#include <sstream>


#ifndef _POSIX_THREAD_PROCESS_SHARED
#warning This system does not support process shared mutex -- alternative method will be used
#endif


using namespace node;
using namespace v8;
using namespace std;

#include "../xxhash/xxhash32.h"
#include "../xxhash/xxhash64.h"

namespace node {
namespace node_xxhash {

	// XXHASH   ----  ----  ----  ----  ----  ----  ----

	/**
	 * init create the hash object and reference it a table.
	 */
	NAN_METHOD(init);

	/**
	 * update take in data 
	 */
	NAN_METHOD(update);

	/**
	 * get_hash return the last hash result according to its type
	 */
	NAN_METHOD(get_hash);

	/**
	 * reset set the state holder object back to initial state
	 */
	NAN_METHOD(reset);

	/**
	 * remove destroy state holder object and clear it from tables
	 */
	NAN_METHOD(remove);

	/**
	 * hash_once_32 or hash_once_64
	 */
	NAN_METHOD(hash_once_32);

}

}
