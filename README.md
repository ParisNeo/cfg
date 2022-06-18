# cfg
Simple Linux C configuration library to help using simplified configuration files in your projects.

# Build
To build and install the library on your system, just use:
```console
foo@bar:~$ make clean;make; sudo make install
```
You can skip the make install part and copy the .a output file as well as the header file to your project to link it statically with your code
# Usage
Once the library is installed on your system or after adding the header file and the .a file to your project, you can use it like this.

First import the header files
```c
#include<cfg.h>
```
if you are using c++, make sure you add extern "C" protection
```cpp
#ifdef __cplusplus
extern "C"
{
#endif
    // udp library
    #include <cfg.h>
#ifdef __cplusplus
}
#endif
```

Let's define the configuration file path. For example:
```c
// The path of the file to load
const char *cfg_file_path = "/etc/myconfig"

```

The library is very lightweight and is very simple to use. You need to provide a function that parses a single line from your configuration file. Then the library searches through the the file, ignores the comments (comments use # as escape character), then sports key value pairs.
A key value pair is defined by typing the key (no spaces allowed for its key), then space, then the value which can be any thing from string, integer, floating point etc. 

Each key value entry is separated by a space.
For example:
```python
# parameter 1 is a string
parameter1 this is a string
# parameter 2 is an integer
parameter2 100
# parameter 4 is a more complex combination of subparameters sepatated by [:]. For example here is a complex parameter that has two subparameters
parameter3 100:string value
```

Now we define the function to parse these lines. This function is going to be called by the library for each valid line it finds

```c
/**
 * \fn void cfg_parser(char* key, char* val)
 * \brief Parses one entry from the configuration file
 *
 * \param key      The configuration parameter name
 * \param val      The configuration value (as string)
 * 
 * \return nothing.
 */
void cfg_parser(char* key, char* val)
{
    // Simple key value configuration
    // a string parameter   ex : parameter1 some text
    if(strcmp(key,"parameter1")==0)
    {
        strcpy(parameter1,val); // Copy the parameter value to the variable
    }
    // an integer parameter ex : parameter2 100
    else if (strcmp(key,"parameter2")==0)
    {
        parameter2 = atoi(val); // Convert the value to an integer
    }
    else if(strcmp(key,"parameter3")==0) // A more complex parameter for example parameter3 100:hello
    {
        char subparam1[UDP_MAXADDR_SIZE];
        char subparam2[UDP_MAXPORT_SIZE];
        
        if(sscanf(val,"%[^:]:%s", subparam1, subparam2)==2) // Use regular expression to decompose the value into sub parameters here the 
        {
            parameter3.subparam1 = atoi(subparam1);
            strcpy(parameter3.subparam2, subparam2);
        }
    }     
}

```

Now in our main (or another function), we call the cfg_read function that will read the entire file and fill the parameters by calling the cfg_parser function.
```c
    // Read the configuration file
    if(cfg_read(cfg_file_path, cfg_parser)==false)
    {
        printf("Error loading configuration file. Make sure the file exists in %s\n", cfg_file_path);
    }
```
In C++, you may want to cast your cfg_file_path to (char*).

Now, you are ready and your parameters are loaded

# Complete example

```c
#include<stdio.h>
#include<cfg.h>

// We define few parameters to fill
char parameter1[256]; // a string parameter
int parameter2; // an integer parameter

// The path of the file to load
const char *cfg_file_path = "/etc/myconfig"

// A more complex parameter
struct paramtype{
    int subparam1;
    char subparam2[256];
}
struct paramtype parameter3;

/**
 * \fn void cfg_parser(char* key, char* val)
 * \brief Parses one entry from the configuration file
 *
 * \param key      The configuration parameter name
 * \param val      The configuration value (as string)
 * 
 * \return nothing.
 */
void cfg_parser(char* key, char* val)
{
    // Simple key value configuration
    // a string parameter   ex : parameter1 some text
    if(strcmp(key,"parameter1")==0)
    {
        strcpy(parameter1,val); // Copy the parameter value to the variable
    }
    // an integer parameter ex : parameter2 100
    else if (strcmp(key,"parameter2")==0)
    {
        parameter2 = atoi(val); // Convert the value to an integer
    }
    else if(strcmp(key,"parameter3")==0) // A more complex parameter for example parameter3 100:hello
    {
        char subparam1[UDP_MAXADDR_SIZE];
        char subparam2[UDP_MAXPORT_SIZE];
        
        if(sscanf(val,"%[^:]:%s", subparam1, subparam2)==2) // Use regular expression to decompose the value into sub parameters here the 
        {
            parameter3.subparam1 = atoi(subparam1);
            strcpy(parameter3.subparam2, subparam2);
        }
    }     
}

int main(int argc, char ** argv)
{
    // Read the configuration file
    if(cfg_read(cfg_file_path, cfg_parser)==false)
    {
        printf("Error loading configuration file. Make sure the file exists in %s\n", cfg_file_path);
    }
    // Now our parameters are all loaded successfully, time to play
}
```
# Information
This is one of multiple libraries I have developed to simplify some tasks we do with C on linux. The objective is for it to be open source, eazy to use and compatible with both c and cpp. The build system is make and is compatible with gcc building system. It is very eazy to use this with cmake or other build systems. All these libraries have been tested on raspberry pi with raspbian. They help starting a new application that requires configuration, communication with arduino tools and spreading information between multiple services on the raspberry pi.

The licence is MIT, so you can use this code in your projects without worrying about licence contamination that could happen when using GPL licences. So you still can use it for free in commercial applications.

Tests and bugfixes are welcome. Just clone it, repare it and send a pull request. I want to keep this code as clean and simple as possible so please avoid feature creaping.

# Useful links
Check out my [uart library](https://github.com/ParisNeo/uart) built in the same spirit as this library.
Check out my [udp library](https://github.com/ParisNeo/udp) built in the same spirit as this library.


