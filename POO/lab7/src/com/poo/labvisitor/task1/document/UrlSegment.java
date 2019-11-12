package com.poo.labvisitor.task1.document;

import com.poo.labvisitor.task1.Visitors.Visitor;

public class UrlSegment extends TextSegment {
    private String description;

    public UrlSegment(String content, String description) {
        super(content);
        this.description = description;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}
