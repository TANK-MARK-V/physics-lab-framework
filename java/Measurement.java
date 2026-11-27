import java.util.Objects;

public class Measurement {
    public String student;
    public String parameter;
    public double value;
    public double error;
    public boolean processed;

    public Measurement(String student, String parameter, double value, double error, boolean processed) {
        this.student = student;
        this.parameter = parameter;
        this.value = value;
        this.error = error;
        this.processed = processed;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Measurement that = (Measurement) o;
        return Double.compare(that.value, value) == 0 &&
               Double.compare(that.error, error) == 0 &&
               processed == that.processed &&
               student.equals(that.student) &&
               parameter.equals(that.parameter);
    }

    @Override
    public int hashCode() {
        return Objects.hash(student, parameter, value, error, processed);
    }

    @Override
    public String toString() {
        return student + " (" + parameter + ": " + value + " ± " + error + ")";
    }
}