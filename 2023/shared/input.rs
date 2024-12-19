
pub fn as_string(p: &str) -> std::io::Result<String> {
    std::fs::read_to_string(p)
}

pub fn as_bytes(p: &str) -> std::io::Result<Vec<u8>> {
    std::fs::read(p)
}

pub fn as_grid(p: &str) -> std::io::Result<Vec<Vec<u8>>> {
    let input = std::fs::read(p)?;

    let mut grid: Vec<Vec<u8>> = vec![Vec::new()];
    let mut columns: Option<usize> = None;
    let mut i: usize = 0;
    for b in input {
        if b == b'\n' {
            match columns {
                // First round (length = None), save length of first row.
                None => columns = Some(grid[i].len()),

                // Make sure that every row has equal amount of columns e.g. is a grid.
                Some(v) => assert_eq!(grid[i].len(), v),
            }

            // Add the next vector as an empty one.
            grid.push(Vec::with_capacity(grid[i].len()));
            // ..and move index to the next vector.
            i += 1;
        } else {
            grid[i].push(b);
        }
    }

    assert!(grid.len() > 1);

    Ok(grid)
}
