use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/1.txt";

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn get_rotation_values(path: &str) -> Vec<i16> {
    if let Ok(lines) = read_lines(path) {
        let mut output: Vec<i16> = vec![];
        for line in lines.flatten() {
            let split = line.split_at(1);
            let parsed = split.1.parse::<i16>().expect("Failed to parse int");
            if split.0 == "R" {
                output.push(parsed);
            } else {
                output.push(parsed * -1);
            }
        }
        return output;
    } else {
        vec![]
    }
}

fn rotate(from: i16, rotate_by: i16) -> i16 {
    let result = from + (rotate_by % 100);
    if result < 0 {
        return (result + 100) % 100;
    } else {
        return result % 100;
    }
}

fn solve_part_2(input: Vec<i16>) -> u32 {
    let mut wheel: i16 = 50;
    let mut ans: u32 = 0;

    for instruction in input {
        let additional_passes = instruction / 100;
        ans += additional_passes.abs() as u32;
        let rotated = rotate(wheel, instruction);

        if wheel != 0 && rotated != 0 {
            if rotated > wheel && instruction < 0 {
                ans += 1;
            } else if rotated < wheel && instruction > 0 {
                ans += 1;
            }
        } else if rotated == 0 {
            ans += 1;
        }

        wheel = rotated;
    }

    ans
}

fn main() {
    let input = get_rotation_values(INPUT_PATH);
    let part_1_ans = solve_part_2(input);

    println!("{part_1_ans}")
}
