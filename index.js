'use strict';
const xxhash = require('./build/Release/xxhash-node-cmake.node');


// For 32 bit hashes, we can have one module that passes parameters using Nan.
// For larger data types, we can set up buffers. Another module can be used for the larger values.
// So, this will skip 64 bit hashes. For instance xxhash3 might be a better target with ARM support.

class CommonHash {
    constructor(seed) {
        if ( typeof seed !== "Number" ) {
            this.seed = parseInt(seed)
        } else {
            this.seed = seed
        }
    }
}


/// --- XXHash32
class XXHash32 extends CommonHash {
    //
    constructor(seed) {
       super(seed)
    }

    hash(data) {
        if ( typeof data !== "string" ) {
            if ( typeof data === 'object' ) {
                data = JSON.stringify(data)
            } else {
                data = data.toString()
            }
        }
        let seed = this.seed
        return xxhash.hash_once_32(data,seed)
    }

    init_running_hash() {
        this.index = xxhash.init(this.seed)
    }

    update(data) {
        if ( typeof data !== "string" ) {
            if ( typeof data === 'object' ) {
                data = JSON.stringify(data)
            } else {
                data = data.toString()
            }
        }
        xxhash.update(this.index,data)
    }

    get_hash() {
        return xxhash.get_hash(this.index)
    }

    reset() {
        if ( xxhash.reset(this.index,this.seed) ) {   // the seed goes back in to do initialization...
            return true
        } else {
            this.index = 0;
            return false
        }
    }
    //
    remove() {
        return xxhash.remove(this.index)
    }
}



module.exports.XXHash32 = XXHash32



