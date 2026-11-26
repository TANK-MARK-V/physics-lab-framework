public class Calculations {

    // Обобщённый метод: T может быть только наследником Number (Integer, Double, Float и т.д.)
    public static <T extends Number> double average(T[] data) {
        if (data == null || data.length == 0) {
            throw new IllegalArgumentException("Average: массив пуст!");
        }
        
        double sum = 0.0;
        for (T item : data) {
            sum += item.doubleValue(); // Используем метод из класса Number
        }
        
        return sum / data.length;
    }
}