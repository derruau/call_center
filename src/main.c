/* 
========================================== MAIN.C ==========================================
The main file of this program. It stitches together every module and makes them work as a
whole.

The global architecture behind this program is as follows
    1. We parse the argc and argv we get from the user into actually usable data.
       This usable data is in the form of a struct that contains every parameter of the
       simulation.
    
    2. We perform the simulation with the parsed parameter. If you wish to know more
       about how the simulation is done, please refer to sim/simulation.c
       The simulation gives us a SimResult object which we'll use further in the
       program.

    3. We save the calls in the SimResultto a file if we gave it the option.

    4. We print the SimResult's statistics to the screen unless specified by the user.
========================================== MAIN.C ==========================================
*/

#include "argparse/misc.h"
#include "argparse/parser.h"
#include "sim/call.h"
#include "sim/simulation.h"
#include "output/save.h"

#define PROGRAM_NAME "call_center"
#define PROGRAM_VERSION "1.0"

void show_help() {
    printf(
    "Simulation of a call center. (School project)\n"
    "\n"
    "Usage:\n"
    "  - %s [options]\n"
    "  - %s --help\n"
    "  - %s -l 2.6 -d 0s:30m -o 6 --output-file output.txt\n"
    "\n"
    "Options:\n"
    "  -h --help            Show this screen.\n"
    "  -v --version         Show version.\n"
    "  -q --quiet           Doesn't print the stats to the screen\n"
    "  -l --lambda          Lambda parameter of a Poisson Law. [DEFAULT: 0.05]\n"
    "  -s --shift           The call centers shift opening and closing hours in \n"
    "                       duration format (see bellow). [DEFAULT: 6h:18h]\n"
    "  -d --duration        Minimum and Maximum call duration for a client in \n"
    "                       duration format (see bellow). [DEFAULT: 30s:5m]\n"
    "  -n --number-of-days  The number of days in the simulation [default: 1]\n"
    "  -o --operators       Number of operators in the call center. [DEFAULT:]\n"
    "  --queue-size         Sets the call queue size to a specific value. Useful\n"
    "                       when the simulation tells you that there is an overflow.\n"
    "                       [DEFAULT: 1000]\n"
    "  --output-file        Saves the generated calls to a file. If this flag is not\n"
    "                       present, the calls won't be saved anywhere!"
    "  --include-names      You can specify a csv file formatted like this:\n"
    "                       '[SURNAME],[NAME]' on each line to include random names\n"
    "                       from this file as the client's names"
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

//TODO: add the day to the output and format the time.
int main(int argc, char *argv[]) {

    if (argc == 1)  {
        show_help();
        return 0;
    }

    // 1. Argument Parsing
    // Parses the arguments into 'a'. If you wish to see
    // The structure of Arguments, please refer to
    // argparse/types.c
    Arguments *a = parser_create_arguments();
    int arg_parsing_error = parser_parse_args(argc, argv, a);

    if (a->help) {
        show_help();
        return 0;
    }

    if (a->version) {
        show_version();
        return 0;
    }

    // 2. Perform the simulation
    SimResults *results = sim_start_simulation(a);

    // 3. Save the calls if the option was given
    if (a->wants_to_save != 0) save_calls_to_file(a, results);

    // 4. Print the eventual results.
    if (a->quiet == 0) save_print_stats(a, results);

    return 0;

}