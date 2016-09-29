use std::fs::File;
use std::io::{Read, Write, SeekFrom,BufReader, Seek, BufRead,BufWriter};

struct Block {
	data : i64,
}

fn initial_permutation(block: &mut Block) {
	let	table_1: [usize; 64] = [
		58,	50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
	];

	block.permutation(&table_1);
}

fn end_permutation(block: &mut Block) {
	let	table_8: [usize; 64] = [
		40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
	];

	block.permutation(&table_8);
}



impl Block {
	

	fn	new(data: i64) -> Block {
		Block {
			data: data,
		}
	}

	fn	print(&self) {
		println!("В этом блоке число {}", self.data);
	}

	fn permutation(&mut self, vec: &[usize]) {
		let	mut b = 0;

		for (i, v) in vec.iter().enumerate() {
			b |= self.permutation_bit(*v, i);
		}

		self.data = b;
	}

	//i_from - с какой позиции взять бит. отсчет от 1
	//i_to - в какую позицию вставить бит. отсчет от 0
	fn permutation_bit(&self, i_from: usize, i_to: usize) -> i64 {
		(self.data >> (i_from - 1) & 1) << i_to
	}

}


fn main() {
	// let a: i64 = 777_778;
	// let	mut b1 = Block::new(a);
	// b1.print();
	// initial_permutation(&mut b1);
	// b1.print();
	// end_permutation(&mut b1);
	// b1.print();

	let fr = File::open("../data/source_file.txt").expect("Unable to open file");
	let mut reader = BufReader::new(fr);

	let fw = File::create("../data/chipher_file.txt").expect("Unable to create file");
	let mut writer = BufWriter::new(&fw);

	for elem in reader.fill_buf() {
		print!("{:?}", elem);
		
		writer.write(elem).unwrap();
	}
}
