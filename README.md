# ft_ls

My own implementation of the famous Unix command: ls, using the C programming language.

### Requirements
To be able to build and run this program you'll need a macbook, because I didn't make it portable for other systems. Sorry :(. As for software Requirements, you'll need:
- GNU make
- GCC

No specific versions, just update them to the latest version if you still can't build the program.

### Building the program

1. Download/Clone the source code
2. `cd` into the root directory
3. Run `make`

### Running the program

It's pretty simple, instead of calling `ls`, call `./ft_ls` from the root directory of the source code after building it.

#### Supported flags

- Long listing display: -l
- Display recursively: -R
- Display all files: -a
- Reverse sort: -r
- Sort by modification date: -t
- Display user ID and group ID: -n

### Preview
<img width="633" alt="Screenshot 2020-03-07 at 15 31 15" src="https://user-images.githubusercontent.com/44320468/76143451-a21f4b00-6088-11ea-8ede-aa9f891b1344.png">
