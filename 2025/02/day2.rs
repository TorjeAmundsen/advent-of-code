use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/2.txt";

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn get_ranges(path: &str) -> Vec<(u64, u64)> {
    if let Ok(lines) = read_lines(path) {
        let mut output: Vec<(u64, u64)> = vec![];

        for line in lines.flatten() {
            let split = line.split(',');
            for section in split {
                println!("{section}");
                if let Some(half) = section.split_once('-') {
                    let from = half
                        .0
                        .parse::<u64>()
                        .expect("Failed to parse left hand number");
                    let to = half
                        .1
                        .parse::<u64>()
                        .expect("Failed to parse right hand number");

                    println!("from {from} to {to}");

                    output.push((from, to));
                }
            }
        }
        return output;
    }
    vec![]
}

fn solve_part_1(input: Vec<(u64, u64)>) -> u64 {
    let mut result: u64 = 0;
    for range in input {
        let mut current = range.0;
        while current <= range.1 {
            let digit_count = (current as f64 + 0.1).log10().ceil() as u32;
            if digit_count % 2 == 1 && digit_count > 1 {
                current = 10_u64.pow(digit_count);
                continue;
            }

            let string = current.to_string();

            let halves = string.split_at((digit_count / 2) as usize);

            if halves.0 == halves.1 {
                result += current;
            }

            current += 1;
        }
    }

    result
}

fn main() {
    let ranges = get_ranges(INPUT_PATH);
    let part_1_result = solve_part_1(ranges);

    println!("{part_1_result}");
}
