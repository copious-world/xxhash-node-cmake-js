#include "node_xxhash_mod.h"

//-------------------------------

#include <map>

using namespace Nan;
using namespace std;

//-------------------------------


static void AtNodeExit(void*) {
	// maybe destroy tables
}


namespace node {
namespace node_xxhash {

	map<uint32_t,XXHash32 *> g_XXHASH_states;
	uint32_t g_hash_count = 0;

	NAN_METHOD(init) {
		Nan::HandleScope scope;
		int err;
		uint32_t seed = Nan::To<uint32_t>(info[0]).FromJust();
		g_hash_count++;
		g_XXHASH_states[g_hash_count] = new XXHash32(seed);
		//
		info.GetReturnValue().Set(Nan::New<Number>(g_hash_count));
	}

	NAN_METHOD(update) {
		Nan::HandleScope scope;
		uint32_t key = Nan::To<uint32_t>(info[0]).FromJust();
		//
		XXHash32 *xxhash = g_XXHASH_states[key];
		if ( xxhash ) {
			//
			v8::Isolate* isolate = info.GetIsolate();
			v8::String::Utf8Value str(isolate, info[1]);
			std::string s(*str);
			//
			bool rslt = xxhash->add(s.c_str(),s.size());
			info.GetReturnValue().Set(Nan::New<Boolean>(rslt));
		} else {
			info.GetReturnValue().Set(Nan::New<Boolean>(false));
		}
	}

	NAN_METHOD(get_hash) {
		Nan::HandleScope scope;
		uint32_t key = Nan::To<uint32_t>(info[0]).FromJust();
		//
		XXHash32 *xxhash = g_XXHASH_states[key];
		if ( xxhash ) {
			uint32_t hash_val = xxhash->hash();
			info.GetReturnValue().Set(Nan::New<Number>(hash_val));
		} else {
			info.GetReturnValue().Set(Nan::New<Boolean>(false));
		}
	}

	NAN_METHOD(reset) {
		Nan::HandleScope scope;
		uint32_t key = Nan::To<uint32_t>(info[0]).FromJust();
		//
		XXHash32 *xxhash = g_XXHASH_states[key];
		if ( xxhash ) {
			uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
			g_XXHASH_states[key] = new XXHash32(seed);
			delete xxhash;
			info.GetReturnValue().Set(Nan::New<Boolean>(true));
		} else {
			info.GetReturnValue().Set(Nan::New<Boolean>(false));
		}
	}

	NAN_METHOD(remove) {
		Nan::HandleScope scope;
		uint32_t key = Nan::To<uint32_t>(info[0]).FromJust();
		//
		XXHash32 *xxhash = g_XXHASH_states[key];
		if ( xxhash ) {
			delete xxhash;
			g_XXHASH_states[key] = NULL;
			delete g_XXHASH_states[key];
			info.GetReturnValue().Set(Nan::New<Boolean>(true));
		} else {
			info.GetReturnValue().Set(Nan::New<Boolean>(false));
		}
	}


	NAN_METHOD(hash_once_32) {
		Nan::HandleScope scope;
		//
		v8::Isolate* isolate = info.GetIsolate();
		v8::String::Utf8Value str(isolate, info[0]);
		std::string s(*str);

		uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
		//
		uint32_t hash = XXHash32::hash(s.c_str(),s.size(),seed);
		//
		info.GetReturnValue().Set(Nan::New<Number>(hash));
	}


	// Init module
	static void Init(Local<Object> target) {
		//
		Nan::SetMethod(target, "init", init);
		Nan::SetMethod(target, "update", update);
		Nan::SetMethod(target, "get_hash", get_hash);
		Nan::SetMethod(target, "reset", reset);
		Nan::SetMethod(target, "remove", remove);
		//
		Nan::SetMethod(target, "hash_once_32", hash_once_32);
		//
		Isolate* isolate = target->GetIsolate();
		AddEnvironmentCleanupHook(isolate,AtNodeExit,nullptr);
		//node::AtExit(AtNodeExit);
	}

}
}

//-------------------------------

NODE_MODULE(xxhash, node::node_xxhash::Init);
