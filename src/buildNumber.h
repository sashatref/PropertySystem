#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)
#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define MAINTENANCE 0
#define BUILD 28

#define FULL_VER STRINGIZE(MAJOR_VERSION) "." STRINGIZE(MINOR_VERSION) "." STRINGIZE(MAINTENANCE) "." STRINGIZE(BUILD)
#define PRODUCT_VER STRINGIZE(MAJOR_VERSION) "." STRINGIZE(MINOR_VERSION) "." STRINGIZE(MAINTENANCE)

#define GIT_HASH "6805a9e9d2d8e52db2443c9e79cc7b51a1885093"
#define COMPILE_DATE "04.04.2020"
#define COMPILE_TIME "17:25:07"
