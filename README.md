![Build](../../actions/workflows/build.yml/badge.svg)
![Format](../../actions/workflows/format.yml/badge.svg)
![Header](../../actions/workflows/header.yml/badge.svg)
![Lint](../../actions/workflows/lint.yml/badge.svg)
![Unit Tests](../../actions/workflows/unittest.yml/badge.svg)

# Instructions

Write a program for each exercise sub-directory. Each exercise subdirectory is prefixed with the string `part-`. The subdirectory contains a README.md which explains the requirements for the exercise.

Each exercise subdirectory has its own [Makefile](https://en.wikipedia.org/wiki/Makefile) which you may use to build and test your progress. Each Makefile has the following targets:

* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* lint: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* header: check to make sure your files have the appropriate header
* test: run tests to help you verify your program is meeting the assignment's requirements. This does not grade your assignment.
* unittest: run unit tests to verify parts of your program performs according to the instructor supplied unit tests.
* doc: generate the project's documentation from the source files and store it in the directory named `doc`.

To build the program use the `make` command. The Makefile's default target is to build `all`.

Every file that you submit must have a header. Please follow the [guidelines provided for this course](https://docs.google.com/document/d/17WkDlxO92zpb26pYM1NIACPcMWtCOlKO7WCrWC6YxRo/edit?usp=sharing).

Please adhere to the [Google C++ coding style](https://google.github.io/styleguide/cppguide.html).

When writing git log comments, please make them descriptive and meaningful.

# Rubric

Each exercise is worth 5 points. There is a total of 10 points possible. Your program must compile before it is graded. Submissions that do not compile shall be assigned a zero grade.

For each problem:

* Functionality (3 points): Your submission shall be assessed for the appropriate constructs and strategies to address the exercise. A program the passes the instructor's tests completely receives full marks. A program that partially passes the instructors tests receives partial-marks. A program that fails the majority or all the tests receives no marks.

* Format & Readability (2 point): Your submission shall be assessed by checking whether your code passess the style and format check, as well as how well it follows the proper naming conventions, and internal documentation guidelines. Git log messages are an integral part of how readable your project is. Failure to include a header forfeits all marks.
