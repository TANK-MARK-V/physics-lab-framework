// import columns.*;
// import table.*;
import demos.*;
// import exceptions.*;
// import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР-7\n");

        AlgorithmsDemo.run();

        System.out.println("\n--- std::variant (sealed interface) ---");
        CalculationResult res1 = new NumberResult(42.5);
        CalculationResult res2 = new ErrorResult(new PhysicalQuantity(10.5, 0.2));
        CalculationResult res3 = new TextResult("Неизвестная переменная");

        ResultPrinter.print(res1);
        ResultPrinter.print(res2);
        ResultPrinter.print(res3);

        // Демонстрация лямбд (Java)
        LambdaDemo.run();

        System.out.println("\n=== КОНЕЦ ===");
    }
}