#include "llog.h"
#include <stdio.h>
LNAMESPACE_BEGIN

#if LTARGET==LTARGET_DEBUG

__Log_Manager __Log_Manager::get;

__Log_Manager::__Log_Manager():__log_repeat(1)
{
    __logfile.open(LLOG_FILE,Lightning::LFile::IOType::IOTypeWrite);
    __logfile.close();
    __logfile.open(LLOG_FILE,Lightning::LFile::IOType::IOTypeAppend);
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
    LString _errormessage=L"[L] Log Message from "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message;
    lMemoryLogStartIgnore();
    __lastlog=_message;
    lMemoryLogEndIgnore();
    __log_repeat=1;
    __logfile.write(_errormessage);
    __logfile.flush();

    lSetConsoleColor(LConsoleColor::White);
    puts(_errormessage.toUTF8().getData());
    lSetConsoleColor(LConsoleColor::Cyan);
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
    LString _errormessage=L"[W] *WARNING* in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message;
    lMemoryLogStartIgnore();
    __lastlog=_message;
    lMemoryLogEndIgnore();
    __log_repeat=1;
    __logfile.write(_errormessage);
    __logfile.flush();

    lSetConsoleColor(LConsoleColor::Yellow);
    puts(_errormessage.toUTF8().getData());
    lSetConsoleColor(LConsoleColor::Cyan);
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
    LString errormessage=L"\n[E] !***ERROR***! in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message;
    lMemoryLogStartIgnore();
    __lastlog=_message;
    lMemoryLogEndIgnore();
    __log_repeat=1;
    __logfile.write(errormessage);
    __logfile.flush();

    lSetConsoleColor(LConsoleColor::Red);
    puts(errormessage.toUTF8().getData());
    lSetConsoleColor(LConsoleColor::Cyan);
}

void __Log_Manager::addAssert(const LString &_message, const LString &_filename, const i32 &_line)
{
    lMemoryLogStartIgnore();
    __lastlog=_message;
    lMemoryLogEndIgnore();
    LString _errormessage=L"[A] ASSERT in "+_filename+L"["+LString::fromInt(_line)+L"] = "+_message;
    __log_repeat=1;
    __logfile.write(LSTR("\n\n==================================================\n\n"));
    __logfile.write(_errormessage);
    __logfile.write(LSTR("\nPROGRAM IS GOING TO BE CLOSED"));
    __logfile.write(LSTR("\n\n==================================================\n\n"));
    __logfile.flush();

    lSetConsoleColor(LConsoleColor::Red);
    puts("\n\n==================================================\n\n");
    puts(_errormessage.toUTF8().getData());
    puts("\nPROGRAM IS GOING TO BE CLOSED");
    puts("\n\n==================================================\n\n");

    while (1)
        throw 1;
}

#endif//LTARGET==LTARGET_DEBUG

LNAMESPACE_END
