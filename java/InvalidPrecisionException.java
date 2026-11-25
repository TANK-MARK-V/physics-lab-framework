public class InvalidPrecisionException extends RuntimeException {
    public InvalidPrecisionException(int precision) {
        super("Ошибка: точность не может быть отрицательной (" + precision + ")");
    }
}