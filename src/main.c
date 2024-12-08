#include "argparse/misc.h"
#include "argparse/parser.h"
#include "sim/call.h"
#include "sim/simulation.h"

#define PROGRAM_NAME "call_center"
#define PROGRAM_VERSION "1.0"

void show_help() {
    printf(
    "Simulation of a call center. (School project)\n"
    "\n"
    "Usage:\n"
    "  - %s [options] <output-path>\n"
    "  - %s --help\n"
    "  - %s -l 2.6 -d 0s:30m -o 6 output.txt\n"
    "\n"
    "Options:\n"
    "  -h --help            Show this screen.\n"
    "  -v --version         Show version.\n"
    "  -q --quiet           Doesn't print anything to the screen\n"
    "  -l --lambda          Lambda parameter of a Poisson Law. [default: TODO]\n"
    "  -s --shift           The call centers shift opening and closing hours in \n"
    "                       duration format (see bellow).\n"
    "  -d --duration        Minimum and Maximum call duration for a client in \n"
    "                       duration format (see bellow).\n"
    "  -n --number-of-days  The number of days in the simulation [default: 1]\n"
    "  -o --operators       Number of operators in the call center.\n"
    "\n"
    "Duration Format:\n"
    "  The duration format encodes a start and end time like so:\n"
    "                [START_TIME]:[END_TIME]\n"
    "  Each TIME parameter is written like so: [NUMBER][UNIT]\n"
    "  Where:\n"
    "    - NUMBER is a whole number\n"
    "    - UNIT is a unit of time (s: seconds, m: minutes, h:hours, d: days,\n"
    "     w: week, M: month, y: year)\n"
    "  Example: The Duration Format 2s:4d means that the minimum duration is 2\n"
    "           seconds and the maximum duration is 4 days.\n",
    PROGRAM_NAME,
    PROGRAM_NAME,
    PROGRAM_NAME
    );
}

void show_version() {
    printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
}

//TODO: free resources at the end of the program's execution
//TODO: add documentation to the code
//TODO: add --output-file option
int main(int argc, char *argv[]) {

    // Parses the arguments into 'a'. If you wish to see
    // The structure of Arguments, please refer to
    // argparse/types.c
    Arguments *a = parser_create_arguments();
    int arg_parsing_error = parser_parse_args(argc, argv, a);

    misc_print_arguments(a);

    if (a->help) {
        show_help();
        return 0;
    }

    if (a->version) {
        show_version();
        return 0;
    }

    // 1. Perform the simulation
    SimResults *results = sim_start_simulation(a);

    printf("yay!!\n");
    // 2. Print the eventual result

    return 0;

}