# xxhash-node-cmake-js -- git repo
# xxhash32-node-cmake  -- node module

Expose xxhash to node modules. 

This implementation is using xxhash from Stephan Brumme for xxhash32. And, will include xxhash64 in future versions.

[xxhash Stephan Brumme](https://create.stephan-brumme.com/xxhash/)

Larger sized hashes will require sharing buffers with the C++ module. Those will come later depending on schedule. Also, there is some thought to targeting ARM intrinsics.

**<u>The main reason for this version</u>:**

## Use cmake-js to compile xxhash

At copious-world we have been setting up a website on small boxes. Some of these boxes are using Linux distros like DietPi, Ambrian, etc. There is some fuzzy requirement to keep from loading all the popular languages, etc. So, some of the boxes don't have Python or PHP on them or Perl for that matter.

They have the ***build essential*** and **node.js** on them. 

Also, node.js is looking to phase out node-gyp. node-gyp has not been worked on in a numner of years. And, new versions of node.js discuss using cmake-js in the documentation.

With the more recent **cmake** and **node.js** versions, builds go fairly nicely.

This version of this module expects cmake 3.5.1 or later. It has flags for C++17 turned on.

* **Example**: On one device I have cmake 3.18.4, and node v18.1.0.

In the package.json file, the following scripts are called out:

```
  "scripts": {
    "preinstall": "bash util/help-install.sh",
    "install": "cmake-js compile",
    "test": "node test/index.js"
  }
```

## Install
```
npm install xxhash32-node-cmake --save
```


## Usage

The application program imports the class definition and then makes an instance that is tied to a particular seed. The seed remains tied to the instance of **XXHash32**. (To use another seed create another instance of **XXHash32**.)

Here is code from the test:

```
const {XXHash32} = require('xxhash32-node-cmake')  // First load the class


let hasher = new XXHash32(9347597)  // make a hash engine with a particular seed

let hash = hasher.hash("this is some test data")
console.log(hash)



hasher.init_running_hash()  // start hashing incoming data

hasher.update("this is some data 1") // first chunk
hasher.update("this is some data 2") // second chunk
hasher.update("this is some data 3") // third chunk

let hash2 = hasher.get_hash()
console.log(hash2)


hasher.update("this is some data 4")

let hash3 = hasher.get_hash()
console.log(hash3)

hasher.reset()		// start over

hasher.update("this is some data 1")
let hash4 = hasher.get_hash()
console.log(hash4)

hasher.remove()
let hash5 = hasher.get_hash()
console.log(hash5)      // should be false

```

Note that the module exports a symbol for each version of the hash. For now, just **XXHash32** is available. But, that may change; so, get the class definition this way:

```
const {XXHash32} = require('xxhash32-node-cmake') 
```

Construct a class object. The seed is the parameter. More than one class object can be made. The are separated by callling **init\_running\_hash()**. But, init\_running\_hash() does not have to be called. It is possible to just call the short form **hash()** method.

```
let hasher = new XXHash32(9347597)
let hash = hasher.hash("this is some test data")
console.log(hash)
```

The same hasher can be used with the running hash. And, the hash method can be called inpendently many times. The two call sequences use different objects internally.

The running hasher exists so that a program can add data as it comes in. Then it can get a hash of the data at any time after it has gotten data.

```
hasher.init_running_hash()   // USE THE SAME SEED

hasher.update("this is some data 1")
hasher.update("this is some data 2")
hasher.update("this is some data 3")

let hash2 = hasher.get_hash()
console.log(hash2)

```

The hasher may be reset. A new internal object will be created with the same seed and previous data will be thrown out.

The hasher may be removed. The class instance will then sieze to function, returning false for operations. The application may want to delete the class instance after calling remove.

```

hasher.reset()		// RESET ... old data is thrown out

hasher.update("this is some data 1")   // new data
let hash4 = hasher.get_hash()
console.log(hash4)

hasher.remove()						// clear out objects
let hash5 = hasher.get_hash()
console.log(hash5)      // should be false

```


## Associated modules

The first place this will be used will be in shm-lru-cache. 

```
npm install shm-lru-cache
```

And, that will in turn be used in global_sessions, a set of processes that attmpt to scale, grow and shrink, for changes in session traffic.

```
npm install -g global_session
```


