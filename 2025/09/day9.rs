use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use std::time::Instant;

const INPUT_PATH: &str = "inputs/9.txt";

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn get_input_coords(path: &str) -> Vec<(i64, i64)> {
    if let Ok(lines) = read_lines(path) {
        let mut output: Vec<(i64, i64)> = vec![];

        for line in lines.flatten() {
            let split = line.split_once(',').expect("Failed to split");
            println!("foo");
            let x = split
                .0
                .parse::<i64>()
                .expect("Failed to parse left hand number");
            let y = split
                .1
                .parse::<i64>()
                .expect("Failed to parse right hand number");

            output.push((x, y));
        }

        return output;
    }
    vec![]
}

fn get_area(x: &(i64, i64), y: &(i64, i64)) -> u64 {
    return (((x.0 - y.0).abs() + 1) * ((x.1 - y.1).abs() + 1)) as u64;
}

fn solve_part_1(input: Vec<(i64, i64)>) -> u64 {
    let mut biggest = 0;
    for coords_a in &input {
        for coords_b in &input {
            let area = get_area(coords_a, coords_b);
            if area > biggest {
                biggest = area;
            }
        }
    }

    biggest
}

fn main() {
    let input = get_input_coords(INPUT_PATH);

    let start_time_part_1 = Instant::now();
    let part_1_result = solve_part_1(input);
    let part_1_calc_time = start_time_part_1.elapsed();

    println!("{part_1_result}");
    println!("Part 1 execution time: {:?}", part_1_calc_time);
}
