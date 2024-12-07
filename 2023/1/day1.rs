use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/1.txt";

fn main() {
    let input = lines_to_string_vec(INPUT_PATH);
    let part_1_solution = solve_part_1(&input);

    println!("{part_1_solution}");
}

fn solve_part_1(vec: &Vec<String>) -> u32 {
    let mut output = 0;
    for string in vec {
        output += part1_line_number(string) as u32;
    }

    output
}

fn part1_line_number(string: &String) -> u8 {
    let mut left_num: u8 = 0;
    let mut right_num: u8 = 0;

    for c in string.as_bytes() {
        if c.is_ascii_digit() {
            left_num = c - 48;
            break;
        }
    }

    let reversed = string.chars().rev().collect::<String>();
    for c in reversed.as_bytes() {
        if c.is_ascii_digit() {
            right_num = *c - 48;
            break;
        }
    }

    (left_num * 10) + right_num
}

fn lines_to_string_vec(path: &str) -> Vec<String> {
    if let Ok(lines) = read_lines(path) {
        let mut vec: Vec<String> = vec![];

        for line in lines.flatten() {
            vec.push(line);
        }

        return vec;
    }

    vec![]
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
