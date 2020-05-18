enum Token {
	else_tk,
	if_tk,
	var_tk(String),
	int_tk(i32),
}

fn tokenize(input: &str) -> Vec<Token> {
	let mut pos = 0;
	tokenize_int(input, pos);
	vec!()
}

fn tokenize_else(input: &str, mut pos: i32) -> Option<Token> {
	let digits: String;

	None
}

fn tokenize_if(input: &str, mut pos: i32) -> Option<Token> {
	let digits: String;

	None
}

fn tokenize_var(input: &str, mut pos: i32) -> Option<Token> {
	let digits: String;

	None
}

fn tokenize_int(input: &str, mut pos: i32) -> Option<Token> {
	let digits: String;

	None
}

fn main() {
	let tokens = tokenize("hello world");
}
