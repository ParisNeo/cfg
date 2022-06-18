
/**
 * \file        cfg.h
 * \brief       A small configuration parser library
 * \author      Saifeddine ALOUI
 * \version     0.1
 * \date        10 juin 2022
 *
 * Loads a configuration file that has its configuration in form :
 * key value
 * The configuration file uses # for comments
 *
 */
#ifndef __cfg__
#define __cfg__

#include<stdbool.h>

// Defines -----------------------------------------------
#ifndef MAX_KEY_SIZE
#define MAX_KEY_SIZE 256
#endif
#ifndef MAX_VAL_SIZE
#define MAX_VAL_SIZE 256
#endif

#define MAX_LINE_SIZE MAX_VAL_SIZE+MAX_VAL_SIZE
// Structs -----------------------------------------------


// Prototypes --------------------------------------------
bool cfg_read(char* cfg_file_path, void(*new_entry_callback)(char* key, char* value));
#endif
