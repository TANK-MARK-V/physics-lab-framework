package demos;

import java.util.List;

public class LambdaDemo {

    public static void run() {
        System.out.println("\n--- ДЕМОНСТРАЦИЯ ЛЯМБД И ЗАХВАТА (Java) ---");

        // 1. Захват переменной
        int threshold = 5;
        // threshold = 10; // Если раскоментировать, будет ошибка компиляции
        // Variable used in lambda expression should be final or effectively final
        
        // Лямбда захватывает копию threshold (он effectively final)
        Runnable checkThreshold = () -> System.out.println("Лямбда видит threshold: " + threshold);
        
        checkThreshold.run();

        // 2. Аналог обобщённой лямбды (обобщённый метод)
        List<Integer> ints = List.of(1, 2, 3);
        List<String> strings = List.of("alpha", "beta", "gamma");
        
        System.out.println("Обобщённый метод:");
        printAll(ints);
        printAll(strings);
    }

    // В Java нет обобщённых лямбд, поэтому пишем обобщённый метод (static <T>)
    public static <T> void printAll(List<T> list) {
        System.out.print("  Элементы: ");
        for (T item : list) {
            System.out.print(item + " ");
        }
        System.out.println();
    }
}