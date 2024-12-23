//Task 1
use rand::Rng;
use std::cmp::Ordering;
use std::io;


fn generate_secret_num(limit: u32) -> u32 {
    return rand::thread_rng().gen_range(1..= limit);
}

fn get_user_guess() -> u32 {
    let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
    
    match guess.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Please enter a valid number.");
            get_user_guess()
        }
    }
}


fn compare_numbers(guess: u32, secret_number: i32) -> Ordering {
    guess.cmp(&(secret_number as u32))
    
}

fn main() {
    println!("Guess the number!");
    println!("Enter the upper limit of numbers:");
    
    let mut input = String::new();
    
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read your limit.");
        
        
    let limit: u32 = match input.trim().parse() {
        Ok(limit) => limit,
        Err(_) => {
            println!("Please enter a valid number.");
            return; 
        }
    };
    
    let secret_number = generate_secret_num(limit);

    

    loop {
        println!("Please input your guess.");

        

        let guess = get_user_guess();

        println!("You guessed: {guess}");

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}