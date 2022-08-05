


const {XXHash32} = require('../index.js')


let hasher = new XXHash32(9347597)

let hash = hasher.hash("this is some junk data")
console.log(hash)



hasher.init_running_hash()

hasher.update("this is some data 1")
hasher.update("this is some data 2")
hasher.update("this is some data 3")

let hash2 = hasher.get_hash()
console.log(hash2)


hasher.update("this is some data 4")

let hash3 = hasher.get_hash()
console.log(hash3)

hasher.reset()

hasher.update("this is some data 1")
let hash4 = hasher.get_hash()
console.log(hash4)

hasher.remove()
let hash5 = hasher.get_hash()
console.log(hash5)      // should be false


