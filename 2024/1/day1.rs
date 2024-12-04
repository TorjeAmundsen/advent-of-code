use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {}

fn lines_to_u32_arrays<P>(filename: P)

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
