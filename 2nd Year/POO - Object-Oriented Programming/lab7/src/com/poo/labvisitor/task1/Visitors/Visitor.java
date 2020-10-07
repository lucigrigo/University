package com.poo.labvisitor.task1.Visitors;

import com.poo.labvisitor.task1.document.*;

public interface Visitor {

    void visit(PlainTextSegment plainTextSegment);

    void visit(ItalicTextSegment italicTextSegment);

    void visit(BoldTextSegment boldTextSegment);

    void visit(UrlSegment urlSegment);

    // doar pentru demonstratie
    void visit(TextSegment textSegment);
}
