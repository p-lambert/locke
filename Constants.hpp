#pragma once

#define MAX_LOG_VALUE_SIZE 20
#define JSON_LARGE 70
#define JSON_SMALL 25
#define REQUEST_BUFFER 85
#define LOG_FILE_NAME "log"
#define CFG_FILE_NAME "svr"
#define INITIAL_TERM 1
#define NOBODY_YET '-'

// AppendEntry payload keys
#define AE_TERM "t"
#define AE_LEADER "l"
#define AE_CANDIDATE "c"
#define AE_PREV_IDX "pi"
#define AE_PREV_TERM "pt"
#define AE_LAST_IDX "li"
#define AE_LAST_TERM "lt"
#define AE_VALUE "v"
#define AE_SUCCESS "v"
