#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>  // ofstream
#include <iomanip>  // std::put_time
#include <iostream> // std::cerr 
#include <cstdio>
#include <cstring>  // std::strcat
#include <cstdlib>
#include <ctime>    // std::strftime
#include <memory>   // unique_ptr
#include <chrono>   // std::chrono::system_clock::now() and std::time_point

// some macros for log prefix
#define D       "::DEBUG::"
#define V       "::VERBOSE"
#define E       "::ERROR::"
#define I       "::INFO::"
#define fstr()  std::string(__func__) + "(): "
#define FN      fstr()

// helper functions
std::string now();

class logger
{
    static logger*  inst_ptr;
    std::ofstream   strm;
    std::string     log_filename;
    std::string     mode;

    // ctor, cpy ctor, and assignment operator 
    logger( ): strm( "./debug.log" ), log_filename( "./debug.log" ), mode(D){}
    logger( std::string name ): strm( name ), log_filename( name ), mode(D){}
    logger( const logger& lg ) {}
    logger& operator = ( const logger& lg ) { return *this; }

public:
    ~logger( )
    {
        std::cerr << "~logger(): flushing and closing " << log_filename << std::endl;
        strm.flush();
        strm.close();
        delete inst_ptr;
    }

    inline void flush_log(bool new_line=false)
    {
        if( new_line )
            strm << "\n";
        strm.flush();
    }

    static inline logger* instance( std::string fname="./debug.log" )
    {
        if( !inst_ptr )
        {
            inst_ptr = new logger( fname );
        }
        return inst_ptr;
    }

    inline void set_mode( std::string md="DEBUG" )
    {
        mode = md;
    }

    template <typename toPrint>
    std::ofstream& operator<<( const toPrint& msg )
    {
        if( strm.is_open() && mode == "OFF" )
        {
            std::cerr << "Mode is set to OFF, closing log_file: " << log_filename << std::endl;
            strm.flush();
            strm.close();
            return strm;
        }
        else if( strm.is_open() )
        {
            strm << now() <<  mode << " " <<  msg;
            strm.flush();
        }
        return strm;
    }

    inline void log( std::string&& msg, bool log_prefix=true )
    {
        if( inst_ptr->strm.is_open() )
        {
            if( log_prefix )
            {
                strm << now() << mode  << " " << msg;
            }
            else
            {
                strm << msg;
            }
        }
        else
        {
            return;
        }
        strm.flush();
    }
};
#endif