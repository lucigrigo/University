package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public enum LogLevel {
    Info,
    Debug,
    Warning,
    Error,
    FunctionalMessage,
    FunctionalError;

    static EnumSet<LogLevel> all() {
        return EnumSet.allOf(LogLevel.class);
    }
}

