# *Row* - a text editor

## Video Demo:  <URL HERE>

## Description:

***Row*** is a text editor which comes with all the basic functionalies one would require, such as:
- <ins>Reading files</ins>
- <ins>Showing *line-numbers*</ins>
- <ins>Text search</ins> *with navigation support between multiple instances*
- <ins>Text selection</ins>
- <ins>Syntax highlighting</ins> *currently for C and Python code files*
- <ins>Saving file</ins> `Ctrl`+`S`
- <ins>Extention detection</ins> *of saved files*

This has been my first experience, building an app; 100% in C.

My main objective was to build an app from *ground up* and along the way I realized; there are always API's to talk to, even at terminal level.

It currently only has support for **Windows**; for which you can find executables in the [releases section](https://github.com/Amaan-E/text_editor/releases).  
Support for additional platforms will be added in future releases. So stay tuned.

I tested it mostly on my own, so it still might have some bugs.  
Plus I shared it with some of my friends too.

## Development Process

I started with this guide: https://viewsourcecode.org/snaptoken/kilo/index.html.  
As I went along, I completed some of the tasks while adapting it for *Windows* and implemented some of my own.

I made use of the following specification for commits: https://www.conventionalcommits.org/en/v1.0.0/

***Row*** was developed using *Visual Studio 2022* with the *C make profile*.

This project is built in **C** and makes use of ***standard library*** along with APIs specific for *Windows* (which includes handling of keyboard and terminal).

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

- The *help-section* was initially the part of *status-bar* just like in the [kilo](https://viewsourcecode.org/snaptoken/kilo/index.html) (*guide I was following*), where *help-section* disappeared as soon as someone begins to write. My friends, after using it for the very first time, complained about the same to be a UserExperience flaw; which I addressed by moving the *help-section* altogether to the top of the interface (*where it now persists*).

- Indication of *Current-line* is done by highlighting the line number at left-most of each row. Inverted colors are used to provide a nice visual distinction.

- Source code is in accordance with ***separation of concerns*** which I did as oppose to bloating source in a single file.

- I was ignoring the malloc, realloc issues error, but later decided to handle them using my die function for robustness.

## Future Plans
- To provide AI explanation of selected text • Using `CTRL`+`E`
- To provide shortcut for "Save and Exit" scenario.
