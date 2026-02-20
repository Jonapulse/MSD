/**
 * \file cmdline.h
 */

#ifndef CMDLINE_H
#define CMDLINE_H

/** 
* \brief run_mode_t returned to main to route behavior
*/
enum class run_mode_t{

  do_nothing,
  do_interp,
  do_print,
  do_pretty_print
};

/**
 * \brief Handler for command line arguments
 * \param argc - argcount from main
 * \param argv - argv from main
 */
run_mode_t use_arguments(int argc, char* argv[]);

#endif