#pragma once

#define MAX_LOG_VALUE_SIZE 70
#define MAX_JSON_SIZE 70
#define LOG_FILE_NAME "log"
#define CFG_FILE_NAME "svr"
#define INITIAL_TERM 1
#define NOBODY_YET '-'

// AppendEntry payload keys
#define AE_TERM "t"
#define AE_LEADER "l"
#define AE_PREV_IDX "pi"
#define AE_PREV_TERM "pt"
#define AE_VALUE "v"
