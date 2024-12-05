use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/2.txt";
fn main() {
    let mut matrix: Vec<Vec<i8>> = vec![Vec::new(); 1000];
}

fn lines_to_i8_matrix(path: &str, matrix: &Vec<Vec<i8>>) {
    if let Ok(lines) = read_lines(path) {
        for line in lines.flatten() {
            ()
        }
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
