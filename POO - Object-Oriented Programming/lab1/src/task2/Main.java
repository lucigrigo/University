package task2;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Course curs = new Course();
        curs.setDescription("cursul de programare pe obiecte");
        curs.setTitle("POO");
        Scanner scanner = new Scanner(System.in);
        for (int i = 1; i < 5; i++) {
            System.out.println("Dati anul pentru studentul " + i + ":\n");
            int nr = 0;
            nr = scanner.nextInt();
            Student student = new Student();
//            student.name = "Student " + i;
            student.setName("Student " + i);
//            student.year = nr;
            student.setYear(nr);
            curs.getStudents().add(student);
        }
        System.out.println("\nAfisare lista studenti:\n");
        System.out.println("Dati anul in care doriti sa vedeti toti studentii:\n");
        int an = 0;
        an = scanner.nextInt();
        for (Student student : curs.filterYear(curs.getStudents(), an)) {
            System.out.println("Student " + student.getName() + " din anul " + student.getYear());
        }

        // TASK 3
        Student stud1 = new Student();
        Student stud2 = new Student();
//        stud1.name = stud2.name = "Marius";
        stud1.setName("Marius");
        stud1.setYear(2);
//        stud1.year = stud2.year = 1;
        stud1.setName("Marius");
        stud2.setYear(2);
        System.out.println(stud1.equals(stud2)); // expected false
        // pentru ca 'equals' compara obiectele in sine
        // nu atributele lor
    }
}
