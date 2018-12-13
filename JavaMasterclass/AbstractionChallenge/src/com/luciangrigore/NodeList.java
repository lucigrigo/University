package com.luciangrigore;

import com.luciangrigore.ListItem;

/**
 * Created by dev on 11/10/2015.
 */
public interface NodeList {
    ListItem getRoot();
    boolean addItem(ListItem item);
    boolean removeItem(ListItem item);
    void traverse(ListItem root);
}
