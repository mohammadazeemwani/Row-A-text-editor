# Row - a text editor

## Video Demo:  <URL HERE>

## Description:

Row is a text or code editor that supports editing any text file. It currently supports syntax highlighting for C and Python.
It has all the basic text editing you would require such as line numbers, find, selection, highlighting, saving, reading files, etc.

This is my first experience building a app in 100% C.
I wanted to learn how to build an app from the ground up and realized there are always API's to talk to even at terminal level.

It currently only supports Windows but I might make it portable in future.

I tested it mostly on my own so there it might be some bugs and I also showed it to some of my friends.

## Development Process

I started with https://viewsourcecode.org/snaptoken/kilo/index.html, adapted it to Windows as I went along, then completed some of the tasks and implemented some of my own.

I followed https://www.conventionalcommits.org/en/v1.0.0/ for all my commits.

Row was developed using Visual Studio 2022 with the C make profile.

This project is built in C uses some of standard library along with some Windows specific API for keyboard handling and terminal handling.

## Source Files

`text_editor.c` - The main loop and handles setting up the terminal for the text editor and displaying a welcome message.

`terminal.c` - Contains the implementation of setting the terminal in raw mode, resetting it back, handling keys, grabbing the window size and last resort error handling.
This is very Windows specific.

`output.c` - Draws each row, refreshs the screen, scroll logic, status messages, message bar and help bar. Interacting with various terminal colour setting and other modes.

`input.c` - All keyboard handling such as moving the cursor, CTRL keys, etc and handles prompts such as for the save screen.

`row.c` - Contains all the row operations such as tabs, inserting, deleting, merging, inserting and removing chars in current row, marking as dirty

`file.c` - Contains the implementation for the all the file operations such as opening and (CTRL-S)saving a file. Also converting rows to a single string buffer for saving.

`find.c` - Implements CTRL-F, the search feature.

`syntax_highlighting.c` - Contains the implementation for syntax engine.

`init.c` - Initializes all variables that are in the editor and also takes care of adjusting the screen rows for the message bar, help bar and status bar.

`editor_operations.c` - Handles various editor operations such as inserting chars, deleting chars and inserting new lines.

`append_buffer.c` - This one is for passing commands to the terminal.

`file_types.h` - This contains definitions of which words to highlight using syntax highlighting.

`data.h` - This contains various variables that need to tracked for the operations in the text editors;

`text_editor.h` - This contains some config and key definitions.

## Design Choices

- I initially had help as part of status bar just like original kilo but then I decided after seeing some of my friends just forgot about it after typing while using that help should always be present so I moved it to top.
Current line is highlighed by having the current line number with inverted colours.

- I initially was going to develop it in one single file just like the original kilo editor but then I decided to split it up it different files and later also into different headers.
- I was ignoring the malloc, realloc issues error, but later decided to handle them using my die function for robustness.
## Future Plans
- I might implement CTRL-E which will provide AI explanations for selected text.