use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/3.txt";

fn main() {
    let directions: Vec<Vec<isize>> = vec![
        vec![0, -1],  // left
        vec![-1, -1], // up-left
        vec![1, -1],  // down-left
        vec![0, 1],   // right
        vec![-1, 1],  // up-right
        vec![1, 1],   // down-right
        vec![1, 0],   // down
        vec![-1, 0],  // up
    ];

    let parsed_input = parse_input(INPUT_PATH);
}

fn solve_part_1(input_vector: &Vec<String>, directions: &Vec<Vec<i32>>) {
    let mut sum_of_valid_part_numbers: i32 = 0;
}

fn is_oob(row: isize, col: isize, rows: isize, cols: isize) -> bool {
    row >= rows || col >= cols
}

fn is_valid_part(
    directions: &Vec<Vec<isize>>,
    input_vector: &Vec<String>,
    row: isize,
    col: isize,
    len: isize,
) {
    for i in 0..3 {
        let offset_row = row + directions[i][0];
        let offset_col = col + directions[i][1];

        if is_oob(
            offset_row,
            offset_col,
            input_vector.len() as isize,
            input_vector[row as usize].len() as isize,
        ) {
            continue;
        }

        if let Some(character) = input_vector[offset_row as usize].get(offset_col as usize)
    }
}

fn parse_input(path: &str) -> Vec<String> {
    if let Ok(lines) = read_lines(path) {
        let mut vector: Vec<String> = vec![];
        for line in lines.flatten() {
            vector.push(line.to_string());
        }

        return vector;
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
