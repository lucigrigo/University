package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public abstract class LoggerBase {

    public LoggerBase nextRef = null;
    public EnumSet<LogLevel> levels;

    public LoggerBase(EnumSet<LogLevel> enumSet) {
        this.levels = enumSet;
    }

    public void setNext(LoggerBase next) {
        this.nextRef = next;
    }

    public abstract void writeMessage(String message);

    public void message(String message,
                        LogLevel logLevel) {
        for (LogLevel logLevel1 : this.levels) {
            if (logLevel1 == logLevel) {
                writeMessage(message);
                // break;
            }
        }
        if (this.nextRef != null) {
            this.nextRef.message(message, logLevel);
        }
    }
}
