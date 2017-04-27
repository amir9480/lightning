#include "llog.h"

LNAMESPACE_BEGIN

#if LTARGET==LTARGET_DEBUG

__Log_Manager __Log_Manager::get;

__Log_Manager::__Log_Manager():__log_repeat(1)
{
    __logfile.open(LLOG_FILE,Lightning::LFile::IOType::IOType_Write);
    __logfile.close();
    __logfile.open(LLOG_FILE,Lightning::LFile::IOType::IOType_Append);
    __logfile.write(LString("Welcome to Lightning "));
    __logfile.write(LString(LIGHTNING_VERSION));
    __logfile.write(LString("\n---------------------------------------------\n How to find by message type? ---> [A]=Asserts - [E]=Errors - [W]=Warnings - [L]=Logs\n---------------------------------------------\n"));
    __logfile.write(LString(" MessageType - File - Message - Repeats \n---------------------------------------------\n"));
    __logfile.flush();
}

__Log_Manager::__Log_Manager(const __Log_Manager &_in)
{
    LUNUSED(_in);
}

__Log_Manager::__Log_Manager(__Log_Manager &&_in)
{
    LUNUSED(_in);
}

__Log_Manager::~__Log_Manager()
{
    __logfile.write(LSTR("\n\n\n-Lightning log end"));
    __logfile.close();
}

void __Log_Manager::addLog(const LString &_message, const LString &_filename, const i32 &_line)
{
    if(_message==__lastlog)
    {
        __log_repeat++;
        return;
    }
    else
    {
        if(!__lastlog.isEmpty())
            __logfile.write(LSTR(" (")+LString::fromInt(__log_repeat)+L")\n");
    }
    __lastlog=_message;
    __log_repeat=1;
    __logfile.write(L"[L] Message from "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message);
    __logfile.flush();
}

void __Log_Manager::addWarning(const LString &_message, const LString &_filename, const i32 &_line)
{
    if(_message==__lastlog)
    {
        __log_repeat++;
        return;
    }
    else
    {
        if(!__lastlog.isEmpty())
            __logfile.write(LSTR(" (")+LString::fromInt(__log_repeat)+L")\n");
    }
    __lastlog=_message;
    __log_repeat=1;
    __logfile.write(L"[W] *WARNING* in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message);
    __logfile.flush();
}

void __Log_Manager::addError(const LString &_message, const LString &_filename, const i32 &_line)
{
    if(_message==__lastlog)
    {
        __log_repeat++;
        return;
    }
    else
    {
        if(!__lastlog.isEmpty())
            __logfile.write(LSTR(" (")+LString::fromInt(__log_repeat)+L")\n");
    }
    __lastlog=_message;
    __log_repeat=1;
    __logfile.write(L"\n[E] !***ERROR***! in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message);
    __logfile.flush();
}

void __Log_Manager::addAssert(const LString &_message, const LString &_filename, const i32 &_line)
{
    __lastlog=_message;
    __log_repeat=1;
    __logfile.write(LSTR("\n\n==================================================\n\n"));
    __logfile.write(L"[A] ASSERT in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message);
    __logfile.write(LSTR("\nPROGRAM IS GOING TO BE CLOSED"));
    __logfile.write(LSTR("\n\n==================================================\n\n"));
    __logfile.flush();
    while (1)
        throw 1;
}

#endif//LTARGET==LTARGET_DEBUG

LNAMESPACE_END
