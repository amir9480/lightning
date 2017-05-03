#ifndef LLOG_H
#define LLOG_H

#include "ldefines.h"
#include "lstring.h"
#include "lfile.h"
#include "lutility.h"

LNAMESPACE_BEGIN

#if LTARGET==LTARGET_DEBUG

// if you want to see where your log will save show LLOG_FILE

#if LIGHTING_USING_NAMESPACE == 1

//! Add a message to log . first parameter is CONDITION that if was true then message will be add.
#define lLogMessage(CONDITION,MESSAGE) {if(CONDITION){Lightning::__Log_Manager::get.addLog((MESSAGE),__FILE__,__LINE__);}}

//! Add a warning to log. first parameter is CONDITION that if was true then second parameter (message) will be add.
#define lWarning(CONDITION,MESSAGE) {if(CONDITION){Lightning::__Log_Manager::get.addWarning((MESSAGE),__FILE__,__LINE__);}}

//! Add a Assert to log . if CONDITION was true program will close
#define lAssert(CONDITION,MESSAGE) {if(CONDITION){Lightning::__Log_Manager::get.addAssert((MESSAGE),__FILE__,__LINE__);}}

#define _lError2(CONDITION,MESSAGE){if(CONDITION){Lightning::__Log_Manager::get.addError((MESSAGE),__FILE__,__LINE__);return;}}
#define _lError3(CONDITION,MESSAGE,RETURN){if(CONDITION){Lightning::__Log_Manager::get.addError((MESSAGE),__FILE__,__LINE__);return (RETURN);}}

//! Add a Error to log and returns from function .first parameter is CONDITION that if was true then message will be add.
//! third parameter is what needs to be return . if you function returns void this parameter is not needed
#define lError(...) LOVERLOADED_MACRO(_lError,__VA_ARGS__)

//! Add a Error to log without return
#define lError2(CONDITION,MESSAGE){if(CONDITION){Lightning::__Log_Manager::get.addError((MESSAGE),__FILE__,__LINE__);}}

#else

//! Add a message to log . first parameter is CONDITION that if was true then message will be add.
#define lLogMessage(CONDITION,MESSAGE) {if(CONDITION){__Log_Manager::get.addLog((MESSAGE),__FILE__,__LINE__);}}

//! Add a warning to log. first parameter is CONDITION that if was true then second parameter (message) will be add.
#define lWarning(CONDITION,MESSAGE) {if(CONDITION){__Log_Manager::get.addWarning((MESSAGE),__FILE__,__LINE__);}}

//! Add a Assert to log . if CONDITION was true program will close
#define lAssert(CONDITION,MESSAGE) {if(CONDITION){__Log_Manager::get.addAssert((MESSAGE),__FILE__,__LINE__);}}


#define _lError2(CONDITION,MESSAGE){if(CONDITION){__Log_Manager::get.addError((MESSAGE),__FILE__,__LINE__);return;}}
#define _lError3(CONDITION,MESSAGE,RETURN){if(CONDITION){__Log_Manager::get.addError((MESSAGE),__FILE__,__LINE__);return (RETURN);}}

//! Add a Error to log and returns from function .first parameter is CONDITION that if was true then message will be add.
//! third parameter is what needs to be return . if you function returns void this parameter is not needed
#define lError(...) L_OVERLOADED_MACRO(_lError,__VA_ARGS__)

#endif// LIGHTING_USING_NAMESPACE

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



#else
#define lLogMessage(CONDITION,MESSAGE)
#define lWarning(CONDITION,MESSAGE)
#define lError(CONDITION,MESSAGE,RETURN)
#define lAssert(CONDITION,MESSAGE)
#endif// LTARGET==LTARGET_DEBUG
LNAMESPACE_END

#endif // LLOG_H
