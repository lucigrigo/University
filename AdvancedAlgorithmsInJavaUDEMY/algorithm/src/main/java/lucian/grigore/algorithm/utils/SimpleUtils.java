package lucian.grigore.algorithm.utils;

public class SimpleUtils {

    public boolean stringToBoolean(String value) {
        if (value == null) {
            return false;
        }
        if ((value.equalsIgnoreCase("n") || (value.equalsIgnoreCase("false")) || value.equalsIgnoreCase("No"))) {
            return false;
        }
        return true;
    }

    public FileType getFileTypeByCode(int code) {
        return FileType.match(code);
    }

    public FileType getFileTypeByName(String name) {
        return FileType.match(name);
    }

    public enum FileType {
        JPEG(1, "jpeg"),
        TEXT(2, "text"),
        PDF(3, "pdf");

        private int code;
        private String name;

        FileType(int code, String name) {
            this.code = code;
            this.name = name;
        }

        public static FileType match(int code) {
            for (FileType f : FileType.values()) {
                if (f.code == code) {
                    return f;
                }
            }
            return null;
        }

        public static FileType match(String name) {
            for (FileType f : FileType.values()) {
                if (f.name.equalsIgnoreCase(name)) {
                    return f;
                }
            }
            return null;
        }
    }
}
