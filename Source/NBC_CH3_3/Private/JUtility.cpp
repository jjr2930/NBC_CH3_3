#include "JUtility.h"


JUtility::JUtility()
{
}

JUtility::~JUtility()
{
}

void JUtility::Log(FString Format , ...)
{
    Print(Format, FColor::Blue);
}

void JUtility::Warning(FString Format, ...)
{
    Print(Format, FColor::Blue);
}

void JUtility::Error(FString Format, ...)
{
    Print(Format, FColor::Red);
}

void JUtility::Print(FString Format, FColor Color, ...)
{
    va_list Args;
    va_start(Args, Format);
    const FString Message = FString::Printf(*Format, Args);
    va_end(Args);

    UE_LOG(LogTemp, Log, TEXT("%s"), *Message);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, Color, Message);
    }
}
