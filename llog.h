#ifndef LLOG_H
#define LLOG_H

#include "ldefines.h"
#include "lstring.h"
#include "lfile.h"
#include "lutility.h"

LNAMESPACE_BEGIN

#if LTARGET==LTARGET_DEBUG

//! singlton class for manage log file
class __Log_Manager
{
private:
    __Log_Manager();
    __Log_Manager(const __Log_Manager& _in);
    __Log_Manager(__Log_Manager&& _in);
    virtual ~__Log_Manager();
public:
    static __Log_Manager get;

    void addLog(const LString &_message, const LString &_filename, const i32 &_line);
    void addWarning(const LString &_message, const LString &_filename, const i32 &_line);
    void addError(const LString &_message, const LString &_filename, const i32 &_line);
    void addAssert(const LString &_message, const LString &_filename, const i32 &_line);
private:
    LFile __logfile;
    LString __lastlog;
    i32 __log_repeat;
};

//! Add a message to log
#define lLogMessage(MESSAGE) __Log_Manager::get.addLog(MESSAGE,__FILE__,__LINE__)
//! Add a warning to log
#define lWarning(MESSAGE) __Log_Manager::get.addWarning(MESSAGE,__FILE__,__LINE__)
//! Add a Error to log
#define lError(MESSAGE) __Log_Manager::get.addError(MESSAGE,__FILE__,__LINE__)
//! Add a Assert to log . if CONDITION was true program will close
#define lAssert(CONDITION,MESSAGE)if(CONDITION)__Log_Manager::get.addAssert(MESSAGE,__FILE__,__LINE__)

#else
#define lLogMessage(MESSAGE)
#define lWarning(MESSAGE)
#define lError(MESSAGE)
#define lAssert(CONDITION,MESSAGE)
#endif// LTARGET==LTARGET_DEBUG

LNAMESPACE_END

#endif // LLOG_H
