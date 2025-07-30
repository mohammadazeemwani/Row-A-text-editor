# CMakeList.txt : CMake project for Text_Editor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("text_editor")

# Add source to this project's executable.
add_executable (text_editor "main/text_editor.c" "main/text_editor.h" "main/terminal.c" "main/output.c" "main/data.h" "main/init.c" "main/append_buffer.c" "main/append_buffer.h" "main/input.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET text_editor PROPERTY C_STANDARD 23)
endif()
