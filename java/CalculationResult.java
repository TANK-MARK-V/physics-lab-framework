public sealed interface CalculationResult 
    permits NumberResult, ErrorResult, TextResult {
}

record NumberResult(double value) implements CalculationResult {}
record ErrorResult(PhysicalQuantity quantity) implements CalculationResult {}
record TextResult(String message) implements CalculationResult {}