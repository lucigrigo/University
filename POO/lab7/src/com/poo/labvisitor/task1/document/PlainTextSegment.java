package com.poo.labvisitor.task1.document;

import com.poo.labvisitor.task1.Visitors.Visitor;

public class PlainTextSegment extends TextSegment{

    public PlainTextSegment(String content) {
        super(content);
    }

    @Override
    public void accept(Visitor visitor) {
         visitor.visit(this);
    }
}
