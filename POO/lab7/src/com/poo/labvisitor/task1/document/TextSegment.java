package com.poo.labvisitor.task1.document;

import com.poo.labvisitor.task1.Visitors.Visitor;

/**
 * Represents a text segment of a document that needs to be parsed.
 */
public abstract class TextSegment {
    private String content;

    TextSegment(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }

    public abstract void accept(Visitor visitor);

    public void acceptWRONG(Visitor visitor){
        visitor.visit(this);
    }
}
