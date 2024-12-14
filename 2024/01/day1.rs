use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/1.txt";

fn main() {
    let mut left_vec: Vec<i32> = Vec::new();
    let mut right_vec: Vec<i32> = Vec::new();

    lines_to_i32_vectors(INPUT_PATH, &mut left_vec, &mut right_vec);

    let left_vec = merge_sort(&mut left_vec);
    let right_vec = merge_sort(&mut right_vec);

    let part_1_solution = solve_part_1(&left_vec, &right_vec);
    println!("{}", part_1_solution);

    let part_2_solution = solve_part_2(&left_vec, &right_vec);
    println!("{}", part_2_solution);
}

fn solve_part_1(left_vec: &Vec<i32>, right_vec: &Vec<i32>) -> i32 {
    let mut total_distance: i32 = 0;
    for i in 0..left_vec.len() {
        total_distance += (left_vec[i] - right_vec[i]).abs();
    }

    total_distance
}

fn solve_part_2(left_vec: &Vec<i32>, right_vec: &Vec<i32>) -> i32 {
    let mut similartity_score = 0;

    let mut map: HashMap<i32, i32> = HashMap::new();

    for i in 0..right_vec.len() {
        let count = map.entry(right_vec[i]).or_insert(0);
        *count += 1;
    }

    for i in 0..left_vec.len() {
        let mut count: i32 = 0;
        match map.get(&left_vec[i]) {
            Some(num) => count = *num,
            None => (),
        }
        similartity_score += left_vec[i] * count;
    }

    similartity_score
}

fn merge_sort(vec: &Vec<i32>) -> Vec<i32> {
    if vec.len() < 2 {
        return vec.to_vec();
    }

    let middle = vec.len() / 2;

    let left_vec = merge_sort(&vec[..middle].to_vec());
    let right_vec = merge_sort(&vec[middle..].to_vec());

    merge(&left_vec, &right_vec)
}

fn merge(left_vec: &Vec<i32>, right_vec: &Vec<i32>) -> Vec<i32> {
    let mut i: usize = 0;
    let mut j: usize = 0;
    let mut merged_vec: Vec<i32> = Vec::new();

    while i < left_vec.len() && j < right_vec.len() {
        if left_vec[i] < right_vec[j] {
            merged_vec.push(left_vec[i]);
            i += 1;
        } else {
            merged_vec.push(right_vec[j]);
            j += 1;
        }
    }

    if i < left_vec.len() {
        while i < left_vec.len() {
            merged_vec.push(left_vec[i]);
            i += 1;
        }
    }

    if j < right_vec.len() {
        while j < right_vec.len() {
            merged_vec.push(right_vec[j]);
            j += 1;
        }
    }

    merged_vec
}

fn lines_to_i32_vectors(path: &str, left_vec: &mut Vec<i32>, right_vec: &mut Vec<i32>) {
    if let Ok(lines) = read_lines(path) {
        for line in lines.flatten() {
            let left_num = &line[0..5];
            let right_num = &line[8..13];

            let left_num: i32 = left_num.parse().expect("Invalid number");
            let right_num: i32 = right_num.parse().expect("Invalid number");

            left_vec.push(left_num);
            right_vec.push(right_num);
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
