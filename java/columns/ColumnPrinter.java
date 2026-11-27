package columns;
public class ColumnPrinter {
    // Этот метод может обращаться к полю name напрямую, 
    // потому что мы в том же пакете (package-private).
    // В C++ для этого нужен был бы friend.
    public static void printRawName(BaseColumn column) {
        System.out.println("Package-private доступ к имени: " + column.name);
    }
}