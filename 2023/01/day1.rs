use twenty23::input;

use std::collections::HashMap;

const INPUT_PATH: &str = "inputs/1.txt";

const DIGIT_STRINGS: [&str; 9] = [
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
];

fn main() {
    let s = input::as_string(INPUT_PATH).unwrap();

    println!("{}", solve_part_1(&s));
    println!("{}", solve_part_2(&s));
}

fn solve_part_1(input: &str) -> u32 {
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

        sum += 10 * left_num.unwrap() as u32 + right_num.unwrap() as u32;
    }

    sum
}

fn solve_part_2(input: &str) -> u32 {
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

    10 * first_digit + last_digit
}
