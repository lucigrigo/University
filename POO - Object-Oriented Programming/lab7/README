# Visitor & OOP Concepts Lab

The purpose of the first and main task is to use the Visitor pattern to generate two types of formatted text,
one in dokuwiki syntax, one in markdown syntax.

In the second task you need to use an API that has a visitor design. Follow the instructions from JavaFilesVisitor class.

## Syntax specs

* Dokuwiki (the one use for our lab's wiki): https://www.dokuwiki.org/wiki:syntax
* Markdown (used by bitbucket, jira, github): https://confluence.atlassian.com/bitbucketserver/markdown-syntax-guide-776639995.html

Types of text parts you need to convert:
* Italic:
    * dokuwiki: //text//
    * markdown: *text* or _text_
* Bold:
    * dokuwiki: **text**
    *markdown: **text** or __text__
* External urls:
    * dokuwiki: [[www.google.com|Google]]
    * markdown: [an example](http://www.example.com/)

The plain text you leave as is.

## Architecture of the implementation:

Entry point:
    * Test class, run its main
        * uncomment its code after you have implemented the required classes

TextSegment - these are the objects needed to be visited
    * ItalicTextSegment
    * BoldTextSegment
    * UrlSegment
    * PlainTextSegment

DocumentVisitor - the interface implemented by all the visitors applied on TextSegment objects
    * DokuWikiVisitor
    * MarkdownVisitor

WikiGenerator
    - applies the visitors on a collection of TextSegment objects
    - uses the visitors' getDocument() method to obtain the document string and a StringBuilder object

+---------------------------+
| TextSegment               |
+---------------------------+
| - content                 |
+---------------------------+                               +--------------------------------+
| + accept(DocumentVisitor) |------------------------------>| DocumentVisitor                |
+---------------------------+                               +--------------------------------+
  ^                                                         | + visit(ItalicTextSegment)     |
  |                                                         | + visit(BoldTextSegment)       |
  |  +-------------------+                                  | + visit(UrlSegment)            |
  |- | ItalicTextSegment |                                  | + visit(PlainTextSegment)      |
  |  +-------------------+                                  | + getDocument(): StringBuilder |
  |                                                         +--------------------------------+
  |  +-------------------+                                    ˆ
  |- | BoldTextSegment   |                                    |
  |  +-------------------+                                    | +------------------+
  |                                                           |-| DokuWikiVisitor  |
  |  +-------------------+                                    | +------------------+
  |- | UrlSegment        |                                    |
  |  +-------------------+                                    | +------------------+
  |  | - url             |                                    |-| MarkdownVisitor  |
  |  | - description     |                                      +------------------+
  |  +--------------------
  |
  |  +-------------------+
  |- | PlainTextSegment  |
     +-------------------+