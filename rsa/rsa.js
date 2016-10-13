var random = require('../jslib/random'); 

function getPrimeNumber() {
	let arr = [23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131];

	let i = random.randFromZeroToMax(arr.length);
	return arr[i];
} 

function getE(fi) {
	let num = 17;

	if (num < fi) return num;
} 

function getD(a, b, n) {
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

function normD(d, n, fi) {
	let kMax = Math.floor((n - d) / fi);
	let kMin = Math.floor((fi - d) / fi);

	return d + random.randFromMinToMax(kMax, kMin) * fi;
}


function getKey() {
	let p = getPrimeNumber();
	let q = getPrimeNumber();

	// console.log("p =", p);
	// console.log("q =", q);

	let n = p * q;
	let fi = (p - 1) * (q - 1);

	// console.log("n =", n);
	// console.log("fi =", fi);

	let e = getE(fi);
	let d = getD(e, fi);
	d = normD(d, n, fi);

	// console.log("e =", e);
	// console.log("d =", d);

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
	let r = 1;
	let k = key.k;
	let n = key.n;

	while (k > 0) {
		if (k % 2) r = (r * m) % n;
		
		m *= m;
		m %= n;
		k >>= 1;
	}

	return r;
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