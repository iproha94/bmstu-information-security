function exponentiationModulo(a, t, n) {
	let r = 1;

	while (t > 0) {
		if (t % 2) r = (r * a) % n;
		
		a *= a;
		a %= n;
		t >>= 1;
	}

	return r;
}

function getNod(a, b) {
	while (a != 0 && b != 0) {
		if (a >= b)
			a %= b;
		else
			b %= a;
	}

	return a + b;
}

module.exports.exponentiationModulo = exponentiationModulo;
module.exports.getNod = getNod;
 
