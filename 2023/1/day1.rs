use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/2.txt";

fn main() {
    let input = "one234five";
    let part_1_solution = solve_part_1(&vec![input]);

    println!("{}", part_1_solution);
}

fn solve_part_1(vec: &Vec<&str>) -> u32 {
    let mut left_num: u8 = 0;
    let mut right_num: u8 = 0;

    for string in vec {
        for c_num in string.as_bytes() {
            if *c_num >= 48 && *c_num <= 57 {
                left_num = *c_num;
            }
        }
    }

    for string in vec.iter().rev() {
        for c_num in string.as_bytes() {
            if *c_num >= 48 && *c_num <= 57 {
                right_num = *c_num;
            }
        }
    }

    <u8 as Into<u32>>::into(right_num) + (<u8 as Into<u32>>::into(left_num) * 10)
}

/* fn lines_to_string_vec(path: &str) -> Vec<&str> {
    if let Ok(lines) = read_lines(path) {
        let mut vec: Vec<&str> = vec![];

        for line in lines.flatten() {
            vec.push(line.as_str());
        }

        return vec;
    }
    vec![]
} */

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
