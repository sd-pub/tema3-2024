echo "Installing Rust"
curl https://sh.rustup.rs -sSf | sh -s -- -y
source "$HOME/.cargo/env"

echo "Downloading checker"
cargo install hw_checker

echo "Install finished. Good luck!"
