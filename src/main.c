#include "../include/helper.h"
#include "../include/args.h"
#include "../include/call.h"

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
    "    - UNIT is a unit of time (s: seconds, m: minutes,, h:hours, d: days,\n"
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

//TODO: add documentation to the code
//TODO: Make the functions have a more consistent style
//TODO: standardize the name of the function's arguments
int main(int argc, char *argv[]) {

    // Parses the arguments into 'a'. If you wish to see
    // The structure of Arguments, please refer to
    // argument_parsing/arg_types.c
    Arguments *a = args_create_arguments();
    int arg_parsing_error = args_handle(argc, argv, a);

    if (a->help) {
        show_help();
        return 0;
    }

    if (a->version) {
        show_version();
        return 0;
    }



    return 0;

}