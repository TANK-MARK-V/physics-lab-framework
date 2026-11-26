import java.util.Objects;

public class PhysicalQuantity implements Comparable<PhysicalQuantity> {
    private final double value; // Среднее значение
    private final double error; // Погрешность

    public PhysicalQuantity(double value, double error) {
        this.value = value;
        this.error = Math.abs(error); // Погрешность всегда положительная
        System.out.println("[PhysicalQuantity] Создана: " + this.value + " ± " + this.error);
    }

    public double getValue() { return value; }
    public double getError() { return error; }

    // Эмуляция перегрузки оператора "+"
    public PhysicalQuantity plus(PhysicalQuantity other) {
        return new PhysicalQuantity(this.value + other.value, this.error + other.error);
    }

    // Эмуляция перегрузки оператора "*"
    public PhysicalQuantity times(int count) {
        return new PhysicalQuantity(this.value * count, this.error * count);
    }

    // Переопределение equals (сравнение по значению и погрешности)
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PhysicalQuantity that = (PhysicalQuantity) o;
        return Double.compare(that.value, value) == 0 && 
               Double.compare(that.error, error) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(value, error);
    }

    // Реализация Comparable (вместо оператора <=>)
    @Override
    public int compareTo(PhysicalQuantity other) {
        return Double.compare(this.value, other.value);
    }

    // Переопределение toString (аналог operator<< для вывода)
    @Override
    public String toString() {
        return value + " ± " + error;
    }
}