#![allow(unused)]

use std::collections::HashMap;
use std::collections::HashSet;
use std::fs::{self, File};
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/1.txt";
const LINE_FEED: u8 = 10;

const DIGIT_STRINGS: [&str; 9] = [
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
];

fn main() {
    let s = get_input_string();
    solve_part_1(&s);

    //let input = get_input_vec_u8();
    let part_2_solution = solve_part_2_2(&s);

    println!("{part_2_solution}");
}

fn solve_part_2(input: &str) {
    let map: HashMap<&str, u8> = HashMap::from([
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ]);

    let map_reversed: HashMap<&str, u8> = HashMap::from([
        ("eno", 1),
        ("owt", 2),
        ("eerht", 3),
        ("ruof", 4),
        ("evif", 5),
        ("xis", 6),
        ("neves", 7),
        ("thgie", 8),
        ("enin", 9),
    ]);

    let mut sum: u32 = 0;
    for line in input.lines() {
        let mut left_num: Option<u8> = None;
        let mut right_num: Option<u8> = None;

        let line_bytes = line.as_bytes();

        let mut i = 0;
        'outer: while i < line.len() - 1 {
            if line_bytes[i].is_ascii_digit() {
                left_num = Some(line_bytes[i]);
                break;
            }

            if i < line.len() - 3 {
                for j in i + 3..i + 5 {
                    if let Some(num) = map.get(&line[i..j]) {
                        left_num = Some(*num);
                        break 'outer;
                    }
                }
            }

            i += 1;
        }

        i = line.len() - 1;

        'outer: while i >= line.len() - 1 {
            if line_bytes[i].is_ascii_digit() {
                left_num = Some(line_bytes[i]);
                break;
            }

            if i > 3 {
                for j in 3..5 {
                    if i < j {
                        continue;
                    }
                    let j = i - j;
                    if let Some(num) = map.get(&line[j..i]) {
                        left_num = Some(*num);
                        break 'outer;
                    }
                }
            }

            i -= 1;
        }
    }
}

fn solve_part_2_2(input: &str) -> u32 {
    let map: HashMap<&str, u8> = HashMap::from([
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
    ]);

    let mut output: u32 = 0;

    for line in input.lines() {
        output += part_2_line(line, &map) as u32;
    }

    output
}

fn part_2_line(line: &str, map: &HashMap<&str, u8>) -> u8 {
    let mut first_index: usize = line.len();
    let mut last_index: usize = 0;

    let mut first_digit: u8 = 0;
    let mut last_digit: u8 = 0;

    let bytes = line.as_bytes();

    for i in 0..bytes.len() {
        let current = bytes[i];
        if current.is_ascii_digit() {
            first_digit = current - 48;
            first_index = i;
            break;
        }
    }

    for i in (0..bytes.len()).rev() {
        let current = bytes[i];
        if current.is_ascii_digit() {
            last_digit = current - 48;
            last_index = i;
            break;
        }
    }

    for i in 0..DIGIT_STRINGS.len() {
        if let Some(first_string_index) = line.find(DIGIT_STRINGS[i]) {
            if first_string_index < first_index {
                first_digit = *map.get(DIGIT_STRINGS[i]).unwrap();
                first_index = first_string_index;
            }
        }
        if let Some(last_string_index) = line.rfind(DIGIT_STRINGS[i]) {
            if last_string_index > last_index {
                last_digit = *map.get(DIGIT_STRINGS[i]).unwrap();
                last_index = last_string_index;
            }
        }
    }

    (first_digit * 10) + last_digit
}

fn solve_part_1(input: &str) {
    let mut sum: u32 = 0;
    for line in input.lines() {
        let mut left_num: Option<u8> = None;
        let mut right_num: Option<u8> = None;

        for b in line.chars() {
            if b.is_digit(10) {
                left_num = Some(b as u8 - 48);
                break;
            }
        }

        for c in line.chars().rev() {
            if c.is_digit(10) {
                right_num = Some(c as u8 - 48);
                break;
            }
        }

        match (left_num, right_num) {
            (Some(l), Some(r)) => {
                sum += ((l as u32 * 10) + r as u32);
            }
            _ => panic!(),
        }
    }

    println!("{sum}");
}

fn get_input_string() -> String {
    fs::read_to_string(INPUT_PATH).unwrap()
}

fn get_input_vec_u8() -> Vec<u8> {
    fs::read(INPUT_PATH).unwrap()
}
