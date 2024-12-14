use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/2.txt";
fn main() {
    let matrix = lines_to_i8_matrix(INPUT_PATH);

    let part_1_solution = solve_part_1(&matrix);
    println!("{}", part_1_solution);

    let part_2_solution = solve_part_2(&matrix);
    println!("{}", part_2_solution);
}

fn solve_part_1(matrix: &Vec<Vec<i8>>) -> i32 {
    let mut safe_reports = 0;
    for vec in matrix {
        if is_vector_safe(vec) {
            safe_reports += 1;
        }
    }

    safe_reports
}

fn solve_part_2(matrix: &Vec<Vec<i8>>) -> i32 {
    let mut safe_reports = 0;

    for vec in matrix {
        for i in 0..vec.len() {
            let mut possible_subvector: Vec<i8> = vec![];

            for j in 0..vec.len() {
                if j == i {
                    continue;
                }
                possible_subvector.push(vec[j]);
            }

            if is_vector_safe(&possible_subvector) {
                safe_reports += 1;
                break;
            }
        }
    }

    safe_reports
}

fn is_vector_safe(vec: &Vec<i8>) -> bool {
    let mut last_num = vec[0];
    let initial_direction = (vec[0] - vec[1]) > 0;

    for num in &vec[1..] {
        let direction = (last_num - *num) > 0;
        let value: i8 = last_num - *num;
        let difference = value.abs();

        let is_unsafe = difference == 0 || difference > 3 || direction != initial_direction;

        if is_unsafe {
            return false;
        }

        last_num = *num;
    }

    true
}

fn lines_to_i8_matrix(path: &str) -> Vec<Vec<i8>> {
    if let Ok(lines) = read_lines(path) {
        let mut matrix: Vec<Vec<i8>> = vec![];
        for line in lines.flatten() {
            let mut vec = Vec::new();
            for num in line.split_whitespace() {
                let num: i8 = num
                    .trim()
                    .parse()
                    .expect("Invalid number, something is wrong with the input!");
                vec.push(num);
            }
            matrix.push(vec);
        }
        return matrix;
    }
    vec![vec![]]
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
