var fs = require('fs');
var rsa = require('./rsa');
var config = require('./app-config');

function arrToBuffer(arr, num) {
	var buffer = new Buffer(num);
	for (var i = 0; i < num; ++i) {
		buffer[i] = arr[i];
	}

	return buffer;
}

function bufferTwoByteToOneByte(arr, num) {
    var buffer = new Buffer(2 * num);
    for (var i = 0; i < 2 * num; i+=2) {
        buffer[i] = arr[i] && 0xFF;
        buffer[i + 1] = (arr[i] && 0xFF00) >> 8;
    }

    return buffer;
}

fs.open(config.nameSourceFile, 'r', function(status, fd) {
    if (status) {
        console.log(status.message);
        return;
    }

    var buffer = new Buffer(config.maxLengthFile);
    fs.read(fd, buffer, 0, config.maxLengthFile, 0, function(err, num) {
    	let key = rsa.getKey();
    	console.log(key);

    	var cipherFile = rsa.translate(buffer, key.public);

        //пишем в файл (он станет больше)
        buffer = bufferTwoByteToOneByte(cipherFile, num);
        fs.writeFile(config.nameCipherFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-ciphertext was saved!");
        }); 

        var plainFile = rsa.translate(cipherFile, key.private)
    	buffer = arrToBuffer(plainFile, num);

        fs.writeFile(config.namePlainFile, buffer, function(err) {
            if(err) {
                return console.log(err);
            }

            console.log("The file-plain was saved!");
        }); 
    });
});
