use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

const INPUT_PATH: &str = "inputs/2.txt";

struct CubeSet {
    color: char,
    count: u32,
}

fn main() {
    let matrix = lines_to_cubeset_matrix(INPUT_PATH);

    let part_1_solution = solve_part_1(&matrix);

    println!("{part_1_solution}");

    let part_2_solution = solve_part_2(&matrix);

    println!("{part_2_solution}");
}

fn solve_part_1(matrix: &Vec<Vec<CubeSet>>) -> u32 {
    let mut sum_of_ids: u32 = 0;
    let mut id: u32 = 1;
    for game in matrix {
        let mut possible = true;

        for set in game {
            if set.color == 'r' && set.count > 12 {
                possible = false;
                break;
            }
            if set.color == 'g' && set.count > 13 {
                possible = false;
                break;
            }

            if set.color == 'b' && set.count > 14 {
                possible = false;
                break;
            }
        }

        if possible {
            sum_of_ids += id;
        }

        id += 1;
    }

    sum_of_ids
}

fn solve_part_2(matrix: &Vec<Vec<CubeSet>>) -> u32 {
    let mut power_sum = 0;

    for vec in matrix {
        let mut map: HashMap<char, u32> = HashMap::from([('r', 0), ('g', 0), ('b', 0)]);

        for set in vec {
            if let Some(count) = map.get(&set.color) {
                if count < &set.count {
                    map.insert(set.color, set.count);
                }
            }
        }

        power_sum += map.get(&'r').unwrap() * map.get(&'g').unwrap() * map.get(&'b').unwrap();
    }

    power_sum
}

fn lines_to_cubeset_matrix(path: &str) -> Vec<Vec<CubeSet>> {
    if let Ok(lines) = read_lines(path) {
        let mut matrix: Vec<Vec<CubeSet>> = vec![];
        for line in lines.flatten() {
            let mut vec: Vec<CubeSet> = vec![];
            let mut game_string: String = line.chars().filter(|c| !c.is_whitespace()).collect();
            game_string = game_string.as_str()[(game_string.find(":").unwrap() + 1)..].to_string();

            for hand in game_string.split(";") {
                for set in hand.split(",") {
                    let set_count: u32 = set[0..(set.find(|c: char| !c.is_digit(10)).unwrap())]
                        .parse::<u32>()
                        .unwrap();
                    let set_color: char = set[(set.find(|c: char| !c.is_digit(10)).unwrap())..]
                        .chars()
                        .nth(0)
                        .unwrap();

                    let cube_set: CubeSet = CubeSet {
                        count: set_count,
                        color: set_color,
                    };

                    vec.push(cube_set);
                }
            }

            matrix.push(vec);
        }

        return matrix;
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
