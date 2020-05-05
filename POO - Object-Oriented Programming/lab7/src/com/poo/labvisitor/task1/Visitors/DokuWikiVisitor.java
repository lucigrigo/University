package com.poo.labvisitor.task1.Visitors;

import com.poo.labvisitor.task1.document.BoldTextSegment;
import com.poo.labvisitor.task1.document.ItalicTextSegment;
import com.poo.labvisitor.task1.document.PlainTextSegment;
import com.poo.labvisitor.task1.document.TextSegment;
import com.poo.labvisitor.task1.document.UrlSegment;

public class DokuWikiVisitor implements Visitor {

    private StringBuilder document;

    public DokuWikiVisitor() {
        this.document = new StringBuilder();
    }

    @Override
    public void visit(TextSegment textSegment) {
        // tratam ca pe PlainTextSegment
        this.document.append(textSegment.getContent());
    }

    @Override
    public void visit(PlainTextSegment plainTextSegment) {
        this.document.append(plainTextSegment.getContent());
    }

    @Override
    public void visit(ItalicTextSegment italicTextSegment) {
        this.document.append("//");
        this.document.append(italicTextSegment.getContent());
        this.document.append("//");
    }

    @Override
    public void visit(BoldTextSegment boldTextSegment) {
        this.document.append("**");
        this.document.append(boldTextSegment.getContent());
        this.document.append("**");
    }

    @Override
    public void visit(UrlSegment urlSegment) {
        this.document.append("[[");
        this.document.append(urlSegment.getContent());
        this.document.append("|");
        this.document.append(urlSegment.getDescription());
        this.document.append("]]");
    }

    public StringBuilder getDocument() {
        return document;
    }
}
