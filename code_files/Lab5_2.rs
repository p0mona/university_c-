//Task 2
use rand::Rng;
use std::io;

fn generate_secret_num(limit: u32) -> u32 {
    rand::thread_rng().gen_range(1..=limit)
}

fn main() {
    println!("The computer has guessed a number! Try to guess it by entering ranges or pressing !!! to guess a specific number.");

    println!("Enter the upper bound of the range for the number riddle:");
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input.");

    let limit: u32 = match input.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Please enter a valid number.");
            return;
        }
    };

    let secret_number = generate_secret_num(limit);

    loop {
        println!("Enter the start and end values ​​of the range separated by a space, or enter !!! to try to guess the number:");

        let mut user_input = String::new();
        io::stdin()
            .read_line(&mut user_input)
            .expect("Failed to read input.");

        let user_input = user_input.trim();

        if user_input == "!!!" {
            println!("Enter your guess:");

            let mut guess_input = String::new();
            io::stdin()
                .read_line(&mut guess_input)
                .expect("Failed to read input.");
            let guess: u32 = match guess_input.trim().parse() {
                Ok(num) => num,
                Err(_) => {
                    println!("Please enter a valid number.");
                    continue;
                }
            };

            if guess == secret_number {
                println!("Congratulations! You have guessed the number: {}!", secret_number);
                break;
            } else {
                println!("No, it's not a hidden number. Keep guessing..");
            }

            continue;
        }
        
        let range: Vec<&str> = user_input.split_whitespace().collect();
        if range.len() != 2 {
            println!("Please enter two numbers for the range, for example: 10 20");
            continue;
        }

        let start: u32 = match range[0].parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please enter a valid starting range value..");
                continue;
            }
        };

        let end: u32 = match range[1].parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please enter a valid range end value..");
                continue;
            }
        };

        if start > end {
            println!("The start value of the range must be less than or equal to the end value.");
            continue;
        }

        if secret_number >= start && secret_number <= end {
            println!("Yes, the guessed number is in this range.");
        } else {
            println!("No, the number you are guessing does not fall within this range.");
        }
    }
}