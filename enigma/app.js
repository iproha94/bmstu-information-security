var fs = require('fs');
var enigma = require('./enigma'); 

var maxLengthFile = 100;
var nameSourceFile = 'data/source_file.txt';
var nameCipherFile = "data/cipher_file.txt";
var namePlainFile = "data/plain_file.txt";

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

    	var ciphertext = enigma.enciphering(buffer);
    	buffer = arrToBuffer(ciphertext, num);
        
        fs.writeFile(nameCipherFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-ciphertext was saved!");
        }); 

        var plaintext = enigma.deciphering(ciphertext)
    	buffer = arrToBuffer(plaintext, num);

        fs.writeFile(namePlainFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-plain was saved!");
        }); 


    });
});
