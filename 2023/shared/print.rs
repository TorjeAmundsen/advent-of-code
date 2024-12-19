const NANO_SECONDS: u32 = 5000000;
const SLEEP: std::time::Duration = std::time::Duration::new(0, NANO_SECONDS);

pub fn grid(grid: &Vec<Vec<u8>>) {
    let mut s = String::with_capacity(grid.len() * grid[0].len());
    for row in 0..grid.len() {
        for col in 0..grid[row].len() {
            let c = if grid[row][col] <= 9 { '.' } else { (grid[row][col] + 48) as char };
            s.push(c);
        }
        s.push('\n');
    }
    println!("{s}");
    std::thread::sleep(SLEEP);
}

// For u8 holding numerics in range 0-9, but as ascii (+48)
pub fn numeric_grid(grid: &Vec<Vec<u8>>) {
    let mut s = String::with_capacity(grid.len() * grid[0].len());
    for row in 0..grid.len() {
        for col in 0..grid[row].len() {
            let c = if grid[row][col] > 9 { '.' } else { (grid[row][col] + 48) as char };
            s.push(c);
        }
        s.push('\n');
    }
    println!("{s}");
    std::thread::sleep(SLEEP);
}
