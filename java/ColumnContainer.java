// T должен быть наследником BaseColumn
public class ColumnContainer<T extends BaseColumn> {
    private static final int MAX_SIZE = 128;
    private final Object[] items; // Используем Object[] для хранения любых наследников T
    private int size = 0;

    public ColumnContainer() {
        this.items = new Object[MAX_SIZE];
        System.out.println("[ColumnContainer] Создан (фиксированный размер: " + MAX_SIZE + ")");
    }

    public void add(T item) {
        if (size >= MAX_SIZE) {
            throw new ArrayIndexOutOfBoundsException("ColumnContainer: достигнут максимальный размер (128)!");
        }
        items[size] = item;
        size++;
    }

    public int size() {
        return size;
    }

    @SuppressWarnings("unchecked")
    public T get(int index) {
        if (index >= size) {
            throw new IndexOutOfBoundsException("ColumnContainer: индекс вне диапазона");
        }
        return (T) items[index]; // Приводим тип
    }

    // ОБОБЩЁННЫЙ МЕТОД внутри класса
    // U должен быть наследником T (аналог std::derived_from<U, T>)
    public <U extends T> void mergeFrom(ColumnContainer<U> other) {
        for (int i = 0; i < other.size(); i++) {
            // В Java clone() возвращает Object, приводим к BaseColumn
            BaseColumn cloned = other.get(i).clone();
            
            // Приводим к T и добавляем
            @SuppressWarnings("unchecked")
            T casted = (T) cloned;
            add(casted);
        }
    }
}