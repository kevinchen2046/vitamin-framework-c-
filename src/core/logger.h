#ifndef VITAMIN_LOGGER
#define VITAMIN_LOGGER

class Logger
{
    public:
        Logger();
        static void line(const char *__format, ...);
        static void grey(const char *__format, ...);
        static void log(const char *__format, ...);
        static void info(const char *__format, ...);
        static void warn(const char *__format, ...);
        static void debug(const char *__format, ...);
        static void error(const char *__format, ...);
    private:
        static void __out(const char *__format, ...);
};
#endif