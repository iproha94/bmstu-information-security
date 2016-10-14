var Random = require('../jslib/Random'); 
var MyMath = require('../jslib/MyMath'); 
var Prime = require('../jslib/Prime'); 
var config = require('./rsa-config'); 

var MIN_FI = config.minFi;
var MIN_PRIME = config.minPrime;
var MAX_PRIME = config.maxPrime;


function getE(fi) {
	let num = Random.randFromMinToMax(MIN_FI, fi);

	while (MyMath.getNod(num, fi) != 1) 
		num = Random.randFromMinToMax(MIN_FI, fi);

	return num;
} 

function getX(a, b) {
	// ax + by = 1
	
	let E = [[1,	0], 
			 [0,	1]];

	let r = a % b;
	while (r != 0) {
		let E2 = [[0,	1], 
				  [1,	-Math.floor(a / b)]];

		let E1 = [[E[0][0], E[0][1]], [E[1][0], E[1][1]]];

		E[0][0] = E1[0][0] * E2[0][0] + E1[0][1] * E2[1][0] ;
		E[0][1] = E1[0][0] * E2[0][1] + E1[0][1] * E2[1][1] ;
		E[1][0] = E1[1][0] * E2[0][0] + E1[1][1] * E2[1][0] ;
		E[1][1] = E1[1][0] * E2[0][1] + E1[1][1] * E2[1][1] ;

		a = b;
		b = r;

		r = a % b;
	}

	return E[0][1];
}

function getD(d, n, fi) {
	let kMax = Math.floor((n - d) / fi);
	let kMin = Math.floor((fi - d) / fi);

	return d + Random.randFromMinToMax(kMax, kMin) * fi;
}


function getKey() {
	let p = Prime.getPrimeNumber(MIN_PRIME, MAX_PRIME);
	let q = Prime.getPrimeNumber(MIN_PRIME, MAX_PRIME);

	let n = p * q;
	let fi = (p - 1) * (q - 1);

	let e = getE(fi);
	let d = getX(e, fi);
	d = getD(d, n, fi);

	return {
		private: {
			k: d,
			n: n
		}, 
		public: {
			k: e,
			n: n
		}
	}
} 


function translateBlock(m, key) {
	return MyMath.exponentiationModulo(m, key.k, key.n);
	
}

function translate(text, key) {
	var newText = [];
	for (let i = 0; i < text.length; ++i) {
		newText.push(translateBlock(text[i], key));
	}

	return newText;
}

module.exports.getKey = getKey;
module.exports.translate = translate;

