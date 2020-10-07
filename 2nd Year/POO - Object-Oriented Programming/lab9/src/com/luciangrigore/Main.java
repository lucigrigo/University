package com.luciangrigore;

import java.util.*;

public class Main {

    public static void main(String[] args) {
        MyHashMap<Integer, Student> newHashMap = new MyHashMap<>();

        Student s1 = new Student("Edu", 10.0f);
        Student s2 = new Student("Alexprst", 6.5f);
        Student s3 = new Student("lukprst", 5.499f);

        newHashMap.put(s1);
        newHashMap.put(s2);
        newHashMap.put(s3);

        for (Iterator<Entry<Integer, Student>> it = newHashMap.get(); it.hasNext(); ) {
            Entry<Integer, Student> entry = it.next();
            System.out.println(entry.getValue().hashCode() + " " + entry.getValue().getName()
                    + " " + entry.getValue().getGrade());
        }

        MyVector3 v1 = new MyVector3(1, 2, 3);
        MyVector3 v2 = new MyVector3(-2, 8, 5);
        MyVector3 v3 = new MyVector3(10, -2, 4);
        MyVector3 v4 = new MyVector3(12, -12, 5);

        List<Sumabil> newList = new ArrayList<>(Arrays.asList(v1, v2, v3, v4));
        MyVector3 sum = new MyVector3(0, 0, 0);
        computeSum(newList, sum);
        System.out.println("Suma pe axe este:\n"
                + "\t " + sum.getX()
                + "\t " + sum.getY()
                + "\t " + sum.getZ());
    }

    static <T extends Sumabil> void computeSum(Collection<T> collection, T sumCheck) {
        for (T o : collection) {
            sumCheck.addValue(o);
        }
    }
}
