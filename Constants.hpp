#pragma once

#define MAX_LOG_VALUE_SIZE 20
#define JSON_LARGE 70
#define JSON_SMALL 25
#define REQUEST_BUFFER 85
#define LOG_FILE_NAME "log"
#define CFG_FILE_NAME "svr"
#define INITIAL_TERM 1
#define NOBODY_YET '-'

// RPC keys
#define RPC_DELIMITER '}'
#define RPC_TYPE "r"
#define RPC_TERM "t"
#define RPC_LEADER "l"
#define RPC_CANDIDATE "c"
#define RPC_PREV_IDX "pi"
#define RPC_PREV_TERM "pt"
#define RPC_LAST_IDX "li"
#define RPC_LAST_TERM "lt"
#define RPC_VALUE "v"
#define RPC_SUCCESS "v"
