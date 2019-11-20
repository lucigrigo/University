package com.luciangrigore;

import javax.swing.plaf.synth.SynthTableUI;
import javax.swing.plaf.synth.SynthToolTipUI;
import java.util.*;
import java.util.function.Consumer;

public class Main {

    public static void main(String[] args) {
        Student s1 = new Student(12345, "Popa", "Rares", 7.5d);
        Student s2 = new Student(12333, "Popa", "Sandra", 7.5d);
        Student s3 = new Student(12344, "Grigorian", "Luchian", 5.0d);
        Student s4 = new Student(12222, "Caragea", "Caragiale", 10.0d);
        Student s5 = new Student(11111, "Olteanu", "Moldovean", 10.0d);

        System.out.println("-----\tTASK 1 & 2\t-----");
        List<Student> studentList = new ArrayList<>(Arrays.asList(s1, s2, s3, s4, s5));
        Collections.sort(studentList);
        for (Student student : studentList) {
            System.out.println(student.toString());
        }

        System.out.println("\n-----\tTASK 3\t-----");
        PriorityQueue<Student> studentPriorityQueue = new PriorityQueue<>((o1, o2)
                -> Long.compare(o2.getId(), o1.getId()));
        studentPriorityQueue.addAll(studentList);
        for (Student student : studentPriorityQueue) {
            System.out.println(student.toString());
        }

        System.out.println("\n-----\tTASK 4 & 5\t-----");
        HashMap<Student, List<String>> studentCourses = new HashMap<>();
        studentCourses.put(s1, Arrays.asList("Germana", "Fizica", "Sociologie"));
        studentCourses.put(s2, Arrays.asList("Germana", "Sport", "Romana"));
        studentCourses.put(s3, Arrays.asList("Mate", "Info", "Chimie"));
        studentCourses.put(s4, Arrays.asList("Mate", "Info", "Chimie", "AA"));
        studentCourses.put(s5, Arrays.asList("MN", "IOCLA", "Mate1", "LFA"));
        for (Map.Entry<Student, List<String>> studentListEntry : studentCourses.entrySet()) {
            System.out.println(studentListEntry.getKey().toString());
            System.out.println("\tsi are materiile:");
            for (String course : studentListEntry.getValue()) {
                System.out.println("\t\t" + course);
            }
        }

        System.out.println("\n-----\tTASK 6\t-----");
        // HashSet
        DoarPareHashSet doarPareHashSet = new DoarPareHashSet();
        doarPareHashSet.add(1);
        doarPareHashSet.add(21);
        doarPareHashSet.add(3000);
        doarPareHashSet.add(400);
        doarPareHashSet.add(51);
        doarPareHashSet.add(60);
        doarPareHashSet.add(5);
        doarPareHashSet.add(10);
        doarPareHashSet.add(9);
        doarPareHashSet.add(100);
        System.out.println("Pentru HashSet:");
        Iterator iterator = doarPareHashSet.iterator();
        while (iterator.hasNext()) {
            System.out.println("\t" + iterator.next());
        }
        // LinkedHashSet
        DoarPareLinkedHashSet doarPareLinkedHashSet = new DoarPareLinkedHashSet();
        doarPareLinkedHashSet.add(1);
        doarPareLinkedHashSet.add(21);
        doarPareLinkedHashSet.add(3000);
        doarPareLinkedHashSet.add(400);
        doarPareLinkedHashSet.add(51);
        doarPareLinkedHashSet.add(60);
        doarPareLinkedHashSet.add(5);
        doarPareLinkedHashSet.add(10);
        doarPareLinkedHashSet.add(9);
        doarPareLinkedHashSet.add(100);
        System.out.println("Pentru LinkedHashSet:");
        iterator = doarPareLinkedHashSet.iterator();
        while (iterator.hasNext()) {
            System.out.println("\t" + iterator.next());
        }
        // TreeSet
        DoarPareTreeSet doarPareTreeSet = new DoarPareTreeSet();
        doarPareTreeSet.add(1);
        doarPareTreeSet.add(21);
        doarPareTreeSet.add(3000);
        doarPareTreeSet.add(400);
        doarPareTreeSet.add(51);
        doarPareTreeSet.add(60);
        doarPareTreeSet.add(5);
        doarPareTreeSet.add(10);
        doarPareTreeSet.add(9);
        doarPareTreeSet.add(100);
        System.out.println("Pentru TreeSet:");
        iterator = doarPareTreeSet.iterator();
        while (iterator.hasNext()) {
            System.out.println("\t" + iterator.next());
        }
    }
}
