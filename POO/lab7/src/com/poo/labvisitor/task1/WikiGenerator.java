package com.poo.labvisitor.task1;

import com.poo.labvisitor.task1.Visitors.DokuWikiVisitor;
import com.poo.labvisitor.task1.Visitors.MarkdownVisitor;
import com.poo.labvisitor.task1.document.TextSegment;

import java.util.List;

/**
 * Uses visitors to parse documents and provide dokuwiki and markdown outputs.
 */
public class WikiGenerator {

    private final List<TextSegment> textSegments;

    public WikiGenerator(List<TextSegment> textSegments) {
        this.textSegments = textSegments;
    }

    public StringBuilder getDOCWRONG(){
        DokuWikiVisitor dokuWikiVisitor = new DokuWikiVisitor();
        textSegments.get(0).acceptWRONG(dokuWikiVisitor);
        return dokuWikiVisitor.getDocument();
    }

    public StringBuilder getDokuWikiDocument() {
        // TODO apply dokuwiki visitor on the text segment
        DokuWikiVisitor dokuWikiVisitor = new DokuWikiVisitor();
        for(TextSegment textSegment : textSegments) {
            textSegment.accept(dokuWikiVisitor);
        }
        return dokuWikiVisitor.getDocument();
    }

    public StringBuilder getMarkdownDocument() {
        // TODO apply Markdown visitor on the text segments
        MarkdownVisitor markdownVisitor = new MarkdownVisitor();
        for(TextSegment textSegment : textSegments){
            textSegment.accept(markdownVisitor);
        }
        return markdownVisitor.getDocument();
    }
}
