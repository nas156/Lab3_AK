#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <cstdlib>


int main(int argc, char *argv[]) {

    const char *short_options = "hs::f:vl:";

    const struct option long_options[] = {
            {"help",    no_argument,       NULL, 'h'},
            {"size",    optional_argument, NULL, 's'},
            {"file",    required_argument, NULL, 'f'},
            {"version", no_argument,       NULL, 'v'},
            {"list",    required_argument, NULL, 'l'},
            {NULL, 0,                      NULL, 0}
    };

    const char *arguments_msg = "List of arguments:\n"
                                "-s[size] or --size=[size] - with option to set size, without - get size\n"
                                "-f<filename> or --file=<filename> - set name of file\n"
                                "-h or --help - get help msg\n"
                                "-v or --version - get version of the program\n"
                                "-l[<val1>,...] or --list=[<num1>,...] - input list\n";
    int rez;
    double size = 1.0;
    bool h_level = false, f_level = false, s_level = false, v_level = false, l_level = false;
    int option_index;

    while ((rez = getopt_long(argc, argv, short_options,
                              long_options, &option_index)) != -1) {

        switch (rez) {
            case 'h': {
                if (!h_level) {
                    printf("**\n%s**\n", arguments_msg);
                    h_level = true;
                }
                break;
            }
            case 's': {
                if (!s_level) {
                    if (optarg != NULL) {
                        char *convert;
                        double num = strtod(optarg, &convert);
                        if (num != 0) {
                            size = num;
                            printf("** Size is set to %.2fmb **\n", num);
                        } else {
                            printf("** Size is %.2fmb, because of wrong input **\n", size);
                        }
                    } else {
                        printf("** Size is %.2fmb **\n", size);
                    }
                    s_level = true;
                }
                break;
            }
            case 'f': {
                if (!f_level) {
                    printf("** File with name '%s' **\n", optarg);
                    f_level = true;
                }
                break;
            }
            case 'v': {
                if (!v_level) {
                    printf("** Version: Latest **\n");
                    v_level = true;
                }
                break;
            }
            case 'l': {
                if (!l_level) {
                    printf("** Your list: { ");
                    char *elem = strtok(optarg, ",");
                    while (elem != NULL) {
                        printf("%s ", elem);
                        elem = strtok(NULL, ",");
                    }
                    printf("} **\n");
                    l_level = true;
                }
                break;
            }
            case '?':
            default: {
                printf("Wrong argument syntax. Type -h or --help to see the list of arguments.\n");
                break;
            }
        }
    }
    return 0;
}