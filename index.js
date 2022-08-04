'use strict';
const xxhash = require('./build/Release/xxhash-node-cmake.node');



/// --- XXHash32
class XXHash32 {
    //
    constructor() {
    }

    update(data) {}

    digest() {}  // returns ref to digets with readUInt32BE(0)

    reset() {}
    //
}



/// --- XXHash64
class XXHash64 {
    //
    constructor() {
    }

    update(data) {}

    digest() {}  // returns ref to digets with readUInt32BE(0)

    reset() {}
    //
}


module.exports.XXHash32 = XXHash32
module.exports.XXHash64 = XXHash64


