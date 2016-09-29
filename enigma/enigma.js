var config = require('./config'); 
 
var random = require('../jslib/random'); 

function createRotor() {
	var rotor = {};
	rotor.there = [];

	for (var i = 0; i < config.alphabet; ++i) {
		rotor.there[i] = i;
	}

	for (var i = 0; i < config.alphabet; ++i) {
		var j = random.randFromZeroToMax(config.alphabet);
		var temp = rotor.there[i];
		rotor.there[i] = rotor.there[j];
		rotor.there[j] = temp;
	}

	rotor.back = [];
	var nmbMixing = config.alphabet;
	for (var i = 0; i < nmbMixing; ++i) {
		rotor.back[rotor.there[i]] = i;
	}

	rotor.originalStart = random.randFromZeroToMax(config.alphabet);

	return rotor;
}

var rotors = [];
for (var i = 0; i < config.nmbRotors; ++i) {
	rotors[i] = createRotor();
}  

function createReflector() {
	var reflector = [];

	for (var i = 0; i < config.alphabet; ++i) {
		reflector[i] = i;
	}

	var nmbMixing = config.alphabet;
	for (var i = 0; i < nmbMixing; ++i) {
		var j = random.randFromZeroToMax(config.alphabet);

		if (reflector[j] == j && reflector[i] == i) {
			reflector[j] = i;
			reflector[i] = j;
		} 
	}

	return reflector;
}

var reflector = createReflector();

function run(text) {
	var newtext = [];

	for (var k = 0; k < rotors.length; ++k) {
		rotors[k].start = rotors[k].originalStart;
	}

	for (var i = 0; i < text.length; ++i) {
		var c = text[i];
		var index;

		for (var k = 0; k < rotors.length; ++k) {
			if (!(i % Math.pow(config.alphabet, k))) {
				(++rotors[k].start);
				rotors[k].start %= config.alphabet;
			}
		}

		for (var k = 0, predPos = 0; k < rotors.length; ++k, predPos = rotors[k - 1].start) {
			var rotor = rotors[k];
			
			index = (c + rotor.start - predPos) % config.alphabet;
			if (index < 0) index += config.alphabet;

			c = rotor.there[index];
		}


		index = (c - rotors[rotors.length - 1].start) % config.alphabet;
		if (index < 0) index += config.alphabet;

		c = reflector[index];


		for (var k = rotors.length - 1, nextPos = 0; k >= 0; --k, nextPos = rotors[k + 1].start) {
			var rotor = rotors[k];

			index = (c + rotor.start - nextPos) % config.alphabet;
			if (index < 0) index += config.alphabet;

			c = rotor.back[index];
		}

		index = (c - rotors[0].start) % config.alphabet;
		if (index < 0) index += config.alphabet;
		newtext[i] = index;
	}

	return newtext;
}

function enciphering(text) {
	return run(text);
}

function deciphering(text) {
	return run(text);
}

module.exports.enciphering = enciphering;
module.exports.deciphering = deciphering;
