#pragma once

#define LogMsg(colour, time, msg) GEngine->AddOnScreenDebugMessage(-1, (time), (colour), TEXT(msg), false)
#define LogMsgFmt(colour, time, msg, ...) GEngine->AddOnScreenDebugMessage(-1, (time), (colour), FString::Printf(TEXT(msg), __VA_ARGS__), false)

#define info(...)  LogMsgFmt(FColor::Green,  15.f, __VA_ARGS__)
#define warn(...)  LogMsgFmt(FColor::Yellow, 15.f, __VA_ARGS__)
#define err(...)   LogMsgFmt(FColor::Red,    15.f, __VA_ARGS__)
#define debug(...) LogMsgFmt(FColor::Blue,   15.f, __VA_ARGS__)