/**
 * \file        cfg.c
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
#include <cfg.h>

// C library headers
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <fcntl.h>      // Contains file controls like O_RDWR
#include <errno.h>      // Error integer and strerror() function
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()


/**
 * \fn char *trimString(char *str)
 * \brief A helper function to trim strings (remove spaces in both sides)
 *
 * \param str string to trim
 * \return the trimmed string.
 */
char *trimString(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}


/**
 * \fn cfg_read(char* cfg_file_path, void(*new_entry_callback)(char* key, char* value))
 * \brief Reads and parses configuration file
 *
 * \param cfg_file_path      The path to the file to read
 * \param new_entry_callback A function to handle the recovered configuration. For every configuration found by the tool, this function is called with two parameters, the key and the value. This function is expected to  recover the configuration.
 * 
 * \return the trimmed string.
 */
bool cfg_read(char* cfg_file_path, void(*new_entry_callback)(char* key, char* value))
{
    /*
     * Reads a configuration key/value configuration file and store its data to the output
     * */
    FILE * fp;
    char bufr[MAX_LINE_SIZE];
    char key[MAX_VAL_SIZE];
    char val[MAX_VAL_SIZE];
    char *cmd;
    
    if (access(cfg_file_path, F_OK) == 0) {
        // file exists    
        if((fp = fopen(cfg_file_path,"r")) != NULL){
            /* then file opened successfully. */
            while(fgets(bufr,MAX_LINE_SIZE,fp)!=NULL){
                /* then no read error */
                
                if(sscanf(bufr, "%s %s", key, val)==2)
                {
                    cmd = trimString(key);
                    if(strlen(cmd)>0)
                    {
                        if(cmd[0]!='#'){
                            new_entry_callback(cmd, val);
                        }
                    }
                }
            }
            /* fgets returned null */
            if(errno != 0){
                return false;
            }
        } else {                    /* there was an error on open */
            return false;
        }
    } else {
        // file doesn't exist
        return false;
    }
    return true;
}
