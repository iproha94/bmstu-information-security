var Random = require('./Random'); 
var MyMath = require('./MyMath'); 


function testRabinMiller(n) {
	if (n < 3 || n % 2 == 0) return false;

	let s = 0;
	let t = n - 1;
	while (t % 2 == 0) {
		++s;
		t /= 2;
	}

	let k = Math.log2(n);

	while (k > 0) {
		--k;
		
		let a = Random.randFromMinToMax(2, n - 1);
		let x = MyMath.exponentiationModulo(a, t, n);

		if (x != 1 && x != n - 1) {
			let i = s - 1;
			while (i > 0) {
				--i;
				x = MyMath.exponentiationModulo(x, 2, n);

				if (x == 1) return false;

				if (x == n - 1) break;
			}	

			if (x != n - 1) return false;			
		}
	}

	return true;
}

function getPrimeNumber(min, max) {
	let prime = Random.randFromMinToMax(min, max);

	while (!testRabinMiller(prime)) {
		prime = Random.randFromMinToMax(min, max);
	}

	return prime;
} 

 
module.exports.getPrimeNumber = getPrimeNumber;
module.exports.testRabinMiller = testRabinMiller;
