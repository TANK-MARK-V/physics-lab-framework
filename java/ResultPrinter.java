public class ResultPrinter {
    public static void print(CalculationResult result) {
        // В Java 17+ (с паттерн-матчингом) или Java 21
        switch (result) {
            case NumberResult n -> System.out.println("Результат (число): " + n.value());
            case ErrorResult e -> System.out.println("Результат (с погрешностью): " + e.quantity());
            case TextResult t -> System.out.println("Результат (ошибка): " + t.message());
        }
    }
}