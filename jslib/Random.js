var randFromZeroToMax = function(max) { 
	return Math.floor(Math.random() * max); 
};

var randFromMinToMax = function(max, min) { 
	return Math.floor(Math.random() * (max - min)) + min ; 
};


module.exports.randFromZeroToMax = randFromZeroToMax;
module.exports.randFromMinToMax = randFromMinToMax;

