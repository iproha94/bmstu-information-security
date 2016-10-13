var fs = require('fs');
var rsa = require('./rsa');

var maxLengthFile = 1000;
var nameSourceFile = '../data/source_file';
var nameCipherFile = "../data/cipher_file";
var namePlainFile = "../data/plain_file";

function arrToBuffer(arr, num) {
	var buffer = new Buffer(num);
	for (var i = 0; i < num; ++i) {
		buffer[i] = arr[i];
	}

	return buffer;
}

fs.open(nameSourceFile, 'r', function(status, fd) {
    if (status) {
        console.log(status.message);
        return;
    }

    var buffer = new Buffer(maxLengthFile);
    fs.read(fd, buffer, 0, maxLengthFile, 0, function(err, num) {

    	let key = rsa.getKey();
    	console.log(key);

    	var cipherFile = rsa.translate(buffer, key.public);
    	buffer = arrToBuffer(cipherFile, num);
        
        fs.writeFile(nameCipherFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-ciphertext was saved!");
        }); 

        var plainFile = rsa.translate(cipherFile, key.private)
    	buffer = arrToBuffer(plainFile, num);

        fs.writeFile(namePlainFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-plain was saved!");
        }); 
    });
});
