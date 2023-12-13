#include<stdio.h>
#include<stdbool.h>

typedef struct { // without bitfields
    bool warn;
    bool error;
    bool info;
} Logger;

typedef enum { //with bitfields
// C interprets variables to be bitfields when it encounters << or | bit-wise operators.
    NONE = 0,                                   // 0b0000
    LOG_INFO = 1,                               // 0b0001
    LOG_WARN = 1<<1,                            // 0b0010
    LOG_ERROR = 1<<2,                           // 0b0100
    LOG_ERROR_AND_WARN = LOG_ERROR | LOG_WARN,  // 0b0110
    LOG_ALL = LOG_INFO | LOG_ERROR | LOG_WARN,  // 0b0111
} LOGGER;

int main()
{
    Logger logger;
    logger.warn = true;
    logger.error = true;
    logger.info = true;

    LOGGER log = LOG_ALL; // treated as an integer constant

    if(logger.warn && logger.error && logger.info) {
        // do something
    } else if (logger.warn && logger.error) {
        //do something
    } else if (logger.error) {
        //do something
    } else if (logger.info) {
        // do something
    } else if (logger.warn) {
        // do something
    }



    // Compact code
    switch (log) {
        case LOG_ALL : break;
        case LOG_ERROR_AND_WARN : break;
        case LOG_ERROR : break;
        case LOG_WARN : break;
        case LOG_INFO : break;
        case NONE : break;
    }
}