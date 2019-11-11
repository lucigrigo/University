package com.poo.labvisitor.task1.document;

import com.poo.labvisitor.task1.Visitors.Visitor;
import org.w3c.dom.Text;

public class BoldTextSegment extends TextSegment {

    public BoldTextSegment(String content) {
        super(content);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}
